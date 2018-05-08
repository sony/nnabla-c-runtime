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

typedef struct {
  float *input;
  int input_size;
  float *output;
  int output_size;
} relu_private_t;

// Relu
rt_function_error_t allocate_relu_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  relu_private_t *p = malloc(sizeof(relu_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  p->input = f->inputs[0]->data;
  p->input_size = calc_shape_size(f->inputs[0]->shape);

  p->output = f->outputs[0]->data;
  p->output_size = calc_shape_size(f->outputs[0]->shape);

  if (p->input_size != p->output_size) {
    free(p);
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  ((relu_local_context_t *)(f->local_context))->private = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_relu_local_context(rt_function_t *f) {
  free(((relu_local_context_t *)(f->local_context))->private);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_relu(rt_function_t *f) {
  relu_local_context_t *context = (relu_local_context_t *)(f->local_context);
  relu_private_t *p = (relu_private_t *)(context->private);

  int i; // Iterator
  for (i = 0; i < p->output_size; i++) {
    float x = p->input[i];
    p->output[i] = (x > 0.0f) ? x : 0.0f;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
