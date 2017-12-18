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

#ifndef H_AFFINE_INTERNAL_H_171218154530_
#define H_AFFINE_INTERNAL_H_171218154530_

#include "../../utilities.h"

typedef void (*exec_affine_func_t)(rt_function_t *f);

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;

  rt_variable_t *weight;
  rt_variable_getter get_weight;

  rt_variable_t *bias;
  rt_variable_getter get_bias;

  rt_variable_t *output;
  int output_size;
  rt_variable_setter set_output;
  rt_variable_getter get_output;

  int base_loop_size;
  int input_loop_size;
  int output_loop_size;

  exec_affine_func_t exec;
} affine_local_context_t;

#endif // H_AFFINE_INTERNAL_H_171218154530_
