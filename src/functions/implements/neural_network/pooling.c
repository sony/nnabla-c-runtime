// Copyright 2018,2019,2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
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
#include "../../utilities/fixedpoint.h"
#include "../../utilities/shape.h"
#include <float.h>
#include <limits.h>
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
  if (context->kernel.size != 2 && context->kernel.size != 3) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (context->kernel.size != context->pad.size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  // Calc and set output shape.
  rt_list_t shape = allocate_list(context->kernel.size);
  int i;
  for (i = 0; i < shape.size; i++) {
    int _w = p->input_shape.data[i + p->input_n_kernel_size_diff];
    int _k = context->kernel.data[i];
    int _s = context->stride.data[i];
    int _p = context->pad.data[i];
    shape.data[i] = (_w + _p - (context->ignore_border ? _k - _p : 1)) / _s + 1;
  }
  for (i = 0; i < p->input_shape.size; i++) {
    if (i < p->input_n_kernel_size_diff) {
      p->output_shape.data[i] = p->input_shape.data[i];
    } else {
      p->output_shape.data[i] = shape.data[i - p->input_n_kernel_size_diff];
    }
  }
  free_list(shape);

  // Calc x_map_size and y_map_size.
  p->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  p->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  p->x_map_size = (p->input_n_kernel_size_diff == 0)
                      ? calc_shape_size(f->inputs[0]->shape)
                      : p->input_strides.data[p->input_n_kernel_size_diff - 1];
  p->y_map_size = (p->input_n_kernel_size_diff == 0)
                      ? calc_shape_size(f->outputs[0]->shape)
                      : p->output_strides.data[p->input_n_kernel_size_diff - 1];

  // Init calc_context.
  p->calc_context.hstart = 0;
  p->calc_context.hend = 0;
  p->calc_context.wstart = 0;
  p->calc_context.wend = 0;
  p->calc_context.dstart = 0;
  p->calc_context.dend = 0;
  p->calc_context.pool_size = 0;
  p->calc_context.x = f->inputs[0];
  p->calc_context.get_x = select_getter(p->calc_context.x);
  p->calc_context.y = f->outputs[0];
  p->calc_context.set_y = select_setter(p->calc_context.y);
  p->calc_context.including_pad = context->including_pad;

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_pooling(pooling_private_t *p) {
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->input_strides);
  free_list(p->output_strides);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pooling(rt_function_t *f, pooling_context_t *context,
                                 pooling_private_t *p,
                                 exec_pooling_func_t exec) {
  float *y = (float *)(p->calc_context.y->data);
  const int hx = p->input_shape.data[p->input_n_kernel_size_diff + 0];
  const int wx = p->input_shape.data[p->input_n_kernel_size_diff + 1];
  const int hy = p->output_shape.data[p->input_n_kernel_size_diff + 0];
  const int wy = p->output_shape.data[p->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / p->x_map_size;
  p->calc_context.offset_x = 0;
  p->calc_context.offset_y = 0;
  p->calc_context.kernel_size = context->kernel.size;

  if (context->kernel.size == 2) {
    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          int hstart = iy * hstride - hpad;
          int wstart = jy * wstride - wpad;
          int hend = (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
          int wend = (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
          p->calc_context.pool_size = (hend - hstart) * (wend - wstart);
          p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
          p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
          p->calc_context.hend = (int)fminf((float)hend, (float)hx);
          p->calc_context.wend = (int)fminf((float)wend, (float)wx);
          p->calc_context.hstride =
              p->input_strides.data[p->input_n_kernel_size_diff + 0];
          int k =
              iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] + jy;
          float val = exec(p->calc_context);
          *(y + k + p->calc_context.offset_y) = val;
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  } else if (context->kernel.size == 3) {
    const int dx = p->input_shape.data[p->input_n_kernel_size_diff + 2];
    const int dy = p->output_shape.data[p->input_n_kernel_size_diff + 2];
    const int dkernel = context->kernel.data[2];
    const int dstride = context->stride.data[2];
    const int dpad = context->pad.data[2];

    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          for (int ky = 0; ky < dy; ky++) {
            int hstart = iy * hstride - hpad;
            int wstart = jy * wstride - wpad;
            int dstart = ky * dstride - dpad;
            int hend =
                (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
            int wend =
                (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
            int dend =
                (int)fminf((float)(dstart + dkernel), (float)(dx + dpad));
            p->calc_context.pool_size =
                (hend - hstart) * (wend - wstart) * (dend - dstart);
            p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
            p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
            p->calc_context.dstart = (int)fmaxf((float)dstart, 0);
            p->calc_context.hend = (int)fminf((float)hend, (float)hx);
            p->calc_context.wend = (int)fminf((float)wend, (float)wx);
            p->calc_context.dend = (int)fminf((float)dend, (float)dx);
            p->calc_context.hstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 0];
            p->calc_context.wstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 1];
            int k =
                iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] +
                jy * p->output_strides.data[p->input_n_kernel_size_diff + 1] +
                ky;
            float val = exec(p->calc_context);
            *(y + k + p->calc_context.offset_y) = val;
          }
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pooling_generic(rt_function_t *f,
                                         pooling_context_t *context,
                                         pooling_private_t *p,
                                         exec_pooling_func_t exec) {
  const int hx = p->input_shape.data[p->input_n_kernel_size_diff + 0];
  const int wx = p->input_shape.data[p->input_n_kernel_size_diff + 1];
  const int hy = p->output_shape.data[p->input_n_kernel_size_diff + 0];
  const int wy = p->output_shape.data[p->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / p->x_map_size;
  p->calc_context.offset_x = 0;
  p->calc_context.offset_y = 0;
  p->calc_context.kernel_size = context->kernel.size;

  if (context->kernel.size == 2) {
    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          int hstart = iy * hstride - hpad;
          int wstart = jy * wstride - wpad;
          int hend = (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
          int wend = (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
          p->calc_context.pool_size = (hend - hstart) * (wend - wstart);
          p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
          p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
          p->calc_context.hend = (int)fminf((float)hend, (float)hx);
          p->calc_context.wend = (int)fminf((float)wend, (float)wx);
          p->calc_context.hstride =
              p->input_strides.data[p->input_n_kernel_size_diff + 0];
          int k =
              iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] + jy;
          float val = exec(p->calc_context);
          p->calc_context.set_y(p->calc_context.y, k + p->calc_context.offset_y,
                                val);
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  } else if (context->kernel.size == 3) {
    const int dx = p->input_shape.data[p->input_n_kernel_size_diff + 2];
    const int dy = p->output_shape.data[p->input_n_kernel_size_diff + 2];
    const int dkernel = context->kernel.data[2];
    const int dstride = context->stride.data[2];
    const int dpad = context->pad.data[2];

    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          for (int ky = 0; ky < dy; ky++) {
            int hstart = iy * hstride - hpad;
            int wstart = jy * wstride - wpad;
            int dstart = ky * dstride - dpad;
            int hend =
                (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
            int wend =
                (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
            int dend =
                (int)fminf((float)(dstart + dkernel), (float)(dx + dpad));
            p->calc_context.pool_size =
                (hend - hstart) * (wend - wstart) * (dend - dstart);
            p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
            p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
            p->calc_context.dstart = (int)fmaxf((float)dstart, 0);
            p->calc_context.hend = (int)fminf((float)hend, (float)hx);
            p->calc_context.wend = (int)fminf((float)wend, (float)wx);
            p->calc_context.dend = (int)fminf((float)dend, (float)dx);
            p->calc_context.hstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 0];
            p->calc_context.wstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 1];
            int k =
                iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] +
                jy * p->output_strides.data[p->input_n_kernel_size_diff + 1] +
                ky;
            float val = exec(p->calc_context);
            p->calc_context.set_y(p->calc_context.y,
                                  k + p->calc_context.offset_y, val);
          }
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pooling_fixed8(rt_function_t *f,
                                        pooling_context_t *context,
                                        pooling_private_t *p,
                                        exec_pooling_func_fixed8_t exec) {
  int8_t *y = (int8_t *)(p->calc_context.y->data);
  const int hx = p->input_shape.data[p->input_n_kernel_size_diff + 0];
  const int wx = p->input_shape.data[p->input_n_kernel_size_diff + 1];
  const int hy = p->output_shape.data[p->input_n_kernel_size_diff + 0];
  const int wy = p->output_shape.data[p->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / p->x_map_size;
  p->calc_context.offset_x = 0;
  p->calc_context.offset_y = 0;
  p->calc_context.kernel_size = context->kernel.size;

  if (context->kernel.size == 2) {
    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          int hstart = iy * hstride - hpad;
          int wstart = jy * wstride - wpad;
          int hend = (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
          int wend = (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
          p->calc_context.pool_size = (hend - hstart) * (wend - wstart);
          p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
          p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
          p->calc_context.hend = (int)fminf((float)hend, (float)hx);
          p->calc_context.wend = (int)fminf((float)wend, (float)wx);
          p->calc_context.hstride =
              p->input_strides.data[p->input_n_kernel_size_diff + 0];
          int k =
              iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] + jy;
          int8_t val = exec(p->calc_context);
          *(y + k + p->calc_context.offset_y) = val;
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  } else if (context->kernel.size == 3) {
    const int dx = p->input_shape.data[p->input_n_kernel_size_diff + 2];
    const int dy = p->output_shape.data[p->input_n_kernel_size_diff + 2];
    const int dkernel = context->kernel.data[2];
    const int dstride = context->stride.data[2];
    const int dpad = context->pad.data[2];

    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          for (int ky = 0; ky < dy; ky++) {
            int hstart = iy * hstride - hpad;
            int wstart = jy * wstride - wpad;
            int dstart = ky * dstride - dpad;
            int hend =
                (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
            int wend =
                (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
            int dend =
                (int)fminf((float)(dstart + dkernel), (float)(dx + dpad));
            p->calc_context.pool_size =
                (hend - hstart) * (wend - wstart) * (dend - dstart);
            p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
            p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
            p->calc_context.dstart = (int)fmaxf((float)dstart, 0);
            p->calc_context.hend = (int)fminf((float)hend, (float)hx);
            p->calc_context.wend = (int)fminf((float)wend, (float)wx);
            p->calc_context.dend = (int)fminf((float)dend, (float)dx);
            p->calc_context.hstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 0];
            p->calc_context.wstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 1];
            int k =
                iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] +
                jy * p->output_strides.data[p->input_n_kernel_size_diff + 1] +
                ky;
            int8_t val = exec(p->calc_context);
            val = rescale_scalar_fixed8(val, f->inputs[0]->fp_pos,
                                        f->outputs[0]->fp_pos);
            *(y + k + p->calc_context.offset_y) = val;
          }
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pooling_fixed16(rt_function_t *f,
                                         pooling_context_t *context,
                                         pooling_private_t *p,
                                         exec_pooling_func_fixed16_t exec) {
  int16_t *y = (int16_t *)(p->calc_context.y->data);
  const int hx = p->input_shape.data[p->input_n_kernel_size_diff + 0];
  const int wx = p->input_shape.data[p->input_n_kernel_size_diff + 1];
  const int hy = p->output_shape.data[p->input_n_kernel_size_diff + 0];
  const int wy = p->output_shape.data[p->input_n_kernel_size_diff + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / p->x_map_size;
  p->calc_context.offset_x = 0;
  p->calc_context.offset_y = 0;
  p->calc_context.kernel_size = context->kernel.size;

  if (context->kernel.size == 2) {
    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          int hstart = iy * hstride - hpad;
          int wstart = jy * wstride - wpad;
          int hend = (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
          int wend = (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
          p->calc_context.pool_size = (hend - hstart) * (wend - wstart);
          p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
          p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
          p->calc_context.hend = (int)fminf((float)hend, (float)hx);
          p->calc_context.wend = (int)fminf((float)wend, (float)wx);
          p->calc_context.hstride =
              p->input_strides.data[p->input_n_kernel_size_diff + 0];
          int k =
              iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] + jy;
          int16_t val = exec(p->calc_context);
          *(y + k + p->calc_context.offset_y) = val;
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  } else if (context->kernel.size == 3) {
    const int dx = p->input_shape.data[p->input_n_kernel_size_diff + 2];
    const int dy = p->output_shape.data[p->input_n_kernel_size_diff + 2];
    const int dkernel = context->kernel.data[2];
    const int dstride = context->stride.data[2];
    const int dpad = context->pad.data[2];

    for (int n = 0; n < n_map; n++) {
      for (int iy = 0; iy < hy; iy++) {
        for (int jy = 0; jy < wy; jy++) {
          for (int ky = 0; ky < dy; ky++) {
            int hstart = iy * hstride - hpad;
            int wstart = jy * wstride - wpad;
            int dstart = ky * dstride - dpad;
            int hend =
                (int)fminf((float)(hstart + hkernel), (float)(hx + hpad));
            int wend =
                (int)fminf((float)(wstart + wkernel), (float)(wx + wpad));
            int dend =
                (int)fminf((float)(dstart + dkernel), (float)(dx + dpad));
            p->calc_context.pool_size =
                (hend - hstart) * (wend - wstart) * (dend - dstart);
            p->calc_context.hstart = (int)fmaxf((float)hstart, 0);
            p->calc_context.wstart = (int)fmaxf((float)wstart, 0);
            p->calc_context.dstart = (int)fmaxf((float)dstart, 0);
            p->calc_context.hend = (int)fminf((float)hend, (float)hx);
            p->calc_context.wend = (int)fminf((float)wend, (float)wx);
            p->calc_context.dend = (int)fminf((float)dend, (float)dx);
            p->calc_context.hstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 0];
            p->calc_context.wstride =
                p->input_strides.data[p->input_n_kernel_size_diff + 1];
            int k =
                iy * p->output_strides.data[p->input_n_kernel_size_diff + 0] +
                jy * p->output_strides.data[p->input_n_kernel_size_diff + 1] +
                ky;
            int16_t val = exec(p->calc_context);
            *(y + k + p->calc_context.offset_y) = val;
          }
        }
      }
      p->calc_context.offset_x += p->x_map_size;
      p->calc_context.offset_y += p->y_map_size;
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

float calc_max(pooling_calc_context_t calc) {
  float max_val = -FLT_MAX;
  float *x = (float *)(calc.x->data);
  if (calc.kernel_size == 2) {
    int l = calc.hstart * calc.hstride + calc.wstart;
    max_val = *(x + l + calc.offset_x);
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        float val = *(x + jx + calc.offset_x);
        if (max_val < val) {
          max_val = val;
        }
      }
    }
  } else if (calc.kernel_size == 3) {
    int l =
        calc.hstart * calc.hstride + calc.wstart * calc.wstride + calc.dstart;
    max_val = *(x + l + calc.offset_x);
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          float val =
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
          if (max_val < val) {
            max_val = val;
          }
        }
      }
    }
  }
  return max_val;
}

int8_t calc_max_fixed8(pooling_calc_context_t calc) {
  int8_t max_val = INT8_MIN;
  int8_t *x = (int8_t *)(calc.x->data);
  if (calc.kernel_size == 2) {
    int l = calc.hstart * calc.hstride + calc.wstart;
    max_val = *(x + l + calc.offset_x);
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        int8_t val = *(x + jx + calc.offset_x);
        if (max_val < val) {
          max_val = val;
        }
      }
    }
  } else if (calc.kernel_size == 3) {
    int l =
        calc.hstart * calc.hstride + calc.wstart * calc.wstride + calc.dstart;
    max_val = *(x + l + calc.offset_x);
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          int8_t val =
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
          if (max_val < val) {
            max_val = val;
          }
        }
      }
    }
  }
  max_val = rescale_scalar_fixed8(max_val, calc.x->fp_pos, calc.y->fp_pos);
  return max_val;
}

int16_t calc_max_fixed16(pooling_calc_context_t calc) {
  int16_t max_val = INT16_MIN;
  int16_t *x = (int16_t *)(calc.x->data);
  if (calc.kernel_size == 2) {
    int l = calc.hstart * calc.hstride + calc.wstart;
    max_val = *(x + l + calc.offset_x);
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        int16_t val = *(x + jx + calc.offset_x);
        if (max_val < val) {
          max_val = val;
        }
      }
    }
  } else if (calc.kernel_size == 3) {
    int l =
        calc.hstart * calc.hstride + calc.wstart * calc.wstride + calc.dstart;
    max_val = *(x + l + calc.offset_x);
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          int16_t val =
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
          if (max_val < val) {
            max_val = val;
          }
        }
      }
    }
  }
  max_val = rescale_scalar_fixed16(max_val, calc.x->fp_pos, calc.y->fp_pos);
  return max_val;
}

