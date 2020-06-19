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

static int check_data_size(int actual_size, int expected_size) {
  if (actual_size != expected_size) {
    printf("Input data size is invalid.\n");
    printf("Expected data size is: %d\n", expected_size);
    printf("Actual data size is: %d\n", actual_size);
    return -1;
  }
  return 0;
}

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
  if (ret != RT_RET_NOERROR) {
    switch (ret) {
    case RT_RET_ERROR_VERSION_UNMATCH:
      printf("input network(.nnb) is mismatch to current runtime library.\n");
      return -1;
    case RT_RET_ERROR_INITIALIZE_CONTEXT_TWICE:
      printf("cannot initialize context twice.\n");
      return -1;
    default:
      printf("rt_initialize_context() failed with %d.\n", ret);
      return -1;
    }
  }

  if (argc != rt_num_of_input(context) + 1) {
    printf("Incorrect input parameters.\n");
    printf(" Required inputs: %d and output: 1\n", rt_num_of_input(context));
    printf(" Actual inputs: %d\n", argc);
    return -1;
  }

  for (i = 0; i < rt_num_of_input(context); i++) {
    printf("Input[%d] size:%d\n", i, rt_input_size(context, i));
    FILE *input = 0;
#ifdef _MSC_VER
    fopen_s(&input, *argv, "rb");
#else
    input = fopen(*argv, "rb");
#endif
    argv += 1;
    if (input == NULL) {
      printf("Cannot open input file: %s.\n", *(argv - 1));
      return -1;
    }
    fseek(input, 0L, SEEK_END);
    size_t input_data_size = ftell(input);
    int read_size = 0;

    nn_variable_t *variable = rt_input_variable(context, i);
    printf("Input[%d] data type:%s, fp:%d\n", i, data_type[variable->type],
           variable->fp_pos);

    switch (variable->type) {
    case NN_DATA_TYPE_FLOAT:
      if (check_data_size(input_data_size,
                          rt_input_size(context, i) * sizeof(float)) < 0)
        return -1;
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    case NN_DATA_TYPE_INT8:
      if (check_data_size(input_data_size,
                          rt_input_size(context, i) * sizeof(uint8_t)) < 0)
        return -1;
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    case NN_DATA_TYPE_INT16:
      if (check_data_size(input_data_size,
                          rt_input_size(context, i) * sizeof(uint16_t)) < 0)
        return -1;
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    case NN_DATA_TYPE_SIGN:
      if (check_data_size(input_data_size, rt_input_size(context, i) >> 3) < 0)
        return -1;
      fseek(input, 0L, SEEK_SET);
      read_size = (int)fread(rt_input_buffer(context, i), sizeof(uint8_t),
                             input_data_size, input);
      break;
    default:
      printf("Type: %d is not yet supported.", variable->type);
      return -1;
    }

    assert(read_size == input_data_size);
    if (read_size != input_data_size) {
      printf("Failed to read input data, expected to read: %d bytes, actual "
             "read: %d bytes\n",
             (int)input_data_size, (int)read_size);
    }
    fclose(input);

    printf("Input[%d] Shape (", i);
    for (j = 0; j < rt_input_dimension(context, i); j++) {
      printf(" %d", rt_input_shape(context, i, j));
    }
    printf(" )\n");
  }

  ret = rt_forward(context);
  if (ret != RT_RET_NOERROR) {
    printf("Error occurs in infer process. %d\n", ret);
    return -1;
  }

  for (i = 0; i < rt_num_of_output(context); i++) {
    printf("Output[%d] size:%d\n", i, rt_output_size(context, i));
    size_t output_filename_length = strlen(*argv) + 10;
    char *output_filename = malloc(output_filename_length);
    assert(output_filename);
#ifdef _MSC_VER
    sprintf_s(output_filename, output_filename_length, "%s_%d.bin", *argv, i);
#else
    snprintf(output_filename, output_filename_length, "%s_%d.bin", *argv, i);
#endif
    printf("Output[%d] filename %s\n", i, output_filename);

    FILE *output = 0;
#ifdef _MSC_VER
    fopen_s(&output, output_filename, "wb");
#else
    output = fopen(output_filename, "wb");
#endif
    if (output == NULL) {
      printf("Cannot open output file:%s.\n", output_filename);
      return -1;
    }
    int output_data_type = rt_output_variable(context, i)->type;
    int output_data_size;

    switch(output_data_type) {
    case NN_DATA_TYPE_FLOAT:
      output_data_size = rt_output_size(context, i) * sizeof(float);
      break;
    case NN_DATA_TYPE_INT8:
      output_data_size = rt_output_size(context, i) * sizeof(int8_t);
      break;
    case NN_DATA_TYPE_INT16:
      output_data_size = rt_output_size(context, i) * sizeof(int16_t);
      break;
    case NN_DATA_TYPE_SIGN:
      output_data_size = rt_output_size(context, i) >> 3;
      break;
    default:
      printf("Type: %d is not yet supported.", output_data_type);
      return -1;
    }

    int output_write_size =
        (int)fwrite(rt_output_buffer(context, i), sizeof(uint8_t),
                    output_data_size, output);
    if (output_write_size != output_data_size) {
      printf("Failed to write output. Expected writing: %d bytes, actual "
             "writing: %d bytes\n",
             output_data_size, output_write_size);
      return -1;
    }

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
