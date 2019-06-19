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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Functions Functions
/// @brief Feed forward function implementations.
/// @{

/// @brief Error definitions
typedef enum {
  RT_FUNCTION_ERROR_UNIMPLEMENTED = -999,   ///< Invalid shape. (-999)
  RT_FUNCTION_ERROR_MALLOC,                 ///< Memory allocation error. (-998)
  RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS,  ///< Invalid number of inputs.(-997)
  RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS, ///< Invalid number of outputs.
                                            ///(-996)
  RT_FUNCTION_ERROR_INVALID_SHAPE,          ///< Invalid shape. (-995)
  RT_FUNCTION_ERROR_NOERROR = 0             ///< No error. (0)
} rt_function_error_t;

/// @brief List
typedef struct {
  int size;  ///< Size of list
  int *data; ///< Data
} rt_list_t;

/// @brief Allocation type
typedef enum {
  RT_BUFFER_ALLOCATE_TYPE_MALLOC = 0, ///< Allocated by runtime
  RT_BUFFER_ALLOCATE_TYPE_ALLOCATED,  ///< User allocated
  RT_BUFFER_ALLOCATE_TYPE_INITIAL,    ///< Shared buffers
  END_OF_RT_BUFFER_ALLOCATE_TYPE      ///< Max num of rt_buffer_allocate_type_t
} rt_buffer_allocate_type_t;

/// @brief Variable
typedef struct {
  rt_list_t shape;         ///< Shape of variable
  nn_data_type_t type : 4; ///< Type of param values
  unsigned int fp_pos : 4; ///< Fixed point position
  float coefficient;       ///< Coefficient value for convert int to float.
  void *data;              ///< Pointer to real data of variable
} rt_variable_t;

/// @brief Function
struct st_rt_function_t;
typedef struct st_rt_function_t rt_function_t;

struct st_rt_function_t {
  int num_of_inputs;       ///< Number of inputs
  rt_variable_t **inputs;  ///< List of input variable
  int num_of_outputs;      ///< Number of outputs
  rt_variable_t **outputs; ///< List of output variable

  rt_function_error_t (*exec_func)(rt_function_t *f);
  rt_function_error_t (*free_local_context_func)(rt_function_t *f);

  void *local_context; ///< General purpose context
};

extern void *(*rt_variable_malloc_func)(
    size_t size); ///< Variable malloc function pointer
extern void (*rt_variable_free_func)(
    void *ptr); ///< Variable free function pointer

extern void *(*rt_malloc_func)(size_t size); ///< malloc function pointer
extern void (*rt_free_func)(void *ptr);      ///< free function pointer

////////////////////////////////////////////////////////////////////////////////
/// @defgroup NeuralNetworkLayer Neural Network Layer
/// @{

/// @defgroup Affine Affine
/// @{

/// Local context for Affine
typedef struct {
  int32_t base_axis; ///< int64
  void *data;        ///< General purpose data area
} affine_local_context_t;

/// Allocate Affine local context
rt_function_error_t allocate_affine_local_context(rt_function_t *f);

/// Free Affine local context
rt_function_error_t free_affine_local_context(rt_function_t *f);

/// Exec Affine
rt_function_error_t exec_affine(rt_function_t *f);
/// @}

/// @defgroup RNN RNN
/// @{

/// Named values for RNN.nonlinearity
typedef enum {
  RNN_NONLINEARITY_TANH,
  RNN_NONLINEARITY_RELU,
  END_OF_RNN_NONLINEARITY
} rnn_nonlinearity_value_t;

/// Local context for RNN
typedef struct {
  int32_t num_layers;                    ///< int64
  rnn_nonlinearity_value_t nonlinearity; ///< string
  float dropout;                         ///< float
  uint8_t bidirectional;                 ///< bool
  uint8_t training;                      ///< bool
  void *data;                            ///< General purpose data area
} rnn_local_context_t;

/// Allocate RNN local context
rt_function_error_t allocate_rnn_local_context(rt_function_t *f);

/// Free RNN local context
rt_function_error_t free_rnn_local_context(rt_function_t *f);

/// Exec RNN
rt_function_error_t exec_rnn(rt_function_t *f);
/// @}

/// @defgroup LSTM LSTM
/// @{

/// Local context for LSTM
typedef struct {
  int32_t num_layers;    ///< int64
  float dropout;         ///< float
  uint8_t bidirectional; ///< bool
  uint8_t training;      ///< bool
  void *data;            ///< General purpose data area
} lstm_local_context_t;

/// Allocate LSTM local context
rt_function_error_t allocate_lstm_local_context(rt_function_t *f);

/// Free LSTM local context
rt_function_error_t free_lstm_local_context(rt_function_t *f);

/// Exec LSTM
rt_function_error_t exec_lstm(rt_function_t *f);
/// @}

/// @defgroup GRU GRU
/// @{

/// Local context for GRU
typedef struct {
  int32_t num_layers;    ///< int64
  float dropout;         ///< float
  uint8_t bidirectional; ///< bool
  uint8_t training;      ///< bool
  void *data;            ///< General purpose data area
} gru_local_context_t;

/// Allocate GRU local context
rt_function_error_t allocate_gru_local_context(rt_function_t *f);

/// Free GRU local context
rt_function_error_t free_gru_local_context(rt_function_t *f);

/// Exec GRU
rt_function_error_t exec_gru(rt_function_t *f);
/// @}

/// @defgroup Convolution Convolution
/// @{

/// Local context for Convolution
typedef struct {
  int32_t base_axis;    ///< int64
  rt_list_t pad;        ///< Original type is [Shape]
  rt_list_t stride;     ///< Original type is [Shape]
  rt_list_t dilation;   ///< Original type is [Shape]
  int32_t group;        ///< int64
  uint8_t channel_last; ///< bool
  void *data;           ///< General purpose data area
} convolution_local_context_t;

/// Allocate Convolution local context
rt_function_error_t allocate_convolution_local_context(rt_function_t *f);

/// Free Convolution local context
rt_function_error_t free_convolution_local_context(rt_function_t *f);

/// Exec Convolution
rt_function_error_t exec_convolution(rt_function_t *f);
/// @}

/// @defgroup DepthwiseConvolution DepthwiseConvolution
/// @{

/// Local context for DepthwiseConvolution
typedef struct {
  int32_t base_axis;  ///< int64
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t multiplier; ///< int64
  void *data;         ///< General purpose data area
} depthwise_convolution_local_context_t;

/// Allocate DepthwiseConvolution local context
rt_function_error_t
allocate_depthwise_convolution_local_context(rt_function_t *f);

/// Free DepthwiseConvolution local context
rt_function_error_t free_depthwise_convolution_local_context(rt_function_t *f);

/// Exec DepthwiseConvolution
rt_function_error_t exec_depthwise_convolution(rt_function_t *f);
/// @}

/// @defgroup Deconvolution Deconvolution
/// @{

/// Local context for Deconvolution
typedef struct {
  int32_t base_axis;  ///< int64
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;      ///< int64
  void *data;         ///< General purpose data area
} deconvolution_local_context_t;

/// Allocate Deconvolution local context
rt_function_error_t allocate_deconvolution_local_context(rt_function_t *f);

/// Free Deconvolution local context
rt_function_error_t free_deconvolution_local_context(rt_function_t *f);

/// Exec Deconvolution
rt_function_error_t exec_deconvolution(rt_function_t *f);
/// @}

/// @defgroup DepthwiseDeconvolution DepthwiseDeconvolution
/// @{

/// Local context for DepthwiseDeconvolution
typedef struct {
  int32_t base_axis;  ///< int64
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t divisor;    ///< int64
  void *data;         ///< General purpose data area
} depthwise_deconvolution_local_context_t;

/// Allocate DepthwiseDeconvolution local context
rt_function_error_t
allocate_depthwise_deconvolution_local_context(rt_function_t *f);

/// Free DepthwiseDeconvolution local context
rt_function_error_t
free_depthwise_deconvolution_local_context(rt_function_t *f);

/// Exec DepthwiseDeconvolution
rt_function_error_t exec_depthwise_deconvolution(rt_function_t *f);
/// @}

/// @defgroup MaxPooling MaxPooling
/// @{

/// Local context for MaxPooling
typedef struct {
  rt_list_t kernel;      ///< Original type is [Shape]
  rt_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< bool
  rt_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< bool
  void *data;            ///< General purpose data area
} max_pooling_local_context_t;

/// Allocate MaxPooling local context
rt_function_error_t allocate_max_pooling_local_context(rt_function_t *f);

/// Free MaxPooling local context
rt_function_error_t free_max_pooling_local_context(rt_function_t *f);

/// Exec MaxPooling
rt_function_error_t exec_max_pooling(rt_function_t *f);
/// @}

/// @defgroup AveragePooling AveragePooling
/// @{

/// Local context for AveragePooling
typedef struct {
  rt_list_t kernel;      ///< Original type is [Shape]
  rt_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< bool
  rt_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< bool
  uint8_t including_pad; ///< bool
  void *data;            ///< General purpose data area
} average_pooling_local_context_t;

/// Allocate AveragePooling local context
rt_function_error_t allocate_average_pooling_local_context(rt_function_t *f);

/// Free AveragePooling local context
rt_function_error_t free_average_pooling_local_context(rt_function_t *f);

/// Exec AveragePooling
rt_function_error_t exec_average_pooling(rt_function_t *f);
/// @}

/// @defgroup GlobalAveragePooling GlobalAveragePooling
/// @{

/// Allocate GlobalAveragePooling local context
rt_function_error_t
allocate_global_average_pooling_local_context(rt_function_t *f);

/// Free GlobalAveragePooling local context
rt_function_error_t free_global_average_pooling_local_context(rt_function_t *f);

/// Exec GlobalAveragePooling
rt_function_error_t exec_global_average_pooling(rt_function_t *f);
/// @}

/// @defgroup SumPooling SumPooling
/// @{

/// Local context for SumPooling
typedef struct {
  rt_list_t kernel;      ///< Original type is [Shape]
  rt_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< bool
  rt_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< bool
  void *data;            ///< General purpose data area
} sum_pooling_local_context_t;

/// Allocate SumPooling local context
rt_function_error_t allocate_sum_pooling_local_context(rt_function_t *f);

/// Free SumPooling local context
rt_function_error_t free_sum_pooling_local_context(rt_function_t *f);

/// Exec SumPooling
rt_function_error_t exec_sum_pooling(rt_function_t *f);
/// @}

/// @defgroup Unpooling Unpooling
/// @{

/// Local context for Unpooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  void *data;       ///< General purpose data area
} unpooling_local_context_t;

/// Allocate Unpooling local context
rt_function_error_t allocate_unpooling_local_context(rt_function_t *f);

/// Free Unpooling local context
rt_function_error_t free_unpooling_local_context(rt_function_t *f);

/// Exec Unpooling
rt_function_error_t exec_unpooling(rt_function_t *f);
/// @}

/// @defgroup Embed Embed
/// @{

/// Allocate Embed local context
rt_function_error_t allocate_embed_local_context(rt_function_t *f);

/// Free Embed local context
rt_function_error_t free_embed_local_context(rt_function_t *f);

