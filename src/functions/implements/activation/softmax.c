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
#include <nnablart/functions.h>

#include "../../utilities.h"

typedef struct {
  float *input;
  float *output;

  int batch_size;
  int specified_axis_size;
  int rest_size;
} softmax_private_t;

rt_function_error_t allocate_softmax_local_context(rt_function_t *f) {
  const int axis = ((softmax_local_context_t *)(f->local_context))->axis;
  const int size = calc_shape_size(f->inputs[0]->shape);
  const int size_axis = f->inputs[0]->shape.data[axis];
  softmax_private_t *p = malloc(sizeof(softmax_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  p->batch_size = size / size_axis;
  p->specified_axis_size = size_axis;
  p->rest_size = size / p->batch_size / p->specified_axis_size;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_softmax_local_context(rt_function_t *f) {
  free((((softmax_local_context_t *)(f->local_context))->private));
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_softmax(rt_function_t *f) {
  softmax_private_t *p = (softmax_private_t *)(((softmax_local_context_t *)(f->local_context))
                               ->private);
  const float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  int i0, i1, i2;
  for (i0 = 0; i0 < p->batch_size ; ++i0) {
    for (i2 = 0; i2 < p->rest_size ; ++i2) {
      const int j = i0 * p->specified_axis_size * p->rest_size + i2;
      // compute maximum
      float max_x = x[j];
      for (i1 = 0; i1 < p->specified_axis_size ; ++i1) {
        const int k = i1 * p->rest_size + j;
        max_x = (max_x >= x[k]) ? max_x : x[k];
      }
      // Compute exponential and sum
      float exp_sum = 0;
      for (i1 = 0; i1 < p->specified_axis_size; ++i1) {
        const int k = i1 * p->rest_size + j;
        const float tmp = expf(x[k] - max_x);
        y[k] = tmp;
        exp_sum += tmp; 
      }
      // Compute softmax
      for (i1 = 0; i1 < p->specified_axis_size; ++i1) {
        const int k = i1 * p->rest_size + j;
        y[k] = y[k] / exp_sum;
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}