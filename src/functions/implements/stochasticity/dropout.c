// Copyright (c) 2018 Sony Corporation. All Rights Reserved.
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
#include "../../utilities/shape.h"
#include "../../utilities/accessor.h"

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int input_size;
  int output_size;
} dropout_private_t;

rt_function_error_t exec_dropout_generic(rt_function_t *f);

// Dropout
rt_function_error_t allocate_dropout_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  dropout_private_t *p = malloc(sizeof(dropout_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  ((dropout_local_context_t *)(f->local_context))->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_size = calc_shape_size(f->inputs[0]->shape);

  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->output_size = calc_shape_size(f->outputs[0]->shape);
  if (p->input_size != p->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_dropout;
  } else {
    f->exec_func = exec_dropout_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_dropout_local_context(rt_function_t *f) {
  free(f->local_context);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_dropout(rt_function_t *f) {
  dropout_local_context_t *context =
    (dropout_local_context_t *)(f->local_context);
  dropout_private_t *p = (dropout_private_t *)(context->data);
  float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  for(int i = 0; i < p->output_size; i++) {
    y[i] = x[i] * (1 - context->p);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_dropout_generic(rt_function_t *f) {
  dropout_local_context_t *context =
    (dropout_local_context_t *)(f->local_context);
  dropout_private_t *p = (dropout_private_t *)(context->data);

  for(int i = 0; i < p->output_size; i++) {
    float x = p->get_input(p->input, i) * (1 - context->p);
    p->set_output(p->output, i, x);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
