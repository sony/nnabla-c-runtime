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

void exec_affine_generic(rt_function_t *f) {
  WHOAMI("%s\n", __func__);

  affine_local_context_t *c =
      (affine_local_context_t *)(((affine_config_t *)(f->config))
                                     ->local_context);
  int i, j, k; // Iterators.

  // Clear output
  for (i = 0; i < c->output_size; i++) {
    c->set_output(c->output, i, 0);
  }

  for (k = 0; k < c->base_loop_size; k++) {
    int output_offset = k * c->output_loop_size;
    int input_offset = k * c->input_loop_size;

    // Weight
    for (j = 0; j < c->input_loop_size; j++) {
      int ipos = input_offset + j;
      int weight_offset = j * c->output_loop_size;

      float u = c->get_input(c->input, ipos);
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int wpos = weight_offset + i;

        float w = c->get_weight(c->weight, wpos);
        float value = c->get_output(c->output, opos);
        c->set_output(c->output, opos, value + u * w);
      }
    }

    // Bias
    if (c->bias) {
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int bpos = i;
        c->set_output(c->output, opos, c->get_output(c->output, opos) +
                                           c->get_bias(c->bias, bpos));
      }
    }
  }
}
