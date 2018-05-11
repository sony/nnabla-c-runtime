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

#include "../../utilities/shape.h"
#include <nnablart/functions.h>

#include <math.h>

typedef struct {
  float *input;
  float *output;
  int input_size;
  int output_size;
} log_private_t;

// Log
rt_function_error_t allocate_log_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  log_private_t *p = malloc(sizeof(log_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  f->local_context = (void *)p;
  p->input = (float *)f->inputs[0]->data;
  p->input_size = calc_shape_size(f->inputs[0]->shape);

  p->output = (float *)f->outputs[0]->data;
  p->output_size = calc_shape_size(f->outputs[0]->shape);

  if (p->input_size != p->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_log_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_log(rt_function_t *f) {
  log_private_t *p = (log_private_t *)(f->local_context);

  int i; // Iterator
  for (i = 0; i < p->output_size; i++) {
    p->output[i] = log(p->input[i]);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
