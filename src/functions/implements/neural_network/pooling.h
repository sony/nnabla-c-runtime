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

#ifndef H_POOLING_H_
#define H_POOLING_H_

#include "../../utilities/accessor.h"
#include <nnablart/functions.h>

typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  uint8_t including_pad;
  void *data;
} pooling_context_t;

typedef struct {
  int hstart;
  int hend;
  int wstart;
  int wend;
  int wx;
  int pool_size;
  rt_variable_t *x;
  rt_variable_getter get_x;
  rt_variable_t *y;
  rt_variable_setter set_y;
  nn_size_t offset_x;
  nn_size_t offset_y;
  uint8_t including_pad;
} pooling_calc_context_t;

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  int input_n_kernel_size_diff;
  int x_stride;
  int y_stride;
  pooling_calc_context_t calc_context;
} pooling_private_t;

typedef float (*exec_pooling_func_t)(pooling_calc_context_t);

rt_function_error_t allocate_pooling(rt_function_t *f,
                                     pooling_context_t *context,
                                     pooling_private_t *p);
rt_function_error_t free_pooling(pooling_private_t *p);
rt_function_error_t exec_pooling(rt_function_t *f, pooling_context_t *context,
                                 pooling_private_t *p,
                                 exec_pooling_func_t exec);
rt_function_error_t exec_pooling_generic(rt_function_t *f,
                                         pooling_context_t *context,
                                         pooling_private_t *p,
                                         exec_pooling_func_t exec);

/// Calculate max value.
float calc_max(pooling_calc_context_t calc);

/// Calculate sum value.
float calc_sum(pooling_calc_context_t calc);

/// Calculate average value.
float calc_average(pooling_calc_context_t calc);

/// Calculate max value.
float calc_max_generic(pooling_calc_context_t calc);

/// Calculate sum value.
float calc_sum_generic(pooling_calc_context_t calc);

/// Calculate average value.
float calc_average_generic(pooling_calc_context_t calc);

#endif // H_POOLING_H_
