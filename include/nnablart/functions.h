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
// *WARNING*
// THIS FILE IS AUTO-GENERATED DUMMY CODE BY CODE GENERATOR.

#ifndef H_FUNCTIONS_H__
#define H_FUNCTIONS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdio.h>

#include <nnablart/network.h>

typedef enum {
  RT_FUNCTION_ERROR_UNIMPLEMENTED = -999,   ///< Invalid shape. (-999)
  RT_FUNCTION_ERROR_MALLOC,                 ///< Memory allocation error. (-998)
  RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS,  ///< Invalid number of inputs.(-997)
  RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS, ///< Invalid number of outputs.
                                            ///(-996)
  RT_FUNCTION_ERROR_INVALID_SHAPE,          ///< Invalid shape. (-995)
  RT_FUNCTION_ERROR_NOERROR = 0             ///< No error. (0)
} rt_function_error_t;

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

typedef struct {
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

  void *local_context;
} rt_function_t;

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

// Affine
typedef struct {
  int32_t base_axis;
  void *private;
} affine_local_context_t;

rt_function_error_t allocate_affine_local_context(rt_function_t *f);
rt_function_error_t free_affine_local_context(rt_function_t *f);
rt_function_error_t exec_affine(rt_function_t *f);

// Convolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *private;
} convolution_local_context_t;

rt_function_error_t allocate_convolution_local_context(rt_function_t *f);
rt_function_error_t free_convolution_local_context(rt_function_t *f);
rt_function_error_t exec_convolution(rt_function_t *f);

// DepthwiseConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t multiplier;
  void *private;
} depthwise_convolution_local_context_t;

rt_function_error_t
allocate_depthwise_convolution_local_context(rt_function_t *f);
rt_function_error_t free_depthwise_convolution_local_context(rt_function_t *f);
rt_function_error_t exec_depthwise_convolution(rt_function_t *f);

// Deconvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *private;
} deconvolution_local_context_t;

rt_function_error_t allocate_deconvolution_local_context(rt_function_t *f);
rt_function_error_t free_deconvolution_local_context(rt_function_t *f);
rt_function_error_t exec_deconvolution(rt_function_t *f);

// MaxPooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  void *private;
} max_pooling_local_context_t;

rt_function_error_t allocate_max_pooling_local_context(rt_function_t *f);
rt_function_error_t free_max_pooling_local_context(rt_function_t *f);
rt_function_error_t exec_max_pooling(rt_function_t *f);

// AveragePooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  uint8_t including_pad;
  void *private;
} average_pooling_local_context_t;

rt_function_error_t allocate_average_pooling_local_context(rt_function_t *f);
rt_function_error_t free_average_pooling_local_context(rt_function_t *f);
rt_function_error_t exec_average_pooling(rt_function_t *f);

// GlobalAveragePooling

rt_function_error_t
allocate_global_average_pooling_local_context(rt_function_t *f);
rt_function_error_t free_global_average_pooling_local_context(rt_function_t *f);
rt_function_error_t exec_global_average_pooling(rt_function_t *f);

// SumPooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  void *private;
} sum_pooling_local_context_t;

rt_function_error_t allocate_sum_pooling_local_context(rt_function_t *f);
rt_function_error_t free_sum_pooling_local_context(rt_function_t *f);
rt_function_error_t exec_sum_pooling(rt_function_t *f);

// Unpooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  void *private;
} unpooling_local_context_t;

rt_function_error_t allocate_unpooling_local_context(rt_function_t *f);
rt_function_error_t free_unpooling_local_context(rt_function_t *f);
rt_function_error_t exec_unpooling(rt_function_t *f);

// Embed

