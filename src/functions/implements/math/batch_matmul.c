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

#include "../../utilities/shape.h"
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

  batch_matmul_local_context_t *context =
      (batch_matmul_local_context_t *)(f->local_context);
  batch_matmul_private_t *private = malloc(sizeof(batch_matmul_private_t));
  if (private == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  ((batch_matmul_local_context_t *)(f->local_context))->data = (void *)private;
private
  ->row_a = f->inputs[0]->shape.data[f->inputs[0]->shape.size - 2];
private
  ->col_a = f->inputs[0]->shape.data[f->inputs[0]->shape.size - 1];
private
  ->row_b = f->inputs[1]->shape.data[f->inputs[1]->shape.size - 2];
private
  ->col_b = f->inputs[1]->shape.data[f->inputs[1]->shape.size - 1];
private
  ->row_y = context->transpose_a ? private->col_a : private->row_a;
private
  ->col_y = context->transpose_b ? private->row_b : private->col_b;
private
  ->offset_a = private->row_a * private->col_a;
private
  ->offset_b = private->row_b * private->col_b;
private
  ->offset_y = private->row_y * private->col_y;

private
  ->input_a = (float *)f->inputs[0]->data;
private
  ->input_b = (float *)f->inputs[1]->data;

private
  ->samples = 1;
  for (int i = 0; i < f->inputs[0]->shape.size - 2; ++i) {
  private
    ->samples *= f->inputs[0]->shape.data[i];
  }

  int samples_b = 1;
  for (int j = 0; j < f->inputs[1]->shape.size - 2; ++j) {
    samples_b *= f->inputs[1]->shape.data[j];
  }

private
  ->output = (float *)f->outputs[0]->data;
private
  ->output_size = calc_shape_size(f->outputs[0]->shape);

  if (private->output_size != private->row_y * private->col_y ||
      private->col_a != private->row_b || private->samples != samples_b) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }

  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_batch_matmul_local_context(rt_function_t *f) {
  free(((batch_matmul_local_context_t *)(f->local_context))->data);
  return RT_FUNCTION_ERROR_NOERROR;
}

static int get_next(int i, int m, int n) { return (i % n) * m + i / n; }

static int get_pre(int i, int m, int n) { return (i % m) * n + i / m; }

static void move_data(float *mtx, int i, int m, int n) {
  float temp = mtx[i];
  int cur = i;
  int pre = get_pre(cur, m, n);
  while (pre != i) {
    mtx[cur] = mtx[pre];
    cur = pre;
    pre = get_pre(cur, m, n);
  }
  mtx[cur] = temp;
}

static void transpose(float *mtx, int m, int n) {
  for (int i = 0; i < m * n; i++) {
    int next = get_next(i, m, n);
    while (next > i)
      next = get_next(next, m, n);
    if (next == i)
      move_data(mtx, i, m, n);
  }
}

rt_function_error_t exec_batch_matmul(rt_function_t *f) {
  batch_matmul_local_context_t *context =
      (batch_matmul_local_context_t *)(f->local_context);
  batch_matmul_private_t *p = (batch_matmul_private_t *)(context->data);

  int i;
  if (context->transpose_a) {
    for (i = 0; i < p->samples; i++) {
      transpose(p->input_a + p->offset_a * i, p->row_a, p->col_a);
    }
    p->row_a = p->row_a ^ p->col_a;
    p->col_a = p->row_a ^ p->col_a;
    p->row_a = p->row_a ^ p->col_a;
  }
  if (context->transpose_b) {
    for (i = 0; i < p->samples; i++) {
      transpose(p->input_b + p->offset_b * i, p->row_b, p->col_b);
    }
    p->row_b = p->row_b ^ p->col_b;
    p->col_b = p->row_b ^ p->col_b;
    p->row_b = p->row_b ^ p->col_b;
  }
  for (i = 0; i < p->samples; i++) {
    float *mtx_y = p->output + p->offset_y * i;
    float *mtx_a = p->input_a + p->offset_a * i;
    float *mtx_b = p->input_b + p->offset_b * i;
    int row_a = p->row_a;
    int col_b = p->col_b;
    int col_a = p->col_a;
    for (int j = 0; j < row_a; j++) {
      for (int k = 0; k < col_b; k++) {
        for (int l = 0; l < col_a; l++) {
          float a = *(mtx_a + col_a * j + l);
          float b = *(mtx_b + col_b * l + k);
          *(mtx_y + col_b * j + k) += a * b;
        }
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
