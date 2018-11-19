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
// DepthwiseDeconvolution
rt_function_error_t
allocate_depthwise_deconvolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_depthwise_deconvolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_depthwise_deconvolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// GlobalAveragePooling
rt_function_error_t
allocate_global_average_pooling_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_global_average_pooling_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_global_average_pooling(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Embed
rt_function_error_t allocate_embed_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_embed_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_embed(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

rt_function_error_t
allocate_clip_grad_by_value_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_clip_grad_by_value_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_clip_grad_by_value(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_clip_grad_by_norm_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_clip_grad_by_norm_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_clip_grad_by_norm(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Mean
rt_function_error_t allocate_mean_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_mean_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_mean(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Max
rt_function_error_t allocate_max_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_max_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_max(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Min
rt_function_error_t allocate_min_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_min_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_min(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Prod
rt_function_error_t allocate_prod_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_prod_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_prod(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// ReduceSum
rt_function_error_t allocate_reduce_sum_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_reduce_sum_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_reduce_sum(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// ReduceMean
rt_function_error_t allocate_reduce_mean_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_reduce_mean_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_reduce_mean(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// BcAdd2
rt_function_error_t allocate_bc_add2_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_bc_add2_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_bc_add2(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// LogicalAnd
rt_function_error_t allocate_logical_and_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_and_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_and(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LogicalOr
rt_function_error_t allocate_logical_or_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_or_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_or(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LogicalXor
rt_function_error_t allocate_logical_xor_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_xor_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_xor(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Equal
rt_function_error_t allocate_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// NotEqual
rt_function_error_t allocate_not_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_not_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_not_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// GreaterEqual
rt_function_error_t allocate_greater_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Greater
rt_function_error_t allocate_greater_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LessEqual
rt_function_error_t allocate_less_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Less
rt_function_error_t allocate_less_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LogicalAndScalar
rt_function_error_t
allocate_logical_and_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_and_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_and_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LogicalOrScalar
rt_function_error_t allocate_logical_or_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_or_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_or_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LogicalXorScalar
rt_function_error_t
allocate_logical_xor_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_xor_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_xor_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// EqualScalar
rt_function_error_t allocate_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// NotEqualScalar
rt_function_error_t allocate_not_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_not_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_not_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// GreaterEqualScalar
rt_function_error_t
allocate_greater_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// GreaterScalar
rt_function_error_t allocate_greater_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LessEqualScalar
rt_function_error_t allocate_less_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LessScalar
rt_function_error_t allocate_less_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// LogicalNot

rt_function_error_t allocate_logical_not_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_not_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_not(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
rt_function_error_t allocate_constant_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_constant_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_constant(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Arange
rt_function_error_t allocate_arange_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_arange_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_arange(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_sin_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sin_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sin(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_cos_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_cos_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_cos(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_tan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_tan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_tan(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_sinh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sinh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sinh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_cosh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_cosh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_cosh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_asin_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_asin_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_asin(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_acos_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_acos_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_acos(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_atan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_atan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_atan(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_asinh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_asinh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_asinh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_acosh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_acosh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_acosh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_atanh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_atanh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_atanh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Ceil
rt_function_error_t allocate_ceil_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_ceil_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_ceil(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Floor
rt_function_error_t allocate_floor_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_floor_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_floor(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

/// Pad
rt_function_error_t allocate_pad_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t free_pad_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t exec_pad(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Broadcast
rt_function_error_t allocate_broadcast_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_broadcast_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_broadcast(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// BroadcastTo
rt_function_error_t allocate_broadcast_to_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_broadcast_to_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_broadcast_to(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// OneHot
rt_function_error_t allocate_one_hot_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_one_hot_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_one_hot(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Sort
rt_function_error_t allocate_sort_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sort_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sort(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// TopKData
rt_function_error_t allocate_top_k_data_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t free_top_k_data_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t exec_top_k_data(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// TopKGrad
rt_function_error_t allocate_top_k_grad_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t free_top_k_grad_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t exec_top_k_grad(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Rand
rt_function_error_t allocate_rand_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_rand_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_rand(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Randint
rt_function_error_t allocate_randint_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_randint_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_randint(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Randn
rt_function_error_t allocate_randn_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_randn_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_randn(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// RandomCrop
rt_function_error_t allocate_random_crop_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_crop_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_crop(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// RandomFlip
rt_function_error_t allocate_random_flip_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_flip_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_flip(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// RandomShift
rt_function_error_t allocate_random_shift_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_shift_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_shift(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// ImageAugmentation
rt_function_error_t
allocate_image_augmentation_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_image_augmentation_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_image_augmentation(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy

rt_function_error_t
allocate_sigmoid_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sigmoid_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sigmoid_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// BinaryCrossEntropy

rt_function_error_t
allocate_binary_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_binary_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_binary_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// SoftmaxCrossEntropy
rt_function_error_t
allocate_softmax_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_softmax_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_softmax_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// CategoricalCrossEntropy
rt_function_error_t
allocate_categorical_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_categorical_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_categorical_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// SquaredError

rt_function_error_t allocate_squared_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_squared_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_squared_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// AbsoluteError

rt_function_error_t allocate_absolute_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_absolute_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_absolute_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// HuberLoss
rt_function_error_t allocate_huber_loss_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_huber_loss_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_huber_loss(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// EpsilonInsensitiveLoss
rt_function_error_t
allocate_epsilon_insensitive_loss_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_epsilon_insensitive_loss_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_epsilon_insensitive_loss(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// KLMultinomial
rt_function_error_t allocate_kl_multinomial_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_kl_multinomial_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_kl_multinomial(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// INQAffine
rt_function_error_t allocate_inq_affine_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_inq_affine_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_inq_affine(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// INQConvolution
rt_function_error_t allocate_inq_convolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_inq_convolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_inq_convolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// FixedPointQuantize
rt_function_error_t
allocate_fixed_point_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_fixed_point_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_fixed_point_quantize(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Pow2Quantize
rt_function_error_t allocate_pow2_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_pow2_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_pow2_quantize(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Prune
rt_function_error_t allocate_prune_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_prune_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_prune(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Spectral Operation
////////////////////////////////////////////////////////////////////////////////

// Interpolate
rt_function_error_t allocate_interpolate_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_interpolate_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_interpolate(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// FFT
rt_function_error_t allocate_fft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_fft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_fft(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// IFFT
rt_function_error_t allocate_ifft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_ifft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_ifft(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
rt_function_error_t allocate_top_n_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_top_n_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_top_n_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// BinaryError

rt_function_error_t allocate_binary_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_binary_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_binary_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// ConfusionMatrix
rt_function_error_t allocate_confusion_matrix_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_confusion_matrix_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_confusion_matrix(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
rt_function_error_t allocate_vat_noise_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_vat_noise_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_vat_noise(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Unlink

rt_function_error_t allocate_unlink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_unlink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_unlink(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

// Sink
rt_function_error_t allocate_sink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sink(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t allocate_nms_detection2d_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_nms_detection2d_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_nms_detection2d(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
