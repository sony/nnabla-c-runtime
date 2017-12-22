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
#include <stdio.h>
#include <string.h>

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "dump_context.h" // For debug.

int infer(nn_network_t *net, int argc, char *argv[]) {
  int i, j; // Iterator
  for (i = 0; i < argc; i++) {
    printf("     %d: %s\n", i, argv[i]);
  }

  rt_context_pointer context;
  rt_initialize_context(&context, net);

  for (i = 0; i < rt_num_of_input(context); i++) {
    printf("Input[%d] size:%d\n", i, rt_input_size(context, i));
    printf("Input[%d] Shape (", i);
    for (j = 0; j < rt_input_dimension(context, i); j++) {
      printf(" %d", rt_input_shape(context, i, j));
    }
    printf(" )\n");
  }

  for (i = 0; i < rt_num_of_output(context); i++) {
    printf("Output[%d] size:%d\n", i, rt_output_size(context, i));
    printf("Output[%d] Shape (", i);
    for (j = 0; j < rt_output_dimension(context, i); j++) {
      printf(" %d", rt_output_shape(context, i, j));
    }
    printf(" )\n");
  }

  dump_context(context);

  rt_free_context(&context);
  return 0;
}
