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
#include "../../utilities/accessor.h"
#include <nnablart/functions.h>
#include <string.h>

#include <math.h>

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  int **table;
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
} shift_private_t;

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

rt_function_error_t exec_shift_generic(rt_function_t *f);

// Shift
rt_function_error_t allocate_shift_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  shift_private_t *p = malloc(sizeof(shift_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  shift_local_context_t *context = (shift_local_context_t *)(f->local_context);
  ((shift_local_context_t *)(f->local_context))->data = (void *)p;
  p->input_shape = clone_list(f->inputs[0]->shape);
  p->output_shape = clone_list(f->outputs[0]->shape);
  p->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  p->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);

  p->table = malloc(sizeof(int *) * p->input_shape.size);

  for (int i = 0; i < p->input_shape.size; i++) {
    const int stride = p->input_strides.data[i];
    const int size = p->input_shape.data[i];
    p->table[i] = malloc(size * sizeof(int));
    const int shift_index = context->shifts.size - p->input_shape.size + i;
    const int shift = shift_index >= 0 ? -context->shifts.data[shift_index] : 0;

    if (context->border_mode == SHIFT_BORDER_MODE_REFLECT) {
      for (int j = 0; j < size; j++) {
        const int a = size > 1 ? (abs(j + size * 2 + shift) % (size * 2)) : 0;
        p->table[i][j] = (a >= size ? (size * 2) - 1 - a : a) * stride;
      }
    } else {
      for (int j = 0; j < size; j++) {
        p->table[i][j] = MIN(MAX(j + shift, 0), size - 1) * stride;
      }
    }
  }
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_shift;
  } else {
    f->exec_func = exec_shift_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_shift_local_context(rt_function_t *f) {
  shift_private_t *p =
      (shift_private_t *)(((shift_local_context_t *)(f->local_context))->data);
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->input_strides);
  free_list(p->output_strides);
  for (int i = 0; i < p->input_shape.size; i++) {
    free(p->table[i]);
  }
  free(p->table);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void shift_recursive(shift_local_context_t *context, int x_offset,
                            int y_offset, int dim) {
  shift_private_t *p = (shift_private_t *)(context->data);
  int current_y_offset = y_offset;
  const int stride = p->input_strides.data[dim];
  const int size = p->input_shape.data[dim];
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);
  if (dim == p->input_shape.size - 1) {
    for (int i = 0; i < size; i++) {
      y[current_y_offset] = x[x_offset + p->table[dim][i]];
      current_y_offset += stride;
    }
  } else {
    for (int i = 0; i < size; i++) {
      shift_recursive(context, x_offset + p->table[dim][i], current_y_offset,
                      dim + 1);
      current_y_offset += stride;
    }
  }
}

static void shift_recursive_generic(shift_local_context_t *context,
                                    int x_offset, int y_offset, int dim) {
  shift_private_t *p = (shift_private_t *)(context->data);
  int current_y_offset = y_offset;
  const int stride = p->input_strides.data[dim];
  const int size = p->input_shape.data[dim];

  if (dim == p->input_shape.size - 1) {
    for (int i = 0; i < size; i++) {
      float x = p->get_input(p->input, x_offset + p->table[dim][i]);
      p->set_output(p->output, current_y_offset, x);
      current_y_offset += stride;
    }
  } else {
    for (int i = 0; i < size; i++) {
      shift_recursive_generic(context, x_offset + p->table[dim][i],
                              current_y_offset, dim + 1);
      current_y_offset += stride;
    }
  }
}

rt_function_error_t exec_shift(rt_function_t *f) {
  shift_local_context_t *context = (shift_local_context_t *)(f->local_context);

  shift_recursive(context, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_shift_generic(rt_function_t *f) {
  shift_local_context_t *context = (shift_local_context_t *)(f->local_context);

  shift_recursive_generic(context, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