/// Exec Embed
rt_function_error_t exec_embed(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup NeuralNetworkActivationFunctions Neural Network Activation
/// Functions
/// @{

/// @defgroup Sigmoid Sigmoid
/// @{

/// Allocate Sigmoid local context
rt_function_error_t allocate_sigmoid_local_context(rt_function_t *f);

/// Free Sigmoid local context
rt_function_error_t free_sigmoid_local_context(rt_function_t *f);

/// Exec Sigmoid
rt_function_error_t exec_sigmoid(rt_function_t *f);
/// @}

/// @defgroup Swish Swish
/// @{

/// Allocate Swish local context
rt_function_error_t allocate_swish_local_context(rt_function_t *f);

/// Free Swish local context
rt_function_error_t free_swish_local_context(rt_function_t *f);

/// Exec Swish
rt_function_error_t exec_swish(rt_function_t *f);
/// @}

/// @defgroup Tanh Tanh
/// @{

/// Allocate Tanh local context
rt_function_error_t allocate_tanh_local_context(rt_function_t *f);

/// Free Tanh local context
rt_function_error_t free_tanh_local_context(rt_function_t *f);

/// Exec Tanh
rt_function_error_t exec_tanh(rt_function_t *f);
/// @}

/// @defgroup ReLU ReLU
/// @{

/// Local context for ReLU
typedef struct {
  uint8_t inplace; ///< bool
  void *data;      ///< General purpose data area
} relu_local_context_t;

/// Allocate ReLU local context
rt_function_error_t allocate_relu_local_context(rt_function_t *f);

/// Free ReLU local context
rt_function_error_t free_relu_local_context(rt_function_t *f);

/// Exec ReLU
rt_function_error_t exec_relu(rt_function_t *f);
/// @}

/// @defgroup LeakyReLU LeakyReLU
/// @{

/// Local context for LeakyReLU
typedef struct {
  float alpha;     ///< float
  uint8_t inplace; ///< bool
  void *data;      ///< General purpose data area
} leaky_relu_local_context_t;

/// Allocate LeakyReLU local context
rt_function_error_t allocate_leaky_relu_local_context(rt_function_t *f);

/// Free LeakyReLU local context
rt_function_error_t free_leaky_relu_local_context(rt_function_t *f);

/// Exec LeakyReLU
rt_function_error_t exec_leaky_relu(rt_function_t *f);
/// @}

/// @defgroup Softmax Softmax
/// @{

/// Local context for Softmax
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} softmax_local_context_t;

/// Allocate Softmax local context
rt_function_error_t allocate_softmax_local_context(rt_function_t *f);

/// Free Softmax local context
rt_function_error_t free_softmax_local_context(rt_function_t *f);

/// Exec Softmax
rt_function_error_t exec_softmax(rt_function_t *f);
/// @}

/// @defgroup LogSoftmax LogSoftmax
/// @{

/// Local context for LogSoftmax
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} log_softmax_local_context_t;

/// Allocate LogSoftmax local context
rt_function_error_t allocate_log_softmax_local_context(rt_function_t *f);

/// Free LogSoftmax local context
rt_function_error_t free_log_softmax_local_context(rt_function_t *f);

/// Exec LogSoftmax
rt_function_error_t exec_log_softmax(rt_function_t *f);
/// @}

/// @defgroup ELU ELU
/// @{

/// Local context for ELU
typedef struct {
  float alpha; ///< double
  void *data;  ///< General purpose data area
} elu_local_context_t;

/// Allocate ELU local context
rt_function_error_t allocate_elu_local_context(rt_function_t *f);

/// Free ELU local context
rt_function_error_t free_elu_local_context(rt_function_t *f);

/// Exec ELU
rt_function_error_t exec_elu(rt_function_t *f);
/// @}

/// @defgroup SELU SELU
/// @{

/// Local context for SELU
typedef struct {
  float scale; ///< double
  float alpha; ///< double
  void *data;  ///< General purpose data area
} selu_local_context_t;

/// Allocate SELU local context
rt_function_error_t allocate_selu_local_context(rt_function_t *f);

/// Free SELU local context
rt_function_error_t free_selu_local_context(rt_function_t *f);

/// Exec SELU
rt_function_error_t exec_selu(rt_function_t *f);
/// @}

/// @defgroup CReLU CReLU
/// @{

/// Local context for CReLU
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} crelu_local_context_t;

/// Allocate CReLU local context
rt_function_error_t allocate_crelu_local_context(rt_function_t *f);

/// Free CReLU local context
rt_function_error_t free_crelu_local_context(rt_function_t *f);

/// Exec CReLU
rt_function_error_t exec_crelu(rt_function_t *f);
/// @}

/// @defgroup CELU CELU
/// @{

/// Local context for CELU
typedef struct {
  float alpha;  ///< double
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} celu_local_context_t;

/// Allocate CELU local context
rt_function_error_t allocate_celu_local_context(rt_function_t *f);

/// Free CELU local context
rt_function_error_t free_celu_local_context(rt_function_t *f);

/// Exec CELU
rt_function_error_t exec_celu(rt_function_t *f);
/// @}

/// @defgroup PReLU PReLU
/// @{

/// Local context for PReLU
typedef struct {
  int32_t base_axis; ///< int64
  void *data;        ///< General purpose data area
} prelu_local_context_t;

/// Allocate PReLU local context
rt_function_error_t allocate_prelu_local_context(rt_function_t *f);

/// Free PReLU local context
rt_function_error_t free_prelu_local_context(rt_function_t *f);

/// Exec PReLU
rt_function_error_t exec_prelu(rt_function_t *f);
/// @}

/// @defgroup GELU GELU
/// @{

/// Allocate GELU local context
rt_function_error_t allocate_gelu_local_context(rt_function_t *f);

/// Free GELU local context
rt_function_error_t free_gelu_local_context(rt_function_t *f);

/// Exec GELU
rt_function_error_t exec_gelu(rt_function_t *f);
/// @}

/// @defgroup ReLU6 ReLU6
/// @{

/// Allocate ReLU6 local context
rt_function_error_t allocate_relu6_local_context(rt_function_t *f);

/// Free ReLU6 local context
rt_function_error_t free_relu6_local_context(rt_function_t *f);

/// Exec ReLU6
rt_function_error_t exec_relu6(rt_function_t *f);
/// @}

/// @defgroup HardSigmoid HardSigmoid
/// @{

/// Allocate HardSigmoid local context
rt_function_error_t allocate_hard_sigmoid_local_context(rt_function_t *f);

/// Free HardSigmoid local context
rt_function_error_t free_hard_sigmoid_local_context(rt_function_t *f);

/// Exec HardSigmoid
rt_function_error_t exec_hard_sigmoid(rt_function_t *f);
/// @}

/// @defgroup HardTanh HardTanh
/// @{

/// Allocate HardTanh local context
rt_function_error_t allocate_hard_tanh_local_context(rt_function_t *f);

/// Free HardTanh local context
rt_function_error_t free_hard_tanh_local_context(rt_function_t *f);

/// Exec HardTanh
rt_function_error_t exec_hard_tanh(rt_function_t *f);
/// @}

/// @defgroup LogSigmoid LogSigmoid
/// @{

/// Allocate LogSigmoid local context
rt_function_error_t allocate_log_sigmoid_local_context(rt_function_t *f);

/// Free LogSigmoid local context
rt_function_error_t free_log_sigmoid_local_context(rt_function_t *f);

/// Exec LogSigmoid
rt_function_error_t exec_log_sigmoid(rt_function_t *f);
/// @}

/// @defgroup SoftPlus SoftPlus
/// @{

/// Allocate SoftPlus local context
rt_function_error_t allocate_softplus_local_context(rt_function_t *f);

/// Free SoftPlus local context
rt_function_error_t free_softplus_local_context(rt_function_t *f);

/// Exec SoftPlus
rt_function_error_t exec_softplus(rt_function_t *f);
/// @}

/// @defgroup SoftSign SoftSign
/// @{

/// Allocate SoftSign local context
rt_function_error_t allocate_softsign_local_context(rt_function_t *f);

/// Free SoftSign local context
rt_function_error_t free_softsign_local_context(rt_function_t *f);

/// Exec SoftSign
rt_function_error_t exec_softsign(rt_function_t *f);
/// @}

/// @defgroup TanhShrink TanhShrink
/// @{

/// Allocate TanhShrink local context
rt_function_error_t allocate_tanh_shrink_local_context(rt_function_t *f);

/// Free TanhShrink local context
rt_function_error_t free_tanh_shrink_local_context(rt_function_t *f);

/// Exec TanhShrink
rt_function_error_t exec_tanh_shrink(rt_function_t *f);
/// @}

/// @defgroup Sinc Sinc
/// @{

/// Allocate Sinc local context
rt_function_error_t allocate_sinc_local_context(rt_function_t *f);

/// Free Sinc local context
rt_function_error_t free_sinc_local_context(rt_function_t *f);

