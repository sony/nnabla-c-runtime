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

#include "../../utilities/shape.h"
#include "../../utilities/accessor.h"
#include <assert.h>
#include <math.h>
#include <nnablart/functions.h>

rt_function_error_t exec_leaky_relu_generic(rt_function_t *f);

// LeakyReLU
rt_function_error_t allocate_leaky_relu_local_context(rt_function_t *f) {
  int input_size, output_size;

  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  input_size = calc_shape_size(f->inputs[0]->shape);
  output_size = calc_shape_size(f->outputs[0]->shape);

  if (input_size != output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_leaky_relu;
  } else {
    f->exec_func = exec_leaky_relu_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_leaky_relu_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_leaky_relu(rt_function_t *f) {
  leaky_relu_local_context_t *c =
      (leaky_relu_local_context_t *)(f->local_context);
  const float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  const int output_size = calc_shape_size(f->inputs[0]->shape);
  int i;

  for (i = 0; i < output_size; ++i) {
    y[i] = x[i] > 0.0f ? x[i] : x[i] * c->alpha;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_leaky_relu_generic(rt_function_t *f) {
  leaky_relu_local_context_t *c =
      (leaky_relu_local_context_t *)(f->local_context);
  rt_variable_t *input = f->inputs[0];
  rt_variable_getter get_input = select_getter(input);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);
  const int output_size = calc_shape_size(f->inputs[0]->shape);
  int i;

  for (i = 0; i < output_size; ++i) {
    float val_x = get_input(input, i);
    float val_y = val_x > 0.0f ? val_x : val_x * c->alpha;
    set_output(output, i, val_y);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
