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
static inline float sum(float a, float b) { return a + b; }
static inline float devide(float a, float b) { return a / b; }
static inline float identify(float a) { return a; }

static inline void map(rt_list_t list, float (*func1)(float), float (*func2)(float, float), float arg) {
  int i;
  for(i = 0; i < list.size; ++i) {
    list.data[i] = func2(func1(list.data[i]), arg);
  }
}

static inline float reduce(rt_list_t list, float (*func)(float, float)) {
  int i;
  float result = 0;
  for(i = 0; i < list.size; ++i) {
    result = func(result, list.data[i]);
  }
  return result;
}

static inline void softmax_impl(const int batch_size, const int specified_axis_size, const int rest_size,
              const int batch_index, const float *const input, float *const output) {
  rt_list_t array = allocate_list(specified_axis_size);
  int specified_index, rest_index;
  for (rest_index = 0; rest_index < rest_size ; ++rest_index) {
    const int j = batch_index * specified_axis_size * rest_size + rest_index;
    for (specified_index = 0; specified_index < specified_axis_size ; ++specified_index) {
      const int k = specified_index * rest_size + j;
      array.data[specified_index] = input[k];
    }

    // compute maximum
    float max_input = reduce(array, max);
    map(array, identify, sum, max_input * -1.0);
    // Compute exponential and sum
    map(array, expf, sum, 0);
    float exp_sum = reduce(array, sum);
    // Compute softmax
    map(array, identify, devide, exp_sum);

    for (specified_index = 0; specified_index < specified_axis_size ; ++specified_index) {
      const int k = specified_index * rest_size + j;
      output[k] = array.data[specified_index];
    }
  }
  free_list(array);
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
  const int rest_size = size / batch_size / specified_axis_size;
  if (batch_size * specified_axis_size * rest_size != size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  // exec
  int sample_index;
  for (sample_index = 0; sample_index < batch_size ; ++sample_index) {
    softmax_impl(batch_size, specified_axis_size, rest_size, sample_index,
            input_data_of(f, 0), output_data_of(f, 0));
  }
  return RT_FUNCTION_ERROR_NOERROR;
}