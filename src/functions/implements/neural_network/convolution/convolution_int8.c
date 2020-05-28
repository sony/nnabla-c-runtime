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

#include "../../../utilities/fixedpoint.h"
#include "../../../utilities/list.h"
#include "../../../utilities/shape.h"

#include <assert.h>
#include <math.h>
#include <nnablart/functions.h>
#include <stdint.h>
#include <string.h>

#define _S(p) (sizeof(p) / sizeof(p[0]))

static inline nn_size_t var_calc_offset(var_t *var, int *pos, int size) {
  int *s = var->stride.data;
  int len = var->stride.size > size ? size : var->stride.size;
  int i, offset = 0;

  for (i = 0; i < len; ++i) {
    offset += (*pos++) * (*s++);
  }
  return offset;
}

static inline void var_setpos(var_t *var, int *pos, int size) {
  var->offset = var_calc_offset(var, pos, size);
}

static inline void convnd(var_t *out, var_t *in, var_t *we,
                          rt_list_t input_shape, rt_list_t output_shape,
                          rt_list_t kernel_shape, rt_list_t in_position,
                          rt_list_t out_position, rt_list_t pad,
                          rt_list_t stride, rt_list_t dilation,
                          int spatial_dims) {

  int8_t *output = (int8_t *)(out->v->data);
  int8_t *input = (int8_t *)(in->v->data);
  int8_t *weight = (int8_t *)(we->v->data);

  const unsigned output_size = calc_shape_size(output_shape);
  const unsigned kernel_size = calc_shape_size(kernel_shape);
  const unsigned short nbits_rescale =
      in->v->fp_pos + we->v->fp_pos - out->v->fp_pos;

  for (int o = 0; o < output_size; o++) {
    int32_t sum = 0;
    pos_to_shape(out_position, output_shape, o);
    for (int k = 0; k < kernel_size; k++) {
      pos_to_shape(in_position, kernel_shape, k);
      uint8_t condition = 1;
      for (int j = 0; j < spatial_dims; j++) {
        in_position.data[j] *= dilation.data[j];
        in_position.data[j] -= pad.data[j];
        in_position.data[j] += out_position.data[j] * stride.data[j];
        if (in_position.data[j] < 0 ||
            in_position.data[j] >= input_shape.data[j]) {
          condition = 0;
          break;
        }
      }
      if (condition) {
        int8_t *x_addr =
            (input + in->offset + shape_to_pos(input_shape, in_position));
        int8_t *w_addr = (weight + we->offset + k);
        sum += (*x_addr) * (*w_addr);
      }
    }
    // Rescale accumulator variable SUM so that it has the same number of
    // fractional bits as OUT. Saturate and downscale to 8 bit.
    *(output + out->offset + o) = saturate32_to_8(*(output + out->offset + o) +
                                                  sum / (1 << nbits_rescale));
  }
}

static inline void conv2d(var_t *out, var_t *in, var_t *we,
                          rt_list_t input_shape, rt_list_t output_shape,
                          rt_list_t kernel_shape, rt_list_t in_position,
                          rt_list_t out_position, rt_list_t pad,
                          rt_list_t stride, rt_list_t dilation,
                          int spatial_dims) {

  int ix, iy, ox, oy, kx, ky;

  int8_t *output_int = (int8_t *)(out->v->data);
  int8_t *input_int = (int8_t *)(in->v->data);
  int8_t *weight_int = (int8_t *)(we->v->data);

  const unsigned nbits_rescale = in->v->fp_pos + we->v->fp_pos - out->v->fp_pos;

  for (iy = -pad.data[0], oy = 0; oy < output_shape.data[0];
       ++oy, iy += stride.data[0]) {
    for (ix = -pad.data[1], ox = 0; ox < output_shape.data[1];
         ++ox, ix += stride.data[1]) {
      int32_t sum = 0;
      for (ky = 0; ky < kernel_shape.data[0]; ++ky) {
        for (kx = 0; kx < kernel_shape.data[1]; ++kx) {
          int iky = ky * dilation.data[0] + iy;
          int ikx = kx * dilation.data[1] + ix;
          if (ikx >= 0 && ikx < input_shape.data[1] && iky >= 0 &&
              iky < input_shape.data[0]) {
            int8_t *x_addr =
                (input_int + in->offset + iky * input_shape.data[1] + ikx);
            int8_t *w_addr =
                (weight_int + we->offset + ky * kernel_shape.data[1] + kx);
            sum += (*x_addr) * (*w_addr);
          }
        }
      }
      // Rescale accumulator variable SUM so that it has the same number of
      // fractional bits as OUT. Saturate and downscale to 8 bit.
      *(output_int + out->offset + oy * output_shape.data[1] + ox) =
          saturate32_to_8(
              *(output_int + out->offset + oy * output_shape.data[1] + ox) +
              sum / (1 << nbits_rescale));
    }
  }
}

