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
#include "../neural_network/affine/affine_generic.h"
#include "../neural_network/affine/affine_internal.h"
#include <nnablart/functions.h>
#include <string.h>

// BinaryWeightAffine
rt_function_error_t
allocate_binary_weight_affine_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 4 && f->num_of_inputs != 5) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  affine_private_t *p = rt_malloc_func(sizeof(affine_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);

  p->weight = f->inputs[2];
  p->get_weight = select_getter(p->weight);

  p->output = f->outputs[0];
  p->get_output = select_getter(p->output);
  p->set_output = select_setter(p->output);

  p->alpha = f->inputs[3];
  p->get_alpha = select_getter(p->alpha);

  if (f->num_of_inputs > 4) {
    p->bias = f->inputs[4];
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
    f->exec_func = exec_affine;
  } else {
    f->exec_func = exec_affine_generic;
  }

  ((affine_local_context_t *)(f->local_context))->data = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_binary_weight_affine_local_context(rt_function_t *f) {
  rt_free_func((((affine_local_context_t *)(f->local_context))->data));
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_binary_weight_affine(rt_function_t *f) {
  return exec_affine(f);
}
