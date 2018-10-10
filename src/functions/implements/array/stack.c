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

typedef struct {
  int inner_size;
  int outer_size;
} stack_private_t;

static inline int calc_size(rt_list_t shape, int axis) {
  int size = 1;
  for (int i = axis; i < shape.size; i++) {
    size *= shape.data[i];
  }
  return size;
}

rt_function_error_t exec_stack_generic(rt_function_t *f);

// Stack
rt_function_error_t allocate_stack_local_context(rt_function_t *f) {
  stack_local_context_t *c = (stack_local_context_t *)(f->local_context);

  f->exec_func = exec_stack;

  for (int i = 0; i < f->num_of_inputs; i++) {
    if (f->inputs[i]->type != NN_DATA_TYPE_FLOAT) {
      f->exec_func = exec_stack_generic;
    }
  }
  if (f->outputs[0]->type != NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_stack_generic;
  }

  stack_private_t *p =
      (stack_private_t *)rt_malloc_func(sizeof(stack_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  ((stack_local_context_t *)(f->local_context))->data = (void *)p;

  p->inner_size = calc_size(f->inputs[0]->shape, c->axis);
  p->outer_size = calc_shape_size(f->inputs[0]->shape) / p->inner_size;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_stack_local_context(rt_function_t *f) {
  stack_private_t *p =
      (stack_private_t *)(((stack_local_context_t *)(f->local_context))->data);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_stack(rt_function_t *f) {
  stack_local_context_t *c = (stack_local_context_t *)(f->local_context);
  stack_private_t *p = (stack_private_t *)(c->data);

  float *y = (float *)(f->outputs[0]->data);
  for (int i = 0; i < f->num_of_inputs; i++) {
    const float *x = (float *)(f->inputs[i]->data);
    for (int j = 0; j < p->outer_size; j++) {
      for (int k = 0; k < p->inner_size; k++) {
        y[j * (p->inner_size * f->num_of_inputs) + i * p->inner_size + k] =
            x[j * p->inner_size + k];
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_stack_generic(rt_function_t *f) {
  stack_local_context_t *c = (stack_local_context_t *)(f->local_context);
  stack_private_t *p = (stack_private_t *)(c->data);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);

  for (int i = 0; i < f->num_of_inputs; i++) {
    rt_variable_t *input = f->inputs[i];
    rt_variable_getter get_input = select_getter(input);
    for (int j = 0; j < p->outer_size; j++) {
      for (int k = 0; k < p->inner_size; k++) {
        float x = get_input(input, j * p->inner_size + k);
        set_output(output, j * (p->inner_size * f->num_of_inputs) +
                               i * p->inner_size + k,
                   x);
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
