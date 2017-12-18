// -*- coding:utf-8 -*-
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

#include <string.h>

#include "affine_internal.h"

void exec_affine_float(rt_function_t *f) {
  affine_local_context_t *c =
      (affine_local_context_t *)(((affine_config_t *)(f->config))
                                     ->local_context);
  int i, j, k; // Iterators.
  float* input = (float*)(c->input->data);
  float* weight = (float*)(c->weight->data);
  float* output = (float*)(c->output->data);
  
  // Clear output
  memset(output, 0, sizeof(float) * c->output_size);

  for (k = 0; k < c->base_loop_size; k++) {
    int output_offset = k * c->output_loop_size;
    int input_offset = k * c->input_loop_size;

    // Weight
    for (j = 0; j < c->input_loop_size; j++) {
      int ipos = input_offset + j;
      int weight_offset = j * c->output_loop_size;

      float u = *(input + ipos);
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int wpos = weight_offset + i;

        float w = *(weight + wpos);
        float value = *(output + opos);
        *(output + opos) = value + u * w;
      }
    }

    // Bias
    if (c->bias) {
      float* bias = (float*)(c->bias->data);
      for (i = 0; i < c->output_loop_size; i++) {
        int opos = output_offset + i;
        int bpos = i;
        *(output + opos) = *(output + opos) + *(bias + bpos);
      }
    }
  }
}
