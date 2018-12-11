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
#include <nnablart/config.h>
#include <nnablart/functions.h>
#include <stdint.h>
#include <string.h>

#ifdef CONFIG_FLIP

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
  rt_list_t input_strides;
  uint8_t *flip;
} flip_private_t;

rt_function_error_t exec_flip_generic(rt_function_t *f);

// Flip
rt_function_error_t allocate_flip_local_context(rt_function_t *f) {
  flip_local_context_t *c = (flip_local_context_t *)(f->local_context);
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_FLIP_FLOAT32
    f->exec_func = exec_flip;
#endif /* CONFIG_FLIP_FLOAT32 */
  } else {
#ifdef CONFIG_FLIP_GENERIC
    f->exec_func = exec_flip_generic;
#endif /* CONFIG_FLIP_GENERIC */
  }

  flip_private_t *p = rt_malloc_func(sizeof(flip_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  ((flip_local_context_t *)(f->local_context))->data = (void *)p;
  p->flip = rt_malloc_func(sizeof(uint8_t) * (f->inputs[0]->shape.size - 1));
  memset(p->flip, 0, sizeof(uint8_t) * (f->inputs[0]->shape.size - 1));
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->input_strides = calc_contiguous_strides(p->input->shape);

  for (int i = 0; i < c->axes.size; i++) {
    p->flip[c->axes.data[i] - 1] = 1;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_flip_local_context(rt_function_t *f) {
  flip_private_t *p =
      (flip_private_t *)(((flip_local_context_t *)(f->local_context))->data);
  free_list(p->input_strides);
  rt_free_func(p->flip);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_FLIP_FLOAT32
static void flip_recursive(flip_local_context_t *c, int x_offset, int y_offset,
                           int dim) {
  flip_private_t *p = (flip_private_t *)(c->data);
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);
  int current_x_offset = x_offset, current_y_offset = y_offset;
  const int y_stride = p->input_strides.data[dim + 1];
  int x_stride = y_stride;
  const int size = p->input->shape.data[dim + 1];
  if (p->flip[dim]) {
    current_x_offset += x_stride * (size - 1);
    x_stride = -x_stride;
  }
  if (dim == p->input->shape.size - 2) {
    const float *current_x = x + current_x_offset;
    const float *end_x = current_x + size * x_stride;
    float *current_y = y + current_y_offset;
    if (x_stride == 1) {
      memcpy(current_y, current_x, sizeof(float) * size);
    } else {
      while (current_x != end_x) {
        *current_y = *current_x;
        current_x += x_stride;
        current_y += y_stride;
      }
    }
  } else {
    for (int i = 0; i < size; i++) {
      flip_recursive(c, current_x_offset, current_y_offset, dim + 1);
      current_x_offset += x_stride;
      current_y_offset += y_stride;
    }
  }
}

rt_function_error_t exec_flip(rt_function_t *f) {
  flip_local_context_t *c = (flip_local_context_t *)(f->local_context);

  flip_recursive(c, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_FLIP_FLOAT32 */

#ifdef CONFIG_FLIP_GENERIC
static void flip_recursive_generic(flip_local_context_t *c, int x_offset,
                                   int y_offset, int dim) {
  flip_private_t *p = (flip_private_t *)(c->data);
  int current_x_offset = x_offset, current_y_offset = y_offset;
  const int y_stride = p->input_strides.data[dim + 1];
  int x_stride = y_stride;
  const int size = p->input->shape.data[dim + 1];
  if (p->flip[dim]) {
    current_x_offset += x_stride * (size - 1);
    x_stride = -x_stride;
  }
  if (dim == p->input->shape.size - 2) {
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
      flip_recursive_generic(c, current_x_offset, current_y_offset, dim + 1);
      current_x_offset += x_stride;
      current_y_offset += y_stride;
    }
  }
}

rt_function_error_t exec_flip_generic(rt_function_t *f) {
  flip_local_context_t *c = (flip_local_context_t *)(f->local_context);

  flip_recursive_generic(c, 0, 0, 0);
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_FLIP_GENERIC */

#endif /* CONFIG_FLIP */
