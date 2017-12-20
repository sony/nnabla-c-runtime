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
void allocate_convolution_local_context(rt_function_t *f) {}

void free_convolution_local_context(rt_function_t *f) {}

void exec_convolution(rt_function_t *f) {}

// DepthwiseConvolution
void allocate_depthwise_convolution_local_context(rt_function_t *f) {}

void free_depthwise_convolution_local_context(rt_function_t *f) {}

void exec_depthwise_convolution(rt_function_t *f) {}

// Deconvolution
void allocate_deconvolution_local_context(rt_function_t *f) {}

void free_deconvolution_local_context(rt_function_t *f) {}

void exec_deconvolution(rt_function_t *f) {}

// MaxPooling
void allocate_max_pooling_local_context(rt_function_t *f) {}

void free_max_pooling_local_context(rt_function_t *f) {}

void exec_max_pooling(rt_function_t *f) {}

// AveragePooling
void allocate_average_pooling_local_context(rt_function_t *f) {}

void free_average_pooling_local_context(rt_function_t *f) {}

void exec_average_pooling(rt_function_t *f) {}

// SumPooling
void allocate_sum_pooling_local_context(rt_function_t *f) {}

void free_sum_pooling_local_context(rt_function_t *f) {}

void exec_sum_pooling(rt_function_t *f) {}

// Unpooling
void allocate_unpooling_local_context(rt_function_t *f) {}

void free_unpooling_local_context(rt_function_t *f) {}

void exec_unpooling(rt_function_t *f) {}

// Embed
void allocate_embed_local_context(rt_function_t *f) {}

void free_embed_local_context(rt_function_t *f) {}

