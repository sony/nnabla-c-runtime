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

#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <math.h>
#include <nnablart/functions.h>

typedef struct {
  rt_variable_t batch_mean;
  rt_variable_t batch_var;
  int batch_size;
  int specified_axis_size;
  int output_size;
  int multiplication_axis_output;
  int multiplication_batch_axis;
} batch_normalization_private_t;

rt_function_error_t exec_batch_normalization_generic(rt_function_t *f);

// BatchNormalization
rt_function_error_t
allocate_batch_normalization_local_context(rt_function_t *f) {
  batch_normalization_local_context_t *context =
      (batch_normalization_local_context_t *)(f->local_context);
  batch_normalization_private_t *p =
      rt_malloc_func(sizeof(batch_normalization_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  // Check axes
  if (context->axes.size != 1) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  // Check and parse shapes
  rt_list_t input_shape = clone_list(f->inputs[0]->shape);
  const int axis = context->axes.data[0];
  const int size = calc_shape_size(input_shape);
  const int size_axis =
      axis <= 0 ? size : shape_product_of(f->inputs[0], axis,
                                          f->inputs[0]->shape.size);
  p->batch_size = size / size_axis;
  p->specified_axis_size = input_shape.data[context->axes.data[0]];
  p->output_size = size / p->batch_size / p->specified_axis_size;
  p->multiplication_axis_output = p->specified_axis_size * p->output_size;
  p->multiplication_batch_axis = p->batch_size * p->output_size;
  if (p->batch_size * p->specified_axis_size * p->output_size != size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  p->batch_mean.shape = clone_list(f->inputs[1]->shape);
  p->batch_var.shape = clone_list(f->inputs[2]->shape);
  p->batch_mean.data =
      rt_malloc_func(sizeof(float) * calc_shape_size(p->batch_mean.shape));
  p->batch_var.data =
      rt_malloc_func(sizeof(float) * calc_shape_size(p->batch_var.shape));
  free_list(input_shape);
  ((batch_normalization_local_context_t *)(f->local_context))->data = (void *)p;

  f->exec_func = exec_batch_normalization;
  for (int i = 0; i < f->num_of_inputs; i++) {
    if (f->inputs[i]->type != NN_DATA_TYPE_FLOAT) {
      f->exec_func = exec_batch_normalization_generic;
      break;
    }
  }
  if (f->outputs[0]->type != NN_DATA_TYPE_FLOAT) {
    f->exec_func = exec_batch_normalization_generic;
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_batch_normalization_local_context(rt_function_t *f) {
  batch_normalization_private_t *p =
      (batch_normalization_private_t
           *)(((batch_normalization_local_context_t *)(f->local_context))
                  ->data);
  free_list(p->batch_mean.shape);
  free_list(p->batch_var.shape);
  rt_free_func(p->batch_mean.data);
  rt_free_func(p->batch_var.data);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void forward_impl_batch(rt_function_t *f,
                               batch_normalization_local_context_t *context,
                               batch_normalization_private_t *p) {
  const float *x = (float *)(f->inputs[0]->data);
  const float *beta = (float *)(f->inputs[1]->data);
  const float *gamma = (float *)(f->inputs[2]->data);
  float *y = (float *)(f->outputs[0]->data);
  float *m = (float *)p->batch_mean.data;    // batch mean
  float *v = (float *)p->batch_var.data;     // batch var
  float *rm = (float *)(f->inputs[3]->data); // running mean
  float *rv = (float *)(f->inputs[4]->data); // running var
  const int specified_axis_size = p->specified_axis_size;
  const int output_size = p->output_size;
  const int multiplication_axis_output = p->multiplication_axis_output;
  const int multiplication_batch_axis = p->multiplication_batch_axis;

  if (f->num_of_outputs == 3) {
    m = (float *)(f->outputs[1]->data);
    v = (float *)(f->outputs[2]->data);
  }

  int i1;
  for (i1 = 0; i1 < specified_axis_size; i1++) {
    m[i1] = 0;
    v[i1] = 0;
    int i02;
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      const float value = x[i];
      m[i1] += value;
      v[i1] += value * value;
    }
    m[i1] /= multiplication_batch_axis;
    v[i1] = v[i1] / multiplication_batch_axis - m[i1] * m[i1];

    // Moving mean and var
    rm[i1] = context->decay_rate * rm[i1] + (1 - context->decay_rate) * m[i1];
    rv[i1] = context->decay_rate * rv[i1] +
             (1 - context->decay_rate) * v[i1] * multiplication_batch_axis /
                 (multiplication_batch_axis - 1);

    const float stdvar = (float)sqrt(v[i1] + context->eps);
    // Subtract mean and divide by std, and apply beta and gamma.
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      y[i] = (x[i] - m[i1]) * gamma[i1] / stdvar + beta[i1];
    }
  }
}

static void
forward_impl_batch_generic(rt_function_t *f,
                           batch_normalization_local_context_t *context,
                           batch_normalization_private_t *p) {
  rt_variable_t *input_x = f->inputs[0];
  rt_variable_getter get_x = select_getter(input_x);
  rt_variable_t *input_beta = f->inputs[1];
  rt_variable_getter get_beta = select_getter(input_beta);
  rt_variable_t *input_gamma = f->inputs[2];
  rt_variable_getter get_gamma = select_getter(input_gamma);
  rt_variable_t *input_rm = f->inputs[3]; // running mean
  rt_variable_getter get_rm = select_getter(input_rm);
  rt_variable_setter set_rm = select_setter(input_rm);
  rt_variable_t *input_rv = f->inputs[4]; // running var
  rt_variable_getter get_rv = select_getter(input_rv);
  rt_variable_setter set_rv = select_setter(input_rv);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);
  float *m = (float *)p->batch_mean.data; // batch mean
  float *v = (float *)p->batch_var.data;  // batch var
  const int specified_axis_size = p->specified_axis_size;
  const int output_size = p->output_size;
  const int multiplication_axis_output = p->multiplication_axis_output;
  const int multiplication_batch_axis = p->multiplication_batch_axis;

  if (f->num_of_outputs == 3) {
    m = (float *)(f->outputs[1]->data);
    v = (float *)(f->outputs[2]->data);
  }

  int i1;
  for (i1 = 0; i1 < specified_axis_size; i1++) {
    m[i1] = 0;
    v[i1] = 0;
    int i02;
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      const float value = get_x(input_x, i);
      m[i1] += value;
      v[i1] += value * value;
    }
    m[i1] /= multiplication_batch_axis;
    v[i1] = v[i1] / multiplication_batch_axis - m[i1] * m[i1];

    // Moving mean and var
    float rm = get_rm(input_rm, i1);
    float rv = get_rv(input_rv, i1);
    rm = context->decay_rate * rm + (1 - context->decay_rate) * m[i1];
    rv = context->decay_rate * rv +
         (1 - context->decay_rate) * v[i1] * multiplication_batch_axis /
             (multiplication_batch_axis - 1);
    set_rm(input_rm, i1, rm);
    set_rv(input_rv, i1, rv);

    // Subtract mean and divide by std, and apply beta and gamma.
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      const float stdvar = (float)sqrt(v[i1] + context->eps);
      float x = get_x(input_x, i);
      float beta = get_beta(input_beta, i1);
      float gamma = get_gamma(input_gamma, i1);
      float y = (x - m[i1]) * gamma / stdvar + beta;
      set_output(output, i, y);
    }
  }
}

static void forward_impl_global(rt_function_t *f,
                                batch_normalization_local_context_t *context,
                                batch_normalization_private_t *p) {
  const float *x = (float *)(f->inputs[0]->data);
  const float *beta = (float *)(f->inputs[1]->data);
  const float *gamma = (float *)(f->inputs[2]->data);
  const float *rm = (float *)(f->inputs[3]->data); // running mean
  const float *rv = (float *)(f->inputs[4]->data); // running var
  float *y = (float *)(f->outputs[0]->data);
  const int specified_axis_size = p->specified_axis_size;
  const int output_size = p->output_size;
  const int multiplication_axis_output = p->multiplication_axis_output;
  const int multiplication_batch_axis = p->multiplication_batch_axis;

  // Subtract mean and divide by std, and apply beta and gamma.
  int i1;
  for (i1 = 0; i1 < specified_axis_size; i1++) {
    int i02;
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      const float mean = rm[i1];
      const float stdvar = (float)sqrt(rv[i1] + context->eps);
      y[i] = (x[i] - mean) * gamma[i1] / stdvar + beta[i1];
    }
  }
}

