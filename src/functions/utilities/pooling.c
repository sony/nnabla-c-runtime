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

#include <math.h>
#include "pooling.h"
#include "shape.h"

rt_function_error_t allocate_pooling(rt_function_t *f, pooling_context_t *context, pooling_private_t *private) {
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  private->input_shape = clone_list(f->inputs[0]->shape);
  private->output_shape = clone_list(f->outputs[0]->shape);
  private->input_n_kernel_size_diff = private->input_shape.size - context->kernel.size;
  if (context->stride.size == 0) {
    context->stride = clone_list(context->kernel);
  } else {
    if (context->kernel.size != context->stride.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
    if (context->kernel.size > private->input_shape.size) {
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
    shape.data[i] = private->input_shape.data[i + private->input_n_kernel_size_diff];
  }
  for (i = 0; i < shape.size; i++) {
    shape.data[i] += 2 * context->pad.data[i];
    if (context->ignore_border) {
      shape.data[i] = (int)((shape.data[i] - context->kernel.data[i]) / context->stride.data[i]) + 1;
    } else {
      shape.data[i] = ceil(shape.data[i] * 1.0 / context->stride.data[i]);
    }
  }
  for (i = 0; i < private->input_shape.size; i++) {
    if (i < private->input_n_kernel_size_diff) {
      private->output_shape.data[i] = private->input_shape.data[i];
    } else {
      private->output_shape.data[i] = shape.data[i - private->input_n_kernel_size_diff];
    }
  }
  free_list(shape);

  // Calc x_stride and y_stride.
  const rt_list_t input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  const rt_list_t output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  private->x_stride =
    (private->input_n_kernel_size_diff == 0) ? calc_shape_size(f->inputs[0]->shape) : input_strides.data[private->input_n_kernel_size_diff - 1];
  private->y_stride =
    (private->input_n_kernel_size_diff == 0) ? calc_shape_size(f->outputs[0]->shape) : output_strides.data[private->input_n_kernel_size_diff - 1];
  free_list(input_strides);
  free_list(output_strides);

  // Init calc_context.
  private->calc_context.hstart = 0;
  private->calc_context.hend = 0;
  private->calc_context.wstart = 0;
  private->calc_context.wend = 0;
  private->calc_context.wx = private->input_shape.data[private->input_n_kernel_size_diff + 1];
  private->calc_context.pool_size = 0;
  private->calc_context.x = (float *)(f->inputs[0]->data);
  private->calc_context.including_pad = context->including_pad;

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_pooling(pooling_private_t *private) {
  free_list(private->input_shape);
  free_list(private->output_shape);
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pooling(rt_function_t *f, pooling_context_t *context, pooling_private_t *private, exec_pooling_func_t exec) {
  float *y = (float *)(f->outputs[0]->data);
  const int hx = private->input_shape.data[private->input_n_kernel_size_diff + 0];
  const int wx = private->calc_context.wx;
  const int hy = private->output_shape.data[private->input_n_kernel_size_diff + 0];
  const int wy = private->output_shape.data[private->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / private->x_stride;
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
        private->calc_context.pool_size = (hend - hstart) * (wend - wstart);
        private->calc_context.hstart = fmaxf(hstart, 0);
        private->calc_context.wstart = fmaxf(wstart, 0);
        private->calc_context.hend = fminf(hend, hx);
        private->calc_context.wend = fminf(wend, wx);
        int k = iy * wy + jy;
        float val = exec(private->calc_context);
        y[k] = val;
      }
    }
    private->calc_context.x += private->x_stride;
    y += private->y_stride;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

float calc_max(pooling_calc_context_t calc) {
  int l = calc.hstart * calc.wx + calc.wstart;
  float max_val = calc.x[l];
  int ix;
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      float val = calc.x[jx];
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
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      sum_val += calc.x[jx];
    }
  }
  return sum_val;
}

float calc_average(pooling_calc_context_t calc) {
  float val = 0.0f;
  float average_val = 0.0f;
  if (!calc.including_pad) {
    calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
  }
  int ix;
  for (ix = calc.hstart; ix < calc.hend; ix++) {
    int jx;
    for (jx = ix * calc.wx + calc.wstart; jx < ix * calc.wx + calc.wend; jx++) {
      val += calc.x[jx];
    }
  }
  average_val = val / calc.pool_size;
  return average_val;
}
