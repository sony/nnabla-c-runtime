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

#include "../../utilities.h"
#include <assert.h>
#include <math.h>
#include <nnablart/functions.h>

typedef struct {
  rt_variable_t weight_param;
  vector_calc_context_t calc_context;
} prelu_private_t;

// PRelu
rt_function_error_t allocate_prelu_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 2) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  prelu_private_t *p = malloc(sizeof(prelu_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }

  p->weight_param = *(f->inputs[1]);

  rt_variable_t input = *(f->inputs[0]);
  rt_variable_t output = *(f->outputs[0]);

  rt_variable_t inputs[] = {input, p->weight_param};
  p->calc_context = init_vector_calc_context(f->num_of_inputs, inputs, output);
  ((prelu_local_context_t *)(f->local_context))->private = (void *)p;
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_prelu_local_context(rt_function_t *f) {
  prelu_local_context_t *context = (prelu_local_context_t *)(f->local_context);
  prelu_private_t *p = (prelu_private_t *)(context->private);

  free_vector_calc_context(p->calc_context);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

static float calc_prelu(int num_of_inputs, float *inputs) {
  if (inputs[0] > 0) {
    return inputs[0];
  }
  return inputs[0] * inputs[1];
}

rt_function_error_t exec_prelu(rt_function_t *f) {
  prelu_local_context_t *context = (prelu_local_context_t *)(f->local_context);
  prelu_private_t *p = (prelu_private_t *)(context->private);

  rt_variable_t input = *(f->inputs[0]);
  rt_variable_t output = *(f->outputs[0]);

  rt_variable_t inputs[] = {input, p->weight_param};
  vector_calc(p->calc_context, f->num_of_inputs, inputs, output, calc_prelu);
  return RT_FUNCTION_ERROR_NOERROR;
}
