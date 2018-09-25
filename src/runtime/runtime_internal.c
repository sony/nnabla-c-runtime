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

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "runtime_internal.h"

rt_list_t create_rt_list_from_nn_list(nn_network_t *n, nn_list_t list) {
  rt_list_t l;
  l.size = list.size;
  l.data = (int *)NN_GET(n, list.list);
  return l;
}

rt_function_context_t allocate_function_io(nn_network_t *n, rt_context_t *c,
                                           nn_function_t *function) {
  int i; // Iterator

  rt_function_context_t func;
  func.info = function;

  rt_list_t inputs = create_rt_list_from_nn_list(n, function->inputs);
  func.func.num_of_inputs = inputs.size;
  func.func.inputs = rt_malloc_func(sizeof(rt_variable_t *) * inputs.size);
  if (func.func.inputs) {
    for (i = 0; i < inputs.size; i++) {
      int index = *(inputs.data + i);
      if (index < c->num_of_variables) {
        func.func.inputs[i] = &(c->variables[index]);
      } else {
        func.func.inputs[i] = 0;
      }
    }
  }

  rt_list_t outputs = create_rt_list_from_nn_list(n, function->outputs);
  func.func.num_of_outputs = outputs.size;
  func.func.outputs = rt_malloc_func(sizeof(rt_variable_t *) * outputs.size);
  if (func.func.outputs) {
    for (i = 0; i < outputs.size; i++) {
      int index = *(outputs.data + i);
      if (index < c->num_of_variables) {
        func.func.outputs[i] = &(c->variables[index]);
      } else {
        func.func.outputs[i] = 0;
      }
    }
  }

  return func;
}
