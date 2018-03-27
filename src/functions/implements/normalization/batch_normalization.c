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
#include <math.h>
#include "../../utilities.h"

typedef struct {
  rt_list_t batch_mean;
  rt_list_t batch_var;
  int batch_size;
  int specified_axis_size;
  int output_size;
  int multiplication_axis_output;
  int multiplication_batch_axis;
} batch_normalization_private_t;

// BatchNormalization
rt_function_error_t allocate_batch_normalization_local_context(rt_function_t *f) {
  batch_normalization_local_context_t *context = 
                    (batch_normalization_local_context_t *)(f->local_context);
  batch_normalization_private_t *private = 
                    malloc(sizeof(batch_normalization_private_t));
  if (private == 0) {
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
  private->batch_size = size / size_axis;
  private->specified_axis_size = input_shape.data[context->axes.data[0]];
  private->output_size = 
                    size / private->batch_size / private->specified_axis_size;
  private->multiplication_axis_output =
                    private->specified_axis_size * private->output_size;
  private->multiplication_batch_axis = 
                    private->batch_size * private->output_size;
  if (private->batch_size * private->specified_axis_size * 
                                      private->output_size != size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  private->batch_mean = clone_list(f->inputs[1]->shape);
  private->batch_var = clone_list(f->inputs[2]->shape);
  free_list(input_shape);
  ((batch_normalization_local_context_t *)(f->local_context))->private = 
                                                              (void *)private;

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_batch_normalization_local_context(rt_function_t *f) {
  batch_normalization_private_t *private =
      (batch_normalization_private_t *)(((batch_normalization_local_context_t *)
      (f->local_context))->private);
  free_list(private->batch_mean);
  free_list(private->batch_var);
  free(private);
  return RT_FUNCTION_ERROR_NOERROR;
}

static void forward_impl_batch(rt_function_t *f, 
                        batch_normalization_local_context_t *context,
                        batch_normalization_private_t *private) {
  const float *x = (float *)(f->inputs[0]->data);
  const float *beta = (float *)(f->inputs[1]->data);
  const float *gamma = (float *)(f->inputs[2]->data);
  float *y = (float *)(f->outputs[0]->data);
  float *m = (float *)private->batch_mean.data; // batch mean
  float *v = (float *)private->batch_var.data;  // batch varf
  float *rm = (float *)(f->inputs[3]->data);    // running mean
  float *rv = (float *)(f->inputs[4]->data);    // running var
  const int specified_axis_size = private->specified_axis_size;
  const int output_size = private->output_size;
  const int multiplication_axis_output = private->multiplication_axis_output;
  const int multiplication_batch_axis = private->multiplication_batch_axis;

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

    // Subtract mean and divide by std, and apply beta and gamma.
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      const float stdvar = sqrt(v[i1] + context->eps);
      y[i] = (x[i] - m[i1]) * gamma[i1] / stdvar + beta[i1];
    }
  }
}

static void forward_impl_global(rt_function_t *f, 
                        batch_normalization_local_context_t *context,
                        batch_normalization_private_t *private) {
  const float *x = (float *)(f->inputs[0]->data);
  const float *beta = (float *)(f->inputs[1]->data);
  const float *gamma = (float *)(f->inputs[2]->data);
  const float *rm = (float *)(f->inputs[3]->data); // running mean
  const float *rv = (float *)(f->inputs[4]->data); // running var
  float *y = (float *)(f->outputs[0]->data);
  const int specified_axis_size = private->specified_axis_size;
  const int output_size = private->output_size;
  const int multiplication_axis_output = private->multiplication_axis_output;
  const int multiplication_batch_axis = private->multiplication_batch_axis;

  // Subtract mean and divide by std, and apply beta and gamma.
  int i1;
  for (i1 = 0; i1 < specified_axis_size; i1++) {
    int i02;
    for (i02 = 0; i02 < multiplication_batch_axis; i02++) {
      const int i0 = i02 / output_size;
      const int i2 = i02 % output_size;
      const int i = i0 * multiplication_axis_output + i1 * output_size + i2;
      const float mean = rm[i1];
      const float stdvar = sqrt(rv[i1] + context->eps);
      y[i] = (x[i] - mean) * gamma[i1] / stdvar + beta[i1];
    }
  }
}

rt_function_error_t exec_batch_normalization(rt_function_t *f) {
  batch_normalization_local_context_t *context = 
                      (batch_normalization_local_context_t *)(f->local_context);
  batch_normalization_private_t *private = 
                      (batch_normalization_private_t *)(context->private);
  
  if (context->batch_stat) {
    forward_impl_batch(f, context, private);
  } else {
    forward_impl_global(f, context, private);
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