rt_function_error_t allocate_embed_local_context(rt_function_t *f);
rt_function_error_t free_embed_local_context(rt_function_t *f);
rt_function_error_t exec_embed(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Sigmoid

rt_function_error_t allocate_sigmoid_local_context(rt_function_t *f);
rt_function_error_t free_sigmoid_local_context(rt_function_t *f);
rt_function_error_t exec_sigmoid(rt_function_t *f);

// Swish

rt_function_error_t allocate_swish_local_context(rt_function_t *f);
rt_function_error_t free_swish_local_context(rt_function_t *f);
rt_function_error_t exec_swish(rt_function_t *f);

// Tanh

rt_function_error_t allocate_tanh_local_context(rt_function_t *f);
rt_function_error_t free_tanh_local_context(rt_function_t *f);
rt_function_error_t exec_tanh(rt_function_t *f);

// ReLU
typedef struct {
  uint8_t inplace;
  void *private;
} relu_local_context_t;

rt_function_error_t allocate_relu_local_context(rt_function_t *f);
rt_function_error_t free_relu_local_context(rt_function_t *f);
rt_function_error_t exec_relu(rt_function_t *f);

// LeakyReLU
typedef struct {
  float alpha;
  void *private;
} leaky_relu_local_context_t;

rt_function_error_t allocate_leaky_relu_local_context(rt_function_t *f);
rt_function_error_t free_leaky_relu_local_context(rt_function_t *f);
rt_function_error_t exec_leaky_relu(rt_function_t *f);

// Softmax
typedef struct {
  int32_t axis;
  void *private;
} softmax_local_context_t;

rt_function_error_t allocate_softmax_local_context(rt_function_t *f);
rt_function_error_t free_softmax_local_context(rt_function_t *f);
rt_function_error_t exec_softmax(rt_function_t *f);

// ELU
typedef struct {
  float alpha;
  void *private;
} elu_local_context_t;

rt_function_error_t allocate_elu_local_context(rt_function_t *f);
rt_function_error_t free_elu_local_context(rt_function_t *f);
rt_function_error_t exec_elu(rt_function_t *f);

// SELU
typedef struct {
  float scale;
  float alpha;
  void *private;
} selu_local_context_t;

rt_function_error_t allocate_selu_local_context(rt_function_t *f);
rt_function_error_t free_selu_local_context(rt_function_t *f);
rt_function_error_t exec_selu(rt_function_t *f);

// CReLU
typedef struct {
  int32_t axis;
  void *private;
} crelu_local_context_t;

rt_function_error_t allocate_crelu_local_context(rt_function_t *f);
rt_function_error_t free_crelu_local_context(rt_function_t *f);
rt_function_error_t exec_crelu(rt_function_t *f);

// CELU
typedef struct {
  float alpha;
  int32_t axis;
  void *private;
} celu_local_context_t;

rt_function_error_t allocate_celu_local_context(rt_function_t *f);
rt_function_error_t free_celu_local_context(rt_function_t *f);
rt_function_error_t exec_celu(rt_function_t *f);

// PReLU
typedef struct {
  int32_t base_axis;
  void *private;
} prelu_local_context_t;

rt_function_error_t allocate_prelu_local_context(rt_function_t *f);
rt_function_error_t free_prelu_local_context(rt_function_t *f);
rt_function_error_t exec_prelu(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  float decay_rate;
  float eps;
  uint8_t batch_stat;
  void *private;
} batch_normalization_local_context_t;

rt_function_error_t
allocate_batch_normalization_local_context(rt_function_t *f);
rt_function_error_t free_batch_normalization_local_context(rt_function_t *f);
rt_function_error_t exec_batch_normalization(rt_function_t *f);

// MeanSubtraction
typedef struct {
  int32_t base_axis;
  uint8_t update_running_mean;
  void *private;
} mean_subtraction_local_context_t;

rt_function_error_t allocate_mean_subtraction_local_context(rt_function_t *f);
rt_function_error_t free_mean_subtraction_local_context(rt_function_t *f);
rt_function_error_t exec_mean_subtraction(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *private;
} sum_local_context_t;

rt_function_error_t allocate_sum_local_context(rt_function_t *f);
rt_function_error_t free_sum_local_context(rt_function_t *f);
rt_function_error_t exec_sum(rt_function_t *f);

// Mean
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *private;
} mean_local_context_t;

rt_function_error_t allocate_mean_local_context(rt_function_t *f);
rt_function_error_t free_mean_local_context(rt_function_t *f);
rt_function_error_t exec_mean(rt_function_t *f);

// Max
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *private;
} max_local_context_t;

rt_function_error_t allocate_max_local_context(rt_function_t *f);
rt_function_error_t free_max_local_context(rt_function_t *f);
rt_function_error_t exec_max(rt_function_t *f);

// Min
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *private;
} min_local_context_t;

