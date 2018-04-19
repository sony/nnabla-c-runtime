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

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  rt_list_t start;
  rt_list_t stop;
  rt_list_t step;
  float *input;
  float *output;
} slice_private_t;

// Slice
rt_function_error_t allocate_slice_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  slice_private_t *private = malloc(sizeof(slice_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);
  ((slice_local_context_t *)(f->local_context))->private = (void *)private;
  private->input_shape = clone_list(f->inputs[0]->shape);
  private->output_shape = clone_list(f->outputs[0]->shape);
  private->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  private->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  private->start = allocate_list(private->input_shape.size);
  private->stop = allocate_list(private->input_shape.size);
  private->step = allocate_list(private->input_shape.size);
  private->input = (float *)(f->inputs[0]->data);
  private->output = (float *)(f->outputs[0]->data);

  int i, j;
  int diff = private->input_shape.size - context->start.size - 1;
  for (i = 0; i <= diff; i++) {
    private->start.data[i] = 0;
    private->stop.data[i] = private->input_shape.data[i];
    private->step.data[i] = 1;
  }
  for (j = 0; i < private->input_shape.size; i++, j++) {
    private->start.data[i] = context->start.data[j];
    private->stop.data[i] = context->stop.data[j];
    private->step.data[i] = context->step.data[j];
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_slice_local_context(rt_function_t *f) {
  slice_private_t *private =
      (slice_private_t *)(((slice_local_context_t *)(f->local_context))
                              ->private);
  free_list(private->input_shape);
  free_list(private->output_shape);
  free_list(private->input_strides);
  free_list(private->output_strides);
  free_list(private->start);
  free_list(private->stop);
  free_list(private->step);
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void slice_recursive(slice_local_context_t *context,
                            int x_offset, int y_offset, int dim)
{
  slice_private_t *private = (slice_private_t *)(context->private);
  int current_x_offset = x_offset;
  int current_y_offset = y_offset;
  const int x_stride = private->input_strides.data[dim] * private->step.data[dim];
  const int y_stride = private->output_strides.data[dim];
  current_x_offset += private->input_strides.data[dim] * private->start.data[dim];
  const int size = private->output_shape.data[dim];
  const float *x = private->input;
  float *y = private->output;

  if (dim == private->input_shape.size - 1) {
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

rt_function_error_t exec_slice(rt_function_t *f) {
  slice_local_context_t *context = (slice_local_context_t *)(f->local_context);

  slice_recursive(context, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