void exec_embed(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Swish
void allocate_swish_local_context(rt_function_t *f) {}

void free_swish_local_context(rt_function_t *f) {}

void exec_swish(rt_function_t *f) {}

// Tanh
void allocate_tanh_local_context(rt_function_t *f) {}

void free_tanh_local_context(rt_function_t *f) {}

void exec_tanh(rt_function_t *f) {}

// ReLU
void allocate_relu_local_context(rt_function_t *f) {}

void free_relu_local_context(rt_function_t *f) {}

void exec_relu(rt_function_t *f) {}

// LeakyReLU
void allocate_leaky_relu_local_context(rt_function_t *f) {}

void free_leaky_relu_local_context(rt_function_t *f) {}

void exec_leaky_relu(rt_function_t *f) {}

// Softmax
void allocate_softmax_local_context(rt_function_t *f) {}

void free_softmax_local_context(rt_function_t *f) {}

void exec_softmax(rt_function_t *f) {}

// ELU
void allocate_elu_local_context(rt_function_t *f) {}

void free_elu_local_context(rt_function_t *f) {}

void exec_elu(rt_function_t *f) {}

// SELU
void allocate_selu_local_context(rt_function_t *f) {}

void free_selu_local_context(rt_function_t *f) {}

void exec_selu(rt_function_t *f) {}

// CReLU
void allocate_crelu_local_context(rt_function_t *f) {}

void free_crelu_local_context(rt_function_t *f) {}

void exec_crelu(rt_function_t *f) {}

// CELU
void allocate_celu_local_context(rt_function_t *f) {}

void free_celu_local_context(rt_function_t *f) {}

void exec_celu(rt_function_t *f) {}

// PReLU
void allocate_prelu_local_context(rt_function_t *f) {}

void free_prelu_local_context(rt_function_t *f) {}

void exec_prelu(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
void allocate_batch_normalization_local_context(rt_function_t *f) {}

void free_batch_normalization_local_context(rt_function_t *f) {}

void exec_batch_normalization(rt_function_t *f) {}

// MeanSubtraction
void allocate_mean_subtraction_local_context(rt_function_t *f) {}

void free_mean_subtraction_local_context(rt_function_t *f) {}

void exec_mean_subtraction(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
void allocate_sum_local_context(rt_function_t *f) {}

void free_sum_local_context(rt_function_t *f) {}

void exec_sum(rt_function_t *f) {}

// Mean
void allocate_mean_local_context(rt_function_t *f) {}

void free_mean_local_context(rt_function_t *f) {}

void exec_mean(rt_function_t *f) {}

// Max
void allocate_max_local_context(rt_function_t *f) {}

void free_max_local_context(rt_function_t *f) {}

void exec_max(rt_function_t *f) {}

// Min
void allocate_min_local_context(rt_function_t *f) {}

void free_min_local_context(rt_function_t *f) {}

void exec_min(rt_function_t *f) {}

// Prod
void allocate_prod_local_context(rt_function_t *f) {}

void free_prod_local_context(rt_function_t *f) {}

void exec_prod(rt_function_t *f) {}

// ReduceSum

void allocate_reduce_sum_local_context(rt_function_t *f) {}

void free_reduce_sum_local_context(rt_function_t *f) {}

void exec_reduce_sum(rt_function_t *f) {}

// ReduceMean

void allocate_reduce_mean_local_context(rt_function_t *f) {}

void free_reduce_mean_local_context(rt_function_t *f) {}

void exec_reduce_mean(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
void allocate_add2_local_context(rt_function_t *f) {}

void free_add2_local_context(rt_function_t *f) {}

void exec_add2(rt_function_t *f) {}

// BcAdd2

void allocate_bc_add2_local_context(rt_function_t *f) {}

void free_bc_add2_local_context(rt_function_t *f) {}

void exec_bc_add2(rt_function_t *f) {}

// Sub2

void allocate_sub2_local_context(rt_function_t *f) {}

void free_sub2_local_context(rt_function_t *f) {}

void exec_sub2(rt_function_t *f) {}

// Mul2

void allocate_mul2_local_context(rt_function_t *f) {}

void free_mul2_local_context(rt_function_t *f) {}

void exec_mul2(rt_function_t *f) {}

// Div2

void allocate_div2_local_context(rt_function_t *f) {}

void free_div2_local_context(rt_function_t *f) {}

void exec_div2(rt_function_t *f) {}

// Pow2

void allocate_pow2_local_context(rt_function_t *f) {}

void free_pow2_local_context(rt_function_t *f) {}

void exec_pow2(rt_function_t *f) {}

// AddScalar
void allocate_add_scalar_local_context(rt_function_t *f) {}

void free_add_scalar_local_context(rt_function_t *f) {}

void exec_add_scalar(rt_function_t *f) {}

// MulScalar
void allocate_mul_scalar_local_context(rt_function_t *f) {}

void free_mul_scalar_local_context(rt_function_t *f) {}

void exec_mul_scalar(rt_function_t *f) {}

// PowScalar
void allocate_pow_scalar_local_context(rt_function_t *f) {}

void free_pow_scalar_local_context(rt_function_t *f) {}

void exec_pow_scalar(rt_function_t *f) {}

// RSubScalar
void allocate_r_sub_scalar_local_context(rt_function_t *f) {}

void free_r_sub_scalar_local_context(rt_function_t *f) {}

void exec_r_sub_scalar(rt_function_t *f) {}

// RDivScalar
void allocate_r_div_scalar_local_context(rt_function_t *f) {}

void free_r_div_scalar_local_context(rt_function_t *f) {}

void exec_r_div_scalar(rt_function_t *f) {}

// RPowScalar
void allocate_r_pow_scalar_local_context(rt_function_t *f) {}

void free_r_pow_scalar_local_context(rt_function_t *f) {}

void exec_r_pow_scalar(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
void allocate_sign_local_context(rt_function_t *f) {}

void free_sign_local_context(rt_function_t *f) {}

void exec_sign(rt_function_t *f) {}

// Minimum2

void allocate_minimum2_local_context(rt_function_t *f) {}

void free_minimum2_local_context(rt_function_t *f) {}

void exec_minimum2(rt_function_t *f) {}

// Maximum2

void allocate_maximum2_local_context(rt_function_t *f) {}

void free_maximum2_local_context(rt_function_t *f) {}

void exec_maximum2(rt_function_t *f) {}

// MinimumScalar
void allocate_minimum_scalar_local_context(rt_function_t *f) {}

void free_minimum_scalar_local_context(rt_function_t *f) {}

void exec_minimum_scalar(rt_function_t *f) {}

// MaximumScalar
void allocate_maximum_scalar_local_context(rt_function_t *f) {}

void free_maximum_scalar_local_context(rt_function_t *f) {}

void exec_maximum_scalar(rt_function_t *f) {}

// LogicalAnd

void allocate_logical_and_local_context(rt_function_t *f) {}

void free_logical_and_local_context(rt_function_t *f) {}

void exec_logical_and(rt_function_t *f) {}

// LogicalOr

void allocate_logical_or_local_context(rt_function_t *f) {}

void free_logical_or_local_context(rt_function_t *f) {}

void exec_logical_or(rt_function_t *f) {}

// LogicalXor

void allocate_logical_xor_local_context(rt_function_t *f) {}

void free_logical_xor_local_context(rt_function_t *f) {}

void exec_logical_xor(rt_function_t *f) {}

// Equal

void allocate_equal_local_context(rt_function_t *f) {}

void free_equal_local_context(rt_function_t *f) {}

void exec_equal(rt_function_t *f) {}

// NotEqual

void allocate_not_equal_local_context(rt_function_t *f) {}

void free_not_equal_local_context(rt_function_t *f) {}

void exec_not_equal(rt_function_t *f) {}

// GreaterEqual

void allocate_greater_equal_local_context(rt_function_t *f) {}

void free_greater_equal_local_context(rt_function_t *f) {}

void exec_greater_equal(rt_function_t *f) {}

// Greater

void allocate_greater_local_context(rt_function_t *f) {}

void free_greater_local_context(rt_function_t *f) {}

void exec_greater(rt_function_t *f) {}

// LessEqual

void allocate_less_equal_local_context(rt_function_t *f) {}

void free_less_equal_local_context(rt_function_t *f) {}

void exec_less_equal(rt_function_t *f) {}

// Less

void allocate_less_local_context(rt_function_t *f) {}

void free_less_local_context(rt_function_t *f) {}

void exec_less(rt_function_t *f) {}

// LogicalAndScalar
void allocate_logical_and_scalar_local_context(rt_function_t *f) {}

void free_logical_and_scalar_local_context(rt_function_t *f) {}

void exec_logical_and_scalar(rt_function_t *f) {}

// LogicalOrScalar
void allocate_logical_or_scalar_local_context(rt_function_t *f) {}

void free_logical_or_scalar_local_context(rt_function_t *f) {}

void exec_logical_or_scalar(rt_function_t *f) {}

// LogicalXorScalar
void allocate_logical_xor_scalar_local_context(rt_function_t *f) {}

void free_logical_xor_scalar_local_context(rt_function_t *f) {}

void exec_logical_xor_scalar(rt_function_t *f) {}

// EqualScalar
void allocate_equal_scalar_local_context(rt_function_t *f) {}

void free_equal_scalar_local_context(rt_function_t *f) {}

void exec_equal_scalar(rt_function_t *f) {}

// NotEqualScalar
void allocate_not_equal_scalar_local_context(rt_function_t *f) {}

void free_not_equal_scalar_local_context(rt_function_t *f) {}

void exec_not_equal_scalar(rt_function_t *f) {}

// GreaterEqualScalar
void allocate_greater_equal_scalar_local_context(rt_function_t *f) {}

void free_greater_equal_scalar_local_context(rt_function_t *f) {}

void exec_greater_equal_scalar(rt_function_t *f) {}

// GreaterScalar
void allocate_greater_scalar_local_context(rt_function_t *f) {}

void free_greater_scalar_local_context(rt_function_t *f) {}

void exec_greater_scalar(rt_function_t *f) {}

// LessEqualScalar
void allocate_less_equal_scalar_local_context(rt_function_t *f) {}

void free_less_equal_scalar_local_context(rt_function_t *f) {}

void exec_less_equal_scalar(rt_function_t *f) {}

// LessScalar
void allocate_less_scalar_local_context(rt_function_t *f) {}

void free_less_scalar_local_context(rt_function_t *f) {}

void exec_less_scalar(rt_function_t *f) {}

// LogicalNot

void allocate_logical_not_local_context(rt_function_t *f) {}

void free_logical_not_local_context(rt_function_t *f) {}

void exec_logical_not(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
void allocate_constant_local_context(rt_function_t *f) {}

void free_constant_local_context(rt_function_t *f) {}

void exec_constant(rt_function_t *f) {}

// Abs

void allocate_abs_local_context(rt_function_t *f) {}

void free_abs_local_context(rt_function_t *f) {}

void exec_abs(rt_function_t *f) {}

// Exp

void allocate_exp_local_context(rt_function_t *f) {}

void free_exp_local_context(rt_function_t *f) {}

void exec_exp(rt_function_t *f) {}

// Log

void allocate_log_local_context(rt_function_t *f) {}

void free_log_local_context(rt_function_t *f) {}

void exec_log(rt_function_t *f) {}

// Identity

void allocate_identity_local_context(rt_function_t *f) {}

void free_identity_local_context(rt_function_t *f) {}

void exec_identity(rt_function_t *f) {}

// BatchMatmul
void allocate_batch_matmul_local_context(rt_function_t *f) {}

void free_batch_matmul_local_context(rt_function_t *f) {}

void exec_batch_matmul(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
void allocate_concatenate_local_context(rt_function_t *f) {}

void free_concatenate_local_context(rt_function_t *f) {}

void exec_concatenate(rt_function_t *f) {}

// Split
void allocate_split_local_context(rt_function_t *f) {}

void free_split_local_context(rt_function_t *f) {}

void exec_split(rt_function_t *f) {}

// Stack
void allocate_stack_local_context(rt_function_t *f) {}

void free_stack_local_context(rt_function_t *f) {}

void exec_stack(rt_function_t *f) {}

// Slice
void allocate_slice_local_context(rt_function_t *f) {}

void free_slice_local_context(rt_function_t *f) {}

void exec_slice(rt_function_t *f) {}

// Transpose
void allocate_transpose_local_context(rt_function_t *f) {}

void free_transpose_local_context(rt_function_t *f) {}

void exec_transpose(rt_function_t *f) {}

// Broadcast
void allocate_broadcast_local_context(rt_function_t *f) {}

void free_broadcast_local_context(rt_function_t *f) {}

void exec_broadcast(rt_function_t *f) {}

// OneHot
void allocate_one_hot_local_context(rt_function_t *f) {}

void free_one_hot_local_context(rt_function_t *f) {}

void exec_one_hot(rt_function_t *f) {}

// Flip
void allocate_flip_local_context(rt_function_t *f) {}

void free_flip_local_context(rt_function_t *f) {}

void exec_flip(rt_function_t *f) {}

// Shift
void allocate_shift_local_context(rt_function_t *f) {}

void free_shift_local_context(rt_function_t *f) {}

void exec_shift(rt_function_t *f) {}

// Reshape
void allocate_reshape_local_context(rt_function_t *f) {}

void free_reshape_local_context(rt_function_t *f) {}

void exec_reshape(rt_function_t *f) {}

// MatrixDiag

void allocate_matrix_diag_local_context(rt_function_t *f) {}

void free_matrix_diag_local_context(rt_function_t *f) {}

void exec_matrix_diag(rt_function_t *f) {}

// MatrixDiagPart

void allocate_matrix_diag_part_local_context(rt_function_t *f) {}

void free_matrix_diag_part_local_context(rt_function_t *f) {}

void exec_matrix_diag_part(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
void allocate_dropout_local_context(rt_function_t *f) {}

void free_dropout_local_context(rt_function_t *f) {}

void exec_dropout(rt_function_t *f) {}

// Rand
void allocate_rand_local_context(rt_function_t *f) {}

void free_rand_local_context(rt_function_t *f) {}

void exec_rand(rt_function_t *f) {}

// Randint
void allocate_randint_local_context(rt_function_t *f) {}

void free_randint_local_context(rt_function_t *f) {}

void exec_randint(rt_function_t *f) {}

// Randn
void allocate_randn_local_context(rt_function_t *f) {}

void free_randn_local_context(rt_function_t *f) {}

void exec_randn(rt_function_t *f) {}

// RandomCrop
void allocate_random_crop_local_context(rt_function_t *f) {}

void free_random_crop_local_context(rt_function_t *f) {}

void exec_random_crop(rt_function_t *f) {}

// RandomFlip
void allocate_random_flip_local_context(rt_function_t *f) {}

void free_random_flip_local_context(rt_function_t *f) {}

void exec_random_flip(rt_function_t *f) {}

// RandomShift
void allocate_random_shift_local_context(rt_function_t *f) {}

void free_random_shift_local_context(rt_function_t *f) {}

void exec_random_shift(rt_function_t *f) {}

// ImageAugmentation
void allocate_image_augmentation_local_context(rt_function_t *f) {}

void free_image_augmentation_local_context(rt_function_t *f) {}

void exec_image_augmentation(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy

void allocate_sigmoid_cross_entropy_local_context(rt_function_t *f) {}

void free_sigmoid_cross_entropy_local_context(rt_function_t *f) {}

void exec_sigmoid_cross_entropy(rt_function_t *f) {}

// BinaryCrossEntropy

void allocate_binary_cross_entropy_local_context(rt_function_t *f) {}

void free_binary_cross_entropy_local_context(rt_function_t *f) {}

void exec_binary_cross_entropy(rt_function_t *f) {}

// SoftmaxCrossEntropy
void allocate_softmax_cross_entropy_local_context(rt_function_t *f) {}

void free_softmax_cross_entropy_local_context(rt_function_t *f) {}

void exec_softmax_cross_entropy(rt_function_t *f) {}

// CategoricalCrossEntropy
void allocate_categorical_cross_entropy_local_context(rt_function_t *f) {}

void free_categorical_cross_entropy_local_context(rt_function_t *f) {}

void exec_categorical_cross_entropy(rt_function_t *f) {}

// SquaredError

void allocate_squared_error_local_context(rt_function_t *f) {}

void free_squared_error_local_context(rt_function_t *f) {}

void exec_squared_error(rt_function_t *f) {}

// AbsoluteError

void allocate_absolute_error_local_context(rt_function_t *f) {}

void free_absolute_error_local_context(rt_function_t *f) {}

void exec_absolute_error(rt_function_t *f) {}

// HuberLoss
void allocate_huber_loss_local_context(rt_function_t *f) {}

void free_huber_loss_local_context(rt_function_t *f) {}

void exec_huber_loss(rt_function_t *f) {}

// EpsilonInsensitiveLoss
void allocate_epsilon_insensitive_loss_local_context(rt_function_t *f) {}

void free_epsilon_insensitive_loss_local_context(rt_function_t *f) {}

void exec_epsilon_insensitive_loss(rt_function_t *f) {}

// KLMultinomial
void allocate_kl_multinomial_local_context(rt_function_t *f) {}

void free_kl_multinomial_local_context(rt_function_t *f) {}

void exec_kl_multinomial(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid

void allocate_binary_sigmoid_local_context(rt_function_t *f) {}

void free_binary_sigmoid_local_context(rt_function_t *f) {}

void exec_binary_sigmoid(rt_function_t *f) {}

// BinaryTanh

void allocate_binary_tanh_local_context(rt_function_t *f) {}

void free_binary_tanh_local_context(rt_function_t *f) {}

void exec_binary_tanh(rt_function_t *f) {}

// BinaryConnectAffine
void allocate_binary_connect_affine_local_context(rt_function_t *f) {}

void free_binary_connect_affine_local_context(rt_function_t *f) {}

void exec_binary_connect_affine(rt_function_t *f) {}

// BinaryConnectConvolution
void allocate_binary_connect_convolution_local_context(rt_function_t *f) {}

void free_binary_connect_convolution_local_context(rt_function_t *f) {}

void exec_binary_connect_convolution(rt_function_t *f) {}

// BinaryWeightAffine
void allocate_binary_weight_affine_local_context(rt_function_t *f) {}

void free_binary_weight_affine_local_context(rt_function_t *f) {}

void exec_binary_weight_affine(rt_function_t *f) {}

// BinaryWeightConvolution
void allocate_binary_weight_convolution_local_context(rt_function_t *f) {}

void free_binary_weight_convolution_local_context(rt_function_t *f) {}

void exec_binary_weight_convolution(rt_function_t *f) {}

// INQAffine
void allocate_inq_affine_local_context(rt_function_t *f) {}

void free_inq_affine_local_context(rt_function_t *f) {}

void exec_inq_affine(rt_function_t *f) {}

// INQConvolution
void allocate_inq_convolution_local_context(rt_function_t *f) {}

void free_inq_convolution_local_context(rt_function_t *f) {}

void exec_inq_convolution(rt_function_t *f) {}

// FixedPointQuantize
void allocate_fixed_point_quantize_local_context(rt_function_t *f) {}

void free_fixed_point_quantize_local_context(rt_function_t *f) {}

void exec_fixed_point_quantize(rt_function_t *f) {}

// Pow2Quantize
void allocate_pow2_quantize_local_context(rt_function_t *f) {}

void free_pow2_quantize_local_context(rt_function_t *f) {}

void exec_pow2_quantize(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
void allocate_top_n_error_local_context(rt_function_t *f) {}

void free_top_n_error_local_context(rt_function_t *f) {}

void exec_top_n_error(rt_function_t *f) {}

// BinaryError

void allocate_binary_error_local_context(rt_function_t *f) {}

void free_binary_error_local_context(rt_function_t *f) {}

void exec_binary_error(rt_function_t *f) {}

// ConfusionMatrix
void allocate_confusion_matrix_local_context(rt_function_t *f) {}

void free_confusion_matrix_local_context(rt_function_t *f) {}

void exec_confusion_matrix(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
void allocate_vat_noise_local_context(rt_function_t *f) {}

void free_vat_noise_local_context(rt_function_t *f) {}

void exec_vat_noise(rt_function_t *f) {}

// Unlink

void allocate_unlink_local_context(rt_function_t *f) {}

void free_unlink_local_context(rt_function_t *f) {}

void exec_unlink(rt_function_t *f) {}

// Sink
void allocate_sink_local_context(rt_function_t *f) {}

void free_sink_local_context(rt_function_t *f) {}

void exec_sink(rt_function_t *f) {}
