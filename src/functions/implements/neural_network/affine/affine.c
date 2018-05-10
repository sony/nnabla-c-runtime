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

#include <assert.h>

#include "affine_internal.h"

#include "affine_float.h"
#include "affine_generic.h"

// Affine
rt_function_error_t allocate_affine_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 2 && f->num_of_inputs != 3) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  affine_private_t *p = malloc(sizeof(affine_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);

  p->weight = f->inputs[1];
  p->get_weight = select_getter(p->weight);

  p->output = f->outputs[0];
  p->get_output = select_getter(p->output);
  p->set_output = select_setter(p->output);

  if (f->num_of_inputs > 2) {
    p->bias = f->inputs[2];
    p->get_bias = select_getter(p->bias);
  } else {
    p->bias = 0;
  }

  p->output_size = calc_shape_size(p->output->shape);

  int base_axis = ((affine_local_context_t *)(f->local_context))->base_axis;
  int i; // Iterator

  p->base_loop_size = 1;
  for (i = 0; i < base_axis; i++) {
    p->base_loop_size *= p->input->shape.data[i];
  }

  p->input_loop_size = 1;
  for (i = base_axis; i < p->input->shape.size; i++) {
    p->input_loop_size *= p->input->shape.data[i];
  }

  p->output_loop_size = 1;
  for (i = base_axis; i < p->output->shape.size; i++) {
    p->output_loop_size *= p->output->shape.data[i];
  }

  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT &&
      p->weight->type == NN_DATA_TYPE_FLOAT &&
      ((p->bias && p->bias->type == NN_DATA_TYPE_FLOAT) || !p->bias)) {
    p->exec = exec_affine_float;
  } else {
    p->exec = exec_affine_generic;
  }

  ((affine_local_context_t *)(f->local_context))->data = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_affine_local_context(rt_function_t *f) {
  free((((affine_local_context_t *)(f->local_context))->data));
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_affine(rt_function_t *f) {
  return ((affine_private_t *)(((affine_local_context_t *)(f->local_context))
                                   ->data))
      ->exec(f);
}
