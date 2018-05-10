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

#include <math.h>
#include <nnablart/functions.h>

#include "../../utilities/shape.h"

static inline float max(float a, float b) { return a < b ? b : a; }

typedef struct {
  int batch_size;
  int specified_axis_size;
  int output_size;
} softmax_private_t;

rt_function_error_t allocate_softmax_local_context(rt_function_t *f) {
  softmax_local_context_t *context =
      (softmax_local_context_t *)(f->local_context);
  softmax_private_t *p = malloc(sizeof(softmax_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  const int axis = context->axis;
  const int size = calc_shape_size(f->inputs[0]->shape);
  const int size_axis =
      axis <= 0 ? size : shape_product_of(f->inputs[0], axis,
                                          f->inputs[0]->shape.size);

  // axis must be less than ndim of inputs[0].
  if (f->inputs[0]->shape.size <= axis) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  p->batch_size = size / size_axis;
  p->specified_axis_size = size_axis;
  p->output_size = size / p->batch_size / p->specified_axis_size;
  if (p->batch_size * p->specified_axis_size * p->output_size != size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  ((softmax_local_context_t *)(f->local_context))->data = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_softmax_local_context(rt_function_t *f) {
  free(((softmax_local_context_t *)(f->local_context))->data);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_softmax(rt_function_t *f) {
  softmax_local_context_t *context =
      (softmax_local_context_t *)(f->local_context);
  softmax_private_t *p = (softmax_private_t *)(context->data);
  const float *const x = (float *)(f->inputs[0]->data);
  float *const y = (float *)(f->outputs[0]->data);
  const int batch_size = p->batch_size;
  const int specified_axis_size = p->specified_axis_size;
  const int output_size = p->output_size;

  int sample_index;
  for (sample_index = 0; sample_index < batch_size; ++sample_index) {
    int output_index;
    for (output_index = 0; output_index < output_size; ++output_index) {
      const int j =
          sample_index * specified_axis_size * output_size + output_index;
      // compute maximum
      float max_input = x[j];
      int specified_index;
      for (specified_index = 0; specified_index < specified_axis_size;
           ++specified_index) {
        const int k = specified_index * output_size + j;
        max_input = max(max_input, x[k]);
      }
      // Compute exponential and sum
      float exp_sum = 0;
      for (specified_index = 0; specified_index < specified_axis_size;
           ++specified_index) {
        const int k = specified_index * output_size + j;
        const float tmp = expf(x[k] - max_input);
        y[k] = tmp;
        exp_sum += tmp;
      }
      // Compute softmax
      for (specified_index = 0; specified_index < specified_axis_size;
           ++specified_index) {
        const int k = specified_index * output_size + j;
        y[k] = y[k] / exp_sum;
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