static void
forward_impl_global_generic(rt_function_t *f,
                            batch_normalization_local_context_t *context,
                            batch_normalization_private_t *p) {
  rt_variable_t *input_x = f->inputs[0];
  rt_variable_getter get_x = select_getter(input_x);
  rt_variable_t *input_beta = f->inputs[1];
  rt_variable_getter get_beta = select_getter(input_beta);
  rt_variable_t *input_gamma = f->inputs[2];
  rt_variable_getter get_gamma = select_getter(input_gamma);
  rt_variable_t *input_rm = f->inputs[3]; // running mean
  rt_variable_getter get_rm = select_getter(input_rm);
  rt_variable_t *input_rv = f->inputs[4]; // running var
  rt_variable_getter get_rv = select_getter(input_rv);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);
  const int specified_axis_size = p->specified_axis_size;
  const int output_size = p->output_size;
  const int multiplication_axis_output = p->multiplication_axis_output;
  const int multiplication_batch_axis = p->multiplication_batch_axis;

  // Subtract mean and divide by std, and apply beta and gamma.
  int i1;
  for (i1 = 0; i1 < specified_axis_size; i1++) {
    int i02;
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      float x = get_x(input_x, i);
      float rm = get_rm(input_rm, i1);
      float rv = get_rv(input_rv, i1);
      float gamma = get_gamma(input_gamma, i1);
      float beta = get_beta(input_beta, i1);
      const float stdvar = (float)sqrt(rv + context->eps);
      float y = (x - rm) * gamma / stdvar + beta;
      set_output(output, i, y);
    }
  }
}

rt_function_error_t exec_batch_normalization(rt_function_t *f) {
  batch_normalization_local_context_t *context =
      (batch_normalization_local_context_t *)(f->local_context);
  batch_normalization_private_t *p =
      (batch_normalization_private_t *)(context->data);

  if (context->batch_stat) {
    forward_impl_batch(f, context, p);
  } else {
    forward_impl_global(f, context, p);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_batch_normalization_generic(rt_function_t *f) {
  batch_normalization_local_context_t *context =
      (batch_normalization_local_context_t *)(f->local_context);
  batch_normalization_private_t *p =
      (batch_normalization_private_t *)(context->data);

  if (context->batch_stat) {
    forward_impl_batch_generic(f, context, p);
  } else {
    forward_impl_global_generic(f, context, p);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
