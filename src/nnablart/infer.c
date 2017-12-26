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
#include <stdlib.h>
#include <string.h>

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "dump_context.h" // For debug.

int infer(nn_network_t *net, int argc, char *argv[]) {
  int i, j; // Iterator
  rt_error_enum_t ret;

  for (i = 0; i < argc; i++) {
    printf("     %d: %s\n", i, argv[i]);
  }

  rt_context_pointer context;
  ret = rt_initialize_context(&context, net);
  assert(ret == RT_ERROR_NOERROR);

  dump_context(context);

  for (i = 0; i < rt_num_of_input(context); i++) {
    printf("Input[%d] size:%d\n", i, rt_input_size(context, i));
    FILE *input = fopen(*argv, "rb");
    argv += 1;
    assert(input);
    fseek(input, 0L, SEEK_END);
    size_t input_data_size = ftell(input);

    assert(input_data_size ==
           rt_input_size(context, i) * sizeof(float)); // TODO float only.
    fseek(input, 0L, SEEK_SET);
    int read_size = fread(rt_input_buffer(context, i), sizeof(uint8_t),
                          input_data_size, input);
    assert(read_size == input_data_size);

    fclose(input);

    printf("Input[%d] Shape (", i);
    for (j = 0; j < rt_input_dimension(context, i); j++) {
      printf(" %d", rt_input_shape(context, i, j));
    }
    printf(" )\n");
  }

  ret = rt_forward(context, 0, 0);
  assert(ret == RT_ERROR_NOERROR);

  for (i = 0; i < rt_num_of_output(context); i++) {
    printf("Output[%d] size:%d\n", i, rt_output_size(context, i));

    char *output_filename = malloc(strlen(*argv) + 10);
    assert(output_filename);
    sprintf(output_filename, "%s_%d.bin", *argv, i);
    printf("Output[%d] filename %s\n", i, output_filename);

    FILE *output = fopen(output_filename, "wb");
    assert(output);

    int output_data_size =
        rt_output_size(context, i) * sizeof(float); // TODO float only.
    int output_write_size = fwrite(rt_output_buffer(context, i),
                                   sizeof(uint8_t), output_data_size, output);
    assert(output_write_size == output_data_size);

    fclose(output);
    free(output_filename);

    printf("Output[%d] Shape (", i);
    for (j = 0; j < rt_output_dimension(context, i); j++) {
      printf(" %d", rt_output_shape(context, i, j));
    }
    printf(" )\n");
  }
  ret = rt_free_context(&context);
  assert(ret == RT_ERROR_NOERROR);
  return 0;
}
