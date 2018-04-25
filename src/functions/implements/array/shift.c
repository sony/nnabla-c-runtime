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
#include <string.h>

#include <math.h>

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  int **table;
  float *input;
  float *output;
} shift_private_t;

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

// Shift
rt_function_error_t allocate_shift_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  shift_private_t *private = malloc(sizeof(shift_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  shift_local_context_t *context = (shift_local_context_t *)(f->local_context);
  ((shift_local_context_t *)(f->local_context))->private = (void *)private;
  private->input_shape = clone_list(f->inputs[0]->shape);
  private->output_shape = clone_list(f->outputs[0]->shape);
  private->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  private->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  private->input = (float *)(f->inputs[0]->data);
  private->output = (float *)(f->outputs[0]->data);

  private->table = malloc(sizeof(int *) * private->input_shape.size);

  for (int i = 0; i < private->input_shape.size; i++) {
    const int stride = private->input_strides.data[i];
    const int size = private->input_shape.data[i];
    private->table[i] = malloc(size * sizeof(int));
    const int shift_index = context->shifts.size - private->input_shape.size + i;
    const int shift = shift_index >= 0 ? -context->shifts.data[shift_index] : 0;

    if (context->border_mode == SHIFT_BORDER_MODE_REFLECT) {
      for (int j = 0; j < size; j++) {
        const int a = size > 1 ? (abs(j + size * 2 + shift) % (size * 2)) : 0;
        private->table[i][j] = (a >= size ? (size * 2) - 1 - a : a) * stride;
      }
    } else {
      for (int j = 0; j < size; j++) {
        private->table[i][j] = MIN(MAX(j + shift, 0), size - 1) * stride;
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_shift_local_context(rt_function_t *f) {
  shift_private_t *private =
      (shift_private_t *)(((shift_local_context_t *)(f->local_context))
							  ->private);
  free_list(private->input_shape);
  free_list(private->output_shape);
  free_list(private->input_strides);
  free_list(private->output_strides);
  for (int i = 0; i < private->input_shape.size; i++) {
    free(private->table[i]);
  }
  free(private->table);
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void shift_recursive(shift_local_context_t *context, 
                            int x_offset, int y_offset, int dim)
{
  shift_private_t *private = (shift_private_t *)(context->private);
  int current_y_offset = y_offset;
  const int stride = private->input_strides.data[dim];
  const int size = private->input_shape.data[dim];
  const float *x = private->input;
  float *y = private->output;
  if (dim == private->input_shape.size -1) {
    for (int i = 0; i < size; i++) {
      y[current_y_offset] = x[x_offset + private->table[dim][i]];
          current_y_offset += stride;
    }
  } else {
    for (int i = 0; i < size; i++) {
      shift_recursive(context, x_offset + private->table[dim][i], current_y_offset, dim + 1);
          current_y_offset += stride;
    }
  }
}
rt_function_error_t exec_shift(rt_function_t *f) {
  shift_local_context_t *context = (shift_local_context_t *)(f->local_context);

  shift_recursive(context, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
