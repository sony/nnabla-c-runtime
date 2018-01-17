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
#include <memory.h>

#include "../../../utilities.h"

struct affine_impl {
  rt_variable_t *input;
  rt_variable_t *weight;
  rt_variable_t *bias;
  rt_variable_t *output;

  int count;
  int input_width;
  int output_width;
};
typedef struct affine_impl affine_impl_t;

static inline int product(const int *array, int begin, int end) {
  int product = 1;
  const int *it = array + begin;
  while (it != array + end) {
    product *= *it++;
  }
  return product;
}

// Affine
void allocate_affine_config(rt_function_t *f) {
  assert(f->num_of_inputs == 2 || f->num_of_inputs == 3);
  assert(f->num_of_outputs == 1);
  affine_impl_t *const pimpl = malloc(sizeof(affine_impl_t));
  affine_config_t *const config = f->config;
  config->local_context = pimpl;

  pimpl->input = f->inputs[0];
  pimpl->weight = f->inputs[1];
  pimpl->bias = f->num_of_inputs == 3 ? f->inputs[2] : NULL;
  pimpl->output = f->outputs[0];

  const int base_axis = config->base_axis;
  pimpl->count = product(pimpl->input->shape.data, 0, base_axis);
  pimpl->input_width = product(pimpl->input->shape.data, base_axis, pimpl->input->shape.size);
  pimpl->output_width = product(pimpl->output->shape.data, base_axis, pimpl->output->shape.size);
  assert(calc_shape_size(f->outputs[0]->shape) == pimpl->count * pimpl->output_width);
}

void free_affine_config(rt_function_t *f) {
  free(((affine_config_t *)f->config)->local_context);
}

static inline void clear(rt_variable_t *variable, int length) {
  if (variable) {
    if (variable->type != NN_DATA_TYPE_FLOAT) {
      const rt_variable_setter write = select_setter(variable);
      int pos = 0;
      while (pos != length) {
        write(variable, pos++, 0);
      }
    } else {
      memset(variable->data, 0, sizeof(float) * length);
    }
  }
}

float* alloc_array(rt_variable_t* variable, int width) {
  return variable && variable->type != NN_DATA_TYPE_FLOAT ? malloc(sizeof(float) * width) : NULL;
}

static inline float* fetch(float *head, rt_variable_t* variable, int width, int offset) {
  if (variable) {
    if (variable->type != NN_DATA_TYPE_FLOAT) {
      const rt_variable_getter read = select_getter(variable);
      float *const end = head + width;
      for ( ; head != end; ++head) {
        *head = read(variable, head - (end - width) + offset);
      }
      return end - width;
    } else {
      return (float *)variable->data + offset;
    }
  } else {
    return NULL;
  }
}

static inline void store(rt_variable_t* variable, float* head, int width, int offset) {
  if (variable) {
    if (variable->type != NN_DATA_TYPE_FLOAT) {
      const rt_variable_setter write = select_setter(variable);
      float *const end = head + width;
      for ( ; head != end; ++head) {
        write(variable, head - (end - width) + offset, *head);
      }
    } else {
      if ((float *)variable->data + offset != head) {
        memmove((float *)variable->data + offset, head, sizeof(float) * width);
      }
    }
  }
}

void exec_affine(rt_function_t *f) {
  affine_impl_t *const pimpl = ((affine_config_t*)f->config)->local_context;
  float *const inputs = alloc_array(pimpl->input, pimpl->input_width);
  float *const outputs = alloc_array(pimpl->output, pimpl->output_width);
  float *const weights = alloc_array(pimpl->weight, pimpl->output_width);
  float *const biases = alloc_array(pimpl->bias, pimpl->output_width);
  int loop = pimpl->count;

  // Clear output
  clear(pimpl->output, pimpl->count * pimpl->output_width);

  while (loop--) {
    int i, j; // Iterators.
    const int input_offset = loop * pimpl->input_width;
    const int output_offset = loop * pimpl->output_width;

    float *const is = fetch(inputs, pimpl->input,  pimpl->input_width, input_offset);
    float *const os = fetch(outputs, pimpl->output, pimpl->output_width, output_offset);
    // Weight
    for (j = 0; j != pimpl->input_width; j++) {
      const int weight_offset = j * pimpl->output_width;
      float *const ws = fetch(weights, pimpl->weight, pimpl->output_width, weight_offset);
      for (i = 0; i != pimpl->output_width; i++) {
        os[i] += ws[i] * is[j];
      }
    }

    // Bias
    float *const bs = fetch(biases, pimpl->bias, pimpl->output_width, 0);
    for (i = 0; bs && i != pimpl->output_width; i++) { // NOTE: skipped entire loop if bs == NULL.
      os[i] += bs[i];
    }
    store(pimpl->output, os, pimpl->output_width, output_offset);
  }

  free(inputs);
  free(outputs);
  free(weights);
  free(biases);
}