/// Exec Sinc
rt_function_error_t exec_sinc(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Normalization Normalization
/// @{

/// @defgroup FusedBatchNormalization FusedBatchNormalization
/// @{

/// Named values for FusedBatchNormalization.nonlinearity
typedef enum {
  FUSED_BATCH_NORMALIZATION_NONLINEARITY_RELU,
  END_OF_FUSED_BATCH_NORMALIZATION_NONLINEARITY
} fused_batch_normalization_nonlinearity_value_t;

/// Local context for FusedBatchNormalization
typedef struct {
  rt_list_t axes;     ///< Original type is [repeated int64]
  float decay_rate;   ///< float
  float eps;          ///< float
  uint8_t batch_stat; ///< bool
  fused_batch_normalization_nonlinearity_value_t nonlinearity; ///< string
  void *data; ///< General purpose data area
} fused_batch_normalization_local_context_t;

/// Allocate FusedBatchNormalization local context
rt_function_error_t
allocate_fused_batch_normalization_local_context(rt_function_t *f);

/// Free FusedBatchNormalization local context
rt_function_error_t
free_fused_batch_normalization_local_context(rt_function_t *f);

/// Exec FusedBatchNormalization
rt_function_error_t exec_fused_batch_normalization(rt_function_t *f);
/// @}

/// @defgroup BatchNormalization BatchNormalization
/// @{

/// Local context for BatchNormalization
typedef struct {
  rt_list_t axes;     ///< Original type is [repeated int64]
  float decay_rate;   ///< float
  float eps;          ///< float
  uint8_t batch_stat; ///< bool
  void *data;         ///< General purpose data area
} batch_normalization_local_context_t;

/// Allocate BatchNormalization local context
rt_function_error_t
allocate_batch_normalization_local_context(rt_function_t *f);

/// Free BatchNormalization local context
rt_function_error_t free_batch_normalization_local_context(rt_function_t *f);

/// Exec BatchNormalization
rt_function_error_t exec_batch_normalization(rt_function_t *f);
/// @}

/// @defgroup SyncBatchNormalization SyncBatchNormalization
/// @{

/// Named values for SyncBatchNormalization.group
typedef enum {
  SYNC_BATCH_NORMALIZATION_GROUP_WORLD,
  END_OF_SYNC_BATCH_NORMALIZATION_GROUP
} sync_batch_normalization_group_value_t;

/// Local context for SyncBatchNormalization
typedef struct {
  sync_batch_normalization_group_value_t group; ///< string
  rt_list_t axes;     ///< Original type is [repeated int64]
  float decay_rate;   ///< float
  float eps;          ///< float
  uint8_t batch_stat; ///< bool
  void *data;         ///< General purpose data area
} sync_batch_normalization_local_context_t;

/// Allocate SyncBatchNormalization local context
rt_function_error_t
allocate_sync_batch_normalization_local_context(rt_function_t *f);

/// Free SyncBatchNormalization local context
rt_function_error_t
free_sync_batch_normalization_local_context(rt_function_t *f);

/// Exec SyncBatchNormalization
rt_function_error_t exec_sync_batch_normalization(rt_function_t *f);
/// @}

/// @defgroup MeanSubtraction MeanSubtraction
/// @{

/// Local context for MeanSubtraction
typedef struct {
  int32_t base_axis;           ///< int64
  uint8_t update_running_mean; ///< bool
  void *data;                  ///< General purpose data area
} mean_subtraction_local_context_t;

/// Allocate MeanSubtraction local context
rt_function_error_t allocate_mean_subtraction_local_context(rt_function_t *f);

/// Free MeanSubtraction local context
rt_function_error_t free_mean_subtraction_local_context(rt_function_t *f);

/// Exec MeanSubtraction
rt_function_error_t exec_mean_subtraction(rt_function_t *f);
/// @}

/// @defgroup ClipGradByValue ClipGradByValue
/// @{

/// Allocate ClipGradByValue local context
rt_function_error_t allocate_clip_grad_by_value_local_context(rt_function_t *f);

/// Free ClipGradByValue local context
rt_function_error_t free_clip_grad_by_value_local_context(rt_function_t *f);

/// Exec ClipGradByValue
rt_function_error_t exec_clip_grad_by_value(rt_function_t *f);
/// @}

/// @defgroup ClipGradByNorm ClipGradByNorm
/// @{

/// Local context for ClipGradByNorm
typedef struct {
  float clip_norm; ///< float
  rt_list_t axes;  ///< Original type is [repeated int64]
  void *data;      ///< General purpose data area
} clip_grad_by_norm_local_context_t;

/// Allocate ClipGradByNorm local context
rt_function_error_t allocate_clip_grad_by_norm_local_context(rt_function_t *f);

/// Free ClipGradByNorm local context
rt_function_error_t free_clip_grad_by_norm_local_context(rt_function_t *f);

/// Exec ClipGradByNorm
rt_function_error_t exec_clip_grad_by_norm(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Reduction Reduction
/// @{

/// @defgroup Sum Sum
/// @{

/// Local context for Sum
typedef struct {
  rt_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< bool
  void *data;        ///< General purpose data area
} sum_local_context_t;

/// Allocate Sum local context
rt_function_error_t allocate_sum_local_context(rt_function_t *f);

/// Free Sum local context
rt_function_error_t free_sum_local_context(rt_function_t *f);

/// Exec Sum
rt_function_error_t exec_sum(rt_function_t *f);
/// @}

/// @defgroup Mean Mean
/// @{

/// Local context for Mean
typedef struct {
  rt_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< bool
  void *data;        ///< General purpose data area
} mean_local_context_t;

/// Allocate Mean local context
rt_function_error_t allocate_mean_local_context(rt_function_t *f);

/// Free Mean local context
rt_function_error_t free_mean_local_context(rt_function_t *f);

/// Exec Mean
rt_function_error_t exec_mean(rt_function_t *f);
/// @}

/// @defgroup Max Max
/// @{

/// Local context for Max
typedef struct {
  rt_list_t axes;     ///< Original type is [repeated int64]
  uint8_t keep_dims;  ///< bool
  uint8_t with_index; ///< bool
  uint8_t only_index; ///< bool
  void *data;         ///< General purpose data area
} max_local_context_t;

/// Allocate Max local context
rt_function_error_t allocate_max_local_context(rt_function_t *f);

/// Free Max local context
rt_function_error_t free_max_local_context(rt_function_t *f);

/// Exec Max
rt_function_error_t exec_max(rt_function_t *f);
/// @}

/// @defgroup Min Min
/// @{

/// Local context for Min
typedef struct {
  rt_list_t axes;     ///< Original type is [repeated int64]
  uint8_t keep_dims;  ///< bool
  uint8_t with_index; ///< bool
  uint8_t only_index; ///< bool
  void *data;         ///< General purpose data area
} min_local_context_t;

/// Allocate Min local context
rt_function_error_t allocate_min_local_context(rt_function_t *f);

/// Free Min local context
rt_function_error_t free_min_local_context(rt_function_t *f);

/// Exec Min
rt_function_error_t exec_min(rt_function_t *f);
/// @}

/// @defgroup Prod Prod
/// @{

/// Local context for Prod
typedef struct {
  rt_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< bool
  void *data;        ///< General purpose data area
} prod_local_context_t;

/// Allocate Prod local context
rt_function_error_t allocate_prod_local_context(rt_function_t *f);

/// Free Prod local context
rt_function_error_t free_prod_local_context(rt_function_t *f);

/// Exec Prod
rt_function_error_t exec_prod(rt_function_t *f);
/// @}

/// @defgroup ReduceSum ReduceSum
/// @{

/// Allocate ReduceSum local context
rt_function_error_t allocate_reduce_sum_local_context(rt_function_t *f);

/// Free ReduceSum local context
rt_function_error_t free_reduce_sum_local_context(rt_function_t *f);

/// Exec ReduceSum
rt_function_error_t exec_reduce_sum(rt_function_t *f);
/// @}

/// @defgroup ReduceMean ReduceMean
/// @{

/// Allocate ReduceMean local context
rt_function_error_t allocate_reduce_mean_local_context(rt_function_t *f);

/// Free ReduceMean local context
rt_function_error_t free_reduce_mean_local_context(rt_function_t *f);

/// Exec ReduceMean
rt_function_error_t exec_reduce_mean(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Arithmetic Arithmetic
/// @{

/// @defgroup Add2 Add2
/// @{

/// Local context for Add2
typedef struct {
  uint8_t inplace; ///< bool
  void *data;      ///< General purpose data area
} add2_local_context_t;

/// Allocate Add2 local context
rt_function_error_t allocate_add2_local_context(rt_function_t *f);

/// Free Add2 local context
rt_function_error_t free_add2_local_context(rt_function_t *f);

/// Exec Add2
rt_function_error_t exec_add2(rt_function_t *f);
/// @}

/// @defgroup BcAdd2 BcAdd2
/// @{

/// Allocate BcAdd2 local context
rt_function_error_t allocate_bc_add2_local_context(rt_function_t *f);

/// Free BcAdd2 local context
rt_function_error_t free_bc_add2_local_context(rt_function_t *f);

/// Exec BcAdd2
rt_function_error_t exec_bc_add2(rt_function_t *f);
/// @}

/// @defgroup Sub2 Sub2
/// @{

/// Allocate Sub2 local context
rt_function_error_t allocate_sub2_local_context(rt_function_t *f);

/// Free Sub2 local context
rt_function_error_t free_sub2_local_context(rt_function_t *f);

/// Exec Sub2
rt_function_error_t exec_sub2(rt_function_t *f);
/// @}

/// @defgroup Mul2 Mul2
/// @{

/// Allocate Mul2 local context
rt_function_error_t allocate_mul2_local_context(rt_function_t *f);

/// Free Mul2 local context
rt_function_error_t free_mul2_local_context(rt_function_t *f);

/// Exec Mul2
rt_function_error_t exec_mul2(rt_function_t *f);
/// @}

/// @defgroup Div2 Div2
/// @{

/// Allocate Div2 local context
rt_function_error_t allocate_div2_local_context(rt_function_t *f);

/// Free Div2 local context
rt_function_error_t free_div2_local_context(rt_function_t *f);

/// Exec Div2
rt_function_error_t exec_div2(rt_function_t *f);
/// @}

/// @defgroup Pow2 Pow2
/// @{

/// Allocate Pow2 local context
rt_function_error_t allocate_pow2_local_context(rt_function_t *f);

/// Free Pow2 local context
rt_function_error_t free_pow2_local_context(rt_function_t *f);

/// Exec Pow2
rt_function_error_t exec_pow2(rt_function_t *f);
/// @}

/// @defgroup AddScalar AddScalar
/// @{

/// Local context for AddScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} add_scalar_local_context_t;

/// Allocate AddScalar local context
rt_function_error_t allocate_add_scalar_local_context(rt_function_t *f);

/// Free AddScalar local context
rt_function_error_t free_add_scalar_local_context(rt_function_t *f);

/// Exec AddScalar
rt_function_error_t exec_add_scalar(rt_function_t *f);
/// @}

/// @defgroup MulScalar MulScalar
/// @{

/// Local context for MulScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} mul_scalar_local_context_t;

/// Allocate MulScalar local context
rt_function_error_t allocate_mul_scalar_local_context(rt_function_t *f);

/// Free MulScalar local context
rt_function_error_t free_mul_scalar_local_context(rt_function_t *f);

/// Exec MulScalar
rt_function_error_t exec_mul_scalar(rt_function_t *f);
/// @}

/// @defgroup PowScalar PowScalar
/// @{

/// Local context for PowScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} pow_scalar_local_context_t;

/// Allocate PowScalar local context
rt_function_error_t allocate_pow_scalar_local_context(rt_function_t *f);

/// Free PowScalar local context
rt_function_error_t free_pow_scalar_local_context(rt_function_t *f);

/// Exec PowScalar
rt_function_error_t exec_pow_scalar(rt_function_t *f);
/// @}

/// @defgroup RSubScalar RSubScalar
/// @{

/// Local context for RSubScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} r_sub_scalar_local_context_t;

/// Allocate RSubScalar local context
rt_function_error_t allocate_r_sub_scalar_local_context(rt_function_t *f);

/// Free RSubScalar local context
rt_function_error_t free_r_sub_scalar_local_context(rt_function_t *f);

/// Exec RSubScalar
rt_function_error_t exec_r_sub_scalar(rt_function_t *f);
/// @}

/// @defgroup RDivScalar RDivScalar
/// @{

/// Local context for RDivScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} r_div_scalar_local_context_t;

/// Allocate RDivScalar local context
rt_function_error_t allocate_r_div_scalar_local_context(rt_function_t *f);

/// Free RDivScalar local context
rt_function_error_t free_r_div_scalar_local_context(rt_function_t *f);

/// Exec RDivScalar
rt_function_error_t exec_r_div_scalar(rt_function_t *f);
/// @}

/// @defgroup RPowScalar RPowScalar
/// @{

/// Local context for RPowScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} r_pow_scalar_local_context_t;

/// Allocate RPowScalar local context
rt_function_error_t allocate_r_pow_scalar_local_context(rt_function_t *f);

/// Free RPowScalar local context
rt_function_error_t free_r_pow_scalar_local_context(rt_function_t *f);

/// Exec RPowScalar
rt_function_error_t exec_r_pow_scalar(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Logical Logical
/// @{

/// @defgroup Sign Sign
/// @{

/// Local context for Sign
typedef struct {
  float alpha; ///< float
  void *data;  ///< General purpose data area
} sign_local_context_t;

/// Allocate Sign local context
rt_function_error_t allocate_sign_local_context(rt_function_t *f);

/// Free Sign local context
rt_function_error_t free_sign_local_context(rt_function_t *f);

/// Exec Sign
rt_function_error_t exec_sign(rt_function_t *f);
/// @}

/// @defgroup Minimum2 Minimum2
/// @{

/// Allocate Minimum2 local context
rt_function_error_t allocate_minimum2_local_context(rt_function_t *f);

/// Free Minimum2 local context
rt_function_error_t free_minimum2_local_context(rt_function_t *f);

/// Exec Minimum2
rt_function_error_t exec_minimum2(rt_function_t *f);
/// @}

/// @defgroup Maximum2 Maximum2
/// @{

/// Allocate Maximum2 local context
rt_function_error_t allocate_maximum2_local_context(rt_function_t *f);

/// Free Maximum2 local context
rt_function_error_t free_maximum2_local_context(rt_function_t *f);

/// Exec Maximum2
rt_function_error_t exec_maximum2(rt_function_t *f);
/// @}

/// @defgroup MinimumScalar MinimumScalar
/// @{

/// Local context for MinimumScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} minimum_scalar_local_context_t;

/// Allocate MinimumScalar local context
rt_function_error_t allocate_minimum_scalar_local_context(rt_function_t *f);

/// Free MinimumScalar local context
rt_function_error_t free_minimum_scalar_local_context(rt_function_t *f);

/// Exec MinimumScalar
rt_function_error_t exec_minimum_scalar(rt_function_t *f);
/// @}

/// @defgroup MaximumScalar MaximumScalar
/// @{

/// Local context for MaximumScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} maximum_scalar_local_context_t;

/// Allocate MaximumScalar local context
rt_function_error_t allocate_maximum_scalar_local_context(rt_function_t *f);

/// Free MaximumScalar local context
rt_function_error_t free_maximum_scalar_local_context(rt_function_t *f);

/// Exec MaximumScalar
rt_function_error_t exec_maximum_scalar(rt_function_t *f);
/// @}

/// @defgroup LogicalAnd LogicalAnd
/// @{

/// Allocate LogicalAnd local context
rt_function_error_t allocate_logical_and_local_context(rt_function_t *f);

/// Free LogicalAnd local context
rt_function_error_t free_logical_and_local_context(rt_function_t *f);

/// Exec LogicalAnd
rt_function_error_t exec_logical_and(rt_function_t *f);
/// @}

/// @defgroup LogicalOr LogicalOr
/// @{

/// Allocate LogicalOr local context
rt_function_error_t allocate_logical_or_local_context(rt_function_t *f);

/// Free LogicalOr local context
rt_function_error_t free_logical_or_local_context(rt_function_t *f);

/// Exec LogicalOr
rt_function_error_t exec_logical_or(rt_function_t *f);
/// @}

/// @defgroup LogicalXor LogicalXor
/// @{

/// Allocate LogicalXor local context
rt_function_error_t allocate_logical_xor_local_context(rt_function_t *f);

/// Free LogicalXor local context
rt_function_error_t free_logical_xor_local_context(rt_function_t *f);

/// Exec LogicalXor
rt_function_error_t exec_logical_xor(rt_function_t *f);
/// @}

/// @defgroup Equal Equal
/// @{

/// Allocate Equal local context
rt_function_error_t allocate_equal_local_context(rt_function_t *f);

/// Free Equal local context
rt_function_error_t free_equal_local_context(rt_function_t *f);

/// Exec Equal
rt_function_error_t exec_equal(rt_function_t *f);
/// @}

/// @defgroup NotEqual NotEqual
/// @{

/// Allocate NotEqual local context
rt_function_error_t allocate_not_equal_local_context(rt_function_t *f);

/// Free NotEqual local context
rt_function_error_t free_not_equal_local_context(rt_function_t *f);

/// Exec NotEqual
rt_function_error_t exec_not_equal(rt_function_t *f);
/// @}

/// @defgroup GreaterEqual GreaterEqual
/// @{

/// Allocate GreaterEqual local context
rt_function_error_t allocate_greater_equal_local_context(rt_function_t *f);

/// Free GreaterEqual local context
rt_function_error_t free_greater_equal_local_context(rt_function_t *f);

/// Exec GreaterEqual
rt_function_error_t exec_greater_equal(rt_function_t *f);
/// @}

/// @defgroup Greater Greater
/// @{

/// Allocate Greater local context
rt_function_error_t allocate_greater_local_context(rt_function_t *f);

/// Free Greater local context
rt_function_error_t free_greater_local_context(rt_function_t *f);

/// Exec Greater
rt_function_error_t exec_greater(rt_function_t *f);
/// @}

/// @defgroup LessEqual LessEqual
/// @{

/// Allocate LessEqual local context
rt_function_error_t allocate_less_equal_local_context(rt_function_t *f);

/// Free LessEqual local context
rt_function_error_t free_less_equal_local_context(rt_function_t *f);

/// Exec LessEqual
rt_function_error_t exec_less_equal(rt_function_t *f);
/// @}

/// @defgroup Less Less
/// @{

/// Allocate Less local context
rt_function_error_t allocate_less_local_context(rt_function_t *f);

/// Free Less local context
rt_function_error_t free_less_local_context(rt_function_t *f);

/// Exec Less
rt_function_error_t exec_less(rt_function_t *f);
/// @}

/// @defgroup LogicalAndScalar LogicalAndScalar
/// @{

/// Local context for LogicalAndScalar
typedef struct {
  uint8_t val; ///< bool
  void *data;  ///< General purpose data area
} logical_and_scalar_local_context_t;

/// Allocate LogicalAndScalar local context
rt_function_error_t allocate_logical_and_scalar_local_context(rt_function_t *f);

/// Free LogicalAndScalar local context
rt_function_error_t free_logical_and_scalar_local_context(rt_function_t *f);

/// Exec LogicalAndScalar
rt_function_error_t exec_logical_and_scalar(rt_function_t *f);
/// @}

/// @defgroup LogicalOrScalar LogicalOrScalar
/// @{

/// Local context for LogicalOrScalar
typedef struct {
  uint8_t val; ///< bool
  void *data;  ///< General purpose data area
} logical_or_scalar_local_context_t;

/// Allocate LogicalOrScalar local context
rt_function_error_t allocate_logical_or_scalar_local_context(rt_function_t *f);

/// Free LogicalOrScalar local context
rt_function_error_t free_logical_or_scalar_local_context(rt_function_t *f);

/// Exec LogicalOrScalar
rt_function_error_t exec_logical_or_scalar(rt_function_t *f);
/// @}

/// @defgroup LogicalXorScalar LogicalXorScalar
/// @{

/// Local context for LogicalXorScalar
typedef struct {
  uint8_t val; ///< bool
  void *data;  ///< General purpose data area
} logical_xor_scalar_local_context_t;

/// Allocate LogicalXorScalar local context
rt_function_error_t allocate_logical_xor_scalar_local_context(rt_function_t *f);

/// Free LogicalXorScalar local context
rt_function_error_t free_logical_xor_scalar_local_context(rt_function_t *f);

/// Exec LogicalXorScalar
rt_function_error_t exec_logical_xor_scalar(rt_function_t *f);
/// @}

/// @defgroup EqualScalar EqualScalar
/// @{

/// Local context for EqualScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} equal_scalar_local_context_t;

/// Allocate EqualScalar local context
rt_function_error_t allocate_equal_scalar_local_context(rt_function_t *f);

/// Free EqualScalar local context
rt_function_error_t free_equal_scalar_local_context(rt_function_t *f);

/// Exec EqualScalar
rt_function_error_t exec_equal_scalar(rt_function_t *f);
/// @}

/// @defgroup NotEqualScalar NotEqualScalar
/// @{

/// Local context for NotEqualScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} not_equal_scalar_local_context_t;

/// Allocate NotEqualScalar local context
rt_function_error_t allocate_not_equal_scalar_local_context(rt_function_t *f);

/// Free NotEqualScalar local context
rt_function_error_t free_not_equal_scalar_local_context(rt_function_t *f);

/// Exec NotEqualScalar
rt_function_error_t exec_not_equal_scalar(rt_function_t *f);
/// @}

/// @defgroup GreaterEqualScalar GreaterEqualScalar
/// @{

/// Local context for GreaterEqualScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} greater_equal_scalar_local_context_t;

/// Allocate GreaterEqualScalar local context
rt_function_error_t
allocate_greater_equal_scalar_local_context(rt_function_t *f);

/// Free GreaterEqualScalar local context
rt_function_error_t free_greater_equal_scalar_local_context(rt_function_t *f);

/// Exec GreaterEqualScalar
rt_function_error_t exec_greater_equal_scalar(rt_function_t *f);
/// @}

/// @defgroup GreaterScalar GreaterScalar
/// @{

/// Local context for GreaterScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} greater_scalar_local_context_t;

/// Allocate GreaterScalar local context
rt_function_error_t allocate_greater_scalar_local_context(rt_function_t *f);

/// Free GreaterScalar local context
rt_function_error_t free_greater_scalar_local_context(rt_function_t *f);

/// Exec GreaterScalar
rt_function_error_t exec_greater_scalar(rt_function_t *f);
/// @}

/// @defgroup LessEqualScalar LessEqualScalar
/// @{

/// Local context for LessEqualScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} less_equal_scalar_local_context_t;

/// Allocate LessEqualScalar local context
rt_function_error_t allocate_less_equal_scalar_local_context(rt_function_t *f);

/// Free LessEqualScalar local context
rt_function_error_t free_less_equal_scalar_local_context(rt_function_t *f);

/// Exec LessEqualScalar
rt_function_error_t exec_less_equal_scalar(rt_function_t *f);
/// @}

/// @defgroup LessScalar LessScalar
/// @{

/// Local context for LessScalar
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} less_scalar_local_context_t;

/// Allocate LessScalar local context
rt_function_error_t allocate_less_scalar_local_context(rt_function_t *f);

/// Free LessScalar local context
rt_function_error_t free_less_scalar_local_context(rt_function_t *f);

/// Exec LessScalar
rt_function_error_t exec_less_scalar(rt_function_t *f);
/// @}

/// @defgroup LogicalNot LogicalNot
/// @{

/// Allocate LogicalNot local context
rt_function_error_t allocate_logical_not_local_context(rt_function_t *f);

/// Free LogicalNot local context
rt_function_error_t free_logical_not_local_context(rt_function_t *f);

/// Exec LogicalNot
rt_function_error_t exec_logical_not(rt_function_t *f);
/// @}

/// @defgroup IsNaN IsNaN
/// @{

/// Allocate IsNaN local context
rt_function_error_t allocate_isnan_local_context(rt_function_t *f);

/// Free IsNaN local context
rt_function_error_t free_isnan_local_context(rt_function_t *f);

/// Exec IsNaN
rt_function_error_t exec_isnan(rt_function_t *f);
/// @}

/// @defgroup IsInf IsInf
/// @{

/// Allocate IsInf local context
rt_function_error_t allocate_isinf_local_context(rt_function_t *f);

/// Free IsInf local context
rt_function_error_t free_isinf_local_context(rt_function_t *f);

/// Exec IsInf
rt_function_error_t exec_isinf(rt_function_t *f);
/// @}

/// @defgroup ResetNaN ResetNaN
/// @{

/// Local context for ResetNaN
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} reset_nan_local_context_t;

/// Allocate ResetNaN local context
rt_function_error_t allocate_reset_nan_local_context(rt_function_t *f);

/// Free ResetNaN local context
rt_function_error_t free_reset_nan_local_context(rt_function_t *f);

/// Exec ResetNaN
rt_function_error_t exec_reset_nan(rt_function_t *f);
/// @}

/// @defgroup ResetInf ResetInf
/// @{

/// Local context for ResetInf
typedef struct {
  float val;  ///< double
  void *data; ///< General purpose data area
} reset_inf_local_context_t;

/// Allocate ResetInf local context
rt_function_error_t allocate_reset_inf_local_context(rt_function_t *f);

/// Free ResetInf local context
rt_function_error_t free_reset_inf_local_context(rt_function_t *f);

/// Exec ResetInf
rt_function_error_t exec_reset_inf(rt_function_t *f);
/// @}

/// @defgroup Where Where
/// @{

/// Allocate Where local context
rt_function_error_t allocate_where_local_context(rt_function_t *f);

/// Free Where local context
rt_function_error_t free_where_local_context(rt_function_t *f);

/// Exec Where
rt_function_error_t exec_where(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Math Math
/// @{

/// @defgroup Constant Constant
/// @{

/// Local context for Constant
typedef struct {
  float val;       ///< float
  rt_list_t shape; ///< Original type is [Shape]
  void *data;      ///< General purpose data area
} constant_local_context_t;

/// Allocate Constant local context
rt_function_error_t allocate_constant_local_context(rt_function_t *f);

/// Free Constant local context
rt_function_error_t free_constant_local_context(rt_function_t *f);

/// Exec Constant
rt_function_error_t exec_constant(rt_function_t *f);
/// @}

/// @defgroup Arange Arange
/// @{

/// Local context for Arange
typedef struct {
  float start; ///< float
  float stop;  ///< float
  float step;  ///< float
  void *data;  ///< General purpose data area
} arange_local_context_t;

/// Allocate Arange local context
rt_function_error_t allocate_arange_local_context(rt_function_t *f);

/// Free Arange local context
rt_function_error_t free_arange_local_context(rt_function_t *f);

/// Exec Arange
rt_function_error_t exec_arange(rt_function_t *f);
/// @}

/// @defgroup Abs Abs
/// @{

/// Allocate Abs local context
rt_function_error_t allocate_abs_local_context(rt_function_t *f);

/// Free Abs local context
rt_function_error_t free_abs_local_context(rt_function_t *f);

/// Exec Abs
rt_function_error_t exec_abs(rt_function_t *f);
/// @}

/// @defgroup Exp Exp
/// @{

/// Allocate Exp local context
rt_function_error_t allocate_exp_local_context(rt_function_t *f);

/// Free Exp local context
rt_function_error_t free_exp_local_context(rt_function_t *f);

/// Exec Exp
rt_function_error_t exec_exp(rt_function_t *f);
/// @}

/// @defgroup Log Log
/// @{

/// Allocate Log local context
rt_function_error_t allocate_log_local_context(rt_function_t *f);

/// Free Log local context
rt_function_error_t free_log_local_context(rt_function_t *f);

/// Exec Log
rt_function_error_t exec_log(rt_function_t *f);
/// @}

/// @defgroup Identity Identity
/// @{

/// Allocate Identity local context
rt_function_error_t allocate_identity_local_context(rt_function_t *f);

/// Free Identity local context
rt_function_error_t free_identity_local_context(rt_function_t *f);

/// Exec Identity
rt_function_error_t exec_identity(rt_function_t *f);
/// @}

/// @defgroup BatchMatmul BatchMatmul
/// @{

/// Local context for BatchMatmul
typedef struct {
  uint8_t transpose_a; ///< bool
  uint8_t transpose_b; ///< bool
  void *data;          ///< General purpose data area
} batch_matmul_local_context_t;

/// Allocate BatchMatmul local context
rt_function_error_t allocate_batch_matmul_local_context(rt_function_t *f);

/// Free BatchMatmul local context
rt_function_error_t free_batch_matmul_local_context(rt_function_t *f);

/// Exec BatchMatmul
rt_function_error_t exec_batch_matmul(rt_function_t *f);
/// @}

/// @defgroup Round Round
/// @{

/// Allocate Round local context
rt_function_error_t allocate_round_local_context(rt_function_t *f);

/// Free Round local context
rt_function_error_t free_round_local_context(rt_function_t *f);

/// Exec Round
rt_function_error_t exec_round(rt_function_t *f);
/// @}

/// @defgroup Ceil Ceil
/// @{

/// Allocate Ceil local context
rt_function_error_t allocate_ceil_local_context(rt_function_t *f);

/// Free Ceil local context
rt_function_error_t free_ceil_local_context(rt_function_t *f);

/// Exec Ceil
rt_function_error_t exec_ceil(rt_function_t *f);
/// @}

/// @defgroup Floor Floor
/// @{

/// Allocate Floor local context
rt_function_error_t allocate_floor_local_context(rt_function_t *f);

/// Free Floor local context
rt_function_error_t free_floor_local_context(rt_function_t *f);

/// Exec Floor
rt_function_error_t exec_floor(rt_function_t *f);
/// @}

/// @defgroup Sin Sin
/// @{

/// Allocate Sin local context
rt_function_error_t allocate_sin_local_context(rt_function_t *f);

/// Free Sin local context
rt_function_error_t free_sin_local_context(rt_function_t *f);

/// Exec Sin
rt_function_error_t exec_sin(rt_function_t *f);
/// @}

/// @defgroup Cos Cos
/// @{

/// Allocate Cos local context
rt_function_error_t allocate_cos_local_context(rt_function_t *f);

/// Free Cos local context
rt_function_error_t free_cos_local_context(rt_function_t *f);

/// Exec Cos
rt_function_error_t exec_cos(rt_function_t *f);
/// @}

/// @defgroup Tan Tan
/// @{

/// Allocate Tan local context
rt_function_error_t allocate_tan_local_context(rt_function_t *f);

/// Free Tan local context
rt_function_error_t free_tan_local_context(rt_function_t *f);

/// Exec Tan
rt_function_error_t exec_tan(rt_function_t *f);
/// @}

/// @defgroup Sinh Sinh
/// @{

/// Allocate Sinh local context
rt_function_error_t allocate_sinh_local_context(rt_function_t *f);

/// Free Sinh local context
rt_function_error_t free_sinh_local_context(rt_function_t *f);

/// Exec Sinh
rt_function_error_t exec_sinh(rt_function_t *f);
/// @}

/// @defgroup Cosh Cosh
/// @{

/// Allocate Cosh local context
rt_function_error_t allocate_cosh_local_context(rt_function_t *f);

/// Free Cosh local context
rt_function_error_t free_cosh_local_context(rt_function_t *f);

/// Exec Cosh
rt_function_error_t exec_cosh(rt_function_t *f);
/// @}

/// @defgroup ASin ASin
/// @{

/// Allocate ASin local context
rt_function_error_t allocate_asin_local_context(rt_function_t *f);

/// Free ASin local context
rt_function_error_t free_asin_local_context(rt_function_t *f);

/// Exec ASin
rt_function_error_t exec_asin(rt_function_t *f);
/// @}

/// @defgroup ACos ACos
/// @{

/// Allocate ACos local context
rt_function_error_t allocate_acos_local_context(rt_function_t *f);

/// Free ACos local context
rt_function_error_t free_acos_local_context(rt_function_t *f);

/// Exec ACos
rt_function_error_t exec_acos(rt_function_t *f);
/// @}

/// @defgroup ATan ATan
/// @{

/// Allocate ATan local context
rt_function_error_t allocate_atan_local_context(rt_function_t *f);

/// Free ATan local context
rt_function_error_t free_atan_local_context(rt_function_t *f);

/// Exec ATan
rt_function_error_t exec_atan(rt_function_t *f);
/// @}

/// @defgroup ATan2 ATan2
/// @{

/// Allocate ATan2 local context
rt_function_error_t allocate_atan2_local_context(rt_function_t *f);

/// Free ATan2 local context
rt_function_error_t free_atan2_local_context(rt_function_t *f);

/// Exec ATan2
rt_function_error_t exec_atan2(rt_function_t *f);
/// @}

/// @defgroup ASinh ASinh
/// @{

/// Allocate ASinh local context
rt_function_error_t allocate_asinh_local_context(rt_function_t *f);

/// Free ASinh local context
rt_function_error_t free_asinh_local_context(rt_function_t *f);

/// Exec ASinh
rt_function_error_t exec_asinh(rt_function_t *f);
/// @}

/// @defgroup ACosh ACosh
/// @{

/// Allocate ACosh local context
rt_function_error_t allocate_acosh_local_context(rt_function_t *f);

/// Free ACosh local context
rt_function_error_t free_acosh_local_context(rt_function_t *f);

/// Exec ACosh
rt_function_error_t exec_acosh(rt_function_t *f);
/// @}

/// @defgroup ATanh ATanh
/// @{

/// Allocate ATanh local context
rt_function_error_t allocate_atanh_local_context(rt_function_t *f);

/// Free ATanh local context
rt_function_error_t free_atanh_local_context(rt_function_t *f);

/// Exec ATanh
rt_function_error_t exec_atanh(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ArrayManipulation Array Manipulation
/// @{

/// @defgroup Concatenate Concatenate
/// @{

/// Local context for Concatenate
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} concatenate_local_context_t;

/// Allocate Concatenate local context
rt_function_error_t allocate_concatenate_local_context(rt_function_t *f);

/// Free Concatenate local context
rt_function_error_t free_concatenate_local_context(rt_function_t *f);

/// Exec Concatenate
rt_function_error_t exec_concatenate(rt_function_t *f);
/// @}

/// @defgroup Split Split
/// @{

/// Local context for Split
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} split_local_context_t;

/// Allocate Split local context
rt_function_error_t allocate_split_local_context(rt_function_t *f);

/// Free Split local context
rt_function_error_t free_split_local_context(rt_function_t *f);

/// Exec Split
rt_function_error_t exec_split(rt_function_t *f);
/// @}

/// @defgroup Stack Stack
/// @{

/// Local context for Stack
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} stack_local_context_t;

/// Allocate Stack local context
rt_function_error_t allocate_stack_local_context(rt_function_t *f);

/// Free Stack local context
rt_function_error_t free_stack_local_context(rt_function_t *f);

/// Exec Stack
rt_function_error_t exec_stack(rt_function_t *f);
/// @}

/// @defgroup Slice Slice
/// @{

/// Local context for Slice
typedef struct {
  rt_list_t start; ///< Original type is [repeated int64]
  rt_list_t stop;  ///< Original type is [repeated int64]
  rt_list_t step;  ///< Original type is [repeated int64]
  void *data;      ///< General purpose data area
} slice_local_context_t;

/// Allocate Slice local context
rt_function_error_t allocate_slice_local_context(rt_function_t *f);

/// Free Slice local context
rt_function_error_t free_slice_local_context(rt_function_t *f);

/// Exec Slice
rt_function_error_t exec_slice(rt_function_t *f);
/// @}

/// @defgroup Pad Pad
/// @{

/// Named values for Pad.mode
typedef enum {
  PAD_MODE_CONSTANT,
  PAD_MODE_REFLECT,
  END_OF_PAD_MODE
} pad_mode_value_t;

/// Local context for Pad
typedef struct {
  rt_list_t pad_width;   ///< Original type is [repeated int64]
  pad_mode_value_t mode; ///< string
  float constant_value;  ///< float
  void *data;            ///< General purpose data area
} pad_local_context_t;

/// Allocate Pad local context
rt_function_error_t allocate_pad_local_context(rt_function_t *f);

/// Free Pad local context
rt_function_error_t free_pad_local_context(rt_function_t *f);

/// Exec Pad
rt_function_error_t exec_pad(rt_function_t *f);
/// @}

/// @defgroup Transpose Transpose
/// @{

/// Local context for Transpose
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *data;     ///< General purpose data area
} transpose_local_context_t;