static inline void add_bias(var_t *out, var_t *b) {
  int size = out->stride.data[I];
  int i;
  int8_t *bias = (int8_t *)(b->v->data);
  int8_t *output = (int8_t *)(out->v->data);

  for (i = 0; i < size; ++i) {
    sum_acc_sat8(output + out->offset + i, *(bias + b->offset));
  }
}

static inline void mul_alpha(var_t *out, var_t *a) {
  int size = out->stride.data[I];
  int i;
  int8_t *alpha = (int8_t *)(a->v->data);
  int8_t *output = (int8_t *)(out->v->data);

  // Rescale variable so that it has the same number of
  // fractional bits as OUT
  // simplified version of: a->v->fp_pos + out->v->fp_pos - out->v->fp_pos;
  const unsigned short nbits_rescale = a->v->fp_pos;

  for (i = 0; i < size; ++i) {
    int8_t ap = *(alpha + a->offset);
    int8_t op = *(output + out->offset + i);
    *(output + out->offset + i) =
        (((int16_t)(op) * (int16_t)(ap))) / (1 << nbits_rescale);
  }
}

rt_function_error_t exec_convolution_int8(rt_function_t *f) {
  convolution_local_context_t *c =
      (convolution_local_context_t *)f->local_context;
  convolution_private_t *p = (convolution_private_t *)(c->data);

  nn_size_t group = c->group;
  nn_size_t in_vars = p->in_var.shape.data[I];
  nn_size_t out_vars = p->out_var.shape.data[I];
  nn_size_t batch_size;
  nn_size_t om, im, g, b;

  var_t *out_var = &p->out_var;
  var_t *in_var = &p->in_var;
  var_t *w_var = &p->w_var;
  var_t *b_var = &p->b_var;
  var_t *a_var = &p->a_var;

  const unsigned output_size = calc_shape_size(out_var->shape);
  const unsigned bias_size = calc_shape_size(b_var->shape);

  if (p->b_var.v) {
    unsigned int b_fp = b_var->v->fp_pos;
    unsigned int out_fp = out_var->v->fp_pos;

    // If bias has less range bits (=more precision bits) than output, rescale
    // bias.
    // Otherwise, output has too few range bits. Change format before starting
    // computations.
    if (b_fp > out_fp) {
      int i;
      int8_t *b_data = (int8_t *)(b_var->v->data);
      for (i = 0; i < bias_size; i++) {
        *(b_data + i) /= (1 << (b_fp - out_fp));
      }
    } else if (b_fp < out_fp) {
      printf(
          "OUTPUT variable has less range bits than BIAS variable. Please "
          "make sure conv/b has same or less range bits than Output to avoid "
          "overflow.\n");
      return RT_FUNCTION_ERROR_UNIMPLEMENTED;
    }
  }

  memset(out_var->v->data, 0, sizeof(int8_t) * output_size);

  batch_size = p->in_var.shape.data[0];
  if (p->spatial_dims == 2) {
    for (b = 0; b < batch_size; ++b) {
      for (g = 0; g < group; ++g) {
        for (om = 0; om < out_vars; ++om) {
          int o_pos[] = {b, g, om};
          var_setpos(out_var, o_pos, _S(o_pos));
          for (im = 0; im < in_vars; ++im) {
            int i_pos[] = {b, g, im};
            int w_pos[] = {g, om, im};
            var_setpos(in_var, i_pos, _S(i_pos));
            var_setpos(w_var, w_pos, _S(w_pos));
            conv2d(out_var, in_var, w_var, p->input_shape, p->output_shape,
                   p->kernel_shape, p->in_position, p->out_position, c->pad,
                   c->stride, c->dilation, p->spatial_dims);
          }
          {
            int b_pos[] = {g, om};
            if (p->a_var.v) {
              var_setpos(a_var, b_pos, _S(b_pos));
              mul_alpha(out_var, a_var);
            }
            if (p->b_var.v) {
              var_setpos(b_var, b_pos, _S(b_pos));
              add_bias(out_var, b_var);
            }
          }
        }
      }
    }
  } else {
    for (b = 0; b < batch_size; ++b) {
      for (g = 0; g < group; ++g) {
        for (om = 0; om < out_vars; ++om) {
          int o_pos[] = {b, g, om};
          var_setpos(out_var, o_pos, _S(o_pos));
          for (im = 0; im < in_vars; ++im) {
            int i_pos[] = {b, g, im};
            int w_pos[] = {g, om, im};
            var_setpos(in_var, i_pos, _S(i_pos));
            var_setpos(w_var, w_pos, _S(w_pos));
            convnd(out_var, in_var, w_var, p->input_shape, p->output_shape,
                   p->kernel_shape, p->in_position, p->out_position, c->pad,
                   c->stride, c->dilation, p->spatial_dims);
          }
          {
            int b_pos[] = {g, om};
            if (p->a_var.v) {
              var_setpos(a_var, b_pos, _S(b_pos));
              mul_alpha(out_var, a_var);
            }
            if (p->b_var.v) {
              var_setpos(b_var, b_pos, _S(b_pos));
              add_bias(out_var, b_var);
            }
          }
        }
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
