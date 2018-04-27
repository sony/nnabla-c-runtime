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

#include "../../utilities.h"
#include <nnablart/functions.h>

#include <string.h>

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  rt_list_t kernel;
  float *input;
  float *output;
} unpooling_private_t;

rt_function_error_t allocate_unpooling_local_context(rt_function_t *f) {
  unpooling_local_context_t *context =
      (unpooling_local_context_t *)(f->local_context);
  unpooling_private_t *private = malloc(sizeof(unpooling_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
private
  ->input_shape = clone_list(f->inputs[0]->shape);
private
  ->output_shape = clone_list(f->outputs[0]->shape);
private
  ->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
private
  ->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
private
  ->input = (float *)(f->inputs[0]->data);
private
  ->output = (float *)(f->outputs[0]->data);

  if (context->kernel.size > private->input_shape.size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  // Calc and set output shape.
  rt_list_t shape = allocate_list(private->input_shape.size);
  int diff = private->input_shape.size - context->kernel.size;
  int i;
  for (i = 0; i < diff; i++) {
    shape.data[i] = 1;
  }
  for (i = diff; i < private->input_shape.size; i++) {
    shape.data[i] = context->kernel.data[i - diff];
  }
private
  ->kernel = clone_list(shape);
  for (i = 0; i < private->input_shape.size; i++) {
  private
    ->output_shape.data[i] =
        private->input_shape.data[i] * private->kernel.data[i];
  }
  free_list(shape);

  ((unpooling_local_context_t *)(f->local_context))->private = (void *)private;

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_unpooling_local_context(rt_function_t *f) {
  unpooling_private_t *private =
      (unpooling_private_t *)(((unpooling_local_context_t *)(f->local_context))
                                  ->private);
  free_list(private->input_shape);
  free_list(private->output_shape);
  free_list(private->input_strides);
  free_list(private->output_strides);
  free_list(private->kernel);
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void unpooling_forward_recursive(unpooling_private_t *private,
                                        int x_offset, int y_offset, int dim) {
  int current_x_offset = x_offset;
  int current_y_offset = y_offset;
  const int x_stride = private->input_strides.data[dim];
  const int y_stride = private->output_strides.data[dim];
  const int kernel = private->kernel.data[dim];
  const int size = private->output_shape.data[dim];
  const float *x = private->input;
  float *y = private->output;

  if (dim == private->input_shape.size - 1) {
    const float *current_x = x + current_x_offset;
    float *current_y = y + current_y_offset;
    if (x_stride == 1 && kernel == 1) {
      memcpy(current_y, current_x, sizeof(float) * size);
    } else {
      const float *end_y = current_y + size * y_stride;
      int count = 0;
      while (current_y != end_y) {
        *current_y = *current_x;
        if (++count >= kernel) {
          count = 0;
          current_x += x_stride;
        }
        current_y += y_stride;
      }
    }
  } else {
    int count = 0;
    int i;
    for (i = 0; i < size; i++) {
      unpooling_forward_recursive(private, current_x_offset, current_y_offset,
                                  dim + 1);
      if (++count >= kernel) {
        count = 0;
        current_x_offset += x_stride;
      }
      current_y_offset += y_stride;
    }
  }
}

rt_function_error_t exec_unpooling(rt_function_t *f) {
  unpooling_private_t *private =
      (unpooling_private_t *)(((unpooling_local_context_t *)(f->local_context))
                                  ->private);
  unpooling_forward_recursive(private, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
