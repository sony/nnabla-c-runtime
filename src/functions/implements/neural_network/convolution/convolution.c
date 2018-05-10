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

// Convolution
rt_function_error_t allocate_convolution_local_context(rt_function_t *f) {
  convolution_local_context_t *c =
      (convolution_local_context_t *)(f->local_context);
  int i;

  if (f->num_of_inputs != 2 && f->num_of_inputs != 3) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  rt_list_t in_shape = f->inputs[0]->shape;
  rt_list_t w_shape = f->inputs[1]->shape;
  int spatial_dims = in_shape.size - c->base_axis - 1;

  if (c->base_axis >= in_shape.size - 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  convolution_private_t *p = malloc(sizeof(convolution_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  c->data = (void *)p;

  if (in_shape.data[c->base_axis] % c->group != 0) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  p->in_var.shape = allocate_list(spatial_dims + 3);
  p->in_var.shape.data[B] = 1;
  for (i = 0; i < c->base_axis; ++i) {
    p->in_var.shape.data[B] *= in_shape.data[i];
  }
  p->in_var.shape.data[G] = c->group;
  p->in_var.shape.data[I] = in_shape.data[c->base_axis] / c->group;

  p->out_var.shape = allocate_list(spatial_dims + 3);
  p->out_var.shape.data[B] = p->in_var.shape.data[B];
  p->out_var.shape.data[G] = c->group;
  p->out_var.shape.data[I] = w_shape.data[0] / c->group;

  for (i = 0; i < spatial_dims; ++i) {
    int k = w_shape.data[i + 2];
    int dims = p->in_var.shape.data[i + 3] =
        in_shape.data[c->base_axis + 1 + i];
    int ks = c->dilation.data[i] * (k - 1) + 1;
    int o = (dims + 2 * c->pad.data[i] - ks) / c->stride.data[i] + 1;
    p->out_var.shape.data[i + 3] = o;
  }
  p->in_var.v = f->inputs[0];
  p->in_var.get = select_getter(f->inputs[0]);
  p->in_var.offset = 0;
  p->in_var.stride = calc_contiguous_strides(p->in_var.shape);
  p->out_var.v = f->outputs[0];
  p->out_var.get = select_getter(f->outputs[0]);
  p->out_var.set = select_setter(f->outputs[0]);
  p->out_var.offset = 0;
  p->out_var.stride = calc_contiguous_strides(p->out_var.shape);

  p->w_var.v = f->inputs[1];
  p->w_var.get = select_getter(f->inputs[1]);
  p->w_var.offset = 0;
  p->w_var.shape = allocate_list(spatial_dims + 3);
  p->w_var.shape.data[KG] = c->group;
  p->w_var.shape.data[KO] = w_shape.data[0] / c->group;
  p->w_var.shape.data[KI] = w_shape.data[1];
  p->w_var.shape.data[KH] = w_shape.data[2];
  p->w_var.shape.data[KW] = w_shape.data[3];
  p->w_var.stride = calc_contiguous_strides(p->w_var.shape);

  if (f->num_of_inputs > 2) {
    p->b_var.v = f->inputs[2];
    p->b_var.get = select_getter(f->inputs[2]);
    p->b_var.offset = 0;
    p->b_var.shape = allocate_list(2);
    p->b_var.shape.data[KG] = c->group;
    p->b_var.shape.data[KO] = f->inputs[2]->shape.data[0] / c->group;
    p->b_var.stride = calc_contiguous_strides(p->b_var.shape);
  } else {
    p->b_var.v = 0;
  }

  p->exec =
      exec_convolution_generic; // currently, we only implement a generic one

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_convolution_local_context(rt_function_t *f) {
  convolution_local_context_t *c =
      (convolution_local_context_t *)(f->local_context);
  convolution_private_t *p = (convolution_private_t *)c->data;
  var_free(&p->out_var);
  var_free(&p->in_var);
  var_free(&p->w_var);
  var_free(&p->b_var);
  free(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_convolution(rt_function_t *f) {
  return ((convolution_private_t
               *)(((convolution_local_context_t *)(f->local_context))->data))
      ->exec(f);
}
