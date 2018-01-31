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

rt_function_error_t allocate_softmax_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_softmax_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

static inline float max(float a, float b) { return a < b ? b : a; }

rt_function_error_t exec_softmax(rt_function_t *f) {
  // set up
  softmax_local_context_t *context = (softmax_local_context_t *)(context_of(f));
  const int axis = context->axis;
  const int size = calc_shape_size(input_shape_of(f, 0));
  int size_axis;
  // axis must be less than ndim of inputs[0].
  if (input_shape_of(f, 0).size <= axis) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  int i;
  if (axis <= 0) {
    size_axis = size;
  } else {
    size_axis = 1;
    for (i = axis; i < input_shape_of(f, 0).size; ++i) {
      size_axis *= input_shape_of(f, 0).data[i];
    }
  }
  const int batch_size = size / size_axis;
  const int specified_axis_size = input_shape_of(f, 0).data[axis];
  const int rest_size = size / batch_size / specified_axis_size;
  if (batch_size * specified_axis_size * rest_size != size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  // exec
  const float *const input = input_data_of(f, 0);
  float *const output = output_data_of(f, 0);
  int batch_index, specified_index, rest_index;
  for (batch_index = 0; batch_index < batch_size ; ++batch_index) {
    for (rest_index = 0; rest_index < rest_size ; ++rest_index) {
      const int j = batch_index * specified_axis_size * rest_size + rest_index;
      // compute maximum
      float max_input = input[j];
      for (specified_index = 0; specified_index < specified_axis_size ; ++specified_index) {
        const int k = specified_index * rest_size + j;
        max_input = max(max_input, input[k]);
      }
      // Compute exponential and sum
      float exp_sum = 0;
      for (specified_index = 0; specified_index < specified_axis_size; ++specified_index) {
        const int k = specified_index * rest_size + j;
        const float tmp = expf(input[k] - max_input);
        output[k] = tmp;
        exp_sum += tmp; 
      }
      // Compute softmax
      for (specified_index = 0; specified_index < specified_axis_size; ++specified_index) {
        const int k = specified_index * rest_size + j;
        output[k] = output[k] / exp_sum;
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}