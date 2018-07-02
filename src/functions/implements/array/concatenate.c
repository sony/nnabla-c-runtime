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
#include <nnablart/functions.h>

typedef struct {
  int outer_size;
  int inner_total_size;
} concatenate_private_t;

static inline int calc_size(rt_list_t shape, int axis) {
  int size = 1;
  for (int i = axis; i < shape.size; i++) {
    size *= shape.data[i];
  }
  return size;
}

rt_function_error_t exec_concatenate_generic(rt_function_t *f);

// Concatenate
rt_function_error_t allocate_concatenate_local_context(rt_function_t *f) {
  concatenate_local_context_t *c =
      (concatenate_local_context_t *)(f->local_context);

  f->exec_func = exec_concatenate;

  for (int i = 0; i < f->num_of_inputs; i++) {
    if (f->inputs[i]->type != NN_DATA_TYPE_FLOAT) {
      f->exec_func = exec_concatenate_generic;
    }
  }
  if (f->outputs[0]->type != NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_concatenate_generic;
  }

  concatenate_private_t *p =
      (concatenate_private_t *)malloc(sizeof(concatenate_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  p->inner_total_size = 0;
  for (int i = 0; i < f->num_of_inputs; i++) {
    const int inner_size = calc_size(f->inputs[i]->shape, c->axis);
    p->inner_total_size += inner_size;
  }
  p->outer_size = calc_shape_size(f->inputs[0]->shape) /
                  calc_size(f->inputs[0]->shape, c->axis);

  ((concatenate_local_context_t *)(f->local_context))->data = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_concatenate_local_context(rt_function_t *f) {
  concatenate_private_t *p =
      (concatenate_private_t
           *)(((concatenate_local_context_t *)(f->local_context))->data);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_concatenate(rt_function_t *f) {
  concatenate_local_context_t *c =
      (concatenate_local_context_t *)(f->local_context);
  concatenate_private_t *p = (concatenate_private_t *)(c->data);

  float *y = (float *)(f->outputs[0]->data);
  int inner_offset = 0;
  for (int i = 0; i < f->num_of_inputs; i++) {
    const float *x = (float *)(f->inputs[i]->data);
    const int inner_size = calc_size(f->inputs[i]->shape, c->axis);
    for (int j = 0; j < p->outer_size; ++j) {
      for (int k = 0; k < inner_size; k++) {
        y[j * p->inner_total_size + inner_offset + k] = x[j * inner_size + k];
      }
    }
    inner_offset += inner_size;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_concatenate_generic(rt_function_t *f) {
  concatenate_local_context_t *c =
      (concatenate_local_context_t *)(f->local_context);
  concatenate_private_t *p = (concatenate_private_t *)(c->data);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);

  int inner_offset = 0;
  for (int i = 0; i < f->num_of_inputs; i++) {
    rt_variable_t *input = f->inputs[i];
    rt_variable_getter get_input = select_getter(input);
    const int inner_size = calc_size(f->inputs[i]->shape, c->axis);
    for (int j = 0; j < p->outer_size; ++j) {
      for (int k = 0; k < inner_size; k++) {
        const float x = get_input(input, j * inner_size + k);
        set_output(output, j * p->inner_total_size + inner_offset + k, x);
      }
    }
    inner_offset += inner_size;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
