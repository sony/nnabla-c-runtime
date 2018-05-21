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

#ifndef H_CONTEXT_H_171220164849_
#define H_CONTEXT_H_171220164849_

#include <nnablart/functions.h>
#include <nnablart/network.h>

typedef struct {
  rt_buffer_allocate_type_t allocate_type;
  void *buffer;
} rt_variable_buffer_context_t;

typedef struct {
  nn_function_t *info;
  rt_function_t func;
} rt_function_context_t;

typedef struct {
  nn_function_type_t type;
  rt_return_value_t (*allocate_local_context)(void *f);
} rt_function_callback_t;

typedef struct {
  int num_of_buffers;
  rt_variable_buffer_context_t *buffers;

  int num_of_variables;
  rt_variable_t *variables;

  int num_of_functions;
  rt_function_context_t *functions;

  int num_of_inputs;
  int *input_variable_ids;

  int num_of_outputs;
  int *output_variable_ids;

  int num_of_callbacks;
  rt_function_callback_t *callbacks;

} rt_context_t;

#endif // H_CONTEXT_H_171220164849_
