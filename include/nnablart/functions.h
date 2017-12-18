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

#ifndef H_FUNCTIONS_H__
#define H_FUNCTIONS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdio.h>

#include <nnablart/network.h>

// version of cforwardprop library
#define NNABLART_MAJOR_VERSION (1)
#define NNABLART_MINOR_VERSION (0)

typedef struct {
  int size;
  int *data;
} rt_list_t;

typedef enum {
  RT_BUFFER_ALLOCATE_TYPE_MALLOC = 0,
  RT_BUFFER_ALLOCATE_TYPE_ALLOCATED,
  RT_BUFFER_ALLOCATE_TYPE_STINGY,
  RT_BUFFER_ALLOCATE_TYPE_INPUT,
  RT_BUFFER_ALLOCATE_TYPE_OUTPUT,
  END_OF_RT_BUFFER_ALLOCATE_TYPE
} rt_buffer_allocate_type_t;

typedef struct rt_variable_t {
  rt_list_t shape;
  nn_data_type_t type : 4; ///< Type of param values
  unsigned int fp_pos : 4;
  float coefficient; ///< Coefficient value for convert int to float.
  void *data;
} rt_variable_t;

typedef struct {
  int num_of_inputs;
  rt_variable_t **inputs;

  int num_of_outputs;
  rt_variable_t **outputs;

  void *config;
} rt_function_t;

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

// Affine
typedef struct {
  int32_t base_axis;
  void *local_context;
} affine_config_t;

void allocate_affine_local_context(rt_function_t *f);
void free_affine_local_context(rt_function_t *f);
void exec_affine(rt_function_t *f);

// Convolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} convolution_config_t;

void allocate_convolution_local_context(rt_function_t *f);
void free_convolution_local_context(rt_function_t *f);
void exec_convolution(rt_function_t *f);

// DepthwiseConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t multiplier;
  void *local_context;
} depthwise_convolution_config_t;

void allocate_depthwise_convolution_local_context(rt_function_t *f);
void free_depthwise_convolution_local_context(rt_function_t *f);
void exec_depthwise_convolution(rt_function_t *f);

// Deconvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} deconvolution_config_t;

void allocate_deconvolution_local_context(rt_function_t *f);
void free_deconvolution_local_context(rt_function_t *f);
void exec_deconvolution(rt_function_t *f);

// MaxPooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  void *local_context;
} max_pooling_config_t;

void allocate_max_pooling_local_context(rt_function_t *f);
void free_max_pooling_local_context(rt_function_t *f);
void exec_max_pooling(rt_function_t *f);

// AveragePooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  uint8_t including_pad;
  void *local_context;
} average_pooling_config_t;

void allocate_average_pooling_local_context(rt_function_t *f);
void free_average_pooling_local_context(rt_function_t *f);
void exec_average_pooling(rt_function_t *f);

// SumPooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  void *local_context;
} sum_pooling_config_t;

void allocate_sum_pooling_local_context(rt_function_t *f);
void free_sum_pooling_local_context(rt_function_t *f);
void exec_sum_pooling(rt_function_t *f);

// Unpooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  void *local_context;
} unpooling_config_t;

void allocate_unpooling_local_context(rt_function_t *f);
void free_unpooling_local_context(rt_function_t *f);
void exec_unpooling(rt_function_t *f);

// Embed

