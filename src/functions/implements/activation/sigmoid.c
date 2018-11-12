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

#include <nnablart/config.h>
#include <nnablart/functions.h>

#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <assert.h>
#include <math.h>

#ifdef CONFIG_SIGMOID

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  int input_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
} sigmoid_local_context_t;

rt_function_error_t exec_sigmoid_generic(rt_function_t *f);

// Sigmoid
rt_function_error_t allocate_sigmoid_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  sigmoid_local_context_t *c = rt_malloc_func(sizeof(sigmoid_local_context_t));
  if (c == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  f->local_context = (void *)c;
  c->input = f->inputs[0];
  c->get_input = select_getter(c->input);
  c->input_size = calc_shape_size(f->inputs[0]->shape);

  c->output = f->outputs[0];
  c->set_output = select_setter(c->output);
  c->output_size = calc_shape_size(f->outputs[0]->shape);

  if (c->input_size != c->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_SIGMOID_FLOAT32
    f->exec_func = exec_sigmoid;
#endif /* CONFIG_SIGMOID_FLOAT32 */
  } else {
#ifdef CONFIG_SIGMOID_GENERIC
    f->exec_func = exec_sigmoid_generic;
#endif /* CONFIG_SIGMOID_GENERIC */
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_sigmoid_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_SIGMOID_FLOAT32
rt_function_error_t exec_sigmoid(rt_function_t *f) {
  sigmoid_local_context_t *c = (sigmoid_local_context_t *)(f->local_context);
  float *x = (float *)(c->input->data);
  float *y = (float *)(c->output->data);

  int i; // Iterator
  for (i = 0; i < c->output_size; i++) {
    y[i] = 1.0f / (1.0f + expf(-x[i]));
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_SIGMOID_FLOAT32 */

#ifdef CONFIG_SIGMOID_GENERIC
rt_function_error_t exec_sigmoid_generic(rt_function_t *f) {
  sigmoid_local_context_t *c = (sigmoid_local_context_t *)(f->local_context);

  int i; // Iterator
  for (i = 0; i < c->output_size; i++) {
    float val_x = c->get_input(c->input, i);
    float val_y = 1.0f / (1.0f + expf(-val_x));
    c->set_output(c->output, i, val_y);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_SIGMOID_GENERIC */

#endif /* CONFIG_SIGMOID */
