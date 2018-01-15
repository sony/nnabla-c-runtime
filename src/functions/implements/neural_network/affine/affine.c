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

#include "../../../utilities.h"

typedef void (*exec_affine_func_t)(rt_function_t *f);

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;

  rt_variable_t *weight;
  rt_variable_getter get_weight;

  rt_variable_t *bias;
  rt_variable_getter get_bias;

  rt_variable_t *output;
  int output_size;
  rt_variable_setter set_output;
  rt_variable_getter get_output;

  int base_loop_size;
  int input_loop_size;
  int output_loop_size;

  exec_affine_func_t exec;
} affine_local_context_t;

static void exec_affine_float(rt_function_t *f);
static void exec_affine_generic(rt_function_t *f);

// Affine
void allocate_affine_config(rt_function_t *f) {
  WHOAMI("%s\n", __func__);

  assert(f->num_of_inputs == 2 || f->num_of_inputs == 3);
  assert(f->num_of_outputs == 1);
  affine_config_t *config = f->config;
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

  int base_axis = config->base_axis;
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

  WHOAMI("%p\n", config);
  config->local_context = (void *)c;
}

void free_affine_config(rt_function_t *f) {
  free((((affine_config_t *)(f->config))->local_context));
}

void exec_affine(rt_function_t *f) {
  ((affine_local_context_t *)(((affine_config_t *)(f->config))->local_context))
      ->exec(f);
}

void exec_affine_float(rt_function_t *f) {
  WHOAMI("%s\n", __func__);

  affine_local_context_t *c =
      (affine_local_context_t *)(((affine_config_t *)(f->config))
                                     ->local_context);
  int i, j, k; // Iterators.
  float *input = (float *)(c->input->data);
  float *weight = (float *)(c->weight->data);
  float *output = (float *)(c->output->data);

  // Clear output
  memset(output, 0, sizeof(float) * c->output_size);

  for (k = 0; k < c->base_loop_size; k++) {
    int output_offset = k * c->output_loop_size;
    int input_offset = k * c->input_loop_size;

    // Weight
    for (j = 0; j < c->input_loop_size; j++) {
      int ipos = input_offset + j;
      int weight_offset = j * c->output_loop_size;

      float u = *(input + ipos);
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int wpos = weight_offset + i;

        float w = *(weight + wpos);
        float value = *(output + opos);
        *(output + opos) = value + u * w;
      }
    }

    // Bias
    if (c->bias) {
      float *bias = (float *)(c->bias->data);
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int bpos = i;
        *(output + opos) = *(output + opos) + *(bias + bpos);
      }
    }
  }
}

void exec_affine_generic(rt_function_t *f) {
  WHOAMI("%s\n", __func__);

  affine_local_context_t *c =
      (affine_local_context_t *)(((affine_config_t *)(f->config))
                                     ->local_context);
  int i, j, k; // Iterators.

  // Clear output
  for (i = 0; i < c->output_size; i++) {
    c->set_output(c->output, i, 0);
  }

  for (k = 0; k < c->base_loop_size; k++) {
    int output_offset = k * c->output_loop_size;
    int input_offset = k * c->input_loop_size;

    // Weight
    for (j = 0; j < c->input_loop_size; j++) {
      int ipos = input_offset + j;
      int weight_offset = j * c->output_loop_size;

      float u = c->get_input(c->input, ipos);
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int wpos = weight_offset + i;

        float w = c->get_weight(c->weight, wpos);
        float value = c->get_output(c->output, opos);
        c->set_output(c->output, opos, value + u * w);
      }
    }

    // Bias
    if (c->bias) {
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int bpos = i;
        c->set_output(c->output, opos, c->get_output(c->output, opos) +
                                           c->get_bias(c->bias, bpos));
      }
    }
  }
}
