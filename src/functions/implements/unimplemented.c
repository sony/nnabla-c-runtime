// Copyright 2017,2018,2019,2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
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

#include <nnablart/config.h>
#include <nnablart/functions.h>

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////
// RNN
#ifdef CONFIG_RNN
rt_function_error_t allocate_rnn_local_context(rt_function_t *f) {
  f->exec_func = exec_rnn;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_rnn_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_rnn(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RNN */

// LSTM
#ifdef CONFIG_LSTM
rt_function_error_t allocate_lstm_local_context(rt_function_t *f) {
  f->exec_func = exec_lstm;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_lstm_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_lstm(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LSTM */

// GRU
#ifdef CONFIG_GRU
rt_function_error_t allocate_gru_local_context(rt_function_t *f) {
  f->exec_func = exec_lstm;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_gru_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_gru(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GRU */

// FusedConvolution
#ifdef CONFIG_FUSEDCONVOLUTION
rt_function_error_t allocate_fused_convolution_local_context(rt_function_t *f) {
  f->exec_func = exec_fused_convolution;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_fused_convolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_fused_convolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_FUSEDCONVOLUTION */

// DepthwiseDeconvolution
#ifdef CONFIG_DEPTHWISEDECONVOLUTION
rt_function_error_t
allocate_depthwise_deconvolution_local_context(rt_function_t *f) {
  f->exec_func = exec_depthwise_deconvolution;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_depthwise_deconvolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_depthwise_deconvolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_DEPTHWISEDECONVOLUTION */

// DeformableConvolution
#ifdef CONFIG_DEFORMABLECONVOLUTION
rt_function_error_t
allocate_deformable_convolution_local_context(rt_function_t *f) {
  f->exec_func = exec_deformable_convolution;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_deformable_convolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_deformable_convolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_DEFORMABLECONVOLUTION */

// AdaptiveSeparableConvolution
#ifdef CONFIG_ADAPTIVESEPARABLECONVOLUTION
rt_function_error_t
allocate_adaptive_separable_convolution_local_context(rt_function_t *f) {
  f->exec_func = exec_adaptive_separable_convolution;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_adaptive_separable_convolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_adaptive_separable_convolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ADAPTIVESEPARABLECONVOLUTION */

// GlobalAveragePooling
#ifdef CONFIG_GLOBALAVERAGEPOOLING
rt_function_error_t
allocate_global_average_pooling_local_context(rt_function_t *f) {
  f->exec_func = exec_global_average_pooling;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_global_average_pooling_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_global_average_pooling(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GLOBALAVERAGEPOOLING */

// Embed
#ifdef CONFIG_EMBED
rt_function_error_t allocate_embed_local_context(rt_function_t *f) {
  f->exec_func = exec_embed;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_embed_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_embed(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_EMBED */

// RoiAlign
#ifdef CONFIG_ROIALIGN
rt_function_error_t allocate_roi_align_local_context(rt_function_t *f) {
  f->exec_func = exec_roi_align;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_roi_align_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_roi_align(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ROIALIGN */

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// LogSoftmax
#ifdef CONFIG_LOGSOFTMAX
rt_function_error_t allocate_log_softmax_local_context(rt_function_t *f) {
  f->exec_func = exec_log_softmax;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_log_softmax_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_log_softmax(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGSOFTMAX */

// ReLU6
#ifdef CONFIG_RELU6
rt_function_error_t allocate_relu6_local_context(rt_function_t *f) {
  f->exec_func = exec_relu6;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_relu6_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_relu6(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RELU6 */

// Mish
#ifdef CONFIG_MISH
rt_function_error_t allocate_mish_local_context(rt_function_t *f) {
  f->exec_func = exec_mish;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_mish_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_mish(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MISH */

// HardSigmoid
#ifdef CONFIG_HARDSIGMOID
rt_function_error_t allocate_hard_sigmoid_local_context(rt_function_t *f) {
  f->exec_func = exec_hard_sigmoid;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_hard_sigmoid_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_hard_sigmoid(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_HARDSIGMOID */

// HardTanh
#ifdef CONFIG_HARDTANH
rt_function_error_t allocate_hard_tanh_local_context(rt_function_t *f) {
  f->exec_func = exec_hard_tanh;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_hard_tanh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_hard_tanh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_HARDTANH */

// LogSigmoid
#ifdef CONFIG_LOGSIGMOID
rt_function_error_t allocate_log_sigmoid_local_context(rt_function_t *f) {
  f->exec_func = exec_log_sigmoid;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_log_sigmoid_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_log_sigmoid(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGSIGMOID */

// SoftPlus
#ifdef CONFIG_LOGSIGMOID
rt_function_error_t allocate_softplus_local_context(rt_function_t *f) {
  f->exec_func = exec_softplus;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_softplus_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_softplus(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGSIGMOID */

// SoftSign
#ifdef CONFIG_SOFTSIGN
rt_function_error_t allocate_softsign_local_context(rt_function_t *f) {
  f->exec_func = exec_softsign;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_softsign_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_softsign(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SOFTSIGN */

// TanhShrink
#ifdef CONFIG_TANHSHRINK
rt_function_error_t allocate_tanh_shrink_local_context(rt_function_t *f) {
  f->exec_func = exec_tanh_shrink;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_tanh_shrink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_tanh_shrink(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TANHSHRINK */

// Sinc
#ifdef CONFIG_SINC
rt_function_error_t allocate_sinc_local_context(rt_function_t *f) {
  f->exec_func = exec_sinc;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sinc_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sinc(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGSIGMOID */

#ifdef CONFIG_GELU
rt_function_error_t allocate_gelu_local_context(rt_function_t *f) {
  f->exec_func = exec_gelu;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_gelu_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_gelu(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GELU */

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// FusedBatchNormalization
#ifdef CONFIG_FUSEDBATCHNORMALIZATION
rt_function_error_t
allocate_fused_batch_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_fused_batch_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_fused_batch_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_fused_batch_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_FUSEDBATCHNORMALIZATION */

// GroupNormalization
#ifdef CONFIG_GROUPNORMALIZATION
rt_function_error_t
allocate_group_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_group_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_group_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_group_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GROUPNORMALIZATION */

// InstanceNormalization
#ifdef CONFIG_INSTANCENORMALIZATION
rt_function_error_t
allocate_instance_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_instance_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_instance_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_instance_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_INSTANCENORMALIZATION */

// LayerNormalization
#ifdef CONFIG_LAYERNORMALIZATION
rt_function_error_t
allocate_layer_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_layer_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_layer_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_layer_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LAYERNORMALIZATION */

// NormNormalization
#ifdef CONFIG_NORMNORMALIZATION
rt_function_error_t
allocate_norm_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_norm_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_norm_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_norm_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_NORMNORMALIZATION */

// SyncBatchNormalization
#ifdef CONFIG_SYNCBATCHNORMALIZATION
rt_function_error_t
allocate_sync_batch_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_sync_batch_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_sync_batch_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sync_batch_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SYNCBATCHNORMALIZATION */

// TensorNormalization
#ifdef CONFIG_TENSORNORMALIZATION
rt_function_error_t
allocate_tensor_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_tensor_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_tensor_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_tensor_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TENSORNORMALIZATION */

// WeightNormalization
#ifdef CONFIG_WEIGHTNORMALIZATION
rt_function_error_t
allocate_weight_normalization_local_context(rt_function_t *f) {
  f->exec_func = exec_weight_normalization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_weight_normalization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_weight_normalization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_WEIGHTNORMALIZATION */

// WeightStandardization
#ifdef CONFIG_WEIGHTSTANDARDIZATION
rt_function_error_t
allocate_weight_standardization_local_context(rt_function_t *f) {
  f->exec_func = exec_weight_standardization;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_weight_standardization_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_weight_standardization(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_WEIGHTSTANDARDIZATION */

// SpectralNorm
#ifdef CONFIG_SPECTRALNORM
rt_function_error_t allocate_spectral_norm_local_context(rt_function_t *f) {
  f->exec_func = exec_spectral_norm;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_spectral_norm_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_spectral_norm(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SPECTRALNORM */

#ifdef CONFIG_CLIPGRADBYVALUE
rt_function_error_t
allocate_clip_grad_by_value_local_context(rt_function_t *f) {
  f->exec_func = exec_clip_grad_by_value;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_clip_grad_by_value_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_clip_grad_by_value(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CLIPGRADBYVALUE */

#ifdef CONFIG_CLIPGRADBYNORM
rt_function_error_t allocate_clip_grad_by_norm_local_context(rt_function_t *f) {
  f->exec_func = exec_clip_grad_by_norm;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_clip_grad_by_norm_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_clip_grad_by_norm(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CLIPGRADBYNORM */

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// CumSum
#ifdef CONFIG_CUMSUM
rt_function_error_t allocate_cumsum_local_context(rt_function_t *f) {
  f->exec_func = exec_cumsum;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_cumsum_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_cumsum(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CUMSUM */

// Mean
#ifdef CONFIG_MEAN
rt_function_error_t allocate_mean_local_context(rt_function_t *f) {
  f->exec_func = exec_mean;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_mean_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_mean(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MEAN */

// Max
#ifdef CONFIG_MAX
rt_function_error_t allocate_max_local_context(rt_function_t *f) {
  f->exec_func = exec_max;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_max_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_max(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MAX */

// Min
#ifdef CONFIG_MIN
rt_function_error_t allocate_min_local_context(rt_function_t *f) {
  f->exec_func = exec_min;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_min_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_min(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MIN */

// Norm
#ifdef CONFIG_NORM
rt_function_error_t allocate_norm_local_context(rt_function_t *f) {
  f->exec_func = exec_norm;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_norm_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_norm(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_NORM */

// Prod
#ifdef CONFIG_PROD
rt_function_error_t allocate_prod_local_context(rt_function_t *f) {
  f->exec_func = exec_prod;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_prod_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_prod(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_PROD */

// CumProd
#ifdef CONFIG_CUMPROD
rt_function_error_t allocate_cumprod_local_context(rt_function_t *f) {
  f->exec_func = exec_cumprod;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_cumprod_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_cumprod(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CUMPROD */

// ReduceSum
#ifdef CONFIG_REDUCESUM
rt_function_error_t allocate_reduce_sum_local_context(rt_function_t *f) {
  f->exec_func = exec_reduce_sum;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_reduce_sum_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_reduce_sum(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_REDUCESUM */

// ReduceMean
#ifdef CONFIG_REDUCEMEAN
rt_function_error_t allocate_reduce_mean_local_context(rt_function_t *f) {
  f->exec_func = exec_reduce_mean;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_reduce_mean_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_reduce_mean(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_REDUCEMEAN */

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// BcAdd2
#ifdef CONFIG_BCADD2
rt_function_error_t allocate_bc_add2_local_context(rt_function_t *f) {
  f->exec_func = exec_bc_add2;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_bc_add2_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_bc_add2(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BCADD2 */

// AddN
#ifdef CONFIG_ADDN
rt_function_error_t allocate_add_n_local_context(rt_function_t *f) {
  f->exec_func = exec_add_n;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_add_n_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_add_n(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ADDN */

// MulN
#ifdef CONFIG_MULN
rt_function_error_t allocate_mul_n_local_context(rt_function_t *f) {
  f->exec_func = exec_mul_n;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_mul_n_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_mul_n(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MULN */

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// LogicalAnd
#ifdef CONFIG_LOGICALAND
rt_function_error_t allocate_logical_and_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_and;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_and_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_and(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALAND */

// LogicalOr
#ifdef CONFIG_LOGICALOR
rt_function_error_t allocate_logical_or_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_or;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_or_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_or(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALOR */

// LogicalXor
#ifdef CONFIG_LOGICALXOR
rt_function_error_t allocate_logical_xor_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_xor;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_xor_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_xor(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALXOR */

// Equal
#ifdef CONFIG_EQUAL
rt_function_error_t allocate_equal_local_context(rt_function_t *f) {
  f->exec_func = exec_equal;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_EQUAL */

// NotEqual
#ifdef CONFIG_NOTEQUAL
rt_function_error_t allocate_not_equal_local_context(rt_function_t *f) {
  f->exec_func = exec_not_equal;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_not_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_not_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_NOTEQUAL */

// GreaterEqual
#ifdef CONFIG_GREATEREQUAL
rt_function_error_t allocate_greater_equal_local_context(rt_function_t *f) {
  f->exec_func = exec_greater_equal;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GREATEREQUAL */

// Greater
#ifdef CONFIG_GREATER
rt_function_error_t allocate_greater_local_context(rt_function_t *f) {
  f->exec_func = exec_greater;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GREATER */

// LessEqual
#ifdef CONFIG_LESSEQUAL
rt_function_error_t allocate_less_equal_local_context(rt_function_t *f) {
  f->exec_func = exec_less_equal;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_equal_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less_equal(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LESSEQUAL */

// Less
#ifdef CONFIG_LESS
rt_function_error_t allocate_less_local_context(rt_function_t *f) {
  f->exec_func = exec_less;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LESS */

// SearchSorted
#ifdef CONFIG_SEARCHSORTED
rt_function_error_t allocate_searchsorted_local_context(rt_function_t *f) {
  f->exec_func = exec_searchsorted;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_searchsorted_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_searchsorted(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SEARCHSORTED */

// LogicalAndScalar
#ifdef CONFIG_LOGICALANDSCALAR
rt_function_error_t
allocate_logical_and_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_and_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_and_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_and_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALANDSCALAR */

// LogicalOrScalar
#ifdef CONFIG_LOGICALORSCALAR
rt_function_error_t allocate_logical_or_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_or_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_or_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_or_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALORSCALAR */

// LogicalXorScalar
#ifdef CONFIG_LOGICALXORSCALAR
rt_function_error_t
allocate_logical_xor_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_xor_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_xor_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_xor_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALXORSCALAR */

// EqualScalar
#ifdef CONFIG_EQUALSCALAR
rt_function_error_t allocate_equal_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_equal_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_EQUALSCALAR */

// NotEqualScalar
#ifdef CONFIG_NOTEQUALSCALAR
rt_function_error_t allocate_not_equal_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_not_equal_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_not_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_not_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_NOTEQUALSCALAR */

// GreaterEqualScalar
#ifdef CONFIG_GREATEREQUALSCALAR
rt_function_error_t
allocate_greater_equal_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_greater_equal_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GREATEREQUALSCALAR */

// GreaterScalar
#ifdef CONFIG_GREATERSCALAR
rt_function_error_t allocate_greater_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_greater_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_greater_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_greater_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GREATERSCALAR */

// LessEqualScalar
#ifdef CONFIG_LESSEQUALSCALAR
rt_function_error_t allocate_less_equal_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_less_equal_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_equal_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less_equal_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LESSEQUALSCALAR */

// LessScalar
#ifdef CONFIG_LESSSCALAR
rt_function_error_t allocate_less_scalar_local_context(rt_function_t *f) {
  f->exec_func = exec_less_scalar;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_less_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_less_scalar(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LESSSCALAR */

// LogicalNot

#ifdef CONFIG_LOGICALNOT
rt_function_error_t allocate_logical_not_local_context(rt_function_t *f) {
  f->exec_func = exec_logical_not;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_logical_not_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_logical_not(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LOGICALNOT */

// IsNaN
#ifdef CONFIG_ISNAN
rt_function_error_t allocate_isnan_local_context(rt_function_t *f) {
  f->exec_func = exec_isnan;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_isnan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_isnan(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ISNAN */

// IsInf
#ifdef CONFIG_ISINF
rt_function_error_t allocate_isinf_local_context(rt_function_t *f) {
  f->exec_func = exec_isinf;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_isinf_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_isinf(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ISINF */

// ResetNaN
#ifdef CONFIG_RESETNAN
rt_function_error_t allocate_reset_nan_local_context(rt_function_t *f) {
  f->exec_func = exec_reset_nan;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_reset_nan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_reset_nan(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RESETNAN */

// ResetInf
#ifdef CONFIG_RESETINF
rt_function_error_t allocate_reset_inf_local_context(rt_function_t *f) {
  f->exec_func = exec_reset_inf;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_reset_inf_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_reset_inf(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RESETINF */

// Where
#ifdef CONFIG_WHERE
rt_function_error_t allocate_where_local_context(rt_function_t *f) {
  f->exec_func = exec_where;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_where_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_where(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_WHERE */

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
#ifdef CONFIG_CONSTANT
rt_function_error_t allocate_constant_local_context(rt_function_t *f) {
  f->exec_func = exec_constant;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_constant_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_constant(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CONSTANT */

// Arange
#ifdef CONFIG_ARANGE
rt_function_error_t allocate_arange_local_context(rt_function_t *f) {
  f->exec_func = exec_arange;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_arange_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_arange(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ARANGE */

// LINSPACE
#ifdef CONFIG_LINSPACE
rt_function_error_t allocate_linspace_local_context(rt_function_t *f) {
  f->exec_func = exec_linspace;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_linspace_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_linspace(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_LINSPACE */

#ifdef CONFIG_SIN
rt_function_error_t allocate_sin_local_context(rt_function_t *f) {
  f->exec_func = exec_sin;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sin_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sin(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SIN */

#ifdef CONFIG_COS
rt_function_error_t allocate_cos_local_context(rt_function_t *f) {
  f->exec_func = exec_cos;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_cos_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_cos(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_COS */

#ifdef CONFIG_TAN
rt_function_error_t allocate_tan_local_context(rt_function_t *f) {
  f->exec_func = exec_tan;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_tan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_tan(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TAN */

#ifdef CONFIG_SINH
rt_function_error_t allocate_sinh_local_context(rt_function_t *f) {
  f->exec_func = exec_sinh;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sinh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sinh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SINH */

#ifdef CONFIG_COSH
rt_function_error_t allocate_cosh_local_context(rt_function_t *f) {
  f->exec_func = exec_cosh;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_cosh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_cosh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_COSH */

#ifdef CONFIG_ASIN
rt_function_error_t allocate_asin_local_context(rt_function_t *f) {
  f->exec_func = exec_asin;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_asin_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_asin(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ASIN */

#ifdef CONFIG_ACOS
rt_function_error_t allocate_acos_local_context(rt_function_t *f) {
  f->exec_func = exec_acos;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_acos_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_acos(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ACOS */

#ifdef CONFIG_ATAN
rt_function_error_t allocate_atan_local_context(rt_function_t *f) {
  f->exec_func = exec_atan;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_atan_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_atan(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ATAN */

#ifdef CONFIG_ASINH
rt_function_error_t allocate_asinh_local_context(rt_function_t *f) {
  f->exec_func = exec_asinh;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_asinh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_asinh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ASINH */

#ifdef CONFIG_ACOSH
rt_function_error_t allocate_acosh_local_context(rt_function_t *f) {
  f->exec_func = exec_acosh;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_acosh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_acosh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ACOSH */

#ifdef CONFIG_ATANH
rt_function_error_t allocate_atanh_local_context(rt_function_t *f) {
  f->exec_func = exec_atanh;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_atanh_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_atanh(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ATANH */

// Ceil
#ifdef CONFIG_CEIL
rt_function_error_t allocate_ceil_local_context(rt_function_t *f) {
  f->exec_func = exec_ceil;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_ceil_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_ceil(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CEIL */

// Floor
#ifdef CONFIG_FLOOR
rt_function_error_t allocate_floor_local_context(rt_function_t *f) {
  f->exec_func = exec_floor;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_floor_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_floor(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_FLOOR */

// ATan2
#ifdef CONFIG_ATAN2
rt_function_error_t allocate_atan2_local_context(rt_function_t *f) {
  f->exec_func = exec_atan2;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_atan2_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_atan2(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ATAN2 */

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Broadcast
#ifdef CONFIG_BROADCAST
rt_function_error_t allocate_broadcast_local_context(rt_function_t *f) {
  f->exec_func = exec_broadcast;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_broadcast_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_broadcast(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BROADCAST */

// BroadcastTo
#ifdef CONFIG_BROADCASTTO
rt_function_error_t allocate_broadcast_to_local_context(rt_function_t *f) {
  f->exec_func = exec_broadcast_to;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_broadcast_to_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_broadcast_to(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BROADCASTTO */

// Tile
#ifdef CONFIG_TILE
rt_function_error_t allocate_tile_local_context(rt_function_t *f) {
  f->exec_func = exec_tile;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_tile_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_tile(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TILE */

// Gather
#ifdef CONFIG_GATHER
rt_function_error_t allocate_gather_local_context(rt_function_t *f) {
  f->exec_func = exec_gather;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_gather_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_gather(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GATHER */

// Assign
#ifdef CONFIG_ASSIGN
rt_function_error_t allocate_assign_local_context(rt_function_t *f) {
  f->exec_func = exec_assign;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_assign_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_assign(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ASSIGN */

// GatherNd
#ifdef CONFIG_GATHERND
rt_function_error_t allocate_gather_nd_local_context(rt_function_t *f) {
  f->exec_func = exec_gather_nd;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_gather_nd_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_gather_nd(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_GATHERND */

// BoolGather
#ifdef CONFIG_BOOLGATHER
rt_function_error_t allocate_bool_gather_local_context(rt_function_t *f) {
  f->exec_func = exec_bool_gather;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_bool_gather_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_bool_gather(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BOOLGATHER */

// ScatterNd
#ifdef CONFIG_SCATTERND
rt_function_error_t allocate_scatter_nd_local_context(rt_function_t *f) {
  f->exec_func = exec_scatter_nd;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_scatter_nd_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_scatter_nd(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SCATTERND */

// ScatterAdd
#ifdef CONFIG_SCATTERADD
rt_function_error_t allocate_scatter_add_local_context(rt_function_t *f) {
  f->exec_func = exec_scatter_add;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_scatter_add_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_scatter_add(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SCATTERADD */

// BoolScatter
#ifdef CONFIG_BOOLSCATTER
rt_function_error_t allocate_bool_scatter_local_context(rt_function_t *f) {
  f->exec_func = exec_bool_scatter;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_bool_scatter_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_bool_scatter(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BOOLSCATTER */

// BoolFill
#ifdef CONFIG_BOOLFILL
rt_function_error_t allocate_bool_fill_local_context(rt_function_t *f) {
  f->exec_func = exec_bool_fill;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_bool_fill_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_bool_fill(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BOOLFILL */

// PackPaddedSequence
#ifdef CONFIG_PACKPADDEDSEQUENCE
rt_function_error_t
allocate_pack_padded_sequence_local_context(rt_function_t *f) {
  f->exec_func = exec_pack_padded_sequence;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_pack_padded_sequence_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_pack_padded_sequence(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_PACKPADDEDSEQUENCE */

// PadPackedSequence
#ifdef CONFIG_PADPACKEDSEQUENCE
rt_function_error_t
allocate_pad_packed_sequence_local_context(rt_function_t *f) {
  f->exec_func = exec_pad_packed_sequence;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_pad_packed_sequence_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_pad_packed_sequence(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_PADPACKEDSEQUENCE */

// OneHot
#ifdef CONFIG_ONEHOT
rt_function_error_t allocate_one_hot_local_context(rt_function_t *f) {
  f->exec_func = exec_one_hot;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_one_hot_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_one_hot(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ONEHOT */

// Sort
#ifdef CONFIG_SORT
rt_function_error_t allocate_sort_local_context(rt_function_t *f) {
  f->exec_func = exec_sort;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sort_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sort(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SORT */

// Meshgrid
#ifdef CONFIG_MESHGRID
rt_function_error_t allocate_meshgrid_local_context(rt_function_t *f) {
  f->exec_func = exec_meshgrid;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_meshgrid_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_meshgrid(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MESHGRID */

// BatchDet
#ifdef CONFIG_BATCHDET
rt_function_error_t allocate_batch_det_local_context(rt_function_t *f) {
  f->exec_func = exec_batch_det;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_batch_det_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_batch_det(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BATCHDET */

// BatchInv
#ifdef CONFIG_BATCHINV
rt_function_error_t allocate_batch_inv_local_context(rt_function_t *f) {
  f->exec_func = exec_batch_inv;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_batch_inv_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_batch_inv(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BATCHINV */

// BatchLogdet
#ifdef CONFIG_BATCHLOGDET
rt_function_error_t allocate_batch_logdet_local_context(rt_function_t *f) {
  f->exec_func = exec_batch_logdet;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_batch_logdet_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_batch_logdet(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BATCHLOGDET */

// BatchtCholesky
#ifdef CONFIG_BATCHCHOLESKY
rt_function_error_t allocate_batch_cholesky_local_context(rt_function_t *f) {
  f->exec_func = exec_batch_cholesky;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_batch_cholesky_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_batch_cholesky(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BATCHCHOLESKY */

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// TopKData
#ifdef CONFIG_TOPKDATA
rt_function_error_t allocate_top_k_data_local_context(rt_function_t *f) {
  f->exec_func = exec_top_k_data;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t free_top_k_data_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t exec_top_k_data(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TOPKDATA */

// TopKGrad
#ifdef CONFIG_TOPKGRAD
rt_function_error_t allocate_top_k_grad_local_context(rt_function_t *f) {
  f->exec_func = exec_top_k_grad;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t free_top_k_grad_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
rt_function_error_t exec_top_k_grad(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TOPKGRAD */

// Rand
#ifdef CONFIG_RAND
rt_function_error_t allocate_rand_local_context(rt_function_t *f) {
  f->exec_func = exec_rand;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_rand_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_rand(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RAND */

// Randint
#ifdef CONFIG_RANDINT
rt_function_error_t allocate_randint_local_context(rt_function_t *f) {
  f->exec_func = exec_randint;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_randint_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_randint(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDINT */

// Randn
#ifdef CONFIG_RANDN
rt_function_error_t allocate_randn_local_context(rt_function_t *f) {
  f->exec_func = exec_randn;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_randn_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_randn(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDN */

// RandBinomial
#ifdef CONFIG_RANDBINOMIAL
rt_function_error_t allocate_rand_binomial_local_context(rt_function_t *f) {
  f->exec_func = exec_rand_binomial;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_rand_binomial_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_rand_binomial(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDBINOMIAL */

// RandBeta
#ifdef CONFIG_RANDBETA
rt_function_error_t allocate_rand_beta_local_context(rt_function_t *f) {
  f->exec_func = exec_rand_beta;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_rand_beta_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_rand_beta(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDBETA */

// RandGamma
#ifdef CONFIG_RANDGAMMA
rt_function_error_t allocate_rand_gamma_local_context(rt_function_t *f) {
  f->exec_func = exec_rand_gamma;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_rand_gamma_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_rand_gamma(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDGAMMA */

// RandomErase
#ifdef CONFIG_RANDOMERASE
rt_function_error_t allocate_random_erase_local_context(rt_function_t *f) {
  f->exec_func = exec_random_erase;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_erase_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_erase(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDOMERASE */

// RandomChoice
#ifdef CONFIG_RANDOMCHOICE
rt_function_error_t allocate_random_choice_local_context(rt_function_t *f) {
  f->exec_func = exec_random_choice;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_choice_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_choice(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDN */

// RandomCrop
#ifdef CONFIG_RANDOMCROP
rt_function_error_t allocate_random_crop_local_context(rt_function_t *f) {
  f->exec_func = exec_random_crop;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_crop_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_crop(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDOMCROP */

// RandomFlip
#ifdef CONFIG_RANDOMFLIP
rt_function_error_t allocate_random_flip_local_context(rt_function_t *f) {
  f->exec_func = exec_random_flip;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_flip_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_flip(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDOMFLIP */

// RandomShift
#ifdef CONFIG_RANDOMSHIFT
rt_function_error_t allocate_random_shift_local_context(rt_function_t *f) {
  f->exec_func = exec_random_shift;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_random_shift_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_random_shift(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_RANDOMSHIFT */

// ImageAugmentation
#ifdef CONFIG_IMAGEAUGMENTATION
rt_function_error_t
allocate_image_augmentation_local_context(rt_function_t *f) {
  f->exec_func = exec_image_augmentation;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_image_augmentation_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_image_augmentation(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_IMAGEAUGMENTATION */

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy

#ifdef CONFIG_SIGMOIDCROSSENTROPY
rt_function_error_t
allocate_sigmoid_cross_entropy_local_context(rt_function_t *f) {
  f->exec_func = exec_sigmoid_cross_entropy;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sigmoid_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sigmoid_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SIGMOIDCROSSENTROPY */

// BinaryCrossEntropy

#ifdef CONFIG_BINARYCROSSENTROPY
rt_function_error_t
allocate_binary_cross_entropy_local_context(rt_function_t *f) {
  f->exec_func = exec_binary_cross_entropy;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_binary_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_binary_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BINARYCROSSENTROPY */

// SoftmaxCrossEntropy
#ifdef CONFIG_SOFTMAXCROSSENTROPY
rt_function_error_t
allocate_softmax_cross_entropy_local_context(rt_function_t *f) {
  f->exec_func = exec_softmax_cross_entropy;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_softmax_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_softmax_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SOFTMAXCROSSENTROPY */

// CategoricalCrossEntropy
#ifdef CONFIG_CATEGORICALCROSSENTROPY
rt_function_error_t
allocate_categorical_cross_entropy_local_context(rt_function_t *f) {
  f->exec_func = exec_categorical_cross_entropy;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_categorical_cross_entropy_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_categorical_cross_entropy(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CATEGORICALCROSSENTROPY */

// SquaredError

#ifdef CONFIG_SQUAREDERROR
rt_function_error_t allocate_squared_error_local_context(rt_function_t *f) {
  f->exec_func = exec_squared_error;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_squared_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_squared_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SQUAREDERROR */

// AbsoluteError

#ifdef CONFIG_ABSOLUTEERROR
rt_function_error_t allocate_absolute_error_local_context(rt_function_t *f) {
  f->exec_func = exec_absolute_error;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_absolute_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_absolute_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ABSOLUTEERROR */

// HuberLoss
#ifdef CONFIG_HUBERLOSS
rt_function_error_t allocate_huber_loss_local_context(rt_function_t *f) {
  f->exec_func = exec_huber_loss;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_huber_loss_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_huber_loss(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_HUBERLOSS */

// EpsilonInsensitiveLoss
#ifdef CONFIG_EPSILONINSENSITIVELOSS
rt_function_error_t
allocate_epsilon_insensitive_loss_local_context(rt_function_t *f) {
  f->exec_func = exec_epsilon_insensitive_loss;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_epsilon_insensitive_loss_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_epsilon_insensitive_loss(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_EPSILONINSENSITIVELOSS */

// KLMultinomial
#ifdef CONFIG_KLMULTINOMIAL
rt_function_error_t allocate_kl_multinomial_local_context(rt_function_t *f) {
  f->exec_func = exec_kl_multinomial;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_kl_multinomial_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_kl_multinomial(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_KLMULTINOMIAL */

////////////////////////////////////////////////////////////////////////////////
// Geometric Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// AffineGrid
#ifdef CONFIG_AFFINEGRID
rt_function_error_t allocate_affine_grid_local_context(rt_function_t *f) {
  f->exec_func = exec_affine_grid;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_affine_grid_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_affine_grid(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_AFFINEGRID */

// WarpByGrid
#ifdef CONFIG_WARPBYGRID
rt_function_error_t allocate_warp_by_grid_local_context(rt_function_t *f) {
  f->exec_func = exec_warp_by_grid;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_warp_by_grid_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_warp_by_grid(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_WARPBYGRID */

// WarpByFlow
#ifdef CONFIG_WARPBYFLOW
rt_function_error_t allocate_warp_by_flow_local_context(rt_function_t *f) {
  f->exec_func = exec_warp_by_flow;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_warp_by_flow_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_warp_by_flow(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_WARPBYFLOW */

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// INQAffine
#ifdef CONFIG_INQAFFINE
rt_function_error_t allocate_inq_affine_local_context(rt_function_t *f) {
  f->exec_func = exec_inq_affine;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_inq_affine_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_inq_affine(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_INQAFFINE */

// INQConvolution
#ifdef CONFIG_INQCONVOLUTION
rt_function_error_t allocate_inq_convolution_local_context(rt_function_t *f) {
  f->exec_func = exec_inq_convolution;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_inq_convolution_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_inq_convolution(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_INQCONVOLUTION */

// FixedPointQuantize
#ifdef CONFIG_FIXEDPOINTQUANTIZE
rt_function_error_t
allocate_fixed_point_quantize_local_context(rt_function_t *f) {
  f->exec_func = exec_fixed_point_quantize;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_fixed_point_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_fixed_point_quantize(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_FIXEDPOINTQUANTIZE */

// MinMaxQuantize
#ifdef CONFIG_MINMAXQUANTIZE
rt_function_error_t allocate_min_max_quantize_local_context(rt_function_t *f) {
  f->exec_func = exec_min_max_quantize;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_min_max_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_min_max_quantize(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MINMAXQUANTIZE */

// Pow2Quantize
#ifdef CONFIG_POW2QUANTIZE
rt_function_error_t allocate_pow2_quantize_local_context(rt_function_t *f) {
  f->exec_func = exec_pow2_quantize;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_pow2_quantize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_pow2_quantize(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_POW2QUANTIZE */

// Prune
#ifdef CONFIG_PRUNE
rt_function_error_t allocate_prune_local_context(rt_function_t *f) {
  f->exec_func = exec_prune;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_prune_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_prune(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_PRUNE */

// QuantizeLinear
#ifdef CONFIG_QUANTIZELINEAR
rt_function_error_t allocate_quantize_linear_local_context(rt_function_t *f) {
  f->exec_func = exec_quantize_linear;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_quantize_linear_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_quantize_linear(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_QUANTIZELINEAR */

// DequantizeLinear
#ifdef CONFIG_DEQUANTIZELINEAR
rt_function_error_t allocate_dequantize_linear_local_context(rt_function_t *f) {
  f->exec_func = exec_dequantize_linear;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_dequantize_linear_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_dequantize_linear(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_DEQUANTIZELINEAR */

////////////////////////////////////////////////////////////////////////////////
// Spectral Operation
////////////////////////////////////////////////////////////////////////////////

// Interpolate
#ifdef CONFIG_INTERPOLATE
rt_function_error_t allocate_interpolate_local_context(rt_function_t *f) {
  f->exec_func = exec_interpolate;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_interpolate_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_interpolate(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_INTERPOLATE */

// FFT
#ifdef CONFIG_FFT
rt_function_error_t allocate_fft_local_context(rt_function_t *f) {
  f->exec_func = exec_fft;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_fft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_fft(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_FFT */

// IFFT
#ifdef CONFIG_IFFT
rt_function_error_t allocate_ifft_local_context(rt_function_t *f) {
  f->exec_func = exec_ifft;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_ifft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_ifft(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_IFFT */

// STFT
#ifdef CONFIG_STFT
rt_function_error_t allocate_stft_local_context(rt_function_t *f) {
  f->exec_func = exec_stft;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_stft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_stft(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_STFT */

// ISTFT
#ifdef CONFIG_ISTFT
rt_function_error_t allocate_istft_local_context(rt_function_t *f) {
  f->exec_func = exec_istft;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_istft_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_istft(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ISTFT */

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
#ifdef CONFIG_TOPNERROR
rt_function_error_t allocate_top_n_error_local_context(rt_function_t *f) {
  f->exec_func = exec_top_n_error;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_top_n_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_top_n_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_TOPNERROR */

// BinaryError

#ifdef CONFIG_BINARYERROR
rt_function_error_t allocate_binary_error_local_context(rt_function_t *f) {
  f->exec_func = exec_binary_error;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_binary_error_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_binary_error(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_BINARYERROR */

// ConfusionMatrix
#ifdef CONFIG_CONFUSIONMATRIX
rt_function_error_t allocate_confusion_matrix_local_context(rt_function_t *f) {
  f->exec_func = exec_confusion_matrix;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_confusion_matrix_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_confusion_matrix(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_CONFUSIONMATRIX */

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
#ifdef CONFIG_VATNOISE
rt_function_error_t allocate_vat_noise_local_context(rt_function_t *f) {
  f->exec_func = exec_vat_noise;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_vat_noise_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_vat_noise(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_VATNOISE */

// Unlink

#ifdef CONFIG_UNLINK
rt_function_error_t allocate_unlink_local_context(rt_function_t *f) {
  f->exec_func = exec_unlink;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_unlink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_unlink(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_UNLINK */

// Sink
#ifdef CONFIG_SINK
rt_function_error_t allocate_sink_local_context(rt_function_t *f) {
  f->exec_func = exec_sink;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_sink_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_sink(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SINK */

// NmsDetection2d
#ifdef CONFIG_NMSDETECTION2D
rt_function_error_t allocate_nms_detection2d_local_context(rt_function_t *f) {
  f->exec_func = exec_nms_detection2d;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_nms_detection2d_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_nms_detection2d(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_NMSDETECTION2D */

// MaxPoolingBackward
#ifdef CONFIG_MAXPOOLINGBACKWARD
rt_function_error_t
allocate_max_pooling_backward_local_context(rt_function_t *f) {
  f->exec_func = exec_nms_detection2d;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_max_pooling_backward_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_max_pooling_backward(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_MAXPOOLINGBACKWARD */

// PatchCorrelation
#ifdef CONFIG_PATCHCORRELATION
rt_function_error_t allocate_patch_correlation_local_context(rt_function_t *f) {
  f->exec_func = exec_patch_correlation;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_patch_correlation_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_patch_correlation(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_PATCHCORRELATION */

// Shape
#ifdef CONFIG_SHAPE
rt_function_error_t allocate_shape_local_context(rt_function_t *f) {
  f->exec_func = exec_shape;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_shape_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_shape(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_SHAPE */

// Erf
#ifdef CONFIG_ERF
rt_function_error_t allocate_erf_local_context(rt_function_t *f) {
  f->exec_func = exec_erf;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_erf_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_erf(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ERF */

// OnnxResize
#ifdef CONFIG_ONNXRESIZE
rt_function_error_t allocate_onnx_resize_local_context(rt_function_t *f) {
  f->exec_func = exec_onnx_resize;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_onnx_resize_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_onnx_resize(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ONNXRESIZE */

// Nonzero
#ifdef CONFIG_NONZERO
rt_function_error_t allocate_nonzero_local_context(rt_function_t *f) {
  f->exec_func = exec_nonzero;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t free_nonzero_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_nonzero(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_NONZERO */

// OnnxNonMaxSuppression
#ifdef CONFIG_ONNXNONMAXSUPPRESSION
rt_function_error_t
allocate_onnx_non_max_suppression_local_context(rt_function_t *f) {
  f->exec_func = exec_onnx_non_max_suppression;
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t
free_onnx_non_max_suppression_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}

rt_function_error_t exec_onnx_non_max_suppression(rt_function_t *f) {
  return RT_FUNCTION_ERROR_UNIMPLEMENTED;
}
#endif /* CONFIG_ONNXNONMAXSUPPRESSION */
