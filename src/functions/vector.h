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

///
/// Calclate size of vector that has given shape.
///
int calc_shape_size(rt_list_t shape);

///
/// Create rt_variable_t from given rt_param_t.
///
/// rt_variable_t.buffer is allocated inside this function.
/// User should free rt_variable_t.buffer when vertex is no longer needed.
/// And rt_variable_t.shape is reference to rt_param_t.shape.
/// User should keep rt_param_t.shape until vertex is needed.
///
rt_variable_t get_values_from_param(rt_param_t param);

///
/// Create rt_param_t from given rt_variable_t.
///
/// All pointer in the created rt_param_t is reference to rt_variable_t.
/// User should keep rt_variable_t.shape and rt_variable_t.buffer until vertex
/// is needed.
///
rt_param_t vertex_to_param(rt_variable_t v);

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

void tensordot(tensordot_context_t c, rt_param_t input1, rt_param_t input2,
               rt_param_t output);

void free_tensordot_context(tensordot_context_t c);

/// @}

/// @defgroup ShapeFunction
/// @{

/// Calc vector size with this shape.
int shape_total_size(rt_list_t s);

/// Allocate shape
rt_list_t allocate_shape(int length);

/// Free allocated shape.
void free_shape(rt_list_t s);

/// Clone shape
///
/// shape.shape will be allocated inside this function.
/// User must free cloned shape.
rt_list_t clone_shape(rt_list_t src);

/// Calc vector axis at specified data pos.
void pos_to_shape(rt_list_t out, rt_list_t shape, int pos);

/// Calc data position at specified vector axis.
int shape_to_pos(rt_list_t s, rt_list_t pos);

/// If s has specified num, return position. Otherwise return -1.
int find_num_in_shape(rt_list_t s, int num);

/// @}

/// @defgroup VectorCalclation
/// @{

typedef struct {
  int num_of_inputs;

  rt_list_t shape;
  int shape_length;

  rt_list_t *input_shapes;
  rt_list_t output_shape;

  rt_list_t position;
  rt_list_t *input_positions;
  rt_list_t output_position;

  float *input_values;
} vector_calc_context_t;

vector_calc_context_t init_vector_calc_context(int num_of_inputs,
                                               rt_param_t *inputs,
                                               rt_param_t output);

void vector_calc(vector_calc_context_t c, int input_size, rt_param_t *inputs,
                 rt_param_t output, float (*calc_func)(int, float *));

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

  rt_param_t output;

} vector_average_context_t;

vector_average_context_t init_vector_average_context(rt_list_t in_shape,
                                                     rt_list_t axes_shape);
void vector_average_calc_mean(vector_average_context_t c, rt_param_t input);
void free_vector_average_context(vector_average_context_t c);

/// @}

/// @}

#endif // H_VECTOR_H_
