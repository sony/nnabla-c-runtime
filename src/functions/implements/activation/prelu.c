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
  int input_size;
  rt_variable_t *weight;
  rt_variable_getter get_weight;
  int weight_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  rt_list_t in_shape;
  rt_list_t in_stride;
} prelu_private_t;

rt_function_error_t exec_prelu_generic(rt_function_t *f);

// PRelu
rt_function_error_t allocate_prelu_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 2) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  prelu_private_t *p = rt_malloc_func(sizeof(prelu_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  ((prelu_local_context_t *)(f->local_context))->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_size = calc_shape_size(f->inputs[0]->shape);
  p->weight = f->inputs[1];
  p->get_weight = select_getter(p->weight);
  p->weight_size = calc_shape_size(f->inputs[1]->shape);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->in_shape = clone_list(f->inputs[0]->shape);
  p->in_stride = calc_contiguous_strides(f->inputs[0]->shape);
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->weight->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_prelu;
  } else {
    f->exec_func = exec_prelu_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_prelu_local_context(rt_function_t *f) {
  prelu_local_context_t *context = (prelu_local_context_t *)(f->local_context);
  prelu_private_t *p = (prelu_private_t *)(context->data);
  free_list(p->in_shape);
  free_list(p->in_stride);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_prelu(rt_function_t *f) {
  prelu_local_context_t *context = (prelu_local_context_t *)(f->local_context);
  prelu_private_t *p = (prelu_private_t *)(context->data);
  float *x = (float *)(p->input->data);
  float *w = (float *)(p->weight->data);
  float *y = (float *)(p->output->data);
  int base_shape = p->in_shape.data[context->base_axis];
  int base_stride = p->in_stride.data[context->base_axis];

  if (p->weight_size == 1) {
    for (int s = 0; s < p->input_size; ++s) {
      y[s] = (x[s] >= 0) ? x[s] : x[s] * (*w);
    }
  } else {
    for (int s = 0; s < p->input_size; ++s) {
      int iw = (s / base_stride) % base_shape;
      y[s] = (x[s] >= 0) ? x[s] : x[s] * w[iw];
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_prelu_generic(rt_function_t *f) {
  prelu_local_context_t *context = (prelu_local_context_t *)(f->local_context);
  prelu_private_t *p = (prelu_private_t *)(context->data);
  int base_shape = p->in_shape.data[context->base_axis];
  int base_stride = p->in_stride.data[context->base_axis];

  if (p->weight_size == 1) {
    float w = p->get_weight(p->weight, 0);
    for (int s = 0; s < p->input_size; ++s) {
      float x = p->get_input(p->input, s);
      float y = (x >= 0) ? x : x * w;
      p->set_output(p->output, s, y);
    }
  } else {
    for (int s = 0; s < p->input_size; ++s) {
      int iw = (s / base_stride) % base_shape;
      float x = p->get_input(p->input, s);
      float w = p->get_weight(p->weight, iw);
      float y = (x >= 0) ? x : x * w;
      p->set_output(p->output, s, y);
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