rt_function_error_t allocate_min_local_context(rt_function_t *f);
rt_function_error_t free_min_local_context(rt_function_t *f);
rt_function_error_t exec_min(rt_function_t *f);

// Prod
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *private;
} prod_local_context_t;

rt_function_error_t allocate_prod_local_context(rt_function_t *f);
rt_function_error_t free_prod_local_context(rt_function_t *f);
rt_function_error_t exec_prod(rt_function_t *f);

// ReduceSum

rt_function_error_t allocate_reduce_sum_local_context(rt_function_t *f);
rt_function_error_t free_reduce_sum_local_context(rt_function_t *f);
rt_function_error_t exec_reduce_sum(rt_function_t *f);

// ReduceMean

rt_function_error_t allocate_reduce_mean_local_context(rt_function_t *f);
rt_function_error_t free_reduce_mean_local_context(rt_function_t *f);
rt_function_error_t exec_reduce_mean(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
typedef struct {
  uint8_t inplace;
  void *private;
} add2_local_context_t;

rt_function_error_t allocate_add2_local_context(rt_function_t *f);
rt_function_error_t free_add2_local_context(rt_function_t *f);
rt_function_error_t exec_add2(rt_function_t *f);

// BcAdd2

rt_function_error_t allocate_bc_add2_local_context(rt_function_t *f);
rt_function_error_t free_bc_add2_local_context(rt_function_t *f);
rt_function_error_t exec_bc_add2(rt_function_t *f);

// Sub2

rt_function_error_t allocate_sub2_local_context(rt_function_t *f);
rt_function_error_t free_sub2_local_context(rt_function_t *f);
rt_function_error_t exec_sub2(rt_function_t *f);

// Mul2

rt_function_error_t allocate_mul2_local_context(rt_function_t *f);
rt_function_error_t free_mul2_local_context(rt_function_t *f);
rt_function_error_t exec_mul2(rt_function_t *f);

// Div2

rt_function_error_t allocate_div2_local_context(rt_function_t *f);
rt_function_error_t free_div2_local_context(rt_function_t *f);
rt_function_error_t exec_div2(rt_function_t *f);

// Pow2

rt_function_error_t allocate_pow2_local_context(rt_function_t *f);
rt_function_error_t free_pow2_local_context(rt_function_t *f);
rt_function_error_t exec_pow2(rt_function_t *f);

// AddScalar
typedef struct {
  float val;
  void *private;
} add_scalar_local_context_t;

rt_function_error_t allocate_add_scalar_local_context(rt_function_t *f);
rt_function_error_t free_add_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_add_scalar(rt_function_t *f);

// MulScalar
typedef struct {
  float val;
  void *private;
} mul_scalar_local_context_t;

rt_function_error_t allocate_mul_scalar_local_context(rt_function_t *f);
rt_function_error_t free_mul_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_mul_scalar(rt_function_t *f);

// PowScalar
typedef struct {
  float val;
  void *private;
} pow_scalar_local_context_t;

rt_function_error_t allocate_pow_scalar_local_context(rt_function_t *f);
rt_function_error_t free_pow_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_pow_scalar(rt_function_t *f);

// RSubScalar
typedef struct {
  float val;
  void *private;
} r_sub_scalar_local_context_t;

rt_function_error_t allocate_r_sub_scalar_local_context(rt_function_t *f);
rt_function_error_t free_r_sub_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_r_sub_scalar(rt_function_t *f);

// RDivScalar
typedef struct {
  float val;
  void *private;
} r_div_scalar_local_context_t;

rt_function_error_t allocate_r_div_scalar_local_context(rt_function_t *f);
rt_function_error_t free_r_div_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_r_div_scalar(rt_function_t *f);

// RPowScalar
typedef struct {
  float val;
  void *private;
} r_pow_scalar_local_context_t;

rt_function_error_t allocate_r_pow_scalar_local_context(rt_function_t *f);
rt_function_error_t free_r_pow_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_r_pow_scalar(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
typedef struct {
  float alpha;
  void *private;
} sign_local_context_t;

rt_function_error_t allocate_sign_local_context(rt_function_t *f);
rt_function_error_t free_sign_local_context(rt_function_t *f);
rt_function_error_t exec_sign(rt_function_t *f);

// Minimum2

rt_function_error_t allocate_minimum2_local_context(rt_function_t *f);
rt_function_error_t free_minimum2_local_context(rt_function_t *f);
rt_function_error_t exec_minimum2(rt_function_t *f);

// Maximum2

rt_function_error_t allocate_maximum2_local_context(rt_function_t *f);
rt_function_error_t free_maximum2_local_context(rt_function_t *f);
rt_function_error_t exec_maximum2(rt_function_t *f);

// MinimumScalar
typedef struct {
  float val;
  void *private;
} minimum_scalar_local_context_t;

rt_function_error_t allocate_minimum_scalar_local_context(rt_function_t *f);
rt_function_error_t free_minimum_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_minimum_scalar(rt_function_t *f);

// MaximumScalar
typedef struct {
  float val;
  void *private;
} maximum_scalar_local_context_t;

rt_function_error_t allocate_maximum_scalar_local_context(rt_function_t *f);
rt_function_error_t free_maximum_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_maximum_scalar(rt_function_t *f);

// LogicalAnd

rt_function_error_t allocate_logical_and_local_context(rt_function_t *f);
rt_function_error_t free_logical_and_local_context(rt_function_t *f);
rt_function_error_t exec_logical_and(rt_function_t *f);

// LogicalOr

rt_function_error_t allocate_logical_or_local_context(rt_function_t *f);
rt_function_error_t free_logical_or_local_context(rt_function_t *f);
rt_function_error_t exec_logical_or(rt_function_t *f);

// LogicalXor

rt_function_error_t allocate_logical_xor_local_context(rt_function_t *f);
rt_function_error_t free_logical_xor_local_context(rt_function_t *f);
rt_function_error_t exec_logical_xor(rt_function_t *f);

// Equal

rt_function_error_t allocate_equal_local_context(rt_function_t *f);
rt_function_error_t free_equal_local_context(rt_function_t *f);
rt_function_error_t exec_equal(rt_function_t *f);

// NotEqual

rt_function_error_t allocate_not_equal_local_context(rt_function_t *f);
rt_function_error_t free_not_equal_local_context(rt_function_t *f);
rt_function_error_t exec_not_equal(rt_function_t *f);

// GreaterEqual

rt_function_error_t allocate_greater_equal_local_context(rt_function_t *f);
rt_function_error_t free_greater_equal_local_context(rt_function_t *f);
rt_function_error_t exec_greater_equal(rt_function_t *f);

// Greater

rt_function_error_t allocate_greater_local_context(rt_function_t *f);
rt_function_error_t free_greater_local_context(rt_function_t *f);
rt_function_error_t exec_greater(rt_function_t *f);

// LessEqual

rt_function_error_t allocate_less_equal_local_context(rt_function_t *f);
rt_function_error_t free_less_equal_local_context(rt_function_t *f);
rt_function_error_t exec_less_equal(rt_function_t *f);

// Less

rt_function_error_t allocate_less_local_context(rt_function_t *f);
rt_function_error_t free_less_local_context(rt_function_t *f);
rt_function_error_t exec_less(rt_function_t *f);

// LogicalAndScalar
typedef struct {
  uint8_t val;
  void *private;
} logical_and_scalar_local_context_t;

rt_function_error_t allocate_logical_and_scalar_local_context(rt_function_t *f);
rt_function_error_t free_logical_and_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_logical_and_scalar(rt_function_t *f);

// LogicalOrScalar
typedef struct {
  uint8_t val;
  void *private;
} logical_or_scalar_local_context_t;

rt_function_error_t allocate_logical_or_scalar_local_context(rt_function_t *f);
rt_function_error_t free_logical_or_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_logical_or_scalar(rt_function_t *f);

// LogicalXorScalar
typedef struct {
  uint8_t val;
  void *private;
} logical_xor_scalar_local_context_t;

rt_function_error_t allocate_logical_xor_scalar_local_context(rt_function_t *f);
rt_function_error_t free_logical_xor_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_logical_xor_scalar(rt_function_t *f);

// EqualScalar
typedef struct {
  float val;
  void *private;
} equal_scalar_local_context_t;

rt_function_error_t allocate_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t free_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_equal_scalar(rt_function_t *f);

// NotEqualScalar
typedef struct {
  float val;
  void *private;
} not_equal_scalar_local_context_t;

rt_function_error_t allocate_not_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t free_not_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_not_equal_scalar(rt_function_t *f);

// GreaterEqualScalar
typedef struct {
  float val;
  void *private;
} greater_equal_scalar_local_context_t;

rt_function_error_t
allocate_greater_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t free_greater_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_greater_equal_scalar(rt_function_t *f);

// GreaterScalar
typedef struct {
  float val;
  void *private;
} greater_scalar_local_context_t;

rt_function_error_t allocate_greater_scalar_local_context(rt_function_t *f);
rt_function_error_t free_greater_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_greater_scalar(rt_function_t *f);

// LessEqualScalar
typedef struct {
  float val;
  void *private;
} less_equal_scalar_local_context_t;

rt_function_error_t allocate_less_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t free_less_equal_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_less_equal_scalar(rt_function_t *f);

// LessScalar
typedef struct {
  float val;
  void *private;
} less_scalar_local_context_t;

rt_function_error_t allocate_less_scalar_local_context(rt_function_t *f);
rt_function_error_t free_less_scalar_local_context(rt_function_t *f);
rt_function_error_t exec_less_scalar(rt_function_t *f);

// LogicalNot

rt_function_error_t allocate_logical_not_local_context(rt_function_t *f);
rt_function_error_t free_logical_not_local_context(rt_function_t *f);
rt_function_error_t exec_logical_not(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
typedef struct {
  float val;
  rt_list_t shape; ///< Original type is [Shape]
  void *private;
} constant_local_context_t;

rt_function_error_t allocate_constant_local_context(rt_function_t *f);
rt_function_error_t free_constant_local_context(rt_function_t *f);
rt_function_error_t exec_constant(rt_function_t *f);

// Abs

rt_function_error_t allocate_abs_local_context(rt_function_t *f);
rt_function_error_t free_abs_local_context(rt_function_t *f);
rt_function_error_t exec_abs(rt_function_t *f);

// Exp

rt_function_error_t allocate_exp_local_context(rt_function_t *f);
rt_function_error_t free_exp_local_context(rt_function_t *f);
rt_function_error_t exec_exp(rt_function_t *f);

// Log

rt_function_error_t allocate_log_local_context(rt_function_t *f);
rt_function_error_t free_log_local_context(rt_function_t *f);
rt_function_error_t exec_log(rt_function_t *f);

// Identity

rt_function_error_t allocate_identity_local_context(rt_function_t *f);
rt_function_error_t free_identity_local_context(rt_function_t *f);
rt_function_error_t exec_identity(rt_function_t *f);

// BatchMatmul
typedef struct {
  uint8_t transpose_a;
  uint8_t transpose_b;
  void *private;
} batch_matmul_local_context_t;

rt_function_error_t allocate_batch_matmul_local_context(rt_function_t *f);
rt_function_error_t free_batch_matmul_local_context(rt_function_t *f);
rt_function_error_t exec_batch_matmul(rt_function_t *f);

// Round

rt_function_error_t allocate_round_local_context(rt_function_t *f);
rt_function_error_t free_round_local_context(rt_function_t *f);
rt_function_error_t exec_round(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
typedef struct {
  int32_t axis;
  void *private;
} concatenate_local_context_t;

rt_function_error_t allocate_concatenate_local_context(rt_function_t *f);
rt_function_error_t free_concatenate_local_context(rt_function_t *f);
rt_function_error_t exec_concatenate(rt_function_t *f);

// Split
typedef struct {
  int32_t axis;
  void *private;
} split_local_context_t;

rt_function_error_t allocate_split_local_context(rt_function_t *f);
rt_function_error_t free_split_local_context(rt_function_t *f);
rt_function_error_t exec_split(rt_function_t *f);

// Stack
typedef struct {
  int32_t axis;
  void *private;
} stack_local_context_t;

rt_function_error_t allocate_stack_local_context(rt_function_t *f);
rt_function_error_t free_stack_local_context(rt_function_t *f);
rt_function_error_t exec_stack(rt_function_t *f);

// Slice
typedef struct {
  rt_list_t start; ///< Original type is [repeated int64]
  rt_list_t stop;  ///< Original type is [repeated int64]
  rt_list_t step;  ///< Original type is [repeated int64]
  void *private;
} slice_local_context_t;

rt_function_error_t allocate_slice_local_context(rt_function_t *f);
rt_function_error_t free_slice_local_context(rt_function_t *f);
rt_function_error_t exec_slice(rt_function_t *f);

// Transpose
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *private;
} transpose_local_context_t;

rt_function_error_t allocate_transpose_local_context(rt_function_t *f);
rt_function_error_t free_transpose_local_context(rt_function_t *f);
rt_function_error_t exec_transpose(rt_function_t *f);

// Broadcast
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *private;
} broadcast_local_context_t;

rt_function_error_t allocate_broadcast_local_context(rt_function_t *f);
rt_function_error_t free_broadcast_local_context(rt_function_t *f);
rt_function_error_t exec_broadcast(rt_function_t *f);

// OneHot
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *private;
} one_hot_local_context_t;

rt_function_error_t allocate_one_hot_local_context(rt_function_t *f);
rt_function_error_t free_one_hot_local_context(rt_function_t *f);
rt_function_error_t exec_one_hot(rt_function_t *f);

// Flip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *private;
} flip_local_context_t;

