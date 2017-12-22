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

#include <assert.h>
#include <string.h>

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "runtime_internal.h"

rt_error_enum_t rt_initialize_context(rt_context_pointer *context,
                                      nn_network_t *n) {
  WHOAMI("%s\n", __func__);
  int i; // Iterator

  rt_context_t *c = malloc(sizeof(rt_context_t));
  if (c == 0) {
    WHOAMI("RT_ERROR_ALLOCATE_CONTEXT\n");
    return RT_ERROR_ALLOCATE_CONTEXT;
  }

  // Buffers
  c->num_of_buffers = n->buffers.size;
  c->buffers = malloc(sizeof(rt_variable_buffer_context_t) * c->num_of_buffers);

  if (c->buffers == 0) {
    WHOAMI("RT_ERROR_ALLOCATE_CONTEXT\n");
    return RT_ERROR_ALLOCATE_CONTEXT;
  }

  int *list = (int *)NN_GET(n, n->buffers.list);
  for (i = 0; i < c->num_of_buffers; i++) {
    WHOAMI("ALLOCATE BUFFER: %d %d\n", i, *(list + i));
    c->buffers[i].allocate_type = RT_BUFFER_ALLOCATE_TYPE_MALLOC;
    c->buffers[i].buffer = malloc(*(list + i));
    if (c->buffers[i].buffer == 0) {
      WHOAMI("RT_ERROR_ALLOCATE_CONTEXT\n");
      return RT_ERROR_ALLOCATE_CONTEXT;
    }
  }

  // Variables
  c->num_of_variables = n->variables.size;
  c->variables = malloc(sizeof(rt_variable_t) * c->num_of_variables);
  if (c->variables == 0) {
    WHOAMI("RT_ERROR_ALLOCATE_CONTEXT\n");
    return RT_ERROR_ALLOCATE_CONTEXT;
  }

  list = (int *)NN_GET(n, n->variables.list);
  for (i = 0; i < c->num_of_variables; i++) {
    nn_variable_t *var = (nn_variable_t *)(NN_GET(n, *(list + i)));
    c->variables[i].shape = create_rt_list_from_nn_list(n, var->shape);
    c->variables[i].type = var->type;
    c->variables[i].fp_pos = var->fp_pos;
    if (var->data_index < 0) {
      int index = (-1 * var->data_index) - 1;
      if (index >= c->num_of_buffers) {
        return RT_ERROR_INVALID_BUFFER_INDEX;
      }
      c->variables[i].data = c->buffers[index].buffer;
    } else {
      c->variables[i].data = NN_GET(n, var->data_index);
    }
  }

  c->num_of_functions = n->functions.size;
  c->functions = malloc(sizeof(rt_function_context_t) * c->num_of_functions);
  list = (int *)NN_GET(n, n->functions.list);
  for (i = 0; i < c->num_of_functions; i++) {
    nn_function_t *func = (nn_function_t *)(NN_GET(n, *(list + i)));
    c->functions[i] = create_function_context(n, c, func);
  }

  rt_list_t inputs = create_rt_list_from_nn_list(n, n->inputs);
  c->num_of_inputs = inputs.size;
  c->input_variable_ids = malloc(sizeof(int *) * c->num_of_inputs);
  for (i = 0; i < c->num_of_inputs; i++) {
    c->input_variable_ids[i] = inputs.data[i];
  }

  rt_list_t outputs = create_rt_list_from_nn_list(n, n->outputs);
  c->num_of_outputs = outputs.size;
  c->output_variable_ids = malloc(sizeof(int *) * c->num_of_outputs);
  for (i = 0; i < c->num_of_outputs; i++) {
    c->output_variable_ids[i] = outputs.data[i];
  }

  *context = c;
  return RT_ERROR_NOERROR;
}

rt_error_enum_t rt_free_context(rt_context_pointer *context) {
  WHOAMI("%s\n", __func__);
  rt_context_t *c = *context;

  int i; // Iterator

  // Buffers
  for (i = 0; i < c->num_of_buffers; i++) {
    if (c->buffers[i].allocate_type == RT_BUFFER_ALLOCATE_TYPE_MALLOC) {
      free(c->buffers[i].buffer);
    }
  }
  free(c->buffers);

  // Variables
  free(c->variables);

  // Functions
  for (i = 0; i < c->num_of_functions; i++) {
    free(c->functions[i].func.inputs);
    free(c->functions[i].func.outputs);

    if (c->functions[i].func.config) {
      free(c->functions[i].func.config);
    }
  }
  free(c->functions);

  free(c->input_variable_ids);
  free(c->output_variable_ids);

  free(*context);
  return RT_ERROR_NOERROR;
}

int rt_num_of_input(rt_context_pointer context) {
  return ((rt_context_t *)context)->num_of_inputs;
}

int rt_input_size(rt_context_pointer context, size_t index) {
  int i; // Iterator

  rt_context_t *c = context;
  rt_variable_t v = c->variables[c->input_variable_ids[index]];

  int size = 1;
  for (i = 0; i < v.shape.size; i++) {
    size *= v.shape.data[i];
  }

  return size;
}

int rt_input_dimension(rt_context_pointer context, size_t index) {
  rt_context_t *c = context;
  return c->variables[c->input_variable_ids[index]].shape.size;
}

int rt_input_shape(rt_context_pointer context, size_t index,
                   size_t shape_index) {
  rt_context_t *c = context;
  return c->variables[c->input_variable_ids[index]].shape.data[shape_index];
}

float *rt_input_buffer(rt_context_pointer context, size_t index) {
  rt_context_t *c = context;
  return c->variables[c->input_variable_ids[index]].data;
}

int rt_num_of_output(rt_context_pointer context) {
  return ((rt_context_t *)context)->num_of_outputs;
}

int rt_output_size(rt_context_pointer context, size_t index) {
  int i; // Iterator

  rt_context_t *c = context;
  rt_variable_t v = c->variables[c->output_variable_ids[index]];

  int size = 1;
  for (i = 0; i < v.shape.size; i++) {
    size *= v.shape.data[i];
  }

  return size;
}

int rt_output_dimension(rt_context_pointer context, size_t index) {
  rt_context_t *c = context;
  return c->variables[c->output_variable_ids[index]].shape.size;
}

int rt_output_shape(rt_context_pointer context, size_t index,
                    size_t shape_index) {
  rt_context_t *c = context;
  return c->variables[c->output_variable_ids[index]].shape.data[shape_index];
}

float *rt_output_buffer(rt_context_pointer context, size_t index) {
  rt_context_t *c = context;
  return c->variables[c->output_variable_ids[index]].data;
}

rt_error_enum_t rt_forward(rt_context_pointer context, float **input,
                           float **output) {
  WHOAMI("%s\n", __func__);
  return RT_ERROR_NOERROR;
}
