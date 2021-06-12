// Copyright 2018,2019,2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
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
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_MATRIXDIAGPART

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  int input_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
  int last_ndim;
} matrix_diag_part_local_context_t;

rt_function_error_t exec_matrix_diag_part_generic(rt_function_t *f);

// MatrixDiag
rt_function_error_t allocate_matrix_diag_part_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  matrix_diag_part_local_context_t *c =
      rt_malloc_func(sizeof(matrix_diag_part_local_context_t));
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

  if (c->input_size / c->last_ndim != c->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (c->input->type == NN_DATA_TYPE_FLOAT &&
      c->output->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_MATRIXDIAGPART_FLOAT32
    f->exec_func = exec_matrix_diag_part;
#endif /* CONFIG_MATRIXDIAGPART_FLOAT32 */
  } else {
#ifdef CONFIG_MATRIXDIAGPART_GENERIC
    f->exec_func = exec_matrix_diag_part_generic;
#endif /* CONFIG_MATRIXDIAGPART_GENERIC*/
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_matrix_diag_part_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_MATRIXDIAGPART_FLOAT32
rt_function_error_t exec_matrix_diag_part(rt_function_t *f) {
  matrix_diag_part_local_context_t *context =
      (matrix_diag_part_local_context_t *)(f->local_context);
  float *x = (float *)(context->input->data);
  float *y = (float *)(context->output->data);

  for (int i = 0; i < context->output_size; ++i) {
    y[i] = x[i * context->last_ndim + i % context->last_ndim];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_MATRIXDIAGPART_FLOAT32 */

#ifdef CONFIG_MATRIXDIAGPART_GENERIC
rt_function_error_t exec_matrix_diag_part_generic(rt_function_t *f) {
  matrix_diag_part_local_context_t *context =
      (matrix_diag_part_local_context_t *)(f->local_context);

  for (int i = 0; i < context->output_size; ++i) {
    float x = context->get_input(context->input, i * context->last_ndim +
                                                     i % context->last_ndim);
    context->set_output(context->output, i, x);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_MATRIXDIAGPART_GENERIC*/

#endif /* CONFIG_MATRIXDIAGPART */
