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

#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <nnablart/functions.h>

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  int input_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
  int last_ndim;
} matrix_diag_local_context_t;

rt_function_error_t exec_matrix_diag_generic(rt_function_t *f);

// MatrixDiag
rt_function_error_t allocate_matrix_diag_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  matrix_diag_local_context_t *c =
      rt_malloc_func(sizeof(matrix_diag_local_context_t));
  if (c == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  f->local_context = (void *)c;
  c->input = f->inputs[0];
  c->get_input = select_getter(c->input);
  c->input_size = calc_shape_size(f->inputs[0]->shape);

  c->output = f->outputs[0];
  c->set_output = select_setter(c->output);
  c->output_size = calc_shape_size(f->outputs[0]->shape);

  c->last_ndim = f->inputs[0]->shape.data[f->inputs[0]->shape.size - 1];

  if (c->input_size * c->last_ndim != c->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (c->input->type == NN_DATA_TYPE_FLOAT &&
      c->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_matrix_diag;
  } else {
    f->exec_func = exec_matrix_diag_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_matrix_diag_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_matrix_diag(rt_function_t *f) {
  matrix_diag_local_context_t *context =
      (matrix_diag_local_context_t *)(f->local_context);
  float *x = (float *)(context->input->data);
  float *y = (float *)(context->output->data);

  int i, j;
  for (i = 0; i < context->input_size; i++) {
    for (j = 0; j < context->last_ndim; j++) {
      if (i % context->last_ndim == j) {
        y[i * context->last_ndim + j] = x[i];
      } else {
        y[i * context->last_ndim + j] = 0.;
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_matrix_diag_generic(rt_function_t *f) {
  matrix_diag_local_context_t *context =
      (matrix_diag_local_context_t *)(f->local_context);

  int i, j;
  for (i = 0; i < context->input_size; i++) {
    for (j = 0; j < context->last_ndim; j++) {
      if (i % context->last_ndim == j) {
        float x = context->get_input(context->input, i);
        context->set_output(context->output, i * context->last_ndim + j, x);
      } else {
        context->set_output(context->output, i * context->last_ndim + j, 0.);
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
