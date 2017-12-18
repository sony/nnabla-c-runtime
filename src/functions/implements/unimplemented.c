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

#include <nnablart/functions.h>

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

// Affine
void allocate_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_affine(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Convolution
void allocate_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_convolution(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// DepthwiseConvolution
void allocate_depthwise_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_depthwise_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_depthwise_convolution(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Deconvolution
void allocate_deconvolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_deconvolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_deconvolution(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MaxPooling
void allocate_max_pooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_max_pooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_max_pooling(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// AveragePooling
void allocate_average_pooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_average_pooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_average_pooling(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// SumPooling
void allocate_sum_pooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_sum_pooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_sum_pooling(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Unpooling
void allocate_unpooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_unpooling_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_unpooling(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Embed
void exec_embed(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Sigmoid
void exec_sigmoid(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Swish
void exec_swish(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Tanh
void exec_tanh(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// ReLU
void allocate_relu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_relu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_relu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LeakyReLU
void allocate_leaky_relu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_leaky_relu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_leaky_relu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Softmax
void allocate_softmax_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_softmax_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_softmax(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// ELU
void allocate_elu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_elu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_elu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// SELU
void allocate_selu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_selu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_selu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// CReLU
void allocate_crelu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_crelu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_crelu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// CELU
void allocate_celu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_celu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_celu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// PReLU
void allocate_prelu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_prelu_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_prelu(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
void allocate_batch_normalization_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_batch_normalization_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_batch_normalization(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MeanSubtraction
void allocate_mean_subtraction_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_mean_subtraction_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_mean_subtraction(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
void allocate_sum_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_sum_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_sum(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Mean
void allocate_mean_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_mean_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_mean(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Max
void allocate_max_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_max_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_max(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Min
void allocate_min_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_min_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_min(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Prod
void allocate_prod_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_prod_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_prod(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// ReduceSum
void exec_reduce_sum(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// ReduceMean
void exec_reduce_mean(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
void allocate_add2_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_add2_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_add2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BcAdd2
void exec_bc_add2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Sub2
void exec_sub2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Mul2
void exec_mul2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Div2
void exec_div2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Pow2
void exec_pow2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// AddScalar
void allocate_add_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_add_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_add_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MulScalar
void allocate_mul_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_mul_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_mul_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// PowScalar
void allocate_pow_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_pow_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_pow_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// RSubScalar
void allocate_r_sub_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_r_sub_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_r_sub_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// RDivScalar
void allocate_r_div_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_r_div_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_r_div_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// RPowScalar
void allocate_r_pow_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_r_pow_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_r_pow_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
void allocate_sign_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_sign_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_sign(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Minimum2
void exec_minimum2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Maximum2
void exec_maximum2(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MinimumScalar
void allocate_minimum_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_minimum_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_minimum_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MaximumScalar
void allocate_maximum_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_maximum_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_maximum_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalAnd
void exec_logical_and(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalOr
void exec_logical_or(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalXor
void exec_logical_xor(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Equal
void exec_equal(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// NotEqual
void exec_not_equal(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// GreaterEqual
void exec_greater_equal(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Greater
void exec_greater(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LessEqual
void exec_less_equal(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Less
void exec_less(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalAndScalar
void allocate_logical_and_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_logical_and_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_logical_and_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalOrScalar
void allocate_logical_or_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_logical_or_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_logical_or_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalXorScalar
void allocate_logical_xor_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_logical_xor_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_logical_xor_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// EqualScalar
void allocate_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_equal_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// NotEqualScalar
void allocate_not_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_not_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_not_equal_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// GreaterEqualScalar
void allocate_greater_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_greater_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_greater_equal_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// GreaterScalar
void allocate_greater_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_greater_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_greater_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LessEqualScalar
void allocate_less_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_less_equal_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_less_equal_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LessScalar
void allocate_less_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_less_scalar_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_less_scalar(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// LogicalNot
void exec_logical_not(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
void allocate_constant_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_constant_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_constant(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Abs
void exec_abs(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Exp
void exec_exp(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Log
void exec_log(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Identity
void exec_identity(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BatchMatmul
void allocate_batch_matmul_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_batch_matmul_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_batch_matmul(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
void allocate_concatenate_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_concatenate_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_concatenate(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Split
void allocate_split_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_split_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_split(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Stack
void allocate_stack_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_stack_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_stack(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Slice
void allocate_slice_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_slice_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_slice(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Transpose
void allocate_transpose_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_transpose_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_transpose(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Broadcast
void allocate_broadcast_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_broadcast_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_broadcast(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// OneHot
void allocate_one_hot_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_one_hot_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_one_hot(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Flip
void allocate_flip_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_flip_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_flip(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Shift
void allocate_shift_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_shift_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_shift(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Reshape
void allocate_reshape_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_reshape_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_reshape(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MatrixDiag
void exec_matrix_diag(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// MatrixDiagPart
void exec_matrix_diag_part(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
void allocate_dropout_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_dropout_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_dropout(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Rand
void allocate_rand_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_rand_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_rand(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Randint
void allocate_randint_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_randint_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_randint(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Randn
void allocate_randn_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_randn_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_randn(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// RandomCrop
void allocate_random_crop_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_random_crop_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_random_crop(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// RandomFlip
void allocate_random_flip_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_random_flip_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_random_flip(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// RandomShift
void allocate_random_shift_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_random_shift_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_random_shift(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// ImageAugmentation
void allocate_image_augmentation_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_image_augmentation_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_image_augmentation(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy
void exec_sigmoid_cross_entropy(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryCrossEntropy
void exec_binary_cross_entropy(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// SoftmaxCrossEntropy
void allocate_softmax_cross_entropy_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_softmax_cross_entropy_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_softmax_cross_entropy(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// CategoricalCrossEntropy
void allocate_categorical_cross_entropy_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_categorical_cross_entropy_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_categorical_cross_entropy(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// SquaredError
void exec_squared_error(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// AbsoluteError
void exec_absolute_error(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// HuberLoss
void allocate_huber_loss_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_huber_loss_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_huber_loss(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// EpsilonInsensitiveLoss
void allocate_epsilon_insensitive_loss_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_epsilon_insensitive_loss_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_epsilon_insensitive_loss(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// KLMultinomial
void allocate_kl_multinomial_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_kl_multinomial_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_kl_multinomial(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid
void exec_binary_sigmoid(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryTanh
void exec_binary_tanh(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryConnectAffine
void allocate_binary_connect_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_binary_connect_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_binary_connect_affine(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryConnectConvolution
void allocate_binary_connect_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_binary_connect_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_binary_connect_convolution(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryWeightAffine
void allocate_binary_weight_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_binary_weight_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_binary_weight_affine(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryWeightConvolution
void allocate_binary_weight_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_binary_weight_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_binary_weight_convolution(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// INQAffine
void allocate_inq_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_inq_affine_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_inq_affine(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// INQConvolution
void allocate_inq_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_inq_convolution_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_inq_convolution(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// FixedPointQuantize
void allocate_fixed_point_quantize_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_fixed_point_quantize_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_fixed_point_quantize(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Pow2Quantize
void allocate_pow2_quantize_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_pow2_quantize_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_pow2_quantize(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
void allocate_top_n_error_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_top_n_error_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_top_n_error(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// BinaryError
void exec_binary_error(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// ConfusionMatrix
void allocate_confusion_matrix_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_confusion_matrix_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_confusion_matrix(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
void allocate_vat_noise_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_vat_noise_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_vat_noise(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Unlink
void exec_unlink(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

// Sink
void allocate_sink_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void free_sink_local_context(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}
void exec_sink(rt_function_t *f)
{
  WHOAMI("%s\n", __func__);
}

