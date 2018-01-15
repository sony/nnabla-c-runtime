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

struct affine_impl {
  affine_config_t config;

  rt_variable_t *input;
  rt_variable_t *weight;
  rt_variable_t *bias;
  rt_variable_t *output;
  int output_size;

  int base_loop_size;
  int input_loop_size;
  int output_loop_size;
};
typedef struct affine_impl affine_impl_t;

// Affine
void allocate_affine_config(rt_function_t *f) {
  WHOAMI("%s\n", __func__);

  assert(f->num_of_inputs == 2 || f->num_of_inputs == 3);
  assert(f->num_of_outputs == 1);
  void *buf = realloc(f->config, sizeof(affine_impl_t));
  if (!buf) {
    buf = malloc(sizeof(affine_impl_t));
    memcpy(buf, f->config, sizeof(affine_config_t));
    f->config = buf;
  }
  affine_impl_t *const pimpl = buf;
  affine_config_t *config = pimpl->config;

  pimpl->input = f->inputs[0];
  pimpl->weight = f->inputs[1];
  pimpl->output = f->outputs[0];

  if (f->num_of_inputs > 2) {
    pimpl->bias = f->inputs[2];
  } else {
    pimpl->bias = 0;
  }

  pimpl->output_size = calc_shape_size(pimpl->output->shape);

  int base_axis = config->base_axis;
  int i; // Iterator

  pimpl->base_loop_size = 1;
  for (i = 0; i < base_axis; i++) {
    pimpl->base_loop_size *= pimpl->input->shape.data[i];
  }

  pimpl->input_loop_size = 1;
  for (i = base_axis; i < pimpl->input->shape.size; i++) {
    pimpl->input_loop_size *= pimpl->input->shape.data[i];
  }

  pimpl->output_loop_size = 1;
  for (i = base_axis; i < pimpl->output->shape.size; i++) {
    pimpl->output_loop_size *= pimpl->output->shape.data[i];
  }
}

void free_affine_config(rt_function_t *f) {
  realloc(f->config, sizeof(affine_config_t)); // can be omitted
}

#define CLEAR(setter, list, length) \
do {\
  if (!setter) {\
    memset(list->data, 0, sizeof(float) * length);\
  } else {\
    int i;\
    for (i = 0; i < length; ++i) {\
      setter(list, i, 0);\
    }\
  }\
} while(0)

#define POKE(setter, list, position, value) \
do {\
  if (!setter) {\
    ((float *)list->data)[position] = value;\
  } else {\
    setter(list, position, value);\
  }\
} while(0)

static inline float peek(rt_variable_getter getter, rt_variable_t *list, int position) {
  if (!getter) {
    return ((float *)list->data)[position];
  } else {
    return getter(list, position);
  }
}

void exec_affine(rt_function_t *f) {
  affine_impl_t *const pimpl = f->config;
  int i, j, k; // Iterators.

  if (pimpl->input->type == NN_DATA_TYPE_FLOAT &&
      pimpl->output->type == NN_DATA_TYPE_FLOAT &&
      pimpl->weight->type == NN_DATA_TYPE_FLOAT &&
      (!pimpl->bias || pimpl->bias->type == NN_DATA_TYPE_FLOAT) {
    // Clear output
    CLEAR(NULL, pimpl->output, pimpl->output_size);

    for (k = 0; k < pimpl->base_loop_size; k++) {
      int output_offset = k * pimpl->output_loop_size;
      int input_offset = k * pimpl->input_loop_size;

      // Weight
      for (j = 0; j < pimpl->input_loop_size; j++) {
        int ipos = input_offset + j;
        int weight_offset = j * pimpl->output_loop_size;

        float u = peek(NULL, pimpl->input, ipos);
        for (i = 0; i < pimpl->output_loop_size; i++) {
          int opos = output_offset + i;
          int wpos = weight_offset + i;

          float w = peek(NULL, pimpl->weight, wpos);
          float value = peek(NULL, pimpl->output, opos);
          POKE(NULL, pimpl->output, opos, value + u * w);
        }
      }

      // Bias
      if (pimpl->bias) {
        for (i = 0; i < pimpl->output_loop_size; i++) {
          int opos = output_offset + i;
          int bpos = i;
          POKE(NULL, pimpl->output, opos, peek(NULL, pimpl->output, opos) + peek(NULL, pimp->bias, bpos));
        }
      }
    }
  } else {
    const rt_variable_getter get_input = select_getter(pimpl->input);
    const rt_variable_getter get_weight = select_getter(pimpl->weight);
    const rt_variable_getter get_bias = select_getter(pimpl->bias);
    const rt_variable_getter get_output = select_getter(pimpl->output);;
    const rt_variable_setter set_output = select_setter(pimpl->output);

    // Clear output
    CLEAR(set_output, pimpl->output, pimpl->output_size);

    for (k = 0; k < pimpl->base_loop_size; k++) {
      int output_offset = k * pimpl->output_loop_size;
      int input_offset = k * pimpl->input_loop_size;

      // Weight
      for (j = 0; j < pimpl->input_loop_size; j++) {
        int ipos = input_offset + j;
        int weight_offset = j * pimpl->output_loop_size;

        float u = peek(get_input, pimpl->input, ipos);
        for (i = 0; i < pimpl->output_loop_size; i++) {
          int opos = output_offset + i;
          int wpos = weight_offset + i;

          float w = peek(get_weight, pimpl->weight, wpos);
          float value = peek(get_output, pimpl->output, opos);
          POKE(set_output, pimpl->output, opos, value + u * w);
        }
      }

      // Bias
      if (pimpl->bias) {
        for (i = 0; i < pimpl->output_loop_size; i++) {
          int opos = output_offset + i;
          int bpos = i;
          POKE(set_output, pimpl->output, opos, peek(get_output, pimpl->output, opos) + peek(get_bias, pimpl->bias, bpos));
        }
      }
    }
  }
}
