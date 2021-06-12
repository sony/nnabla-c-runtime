// Copyright 2018,2019,2020,2021 Sony Corporation.
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

#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <nnablart/config.h>
#include <nnablart/functions.h>
#include <stdio.h>

#ifdef CONFIG_BATCHMATMUL

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
  rt_variable_t *input_a;
  rt_variable_getter get_input_a;
  rt_variable_t *input_b;
  rt_variable_getter get_input_b;
  rt_variable_t *output;
  rt_variable_getter get_output;
  rt_variable_setter set_output;
  int output_size;
} batch_matmul_private_t;

rt_function_error_t exec_batch_matmul_generic(rt_function_t *f);

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
  batch_matmul_private_t *p = rt_malloc_func(sizeof(batch_matmul_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  ((batch_matmul_local_context_t *)(f->local_context))->data = (void *)p;
  p->row_a = f->inputs[0]->shape.data[f->inputs[0]->shape.size - 2];
  p->col_a = f->inputs[0]->shape.data[f->inputs[0]->shape.size - 1];
  p->row_b = f->inputs[1]->shape.data[f->inputs[1]->shape.size - 2];
  p->col_b = f->inputs[1]->shape.data[f->inputs[1]->shape.size - 1];
  p->row_y = context->transpose_a ? p->col_a : p->row_a;
  p->col_y = context->transpose_b ? p->row_b : p->col_b;
  p->offset_a = p->row_a * p->col_a;
  p->offset_b = p->row_b * p->col_b;
  p->offset_y = p->row_y * p->col_y;

  p->input_a = f->inputs[0];
  p->get_input_a = select_getter(p->input_a);
  p->input_b = f->inputs[1];
  p->get_input_b = select_getter(p->input_b);

  p->samples = 1;
  for (int i = 0; i < f->inputs[0]->shape.size - 2; ++i) {
    p->samples *= f->inputs[0]->shape.data[i];
  }

  int samples_b = 1;
  for (int j = 0; j < f->inputs[1]->shape.size - 2; ++j) {
    samples_b *= f->inputs[1]->shape.data[j];
  }

  p->output = f->outputs[0];
  p->get_output = select_getter(p->output);
  p->set_output = select_setter(p->output);
  p->output_size = calc_shape_size(f->outputs[0]->shape);

  if (p->samples != samples_b) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (p->input_a->type == NN_DATA_TYPE_FLOAT &&
      p->input_b->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_BATCHMATMUL_FLOAT32
    f->exec_func = exec_batch_matmul;
#endif /* CONFIG_BATCHMATMUL_FLOAT32 */
  } else {
#ifdef CONFIG_BATCHMATMUL_GENERIC
    f->exec_func = exec_batch_matmul_generic;
#endif /* CONFIG_BATCHMATMUL_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_batch_matmul_local_context(rt_function_t *f) {
  rt_free_func(((batch_matmul_local_context_t *)(f->local_context))->data);
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

#ifdef CONFIG_BATCHMATMUL_FLOAT32
rt_function_error_t exec_batch_matmul(rt_function_t *f) {
  batch_matmul_local_context_t *context =
      (batch_matmul_local_context_t *)(f->local_context);
  batch_matmul_private_t *p = (batch_matmul_private_t *)(context->data);
  float *input_a = (float *)(p->input_a->data);
  float *input_b = (float *)(p->input_b->data);
  float *output = (float *)(p->output->data);

  int i;
  if (context->transpose_a) {
    for (i = 0; i < p->samples; i++) {
      transpose(input_a + p->offset_a * i, p->row_a, p->col_a);
    }
    p->row_a = p->row_a ^ p->col_a;
    p->col_a = p->row_a ^ p->col_a;
    p->row_a = p->row_a ^ p->col_a;
  }
  if (context->transpose_b) {
    for (i = 0; i < p->samples; i++) {
      transpose(input_b + p->offset_b * i, p->row_b, p->col_b);
    }
    p->row_b = p->row_b ^ p->col_b;
    p->col_b = p->row_b ^ p->col_b;
    p->row_b = p->row_b ^ p->col_b;
  }
  for (i = 0; i < p->samples; i++) {
    float *mtx_y = output + p->offset_y * i;
    float *mtx_a = input_a + p->offset_a * i;
    float *mtx_b = input_b + p->offset_b * i;
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
#endif /* CONFIG_BATCHMATMUL_FLOAT32 */

#ifdef CONFIG_BATCHMATMUL_GENERIC
rt_function_error_t exec_batch_matmul_generic(rt_function_t *f) {
  batch_matmul_local_context_t *context =
      (batch_matmul_local_context_t *)(f->local_context);
  batch_matmul_private_t *p = (batch_matmul_private_t *)(context->data);
  float *input_a = (float *)(p->input_a->data);
  float *input_b = (float *)(p->input_b->data);

  int i;
  if (context->transpose_a) {
    for (i = 0; i < p->samples; i++) {
      transpose(input_a + p->offset_a * i, p->row_a, p->col_a);
    }
    p->row_a = p->row_a ^ p->col_a;
    p->col_a = p->row_a ^ p->col_a;
    p->row_a = p->row_a ^ p->col_a;
  }
  if (context->transpose_b) {
    for (i = 0; i < p->samples; i++) {
      transpose(input_b + p->offset_b * i, p->row_b, p->col_b);
    }
    p->row_b = p->row_b ^ p->col_b;
    p->col_b = p->row_b ^ p->col_b;
    p->row_b = p->row_b ^ p->col_b;
  }
  for (i = 0; i < p->samples; i++) {
    int row_a = p->row_a;
    int col_b = p->col_b;
    int col_a = p->col_a;
    for (int j = 0; j < row_a; j++) {
      for (int k = 0; k < col_b; k++) {
        for (int l = 0; l < col_a; l++) {
          float a = p->get_input_a(p->input_a, p->offset_y * i + col_a * j + l);
          float b = p->get_input_b(p->input_b, p->offset_b * i + col_b * l + k);
          float y = p->get_output(p->output, p->offset_y * i + col_b * j + k);
          y += a * b;
          p->set_output(p->output, p->offset_y * i + col_b * j + k, y);
        }
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_BATCHMATMUL_GENERIC */

#endif /* CONFIG_BATCHMATMUL */
