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

typedef struct {
  float *input;
  int input_size;
  float *output;
  int output_size;
} reshape_private_t;

// Reshape
rt_function_error_t allocate_reshape_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  reshape_private_t *private = malloc(sizeof(reshape_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  private->input = f->inputs[0]->data;
  private->input_size = calc_shape_size(f->inputs[0]->shape);
  private->output = f->outputs[0]->data;
  private->output_size = calc_shape_size(f->outputs[0]->shape);
  if (private->input_size != private->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  ((reshape_local_context_t *)(f->local_context))->private = (void *)private;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_reshape_local_context(rt_function_t *f) {
  free(((reshape_local_context_t *)(f->local_context))->private);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_reshape(rt_function_t *f) {
  reshape_local_context_t *context = (reshape_local_context_t *)(f->local_context);
  reshape_private_t *private = (reshape_private_t *)(context->private);
  int i; // Iterator
  for (i = 0; i < private->output_size; i++) {
    private->output[i] = private->input[i];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
