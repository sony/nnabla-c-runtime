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

int infer(nn_network_t *net, int argc, char *argv[]) {
  int i, j; // Iterator
  rt_return_value_t ret;
  const char *data_type[] = {"NN_DATA_TYPE_FLOAT", "NN_DATA_TYPE_INT16",
                             "NN_DATA_TYPE_INT8", "NN_DATA_TYPE_SIGN",
                             "END_OF_NN_DATA_TYPE"};

  for (i = 0; i < argc; i++) {
    printf("     %d: %s\n", i, argv[i]);
  }

  rt_context_pointer context = 0;

  ret = rt_allocate_context(&context);
  assert(ret == RT_RET_NOERROR);

  ret = rt_initialize_context(context, net);
  assert(ret == RT_RET_NOERROR);

  for (i = 0; i < rt_num_of_input(context); i++) {
    printf("Input[%d] size:%d\n", i, rt_input_size(context, i));
    FILE *input = 0;
#ifdef _MSC_VER
    fopen_s(&input, *argv, "rb");
#else
    input = fopen(*argv, "rb");
#endif
    argv += 1;
    assert(input);
    fseek(input, 0L, SEEK_END);
    size_t input_data_size = ftell(input);
    int read_size = 0;

    nn_variable_t *variable = rt_input_variable(context, i);
    printf("Input[%d] data type:%s, fp:%d\n", i, data_type[variable->type],
           variable->fp_pos);

    switch (variable->type) {
    case NN_DATA_TYPE_FLOAT:
      assert(input_data_size == rt_input_size(context, i) * sizeof(float));
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    case NN_DATA_TYPE_INT8:
      assert(input_data_size == rt_input_size(context, i) * sizeof(uint8_t));
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    case NN_DATA_TYPE_INT16:
      assert(input_data_size == rt_input_size(context, i) * sizeof(uint16_t));
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    case NN_DATA_TYPE_SIGN:
      assert(input_data_size == (rt_input_size(context, i) >> 3));
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    default:
      printf("NN_DATA_TYPE_SIGN is not yet supported.");
      assert(0);
      break;
    }

    assert(read_size == input_data_size);
    fclose(input);

    printf("Input[%d] Shape (", i);
    for (j = 0; j < rt_input_dimension(context, i); j++) {
      printf(" %d", rt_input_shape(context, i, j));
    }
    printf(" )\n");
  }

  ret = rt_forward(context);
  assert(ret == RT_RET_NOERROR);

  for (i = 0; i < rt_num_of_output(context); i++) {
    printf("Output[%d] size:%d\n", i, rt_output_size(context, i));
    size_t output_filename_length = strlen(*argv) + 10;
    char *output_filename = malloc(output_filename_length);
    assert(output_filename);
#ifdef _MSC_VER
    sprintf_s(output_filename, output_filename_length, "%s_%d.bin", *argv, i);
#else
    sprintf(output_filename, "%s_%d.bin", *argv, i);
#endif
    printf("Output[%d] filename %s\n", i, output_filename);

    FILE *output = 0;
#ifdef _MSC_VER
    fopen_s(&output, output_filename, "wb");
#else
    output = fopen(output_filename, "wb");
#endif
    assert(output);

    int output_data_size =
        rt_output_size(context, i) * sizeof(float); // TODO float only.
    int output_write_size =
        (int)fwrite(rt_output_buffer(context, i), sizeof(uint8_t),
                    output_data_size, output);
    assert(output_write_size == output_data_size);

    fclose(output);
    free(output_filename);

    printf("Output[%d] Shape (", i);
    for (j = 0; j < rt_output_dimension(context, i); j++) {
      printf(" %d", rt_output_shape(context, i, j));
    }
    printf(" )\n");

    nn_variable_t *variable = rt_output_variable(context, i);
    printf("Output[%d] data type:%s, fp:%d\n", i, data_type[variable->type],
           variable->fp_pos);
  }
  ret = rt_free_context(&context);
  assert(ret == RT_RET_NOERROR);
  return 0;
}
