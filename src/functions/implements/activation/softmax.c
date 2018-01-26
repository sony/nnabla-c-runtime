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
  int batch_size;
  int specified_axis_size;
  int rest_size;
} softmax_private_t;

rt_function_error_t allocate_softmax_local_context(rt_function_t *f) {
  const int axis = context_of(f)->axis;
  const int size = calc_shape_size(input_shape_of(f, 0));
  int size_axis;
  softmax_private_t *p = malloc(sizeof(softmax_private_t));
  int i;
  if (axis <= 0) {
    size_axis = calc_shape_size(input_shape_of(f, 0));
  } else {
    size_axis = 1;
    for (i = axis; i < input_shape_of(f, 0).size; ++i) {
      size_axis *= input_shape_of(f, 0).data[i];
    }
  }
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  p->batch_size = size / size_axis;
  p->specified_axis_size = input_shape_of(f, 0).data[axis];
  p->rest_size = size / p->batch_size / p->specified_axis_size;
  context_of(f)->private = p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_softmax_local_context(rt_function_t *f) {
  free(context_of(f)->private);
  return RT_FUNCTION_ERROR_NOERROR;
}

static inline float max(float a, float b) { return a < b ? b : a; }

rt_function_error_t exec_softmax(rt_function_t *f) {
  softmax_private_t *const p = context_of(f)->private;
  const float *const input = input_data_of(f, 0);
  float *const output = output_data_of(f, 0);
  int batch_index, specified_index, rest_index;
  for (batch_index = 0; batch_index < p->batch_size ; ++batch_index) {
    for (rest_index = 0; rest_index < p->rest_size ; ++rest_index) {
      const int j = batch_index * p->specified_axis_size * p->rest_size + rest_index;
      // compute maximum
      float max_input = input[j];
      for (specified_index = 0; specified_index < p->specified_axis_size ; ++specified_index) {
        const int k = specified_index * p->rest_size + j;
        max_input = max(max_input, input[k]);
      }
      // Compute exponential and sum
      float exp_sum = 0;
      for (specified_index = 0; specified_index < p->specified_axis_size; ++specified_index) {
        const int k = specified_index * p->rest_size + j;
        const float tmp = expf(input[k] - max_input);
        output[k] = tmp;
        exp_sum += tmp; 
      }
      // Compute softmax
      for (specified_index = 0; specified_index < p->specified_axis_size; ++specified_index) {
        const int k = specified_index * p->rest_size + j;
        output[k] = output[k] / exp_sum;
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}