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
#include <string.h>

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  rt_list_t start;
  rt_list_t stop;
  rt_list_t step;
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
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

  slice_private_t *p = malloc(sizeof(slice_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);
  ((slice_local_context_t *)(f->local_context))->data = (void *)p;
  p->input_shape = clone_list(f->inputs[0]->shape);
  p->output_shape = clone_list(f->outputs[0]->shape);
  p->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  p->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  p->start = allocate_list(p->input_shape.size);
  p->stop = allocate_list(p->input_shape.size);
  p->step = allocate_list(p->input_shape.size);
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);

  int i, j;
  int diff = p->input_shape.size - context->start.size - 1;
  for (i = 0; i <= diff; i++) {
    p->start.data[i] = 0;
    p->stop.data[i] = p->input_shape.data[i];
    p->step.data[i] = 1;
  }
  for (j = 0; i < p->input_shape.size; i++, j++) {
    p->start.data[i] = context->start.data[j];
    p->stop.data[i] = context->stop.data[j];
    p->step.data[i] = context->step.data[j];
  }
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_slice;
  } else {
    f->exec_func = exec_slice_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_slice_local_context(rt_function_t *f) {
  slice_private_t *p =
      (slice_private_t *)(((slice_local_context_t *)(f->local_context))->data);
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->input_strides);
  free_list(p->output_strides);
  free_list(p->start);
  free_list(p->stop);
  free_list(p->step);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void slice_recursive(slice_local_context_t *context, int x_offset,
                            int y_offset, int dim) {
  slice_private_t *p = (slice_private_t *)(context->data);
  int current_x_offset = x_offset;
  int current_y_offset = y_offset;
  const int x_stride = p->input_strides.data[dim] * p->step.data[dim];
  const int y_stride = p->output_strides.data[dim];
  current_x_offset += p->input_strides.data[dim] * p->start.data[dim];
  const int size = p->output_shape.data[dim];
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  if (dim == p->input_shape.size - 1) {
    const float *current_x = x + current_x_offset;
    float *current_y = y + current_y_offset;
    if (x_stride == 1) {
      memcpy(current_y, current_x, sizeof(float) * size);
    } else {
      const float *end_x = current_x + size * x_stride;
      while (current_x != end_x) {
        *current_y = *current_x;
        current_x += x_stride;
        current_y += y_stride;
      }
    }
  } else {
    for (int i = 0; i < size; i++) {
      slice_recursive(context, current_x_offset, current_y_offset, dim + 1);
      current_x_offset += x_stride;
      current_y_offset += y_stride;
    }
  }
}

static void slice_recursive_generic(slice_local_context_t *context,
                                    int x_offset, int y_offset, int dim) {
  slice_private_t *p = (slice_private_t *)(context->data);
  int current_x_offset = x_offset;
  int current_y_offset = y_offset;
  const int x_stride = p->input_strides.data[dim] * p->step.data[dim];
  const int y_stride = p->output_strides.data[dim];
  current_x_offset += p->input_strides.data[dim] * p->start.data[dim];
  const int size = p->output_shape.data[dim];

  if (dim == p->input_shape.size - 1) {
    if (x_stride == 1) {
      for (int i = 0; i < size; i++) {
        float x = p->get_input(p->input, i + current_x_offset);
        p->set_output(p->output, i + current_y_offset, x);
      }
    } else {
      for (int i = 0; i < size; i++) {
        float x = p->get_input(p->input, current_x_offset);
        p->set_output(p->output, current_y_offset, x);
        current_x_offset += x_stride;
        current_y_offset += y_stride;
      }
    }
  } else {
    for (int i = 0; i < size; i++) {
      slice_recursive_generic(context, current_x_offset, current_y_offset,
                              dim + 1);
      current_x_offset += x_stride;
      current_y_offset += y_stride;
    }
  }
}

rt_function_error_t exec_slice(rt_function_t *f) {
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);

  slice_recursive(context, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_slice_generic(rt_function_t *f) {
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);

  slice_recursive_generic(context, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
