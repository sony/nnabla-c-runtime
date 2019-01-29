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

#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_RESHAPE

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;
  int input_size;
  rt_variable_t *output;
  rt_variable_setter set_output;
  int output_size;
} reshape_private_t;

rt_function_error_t exec_reshape_generic(rt_function_t *f);

// Reshape
rt_function_error_t allocate_reshape_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  reshape_private_t *p = rt_malloc_func(sizeof(reshape_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->input_size = calc_shape_size(f->inputs[0]->shape);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);
  p->output_size = calc_shape_size(f->outputs[0]->shape);
  if (p->input_size != p->output_size) {
    rt_free_func(p);
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  ((reshape_local_context_t *)(f->local_context))->data = (void *)p;
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_RESHAPE_FLOAT32
    f->exec_func = exec_reshape;
#endif /* CONFIG_RESHAPE_FLOAT32 */
  } else {
#ifdef CONFIG_RESHAPE_GENERIC
    f->exec_func = exec_reshape_generic;
#endif /* CONFIG_RESHAPE_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_reshape_local_context(rt_function_t *f) {
  rt_free_func(((reshape_local_context_t *)(f->local_context))->data);
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_RESHAPE_FLOAT32
rt_function_error_t exec_reshape(rt_function_t *f) {
  reshape_local_context_t *context =
      (reshape_local_context_t *)(f->local_context);
  reshape_private_t *p = (reshape_private_t *)(context->data);
  float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  int i; // Iterator
  for (i = 0; i < p->output_size; i++) {
    y[i] = x[i];
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_RESHAPE_FLOAT32 */

#ifdef CONFIG_RESHAPE_GENERIC
rt_function_error_t exec_reshape_generic(rt_function_t *f) {
  reshape_local_context_t *context =
      (reshape_local_context_t *)(f->local_context);
  reshape_private_t *p = (reshape_private_t *)(context->data);

  int i; // Iterator
  for (i = 0; i < p->output_size; i++) {
    float x = p->get_input(p->input, i);
    p->set_output(p->output, i, x);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_RESHAPE_GENERIC */

#endif /* CONFIG_RESHAPE */
