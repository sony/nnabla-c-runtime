// Copyright 2018,2019,2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
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
#include <math.h>
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_BINARYTANH

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  int input_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
} binary_tanh_private_context_t;

rt_function_error_t exec_binary_tanh_generic(rt_function_t *f);

// BinaryTanh
rt_function_error_t allocate_binary_tanh_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  binary_tanh_private_context_t *p =
      rt_malloc_func(sizeof(binary_tanh_private_context_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  f->local_context = p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_size = calc_shape_size(f->inputs[0]->shape);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->output_size = calc_shape_size(f->outputs[0]->shape);
  if (p->input_size != p->output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_BINARYTANH_FLOAT32
    f->exec_func = exec_binary_tanh;
#endif /* CONFIG_BINARYTANH_FLOAT32 */
  } else {
#ifdef CONFIG_BINARYTANH_GENERIC
    f->exec_func = exec_binary_tanh_generic;
#endif /* CONFIG_BINARYTANH_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_binary_tanh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_BINARYTANH_FLOAT32
rt_function_error_t exec_binary_tanh(rt_function_t *f) {
  binary_tanh_private_context_t *p =
      (binary_tanh_private_context_t *)(f->local_context);
  float *input = (float *)(p->input->data);
  float *output = (float *)(p->output->data);
  int i; // Iterator
  for (i = 0; i < p->input_size; i++) {
    float x = (input[i] + 1) / 2;
    if (x < 0) {
      x = 0;
    }
    if (x > 1) {
      x = 1;
    }
    output[i] = roundf(x) * 2 - 1;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_BINARYTANH_FLOAT32 */

#ifdef CONFIG_BINARYTANH_GENERIC
rt_function_error_t exec_binary_tanh_generic(rt_function_t *f) {
  binary_tanh_private_context_t *p =
      (binary_tanh_private_context_t *)(f->local_context);
  int i; // Iterator
  for (i = 0; i < p->input_size; i++) {
    float x = (p->get_input(p->input, i) + 1) / 2;
    if (x < 0) {
      x = 0;
    }
    if (x > 1) {
      x = 1;
    }
    p->set_output(p->output, i, roundf(x) * 2 - 1);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_BINARYTANH_GENERIC */

#endif /* CONFIG_BINARYTANH */
