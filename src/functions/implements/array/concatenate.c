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
#include <nnablart/functions.h>
#include "../../utilities.h"

typedef struct {
  int outer_size;
  int inner_total_size;
  rt_list_t *in_shape;
} concatenate_private_t;

static inline int calc_size(rt_list_t shape, int axis)
{
  int size = 1;
  for (int i = axis; i < shape.size; i++) {
    size *= shape.data[i];
  }
  return size;
}

// Concatenate
rt_function_error_t allocate_concatenate_local_context(rt_function_t *f) {
  concatenate_local_context_t *c = (concatenate_local_context_t *)(f->local_context);
  concatenate_private_t* p = (concatenate_private_t*)malloc(sizeof(concatenate_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  for (int i = 0; i < f->num_of_inputs; i++) {
    p->in_shape[i] = clone_list(f->inputs[i]->shape);
    const int inner_size = calc_size(p->in_shape[i], c->axis);
    p->inner_total_size += inner_size;

    if (i >= 1) {
      p->in_shape[0].data[c->axis] += p->in_shape[i].data[c->axis];
    }
  }
  p->outer_size = calc_shape_size(p->in_shape[0]) / calc_size(p->in_shape[0], c->axis);

  ((concatenate_local_context_t *)(f->local_context))->private = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_concatenate_local_context(rt_function_t *f) {
  concatenate_private_t *private =
      (concatenate_private_t *)(((concatenate_local_context_t *)(f->local_context))
                           ->private);
  for (int i = 0; i < f->num_of_inputs; i++) {
    free_list(private->in_shape[i]);
  }
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_concatenate(rt_function_t *f) {
  concatenate_local_context_t *c = (concatenate_local_context_t *)(f->local_context);
  concatenate_private_t* p = (concatenate_private_t*)(c->private);

  float *y = (float *)(f->outputs[0]->data);
  int inner_offset = 0;
  for (int i = 0; i < f->num_of_inputs; i++) {
    const float *x = (float *)(f->inputs[i]->data);
    const int inner_size = calc_size(p->in_shape[i], c->axis);
    for (int j = 0; j < p->outer_size; ++j) {
      for (int k = 0; k < inner_size; k++) {
        y[j * p->inner_total_size + inner_offset + k] = x[j * inner_size + k];
      }
    }
    inner_offset += inner_size;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
