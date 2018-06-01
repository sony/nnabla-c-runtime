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

rt_function_error_t exec_sum_generic(rt_function_t *f);

// Sum
rt_function_error_t allocate_sum_local_context(rt_function_t *f) {
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_sum;
  } else {
    f->exec_func = exec_sum_generic;
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_sum_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sum(rt_function_t *f) {
  sum_local_context_t *context = (sum_local_context_t *)(f->local_context);
  const int *x = (int *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  int reduction_size = 1;

  for (int i = 0; i < context->axes.size; i++) {
    reduction_size *= f->inputs[0]->shape.data[context->axes.data[i]];
  }

  const int outer_size = calc_shape_size(f->inputs[0]->shape) / reduction_size;
  for (int i = 0; i < outer_size; i++) {
    for (int j = 0; j < reduction_size; j++) {
      y[i] += x[i * reduction_size + j];
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sum_generic(rt_function_t *f) {
  sum_local_context_t *context = (sum_local_context_t *)(f->local_context);
  rt_variable_t *input = f->inputs[0];
  rt_variable_getter get_input = select_getter(input);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);
  int reduction_size = 1;

  for (int i = 0; i < context->axes.size; i++) {
    reduction_size *= f->inputs[0]->shape.data[context->axes.data[i]];
  }

  const int outer_size = calc_shape_size(f->inputs[0]->shape) / reduction_size;
  for (int i = 0; i < outer_size; i++) {
    for (int j = 0; j < reduction_size; j++) {
      float x = get_input(input, i * reduction_size + j);
      set_output(output, i, x);
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
