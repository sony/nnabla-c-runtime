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
void allocate_affine_local_context(rt_function_t *f) {
  assert(f->num_of_inputs == 2 || f->num_of_inputs == 3);
  assert(f->num_of_outputs == 1);
  affine_local_context_t *c = malloc(sizeof(affine_local_context_t));
  c->input = f->inputs[0];
  c->get_input = select_getter(c->input);

  c->weight = f->inputs[1];
  c->get_weight = select_getter(c->weight);

  c->output = f->outputs[0];
  c->get_output = select_getter(c->output);
  c->set_output = select_setter(c->output);

  if (f->num_of_inputs > 2) {
    c->bias = f->inputs[2];
    c->get_bias = select_getter(c->bias);
  } else {
    c->bias = 0;
  }

  c->output_size = calc_shape_size(c->output->shape);

  int base_axis = ((affine_config_t *)(f->config))->base_axis;
  int i; // Iterator

  c->base_loop_size = 1;
  for (i = 0; i < base_axis; i++) {
    c->base_loop_size *= c->input->shape.data[i];
  }

  c->input_loop_size = 1;
  for (i = base_axis; i < c->input->shape.size; i++) {
    c->input_loop_size *= c->input->shape.data[i];
  }

  c->output_loop_size = 1;
  for (i = base_axis; i < c->output->shape.size; i++) {
    c->output_loop_size *= c->output->shape.data[i];
  }

  if (c->input->type == NN_DATA_TYPE_FLOAT &&
      c->output->type == NN_DATA_TYPE_FLOAT &&
      c->weight->type == NN_DATA_TYPE_FLOAT &&
      ((c->bias && c->bias->type == NN_DATA_TYPE_FLOAT) || !c->bias)) {
    c->exec = exec_affine_float;
  } else {
    c->exec = exec_affine_generic;
  }

  ((affine_config_t *)(f->config))->local_context = (void *)c;
}

void free_affine_local_context(rt_function_t *f) {
  free((((affine_config_t *)(f->config))->local_context));
}

void exec_affine(rt_function_t *f) {
  assert(((affine_local_context_t *)(((affine_config_t *)(f->config))
                                         ->local_context))
             ->exec);
  ((affine_local_context_t *)(((affine_config_t *)(f->config))->local_context))
      ->exec(f);
}
