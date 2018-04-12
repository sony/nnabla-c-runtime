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

#include "../../utilities.h"
#include <nnablart/functions.h>
#include <stdio.h>

typedef struct {
  int samples;
  int col_a;
  int row_a;
  int col_b;
  int row_b;
  int col_y;
  int row_y;
  int offset_a;
  int offset_b;
  int offset_y;
  float *input_a;
  float *input_b;
  float *output;
  int output_size;
} batch_matmul_private_t;

// BatchMatmul
rt_function_error_t allocate_batch_matmul_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 2) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  batch_matmul_local_context_t *context = (batch_matmul_local_context_t *)(f->local_context);
  batch_matmul_private_t *private = malloc(sizeof(batch_matmul_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  ((batch_matmul_local_context_t *)(f->local_context))->private = (void *)private;
  private->row_a = f->inputs[0]->shape.data[f->inputs[0]->shape.size-2];
  private->col_a = f->inputs[0]->shape.data[f->inputs[0]->shape.size-1];
  private->row_b = f->inputs[1]->shape.data[f->inputs[1]->shape.size-2];
  private->col_b = f->inputs[1]->shape.data[f->inputs[1]->shape.size-1];
  private->row_y = context->transpose_a ? private->col_a : private->row_a;
  private->col_y = context->transpose_b ? private->row_b : private->col_b;
  private->offset_a = private->row_a * private->col_a;
  private->offset_b = private->row_b * private->col_b;
  private->offset_y = private->row_y * private->col_y;

  private->input_a = (float *)f->inputs[0]->data;
  private->input_b = (float *)f->inputs[1]->data;

  private->samples = 1;
  for (int i = 0; i < f->inputs[0]->shape.size - 2; ++i) {
    private->samples *= f->inputs[0]->shape.data[i];
  }

  int samples_b = 1;
  for (int j = 0; j < f->inputs[1]->shape.size - 2; ++j) {
    samples_b *= f->inputs[1]->shape.data[j];
  }

  private->output = (float *)f->outputs[0]->data;
  private->output_size = calc_shape_size(f->outputs[0]->shape);

  if (private->output_size != private->row_y * private->col_y ||
      private->col_a != private->row_b || private->samples != samples_b) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_batch_matmul_local_context(rt_function_t *f) {
  free(((batch_matmul_local_context_t *)(f->local_context))->private);
  return RT_FUNCTION_ERROR_NOERROR;
}

static int getNext(int i, int m, int n)
{
  return (i%n)*m + i / n;
}

static int getPre(int i, int m, int n)
{
  return (i%m)*n + i / m;
}

static void movedata(float *mtx, int i, int m, int n)
{
  float temp = mtx[i];
  int cur = i;
  int pre = getPre(cur, m, n);
  while (pre != i) {
    mtx[cur] = mtx[pre];
    cur = pre;
    pre = getPre(cur, m, n);
  }
  mtx[cur] = temp;
}

static void transpose(float *mtx, int m, int n)
{
  for (int i = 0; i < m * n; i++) {
    int next = getNext(i, m, n);
    while (next > i)
      next = getNext(next, m, n);
    if (next == i)
      movedata(mtx, i, m, n);
  }
}

static void matrix_multiply(float *mtx_y, float *mtx_a, float *mtx_b, int row_a, int col_b, int col_a)
{
  for (int i = 0; i < row_a; i++) {
    for (int j = 0; j < col_b; j++) {
      for (int k = 0; k < col_a; k++) {
        float a = *(mtx_a + col_a * i + k);
        float b = *(mtx_b + col_b * k + j);
        *(mtx_y + col_b * i + j) += a * b;
      }
    }
  }
}

rt_function_error_t exec_batch_matmul(rt_function_t *f) {
  batch_matmul_local_context_t *context = (batch_matmul_local_context_t *)(f->local_context);
  batch_matmul_private_t *private = (batch_matmul_private_t *)(context->private);

  int i;
  if (context->transpose_a) {
    for(i = 0; i < private->samples; i++) {
      transpose(private->input_a + private->offset_a * i, private->row_a, private->col_a);
    }
    private->row_a = private->row_a ^ private->col_a;
    private->col_a = private->row_a ^ private->col_a;
    private->row_a = private->row_a ^ private->col_a;
  }
  if (context->transpose_b) {
    for(i = 0; i < private->samples; i++) {
      transpose(private->input_b + private->offset_b * i, private->row_b, private->col_b);
    }
    private->row_b = private->row_b ^ private->col_b;
    private->col_b = private->row_b ^ private->col_b;
    private->row_b = private->row_b ^ private->col_b;
  }
  for (i = 0; i < private->samples; i++) {
    matrix_multiply(private->output + private->offset_y * i, private->input_a + private->offset_a * i,
                    private->input_b + private->offset_b * i, private->row_a, private->col_b, private->col_a);
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
