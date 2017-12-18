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

// Convolution
void init_convolution_config(convolution_config_t *config, int32_t base_axis,
                             rt_list_t pad, rt_list_t stride,
                             rt_list_t dilation, int32_t group) {
  WHOAMI(" %s\n", __func__);
}
void init_convolution_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_convolutionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_convolution(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// DepthwiseConvolution
void init_depthwise_convolution_config(depthwise_convolution_config_t *config,
                                       int32_t base_axis, rt_list_t pad,
                                       rt_list_t stride, rt_list_t dilation,
                                       int32_t multiplier) {
  WHOAMI(" %s\n", __func__);
}
void init_depthwise_convolution_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_depthwise_convolutionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_depthwise_convolution(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Deconvolution
void init_deconvolution_config(deconvolution_config_t *config,
                               int32_t base_axis, rt_list_t pad,
                               rt_list_t stride, rt_list_t dilation,
                               int32_t group) {
  WHOAMI(" %s\n", __func__);
}
void init_deconvolution_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_deconvolutionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_deconvolution(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MaxPooling
void init_max_pooling_config(max_pooling_config_t *config, rt_list_t kernel,
                             rt_list_t stride, uint8_t ignore_border,
                             rt_list_t pad) {
  WHOAMI(" %s\n", __func__);
}
void init_max_pooling_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_max_poolinglocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_max_pooling(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// AveragePooling
void init_average_pooling_config(average_pooling_config_t *config,
                                 rt_list_t kernel, rt_list_t stride,
                                 uint8_t ignore_border, rt_list_t pad,
                                 uint8_t including_pad) {
  WHOAMI(" %s\n", __func__);
}
void init_average_pooling_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_average_poolinglocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_average_pooling(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// SumPooling
void init_sum_pooling_config(sum_pooling_config_t *config, rt_list_t kernel,
                             rt_list_t stride, uint8_t ignore_border,
                             rt_list_t pad) {
  WHOAMI(" %s\n", __func__);
}
void init_sum_pooling_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_sum_poolinglocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_sum_pooling(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Unpooling
void init_unpooling_config(unpooling_config_t *config, rt_list_t kernel) {
  WHOAMI(" %s\n", __func__);
}
void init_unpooling_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_unpoolinglocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_unpooling(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Embed
void exec_embed(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Swish
void exec_swish(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Tanh
void exec_tanh(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// ReLU
void init_relu_config(relu_config_t *config, uint8_t inplace) {
  WHOAMI(" %s\n", __func__);
}
void init_relu_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_relulocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_relu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LeakyReLU
void init_leaky_relu_config(leaky_relu_config_t *config, float alpha) {
  WHOAMI(" %s\n", __func__);
}
void init_leaky_relu_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_leaky_relulocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_leaky_relu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Softmax
void init_softmax_config(softmax_config_t *config, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_softmax_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_softmaxlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_softmax(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// ELU
void init_elu_config(elu_config_t *config, float alpha) {
  WHOAMI(" %s\n", __func__);
}
void init_elu_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_elulocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_elu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// SELU
void init_selu_config(selu_config_t *config, float scale, float alpha) {
  WHOAMI(" %s\n", __func__);
}
void init_selu_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_selulocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_selu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// CReLU
void init_crelu_config(crelu_config_t *config, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_crelu_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_crelulocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_crelu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// CELU
void init_celu_config(celu_config_t *config, float alpha, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_celu_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_celulocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_celu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// PReLU
void init_prelu_config(prelu_config_t *config, int32_t base_axis) {
  WHOAMI(" %s\n", __func__);
}
void init_prelu_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_prelulocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_prelu(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
void init_batch_normalization_config(batch_normalization_config_t *config,
                                     rt_list_t axes, float decay_rate,
                                     float eps, uint8_t batch_stat) {
  WHOAMI(" %s\n", __func__);
}
void init_batch_normalization_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_batch_normalizationlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_batch_normalization(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MeanSubtraction
void init_mean_subtraction_config(mean_subtraction_config_t *config,
                                  int32_t base_axis,
                                  uint8_t update_running_mean) {
  WHOAMI(" %s\n", __func__);
}
void init_mean_subtraction_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_mean_subtractionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_mean_subtraction(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
void init_sum_config(sum_config_t *config, rt_list_t axes, uint8_t keep_dims) {
  WHOAMI(" %s\n", __func__);
}
void init_sum_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_sumlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_sum(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Mean
void init_mean_config(mean_config_t *config, rt_list_t axes,
                      uint8_t keep_dims) {
  WHOAMI(" %s\n", __func__);
}
void init_mean_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_meanlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_mean(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Max
void init_max_config(max_config_t *config, rt_list_t axes, uint8_t keep_dims) {
  WHOAMI(" %s\n", __func__);
}
void init_max_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_maxlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_max(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Min
void init_min_config(min_config_t *config, rt_list_t axes, uint8_t keep_dims) {
  WHOAMI(" %s\n", __func__);
}
void init_min_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_minlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_min(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Prod
void init_prod_config(prod_config_t *config, rt_list_t axes,
                      uint8_t keep_dims) {
  WHOAMI(" %s\n", __func__);
}
void init_prod_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_prodlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_prod(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// ReduceSum
void exec_reduce_sum(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// ReduceMean
void exec_reduce_mean(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
void init_add2_config(add2_config_t *config, uint8_t inplace) {
  WHOAMI(" %s\n", __func__);
}
void init_add2_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_add2local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_add2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BcAdd2
void exec_bc_add2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Sub2
void exec_sub2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Mul2
void exec_mul2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Div2
void exec_div2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Pow2
void exec_pow2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// AddScalar
void init_add_scalar_config(add_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_add_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_add_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_add_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MulScalar
void init_mul_scalar_config(mul_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_mul_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_mul_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_mul_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// PowScalar
void init_pow_scalar_config(pow_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_pow_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_pow_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_pow_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// RSubScalar
void init_r_sub_scalar_config(r_sub_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_r_sub_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_r_sub_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_r_sub_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// RDivScalar
void init_r_div_scalar_config(r_div_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_r_div_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_r_div_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_r_div_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// RPowScalar
void init_r_pow_scalar_config(r_pow_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_r_pow_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_r_pow_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_r_pow_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
void init_sign_config(sign_config_t *config, float alpha) {
  WHOAMI(" %s\n", __func__);
}
void init_sign_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_signlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_sign(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Minimum2
void exec_minimum2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Maximum2
void exec_maximum2(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MinimumScalar
void init_minimum_scalar_config(minimum_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_minimum_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_minimum_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_minimum_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MaximumScalar
void init_maximum_scalar_config(maximum_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_maximum_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_maximum_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_maximum_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalAnd
void exec_logical_and(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalOr
void exec_logical_or(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalXor
void exec_logical_xor(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Equal
void exec_equal(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// NotEqual
void exec_not_equal(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// GreaterEqual
void exec_greater_equal(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Greater
void exec_greater(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LessEqual
void exec_less_equal(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Less
void exec_less(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalAndScalar
void init_logical_and_scalar_config(logical_and_scalar_config_t *config,
                                    uint8_t val) {
  WHOAMI(" %s\n", __func__);
}
void init_logical_and_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_logical_and_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_logical_and_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalOrScalar
void init_logical_or_scalar_config(logical_or_scalar_config_t *config,
                                   uint8_t val) {
  WHOAMI(" %s\n", __func__);
}
void init_logical_or_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_logical_or_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_logical_or_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalXorScalar
void init_logical_xor_scalar_config(logical_xor_scalar_config_t *config,
                                    uint8_t val) {
  WHOAMI(" %s\n", __func__);
}
void init_logical_xor_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_logical_xor_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_logical_xor_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// EqualScalar
void init_equal_scalar_config(equal_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_equal_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_equal_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_equal_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// NotEqualScalar
void init_not_equal_scalar_config(not_equal_scalar_config_t *config,
                                  float val) {
  WHOAMI(" %s\n", __func__);
}
void init_not_equal_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_not_equal_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_not_equal_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// GreaterEqualScalar
void init_greater_equal_scalar_config(greater_equal_scalar_config_t *config,
                                      float val) {
  WHOAMI(" %s\n", __func__);
}
void init_greater_equal_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_greater_equal_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_greater_equal_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// GreaterScalar
void init_greater_scalar_config(greater_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_greater_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_greater_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_greater_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LessEqualScalar
void init_less_equal_scalar_config(less_equal_scalar_config_t *config,
                                   float val) {
  WHOAMI(" %s\n", __func__);
}
void init_less_equal_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_less_equal_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_less_equal_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LessScalar
void init_less_scalar_config(less_scalar_config_t *config, float val) {
  WHOAMI(" %s\n", __func__);
}
void init_less_scalar_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_less_scalarlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_less_scalar(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// LogicalNot
void exec_logical_not(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
void init_constant_config(constant_config_t *config, float val,
                          rt_list_t shape) {
  WHOAMI(" %s\n", __func__);
}
void init_constant_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_constantlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_constant(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Abs
void exec_abs(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Exp
void exec_exp(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Log
void exec_log(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Identity
void exec_identity(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BatchMatmul
void init_batch_matmul_config(batch_matmul_config_t *config,
                              uint8_t transpose_a, uint8_t transpose_b) {
  WHOAMI(" %s\n", __func__);
}
void init_batch_matmul_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_batch_matmullocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_batch_matmul(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
void init_concatenate_config(concatenate_config_t *config, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_concatenate_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_concatenatelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_concatenate(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Split
void init_split_config(split_config_t *config, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_split_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_splitlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_split(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Stack
void init_stack_config(stack_config_t *config, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_stack_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_stacklocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_stack(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Slice
void init_slice_config(slice_config_t *config, rt_list_t start, rt_list_t stop,
                       rt_list_t step) {
  WHOAMI(" %s\n", __func__);
}
void init_slice_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_slicelocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_slice(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Transpose
void init_transpose_config(transpose_config_t *config, rt_list_t axes) {
  WHOAMI(" %s\n", __func__);
}
void init_transpose_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_transposelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_transpose(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Broadcast
void init_broadcast_config(broadcast_config_t *config, rt_list_t shape) {
  WHOAMI(" %s\n", __func__);
}
void init_broadcast_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_broadcastlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_broadcast(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// OneHot
void init_one_hot_config(one_hot_config_t *config, rt_list_t shape) {
  WHOAMI(" %s\n", __func__);
}
void init_one_hot_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_one_hotlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_one_hot(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Flip
void init_flip_config(flip_config_t *config, rt_list_t axes) {
  WHOAMI(" %s\n", __func__);
}
void init_flip_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_fliplocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_flip(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Shift
void init_shift_config(shift_config_t *config, rt_list_t shifts,
                       uint32_t border_mode) {
  WHOAMI(" %s\n", __func__);
}
void init_shift_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_shiftlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_shift(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Reshape
void init_reshape_config(reshape_config_t *config, rt_list_t shape) {
  WHOAMI(" %s\n", __func__);
}
void init_reshape_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_reshapelocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_reshape(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MatrixDiag
void exec_matrix_diag(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// MatrixDiagPart
void exec_matrix_diag_part(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
void init_dropout_config(dropout_config_t *config, float p, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_dropout_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_dropoutlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_dropout(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Rand
void init_rand_config(rand_config_t *config, float low, float high,
                      rt_list_t shape, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_rand_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_randlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_rand(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Randint
void init_randint_config(randint_config_t *config, int32_t low, int32_t high,
                         rt_list_t shape, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_randint_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_randintlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_randint(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Randn
void init_randn_config(randn_config_t *config, float mu, float sigma,
                       rt_list_t shape, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_randn_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_randnlocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_randn(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// RandomCrop
void init_random_crop_config(random_crop_config_t *config, rt_list_t shape,
                             int32_t base_axis, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_random_crop_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_random_croplocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_random_crop(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// RandomFlip
void init_random_flip_config(random_flip_config_t *config, rt_list_t axes,
                             int32_t base_axis, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_random_flip_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_random_fliplocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_random_flip(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// RandomShift
void init_random_shift_config(random_shift_config_t *config, rt_list_t shifts,
                              uint32_t border_mode, int32_t base_axis,
                              int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_random_shift_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_random_shiftlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_random_shift(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// ImageAugmentation
void init_image_augmentation_config(
    image_augmentation_config_t *config, rt_list_t shape, rt_list_t pad,
    float min_scale, float max_scale, float angle, float aspect_ratio,
    float distortion, uint8_t flip_lr, uint8_t flip_ud, float brightness,
    uint8_t brightness_each, float contrast, float contrast_center,
    uint8_t contrast_each, float noise, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_image_augmentation_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_image_augmentationlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_image_augmentation(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy
void exec_sigmoid_cross_entropy(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BinaryCrossEntropy
void exec_binary_cross_entropy(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// SoftmaxCrossEntropy
void init_softmax_cross_entropy_config(softmax_cross_entropy_config_t *config,
                                       int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_softmax_cross_entropy_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_softmax_cross_entropylocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_softmax_cross_entropy(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// CategoricalCrossEntropy
void init_categorical_cross_entropy_config(
    categorical_cross_entropy_config_t *config, int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_categorical_cross_entropy_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_categorical_cross_entropylocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_categorical_cross_entropy(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}

// SquaredError
void exec_squared_error(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// AbsoluteError
void exec_absolute_error(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// HuberLoss
void init_huber_loss_config(huber_loss_config_t *config, float delta) {
  WHOAMI(" %s\n", __func__);
}
void init_huber_loss_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_huber_losslocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_huber_loss(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// EpsilonInsensitiveLoss
void init_epsilon_insensitive_loss_config(
    epsilon_insensitive_loss_config_t *config, float epsilon) {
  WHOAMI(" %s\n", __func__);
}
void init_epsilon_insensitive_loss_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_epsilon_insensitive_losslocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_epsilon_insensitive_loss(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}

// KLMultinomial
void init_kl_multinomial_config(kl_multinomial_config_t *config,
                                int32_t base_axis) {
  WHOAMI(" %s\n", __func__);
}
void init_kl_multinomial_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_kl_multinomiallocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_kl_multinomial(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid
void exec_binary_sigmoid(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BinaryTanh
void exec_binary_tanh(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BinaryConnectAffine
void init_binary_connect_affine_config(binary_connect_affine_config_t *config,
                                       int32_t base_axis) {
  WHOAMI(" %s\n", __func__);
}
void init_binary_connect_affine_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_binary_connect_affinelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_binary_connect_affine(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BinaryConnectConvolution
void init_binary_connect_convolution_config(
    binary_connect_convolution_config_t *config, int32_t base_axis,
    rt_list_t pad, rt_list_t stride, rt_list_t dilation, int32_t group) {
  WHOAMI(" %s\n", __func__);
}
void init_binary_connect_convolution_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_binary_connect_convolutionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_binary_connect_convolution(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}

// BinaryWeightAffine
void init_binary_weight_affine_config(binary_weight_affine_config_t *config,
                                      int32_t base_axis) {
  WHOAMI(" %s\n", __func__);
}
void init_binary_weight_affine_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_binary_weight_affinelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_binary_weight_affine(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BinaryWeightConvolution
void init_binary_weight_convolution_config(
    binary_weight_convolution_config_t *config, int32_t base_axis,
    rt_list_t pad, rt_list_t stride, rt_list_t dilation, int32_t group) {
  WHOAMI(" %s\n", __func__);
}
void init_binary_weight_convolution_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_binary_weight_convolutionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_binary_weight_convolution(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}

// INQAffine
void init_inq_affine_config(inq_affine_config_t *config, int32_t base_axis,
                            int32_t num_bits, rt_list_t inq_iterations,
                            uint32_t selection_algorithm, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_inq_affine_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_inq_affinelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_inq_affine(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// INQConvolution
void init_inq_convolution_config(inq_convolution_config_t *config,
                                 int32_t base_axis, rt_list_t pad,
                                 rt_list_t stride, rt_list_t dilation,
                                 int32_t group, int32_t num_bits,
                                 rt_list_t inq_iterations,
                                 uint32_t selection_algorithm, int32_t seed) {
  WHOAMI(" %s\n", __func__);
}
void init_inq_convolution_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_inq_convolutionlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_inq_convolution(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// FixedPointQuantize
void init_fixed_point_quantize_config(fixed_point_quantize_config_t *config,
                                      uint8_t sign, int32_t n, float delta,
                                      uint8_t ste_fine_grained) {
  WHOAMI(" %s\n", __func__);
}
void init_fixed_point_quantize_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_fixed_point_quantizelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_fixed_point_quantize(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Pow2Quantize
void init_pow2_quantize_config(pow2_quantize_config_t *config, uint8_t sign,
                               uint8_t with_zero, int32_t n, int32_t m,
                               uint8_t ste_fine_grained) {
  WHOAMI(" %s\n", __func__);
}
void init_pow2_quantize_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_pow2_quantizelocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_pow2_quantize(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
void init_top_n_error_config(top_n_error_config_t *config, int32_t axis,
                             int32_t n) {
  WHOAMI(" %s\n", __func__);
}
void init_top_n_error_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_top_n_errorlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_top_n_error(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// BinaryError
void exec_binary_error(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// ConfusionMatrix
void init_confusion_matrix_config(confusion_matrix_config_t *config,
                                  int32_t axis) {
  WHOAMI(" %s\n", __func__);
}
void init_confusion_matrix_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_confusion_matrixlocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_confusion_matrix(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
void init_vat_noise_config(vat_noise_config_t *config, int32_t base_axis,
                           float eps) {
  WHOAMI(" %s\n", __func__);
}
void init_vat_noise_local_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void free_vat_noiselocal_context(rt_function_t *f) {
  WHOAMI(" %s\n", __func__);
}
void exec_vat_noise(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Unlink
void exec_unlink(rt_function_t *f) { WHOAMI(" %s\n", __func__); }

// Sink
void init_sink_config(sink_config_t *config, uint8_t one_input_grad) {
  WHOAMI(" %s\n", __func__);
}
void init_sink_local_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void free_sinklocal_context(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
void exec_sink(rt_function_t *f) { WHOAMI(" %s\n", __func__); }