rt_function_error_t allocate_flip_local_context(rt_function_t *f);
rt_function_error_t free_flip_local_context(rt_function_t *f);
rt_function_error_t exec_flip(rt_function_t *f);

// Shift
typedef enum {
  SHIFT_BORDER_MODE_NEAREST,
  SHIFT_BORDER_MODE_REFLECT,
  END_OF_SHIFT_BORDER_MODE
} shift_border_mode_value_t;

typedef struct {
  rt_list_t shifts; ///< Original type is [repeated int64]
  shift_border_mode_value_t border_mode;
  void *private;
} shift_local_context_t;

rt_function_error_t allocate_shift_local_context(rt_function_t *f);
rt_function_error_t free_shift_local_context(rt_function_t *f);
rt_function_error_t exec_shift(rt_function_t *f);

// Reshape
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *private;
} reshape_local_context_t;

rt_function_error_t allocate_reshape_local_context(rt_function_t *f);
rt_function_error_t free_reshape_local_context(rt_function_t *f);
rt_function_error_t exec_reshape(rt_function_t *f);

// MatrixDiag

rt_function_error_t allocate_matrix_diag_local_context(rt_function_t *f);
rt_function_error_t free_matrix_diag_local_context(rt_function_t *f);
rt_function_error_t exec_matrix_diag(rt_function_t *f);