/// Allocate Transpose local context
rt_function_error_t allocate_transpose_local_context(rt_function_t *f);

/// Free Transpose local context
rt_function_error_t free_transpose_local_context(rt_function_t *f);

/// Exec Transpose
rt_function_error_t exec_transpose(rt_function_t *f);
/// @}

/// @defgroup Broadcast Broadcast
/// @{

/// Local context for Broadcast
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *data;      ///< General purpose data area
} broadcast_local_context_t;

/// Allocate Broadcast local context
rt_function_error_t allocate_broadcast_local_context(rt_function_t *f);

/// Free Broadcast local context
rt_function_error_t free_broadcast_local_context(rt_function_t *f);

/// Exec Broadcast
rt_function_error_t exec_broadcast(rt_function_t *f);
/// @}

/// @defgroup BroadcastTo BroadcastTo
/// @{

/// Local context for BroadcastTo
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} broadcast_to_local_context_t;

/// Allocate BroadcastTo local context
rt_function_error_t allocate_broadcast_to_local_context(rt_function_t *f);

/// Free BroadcastTo local context
rt_function_error_t free_broadcast_to_local_context(rt_function_t *f);

/// Exec BroadcastTo
rt_function_error_t exec_broadcast_to(rt_function_t *f);
/// @}

/// @defgroup Tile Tile
/// @{

