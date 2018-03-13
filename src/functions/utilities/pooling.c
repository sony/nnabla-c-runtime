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

#include <assert.h>
#include <math.h>
#include "pooling.h"
#include "shape.h"

rt_function_error_t exec_pooling(rt_function_t *f, pooling_context_t *context, pooling_private_t *private, exec_pooling_func_t exec) {
  const float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  const int hx = private->input_shape.data[private->input_n_kernel_size_diff + 0];
  const int wx = private->input_shape.data[private->input_n_kernel_size_diff + 1];
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
        hstart = fmaxf(hstart, 0);
        wstart = fmaxf(wstart, 0);
        hend = fminf(hend, hx);
        wend = fminf(wend, wx);
        int k = iy * wy + jy;
        float val = exec(hstart, hend, wstart, wend, wx, x);
        y[k] = val;
      }
    }
    x += private->x_stride;
    y += private->y_stride;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

float calc_max(int hstart, int hend, int wstart, int wend, int wx, const float *x){
  int l = hstart * wx + wstart;
  float max_val = x[l];
  int ix;
  for (ix = hstart; ix < hend; ix++) {
    int jx;
    for (jx = ix * wx + wstart; jx < ix * wx + wend; jx++) {
      float val = x[jx];
      if (max_val < val) {
        max_val = val;
      }
    }
  }
  return max_val;
}

float calc_sum(int hstart, int hend, int wstart, int wend, int wx, const float *x){
  float sum_val = 0.0f;
  int ix;
  for (ix = hstart; ix < hend; ix++) {
    int jx;
    for (jx = ix * wx + wstart; jx < ix * wx + wend; jx++) {
      sum_val += x[jx];
    }
  }
  return sum_val;
}