void allocate_embed_local_context(rt_function_t *f);
void free_embed_local_context(rt_function_t *f);
void exec_embed(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Sigmoid

void allocate_sigmoid_local_context(rt_function_t *f);
void free_sigmoid_local_context(rt_function_t *f);
void exec_sigmoid(rt_function_t *f);

// Swish

void allocate_swish_local_context(rt_function_t *f);
void free_swish_local_context(rt_function_t *f);
void exec_swish(rt_function_t *f);

// Tanh

void allocate_tanh_local_context(rt_function_t *f);
void free_tanh_local_context(rt_function_t *f);
void exec_tanh(rt_function_t *f);

// ReLU
typedef struct {
  uint8_t inplace;
  void *local_context;
} relu_config_t;

void allocate_relu_local_context(rt_function_t *f);
void free_relu_local_context(rt_function_t *f);
void exec_relu(rt_function_t *f);

// LeakyReLU
typedef struct {
  float alpha;
  void *local_context;
} leaky_relu_config_t;

void allocate_leaky_relu_local_context(rt_function_t *f);
void free_leaky_relu_local_context(rt_function_t *f);
void exec_leaky_relu(rt_function_t *f);

// Softmax
typedef struct {
  int32_t axis;
  void *local_context;
} softmax_config_t;

void allocate_softmax_local_context(rt_function_t *f);
void free_softmax_local_context(rt_function_t *f);
void exec_softmax(rt_function_t *f);

// ELU
typedef struct {
  float alpha;
  void *local_context;
} elu_config_t;

void allocate_elu_local_context(rt_function_t *f);
void free_elu_local_context(rt_function_t *f);
void exec_elu(rt_function_t *f);

// SELU
typedef struct {
  float scale;
  float alpha;
  void *local_context;
} selu_config_t;

void allocate_selu_local_context(rt_function_t *f);
void free_selu_local_context(rt_function_t *f);
void exec_selu(rt_function_t *f);

// CReLU
typedef struct {
  int32_t axis;
  void *local_context;
} crelu_config_t;

void allocate_crelu_local_context(rt_function_t *f);
void free_crelu_local_context(rt_function_t *f);
void exec_crelu(rt_function_t *f);

// CELU
typedef struct {
  float alpha;
  int32_t axis;
  void *local_context;
} celu_config_t;

void allocate_celu_local_context(rt_function_t *f);
void free_celu_local_context(rt_function_t *f);
void exec_celu(rt_function_t *f);

// PReLU
typedef struct {
  int32_t base_axis;
  void *local_context;
} prelu_config_t;

void allocate_prelu_local_context(rt_function_t *f);
void free_prelu_local_context(rt_function_t *f);
void exec_prelu(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  float decay_rate;
  float eps;
  uint8_t batch_stat;
  void *local_context;
} batch_normalization_config_t;

void allocate_batch_normalization_local_context(rt_function_t *f);
void free_batch_normalization_local_context(rt_function_t *f);
void exec_batch_normalization(rt_function_t *f);

// MeanSubtraction
typedef struct {
  int32_t base_axis;
  uint8_t update_running_mean;
  void *local_context;
} mean_subtraction_config_t;

void allocate_mean_subtraction_local_context(rt_function_t *f);
void free_mean_subtraction_local_context(rt_function_t *f);
void exec_mean_subtraction(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} sum_config_t;

void allocate_sum_local_context(rt_function_t *f);
void free_sum_local_context(rt_function_t *f);
void exec_sum(rt_function_t *f);

// Mean
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} mean_config_t;

void allocate_mean_local_context(rt_function_t *f);
void free_mean_local_context(rt_function_t *f);
void exec_mean(rt_function_t *f);

// Max
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} max_config_t;

void allocate_max_local_context(rt_function_t *f);
void free_max_local_context(rt_function_t *f);
void exec_max(rt_function_t *f);

// Min
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} min_config_t;

void allocate_min_local_context(rt_function_t *f);
void free_min_local_context(rt_function_t *f);
void exec_min(rt_function_t *f);

// Prod
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} prod_config_t;

void allocate_prod_local_context(rt_function_t *f);
void free_prod_local_context(rt_function_t *f);
void exec_prod(rt_function_t *f);

// ReduceSum

void allocate_reduce_sum_local_context(rt_function_t *f);
void free_reduce_sum_local_context(rt_function_t *f);
void exec_reduce_sum(rt_function_t *f);

// ReduceMean

