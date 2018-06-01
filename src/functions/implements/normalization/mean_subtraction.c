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
#include <assert.h>
#include <math.h>
#include <nnablart/functions.h>

rt_function_error_t exec_mean_subtraction_generic(rt_function_t *f);

// MeanSubtraction
rt_function_error_t allocate_mean_subtraction_local_context(rt_function_t *f) {
  mean_subtraction_local_context_t *ctx =
      (mean_subtraction_local_context_t *)f->local_context;
  rt_list_t in_shape = f->inputs[0]->shape;
  int s0 = 1, i;
  for (i = ctx->base_axis; i < in_shape.size; ++i) {
    s0 *= in_shape.data[i];
  }
  if (calc_shape_size(f->inputs[1]->shape) != s0) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->inputs[1]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_mean_subtraction;
  } else {
    f->exec_func = exec_mean_subtraction_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_mean_subtraction_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

/*
 * ctx->update_running_mean is omitted, since in inferring time,
 * we do not update running mean any more.
 */
rt_function_error_t exec_mean_subtraction(rt_function_t *f) {
  mean_subtraction_local_context_t *ctx =
      (mean_subtraction_local_context_t *)f->local_context;
  rt_list_t in_shape = f->inputs[0]->shape;
  float *y = (float *)(f->outputs[0]->data);
  float *x = (float *)(f->inputs[0]->data);
  float *rm = (float *)(f->inputs[1]->data);
  int i, j, s0 = 1, s1;

  for (i = ctx->base_axis; i < in_shape.size; ++i) {
    s0 *= in_shape.data[i];
  }
  s1 = calc_shape_size(f->inputs[0]->shape) / s0;
  for (i = 0; i < s0; ++i) {
    for (j = 0; j < s1; ++i) {
      int idx = j * s0 + i;
      y[idx] = x[idx] - rm[i];
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_mean_subtraction_generic(rt_function_t *f) {
  mean_subtraction_local_context_t *ctx =
      (mean_subtraction_local_context_t *)f->local_context;
  rt_list_t in_shape = f->inputs[0]->shape;
  rt_variable_t *input_x = f->inputs[0];
  rt_variable_getter get_x = select_getter(input_x);
  rt_variable_t *input_rm = f->inputs[1];
  rt_variable_getter get_rm = select_getter(input_rm);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);
  int i, j, s0 = 1, s1;

  for (i = ctx->base_axis; i < in_shape.size; ++i) {
    s0 *= in_shape.data[i];
  }
  s1 = calc_shape_size(f->inputs[0]->shape) / s0;
  for (i = 0; i < s0; ++i) {
    for (j = 0; j < s1; ++i) {
      int idx = j * s0 + i;
      float x = get_x(input_x, idx);
      float rm = get_rm(input_rm, i);
      set_output(output, idx, x - rm);
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
