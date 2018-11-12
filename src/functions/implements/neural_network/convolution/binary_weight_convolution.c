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
#include "convolution_internal.h"
#include <assert.h>
#include <nnablart/config.h>

#ifdef CONFIG_BINARYWEIGHTCONVOLUTION

#define X (0)      // x input
#define WEIGHT (2) // weight
#define ALPHA (3)  // alpha
#define BIAS (4)   // bias
#define Y0 (0)     // y0 output

// BinaryWeightConvolution
rt_function_error_t
allocate_binary_weight_convolution_local_context(rt_function_t *f) {
  assert(sizeof(convolution_local_context_t) ==
         sizeof(binary_weight_convolution_local_context_t));

#ifdef CONFIG_BINARYWEIGHTCONVOLUTION_FLOAT32
  f->exec_func = exec_binary_weight_convolution;
#endif /* CONFIG_BINARYWEIGHTCONVOLUTION_FLOAT32 */

#ifdef CONFIG_BINARYWEIGHTCONVOLUTION_GENERIC
  for (int i = 0; i < f->num_of_inputs; i++) {
    if (f->inputs[i]->type != NN_DATA_TYPE_FLOAT) {
      f->exec_func = exec_convolution_generic;
      break;
    }
  }
  if (f->outputs[0]->type != NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_convolution_generic;
  }
#endif /* CONFIG_BINARYWEIGHTCONVOLUTION_GENERIC */
  return allocate_convolution_local_context_common(f, X, WEIGHT, BIAS, ALPHA,
                                                   Y0);
}

rt_function_error_t
free_binary_weight_convolution_local_context(rt_function_t *f) {
  return free_convolution_local_context_common(f);
}

#ifdef CONFIG_BINARYWEIGHTCONVOLUTION_FLOAT32
rt_function_error_t exec_binary_weight_convolution(rt_function_t *f) {
  return exec_convolution_float(f);
}
#endif /* CONFIG_BINARYWEIGHTCONVOLUTION_FLOAT32 */

#endif /* CONFIG_BINARYWEIGHTCONVOLUTION */
