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

rt_function_error_t exec_sign_generic(rt_function_t *f);

// Sign
rt_function_error_t allocate_sign_local_context(rt_function_t *f) {
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_sign;
  } else {
    f->exec_func = exec_sign_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_sign_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sign(rt_function_t *f) {
  sign_local_context_t *c = (sign_local_context_t *)(f->local_context);
  float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);

  const int output_size = calc_shape_size(f->inputs[0]->shape);
  int i;
  for (i = 0; i < output_size; ++i) {
    y[i] = (x[i] > 0) ? 1 : ((x[i] < 0) ? -1 : c->alpha);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_sign_generic(rt_function_t *f) {
  sign_local_context_t *c = (sign_local_context_t *)(f->local_context);
  rt_variable_t *input = f->inputs[0];
  rt_variable_getter get_input = select_getter(input);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);

  const int output_size = calc_shape_size(f->inputs[0]->shape);
  int i;
  for (i = 0; i < output_size; ++i) {
    float x = get_input(input, i);
    float y = (x > 0) ? 1 : ((x < 0) ? -1 : c->alpha);
    set_output(output, i, y);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