void allocate_reduce_mean_local_context(rt_function_t *f);
void free_reduce_mean_local_context(rt_function_t *f);
void exec_reduce_mean(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
typedef struct {
  uint8_t inplace;
  void *local_context;
} add2_config_t;

void allocate_add2_local_context(rt_function_t *f);
void free_add2_local_context(rt_function_t *f);
void exec_add2(rt_function_t *f);

// BcAdd2

void allocate_bc_add2_local_context(rt_function_t *f);
void free_bc_add2_local_context(rt_function_t *f);
void exec_bc_add2(rt_function_t *f);

// Sub2

void allocate_sub2_local_context(rt_function_t *f);
void free_sub2_local_context(rt_function_t *f);
void exec_sub2(rt_function_t *f);

// Mul2

void allocate_mul2_local_context(rt_function_t *f);
void free_mul2_local_context(rt_function_t *f);
void exec_mul2(rt_function_t *f);

// Div2

void allocate_div2_local_context(rt_function_t *f);
void free_div2_local_context(rt_function_t *f);
void exec_div2(rt_function_t *f);

// Pow2

void allocate_pow2_local_context(rt_function_t *f);
void free_pow2_local_context(rt_function_t *f);
void exec_pow2(rt_function_t *f);

// AddScalar
typedef struct {
  float val;
  void *local_context;
} add_scalar_config_t;

void allocate_add_scalar_local_context(rt_function_t *f);
void free_add_scalar_local_context(rt_function_t *f);
void exec_add_scalar(rt_function_t *f);

// MulScalar
typedef struct {
  float val;
  void *local_context;
} mul_scalar_config_t;

void allocate_mul_scalar_local_context(rt_function_t *f);
void free_mul_scalar_local_context(rt_function_t *f);
void exec_mul_scalar(rt_function_t *f);

// PowScalar
typedef struct {
  float val;
  void *local_context;
} pow_scalar_config_t;

void allocate_pow_scalar_local_context(rt_function_t *f);
void free_pow_scalar_local_context(rt_function_t *f);
void exec_pow_scalar(rt_function_t *f);

// RSubScalar
typedef struct {
  float val;
  void *local_context;
} r_sub_scalar_config_t;

void allocate_r_sub_scalar_local_context(rt_function_t *f);
void free_r_sub_scalar_local_context(rt_function_t *f);
void exec_r_sub_scalar(rt_function_t *f);

// RDivScalar
typedef struct {
  float val;
  void *local_context;
} r_div_scalar_config_t;

void allocate_r_div_scalar_local_context(rt_function_t *f);
void free_r_div_scalar_local_context(rt_function_t *f);
void exec_r_div_scalar(rt_function_t *f);

// RPowScalar
typedef struct {
  float val;
  void *local_context;
} r_pow_scalar_config_t;

void allocate_r_pow_scalar_local_context(rt_function_t *f);
void free_r_pow_scalar_local_context(rt_function_t *f);
void exec_r_pow_scalar(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
typedef struct {
  float alpha;
  void *local_context;
} sign_config_t;

void allocate_sign_local_context(rt_function_t *f);
void free_sign_local_context(rt_function_t *f);
void exec_sign(rt_function_t *f);

// Minimum2

void allocate_minimum2_local_context(rt_function_t *f);
void free_minimum2_local_context(rt_function_t *f);
void exec_minimum2(rt_function_t *f);

// Maximum2

void allocate_maximum2_local_context(rt_function_t *f);
void free_maximum2_local_context(rt_function_t *f);
void exec_maximum2(rt_function_t *f);

// MinimumScalar
typedef struct {
  float val;
  void *local_context;
} minimum_scalar_config_t;

void allocate_minimum_scalar_local_context(rt_function_t *f);
void free_minimum_scalar_local_context(rt_function_t *f);
void exec_minimum_scalar(rt_function_t *f);

// MaximumScalar
typedef struct {
  float val;
  void *local_context;
} maximum_scalar_config_t;

void allocate_maximum_scalar_local_context(rt_function_t *f);
void free_maximum_scalar_local_context(rt_function_t *f);
void exec_maximum_scalar(rt_function_t *f);

// LogicalAnd

void allocate_logical_and_local_context(rt_function_t *f);
void free_logical_and_local_context(rt_function_t *f);
void exec_logical_and(rt_function_t *f);

// LogicalOr

void allocate_logical_or_local_context(rt_function_t *f);
void free_logical_or_local_context(rt_function_t *f);
void exec_logical_or(rt_function_t *f);

// LogicalXor

void allocate_logical_xor_local_context(rt_function_t *f);
void free_logical_xor_local_context(rt_function_t *f);
void exec_logical_xor(rt_function_t *f);

// Equal

void allocate_equal_local_context(rt_function_t *f);
void free_equal_local_context(rt_function_t *f);
void exec_equal(rt_function_t *f);

// NotEqual

void allocate_not_equal_local_context(rt_function_t *f);
void free_not_equal_local_context(rt_function_t *f);
void exec_not_equal(rt_function_t *f);

// GreaterEqual

void allocate_greater_equal_local_context(rt_function_t *f);
void free_greater_equal_local_context(rt_function_t *f);
void exec_greater_equal(rt_function_t *f);

// Greater

void allocate_greater_local_context(rt_function_t *f);
void free_greater_local_context(rt_function_t *f);
void exec_greater(rt_function_t *f);

// LessEqual

void allocate_less_equal_local_context(rt_function_t *f);
void free_less_equal_local_context(rt_function_t *f);
void exec_less_equal(rt_function_t *f);

// Less

void allocate_less_local_context(rt_function_t *f);
void free_less_local_context(rt_function_t *f);
void exec_less(rt_function_t *f);

// LogicalAndScalar
typedef struct {
  uint8_t val;
  void *local_context;
} logical_and_scalar_config_t;

void allocate_logical_and_scalar_local_context(rt_function_t *f);
void free_logical_and_scalar_local_context(rt_function_t *f);
void exec_logical_and_scalar(rt_function_t *f);

// LogicalOrScalar
typedef struct {
  uint8_t val;
  void *local_context;
} logical_or_scalar_config_t;

void allocate_logical_or_scalar_local_context(rt_function_t *f);
void free_logical_or_scalar_local_context(rt_function_t *f);
void exec_logical_or_scalar(rt_function_t *f);

// LogicalXorScalar
typedef struct {
  uint8_t val;
  void *local_context;
} logical_xor_scalar_config_t;

void allocate_logical_xor_scalar_local_context(rt_function_t *f);
void free_logical_xor_scalar_local_context(rt_function_t *f);
void exec_logical_xor_scalar(rt_function_t *f);

// EqualScalar
typedef struct {
  float val;
  void *local_context;
} equal_scalar_config_t;

void allocate_equal_scalar_local_context(rt_function_t *f);
void free_equal_scalar_local_context(rt_function_t *f);
void exec_equal_scalar(rt_function_t *f);

// NotEqualScalar
typedef struct {
  float val;
  void *local_context;
} not_equal_scalar_config_t;

void allocate_not_equal_scalar_local_context(rt_function_t *f);
void free_not_equal_scalar_local_context(rt_function_t *f);
void exec_not_equal_scalar(rt_function_t *f);

// GreaterEqualScalar
typedef struct {
  float val;
  void *local_context;
} greater_equal_scalar_config_t;

void allocate_greater_equal_scalar_local_context(rt_function_t *f);
void free_greater_equal_scalar_local_context(rt_function_t *f);
void exec_greater_equal_scalar(rt_function_t *f);

// GreaterScalar
typedef struct {
  float val;
  void *local_context;
} greater_scalar_config_t;

void allocate_greater_scalar_local_context(rt_function_t *f);
void free_greater_scalar_local_context(rt_function_t *f);
void exec_greater_scalar(rt_function_t *f);

// LessEqualScalar
typedef struct {
  float val;
  void *local_context;
} less_equal_scalar_config_t;

void allocate_less_equal_scalar_local_context(rt_function_t *f);
void free_less_equal_scalar_local_context(rt_function_t *f);
void exec_less_equal_scalar(rt_function_t *f);

// LessScalar
typedef struct {
  float val;
  void *local_context;
} less_scalar_config_t;

void allocate_less_scalar_local_context(rt_function_t *f);
void free_less_scalar_local_context(rt_function_t *f);
void exec_less_scalar(rt_function_t *f);

// LogicalNot

void allocate_logical_not_local_context(rt_function_t *f);
void free_logical_not_local_context(rt_function_t *f);
void exec_logical_not(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
typedef struct {
  float val;
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} constant_config_t;

void allocate_constant_local_context(rt_function_t *f);
void free_constant_local_context(rt_function_t *f);
void exec_constant(rt_function_t *f);

// Abs

void allocate_abs_local_context(rt_function_t *f);
void free_abs_local_context(rt_function_t *f);
void exec_abs(rt_function_t *f);

// Exp

void allocate_exp_local_context(rt_function_t *f);
void free_exp_local_context(rt_function_t *f);
void exec_exp(rt_function_t *f);

// Log

void allocate_log_local_context(rt_function_t *f);
void free_log_local_context(rt_function_t *f);
void exec_log(rt_function_t *f);

// Identity

void allocate_identity_local_context(rt_function_t *f);
void free_identity_local_context(rt_function_t *f);
void exec_identity(rt_function_t *f);

// BatchMatmul
typedef struct {
  uint8_t transpose_a;
  uint8_t transpose_b;
  void *local_context;
} batch_matmul_config_t;

void allocate_batch_matmul_local_context(rt_function_t *f);
void free_batch_matmul_local_context(rt_function_t *f);
void exec_batch_matmul(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
typedef struct {
  int32_t axis;
  void *local_context;
} concatenate_config_t;

void allocate_concatenate_local_context(rt_function_t *f);
void free_concatenate_local_context(rt_function_t *f);
void exec_concatenate(rt_function_t *f);

// Split
typedef struct {
  int32_t axis;
  void *local_context;
} split_config_t;

void allocate_split_local_context(rt_function_t *f);
void free_split_local_context(rt_function_t *f);
void exec_split(rt_function_t *f);

// Stack
typedef struct {
  int32_t axis;
  void *local_context;
} stack_config_t;

void allocate_stack_local_context(rt_function_t *f);
void free_stack_local_context(rt_function_t *f);
void exec_stack(rt_function_t *f);

// Slice
typedef struct {
  rt_list_t start; ///< Original type is [repeated int64]
  rt_list_t stop;  ///< Original type is [repeated int64]
  rt_list_t step;  ///< Original type is [repeated int64]
  void *local_context;
} slice_config_t;

void allocate_slice_local_context(rt_function_t *f);
void free_slice_local_context(rt_function_t *f);
void exec_slice(rt_function_t *f);

// Transpose
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *local_context;
} transpose_config_t;

void allocate_transpose_local_context(rt_function_t *f);
void free_transpose_local_context(rt_function_t *f);
void exec_transpose(rt_function_t *f);

// Broadcast
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} broadcast_config_t;

void allocate_broadcast_local_context(rt_function_t *f);
void free_broadcast_local_context(rt_function_t *f);
void exec_broadcast(rt_function_t *f);

// OneHot
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} one_hot_config_t;

void allocate_one_hot_local_context(rt_function_t *f);
void free_one_hot_local_context(rt_function_t *f);
void exec_one_hot(rt_function_t *f);

// Flip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *local_context;
} flip_config_t;

