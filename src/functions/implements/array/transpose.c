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
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
  rt_list_t input_strides;
  rt_list_t output_strides;
  rt_list_t input_shape;
  rt_list_t output_shape;
} transpose_private_t;

rt_function_error_t exec_transpose_generic(rt_function_t *f);

// Transpose
rt_function_error_t allocate_transpose_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  transpose_private_t *p = rt_malloc_func(sizeof(transpose_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  ((transpose_local_context_t *)(f->local_context))->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_shape = clone_list(f->inputs[0]->shape);
  p->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->output_shape = clone_list(f->outputs[0]->shape);
  p->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  p->output_size = calc_shape_size(f->outputs[0]->shape);

  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_transpose;
  } else {
    f->exec_func = exec_transpose_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_transpose_local_context(rt_function_t *f) {
  transpose_private_t *p =
      (transpose_private_t *)(((transpose_local_context_t *)(f->local_context))
                                  ->data);
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->input_strides);
  free_list(p->output_strides);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_transpose(rt_function_t *f) {
  transpose_local_context_t *c =
      (transpose_local_context_t *)(f->local_context);
  transpose_private_t *p = (transpose_private_t *)(c->data);
  float *x = (float *)p->input->data;
  float *y = (float *)p->output->data;

  for (int o = 0; o < p->output_size; ++o) {
    int i = 0;
    for (int d = 0; d < p->input_shape.size; ++d) {
      const int k =
          (int)(o / p->output_strides.data[d]) % p->output_shape.data[d];
      i += k * p->input_strides.data[c->axes.data[d]];
    }
    y[o] = x[i];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_transpose_generic(rt_function_t *f) {
  transpose_local_context_t *c =
      (transpose_local_context_t *)(f->local_context);
  transpose_private_t *p = (transpose_private_t *)(c->data);

  for (int o = 0; o < p->output_size; ++o) {
    int i = 0;
    for (int d = 0; d < p->input_shape.size; ++d) {
      const int k =
          (int)(o / p->output_strides.data[d]) % p->output_shape.data[d];
      i += k * p->input_strides.data[c->axes.data[d]];
    }
    const float x = p->get_input(p->input, i);
    p->set_output(p->output, o, x);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