/// Local context for Tile
typedef struct {
  rt_list_t reps; ///< Original type is [repeated int64]
  void *data;     ///< General purpose data area
} tile_local_context_t;

/// Allocate Tile local context
rt_function_error_t allocate_tile_local_context(rt_function_t *f);

/// Free Tile local context
rt_function_error_t free_tile_local_context(rt_function_t *f);

/// Exec Tile
rt_function_error_t exec_tile(rt_function_t *f);
/// @}

/// @defgroup OneHot OneHot
/// @{

/// Local context for OneHot
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *data;      ///< General purpose data area
} one_hot_local_context_t;

/// Allocate OneHot local context
rt_function_error_t allocate_one_hot_local_context(rt_function_t *f);

/// Free OneHot local context
rt_function_error_t free_one_hot_local_context(rt_function_t *f);

/// Exec OneHot
rt_function_error_t exec_one_hot(rt_function_t *f);
/// @}

/// @defgroup Flip Flip
/// @{

/// Local context for Flip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *data;     ///< General purpose data area
} flip_local_context_t;

/// Allocate Flip local context
rt_function_error_t allocate_flip_local_context(rt_function_t *f);

/// Free Flip local context
rt_function_error_t free_flip_local_context(rt_function_t *f);

/// Exec Flip
rt_function_error_t exec_flip(rt_function_t *f);
/// @}