void allocate_flip_local_context(rt_function_t *f);
void free_flip_local_context(rt_function_t *f);
void exec_flip(rt_function_t *f);

// Shift
typedef enum {
  SHIFT_BORDER_MODE_NEAREST,
  SHIFT_BORDER_MODE_REFLECT,
  END_OF_SHIFT_BORDER_MODE
} shift_border_mode_value_t;

typedef struct {
  rt_list_t shifts; ///< Original type is [repeated int64]
  shift_border_mode_value_t border_mode;
  void *local_context;
} shift_config_t;

void allocate_shift_local_context(rt_function_t *f);
void free_shift_local_context(rt_function_t *f);
void exec_shift(rt_function_t *f);

// Reshape
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} reshape_config_t;

void allocate_reshape_local_context(rt_function_t *f);
void free_reshape_local_context(rt_function_t *f);
void exec_reshape(rt_function_t *f);

// MatrixDiag

void allocate_matrix_diag_local_context(rt_function_t *f);
void free_matrix_diag_local_context(rt_function_t *f);
void exec_matrix_diag(rt_function_t *f);

// MatrixDiagPart

void allocate_matrix_diag_part_local_context(rt_function_t *f);
void free_matrix_diag_part_local_context(rt_function_t *f);
void exec_matrix_diag_part(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
typedef struct {
  float p;
  int32_t seed;
  void *local_context;
} dropout_config_t;

void allocate_dropout_local_context(rt_function_t *f);
void free_dropout_local_context(rt_function_t *f);
void exec_dropout(rt_function_t *f);

// Rand
typedef struct {
  float low;
  float high;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *local_context;
} rand_config_t;

void allocate_rand_local_context(rt_function_t *f);
void free_rand_local_context(rt_function_t *f);
void exec_rand(rt_function_t *f);

// Randint
typedef struct {
  int32_t low;
  int32_t high;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *local_context;
} randint_config_t;

void allocate_randint_local_context(rt_function_t *f);
void free_randint_local_context(rt_function_t *f);
void exec_randint(rt_function_t *f);

// Randn
typedef struct {
  float mu;
  float sigma;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *local_context;
} randn_config_t;

void allocate_randn_local_context(rt_function_t *f);
void free_randn_local_context(rt_function_t *f);
void exec_randn(rt_function_t *f);

// RandomCrop
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  int32_t base_axis;
  int32_t seed;
  void *local_context;
} random_crop_config_t;

