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
  rt_list_t in_position;
  rt_list_t out_position;
  uint8_t *flip;
  int output_size;
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
  p->flip = rt_malloc_func(sizeof(uint8_t) * (f->inputs[0]->shape.size));
  memset(p->flip, 0, sizeof(uint8_t) * (f->inputs[0]->shape.size));
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->in_position = allocate_list(p->input->shape.size);
  p->out_position = allocate_list(p->output->shape.size);
  p->output_size = calc_shape_size(p->output->shape);

  for (int i = 0; i < c->axes.size; i++) {
    p->flip[c->axes.data[i]] = 1;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_flip_local_context(rt_function_t *f) {
  flip_private_t *p =
      (flip_private_t *)(((flip_local_context_t *)(f->local_context))->data);
  free_list(p->in_position);
  free_list(p->out_position);
  rt_free_func(p->flip);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_FLIP_FLOAT32
rt_function_error_t exec_flip(rt_function_t *f) {
  flip_local_context_t *c = (flip_local_context_t *)(f->local_context);
  flip_private_t *p = (flip_private_t *)(c->data);
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  for (int o = 0; o < p->output_size; o++) {
    pos_to_shape(p->out_position, p->output->shape, o);
    for (int i = 0; i < p->input->shape.size; i++) {
      if (p->flip[i]) {
        p->in_position.data[i] =
            p->input->shape.data[i] - p->out_position.data[i] - 1;
      } else {
        p->in_position.data[i] = p->out_position.data[i];
      }
    }
    int index = shape_to_pos(p->input->shape, p->in_position);
    y[o] = x[index];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_FLIP_FLOAT32 */

#ifdef CONFIG_FLIP_GENERIC
rt_function_error_t exec_flip_generic(rt_function_t *f) {
  flip_local_context_t *c = (flip_local_context_t *)(f->local_context);
  flip_private_t *p = (flip_private_t *)(c->data);

  for (int o = 0; o < p->output_size; o++) {
    pos_to_shape(p->out_position, p->output->shape, o);
    for (int i = 0; i < p->input->shape.size; i++) {
      if (p->flip[i]) {
        p->in_position.data[i] =
            p->input->shape.data[i] - p->out_position.data[i] - 1;
      } else {
        p->in_position.data[i] = p->out_position.data[i];
      }
    }
    int index = shape_to_pos(p->input->shape, p->in_position);
    float x = p->get_input(p->input, index);
    p->set_output(p->output, o, x);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_FLIP_GENERIC */

#endif /* CONFIG_FLIP */
