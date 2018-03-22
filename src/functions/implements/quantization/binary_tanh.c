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

#include "../../utilities.h"
#include <math.h>
#include <nnablart/functions.h>

typedef struct {
  float *input;
  int input_size;
  float *output;
  int output_size;
} binary_tanh_private_context_t;

// BinaryTanh
rt_function_error_t allocate_binary_tanh_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  binary_tanh_private_context_t *private =
      malloc(sizeof(binary_tanh_private_context_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  f->local_context = private;
private
  ->input = f->inputs[0]->data;
private
  ->input_size = calc_shape_size(f->inputs[0]->shape);
private
  ->output = f->outputs[0]->data;
private
  ->output_size = calc_shape_size(f->outputs[0]->shape);
  if (private->input_size != private->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_binary_tanh_local_context(rt_function_t *f) {
  free(f->local_context);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_binary_tanh(rt_function_t *f) {
  binary_tanh_private_context_t *private =
      (binary_tanh_private_context_t *)(f->local_context);
  int i; // Iterator
  for (i = 0; i < private->input_size; i++) {
    float x = (private->input[i] + 1) / 2;
    if (x < 0) {
      x = 0;
    }
    if (x > 1) {
      x = 1;
    }
  private
    ->output[i] = roundf(x) * 2 - 1;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
