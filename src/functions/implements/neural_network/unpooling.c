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

#include "../../utilities/list.h"
#include "../../utilities/shape.h"
#include "pooling.h"

#include <nnablart/functions.h>

#include <string.h>

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  rt_list_t kernel;
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
} unpooling_private_t;

rt_function_error_t allocate_unpooling_local_context(rt_function_t *f) {
  unpooling_local_context_t *context =
      (unpooling_local_context_t *)(f->local_context);
  unpooling_private_t *p = malloc(sizeof(unpooling_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  p->input_shape = clone_list(f->inputs[0]->shape);
  p->output_shape = clone_list(f->outputs[0]->shape);
  p->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  p->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);

  if (context->kernel.size > p->input_shape.size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  // Calc and set output shape.
  rt_list_t shape = allocate_list(p->input_shape.size);
  int diff = p->input_shape.size - context->kernel.size;
  int i;
  for (i = 0; i < diff; i++) {
    shape.data[i] = 1;
  }
  for (i = diff; i < p->input_shape.size; i++) {
    shape.data[i] = context->kernel.data[i - diff];
  }
  p->kernel = clone_list(shape);
  for (i = 0; i < p->input_shape.size; i++) {
    p->output_shape.data[i] = p->input_shape.data[i] * p->kernel.data[i];
  }
  free_list(shape);

  ((unpooling_local_context_t *)(f->local_context))->data = (void *)p;

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_unpooling_local_context(rt_function_t *f) {
  unpooling_private_t *p =
      (unpooling_private_t *)(((unpooling_local_context_t *)(f->local_context))
                                  ->data);
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->input_strides);
  free_list(p->output_strides);
  free_list(p->kernel);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void unpooling_forward_recursive_generic(unpooling_private_t *p,
                                                int x_offset, int y_offset,
                                                int dim) {
  int current_x_offset = x_offset;
  int current_y_offset = y_offset;
  const int x_stride = p->input_strides.data[dim];
  const int y_stride = p->output_strides.data[dim];
  const int kernel = p->kernel.data[dim];
  const int size = p->output_shape.data[dim];

  if (dim == p->input_shape.size - 1) {
    if (x_stride == 1 && kernel == 1) {
      for (int i = 0; i < size; i++) {
        float value = p->get_input(p->input, i + current_x_offset);
        p->set_output(p->output, i + current_y_offset, value);
      }
    } else {
      int count = 0;
      for (int i = 0; i < size; i++) {
        float value = p->get_input(p->input, current_x_offset);
        p->set_output(p->output, current_y_offset, value);
        if (++count >= kernel) {
          count = 0;
          current_x_offset += x_stride;
        }
        current_y_offset += y_stride;
      }
    }
  } else {
    int count = 0;
    int i;
    for (i = 0; i < size; i++) {
      unpooling_forward_recursive_generic(p, current_x_offset, current_y_offset,
                                          dim + 1);
      if (++count >= kernel) {
        count = 0;
        current_x_offset += x_stride;
      }
      current_y_offset += y_stride;
    }
  }
}

static void unpooling_forward_recursive(unpooling_private_t *p, int x_offset,
                                        int y_offset, int dim) {
  int current_x_offset = x_offset;
  int current_y_offset = y_offset;
  const int x_stride = p->input_strides.data[dim];
  const int y_stride = p->output_strides.data[dim];
  const int kernel = p->kernel.data[dim];
  const int size = p->output_shape.data[dim];
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  if (dim == p->input_shape.size - 1) {
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
      unpooling_forward_recursive(p, current_x_offset, current_y_offset,
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
  unpooling_private_t *p =
      (unpooling_private_t *)(((unpooling_local_context_t *)(f->local_context))
                                  ->data);
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
    unpooling_forward_recursive(p, 0, 0, 0);
  } else {
    unpooling_forward_recursive_generic(p, 0, 0, 0);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
