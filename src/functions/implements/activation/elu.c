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
#include <math.h>
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_ELU

rt_function_error_t exec_elu_generic(rt_function_t *f);

rt_function_error_t allocate_elu_local_context(rt_function_t *f) {
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_ELU_FLOAT32
    f->exec_func = exec_elu;
#endif /* CONFIG_ELU_FLOAT32 */
  } else {
#ifdef CONFIG_ELU_GENERIC
    f->exec_func = exec_elu_generic;
#endif /* CONFIG_ELU_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_elu_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_ELU_FLOAT32
rt_function_error_t exec_elu(rt_function_t *f) {
  elu_local_context_t *context = (elu_local_context_t *)(f->local_context);
  const float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  const int size = calc_shape_size(f->inputs[0]->shape);
  int s;
  for (s = 0; s < size; s++) {
    y[s] = (float)(x[s] > (float)0 ? x[s]
                                   : context->alpha * (expf(x[s]) - (float)1));
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_ELU_FLOAT32 */

#ifdef CONFIG_ELU_GENERIC
rt_function_error_t exec_elu_generic(rt_function_t *f) {
  elu_local_context_t *context = (elu_local_context_t *)(f->local_context);
  rt_variable_t *input = f->inputs[0];
  rt_variable_getter get_input = select_getter(input);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);
  const int size = calc_shape_size(f->inputs[0]->shape);
  int s;
  for (s = 0; s < size; s++) {
    float val_x = get_input(input, s);
    float val_y =
        (float)(val_x > (float)0 ? val_x
                                 : context->alpha * (expf(val_x) - (float)1));
    set_output(output, s, val_y);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_ELU_GENERIC */

#endif /* CONFIG_ELU */