float calc_max_generic(pooling_calc_context_t calc) {
  float max_val = -FLT_MAX;
  if (calc.kernel_size == 2) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        float val = calc.get_x(calc.x, jx + calc.offset_x);
        if (max_val < val) {
          max_val = val;
        }
      }
    }
  } else if (calc.kernel_size == 3) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          float val = calc.get_x(calc.x, ix * calc.hstride + jx * calc.wstride +
                                             kx + calc.offset_x);
          if (max_val < val) {
            max_val = val;
          }
        }
      }
    }
  }
  return max_val;
}

float calc_sum(pooling_calc_context_t calc) {
  float sum_val = 0.0f;
  float *x = (float *)(calc.x->data);
  if (calc.kernel_size == 2) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        sum_val += *(x + jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          sum_val +=
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
        }
      }
    }
  }
  return sum_val;
}

int8_t calc_sum_fixed8(pooling_calc_context_t calc) {
  int16_t sum_val = 0;
  int8_t *x = (int8_t *)(calc.x->data);
  if (calc.kernel_size == 2) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        sum_val += *(x + jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          sum_val +=
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
        }
      }
    }
  }
  sum_val = rescale_scalar_fixed16(sum_val, calc.x->fp_pos, calc.y->fp_pos);
  sum_val = saturate16_to_8(sum_val);
  return (int8_t)sum_val;
}

