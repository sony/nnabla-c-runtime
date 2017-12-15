// -*- coding:utf-8 -*-
#ifndef H_FUNCTIONS_H__
#define H_FUNCTIONS_H__

#ifdef __cplusplus
extern "C" {{
#endif /* __cplusplus */

#include <stdint.h>
#include <stdio.h>

#include <nnablart/network.h>

// Definitions.
#define INT8_BIT_LENGTH (8)
#define INT16_BIT_LENGTH (16)

// version of cforwardprop library
#define NNABLART_MAJOR_VERSION (1)
#define NNABLART_MINOR_VERSION (0)

typedef struct {{
  int size;
  int *data;
}} rt_list_t;

typedef enum {{
  RT_BUFFER_ALLOCATE_TYPE_MALLOC = 0,
  RT_BUFFER_ALLOCATE_TYPE_ALLOCATED,
  RT_BUFFER_ALLOCATE_TYPE_STINGY,
  RT_BUFFER_ALLOCATE_TYPE_INPUT,
  RT_BUFFER_ALLOCATE_TYPE_OUTPUT,
}} rt_buffer_allocate_type_t;

typedef struct rt_variable_t {{
  rt_list_t shape;
  nn_data_type_t type:4; ///< Type of param values
  unsigned int fp_pos:4;
  float coefficient;    ///< Coefficient value for convert int to float.
  void *data;
}} rt_variable_t;

typedef struct {{
  int num_of_inputs;
  rt_variable_t **inputs;

  int num_of_outputs;
  rt_variable_t **outputs;

  void *config;
}} rt_function_t;

{FUNCTION_DEFINES}

#ifdef __cplusplus
}}
#endif /* __cplusplus */
#endif // H_FUNCTIONS_H__
