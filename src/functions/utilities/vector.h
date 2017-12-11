// -*- coding:utf-8 -*-
#ifndef H_VECTOR_H_
#define H_VECTOR_H_

#include <nnablart/functions.h>

////////////////////////////////////////////////////////////////////////////////
/// @defgroup VectorFunctions API for vector calculation.
///
/// APIs for calculate vector.
///
/// @{

/// @defgroup TensorDot
/// @{

typedef struct {
  rt_list_t input1_shape;
  rt_list_t input2_shape;
  rt_list_t axes1;
  rt_list_t axes2;
  rt_list_t output_shape;
} tensordot_context_t;

tensordot_context_t init_tensordot_context(rt_list_t input1_shape,
                                           rt_list_t input2_shape,
                                           rt_list_t axes1, rt_list_t axes2);

void tensordot(tensordot_context_t c, rt_variable_t input1, rt_variable_t input2,
               rt_variable_t output);

void free_tensordot_context(tensordot_context_t c);

/// @}

/// @defgroup ShapeFunction
/// @{

/// Calc vector axis at specified data pos.
void pos_to_shape(rt_list_t out, rt_list_t shape, int pos);

/// Calc data position at specified vector axis.
int shape_to_pos(rt_list_t s, rt_list_t pos);

/// If s has specified num, return position. Otherwise return -1.
int find_num_in_shape(rt_list_t s, int num);

/// Calclate data size with shape
int calc_shape_size(rt_list_t shape);

/// @}

/// @defgroup VectorCalclation
/// @{

typedef struct {
  int num_of_inputs;

  rt_list_t shape;

  rt_list_t *input_shapes;
  rt_list_t output_shape;

  rt_list_t position;
  rt_list_t *input_positions;
  rt_list_t output_position;

  float *input_values;
} vector_calc_context_t;

vector_calc_context_t init_vector_calc_context(int num_of_inputs,
                                               rt_variable_t *inputs,
                                               rt_variable_t output);

void vector_calc(vector_calc_context_t c, int input_size, rt_variable_t *inputs,
                 rt_variable_t output, float (*calc_func)(int, float *));

void free_vector_calc_context(vector_calc_context_t c);

/// @}

/// @defgroup VectorAverages
/// @{
typedef struct {
  rt_list_t in_shape;
  rt_list_t in_pos;

  rt_list_t calc_axes;
  rt_list_t calc_shape;
  rt_list_t calc_pos;
  int calc_ipos_max;

  rt_list_t rest_axes;
  rt_list_t rest_shape;
  rt_list_t rest_pos;
  int rest_ipos_max;

  rt_variable_t output;

} vector_average_context_t;

vector_average_context_t init_vector_average_context(rt_list_t in_shape,
                                                     rt_list_t axes_shape);
void vector_average_calc_mean(vector_average_context_t c, rt_variable_t input);
void free_vector_average_context(vector_average_context_t c);

/// @}

/// @}

#endif // H_VECTOR_H_