int16_t calc_sum_fixed16(pooling_calc_context_t calc) {
  int32_t sum_val = 0;
  int16_t *x = (int16_t *)(calc.x->data);
  if (calc.kernel_size == 2) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        sum_val += *(x + jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          sum_val +=
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
        }
      }
    }
  }
  sum_val = rescale_scalar_fixed32(sum_val, calc.x->fp_pos, calc.y->fp_pos);
  sum_val = saturate32_to_16(sum_val);
  return (int16_t)sum_val;
}

float calc_sum_generic(pooling_calc_context_t calc) {
  float sum_val = 0.0f;
  if (calc.kernel_size == 2) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        sum_val += calc.get_x(calc.x, jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          sum_val += calc.get_x(calc.x, ix * calc.hstride + jx * calc.wstride +
                                            kx + calc.offset_x);
        }
      }
    }
  }
  return sum_val;
}

float calc_average(pooling_calc_context_t calc) {
  float val = 0.0f;
  float average_val = 0.0f;
  float *x = (float *)(calc.x->data);
  if (calc.kernel_size == 2) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        val += *(x + jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart) *
                       (calc.dend - calc.dstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          val +=
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
        }
      }
    }
  }
  average_val = val / calc.pool_size;
  return average_val;
}

int8_t calc_average_fixed8(pooling_calc_context_t calc) {
  int16_t val = 0;
  int8_t average_val = 0;
  int8_t *x = (int8_t *)(calc.x->data);
  if (calc.kernel_size == 2) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        val += *(x + jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart) *
                       (calc.dend - calc.dstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          val +=
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
        }
      }
    }
  }
  average_val = val / calc.pool_size;
  average_val =
      rescale_scalar_fixed16(average_val, calc.x->fp_pos, calc.y->fp_pos);
  average_val = saturate16_to_8(average_val);
  return average_val;
}

