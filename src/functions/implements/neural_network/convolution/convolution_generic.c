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

void var_free(var_t *var) {
  free_list(var->shape);
  free_list(var->stride);
}

static inline void var_setpos(var_t *var, int *pos, int size) {
  var->offset = var_calc_offset(var, pos, size);
}

static inline float var_get(var_t *var, nn_size_t offset) {
  return var->get(var->v, offset);
}

static inline void var_set(var_t *var, nn_size_t offset, float v) {
  return var->set(var->v, offset, v);
}

static inline void conv2d(var_t *out, var_t *in, var_t *ke, var_t *b,
                          rt_list_t pad, rt_list_t stride, rt_list_t dilation) {
  int ix, iy, ox, oy, kx, ky;
  int pad_y = pad.data[SPH];
  int pad_x = pad.data[SPW];
  int step_y = stride.data[SPH];
  int step_x = stride.data[SPW];
  int kh = ke->shape.data[KH];
  int kw = ke->shape.data[KW];
  int out_h = out->shape.data[H];
  int out_w = out->shape.data[W];
  int dx = dilation.data[SPW];
  int dy = dilation.data[SPH];
  int in_w = in->shape.data[W];
  int in_h = in->shape.data[H];

  for (iy = -pad_y, oy = 0; oy < out_h; ++oy, iy += step_y) {
    for (ix = -pad_x, ox = 0; ox < out_w; ++ox, ix += step_x) {
      float sum = 0.0f;
      for (ky = 0; ky < kh; ++ky) {
        for (kx = 0; kx < kw; ++kx) {
          int iky = ky * dy + iy;
          int ikx = kx * dx + ix;
          if (ikx >= 0 && ikx < in_w && iky >= 0 && iky < in_h) {
            float x = var_get(in, in->offset + iky * in_w + ikx);
            float w = var_get(ke, ke->offset + kw * ky + kx);
            sum += x * w;
          }
        }
      }
      float o = var_get(out, out->offset + oy * out_w + ox);
      o += sum;
      var_set(out, out->offset + oy * out_w + ox, o);
    }
  }
}

static inline void add_bias(var_t *out, var_t *b) {
  int size = out->stride.data[I];
  int i;
  float bias = var_get(b, b->offset);
  for (i = 0; i < size; ++i) {
    float x = var_get(out, out->offset + i);
    x += bias;
    var_set(out, out->offset + i, x);
  }
}

static inline void mul_alpha(var_t* out, var_t* a) {
  int size = out->stride.data[I];
  int i;
  float alpha = var_get(a, a->offset);
  for (i = 0; i < size; ++i) {
    float x = var_get(out, out->offset + i);
    x *= alpha;
    var_set(out, out->offset + i, x);
  }
}

rt_function_error_t exec_convolution_generic(rt_function_t *f) {
  convolution_local_context_t *c =
      (convolution_local_context_t *)f->local_context;
  convolution_private_t *p = (convolution_private_t *)(c->data);

  nn_size_t group = c->group;
  nn_size_t in_vars = p->in_var.shape.data[I];
  nn_size_t out_vars = p->out_var.shape.data[I];
  nn_size_t batch_size;
  nn_size_t om, im, g, b;
  var_t* out_var = &p->out_var;
  var_t* in_var = &p->in_var;
  var_t* w_var = &p->w_var;
  var_t* b_var = &p->b_var;
  var_t* a_var = &p->a_var;

  batch_size = p->in_var.shape.data[0];
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
          conv2d(out_var, in_var, w_var, b_var, c->pad, c->stride, c->dilation);
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

  return RT_FUNCTION_ERROR_NOERROR;
}
