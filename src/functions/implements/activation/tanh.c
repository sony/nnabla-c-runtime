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

#include <assert.h>
#include <math.h>

typedef struct {
  float *input;
  int input_size;
  float *output;
  int output_size;
} tanh_local_context_t;

// Tanh
void allocate_tanh_config(rt_function_t *f) {
  tanh_local_context_t *c = malloc(sizeof(tanh_local_context_t));
  f->config = c;
  assert(f->num_of_inputs == 1);
  assert(f->num_of_outputs == 1);
  c->input = f->inputs[0]->data;
  c->input_size = calc_shape_size(f->inputs[0]->shape);
  c->output = f->outputs[0]->data;
  c->output_size = calc_shape_size(f->outputs[0]->shape);
  assert(c->input_size == c->output_size);
}

void free_tanh_config(rt_function_t *f) {
  free(f->config);
}

void exec_tanh(rt_function_t *f) {
  tanh_local_context_t *c = (tanh_local_context_t *)(f->config);
  int i; // Iterator
  for (i = 0; i < c->input_size; i++) {
    c->output[i] = tanhf(c->input[i]);
  }
}