// MatrixDiagPart

rt_function_error_t allocate_matrix_diag_part_local_context(rt_function_t *f);
rt_function_error_t free_matrix_diag_part_local_context(rt_function_t *f);
rt_function_error_t exec_matrix_diag_part(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
typedef struct {
  float p;
  int32_t seed;
  void *private;
} dropout_local_context_t;

rt_function_error_t allocate_dropout_local_context(rt_function_t *f);
rt_function_error_t free_dropout_local_context(rt_function_t *f);
rt_function_error_t exec_dropout(rt_function_t *f);

// Rand
typedef struct {
  float low;
  float high;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *private;
} rand_local_context_t;

rt_function_error_t allocate_rand_local_context(rt_function_t *f);
rt_function_error_t free_rand_local_context(rt_function_t *f);
rt_function_error_t exec_rand(rt_function_t *f);

// Randint
typedef struct {
  int32_t low;
  int32_t high;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *private;
} randint_local_context_t;

rt_function_error_t allocate_randint_local_context(rt_function_t *f);
rt_function_error_t free_randint_local_context(rt_function_t *f);
rt_function_error_t exec_randint(rt_function_t *f);

// Randn
typedef struct {
  float mu;
  float sigma;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *private;
} randn_local_context_t;

rt_function_error_t allocate_randn_local_context(rt_function_t *f);
rt_function_error_t free_randn_local_context(rt_function_t *f);
rt_function_error_t exec_randn(rt_function_t *f);

// RandomCrop
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  int32_t base_axis;
  int32_t seed;
  void *private;
} random_crop_local_context_t;