/// @defgroup Shift Shift
/// @{

/// Named values for Shift.border_mode
typedef enum {
  SHIFT_BORDER_MODE_NEAREST,
  SHIFT_BORDER_MODE_REFLECT,
  END_OF_SHIFT_BORDER_MODE
} shift_border_mode_value_t;

/// Local context for Shift
typedef struct {
  rt_list_t shifts;                      ///< Original type is [repeated int64]
  shift_border_mode_value_t border_mode; ///< string
  void *data;                            ///< General purpose data area
} shift_local_context_t;

/// Allocate Shift local context
rt_function_error_t allocate_shift_local_context(rt_function_t *f);

/// Free Shift local context
rt_function_error_t free_shift_local_context(rt_function_t *f);

/// Exec Shift
rt_function_error_t exec_shift(rt_function_t *f);
/// @}

/// @defgroup Sort Sort
/// @{

/// Local context for Sort
typedef struct {
  int32_t axis;       ///< int64
  uint8_t reverse;    ///< bool
  uint8_t with_index; ///< bool
  uint8_t only_index; ///< bool
  void *data;         ///< General purpose data area
} sort_local_context_t;

/// Allocate Sort local context
rt_function_error_t allocate_sort_local_context(rt_function_t *f);

/// Free Sort local context
rt_function_error_t free_sort_local_context(rt_function_t *f);

/// Exec Sort
rt_function_error_t exec_sort(rt_function_t *f);
/// @}

/// @defgroup Reshape Reshape
/// @{

/// Local context for Reshape
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  uint8_t inplace; ///< bool
  void *data;      ///< General purpose data area
} reshape_local_context_t;

/// Allocate Reshape local context
rt_function_error_t allocate_reshape_local_context(rt_function_t *f);

/// Free Reshape local context
rt_function_error_t free_reshape_local_context(rt_function_t *f);

/// Exec Reshape
rt_function_error_t exec_reshape(rt_function_t *f);
/// @}

/// @defgroup MatrixDiag MatrixDiag
/// @{

/// Allocate MatrixDiag local context
rt_function_error_t allocate_matrix_diag_local_context(rt_function_t *f);

/// Free MatrixDiag local context
rt_function_error_t free_matrix_diag_local_context(rt_function_t *f);

/// Exec MatrixDiag
rt_function_error_t exec_matrix_diag(rt_function_t *f);
/// @}

/// @defgroup MatrixDiagPart MatrixDiagPart
/// @{

/// Allocate MatrixDiagPart local context
rt_function_error_t allocate_matrix_diag_part_local_context(rt_function_t *f);

/// Free MatrixDiagPart local context
rt_function_error_t free_matrix_diag_part_local_context(rt_function_t *f);

/// Exec MatrixDiagPart
rt_function_error_t exec_matrix_diag_part(rt_function_t *f);
/// @}

/// @defgroup Assign Assign
/// @{

/// Allocate Assign local context
rt_function_error_t allocate_assign_local_context(rt_function_t *f);

/// Free Assign local context
rt_function_error_t free_assign_local_context(rt_function_t *f);

/// Exec Assign
rt_function_error_t exec_assign(rt_function_t *f);
/// @}

/// @defgroup GatherNd GatherNd
/// @{

/// Allocate GatherNd local context
rt_function_error_t allocate_gather_nd_local_context(rt_function_t *f);

/// Free GatherNd local context
rt_function_error_t free_gather_nd_local_context(rt_function_t *f);