void allocate_random_crop_local_context(rt_function_t *f);
void free_random_crop_local_context(rt_function_t *f);
void exec_random_crop(rt_function_t *f);

// RandomFlip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  int32_t base_axis;
  int32_t seed;
  void *local_context;
} random_flip_config_t;

void allocate_random_flip_local_context(rt_function_t *f);
void free_random_flip_local_context(rt_function_t *f);
void exec_random_flip(rt_function_t *f);

// RandomShift
typedef enum {
  RANDOM_SHIFT_BORDER_MODE_NEAREST,
  RANDOM_SHIFT_BORDER_MODE_REFLECT,
  END_OF_RANDOM_SHIFT_BORDER_MODE
} random_shift_border_mode_value_t;

typedef struct {
  rt_list_t shifts; ///< Original type is [repeated int64]
  random_shift_border_mode_value_t border_mode;
  int32_t base_axis;
  int32_t seed;
  void *local_context;
} random_shift_config_t;

void allocate_random_shift_local_context(rt_function_t *f);
void free_random_shift_local_context(rt_function_t *f);
void exec_random_shift(rt_function_t *f);

// ImageAugmentation
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  rt_list_t pad;   ///< Original type is [Shape]
  float min_scale;
  float max_scale;
  float angle;
  float aspect_ratio;
  float distortion;
  uint8_t flip_lr;
  uint8_t flip_ud;
  float brightness;
  uint8_t brightness_each;
  float contrast;
  float contrast_center;
  uint8_t contrast_each;
  float noise;
  int32_t seed;
  void *local_context;
} image_augmentation_config_t;

