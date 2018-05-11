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

#include "../../utilities/shape.h"
#include <math.h>
#include <nnablart/functions.h>

rt_function_error_t allocate_selu_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_selu_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_selu(rt_function_t *f) {
  selu_local_context_t *context = (selu_local_context_t *)(f->local_context);
  const float *x = (float *)(f->inputs[0]->data);
  float *y = (float *)(f->outputs[0]->data);
  const float coef = context->alpha * context->scale;
  const int size = calc_shape_size(f->inputs[0]->shape);
  int s;
  for (s = 0; s < size; s++) {
    y[s] =
        x[s] > (float)0 ? context->scale * x[s] : coef * (exp(x[s]) - (float)1);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