rt_function_error_t allocate_random_crop_local_context(rt_function_t *f);
rt_function_error_t free_random_crop_local_context(rt_function_t *f);
rt_function_error_t exec_random_crop(rt_function_t *f);

// RandomFlip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  int32_t base_axis;
  int32_t seed;
  void *private;
} random_flip_local_context_t;

rt_function_error_t allocate_random_flip_local_context(rt_function_t *f);
rt_function_error_t free_random_flip_local_context(rt_function_t *f);
rt_function_error_t exec_random_flip(rt_function_t *f);

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
  void *private;
} random_shift_local_context_t;

rt_function_error_t allocate_random_shift_local_context(rt_function_t *f);
rt_function_error_t free_random_shift_local_context(rt_function_t *f);
rt_function_error_t exec_random_shift(rt_function_t *f);

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
  void *private;
} image_augmentation_local_context_t;

rt_function_error_t allocate_image_augmentation_local_context(rt_function_t *f);
rt_function_error_t free_image_augmentation_local_context(rt_function_t *f);
rt_function_error_t exec_image_augmentation(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy

rt_function_error_t
allocate_sigmoid_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t free_sigmoid_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t exec_sigmoid_cross_entropy(rt_function_t *f);

// BinaryCrossEntropy

rt_function_error_t
allocate_binary_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t free_binary_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t exec_binary_cross_entropy(rt_function_t *f);

// SoftmaxCrossEntropy
typedef struct {
  int32_t axis;
  void *private;
} softmax_cross_entropy_local_context_t;

rt_function_error_t
allocate_softmax_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t free_softmax_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t exec_softmax_cross_entropy(rt_function_t *f);

// CategoricalCrossEntropy
typedef struct {
  int32_t axis;
  void *private;
} categorical_cross_entropy_local_context_t;

rt_function_error_t
allocate_categorical_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t
free_categorical_cross_entropy_local_context(rt_function_t *f);
rt_function_error_t exec_categorical_cross_entropy(rt_function_t *f);

// SquaredError

rt_function_error_t allocate_squared_error_local_context(rt_function_t *f);
rt_function_error_t free_squared_error_local_context(rt_function_t *f);
rt_function_error_t exec_squared_error(rt_function_t *f);

// AbsoluteError

rt_function_error_t allocate_absolute_error_local_context(rt_function_t *f);
rt_function_error_t free_absolute_error_local_context(rt_function_t *f);
rt_function_error_t exec_absolute_error(rt_function_t *f);

// HuberLoss
typedef struct {
  float delta;
  void *private;
} huber_loss_local_context_t;

rt_function_error_t allocate_huber_loss_local_context(rt_function_t *f);
rt_function_error_t free_huber_loss_local_context(rt_function_t *f);
rt_function_error_t exec_huber_loss(rt_function_t *f);

// EpsilonInsensitiveLoss
typedef struct {
  float epsilon;
  void *private;
} epsilon_insensitive_loss_local_context_t;

rt_function_error_t
allocate_epsilon_insensitive_loss_local_context(rt_function_t *f);
rt_function_error_t
free_epsilon_insensitive_loss_local_context(rt_function_t *f);
rt_function_error_t exec_epsilon_insensitive_loss(rt_function_t *f);

// KLMultinomial
typedef struct {
  int32_t base_axis;
  void *private;
} kl_multinomial_local_context_t;

rt_function_error_t allocate_kl_multinomial_local_context(rt_function_t *f);
rt_function_error_t free_kl_multinomial_local_context(rt_function_t *f);
rt_function_error_t exec_kl_multinomial(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid

rt_function_error_t allocate_binary_sigmoid_local_context(rt_function_t *f);
rt_function_error_t free_binary_sigmoid_local_context(rt_function_t *f);
rt_function_error_t exec_binary_sigmoid(rt_function_t *f);

// BinaryTanh

rt_function_error_t allocate_binary_tanh_local_context(rt_function_t *f);
rt_function_error_t free_binary_tanh_local_context(rt_function_t *f);
rt_function_error_t exec_binary_tanh(rt_function_t *f);

// BinaryConnectAffine
typedef struct {
  int32_t base_axis;
  void *private;
} binary_connect_affine_local_context_t;

rt_function_error_t
allocate_binary_connect_affine_local_context(rt_function_t *f);
rt_function_error_t free_binary_connect_affine_local_context(rt_function_t *f);
rt_function_error_t exec_binary_connect_affine(rt_function_t *f);

// BinaryConnectConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *private;
} binary_connect_convolution_local_context_t;

rt_function_error_t
allocate_binary_connect_convolution_local_context(rt_function_t *f);
rt_function_error_t
free_binary_connect_convolution_local_context(rt_function_t *f);
rt_function_error_t exec_binary_connect_convolution(rt_function_t *f);

// BinaryWeightAffine
typedef struct {
  int32_t base_axis;
  void *private;
} binary_weight_affine_local_context_t;

rt_function_error_t
allocate_binary_weight_affine_local_context(rt_function_t *f);
rt_function_error_t free_binary_weight_affine_local_context(rt_function_t *f);
rt_function_error_t exec_binary_weight_affine(rt_function_t *f);

// BinaryWeightConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *private;
} binary_weight_convolution_local_context_t;

