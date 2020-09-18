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
#include "../../../utilities/shape.h"
#include "convolution_internal.h"
#include <assert.h>
#include <math.h>
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_DEPTHWISECONVOLUTION

rt_function_error_t
allocate_depthwise_convolution_local_context(rt_function_t *f) {
  const int bias = 2;
  const int x = 0;
  const int weight = 1;
  const int y0 = 0;
  depthwise_convolution_local_context_t *c =
      (depthwise_convolution_local_context_t *)(f->local_context);
  int i;
  int multiplier = c->multiplier;
  int group;

  if (f->num_of_inputs != bias && f->num_of_inputs != bias + 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  rt_list_t in_shape = f->inputs[x]->shape;
  rt_list_t w_shape = f->inputs[weight]->shape;
  int spatial_dims = in_shape.size - c->base_axis - 1;

  if (c->base_axis >= in_shape.size - 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  convolution_private_t *p = rt_malloc_func(sizeof(convolution_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  c->data = (void *)p;

  p->in_var.shape = allocate_list(spatial_dims + 3);
  p->in_var.shape.data[B] = 1;
  for (i = 0; i < c->base_axis; ++i) {
    p->in_var.shape.data[B] *= in_shape.data[i];
  }
  p->in_var.shape.data[G] = in_shape.data[c->base_axis];
  p->in_var.shape.data[I] = 1;
  // Potential Issue: <to avoid duplicated convolution codes>
  // c->multiplier is used as c->group.
  group = c->multiplier = in_shape.data[c->base_axis];

  p->out_var.shape = allocate_list(spatial_dims + 3);
  p->out_var.shape.data[B] = p->in_var.shape.data[B];
  p->out_var.shape.data[G] = group;
  p->out_var.shape.data[I] = multiplier;

  for (i = 0; i < spatial_dims; ++i) {
    int k = w_shape.data[i + 1];
    int dims = p->in_var.shape.data[i + 3] =
        in_shape.data[c->base_axis + 1 + i];
    int ks = c->dilation.data[i] * (k - 1) + 1;
    int o = (dims + 2 * c->pad.data[i] - ks) / c->stride.data[i] + 1;
    p->out_var.shape.data[i + 3] = o;
  }
  p->in_var.v = f->inputs[x];
  p->in_var.get = select_getter(f->inputs[x]);
  p->in_var.offset = 0;
  p->in_var.stride = calc_contiguous_strides(p->in_var.shape);
  p->out_var.v = f->outputs[y0];
  p->out_var.get = select_getter(f->outputs[y0]);
  p->out_var.set = select_setter(f->outputs[y0]);
  p->out_var.offset = 0;
  p->out_var.stride = calc_contiguous_strides(p->out_var.shape);

  p->w_var.v = f->inputs[weight];
  p->w_var.get = select_getter(f->inputs[weight]);
  p->w_var.offset = 0;
  p->w_var.shape = allocate_list(spatial_dims + 3);
  p->w_var.shape.data[KG] = group;
  p->w_var.shape.data[KO] = multiplier;
  p->w_var.shape.data[KI] = 1;
  for (i = 0; i < spatial_dims; i++) {
    p->w_var.shape.data[i + 3] = w_shape.data[i + 1];
  }
  p->w_var.stride = calc_contiguous_strides(p->w_var.shape);

  if (f->num_of_inputs > bias) {
    p->b_var.v = f->inputs[bias];
    p->b_var.get = select_getter(f->inputs[bias]);
    p->b_var.offset = 0;
    p->b_var.shape = allocate_list(2);
    p->b_var.shape.data[KG] = group;
    p->b_var.shape.data[KO] = multiplier;
    p->b_var.stride = calc_contiguous_strides(p->b_var.shape);
  } else {
    p->b_var.v = 0;
  }

  p->a_var.v = 0;
  p->spatial_dims = spatial_dims;
  p->input_shape = allocate_list(p->spatial_dims);
  p->kernel_shape = allocate_list(p->spatial_dims);
  p->output_shape = allocate_list(p->spatial_dims);
  p->in_position = allocate_list(p->spatial_dims);
  p->out_position = allocate_list(p->spatial_dims);

  for (i = 0; i < p->spatial_dims; i++) {
    p->kernel_shape.data[i] = p->w_var.shape.data[i + 3];
    p->input_shape.data[i] = p->in_var.shape.data[i + 3];
    p->output_shape.data[i] = p->out_var.shape.data[i + 3];
  }

#ifdef CONFIG_DEPTHWISECONVOLUTION_FLOAT32
  f->exec_func = exec_depthwise_convolution;
#endif /* CONFIG_DEPTHWISECONVOLUTION_FLOAT32 */

#ifdef CONFIG_DEPTHWISECONVOLUTION_GENERIC
  for (int i = 0; i < f->num_of_inputs; i++) {

#ifdef CONFIG_DEPTHWISECONVOLUTION_FIXED8
    if (f->inputs[i]->type == NN_DATA_TYPE_INT8) {
      f->exec_func = exec_convolution_int8;
      break;
    }
#endif /* CONFIG_DEPTHWISECONVOLUTION_FIXED8 */

#ifdef CONFIG_DEPTHWISECONVOLUTION_FIXED16
    if (f->inputs[i]->type == NN_DATA_TYPE_INT16) {
      f->exec_func = exec_convolution_int16;
      break;
    }
#endif /* CONFIG_DEPTHWISECONVOLUTION_FIXED16 */

    if (f->inputs[i]->type != NN_DATA_TYPE_FLOAT) {
      f->exec_func = exec_convolution_generic;
      break;
    }
  }

  for (int i = 0; i < f->num_of_outputs; i++) {
    int conv_output_assigned = 0;

#ifdef CONFIG_DEPTHWISECONVOLUTION_FIXED8
    if ((f->outputs[i]->type == NN_DATA_TYPE_INT8) &&
        (f->exec_func == exec_convolution_int8)) {
      f->exec_func = exec_convolution_int8;
      conv_output_assigned = 1;
      break;
    }
#endif /* CONFIG_DEPTHWISECONVOLUTION_FIXED8 */

#ifdef CONFIG_DEPTHWISECONVOLUTION_FIXED16
    if ((f->outputs[i]->type == NN_DATA_TYPE_INT16) &&
        (f->exec_func == exec_convolution_int16)) {
      f->exec_func = exec_convolution_int16;
      conv_output_assigned = 1;
      break;
    }
#endif /* CONFIG_DEPTHWISECONVOLUTION_FIXED16 */

#ifdef CONFIG_DEPTHWISECONVOLUTION_FLOAT32
    if ((f->outputs[i]->type == NN_DATA_TYPE_FLOAT) &&
        (f->exec_func == exec_convolution_float)) {
      f->exec_func = exec_convolution_float;
      conv_output_assigned = 1;
      break;
    }
#endif /* CONFIG_DEPTHWISECONVOLUTION_FLOAT32 */

    if (!conv_output_assigned) {
      f->exec_func = exec_convolution_generic;
    }
  }
#endif /* CONFIG_DEPTHWISECONVOLUTION_GENERIC */

  c->multiplier = group;

  return RT_FUNCTION_ERROR_NOERROR;
}

static inline void var_free(var_t *var) {
  free_list(var->shape);
  free_list(var->stride);
}

rt_function_error_t free_depthwise_convolution_local_context(rt_function_t *f) {
  depthwise_convolution_local_context_t *c =
      (depthwise_convolution_local_context_t *)(f->local_context);
  convolution_private_t *p = (convolution_private_t *)c->data;
  var_free(&p->out_var);
  var_free(&p->in_var);
  var_free(&p->w_var);
  if (p->b_var.v != 0)
    var_free(&p->b_var);
  if (p->a_var.v != 0)
    var_free(&p->a_var);
  free_list(p->input_shape);
  free_list(p->kernel_shape);
  free_list(p->in_position);
  free_list(p->out_position);
  free_list(p->output_shape);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_DEPTHWISECONVOLUTION_FLOAT32
rt_function_error_t exec_depthwise_convolution(rt_function_t *f) {
  return exec_convolution_float(f);
}
#endif /* CONFIG_DEPTHWISECONVOLUTION_FLOAT32 */

#endif /* CONFIG_DEPTHWISECONVOLUTION */
