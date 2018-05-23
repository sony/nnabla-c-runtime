// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "pooling.h"
#include "../../utilities/shape.h"
#include <math.h>

rt_function_error_t allocate_pooling(rt_function_t *f,
                                     pooling_context_t *context,
                                     pooling_private_t *p) {
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  p->input_shape = clone_list(f->inputs[0]->shape);
  p->output_shape = clone_list(f->outputs[0]->shape);
  p->input_n_kernel_size_diff = p->input_shape.size - context->kernel.size;
  if (context->stride.size == 0) {
    context->stride = clone_list(context->kernel);
  } else {
    if (context->kernel.size != context->stride.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
    if (context->kernel.size > p->input_shape.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
  }
  if (context->kernel.size != 2) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (context->kernel.size != context->pad.size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  // Calc and set output shape.
  rt_list_t shape = allocate_list(context->kernel.size);
  int i;
  for (i = 0; i < context->kernel.size; i++) {
    shape.data[i] = p->input_shape.data[i + p->input_n_kernel_size_diff];
  }
  for (i = 0; i < shape.size; i++) {
    shape.data[i] += 2 * context->pad.data[i];
    if (context->ignore_border) {
      shape.data[i] = (int)((shape.data[i] - context->kernel.data[i]) /
                            context->stride.data[i]) +
                      1;
    } else {
      shape.data[i] = ceil(shape.data[i] * 1.0 / context->stride.data[i]);
    }
  }
  for (i = 0; i < p->input_shape.size; i++) {
    if (i < p->input_n_kernel_size_diff) {
      p->output_shape.data[i] = p->input_shape.data[i];
    } else {
      p->output_shape.data[i] = shape.data[i - p->input_n_kernel_size_diff];
    }
  }
  free_list(shape);

  // Calc x_stride and y_stride.
  const rt_list_t input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  const rt_list_t output_strides =
      calc_contiguous_strides(f->outputs[0]->shape);
  p->x_stride = (p->input_n_kernel_size_diff == 0)
                    ? calc_shape_size(f->inputs[0]->shape)
                    : input_strides.data[p->input_n_kernel_size_diff - 1];
  p->y_stride = (p->input_n_kernel_size_diff == 0)
                    ? calc_shape_size(f->outputs[0]->shape)
                    : output_strides.data[p->input_n_kernel_size_diff - 1];
  free_list(input_strides);
  free_list(output_strides);

  // Init calc_context.
  p->calc_context.hstart = 0;
  p->calc_context.hend = 0;
  p->calc_context.wstart = 0;
  p->calc_context.wend = 0;
  p->calc_context.wx = p->input_shape.data[p->input_n_kernel_size_diff + 1];
  p->calc_context.pool_size = 0;
  p->calc_context.x = f->inputs[0];
  p->calc_context.get_x = select_getter(p->calc_context.x);
  p->calc_context.y = f->outputs[0];
  p->calc_context.set_y = select_setter(p->calc_context.y);
  p->calc_context.offset_x = 0;
  p->calc_context.offset_y = 0;
  p->calc_context.including_pad = context->including_pad;

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_pooling(pooling_private_t *p) {
  free_list(p->input_shape);
  free_list(p->output_shape);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pooling(rt_function_t *f, pooling_context_t *context,
                                 pooling_private_t *p,
                                 exec_pooling_func_t exec) {
  float *y = (float *)(p->calc_context.y->data);
  const int hx = p->input_shape.data[p->input_n_kernel_size_diff + 0];
  const int wx = p->calc_context.wx;
  const int hy = p->output_shape.data[p->input_n_kernel_size_diff + 0];
  const int wy = p->output_shape.data[p->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / p->x_stride;
  int n;
  for (n = 0; n < n_map; n++) {
    int iy;
    for (iy = 0; iy < hy; iy++) {
      int jy;
      for (jy = 0; jy < wy; jy++) {
        int hstart = iy * hstride - hpad;
        int wstart = jy * wstride - wpad;
        int hend = fminf(hstart + hkernel, hx + hpad);
        int wend = fminf(wstart + wkernel, wx + wpad);
        p->calc_context.pool_size = (hend - hstart) * (wend - wstart);
        p->calc_context.hstart = fmaxf(hstart, 0);
        p->calc_context.wstart = fmaxf(wstart, 0);
        p->calc_context.hend = fminf(hend, hx);
        p->calc_context.wend = fminf(wend, wx);
        int k = iy * wy + jy;
        float val = exec(p->calc_context);
        *(y + k + p->calc_context.offset_y) = val;
      }
    }
    p->calc_context.offset_x += p->x_stride;
    p->calc_context.offset_y += p->y_stride;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t
exec_pooling_generic(rt_function_t *f, pooling_context_t *context,
                                 pooling_private_t *p,
                                 exec_pooling_func_t exec) {
  const int hx = p->input_shape.data[p->input_n_kernel_size_diff + 0];
  const int wx = p->calc_context.wx;
  const int hy = p->output_shape.data[p->input_n_kernel_size_diff + 0];
  const int wy = p->output_shape.data[p->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / p->x_stride;
  int n;
  for (n = 0; n < n_map; n++) {
    int iy;
    for (iy = 0; iy < hy; iy++) {
      int jy;
      for (jy = 0; jy < wy; jy++) {
        int hstart = iy * hstride - hpad;
        int wstart = jy * wstride - wpad;
        int hend = fminf(hstart + hkernel, hx + hpad);
        int wend = fminf(wstart + wkernel, wx + wpad);
        p->calc_context.pool_size = (hend - hstart) * (wend - wstart);
        p->calc_context.hstart = fmaxf(hstart, 0);
        p->calc_context.wstart = fmaxf(wstart, 0);
        p->calc_context.hend = fminf(hend, hx);
        p->calc_context.wend = fminf(wend, wx);
        int k = iy * wy + jy;
        float val = exec(p->calc_context);
        p->calc_context.set_y(p->calc_context.y, k + p->calc_context.offset_y, val);
      }
    }
    p->calc_context.offset_x += p->x_stride;
    p->calc_context.offset_y += p->y_stride;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

float calc_max(pooling_calc_context_t calc) {
  int l = calc.hstart * calc.wx + calc.wstart;
  int ix;
  float *x = (float *)(calc.x->data);
  float max_val = *(x + l + calc.offset_x);
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      float val = *(x + jx + calc.offset_x);
      if (max_val < val) {
        max_val = val;
      }
    }
  }
  return max_val;
}

float calc_max_generic(pooling_calc_context_t calc) {
  int l = calc.hstart * calc.wx + calc.wstart;
  int ix;
  float max_val = calc.get_x(calc.x, l + calc.offset_x);
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      float val = calc.get_x(calc.x, jx + calc.offset_x);
      if (max_val < val) {
        max_val = val;
      }
    }
  }
  return max_val;
}

float calc_sum(pooling_calc_context_t calc) {
  float sum_val = 0.0f;
  int ix;
  float *x = (float *)(calc.x->data);
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      sum_val += *(x + jx + calc.offset_x);
    }
  }
  return sum_val;
}

float calc_sum_generic(pooling_calc_context_t calc) {
  float sum_val = 0.0f;
  int ix;
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      sum_val += calc.get_x(calc.x, jx + calc.offset_x);
    }
  }
  return sum_val;
}

float calc_average(pooling_calc_context_t calc) {
  float val = 0.0f;
  float average_val = 0.0f;
  float *x = (float *)(calc.x->data);
  if (!calc.including_pad) {
    calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
  }
  int ix;
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      val += *(x + jx + calc.offset_x);
    }
  }
  average_val = val / calc.pool_size;
  return average_val;
}

float calc_average_generic(pooling_calc_context_t calc) {
  float val = 0.0f;
  float average_val = 0.0f;
  if (!calc.including_pad) {
    calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
  }
  int ix;
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      val += calc.get_x(calc.x, jx + calc.offset_x);
    }
  }
  average_val = val / calc.pool_size;
  return average_val;
}
