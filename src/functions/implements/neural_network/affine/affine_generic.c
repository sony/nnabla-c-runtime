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

#include <nnablart/functions.h>

#include "affine_internal.h"

rt_function_error_t exec_affine_generic(rt_function_t *f) {
  affine_private_t *p =
      (affine_private_t *)(((affine_local_context_t *)(f->local_context))
                               ->data);
  int i, j, k; // Iterators.

  // Clear output
  for (i = 0; i < p->output_size; i++) {
    p->set_output(p->output, i, 0);
  }

  for (k = 0; k < p->base_loop_size; k++) {
    int output_offset = k * p->output_loop_size;
    int input_offset = k * p->input_loop_size;

    // Weight
    for (j = 0; j < p->output_loop_size; ++j) {
      int opos = output_offset + j;
      int weight_offset = j * p->input_loop_size;
      float y0 = p->get_output(p->output, opos);

      for (i = 0; i < p->input_loop_size; ++i) {
        int ipos = input_offset + i;
        int wpos = weight_offset + i;

        float w = p->get_weight(p->weight, wpos);
        float x = p->get_input(p->input, ipos);
        y0 += x * w;
      }

      p->set_output(p->output, opos, y0);
    }

    // Bias
    if (p->bias) {
      for (i = 0; i < p->output_loop_size; i++) {
        int opos = output_offset + i;
        int bpos = i;
        p->set_output(p->output, opos, p->get_output(p->output, opos) +
                                           p->get_bias(p->bias, bpos));
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
