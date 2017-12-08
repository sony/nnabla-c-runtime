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

typedef struct rt_param_t {{
  rt_list_t shape;
  nn_param_type_t type; ///< Type of param values
  float coefficient;    ///< Coefficient value for convert int to float.
  void *data;           ///< Pointer to param data
  float (*get)(struct rt_param_t *, nn_size_t); ///< Get data from position
  void (*set)(struct rt_param_t *, nn_size_t,
              float); ///< Get data from position
}} rt_param_t;

#define GET_FLOAT(xParam, xPos) (*((float *)((xParam)->data) + (xPos)))
float getFloat(rt_param_t *param, nn_size_t pos);
#define GET_INT16(xParam, xPos)                                                \
  ((xParam)->coefficient * (float)(*((int16_t *)((xParam)->data) + (xPos))))
float getInt16(rt_param_t *param, nn_size_t pos);
#define GET_INT8(xParam, xPos)                                                 \
  ((xParam)->coefficient * (float)(*((int8_t *)((xParam)->data) + (xPos))))
float getInt8(rt_param_t *param, nn_size_t pos);
#define GET_SIGN(xParam, xPos) getSign(xParam, xPos)
float getSign(rt_param_t *param, nn_size_t pos);

void setFloat(rt_param_t *param, nn_size_t pos, float value);
void setInt16(rt_param_t *param, nn_size_t pos, float value);
void setInt8(rt_param_t *param, nn_size_t pos, float value);
void setSign(rt_param_t *param, nn_size_t pos, float value);

typedef enum {{
  RT_BUFFER_ALLOCATE_TYPE_MALLOC = 0,
  RT_BUFFER_ALLOCATE_TYPE_STINGY,
  RT_BUFFER_ALLOCATE_TYPE_INPUT,
  RT_BUFFER_ALLOCATE_TYPE_OUTPUT,
}} rt_buffer_allocate_type_t;

typedef struct {{
  rt_list_t shape;
  rt_buffer_allocate_type_t allocate_type;
  float *buffer;
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