rt_function_error_t
allocate_binary_weight_convolution_local_context(rt_function_t *f);
rt_function_error_t
free_binary_weight_convolution_local_context(rt_function_t *f);
rt_function_error_t exec_binary_weight_convolution(rt_function_t *f);

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
  void *private;
} inq_affine_local_context_t;

rt_function_error_t allocate_inq_affine_local_context(rt_function_t *f);
rt_function_error_t free_inq_affine_local_context(rt_function_t *f);
rt_function_error_t exec_inq_affine(rt_function_t *f);

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
  void *private;
} inq_convolution_local_context_t;

rt_function_error_t allocate_inq_convolution_local_context(rt_function_t *f);
rt_function_error_t free_inq_convolution_local_context(rt_function_t *f);
rt_function_error_t exec_inq_convolution(rt_function_t *f);

// FixedPointQuantize
typedef struct {
  uint8_t sign;
  int32_t n;
  float delta;
  uint8_t ste_fine_grained;
  void *private;
} fixed_point_quantize_local_context_t;

rt_function_error_t
allocate_fixed_point_quantize_local_context(rt_function_t *f);
rt_function_error_t free_fixed_point_quantize_local_context(rt_function_t *f);
rt_function_error_t exec_fixed_point_quantize(rt_function_t *f);

