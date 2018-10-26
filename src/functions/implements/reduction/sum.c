// Copyright (c) 2018 Sony Corporation. All Rights Reserved.
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
#include <string.h>

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_getter get_output;
  rt_variable_setter set_output;
  rt_list_t in_position;
  rt_list_t out_position;
  int input_size;
} sum_private_t;

rt_function_error_t exec_sum_generic(rt_function_t *f);

// Sum
rt_function_error_t allocate_sum_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  sum_private_t *p = rt_malloc_func(sizeof(sum_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  ((sum_local_context_t *)(f->local_context))->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_size = calc_shape_size(f->inputs[0]->shape);

  p->output = f->outputs[0];
  p->get_output = select_getter(p->output);
  p->set_output = select_setter(p->output);

  p->in_position = allocate_list(p->input->shape.size);
  p->out_position = allocate_list(p->output->shape.size);

  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_sum;
  } else {
    f->exec_func = exec_sum_generic;
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_sum_local_context(rt_function_t *f) {
  sum_private_t *p =
      (sum_private_t *)(((sum_local_context_t *)(f->local_context))->data);
  free_list(p->in_position);
  free_list(p->out_position);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sum(rt_function_t *f) {
  sum_local_context_t *context = (sum_local_context_t *)(f->local_context);
  sum_private_t *p = (sum_private_t *)(context->data);
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  memset(p->output->data, 0, sizeof(float) * calc_shape_size(p->output->shape));
  for (int i = 0; i < p->input_size; i++) {
    int o = 0;
    int prev = -1;
    pos_to_shape(p->in_position, p->input->shape, i);
    for (int a = 0; a < context->axes.size; a++) {
      for (int j = prev + 1; j < context->axes.data[a]; j++) {
        if (o < p->out_position.size) {
          p->out_position.data[o++] = p->in_position.data[j];
        }
      }
      if (context->keep_dims) {
        if (o < p->out_position.size) {
          p->out_position.data[o++] = 0;
        }
      }
      prev = context->axes.data[a];
    }
    for (int j = prev + 1; j < p->in_position.size; j++) {
      if (o < p->out_position.size) {
        p->out_position.data[o++] = p->in_position.data[j];
      }
    }
    int index = shape_to_pos(p->output->shape, p->out_position);
    y[index] += x[i];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sum_generic(rt_function_t *f) {
  sum_local_context_t *context = (sum_local_context_t *)(f->local_context);
  sum_private_t *p = (sum_private_t *)(context->data);

  fill_variable_with(f->outputs[0], 0);
  for (int i = 0; i < p->input_size; i++) {
    int o = 0;
    int prev = -1;
    pos_to_shape(p->in_position, p->input->shape, i);
    for (int a = 0; a < context->axes.size; a++) {
      for (int j = prev + 1; j < context->axes.data[a]; j++) {
        if (o < p->out_position.size) {
          p->out_position.data[o++] = p->in_position.data[j];
        }
      }
      if (context->keep_dims) {
        if (o < p->out_position.size) {
          p->out_position.data[o++] = 0;
        }
      }
      prev = context->axes.data[a];
    }
    for (int j = prev + 1; j < p->in_position.size; j++) {
      if (o < p->out_position.size) {
        p->out_position.data[o++] = p->in_position.data[j];
      }
    }
    int index = shape_to_pos(p->output->shape, p->out_position);
    float x = p->get_input(p->input, i);
    float y = p->get_output(p->output, index);
    y += x;
    p->set_output(p->output, index, y);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
