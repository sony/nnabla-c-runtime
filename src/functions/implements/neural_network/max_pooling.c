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

#include <nnablart/functions.h>

#include "../../utilities.h"

#include <math.h>

rt_function_error_t allocate_max_pooling_local_context(rt_function_t *f) {
  max_pooling_local_context_t *context = (max_pooling_local_context_t *)(f->local_context);
  const rt_list_t inshape = clone_list(f->inputs[0]->shape);
  const rt_list_t outshape = clone_list(f->outputs[0]->shape);
  int i;
  rt_list_t shape = allocate_list(context->kernel.size);
  const int s = inshape.size - context->kernel.size;
  if(context->stride.size == 0) {
    context->stride = clone_list(context->kernel);
  } else {
    if(context->kernel.size != context->stride.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
    if(context->kernel.size > inshape.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
  }
  if(context->kernel.size != 2) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if(context->kernel.size != context->pad.size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  for (i = 0; i < inshape.size; i++) {
    shape.data[i] = inshape.data[i + s];
  }
  for (i = 0; i < shape.size; i++) {
    shape.data[i] += 2 * context->pad.data[i];
    if (context->ignore_border) {
      shape.data[i] = (int)((shape.data[i] - context->kernel.data[i]) / context->stride.data[i]) + 1;
    } else {
      shape.data[i] = ceil(shape.data[i] * 1.0 / context->stride.data[i]);
    }
  }
  for (i = 0; i < inshape.size; i++) {
    if (i < s) {
      outshape.data[i] = inshape.data[i];
    } else {
      outshape.data[i] = shape.data[i - s];
    }
  }
  free_list(inshape);
  free_list(outshape);
  free_list(shape);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_max_pooling_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_list_t get_c_contiguous_strides(rt_list_t shape) {
  if(!shape.size) {
    return shape;
  }
  rt_list_t strides = allocate_list(shape.size);
  int i;
  for (i = 0; i< shape.size; ++i) {
    strides.data[i] = 1;
  }
  for (i = strides.size - 2; i >= 0; --i) {
    strides.data[i] *= strides.data[i + 1] * shape.data[i + 1];
  }
  return strides;
}

rt_function_error_t exec_max_pooling(rt_function_t *f) {
  max_pooling_local_context_t *context = (max_pooling_local_context_t *)(f->local_context);
  const float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  const rt_list_t inshape = clone_list(f->inputs[0]->shape);
  const rt_list_t outshape = clone_list(f->outputs[0]->shape);
  const int s = inshape.size - context->kernel.size;
  const rt_list_t input_strides = get_c_contiguous_strides(f->inputs[0]->shape);
  const rt_list_t output_strides = get_c_contiguous_strides(f->outputs[0]->shape);
  const int x_stride =
    (s == 0) ? calc_shape_size(f->inputs[0]->shape) : input_strides.data[s - 1];
  const int y_stride =
    (s == 0) ? calc_shape_size(f->outputs[0]->shape) : output_strides.data[s - 1];
  free_list(input_strides);
  free_list(output_strides);
  const int hx = inshape.data[s + 0];
  const int wx = inshape.data[s + 1];
  const int hy = outshape.data[s + 0];
  const int wy = outshape.data[s + 1];
  const int hkernel = context->kernel.data[0];
  const int wkernel = context->kernel.data[1];
  const int hstride = context->stride.data[0];
  const int wstride = context->stride.data[1];
  const int hpad = context->pad.data[0];
  const int wpad = context->pad.data[1];
  const int n_map = calc_shape_size(f->inputs[0]->shape) / x_stride;
  int n, iy, jy, ix, jx;
  int hstart, wstart, hend, wend;
  int k, l;
  float max_val;
  float val;
  for (n = 0; n < n_map; ++n) {
    for(iy = 0; iy < hy; ++iy) {
      for(jy = 0; jy < wy; ++jy) {
        hstart = iy * hstride - hpad;
        wstart = jy * wstride - wpad;
        hend = fminf(hstart + hkernel, hx + hpad);
        wend = fminf(wstart + wkernel, wx + wpad);
        hstart = fmaxf(hstart, 0);
        wstart = fmax(wstart, 0);
        hend = fminf(hend, hx);
        wend = fminf(wend, wx);
        k = iy * wy + jy;
        l = hstart * wx + wstart;
        max_val = x[l];
        for (ix = hstart; ix < hend; ++ix) {
          for (jx = ix * wx + wstart; jx < ix * wx + wend; ++jx) {
            val = x[jx];
            if (max_val < val) {
              max_val = val;
            }
          }
        }
        y[k] = max_val;
      }
    }
    x += x_stride;
    y += y_stride;
  }
  free_list(inshape);
  free_list(outshape);
  return RT_FUNCTION_ERROR_NOERROR;
}