/// Exec GatherNd
rt_function_error_t exec_gather_nd(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup SignalProcessing Signal Processing
/// @{

/// @defgroup Interpolate Interpolate
/// @{

/// Named values for Interpolate.mode
typedef enum {
  INTERPOLATE_MODE_NEAREST,
  INTERPOLATE_MODE_LINEAR,
  END_OF_INTERPOLATE_MODE
} interpolate_mode_value_t;

/// Local context for Interpolate
typedef struct {
  rt_list_t output_size;         ///< Original type is [repeated int64]
  interpolate_mode_value_t mode; ///< string
  uint8_t align_corners;         ///< bool
  void *data;                    ///< General purpose data area
} interpolate_local_context_t;

/// Allocate Interpolate local context
rt_function_error_t allocate_interpolate_local_context(rt_function_t *f);

/// Free Interpolate local context
rt_function_error_t free_interpolate_local_context(rt_function_t *f);

/// Exec Interpolate
rt_function_error_t exec_interpolate(rt_function_t *f);
/// @}

/// @defgroup FFT FFT
/// @{

/// Local context for FFT
typedef struct {
  int32_t signal_ndim; ///< int64
  uint8_t normalized;  ///< bool
  void *data;          ///< General purpose data area
} fft_local_context_t;

/// Allocate FFT local context
rt_function_error_t allocate_fft_local_context(rt_function_t *f);

/// Free FFT local context
rt_function_error_t free_fft_local_context(rt_function_t *f);

/// Exec FFT
rt_function_error_t exec_fft(rt_function_t *f);
/// @}

/// @defgroup IFFT IFFT
/// @{

/// Local context for IFFT
typedef struct {
  int32_t signal_ndim; ///< int64
  uint8_t normalized;  ///< bool
  void *data;          ///< General purpose data area
} ifft_local_context_t;

/// Allocate IFFT local context
rt_function_error_t allocate_ifft_local_context(rt_function_t *f);

/// Free IFFT local context
rt_function_error_t free_ifft_local_context(rt_function_t *f);

/// Exec IFFT
rt_function_error_t exec_ifft(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Stochasticity Stochasticity
/// @{

/// @defgroup Dropout Dropout
/// @{

/// Local context for Dropout
typedef struct {
  float p;      ///< double
  int32_t seed; ///< int64
  void *data;   ///< General purpose data area
} dropout_local_context_t;

/// Allocate Dropout local context
rt_function_error_t allocate_dropout_local_context(rt_function_t *f);

/// Free Dropout local context
rt_function_error_t free_dropout_local_context(rt_function_t *f);

/// Exec Dropout
rt_function_error_t exec_dropout(rt_function_t *f);
/// @}

/// @defgroup TopKData TopKData
/// @{

/// Local context for TopKData
typedef struct {
  int32_t k;         ///< int64
  uint8_t abs;       ///< bool
  uint8_t reduce;    ///< bool
  int32_t base_axis; ///< int64
  void *data;        ///< General purpose data area
} top_k_data_local_context_t;

/// Allocate TopKData local context
rt_function_error_t allocate_top_k_data_local_context(rt_function_t *f);

/// Free TopKData local context
rt_function_error_t free_top_k_data_local_context(rt_function_t *f);

/// Exec TopKData
rt_function_error_t exec_top_k_data(rt_function_t *f);
/// @}

/// @defgroup TopKGrad TopKGrad
/// @{

/// Local context for TopKGrad
typedef struct {
  int32_t k;         ///< int64
  uint8_t abs;       ///< bool
  int32_t base_axis; ///< int64
  void *data;        ///< General purpose data area
} top_k_grad_local_context_t;

/// Allocate TopKGrad local context
rt_function_error_t allocate_top_k_grad_local_context(rt_function_t *f);

/// Free TopKGrad local context
rt_function_error_t free_top_k_grad_local_context(rt_function_t *f);

/// Exec TopKGrad
rt_function_error_t exec_top_k_grad(rt_function_t *f);
/// @}

/// @defgroup Rand Rand
/// @{

/// Local context for Rand
typedef struct {
  float low;       ///< float
  float high;      ///< float
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< int64
  void *data;      ///< General purpose data area
} rand_local_context_t;

/// Allocate Rand local context
rt_function_error_t allocate_rand_local_context(rt_function_t *f);

/// Free Rand local context
rt_function_error_t free_rand_local_context(rt_function_t *f);

/// Exec Rand
rt_function_error_t exec_rand(rt_function_t *f);
/// @}

/// @defgroup Randint Randint
/// @{

/// Local context for Randint
typedef struct {
  int32_t low;     ///< int64
  int32_t high;    ///< int64
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< int64
  void *data;      ///< General purpose data area
} randint_local_context_t;

/// Allocate Randint local context
rt_function_error_t allocate_randint_local_context(rt_function_t *f);

/// Free Randint local context
rt_function_error_t free_randint_local_context(rt_function_t *f);

/// Exec Randint
rt_function_error_t exec_randint(rt_function_t *f);
/// @}

/// @defgroup Randn Randn
/// @{

/// Local context for Randn
typedef struct {
  float mu;        ///< float
  float sigma;     ///< float
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< int64
  void *data;      ///< General purpose data area
} randn_local_context_t;

/// Allocate Randn local context
rt_function_error_t allocate_randn_local_context(rt_function_t *f);

/// Free Randn local context
rt_function_error_t free_randn_local_context(rt_function_t *f);

/// Exec Randn
rt_function_error_t exec_randn(rt_function_t *f);
/// @}

/// @defgroup RandomChoice RandomChoice
/// @{

/// Local context for RandomChoice
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  uint8_t replace; ///< bool
  int32_t seed;    ///< int64
  void *data;      ///< General purpose data area
} random_choice_local_context_t;

/// Allocate RandomChoice local context
rt_function_error_t allocate_random_choice_local_context(rt_function_t *f);

/// Free RandomChoice local context
rt_function_error_t free_random_choice_local_context(rt_function_t *f);

/// Exec RandomChoice
rt_function_error_t exec_random_choice(rt_function_t *f);
/// @}

/// @defgroup RandomCrop RandomCrop
/// @{

/// Local context for RandomCrop
typedef struct {
  rt_list_t shape;   ///< Original type is [Shape]
  int32_t base_axis; ///< int64
  int32_t seed;      ///< int64
  void *data;        ///< General purpose data area
} random_crop_local_context_t;

/// Allocate RandomCrop local context
rt_function_error_t allocate_random_crop_local_context(rt_function_t *f);

/// Free RandomCrop local context
rt_function_error_t free_random_crop_local_context(rt_function_t *f);

/// Exec RandomCrop
rt_function_error_t exec_random_crop(rt_function_t *f);
/// @}

/// @defgroup RandomFlip RandomFlip
/// @{

/// Local context for RandomFlip
typedef struct {
  rt_list_t axes;    ///< Original type is [repeated int64]
  int32_t base_axis; ///< int64
  int32_t seed;      ///< int64
  void *data;        ///< General purpose data area
} random_flip_local_context_t;

/// Allocate RandomFlip local context
rt_function_error_t allocate_random_flip_local_context(rt_function_t *f);

/// Free RandomFlip local context
rt_function_error_t free_random_flip_local_context(rt_function_t *f);

/// Exec RandomFlip
rt_function_error_t exec_random_flip(rt_function_t *f);
/// @}

/// @defgroup RandomShift RandomShift
/// @{

/// Named values for RandomShift.border_mode
typedef enum {
  RANDOM_SHIFT_BORDER_MODE_NEAREST,
  RANDOM_SHIFT_BORDER_MODE_REFLECT,
  END_OF_RANDOM_SHIFT_BORDER_MODE
} random_shift_border_mode_value_t;

/// Local context for RandomShift
typedef struct {
  rt_list_t shifts; ///< Original type is [repeated int64]
  random_shift_border_mode_value_t border_mode; ///< string
  int32_t base_axis;                            ///< int64
  int32_t seed;                                 ///< int64
  void *data;                                   ///< General purpose data area
} random_shift_local_context_t;

/// Allocate RandomShift local context
rt_function_error_t allocate_random_shift_local_context(rt_function_t *f);

/// Free RandomShift local context
rt_function_error_t free_random_shift_local_context(rt_function_t *f);

/// Exec RandomShift
rt_function_error_t exec_random_shift(rt_function_t *f);
/// @}

/// @defgroup ImageAugmentation ImageAugmentation
/// @{

/// Local context for ImageAugmentation
typedef struct {
  rt_list_t shape;         ///< Original type is [Shape]
  rt_list_t pad;           ///< Original type is [Shape]
  float min_scale;         ///< float
  float max_scale;         ///< float
  float angle;             ///< float
  float aspect_ratio;      ///< float
  float distortion;        ///< float
  uint8_t flip_lr;         ///< bool
  uint8_t flip_ud;         ///< bool
  float brightness;        ///< float
  uint8_t brightness_each; ///< bool
  float contrast;          ///< float
  float contrast_center;   ///< float
  uint8_t contrast_each;   ///< bool
  float noise;             ///< float
  int32_t seed;            ///< int64
  void *data;              ///< General purpose data area
} image_augmentation_local_context_t;

/// Allocate ImageAugmentation local context
rt_function_error_t allocate_image_augmentation_local_context(rt_function_t *f);

/// Free ImageAugmentation local context
rt_function_error_t free_image_augmentation_local_context(rt_function_t *f);

/// Exec ImageAugmentation
rt_function_error_t exec_image_augmentation(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup LossFunctions Loss Functions
/// @{

/// @defgroup SigmoidCrossEntropy SigmoidCrossEntropy
/// @{

/// Allocate SigmoidCrossEntropy local context
rt_function_error_t
allocate_sigmoid_cross_entropy_local_context(rt_function_t *f);

/// Free SigmoidCrossEntropy local context
rt_function_error_t free_sigmoid_cross_entropy_local_context(rt_function_t *f);

/// Exec SigmoidCrossEntropy
rt_function_error_t exec_sigmoid_cross_entropy(rt_function_t *f);
/// @}

/// @defgroup BinaryCrossEntropy BinaryCrossEntropy
/// @{

/// Allocate BinaryCrossEntropy local context
rt_function_error_t
allocate_binary_cross_entropy_local_context(rt_function_t *f);

/// Free BinaryCrossEntropy local context
rt_function_error_t free_binary_cross_entropy_local_context(rt_function_t *f);

/// Exec BinaryCrossEntropy
rt_function_error_t exec_binary_cross_entropy(rt_function_t *f);
/// @}

/// @defgroup SoftmaxCrossEntropy SoftmaxCrossEntropy
/// @{

/// Local context for SoftmaxCrossEntropy
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} softmax_cross_entropy_local_context_t;

/// Allocate SoftmaxCrossEntropy local context
rt_function_error_t
allocate_softmax_cross_entropy_local_context(rt_function_t *f);

/// Free SoftmaxCrossEntropy local context
rt_function_error_t free_softmax_cross_entropy_local_context(rt_function_t *f);

/// Exec SoftmaxCrossEntropy
rt_function_error_t exec_softmax_cross_entropy(rt_function_t *f);
/// @}

/// @defgroup CategoricalCrossEntropy CategoricalCrossEntropy
/// @{

/// Local context for CategoricalCrossEntropy
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} categorical_cross_entropy_local_context_t;

/// Allocate CategoricalCrossEntropy local context
rt_function_error_t
allocate_categorical_cross_entropy_local_context(rt_function_t *f);

/// Free CategoricalCrossEntropy local context
rt_function_error_t
free_categorical_cross_entropy_local_context(rt_function_t *f);

/// Exec CategoricalCrossEntropy
rt_function_error_t exec_categorical_cross_entropy(rt_function_t *f);
/// @}

/// @defgroup SquaredError SquaredError
/// @{

/// Allocate SquaredError local context
rt_function_error_t allocate_squared_error_local_context(rt_function_t *f);

/// Free SquaredError local context
rt_function_error_t free_squared_error_local_context(rt_function_t *f);

/// Exec SquaredError
rt_function_error_t exec_squared_error(rt_function_t *f);
/// @}

/// @defgroup AbsoluteError AbsoluteError
/// @{

/// Allocate AbsoluteError local context
rt_function_error_t allocate_absolute_error_local_context(rt_function_t *f);

/// Free AbsoluteError local context
rt_function_error_t free_absolute_error_local_context(rt_function_t *f);

/// Exec AbsoluteError
rt_function_error_t exec_absolute_error(rt_function_t *f);
/// @}

/// @defgroup HuberLoss HuberLoss
/// @{

/// Local context for HuberLoss
typedef struct {
  float delta; ///< float
  void *data;  ///< General purpose data area
} huber_loss_local_context_t;

/// Allocate HuberLoss local context
rt_function_error_t allocate_huber_loss_local_context(rt_function_t *f);

/// Free HuberLoss local context
rt_function_error_t free_huber_loss_local_context(rt_function_t *f);

/// Exec HuberLoss
rt_function_error_t exec_huber_loss(rt_function_t *f);
/// @}

/// @defgroup EpsilonInsensitiveLoss EpsilonInsensitiveLoss
/// @{

/// Local context for EpsilonInsensitiveLoss
typedef struct {
  float epsilon; ///< float
  void *data;    ///< General purpose data area
} epsilon_insensitive_loss_local_context_t;

/// Allocate EpsilonInsensitiveLoss local context
rt_function_error_t
allocate_epsilon_insensitive_loss_local_context(rt_function_t *f);

/// Free EpsilonInsensitiveLoss local context
rt_function_error_t
free_epsilon_insensitive_loss_local_context(rt_function_t *f);

/// Exec EpsilonInsensitiveLoss
rt_function_error_t exec_epsilon_insensitive_loss(rt_function_t *f);
/// @}

/// @defgroup KLMultinomial KLMultinomial
/// @{

/// Local context for KLMultinomial
typedef struct {
  int32_t base_axis; ///< int64
  void *data;        ///< General purpose data area
} kl_multinomial_local_context_t;

/// Allocate KLMultinomial local context
rt_function_error_t allocate_kl_multinomial_local_context(rt_function_t *f);

/// Free KLMultinomial local context
rt_function_error_t free_kl_multinomial_local_context(rt_function_t *f);

