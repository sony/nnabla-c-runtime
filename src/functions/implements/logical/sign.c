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
#include <nnablart/functions.h>
#include "../../utilities.h"

// Sign
rt_function_error_t allocate_sign_local_context(rt_function_t *f) {
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