void allocate_image_augmentation_local_context(rt_function_t *f);
void free_image_augmentation_local_context(rt_function_t *f);
void exec_image_augmentation(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy

void allocate_sigmoid_cross_entropy_local_context(rt_function_t *f);
void free_sigmoid_cross_entropy_local_context(rt_function_t *f);
void exec_sigmoid_cross_entropy(rt_function_t *f);

// BinaryCrossEntropy

void allocate_binary_cross_entropy_local_context(rt_function_t *f);
void free_binary_cross_entropy_local_context(rt_function_t *f);
void exec_binary_cross_entropy(rt_function_t *f);

// SoftmaxCrossEntropy
typedef struct {
  int32_t axis;
  void *local_context;
} softmax_cross_entropy_config_t;

void allocate_softmax_cross_entropy_local_context(rt_function_t *f);
void free_softmax_cross_entropy_local_context(rt_function_t *f);
void exec_softmax_cross_entropy(rt_function_t *f);

// CategoricalCrossEntropy
typedef struct {
  int32_t axis;
  void *local_context;
} categorical_cross_entropy_config_t;

void allocate_categorical_cross_entropy_local_context(rt_function_t *f);
void free_categorical_cross_entropy_local_context(rt_function_t *f);
void exec_categorical_cross_entropy(rt_function_t *f);

// SquaredError

void allocate_squared_error_local_context(rt_function_t *f);
void free_squared_error_local_context(rt_function_t *f);
void exec_squared_error(rt_function_t *f);

// AbsoluteError

void allocate_absolute_error_local_context(rt_function_t *f);
void free_absolute_error_local_context(rt_function_t *f);
void exec_absolute_error(rt_function_t *f);

// HuberLoss
typedef struct {
  float delta;
  void *local_context;
} huber_loss_config_t;

void allocate_huber_loss_local_context(rt_function_t *f);
void free_huber_loss_local_context(rt_function_t *f);
void exec_huber_loss(rt_function_t *f);

// EpsilonInsensitiveLoss
typedef struct {
  float epsilon;
  void *local_context;
} epsilon_insensitive_loss_config_t;

void allocate_epsilon_insensitive_loss_local_context(rt_function_t *f);
void free_epsilon_insensitive_loss_local_context(rt_function_t *f);
void exec_epsilon_insensitive_loss(rt_function_t *f);

// KLMultinomial
typedef struct {
  int32_t base_axis;
  void *local_context;
} kl_multinomial_config_t;

void allocate_kl_multinomial_local_context(rt_function_t *f);
void free_kl_multinomial_local_context(rt_function_t *f);
void exec_kl_multinomial(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid

void allocate_binary_sigmoid_local_context(rt_function_t *f);
void free_binary_sigmoid_local_context(rt_function_t *f);
void exec_binary_sigmoid(rt_function_t *f);

// BinaryTanh

void allocate_binary_tanh_local_context(rt_function_t *f);
void free_binary_tanh_local_context(rt_function_t *f);
void exec_binary_tanh(rt_function_t *f);

// BinaryConnectAffine
typedef struct {
  int32_t base_axis;
  void *local_context;
} binary_connect_affine_config_t;

void allocate_binary_connect_affine_local_context(rt_function_t *f);
void free_binary_connect_affine_local_context(rt_function_t *f);
void exec_binary_connect_affine(rt_function_t *f);

// BinaryConnectConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} binary_connect_convolution_config_t;

void allocate_binary_connect_convolution_local_context(rt_function_t *f);
void free_binary_connect_convolution_local_context(rt_function_t *f);
void exec_binary_connect_convolution(rt_function_t *f);

// BinaryWeightAffine
typedef struct {
  int32_t base_axis;
  void *local_context;
} binary_weight_affine_config_t;

void allocate_binary_weight_affine_local_context(rt_function_t *f);
void free_binary_weight_affine_local_context(rt_function_t *f);
void exec_binary_weight_affine(rt_function_t *f);

// BinaryWeightConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} binary_weight_convolution_config_t;

void allocate_binary_weight_convolution_local_context(rt_function_t *f);
void free_binary_weight_convolution_local_context(rt_function_t *f);
void exec_binary_weight_convolution(rt_function_t *f);

// INQAffine
typedef enum {
  INQ_AFFINE_SELECTION_ALGORITHM_LARGEST_ABS,
  INQ_AFFINE_SELECTION_ALGORITHM_RANDOM,
  END_OF_INQ_AFFINE_SELECTION_ALGORITHM
} inq_affine_selection_algorithm_value_t;

typedef struct {
  int32_t base_axis;
  int32_t num_bits;
  rt_list_t inq_iterations; ///< Original type is [repeated int64]
  inq_affine_selection_algorithm_value_t selection_algorithm;
  int32_t seed;
  void *local_context;
} inq_affine_config_t;

void allocate_inq_affine_local_context(rt_function_t *f);
void free_inq_affine_local_context(rt_function_t *f);
void exec_inq_affine(rt_function_t *f);

// INQConvolution
typedef enum {
  INQ_CONVOLUTION_SELECTION_ALGORITHM_LARGEST_ABS,
  INQ_CONVOLUTION_SELECTION_ALGORITHM_RANDOM,
  END_OF_INQ_CONVOLUTION_SELECTION_ALGORITHM
} inq_convolution_selection_algorithm_value_t;

typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  int32_t num_bits;
  rt_list_t inq_iterations; ///< Original type is [repeated int64]
  inq_convolution_selection_algorithm_value_t selection_algorithm;
  int32_t seed;
  void *local_context;
} inq_convolution_config_t;

void allocate_inq_convolution_local_context(rt_function_t *f);
void free_inq_convolution_local_context(rt_function_t *f);
void exec_inq_convolution(rt_function_t *f);

// FixedPointQuantize
typedef struct {
  uint8_t sign;
  int32_t n;
  float delta;
  uint8_t ste_fine_grained;
  void *local_context;
} fixed_point_quantize_config_t;

void allocate_fixed_point_quantize_local_context(rt_function_t *f);
void free_fixed_point_quantize_local_context(rt_function_t *f);
void exec_fixed_point_quantize(rt_function_t *f);

// Pow2Quantize
typedef struct {
  uint8_t sign;
  uint8_t with_zero;
  int32_t n;
  int32_t m;
  uint8_t ste_fine_grained;
  void *local_context;
} pow2_quantize_config_t;

void allocate_pow2_quantize_local_context(rt_function_t *f);
void free_pow2_quantize_local_context(rt_function_t *f);
void exec_pow2_quantize(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
typedef struct {
  int32_t axis;
  int32_t n;
  void *local_context;
} top_n_error_config_t;

void allocate_top_n_error_local_context(rt_function_t *f);
void free_top_n_error_local_context(rt_function_t *f);
void exec_top_n_error(rt_function_t *f);

// BinaryError

void allocate_binary_error_local_context(rt_function_t *f);
void free_binary_error_local_context(rt_function_t *f);
void exec_binary_error(rt_function_t *f);

// ConfusionMatrix
typedef struct {
  int32_t axis;
  void *local_context;
} confusion_matrix_config_t;

void allocate_confusion_matrix_local_context(rt_function_t *f);
void free_confusion_matrix_local_context(rt_function_t *f);
void exec_confusion_matrix(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
typedef struct {
  int32_t base_axis;
  float eps;
  void *local_context;
} vat_noise_config_t;

void allocate_vat_noise_local_context(rt_function_t *f);
void free_vat_noise_local_context(rt_function_t *f);
void exec_vat_noise(rt_function_t *f);

// Unlink

void allocate_unlink_local_context(rt_function_t *f);
void free_unlink_local_context(rt_function_t *f);
void exec_unlink(rt_function_t *f);

// Sink
typedef struct {
  uint8_t one_input_grad;
  void *local_context;
} sink_config_t;

void allocate_sink_local_context(rt_function_t *f);
void free_sink_local_context(rt_function_t *f);
void exec_sink(rt_function_t *f);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // H_FUNCTIONS_H__