/// Exec KLMultinomial
rt_function_error_t exec_kl_multinomial(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup QuantizationNeuralNetworkLayers Quantization Neural Network Layers
/// @{

/// @defgroup BinarySigmoid BinarySigmoid
/// @{

/// Allocate BinarySigmoid local context
rt_function_error_t allocate_binary_sigmoid_local_context(rt_function_t *f);

/// Free BinarySigmoid local context
rt_function_error_t free_binary_sigmoid_local_context(rt_function_t *f);

/// Exec BinarySigmoid
rt_function_error_t exec_binary_sigmoid(rt_function_t *f);
/// @}

/// @defgroup BinaryTanh BinaryTanh
/// @{

/// Allocate BinaryTanh local context
rt_function_error_t allocate_binary_tanh_local_context(rt_function_t *f);

/// Free BinaryTanh local context
rt_function_error_t free_binary_tanh_local_context(rt_function_t *f);

/// Exec BinaryTanh
rt_function_error_t exec_binary_tanh(rt_function_t *f);
/// @}

/// @defgroup BinaryConnectAffine BinaryConnectAffine
/// @{

/// Local context for BinaryConnectAffine
typedef struct {
  int32_t base_axis;      ///< int64
  float quantize_zero_to; ///< float
  void *data;             ///< General purpose data area
} binary_connect_affine_local_context_t;

/// Allocate BinaryConnectAffine local context
rt_function_error_t
allocate_binary_connect_affine_local_context(rt_function_t *f);

/// Free BinaryConnectAffine local context
rt_function_error_t free_binary_connect_affine_local_context(rt_function_t *f);

/// Exec BinaryConnectAffine
rt_function_error_t exec_binary_connect_affine(rt_function_t *f);
/// @}

/// @defgroup BinaryConnectConvolution BinaryConnectConvolution
/// @{

/// Local context for BinaryConnectConvolution
typedef struct {
  int32_t base_axis;      ///< int64
  rt_list_t pad;          ///< Original type is [Shape]
  rt_list_t stride;       ///< Original type is [Shape]
  rt_list_t dilation;     ///< Original type is [Shape]
  int32_t group;          ///< int64
  float quantize_zero_to; ///< float
  void *data;             ///< General purpose data area
} binary_connect_convolution_local_context_t;

/// Allocate BinaryConnectConvolution local context
rt_function_error_t
allocate_binary_connect_convolution_local_context(rt_function_t *f);

/// Free BinaryConnectConvolution local context
rt_function_error_t
free_binary_connect_convolution_local_context(rt_function_t *f);

/// Exec BinaryConnectConvolution
rt_function_error_t exec_binary_connect_convolution(rt_function_t *f);
/// @}

/// @defgroup BinaryWeightAffine BinaryWeightAffine
/// @{

/// Local context for BinaryWeightAffine
typedef struct {
  int32_t base_axis;      ///< int64
  float quantize_zero_to; ///< float
  void *data;             ///< General purpose data area
} binary_weight_affine_local_context_t;

/// Allocate BinaryWeightAffine local context
rt_function_error_t
allocate_binary_weight_affine_local_context(rt_function_t *f);

/// Free BinaryWeightAffine local context
rt_function_error_t free_binary_weight_affine_local_context(rt_function_t *f);

/// Exec BinaryWeightAffine
rt_function_error_t exec_binary_weight_affine(rt_function_t *f);
/// @}

/// @defgroup BinaryWeightConvolution BinaryWeightConvolution
/// @{

/// Local context for BinaryWeightConvolution
typedef struct {
  int32_t base_axis;      ///< int64
  rt_list_t pad;          ///< Original type is [Shape]
  rt_list_t stride;       ///< Original type is [Shape]
  rt_list_t dilation;     ///< Original type is [Shape]
  int32_t group;          ///< int64
  float quantize_zero_to; ///< float
  void *data;             ///< General purpose data area
} binary_weight_convolution_local_context_t;

/// Allocate BinaryWeightConvolution local context
rt_function_error_t
allocate_binary_weight_convolution_local_context(rt_function_t *f);

/// Free BinaryWeightConvolution local context
rt_function_error_t
free_binary_weight_convolution_local_context(rt_function_t *f);

/// Exec BinaryWeightConvolution
rt_function_error_t exec_binary_weight_convolution(rt_function_t *f);
/// @}

/// @defgroup INQAffine INQAffine
/// @{

/// Named values for INQAffine.selection_algorithm
typedef enum {
  INQ_AFFINE_SELECTION_ALGORITHM_LARGEST_ABS,
  INQ_AFFINE_SELECTION_ALGORITHM_RANDOM,
  END_OF_INQ_AFFINE_SELECTION_ALGORITHM
} inq_affine_selection_algorithm_value_t;

/// Local context for INQAffine
typedef struct {
  int32_t base_axis;        ///< int64
  int32_t num_bits;         ///< int64
  rt_list_t inq_iterations; ///< Original type is [repeated int64]
  inq_affine_selection_algorithm_value_t selection_algorithm; ///< string
  int32_t seed;                                               ///< int64
  void *data; ///< General purpose data area
} inq_affine_local_context_t;

/// Allocate INQAffine local context
rt_function_error_t allocate_inq_affine_local_context(rt_function_t *f);

/// Free INQAffine local context
rt_function_error_t free_inq_affine_local_context(rt_function_t *f);

/// Exec INQAffine
rt_function_error_t exec_inq_affine(rt_function_t *f);
/// @}

/// @defgroup INQConvolution INQConvolution
/// @{

/// Named values for INQConvolution.selection_algorithm
typedef enum {
  INQ_CONVOLUTION_SELECTION_ALGORITHM_LARGEST_ABS,
  INQ_CONVOLUTION_SELECTION_ALGORITHM_RANDOM,
  END_OF_INQ_CONVOLUTION_SELECTION_ALGORITHM
} inq_convolution_selection_algorithm_value_t;

/// Local context for INQConvolution
typedef struct {
  int32_t base_axis;        ///< int64
  rt_list_t pad;            ///< Original type is [Shape]
  rt_list_t stride;         ///< Original type is [Shape]
  rt_list_t dilation;       ///< Original type is [Shape]
  int32_t group;            ///< int64
  int32_t num_bits;         ///< int64
  rt_list_t inq_iterations; ///< Original type is [repeated int64]
  inq_convolution_selection_algorithm_value_t selection_algorithm; ///< string
  int32_t seed;                                                    ///< int64
  void *data; ///< General purpose data area
} inq_convolution_local_context_t;

/// Allocate INQConvolution local context
rt_function_error_t allocate_inq_convolution_local_context(rt_function_t *f);

/// Free INQConvolution local context
rt_function_error_t free_inq_convolution_local_context(rt_function_t *f);

/// Exec INQConvolution
rt_function_error_t exec_inq_convolution(rt_function_t *f);
/// @}

/// @defgroup FixedPointQuantize FixedPointQuantize
/// @{

/// Local context for FixedPointQuantize
typedef struct {
  uint8_t sign;             ///< bool
  int32_t n;                ///< int64
  float delta;              ///< float
  uint8_t ste_fine_grained; ///< bool
  void *data;               ///< General purpose data area
} fixed_point_quantize_local_context_t;

/// Allocate FixedPointQuantize local context
rt_function_error_t
allocate_fixed_point_quantize_local_context(rt_function_t *f);

/// Free FixedPointQuantize local context
rt_function_error_t free_fixed_point_quantize_local_context(rt_function_t *f);

/// Exec FixedPointQuantize
rt_function_error_t exec_fixed_point_quantize(rt_function_t *f);
/// @}

/// @defgroup Pow2Quantize Pow2Quantize
/// @{

/// Local context for Pow2Quantize
typedef struct {
  uint8_t sign;             ///< bool
  uint8_t with_zero;        ///< bool
  int32_t n;                ///< int64
  int32_t m;                ///< int64
  uint8_t ste_fine_grained; ///< bool
  void *data;               ///< General purpose data area
} pow2_quantize_local_context_t;

/// Allocate Pow2Quantize local context
rt_function_error_t allocate_pow2_quantize_local_context(rt_function_t *f);

/// Free Pow2Quantize local context
rt_function_error_t free_pow2_quantize_local_context(rt_function_t *f);

/// Exec Pow2Quantize
rt_function_error_t exec_pow2_quantize(rt_function_t *f);
/// @}

/// @defgroup Prune Prune
/// @{

/// Local context for Prune
typedef struct {
  float rate; ///< float
  void *data; ///< General purpose data area
} prune_local_context_t;

/// Allocate Prune local context
rt_function_error_t allocate_prune_local_context(rt_function_t *f);

/// Free Prune local context
rt_function_error_t free_prune_local_context(rt_function_t *f);

/// Exec Prune
rt_function_error_t exec_prune(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup Validation Validation
/// @{

/// @defgroup TopNError TopNError
/// @{

/// Local context for TopNError
typedef struct {
  int32_t axis; ///< int64
  int32_t n;    ///< int64
  void *data;   ///< General purpose data area
} top_n_error_local_context_t;

/// Allocate TopNError local context
rt_function_error_t allocate_top_n_error_local_context(rt_function_t *f);

/// Free TopNError local context
rt_function_error_t free_top_n_error_local_context(rt_function_t *f);

/// Exec TopNError
rt_function_error_t exec_top_n_error(rt_function_t *f);
/// @}

/// @defgroup BinaryError BinaryError
/// @{

/// Allocate BinaryError local context
rt_function_error_t allocate_binary_error_local_context(rt_function_t *f);

/// Free BinaryError local context
rt_function_error_t free_binary_error_local_context(rt_function_t *f);

/// Exec BinaryError
rt_function_error_t exec_binary_error(rt_function_t *f);
/// @}

/// @defgroup ConfusionMatrix ConfusionMatrix
/// @{

/// Local context for ConfusionMatrix
typedef struct {
  int32_t axis; ///< int64
  void *data;   ///< General purpose data area
} confusion_matrix_local_context_t;

/// Allocate ConfusionMatrix local context
rt_function_error_t allocate_confusion_matrix_local_context(rt_function_t *f);

/// Free ConfusionMatrix local context
rt_function_error_t free_confusion_matrix_local_context(rt_function_t *f);

/// Exec ConfusionMatrix
rt_function_error_t exec_confusion_matrix(rt_function_t *f);
/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup SpecialUse  Special Use
/// @{

/// @defgroup VATNoise VATNoise
/// @{

/// Local context for VATNoise
typedef struct {
  int32_t base_axis; ///< int64
  float eps;         ///< float
  void *data;        ///< General purpose data area
} vat_noise_local_context_t;

/// Allocate VATNoise local context
rt_function_error_t allocate_vat_noise_local_context(rt_function_t *f);

/// Free VATNoise local context
rt_function_error_t free_vat_noise_local_context(rt_function_t *f);

/// Exec VATNoise
rt_function_error_t exec_vat_noise(rt_function_t *f);
/// @}

/// @defgroup Unlink Unlink
/// @{

/// Allocate Unlink local context
rt_function_error_t allocate_unlink_local_context(rt_function_t *f);

/// Free Unlink local context
rt_function_error_t free_unlink_local_context(rt_function_t *f);

/// Exec Unlink
rt_function_error_t exec_unlink(rt_function_t *f);
/// @}

/// @defgroup Sink Sink
/// @{

/// Local context for Sink
typedef struct {
  uint8_t one_input_grad; ///< bool
  void *data;             ///< General purpose data area
} sink_local_context_t;

/// Allocate Sink local context
rt_function_error_t allocate_sink_local_context(rt_function_t *f);

/// Free Sink local context
rt_function_error_t free_sink_local_context(rt_function_t *f);

/// Exec Sink
rt_function_error_t exec_sink(rt_function_t *f);
/// @}

/// @defgroup NmsDetection2d NmsDetection2d
/// @{

/// Local context for NmsDetection2d
typedef struct {
  float thresh;          ///< float
  float nms;             ///< float
  uint8_t nms_per_class; ///< bool
  void *data;            ///< General purpose data area
} nms_detection2d_local_context_t;

/// Allocate NmsDetection2d local context
rt_function_error_t allocate_nms_detection2d_local_context(rt_function_t *f);

/// Free NmsDetection2d local context
rt_function_error_t free_nms_detection2d_local_context(rt_function_t *f);

/// Exec NmsDetection2d
rt_function_error_t exec_nms_detection2d(rt_function_t *f);
/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // H_FUNCTIONS_H__