// Pow2Quantize
typedef struct {
  uint8_t sign;
  uint8_t with_zero;
  int32_t n;
  int32_t m;
  uint8_t ste_fine_grained;
  void *private;
} pow2_quantize_local_context_t;

rt_function_error_t allocate_pow2_quantize_local_context(rt_function_t *f);
rt_function_error_t free_pow2_quantize_local_context(rt_function_t *f);
rt_function_error_t exec_pow2_quantize(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
typedef struct {
  int32_t axis;
  int32_t n;
  void *private;
} top_n_error_local_context_t;

rt_function_error_t allocate_top_n_error_local_context(rt_function_t *f);
rt_function_error_t free_top_n_error_local_context(rt_function_t *f);
rt_function_error_t exec_top_n_error(rt_function_t *f);

// BinaryError

rt_function_error_t allocate_binary_error_local_context(rt_function_t *f);
rt_function_error_t free_binary_error_local_context(rt_function_t *f);
rt_function_error_t exec_binary_error(rt_function_t *f);

// ConfusionMatrix
typedef struct {
  int32_t axis;
  void *private;
} confusion_matrix_local_context_t;

rt_function_error_t allocate_confusion_matrix_local_context(rt_function_t *f);
rt_function_error_t free_confusion_matrix_local_context(rt_function_t *f);
rt_function_error_t exec_confusion_matrix(rt_function_t *f);

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
typedef struct {
  int32_t base_axis;
  float eps;
  void *private;
} vat_noise_local_context_t;

rt_function_error_t allocate_vat_noise_local_context(rt_function_t *f);
rt_function_error_t free_vat_noise_local_context(rt_function_t *f);
rt_function_error_t exec_vat_noise(rt_function_t *f);

// Unlink

rt_function_error_t allocate_unlink_local_context(rt_function_t *f);
rt_function_error_t free_unlink_local_context(rt_function_t *f);
rt_function_error_t exec_unlink(rt_function_t *f);

// Sink
typedef struct {
  uint8_t one_input_grad;
  void *private;
} sink_local_context_t;

rt_function_error_t allocate_sink_local_context(rt_function_t *f);
rt_function_error_t free_sink_local_context(rt_function_t *f);
rt_function_error_t exec_sink(rt_function_t *f);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // H_FUNCTIONS_H__
