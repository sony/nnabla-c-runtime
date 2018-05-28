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

#include "../../utilities/shape.h"
#include "../../utilities/accessor.h"

#include <math.h>

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  int input_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
} relu_private_t;

rt_function_error_t exec_relu_generic(rt_function_t *f);

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

  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_size = calc_shape_size(f->inputs[0]->shape);

  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->output_size = calc_shape_size(f->outputs[0]->shape);

  if (p->input_size != p->output_size) {
    free(p);
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  ((relu_local_context_t *)(f->local_context))->data = (void *)p;
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_relu;
  } else {
    f->exec_func = exec_relu_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_relu_local_context(rt_function_t *f) {
  free(((relu_local_context_t *)(f->local_context))->data);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_relu(rt_function_t *f) {
  relu_local_context_t *context = (relu_local_context_t *)(f->local_context);
  relu_private_t *p = (relu_private_t *)(context->data);
  float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  int i; // Iterator
  for (i = 0; i < p->output_size; i++) {
    y[i] = (x[i] > 0.0f) ? x[i] : 0.0f;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_relu_generic(rt_function_t *f) {
  relu_local_context_t *context = (relu_local_context_t *)(f->local_context);
  relu_private_t *p = (relu_private_t *)(context->data);

  int i; // Iterator
  for (i = 0; i < p->output_size; i++) {
    float x = p->get_input(p->input, i);
    p->set_output(p->output, i, ((x > 0.0f) ? x : 0.0f));
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
