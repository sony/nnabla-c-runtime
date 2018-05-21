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
#include <assert.h>
#include "convolution_internal.h"

#define X             (0)            //x input
#define WEIGHT        (2)            //weight
#define BIAS          (3)            //bias
#define Y0            (0)            //y0 output
#define ALPHA         (-1)           //alpha

// BinaryConnectConvolution
rt_function_error_t
allocate_binary_connect_convolution_local_context(rt_function_t *f) {
  assert(sizeof(convolution_local_context_t)
    == sizeof(binary_connect_convolution_local_context_t));

  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_binary_connect_convolution;
  } else {
    f->exec_func = exec_convolution_generic;
  }

  return allocate_convolution_local_context_common(f, X, WEIGHT, BIAS, ALPHA, Y0);
}

rt_function_error_t
free_binary_connect_convolution_local_context(rt_function_t *f) {
  return free_convolution_local_context_common(f);
}

rt_function_error_t exec_binary_connect_convolution(rt_function_t *f) {
  return exec_convolution_float(f);
}


