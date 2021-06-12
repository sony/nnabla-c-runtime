// Copyright 2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
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

#include "../../../utilities/fixedpoint.h"
#include "affine_internal.h"
#include <nnablart/functions.h>
#include <stdint.h>
#include <string.h> /* memset */

rt_function_error_t exec_affine_fixed8(rt_function_t *f) {
  affine_private_t *p =
      (affine_private_t *)(((affine_local_context_t *)(f->local_context))
                               ->data);
  int i, j, k; // Iterators.

  int8_t *input = (int8_t *)(p->input->data);
  int8_t *weight = (int8_t *)(p->weight->data);
  int8_t *output = (int8_t *)(p->output->data);
  int8_t *alpha = 0;

  const unsigned nbits_rescale =
      p->input->fp_pos + p->weight->fp_pos - p->output->fp_pos;

  if (p->alpha) {
    alpha = (int8_t *)p->alpha->data;
  }

  // If bias has less range bits (=more precision bits) than output, rescale
  // bias.
  // Otherwise, output has too few range bits. Change format before starting
  // computations.
  if (p->bias) {
    const unsigned int b_fp = p->bias->fp_pos;
    const unsigned int out_fp = p->output->fp_pos;
    const unsigned bias_size = p->output_loop_size;
    int8_t *bias = (int8_t *)(p->bias->data);

    if (b_fp > out_fp) {
      int i;
      for (i = 0; i < bias_size; i++) {
        *(bias + i) /= (1 << (b_fp - out_fp));
      }
    } else if (b_fp < out_fp) {
      printf(
          "OUTPUT variable has less range bits than BIAS variable. Please "
          "make sure affine/b has same or less range bits than Output to avoid "
          "overflow.\n");
      return RT_FUNCTION_ERROR_UNIMPLEMENTED;
    }
  }

  // Clear output
  memset(output, 0, sizeof(int8_t) * p->output_size);

  for (k = 0; k < p->base_loop_size; k++) {
    int output_offset = k * p->output_loop_size;
    int input_offset = k * p->input_loop_size;
    int8_t *o_addr = output + output_offset;
    int8_t *alpha_addr = alpha;

    for (j = 0; j < p->output_loop_size; ++j) {
      int weight_offset = j * p->input_loop_size;

      int8_t *i_addr = input + input_offset;
      int8_t *w_addr = weight + weight_offset;
      int32_t sum = 0;

      for (i = 0; i < p->input_loop_size; ++i) {
        sum += (*i_addr++) * (*w_addr++);
      }
      // Rescale output to desired # of precision bits
      *o_addr = saturate32_to_8(sum / (1 << nbits_rescale));

      if (alpha) {
        *o_addr = (((int16_t)(*o_addr) * (int16_t)(*alpha_addr++))) /
                  (1 << p->alpha->fp_pos);
      }
      ++o_addr;
    }

    // Bias
    if (p->bias) {
      int8_t *bias = (int8_t *)(p->bias->data);
      for (i = 0; i < p->output_loop_size; i++) {
        int opos = output_offset + i;
        int bpos = i;
        sum_acc_sat8(output + opos, *(bias + bpos));
      }
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}