int16_t calc_average_fixed16(pooling_calc_context_t calc) {
  int32_t val = 0;
  int16_t average_val = 0;
  int16_t *x = (int16_t *)(calc.x->data);
  if (calc.kernel_size == 2) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        val += *(x + jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart) *
                       (calc.dend - calc.dstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          val +=
              *(x + ix * calc.hstride + jx * calc.wstride + kx + calc.offset_x);
        }
      }
    }
  }
  average_val = val / calc.pool_size;
  average_val =
      rescale_scalar_fixed32(average_val, calc.x->fp_pos, calc.y->fp_pos);
  average_val = saturate32_to_16(average_val);
  return average_val;
}

float calc_average_generic(pooling_calc_context_t calc) {
  float val = 0.0f;
  float average_val = 0.0f;
  if (calc.kernel_size == 2) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = ix * calc.hstride + calc.wstart;
           jx < ix * calc.hstride + calc.wend; jx++) {
        val += calc.get_x(calc.x, jx + calc.offset_x);
      }
    }
  } else if (calc.kernel_size == 3) {
    if (!calc.including_pad) {
      calc.pool_size = (calc.hend - calc.hstart) * (calc.wend - calc.wstart) *
                       (calc.dend - calc.dstart);
    }
    for (int ix = calc.hstart; ix < calc.hend; ix++) {
      for (int jx = calc.wstart; jx < calc.wend; jx++) {
        for (int kx = calc.dstart; kx < calc.dend; kx++) {
          val += calc.get_x(calc.x, ix * calc.hstride + jx * calc.wstride + kx +
                                        calc.offset_x);
        }
      }
    }
  }
  average_val = val / calc.pool_size;
  return average_val;
}
