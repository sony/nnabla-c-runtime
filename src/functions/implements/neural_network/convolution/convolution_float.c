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

#include "../../../utilities/list.h"
#include "../../../utilities/shape.h"

#include <assert.h>
#include <math.h>
#include <nnablart/functions.h>
#include <string.h>

#define _S(p) (sizeof(p) / sizeof(p[0]))

/*
 * group (g) [default 1]: If g > 1, we restrict the connectivity of each filter
 * to a subset of the input. Specifically, the input and output channels are
 * separated into g groups, and the i-th output group channels will be only
 * connected  to the i-th input group channels.
 */
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
  float *output = (float *)(out->v->data);
  float *input = (float *)(in->v->data);
  float *weight = (float *)(we->v->data);
  int output_size = calc_shape_size(output_shape);
  int kernel_size = calc_shape_size(kernel_shape);

  for (int o = 0; o < output_size; o++) {
    float sum = 0.0f;
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
        float x =
            *(input + in->offset + shape_to_pos(input_shape, in_position));
        float w = *(weight + we->offset + k);
        sum += x * w;
      }
    }
    *(output + out->offset + o) += sum;
  }
}

static inline void conv2d(var_t *out, var_t *in, var_t *we,
                          rt_list_t input_shape, rt_list_t output_shape,
                          rt_list_t kernel_shape, rt_list_t in_position,
                          rt_list_t out_position, rt_list_t pad,
                          rt_list_t stride, rt_list_t dilation,
                          int spatial_dims) {
  float *output = (float *)(out->v->data);
  float *input = (float *)(in->v->data);
  float *weight = (float *)(we->v->data);
  int ix, iy, ox, oy, kx, ky;

  for (iy = -pad.data[0], oy = 0; oy < output_shape.data[0];
       ++oy, iy += stride.data[0]) {
    for (ix = -pad.data[1], ox = 0; ox < output_shape.data[1];
         ++ox, ix += stride.data[1]) {
      float sum = 0.0f;
      for (ky = 0; ky < kernel_shape.data[0]; ++ky) {
        for (kx = 0; kx < kernel_shape.data[1]; ++kx) {
          int iky = ky * dilation.data[0] + iy;
          int ikx = kx * dilation.data[1] + ix;
          if (ikx >= 0 && ikx < input_shape.data[1] && iky >= 0 &&
              iky < input_shape.data[0]) {
            float x = *(input + in->offset + iky * input_shape.data[1] + ikx);
            float w = *(weight + we->offset + ky * kernel_shape.data[1] + kx);
            sum += x * w;
          }
        }
      }
      float o = *(output + out->offset + oy * output_shape.data[1] + ox);
      o += sum;
      *(output + out->offset + oy * output_shape.data[1] + ox) = o;
    }
  }
}

static inline void add_bias(var_t *out, var_t *b) {
  int size = out->stride.data[I];
  int i;
  float *bias = (float *)(b->v->data);
  float *output = (float *)(out->v->data);
  for (i = 0; i < size; ++i) {
    *(output + out->offset + i) += *(bias + b->offset);
  }
}

static inline void mul_alpha(var_t *out, var_t *a) {
  int size = out->stride.data[I];
  int i;
  float *alpha = (float *)(a->v->data);
  float *output = (float *)(out->v->data);
  for (i = 0; i < size; ++i) {
    *(output + out->offset + i) *= *(alpha + a->offset);
  }
}

rt_function_error_t exec_convolution_float(rt_function_t *f) {
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

  int output_size = calc_shape_size(p->out_var.shape);

  memset(out_var->v->data, 0, sizeof(float) * output_size);

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
