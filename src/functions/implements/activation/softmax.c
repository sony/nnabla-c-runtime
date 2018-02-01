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

static inline float max(float a, float b);
static inline void softmax(float *array, int array_size);
static inline void exec_1d(const int batch_size, const int specified_axis_size, const int output_size,
              const float *const input, float *const output, void (*func)(float*, int));

rt_function_error_t allocate_softmax_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_softmax_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_softmax(rt_function_t *f) {
  // set up
  softmax_local_context_t *context = (softmax_local_context_t *)(context_of(f));
  const int axis = context->axis;
  const int size = calc_shape_size(input_shape_of(f, 0));
  // axis must be less than ndim of inputs[0].
  if (input_shape_of(f, 0).size <= axis) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  const rt_variable_t *const input = input_of(f, 0);
  const int batch_size = shape_product_of(input, 0, axis);
  const int specified_axis_size = input_shape_value_of(f, 0, axis);
  const int output_size = size / batch_size / specified_axis_size;
  if (batch_size * specified_axis_size * output_size != size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  // exec
  exec_1d(batch_size, specified_axis_size, output_size,
          input_data_of(f, 0), output_data_of(f, 0), softmax);
  return RT_FUNCTION_ERROR_NOERROR;
}

static inline float max(float a, float b) { return a < b ? b : a; }

static inline void softmax(float *array, int array_size) {
    int i;

    // compute maximum
    float max_input = 0;
    for (i = 0; i < array_size; ++i) {
      max_input = max(max_input, array[i]);
    }
    // Compute exponential and sum
    float exp_sum = 0;
    for (i = 0; i < array_size; ++i) {
      const float tmp = expf(array[i] - max_input);
      array[i] = tmp;
      exp_sum += tmp;
    }
    // Compute softmax
    for (i = 0; i < array_size; ++i) {
      array[i] = array[i] / exp_sum;
    }
}

static inline void exec_1d(const int batch_size, const int specified_axis_size, const int output_size,
              const float *const batch_input, float *const batch_output, void (*func)(float*, int)) {
  float *array = malloc(sizeof(float) * specified_axis_size);
  int sample_index, specified_index, output_index;
  for (sample_index = 0; sample_index < batch_size ; ++sample_index) {
    for (output_index = 0; output_index < output_size ; ++output_index) {
      const int j = sample_index * specified_axis_size * output_size + output_index;

      // Get 1dim array from batch_input.
      for (specified_index = 0; specified_index < specified_axis_size ; ++specified_index) {
        const int k = specified_index * output_size + j;
        array[specified_index] = batch_input[k];
      }

      func(array, specified_axis_size);

      // Rewrite batch_output from calculated 1dim array.
      for (specified_index = 0; specified_index < specified_axis_size ; ++specified_index) {
        const int k = specified_index * output_size + j;
        batch_output[k] = array[specified_index];
      }
    }
  }
  free(array);
}