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
  int last_ndim;
} matrix_diag_part_local_context_t;

// MatrixDiag
rt_function_error_t allocate_matrix_diag_part_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  matrix_diag_part_local_context_t *c = malloc(sizeof(matrix_diag_part_local_context_t));
  if (c == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  f->local_context = (void *)c;
  c->input = (float *)f->inputs[0]->data;
  c->input_size = calc_shape_size(f->inputs[0]->shape);

  c->output = (float *)f->outputs[0]->data;
  c->output_size = calc_shape_size(f->outputs[0]->shape);

  c->last_ndim = f->inputs[0]->shape.data[f->inputs[0]->shape.size-1];

  if (c->input_size / c->last_ndim != c->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_matrix_diag_part_local_context(rt_function_t *f) {
  free(f->local_context);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_matrix_diag_part(rt_function_t *f) {
  matrix_diag_part_local_context_t *context = (matrix_diag_part_local_context_t *)(f->local_context);

  for (int i = 0; i < context->output_size; ++i) {
    context->output[i] = context->input[i * context->last_ndim + i % context->last_ndim];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
