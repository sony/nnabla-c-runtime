// Copyright 2018,2019,2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
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
#include <limits.h>
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_SLICE

typedef struct {
  rt_list_t start;
  rt_list_t step;
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
  rt_list_t in_position;
  rt_list_t out_position;
  int output_size;
} slice_private_t;

rt_function_error_t exec_slice_generic(rt_function_t *f);

// Slice
rt_function_error_t allocate_slice_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  slice_private_t *p = rt_malloc_func(sizeof(slice_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);
  ((slice_local_context_t *)(f->local_context))->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->start = allocate_list(p->input->shape.size);
  p->step = allocate_list(p->input->shape.size);
  p->in_position = allocate_list(p->input->shape.size);
  p->out_position = allocate_list(p->output->shape.size);
  p->output_size = calc_shape_size(p->output->shape);

  int i, j;
  int diff = p->input->shape.size - context->start.size - 1;
  for (i = 0; i <= diff; i++) {
    p->start.data[i] = 0;
    p->step.data[i] = 1;
  }
  for (j = 0; i < p->input->shape.size; i++, j++) {
    if (context->start.data[j] < 0 || context->start.data[j] == INT_MAX) {
      p->start.data[i] = 0;
    } else {
      p->start.data[i] = context->start.data[j];
    }
    if (context->step.data[j] < 0 || context->step.data[j] == INT_MAX) {
      p->step.data[i] = 1;
    } else {
      p->step.data[i] = context->step.data[j];
    }
  }
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_SLICE_FLOAT32
    f->exec_func = exec_slice;
#endif /* CONFIG_SLICE_FLOAT32 */
  } else {
#ifdef CONFIG_SLICE_GENERIC
    f->exec_func = exec_slice_generic;
#endif /* CONFIG_SLICE_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_slice_local_context(rt_function_t *f) {
  slice_private_t *p =
      (slice_private_t *)(((slice_local_context_t *)(f->local_context))->data);
  free_list(p->start);
  free_list(p->step);
  free_list(p->in_position);
  free_list(p->out_position);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_SLICE_FLOAT32
rt_function_error_t exec_slice(rt_function_t *f) {
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);
  slice_private_t *p = (slice_private_t *)(context->data);
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  for (int o = 0; o < p->output_size; o++) {
    pos_to_shape(p->out_position, p->output->shape, o);
    for (int i = 0; i < p->input->shape.size; i++) {
      p->in_position.data[i] =
          p->out_position.data[i] * p->step.data[i] + p->start.data[i];
    }
    int index = shape_to_pos(p->input->shape, p->in_position);
    y[o] = x[index];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_SLICE_FLOAT32 */

#ifdef CONFIG_SLICE_GENERIC
rt_function_error_t exec_slice_generic(rt_function_t *f) {
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);
  slice_private_t *p = (slice_private_t *)(context->data);

  for (int o = 0; o < p->output_size; o++) {
    pos_to_shape(p->out_position, p->output->shape, o);
    for (int i = 0; i < p->input->shape.size; i++) {
      p->in_position.data[i] =
          p->out_position.data[i] * p->step.data[i] + p->start.data[i];
    }
    int index = shape_to_pos(p->input->shape, p->in_position);
    float x = p->get_input(p->input, index);
    p->set_output(p->output, o, x);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_SLICE_GENERIC */

#endif /* CONFIG_SLICE */
