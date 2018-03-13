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

#include <math.h>

rt_function_error_t allocate_sum_pooling_local_context(rt_function_t *f) {
  sum_pooling_local_context_t *context = (sum_pooling_local_context_t *)(f->local_context);
  pooling_private_t *private = malloc(sizeof(pooling_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  private->input_shape = clone_list(f->inputs[0]->shape);
  private->output_shape = clone_list(f->outputs[0]->shape);
  private->input_n_kernel_size_diff = private->input_shape.size - context->kernel.size;
  if (context->stride.size == 0) {
    context->stride = clone_list(context->kernel);
  } else {
    if (context->kernel.size != context->stride.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
    if (context->kernel.size > private->input_shape.size) {
      return RT_FUNCTION_ERROR_INVALID_SHAPE;
    }
  }
  if (context->kernel.size != 2) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (context->kernel.size != context->pad.size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  // Calc and set output shape.
  rt_list_t shape = allocate_list(context->kernel.size);
  int i;
  for (i = 0; i < context->kernel.size; i++) {
    shape.data[i] = private->input_shape.data[i + private->input_n_kernel_size_diff];
  }
  for (i = 0; i < shape.size; i++) {
    shape.data[i] += 2 * context->pad.data[i];
    if (context->ignore_border) {
      shape.data[i] = (int)((shape.data[i] - context->kernel.data[i]) / context->stride.data[i]) + 1;
    } else {
      shape.data[i] = ceil(shape.data[i] * 1.0 / context->stride.data[i]);
    }
  }
  for (i = 0; i < private->input_shape.size; i++) {
    if (i < private->input_n_kernel_size_diff) {
      private->output_shape.data[i] = private->input_shape.data[i];
    } else {
      private->output_shape.data[i] = shape.data[i - private->input_n_kernel_size_diff];
    }
  }
  free_list(shape);

  // Calc x_stride and y_stride.
  const rt_list_t input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  const rt_list_t output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  private->x_stride =
    (private->input_n_kernel_size_diff == 0) ? calc_shape_size(f->inputs[0]->shape) : input_strides.data[private->input_n_kernel_size_diff - 1];
  private->y_stride =
    (private->input_n_kernel_size_diff == 0) ? calc_shape_size(f->outputs[0]->shape) : output_strides.data[private->input_n_kernel_size_diff - 1];
  free_list(input_strides);
  free_list(output_strides);

  ((sum_pooling_local_context_t *)(f->local_context))->private = (void *)private;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_sum_pooling_local_context(rt_function_t *f) {
  pooling_private_t *private =
      (pooling_private_t *)(((sum_pooling_local_context_t *)(f->local_context))
                               ->private);
  free_list(private->input_shape);
  free_list(private->output_shape);
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sum_pooling(rt_function_t *f) {
  sum_pooling_local_context_t *context = (sum_pooling_local_context_t *)(f->local_context);
  pooling_private_t *private =
      (pooling_private_t *)(((sum_pooling_local_context_t *)(f->local_context))
                               ->private);
  return exec_pooling(f, (pooling_context_t*)context, private, calc_sum);
}
