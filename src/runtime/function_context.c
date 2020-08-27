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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <nnablart/config.h>
#include <nnablart/functions.h>
#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "runtime_internal.h"

void allocate_function_context(nn_network_t *n, nn_function_t *function,
                               rt_function_context_t *function_context) {
  switch (function_context->info->type) {
#ifdef CONFIG_AFFINE
  case NN_FUNCTION_AFFINE: { // Affine
    function_context->func.free_local_context_func = free_affine_local_context;
    nn_function_affine_t *f = (nn_function_affine_t *)function;
    affine_local_context_t *ctx =
        rt_malloc_func(sizeof(affine_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_affine_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RNN
  case NN_FUNCTION_RNN: { // RNN
    function_context->func.free_local_context_func = free_rnn_local_context;
    nn_function_rnn_t *f = (nn_function_rnn_t *)function;
    rnn_local_context_t *ctx = rt_malloc_func(sizeof(rnn_local_context_t));
    ctx->num_layers = f->num_layers;
    ctx->nonlinearity = f->nonlinearity;
    ctx->dropout = f->dropout;
    ctx->bidirectional = f->bidirectional;
    ctx->training = f->training;
    function_context->func.local_context = ctx;
    allocate_rnn_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LSTM
  case NN_FUNCTION_LSTM: { // LSTM
    function_context->func.free_local_context_func = free_lstm_local_context;
    nn_function_lstm_t *f = (nn_function_lstm_t *)function;
    lstm_local_context_t *ctx = rt_malloc_func(sizeof(lstm_local_context_t));
    ctx->num_layers = f->num_layers;
    ctx->dropout = f->dropout;
    ctx->bidirectional = f->bidirectional;
    ctx->training = f->training;
    function_context->func.local_context = ctx;
    allocate_lstm_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GRU
  case NN_FUNCTION_GRU: { // GRU
    function_context->func.free_local_context_func = free_gru_local_context;
    nn_function_gru_t *f = (nn_function_gru_t *)function;
    gru_local_context_t *ctx = rt_malloc_func(sizeof(gru_local_context_t));
    ctx->num_layers = f->num_layers;
    ctx->dropout = f->dropout;
    ctx->bidirectional = f->bidirectional;
    ctx->training = f->training;
    function_context->func.local_context = ctx;
    allocate_gru_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CONVOLUTION
  case NN_FUNCTION_CONVOLUTION_0: { // Convolution
    function_context->func.free_local_context_func =
        free_convolution_local_context;
    nn_function_convolution_t *f = (nn_function_convolution_t *)function;
    convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->channel_last = 0;
    function_context->func.local_context = ctx;
    allocate_convolution_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_CONVOLUTION: { // Convolution
    function_context->func.free_local_context_func =
        free_convolution_local_context;
    nn_function_convolution_t *f = (nn_function_convolution_t *)function;
    convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_convolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_FUSEDCONVOLUTION
  case NN_FUNCTION_FUSED_CONVOLUTION: { // FusedConvolution
    function_context->func.free_local_context_func =
        free_fused_convolution_local_context;
    nn_function_fused_convolution_t *f =
        (nn_function_fused_convolution_t *)function;
    fused_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(fused_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->channel_last = f->channel_last;
    ctx->decay_rate = f->decay_rate;
    ctx->eps = f->eps;
    ctx->batch_stat = f->batch_stat;
    ctx->nonlinearity = f->nonlinearity;
    function_context->func.local_context = ctx;
    allocate_fused_convolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_DEPTHWISECONVOLUTION
  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    function_context->func.free_local_context_func =
        free_depthwise_convolution_local_context;
    nn_function_depthwise_convolution_t *f =
        (nn_function_depthwise_convolution_t *)function;
    depthwise_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(depthwise_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->multiplier = f->multiplier;
    function_context->func.local_context = ctx;
    allocate_depthwise_convolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_DECONVOLUTION
  case NN_FUNCTION_DECONVOLUTION_0: { // Deconvolution
    function_context->func.free_local_context_func =
        free_deconvolution_local_context;
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)function;
    deconvolution_local_context_t *ctx =
        rt_malloc_func(sizeof(deconvolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->channel_last = 0;
    ctx->output_padding.size = 0;
    ctx->output_padding.data = NULL;
    function_context->func.local_context = ctx;
    allocate_deconvolution_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_DECONVOLUTION_1: { // Deconvolution
    function_context->func.free_local_context_func =
        free_deconvolution_local_context;
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)function;
    deconvolution_local_context_t *ctx =
        rt_malloc_func(sizeof(deconvolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->channel_last = f->channel_last;
    ctx->output_padding.size = 0;
    ctx->output_padding.data = NULL;
    function_context->func.local_context = ctx;
    allocate_deconvolution_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    function_context->func.free_local_context_func =
        free_deconvolution_local_context;
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)function;
    deconvolution_local_context_t *ctx =
        rt_malloc_func(sizeof(deconvolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->channel_last = f->channel_last;
    ctx->output_padding = create_rt_list_from_nn_list(n, f->output_padding);
    function_context->func.local_context = ctx;
    allocate_deconvolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_DEPTHWISEDECONVOLUTION
  case NN_FUNCTION_DEPTHWISE_DECONVOLUTION: { // DepthwiseDeconvolution
    function_context->func.free_local_context_func =
        free_depthwise_deconvolution_local_context;
    nn_function_depthwise_deconvolution_t *f =
        (nn_function_depthwise_deconvolution_t *)function;
    depthwise_deconvolution_local_context_t *ctx =
        rt_malloc_func(sizeof(depthwise_deconvolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->divisor = f->divisor;
    function_context->func.local_context = ctx;
    allocate_depthwise_deconvolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ADAPTIVESEPARABLECONVOLUTION
  case NN_FUNCTION_ADAPTIVE_SEPARABLE_CONVOLUTION: { // AdaptiveSeparableConvolution
    function_context->func.free_local_context_func =
        free_adaptive_separable_convolution_local_context;
    function_context->func.local_context = 0;
    allocate_adaptive_separable_convolution_local_context(
        &function_context->func);
  } break;
#endif

#ifdef CONFIG_MAXPOOLING
  case NN_FUNCTION_MAX_POOLING_0: { // MaxPooling
    function_context->func.free_local_context_func =
        free_max_pooling_local_context;
    nn_function_max_pooling_t *f = (nn_function_max_pooling_t *)function;
    max_pooling_local_context_t *ctx =
        rt_malloc_func(sizeof(max_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = 0;
    function_context->func.local_context = ctx;
    allocate_max_pooling_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    function_context->func.free_local_context_func =
        free_max_pooling_local_context;
    nn_function_max_pooling_t *f = (nn_function_max_pooling_t *)function;
    max_pooling_local_context_t *ctx =
        rt_malloc_func(sizeof(max_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_max_pooling_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_AVERAGEPOOLING
  case NN_FUNCTION_AVERAGE_POOLING_0: { // AveragePooling
    function_context->func.free_local_context_func =
        free_average_pooling_local_context;
    nn_function_average_pooling_t *f =
        (nn_function_average_pooling_t *)function;
    average_pooling_local_context_t *ctx =
        rt_malloc_func(sizeof(average_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = f->channel_last;
    ctx->including_pad = 1;
    function_context->func.local_context = ctx;
    allocate_average_pooling_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    function_context->func.free_local_context_func =
        free_average_pooling_local_context;
    nn_function_average_pooling_t *f =
        (nn_function_average_pooling_t *)function;
    average_pooling_local_context_t *ctx =
        rt_malloc_func(sizeof(average_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = f->channel_last;
    ctx->including_pad = f->including_pad;
    function_context->func.local_context = ctx;
    allocate_average_pooling_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GLOBALAVERAGEPOOLING
  case NN_FUNCTION_GLOBAL_AVERAGE_POOLING: { // GlobalAveragePooling
    function_context->func.free_local_context_func =
        free_global_average_pooling_local_context;
    function_context->func.local_context = 0;
    allocate_global_average_pooling_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SUMPOOLING
  case NN_FUNCTION_SUM_POOLING_0: { // SumPooling
    function_context->func.free_local_context_func =
        free_sum_pooling_local_context;
    nn_function_sum_pooling_t *f = (nn_function_sum_pooling_t *)function;
    sum_pooling_local_context_t *ctx =
        rt_malloc_func(sizeof(sum_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = 0;
    function_context->func.local_context = ctx;
    allocate_sum_pooling_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    function_context->func.free_local_context_func =
        free_sum_pooling_local_context;
    nn_function_sum_pooling_t *f = (nn_function_sum_pooling_t *)function;
    sum_pooling_local_context_t *ctx =
        rt_malloc_func(sizeof(sum_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_sum_pooling_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_UNPOOLING
  case NN_FUNCTION_UNPOOLING_0: { // Unpooling
    function_context->func.free_local_context_func =
        free_unpooling_local_context;
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)function;
    unpooling_local_context_t *ctx =
        rt_malloc_func(sizeof(unpooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->channel_last = 0;
    function_context->func.local_context = ctx;
    allocate_unpooling_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_UNPOOLING: { // Unpooling
    function_context->func.free_local_context_func =
        free_unpooling_local_context;
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)function;
    unpooling_local_context_t *ctx =
        rt_malloc_func(sizeof(unpooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_unpooling_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_EMBED
  case NN_FUNCTION_EMBED: { // Embed
    function_context->func.free_local_context_func = free_embed_local_context;
    function_context->func.local_context = 0;
    allocate_embed_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SIGMOID
  case NN_FUNCTION_SIGMOID: { // Sigmoid
    function_context->func.free_local_context_func = free_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_sigmoid_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SWISH
  case NN_FUNCTION_SWISH: { // Swish
    function_context->func.free_local_context_func = free_swish_local_context;
    function_context->func.local_context = 0;
    allocate_swish_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TANH
  case NN_FUNCTION_TANH: { // Tanh
    function_context->func.free_local_context_func = free_tanh_local_context;
    function_context->func.local_context = 0;
    allocate_tanh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RELU
  case NN_FUNCTION_RELU: { // ReLU
    function_context->func.free_local_context_func = free_relu_local_context;
    nn_function_relu_t *f = (nn_function_relu_t *)function;
    relu_local_context_t *ctx = rt_malloc_func(sizeof(relu_local_context_t));
    ctx->inplace = f->inplace;
    function_context->func.local_context = ctx;
    allocate_relu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LEAKYRELU
  case NN_FUNCTION_LEAKY_RELU_0: { // LeakyReLU
    function_context->func.free_local_context_func =
        free_leaky_relu_local_context;
    nn_function_leaky_relu_t *f = (nn_function_leaky_relu_t *)function;
    leaky_relu_local_context_t *ctx =
        rt_malloc_func(sizeof(leaky_relu_local_context_t));
    ctx->alpha = f->alpha;
    ctx->inplace = 0;
    function_context->func.local_context = ctx;
    allocate_leaky_relu_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    function_context->func.free_local_context_func =
        free_leaky_relu_local_context;
    nn_function_leaky_relu_t *f = (nn_function_leaky_relu_t *)function;
    leaky_relu_local_context_t *ctx =
        rt_malloc_func(sizeof(leaky_relu_local_context_t));
    ctx->alpha = f->alpha;
    ctx->inplace = f->inplace;
    function_context->func.local_context = ctx;
    allocate_leaky_relu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SOFTMAX
  case NN_FUNCTION_SOFTMAX: { // Softmax
    function_context->func.free_local_context_func = free_softmax_local_context;
    nn_function_softmax_t *f = (nn_function_softmax_t *)function;
    softmax_local_context_t *ctx =
        rt_malloc_func(sizeof(softmax_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_softmax_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGSOFTMAX
  case NN_FUNCTION_LOG_SOFTMAX: { // LogSoftmax
    function_context->func.free_local_context_func =
        free_log_softmax_local_context;
    nn_function_log_softmax_t *f = (nn_function_log_softmax_t *)function;
    log_softmax_local_context_t *ctx =
        rt_malloc_func(sizeof(log_softmax_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_log_softmax_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ELU
  case NN_FUNCTION_ELU: { // ELU
    function_context->func.free_local_context_func = free_elu_local_context;
    nn_function_elu_t *f = (nn_function_elu_t *)function;
    elu_local_context_t *ctx = rt_malloc_func(sizeof(elu_local_context_t));
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_elu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SELU
  case NN_FUNCTION_SELU: { // SELU
    function_context->func.free_local_context_func = free_selu_local_context;
    nn_function_selu_t *f = (nn_function_selu_t *)function;
    selu_local_context_t *ctx = rt_malloc_func(sizeof(selu_local_context_t));
    ctx->scale = f->scale;
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_selu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CRELU
  case NN_FUNCTION_CRELU: { // CReLU
    function_context->func.free_local_context_func = free_crelu_local_context;
    nn_function_crelu_t *f = (nn_function_crelu_t *)function;
    crelu_local_context_t *ctx = rt_malloc_func(sizeof(crelu_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_crelu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CELU
  case NN_FUNCTION_CELU: { // CELU
    function_context->func.free_local_context_func = free_celu_local_context;
    nn_function_celu_t *f = (nn_function_celu_t *)function;
    celu_local_context_t *ctx = rt_malloc_func(sizeof(celu_local_context_t));
    ctx->alpha = f->alpha;
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_celu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_PRELU
  case NN_FUNCTION_PRELU: { // PReLU
    function_context->func.free_local_context_func = free_prelu_local_context;
    nn_function_prelu_t *f = (nn_function_prelu_t *)function;
    prelu_local_context_t *ctx = rt_malloc_func(sizeof(prelu_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_prelu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GELU
  case NN_FUNCTION_GELU: { // GELU
    function_context->func.free_local_context_func = free_gelu_local_context;
    function_context->func.local_context = 0;
    allocate_gelu_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MISH
  case NN_FUNCTION_MISH: { // Mish
    function_context->func.free_local_context_func = free_mish_local_context;
    function_context->func.local_context = 0;
    allocate_mish_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RELU6
  case NN_FUNCTION_RELU6: { // ReLU6
    function_context->func.free_local_context_func = free_relu6_local_context;
    function_context->func.local_context = 0;
    allocate_relu6_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_HARDSIGMOID
  case NN_FUNCTION_HARD_SIGMOID_0: { // HardSigmoid
    function_context->func.free_local_context_func =
        free_hard_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_hard_sigmoid_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_HARD_SIGMOID: { // HardSigmoid
    function_context->func.free_local_context_func =
        free_hard_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_hard_sigmoid_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_HARDTANH
  case NN_FUNCTION_HARD_TANH: { // HardTanh
    function_context->func.free_local_context_func =
        free_hard_tanh_local_context;
    function_context->func.local_context = 0;
    allocate_hard_tanh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGSIGMOID
  case NN_FUNCTION_LOG_SIGMOID: { // LogSigmoid
    function_context->func.free_local_context_func =
        free_log_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_log_sigmoid_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SOFTPLUS
  case NN_FUNCTION_SOFTPLUS: { // SoftPlus
    function_context->func.free_local_context_func =
        free_softplus_local_context;
    function_context->func.local_context = 0;
    allocate_softplus_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SOFTSIGN
  case NN_FUNCTION_SOFTSIGN: { // SoftSign
    function_context->func.free_local_context_func =
        free_softsign_local_context;
    function_context->func.local_context = 0;
    allocate_softsign_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TANHSHRINK
  case NN_FUNCTION_TANH_SHRINK: { // TanhShrink
    function_context->func.free_local_context_func =
        free_tanh_shrink_local_context;
    function_context->func.local_context = 0;
    allocate_tanh_shrink_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SINC
  case NN_FUNCTION_SINC: { // Sinc
    function_context->func.free_local_context_func = free_sinc_local_context;
    function_context->func.local_context = 0;
    allocate_sinc_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_FUSEDBATCHNORMALIZATION
  case NN_FUNCTION_FUSED_BATCH_NORMALIZATION: { // FusedBatchNormalization
    function_context->func.free_local_context_func =
        free_fused_batch_normalization_local_context;
    nn_function_fused_batch_normalization_t *f =
        (nn_function_fused_batch_normalization_t *)function;
    fused_batch_normalization_local_context_t *ctx =
        rt_malloc_func(sizeof(fused_batch_normalization_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->decay_rate = f->decay_rate;
    ctx->eps = f->eps;
    ctx->batch_stat = f->batch_stat;
    ctx->nonlinearity = f->nonlinearity;
    function_context->func.local_context = ctx;
    allocate_fused_batch_normalization_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BATCHNORMALIZATION
  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    function_context->func.free_local_context_func =
        free_batch_normalization_local_context;
    nn_function_batch_normalization_t *f =
        (nn_function_batch_normalization_t *)function;
    batch_normalization_local_context_t *ctx =
        rt_malloc_func(sizeof(batch_normalization_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->decay_rate = f->decay_rate;
    ctx->eps = f->eps;
    ctx->batch_stat = f->batch_stat;
    function_context->func.local_context = ctx;
    allocate_batch_normalization_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SYNCBATCHNORMALIZATION
  case NN_FUNCTION_SYNC_BATCH_NORMALIZATION: { // SyncBatchNormalization
    function_context->func.free_local_context_func =
        free_sync_batch_normalization_local_context;
    nn_function_sync_batch_normalization_t *f =
        (nn_function_sync_batch_normalization_t *)function;
    sync_batch_normalization_local_context_t *ctx =
        rt_malloc_func(sizeof(sync_batch_normalization_local_context_t));
    ctx->group = f->group;
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->decay_rate = f->decay_rate;
    ctx->eps = f->eps;
    ctx->batch_stat = f->batch_stat;
    function_context->func.local_context = ctx;
    allocate_sync_batch_normalization_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MEANSUBTRACTION
  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    function_context->func.free_local_context_func =
        free_mean_subtraction_local_context;
    nn_function_mean_subtraction_t *f =
        (nn_function_mean_subtraction_t *)function;
    mean_subtraction_local_context_t *ctx =
        rt_malloc_func(sizeof(mean_subtraction_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->update_running_mean = f->update_running_mean;
    function_context->func.local_context = ctx;
    allocate_mean_subtraction_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CLIPGRADBYVALUE
  case NN_FUNCTION_CLIP_GRAD_BY_VALUE: { // ClipGradByValue
    function_context->func.free_local_context_func =
        free_clip_grad_by_value_local_context;
    function_context->func.local_context = 0;
    allocate_clip_grad_by_value_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CLIPGRADBYNORM
  case NN_FUNCTION_CLIP_GRAD_BY_NORM: { // ClipGradByNorm
    function_context->func.free_local_context_func =
        free_clip_grad_by_norm_local_context;
    nn_function_clip_grad_by_norm_t *f =
        (nn_function_clip_grad_by_norm_t *)function;
    clip_grad_by_norm_local_context_t *ctx =
        rt_malloc_func(sizeof(clip_grad_by_norm_local_context_t));
    ctx->clip_norm = f->clip_norm;
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    function_context->func.local_context = ctx;
    allocate_clip_grad_by_norm_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SUM
  case NN_FUNCTION_SUM: { // Sum
    function_context->func.free_local_context_func = free_sum_local_context;
    nn_function_sum_t *f = (nn_function_sum_t *)function;
    sum_local_context_t *ctx = rt_malloc_func(sizeof(sum_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_sum_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MEAN
  case NN_FUNCTION_MEAN: { // Mean
    function_context->func.free_local_context_func = free_mean_local_context;
    nn_function_mean_t *f = (nn_function_mean_t *)function;
    mean_local_context_t *ctx = rt_malloc_func(sizeof(mean_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_mean_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MAX
  case NN_FUNCTION_MAX_0: { // Max
    function_context->func.free_local_context_func = free_max_local_context;
    nn_function_max_t *f = (nn_function_max_t *)function;
    max_local_context_t *ctx = rt_malloc_func(sizeof(max_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    ctx->with_index = 0;
    ctx->only_index = 0;
    function_context->func.local_context = ctx;
    allocate_max_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_MAX: { // Max
    function_context->func.free_local_context_func = free_max_local_context;
    nn_function_max_t *f = (nn_function_max_t *)function;
    max_local_context_t *ctx = rt_malloc_func(sizeof(max_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    ctx->with_index = f->with_index;
    ctx->only_index = f->only_index;
    function_context->func.local_context = ctx;
    allocate_max_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MIN
  case NN_FUNCTION_MIN_0: { // Min
    function_context->func.free_local_context_func = free_min_local_context;
    nn_function_min_t *f = (nn_function_min_t *)function;
    min_local_context_t *ctx = rt_malloc_func(sizeof(min_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    ctx->with_index = 0;
    ctx->only_index = 0;
    function_context->func.local_context = ctx;
    allocate_min_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_MIN: { // Min
    function_context->func.free_local_context_func = free_min_local_context;
    nn_function_min_t *f = (nn_function_min_t *)function;
    min_local_context_t *ctx = rt_malloc_func(sizeof(min_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    ctx->with_index = f->with_index;
    ctx->only_index = f->only_index;
    function_context->func.local_context = ctx;
    allocate_min_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_PROD
  case NN_FUNCTION_PROD: { // Prod
    function_context->func.free_local_context_func = free_prod_local_context;
    nn_function_prod_t *f = (nn_function_prod_t *)function;
    prod_local_context_t *ctx = rt_malloc_func(sizeof(prod_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_prod_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_REDUCESUM
  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
    function_context->func.free_local_context_func =
        free_reduce_sum_local_context;
    function_context->func.local_context = 0;
    allocate_reduce_sum_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_REDUCEMEAN
  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
    function_context->func.free_local_context_func =
        free_reduce_mean_local_context;
    function_context->func.local_context = 0;
    allocate_reduce_mean_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ADD2
  case NN_FUNCTION_ADD2: { // Add2
    function_context->func.free_local_context_func = free_add2_local_context;
    nn_function_add2_t *f = (nn_function_add2_t *)function;
    add2_local_context_t *ctx = rt_malloc_func(sizeof(add2_local_context_t));
    ctx->inplace = f->inplace;
    function_context->func.local_context = ctx;
    allocate_add2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ADDN
  case NN_FUNCTION_ADD_N: { // AddN
    function_context->func.free_local_context_func = free_add_n_local_context;
    function_context->func.local_context = 0;
    allocate_add_n_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BCADD2
  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    function_context->func.free_local_context_func = free_bc_add2_local_context;
    function_context->func.local_context = 0;
    allocate_bc_add2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SUB2
  case NN_FUNCTION_SUB2: { // Sub2
    function_context->func.free_local_context_func = free_sub2_local_context;
    function_context->func.local_context = 0;
    allocate_sub2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MUL2
  case NN_FUNCTION_MUL2: { // Mul2
    function_context->func.free_local_context_func = free_mul2_local_context;
    function_context->func.local_context = 0;
    allocate_mul2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MULN
  case NN_FUNCTION_MUL_N: { // MulN
    function_context->func.free_local_context_func = free_mul_n_local_context;
    function_context->func.local_context = 0;
    allocate_mul_n_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_DIV2
  case NN_FUNCTION_DIV2: { // Div2
    function_context->func.free_local_context_func = free_div2_local_context;
    function_context->func.local_context = 0;
    allocate_div2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_POW2
  case NN_FUNCTION_POW2: { // Pow2
    function_context->func.free_local_context_func = free_pow2_local_context;
    function_context->func.local_context = 0;
    allocate_pow2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ADDSCALAR
  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    function_context->func.free_local_context_func =
        free_add_scalar_local_context;
    nn_function_add_scalar_t *f = (nn_function_add_scalar_t *)function;
    add_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(add_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_add_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MULSCALAR
  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    function_context->func.free_local_context_func =
        free_mul_scalar_local_context;
    nn_function_mul_scalar_t *f = (nn_function_mul_scalar_t *)function;
    mul_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(mul_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_mul_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_POWSCALAR
  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    function_context->func.free_local_context_func =
        free_pow_scalar_local_context;
    nn_function_pow_scalar_t *f = (nn_function_pow_scalar_t *)function;
    pow_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(pow_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_pow_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RSUBSCALAR
  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    function_context->func.free_local_context_func =
        free_r_sub_scalar_local_context;
    nn_function_r_sub_scalar_t *f = (nn_function_r_sub_scalar_t *)function;
    r_sub_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(r_sub_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_r_sub_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RDIVSCALAR
  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    function_context->func.free_local_context_func =
        free_r_div_scalar_local_context;
    nn_function_r_div_scalar_t *f = (nn_function_r_div_scalar_t *)function;
    r_div_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(r_div_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_r_div_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RPOWSCALAR
  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    function_context->func.free_local_context_func =
        free_r_pow_scalar_local_context;
    nn_function_r_pow_scalar_t *f = (nn_function_r_pow_scalar_t *)function;
    r_pow_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(r_pow_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_r_pow_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SIGN
  case NN_FUNCTION_SIGN: { // Sign
    function_context->func.free_local_context_func = free_sign_local_context;
    nn_function_sign_t *f = (nn_function_sign_t *)function;
    sign_local_context_t *ctx = rt_malloc_func(sizeof(sign_local_context_t));
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_sign_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MINIMUM2
  case NN_FUNCTION_MINIMUM2: { // Minimum2
    function_context->func.free_local_context_func =
        free_minimum2_local_context;
    function_context->func.local_context = 0;
    allocate_minimum2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MAXIMUM2
  case NN_FUNCTION_MAXIMUM2: { // Maximum2
    function_context->func.free_local_context_func =
        free_maximum2_local_context;
    function_context->func.local_context = 0;
    allocate_maximum2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MINIMUMSCALAR
  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    function_context->func.free_local_context_func =
        free_minimum_scalar_local_context;
    nn_function_minimum_scalar_t *f = (nn_function_minimum_scalar_t *)function;
    minimum_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(minimum_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_minimum_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MAXIMUMSCALAR
  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    function_context->func.free_local_context_func =
        free_maximum_scalar_local_context;
    nn_function_maximum_scalar_t *f = (nn_function_maximum_scalar_t *)function;
    maximum_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(maximum_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_maximum_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALAND
  case NN_FUNCTION_LOGICAL_AND: { // LogicalAnd
    function_context->func.free_local_context_func =
        free_logical_and_local_context;
    function_context->func.local_context = 0;
    allocate_logical_and_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALOR
  case NN_FUNCTION_LOGICAL_OR: { // LogicalOr
    function_context->func.free_local_context_func =
        free_logical_or_local_context;
    function_context->func.local_context = 0;
    allocate_logical_or_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALXOR
  case NN_FUNCTION_LOGICAL_XOR: { // LogicalXor
    function_context->func.free_local_context_func =
        free_logical_xor_local_context;
    function_context->func.local_context = 0;
    allocate_logical_xor_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_EQUAL
  case NN_FUNCTION_EQUAL: { // Equal
    function_context->func.free_local_context_func = free_equal_local_context;
    function_context->func.local_context = 0;
    allocate_equal_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_NOTEQUAL
  case NN_FUNCTION_NOT_EQUAL: { // NotEqual
    function_context->func.free_local_context_func =
        free_not_equal_local_context;
    function_context->func.local_context = 0;
    allocate_not_equal_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GREATEREQUAL
  case NN_FUNCTION_GREATER_EQUAL: { // GreaterEqual
    function_context->func.free_local_context_func =
        free_greater_equal_local_context;
    function_context->func.local_context = 0;
    allocate_greater_equal_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GREATER
  case NN_FUNCTION_GREATER: { // Greater
    function_context->func.free_local_context_func = free_greater_local_context;
    function_context->func.local_context = 0;
    allocate_greater_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LESSEQUAL
  case NN_FUNCTION_LESS_EQUAL: { // LessEqual
    function_context->func.free_local_context_func =
        free_less_equal_local_context;
    function_context->func.local_context = 0;
    allocate_less_equal_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LESS
  case NN_FUNCTION_LESS: { // Less
    function_context->func.free_local_context_func = free_less_local_context;
    function_context->func.local_context = 0;
    allocate_less_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALANDSCALAR
  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    function_context->func.free_local_context_func =
        free_logical_and_scalar_local_context;
    nn_function_logical_and_scalar_t *f =
        (nn_function_logical_and_scalar_t *)function;
    logical_and_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(logical_and_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_logical_and_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALORSCALAR
  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    function_context->func.free_local_context_func =
        free_logical_or_scalar_local_context;
    nn_function_logical_or_scalar_t *f =
        (nn_function_logical_or_scalar_t *)function;
    logical_or_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(logical_or_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_logical_or_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALXORSCALAR
  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    function_context->func.free_local_context_func =
        free_logical_xor_scalar_local_context;
    nn_function_logical_xor_scalar_t *f =
        (nn_function_logical_xor_scalar_t *)function;
    logical_xor_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(logical_xor_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_logical_xor_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_EQUALSCALAR
  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    function_context->func.free_local_context_func =
        free_equal_scalar_local_context;
    nn_function_equal_scalar_t *f = (nn_function_equal_scalar_t *)function;
    equal_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_equal_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_NOTEQUALSCALAR
  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    function_context->func.free_local_context_func =
        free_not_equal_scalar_local_context;
    nn_function_not_equal_scalar_t *f =
        (nn_function_not_equal_scalar_t *)function;
    not_equal_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(not_equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_not_equal_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GREATEREQUALSCALAR
  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    function_context->func.free_local_context_func =
        free_greater_equal_scalar_local_context;
    nn_function_greater_equal_scalar_t *f =
        (nn_function_greater_equal_scalar_t *)function;
    greater_equal_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(greater_equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_greater_equal_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GREATERSCALAR
  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    function_context->func.free_local_context_func =
        free_greater_scalar_local_context;
    nn_function_greater_scalar_t *f = (nn_function_greater_scalar_t *)function;
    greater_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(greater_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_greater_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LESSEQUALSCALAR
  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    function_context->func.free_local_context_func =
        free_less_equal_scalar_local_context;
    nn_function_less_equal_scalar_t *f =
        (nn_function_less_equal_scalar_t *)function;
    less_equal_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(less_equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_less_equal_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LESSSCALAR
  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    function_context->func.free_local_context_func =
        free_less_scalar_local_context;
    nn_function_less_scalar_t *f = (nn_function_less_scalar_t *)function;
    less_scalar_local_context_t *ctx =
        rt_malloc_func(sizeof(less_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_less_scalar_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOGICALNOT
  case NN_FUNCTION_LOGICAL_NOT: { // LogicalNot
    function_context->func.free_local_context_func =
        free_logical_not_local_context;
    function_context->func.local_context = 0;
    allocate_logical_not_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ISNAN
  case NN_FUNCTION_ISNAN: { // IsNaN
    function_context->func.free_local_context_func = free_isnan_local_context;
    function_context->func.local_context = 0;
    allocate_isnan_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ISINF
  case NN_FUNCTION_ISINF: { // IsInf
    function_context->func.free_local_context_func = free_isinf_local_context;
    function_context->func.local_context = 0;
    allocate_isinf_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RESETNAN
  case NN_FUNCTION_RESET_NAN: { // ResetNaN
    function_context->func.free_local_context_func =
        free_reset_nan_local_context;
    nn_function_reset_nan_t *f = (nn_function_reset_nan_t *)function;
    reset_nan_local_context_t *ctx =
        rt_malloc_func(sizeof(reset_nan_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_reset_nan_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RESETINF
  case NN_FUNCTION_RESET_INF: { // ResetInf
    function_context->func.free_local_context_func =
        free_reset_inf_local_context;
    nn_function_reset_inf_t *f = (nn_function_reset_inf_t *)function;
    reset_inf_local_context_t *ctx =
        rt_malloc_func(sizeof(reset_inf_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_reset_inf_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_WHERE
  case NN_FUNCTION_WHERE: { // Where
    function_context->func.free_local_context_func = free_where_local_context;
    function_context->func.local_context = 0;
    allocate_where_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CONSTANT
  case NN_FUNCTION_CONSTANT: { // Constant
    function_context->func.free_local_context_func =
        free_constant_local_context;
    nn_function_constant_t *f = (nn_function_constant_t *)function;
    constant_local_context_t *ctx =
        rt_malloc_func(sizeof(constant_local_context_t));
    ctx->val = f->val;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_constant_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ARANGE
  case NN_FUNCTION_ARANGE: { // Arange
    function_context->func.free_local_context_func = free_arange_local_context;
    nn_function_arange_t *f = (nn_function_arange_t *)function;
    arange_local_context_t *ctx =
        rt_malloc_func(sizeof(arange_local_context_t));
    ctx->start = f->start;
    ctx->stop = f->stop;
    ctx->step = f->step;
    function_context->func.local_context = ctx;
    allocate_arange_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ABS
  case NN_FUNCTION_ABS: { // Abs
    function_context->func.free_local_context_func = free_abs_local_context;
    function_context->func.local_context = 0;
    allocate_abs_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_EXP
  case NN_FUNCTION_EXP: { // Exp
    function_context->func.free_local_context_func = free_exp_local_context;
    function_context->func.local_context = 0;
    allocate_exp_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_LOG
  case NN_FUNCTION_LOG: { // Log
    function_context->func.free_local_context_func = free_log_local_context;
    function_context->func.local_context = 0;
    allocate_log_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_IDENTITY
  case NN_FUNCTION_IDENTITY: { // Identity
    function_context->func.free_local_context_func =
        free_identity_local_context;
    function_context->func.local_context = 0;
    allocate_identity_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BATCHMATMUL
  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    function_context->func.free_local_context_func =
        free_batch_matmul_local_context;
    nn_function_batch_matmul_t *f = (nn_function_batch_matmul_t *)function;
    batch_matmul_local_context_t *ctx =
        rt_malloc_func(sizeof(batch_matmul_local_context_t));
    ctx->transpose_a = f->transpose_a;
    ctx->transpose_b = f->transpose_b;
    function_context->func.local_context = ctx;
    allocate_batch_matmul_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ROUND
  case NN_FUNCTION_ROUND: { // Round
    function_context->func.free_local_context_func = free_round_local_context;
    function_context->func.local_context = 0;
    allocate_round_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CEIL
  case NN_FUNCTION_CEIL: { // Ceil
    function_context->func.free_local_context_func = free_ceil_local_context;
    function_context->func.local_context = 0;
    allocate_ceil_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_FLOOR
  case NN_FUNCTION_FLOOR: { // Floor
    function_context->func.free_local_context_func = free_floor_local_context;
    function_context->func.local_context = 0;
    allocate_floor_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SIN
  case NN_FUNCTION_SIN: { // Sin
    function_context->func.free_local_context_func = free_sin_local_context;
    function_context->func.local_context = 0;
    allocate_sin_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_COS
  case NN_FUNCTION_COS: { // Cos
    function_context->func.free_local_context_func = free_cos_local_context;
    function_context->func.local_context = 0;
    allocate_cos_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TAN
  case NN_FUNCTION_TAN: { // Tan
    function_context->func.free_local_context_func = free_tan_local_context;
    function_context->func.local_context = 0;
    allocate_tan_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SINH
  case NN_FUNCTION_SINH: { // Sinh
    function_context->func.free_local_context_func = free_sinh_local_context;
    function_context->func.local_context = 0;
    allocate_sinh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_COSH
  case NN_FUNCTION_COSH: { // Cosh
    function_context->func.free_local_context_func = free_cosh_local_context;
    function_context->func.local_context = 0;
    allocate_cosh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ASIN
  case NN_FUNCTION_ASIN: { // ASin
    function_context->func.free_local_context_func = free_asin_local_context;
    function_context->func.local_context = 0;
    allocate_asin_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ACOS
  case NN_FUNCTION_ACOS: { // ACos
    function_context->func.free_local_context_func = free_acos_local_context;
    function_context->func.local_context = 0;
    allocate_acos_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ATAN
  case NN_FUNCTION_ATAN: { // ATan
    function_context->func.free_local_context_func = free_atan_local_context;
    function_context->func.local_context = 0;
    allocate_atan_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ATAN2
  case NN_FUNCTION_ATAN2: { // ATan2
    function_context->func.free_local_context_func = free_atan2_local_context;
    function_context->func.local_context = 0;
    allocate_atan2_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ASINH
  case NN_FUNCTION_ASINH: { // ASinh
    function_context->func.free_local_context_func = free_asinh_local_context;
    function_context->func.local_context = 0;
    allocate_asinh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ACOSH
  case NN_FUNCTION_ACOSH: { // ACosh
    function_context->func.free_local_context_func = free_acosh_local_context;
    function_context->func.local_context = 0;
    allocate_acosh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ATANH
  case NN_FUNCTION_ATANH: { // ATanh
    function_context->func.free_local_context_func = free_atanh_local_context;
    function_context->func.local_context = 0;
    allocate_atanh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CONCATENATE
  case NN_FUNCTION_CONCATENATE: { // Concatenate
    function_context->func.free_local_context_func =
        free_concatenate_local_context;
    nn_function_concatenate_t *f = (nn_function_concatenate_t *)function;
    concatenate_local_context_t *ctx =
        rt_malloc_func(sizeof(concatenate_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_concatenate_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SPLIT
  case NN_FUNCTION_SPLIT: { // Split
    function_context->func.free_local_context_func = free_split_local_context;
    nn_function_split_t *f = (nn_function_split_t *)function;
    split_local_context_t *ctx = rt_malloc_func(sizeof(split_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_split_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_STACK
  case NN_FUNCTION_STACK: { // Stack
    function_context->func.free_local_context_func = free_stack_local_context;
    nn_function_stack_t *f = (nn_function_stack_t *)function;
    stack_local_context_t *ctx = rt_malloc_func(sizeof(stack_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_stack_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SLICE
  case NN_FUNCTION_SLICE: { // Slice
    function_context->func.free_local_context_func = free_slice_local_context;
    nn_function_slice_t *f = (nn_function_slice_t *)function;
    slice_local_context_t *ctx = rt_malloc_func(sizeof(slice_local_context_t));
    ctx->start = create_rt_list_from_nn_list(n, f->start);
    ctx->stop = create_rt_list_from_nn_list(n, f->stop);
    ctx->step = create_rt_list_from_nn_list(n, f->step);
    function_context->func.local_context = ctx;
    allocate_slice_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_PAD
  case NN_FUNCTION_PAD: { // Pad
    function_context->func.free_local_context_func = free_pad_local_context;
    nn_function_pad_t *f = (nn_function_pad_t *)function;
    pad_local_context_t *ctx = rt_malloc_func(sizeof(pad_local_context_t));
    ctx->pad_width = create_rt_list_from_nn_list(n, f->pad_width);
    ctx->mode = f->mode;
    ctx->constant_value = f->constant_value;
    function_context->func.local_context = ctx;
    allocate_pad_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TRANSPOSE
  case NN_FUNCTION_TRANSPOSE: { // Transpose
    function_context->func.free_local_context_func =
        free_transpose_local_context;
    nn_function_transpose_t *f = (nn_function_transpose_t *)function;
    transpose_local_context_t *ctx =
        rt_malloc_func(sizeof(transpose_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    function_context->func.local_context = ctx;
    allocate_transpose_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BROADCAST
  case NN_FUNCTION_BROADCAST: { // Broadcast
    function_context->func.free_local_context_func =
        free_broadcast_local_context;
    nn_function_broadcast_t *f = (nn_function_broadcast_t *)function;
    broadcast_local_context_t *ctx =
        rt_malloc_func(sizeof(broadcast_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_broadcast_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BROADCASTTO
  case NN_FUNCTION_BROADCAST_TO: { // BroadcastTo
    function_context->func.free_local_context_func =
        free_broadcast_to_local_context;
    nn_function_broadcast_to_t *f = (nn_function_broadcast_to_t *)function;
    broadcast_to_local_context_t *ctx =
        rt_malloc_func(sizeof(broadcast_to_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_broadcast_to_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TILE
  case NN_FUNCTION_TILE: { // Tile
    function_context->func.free_local_context_func = free_tile_local_context;
    nn_function_tile_t *f = (nn_function_tile_t *)function;
    tile_local_context_t *ctx = rt_malloc_func(sizeof(tile_local_context_t));
    ctx->reps = create_rt_list_from_nn_list(n, f->reps);
    function_context->func.local_context = ctx;
    allocate_tile_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ONEHOT
  case NN_FUNCTION_ONE_HOT: { // OneHot
    function_context->func.free_local_context_func = free_one_hot_local_context;
    nn_function_one_hot_t *f = (nn_function_one_hot_t *)function;
    one_hot_local_context_t *ctx =
        rt_malloc_func(sizeof(one_hot_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_one_hot_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_FLIP
  case NN_FUNCTION_FLIP: { // Flip
    function_context->func.free_local_context_func = free_flip_local_context;
    nn_function_flip_t *f = (nn_function_flip_t *)function;
    flip_local_context_t *ctx = rt_malloc_func(sizeof(flip_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    function_context->func.local_context = ctx;
    allocate_flip_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SHIFT
  case NN_FUNCTION_SHIFT: { // Shift
    function_context->func.free_local_context_func = free_shift_local_context;
    nn_function_shift_t *f = (nn_function_shift_t *)function;
    shift_local_context_t *ctx = rt_malloc_func(sizeof(shift_local_context_t));
    ctx->shifts = create_rt_list_from_nn_list(n, f->shifts);
    ctx->border_mode = f->border_mode;
    function_context->func.local_context = ctx;
    allocate_shift_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SORT
  case NN_FUNCTION_SORT: { // Sort
    function_context->func.free_local_context_func = free_sort_local_context;
    nn_function_sort_t *f = (nn_function_sort_t *)function;
    sort_local_context_t *ctx = rt_malloc_func(sizeof(sort_local_context_t));
    ctx->axis = f->axis;
    ctx->reverse = f->reverse;
    ctx->with_index = f->with_index;
    ctx->only_index = f->only_index;
    function_context->func.local_context = ctx;
    allocate_sort_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RESHAPE
  case NN_FUNCTION_RESHAPE_0: { // Reshape
    function_context->func.free_local_context_func = free_reshape_local_context;
    nn_function_reshape_t *f = (nn_function_reshape_t *)function;
    reshape_local_context_t *ctx =
        rt_malloc_func(sizeof(reshape_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->inplace = 1;
    function_context->func.local_context = ctx;
    allocate_reshape_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_RESHAPE: { // Reshape
    function_context->func.free_local_context_func = free_reshape_local_context;
    nn_function_reshape_t *f = (nn_function_reshape_t *)function;
    reshape_local_context_t *ctx =
        rt_malloc_func(sizeof(reshape_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->inplace = f->inplace;
    function_context->func.local_context = ctx;
    allocate_reshape_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MATRIXDIAG
  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
    function_context->func.free_local_context_func =
        free_matrix_diag_local_context;
    function_context->func.local_context = 0;
    allocate_matrix_diag_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MATRIXDIAGPART
  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
    function_context->func.free_local_context_func =
        free_matrix_diag_part_local_context;
    function_context->func.local_context = 0;
    allocate_matrix_diag_part_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BATCHINV
  case NN_FUNCTION_BATCH_INV: { // BatchInv
    function_context->func.free_local_context_func =
        free_batch_inv_local_context;
    function_context->func.local_context = 0;
    allocate_batch_inv_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BATCHDET
  case NN_FUNCTION_BATCH_DET: { // BatchDet
    function_context->func.free_local_context_func =
        free_batch_det_local_context;
    function_context->func.local_context = 0;
    allocate_batch_det_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ASSIGN
  case NN_FUNCTION_ASSIGN: { // Assign
    function_context->func.free_local_context_func = free_assign_local_context;
    function_context->func.local_context = 0;
    allocate_assign_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_GATHERND
  case NN_FUNCTION_GATHER_ND: { // GatherNd
    function_context->func.free_local_context_func =
        free_gather_nd_local_context;
    function_context->func.local_context = 0;
    allocate_gather_nd_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SCATTERND
  case NN_FUNCTION_SCATTER_ND: { // ScatterNd
    function_context->func.free_local_context_func =
        free_scatter_nd_local_context;
    nn_function_scatter_nd_t *f = (nn_function_scatter_nd_t *)function;
    scatter_nd_local_context_t *ctx =
        rt_malloc_func(sizeof(scatter_nd_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_scatter_nd_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_INTERPOLATE
  case NN_FUNCTION_INTERPOLATE_0: { // Interpolate
    function_context->func.free_local_context_func =
        free_interpolate_local_context;
    nn_function_interpolate_t *f = (nn_function_interpolate_t *)function;
    interpolate_local_context_t *ctx =
        rt_malloc_func(sizeof(interpolate_local_context_t));
    ctx->output_size = create_rt_list_from_nn_list(n, f->output_size);
    ctx->mode = f->mode;
    ctx->align_corners = f->align_corners;
    ctx->half_pixel = 0;
    ctx->half_pixel_for_nn = 0;
    ctx->channel_last = 0;
    function_context->func.local_context = ctx;
    allocate_interpolate_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_INTERPOLATE_1: { // Interpolate
    function_context->func.free_local_context_func =
        free_interpolate_local_context;
    nn_function_interpolate_t *f = (nn_function_interpolate_t *)function;
    interpolate_local_context_t *ctx =
        rt_malloc_func(sizeof(interpolate_local_context_t));
    ctx->output_size = create_rt_list_from_nn_list(n, f->output_size);
    ctx->mode = f->mode;
    ctx->align_corners = f->align_corners;
    ctx->half_pixel = f->half_pixel;
    ctx->half_pixel_for_nn = 0;
    ctx->channel_last = 0;
    function_context->func.local_context = ctx;
    allocate_interpolate_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_INTERPOLATE: { // Interpolate
    function_context->func.free_local_context_func =
        free_interpolate_local_context;
    nn_function_interpolate_t *f = (nn_function_interpolate_t *)function;
    interpolate_local_context_t *ctx =
        rt_malloc_func(sizeof(interpolate_local_context_t));
    ctx->output_size = create_rt_list_from_nn_list(n, f->output_size);
    ctx->mode = f->mode;
    ctx->align_corners = f->align_corners;
    ctx->half_pixel = f->half_pixel;
    ctx->half_pixel_for_nn = f->half_pixel_for_nn;
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_interpolate_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_FFT
  case NN_FUNCTION_FFT: { // FFT
    function_context->func.free_local_context_func = free_fft_local_context;
    nn_function_fft_t *f = (nn_function_fft_t *)function;
    fft_local_context_t *ctx = rt_malloc_func(sizeof(fft_local_context_t));
    ctx->signal_ndim = f->signal_ndim;
    ctx->normalized = f->normalized;
    function_context->func.local_context = ctx;
    allocate_fft_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_IFFT
  case NN_FUNCTION_IFFT: { // IFFT
    function_context->func.free_local_context_func = free_ifft_local_context;
    nn_function_ifft_t *f = (nn_function_ifft_t *)function;
    ifft_local_context_t *ctx = rt_malloc_func(sizeof(ifft_local_context_t));
    ctx->signal_ndim = f->signal_ndim;
    ctx->normalized = f->normalized;
    function_context->func.local_context = ctx;
    allocate_ifft_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_DROPOUT
  case NN_FUNCTION_DROPOUT: { // Dropout
    function_context->func.free_local_context_func = free_dropout_local_context;
    nn_function_dropout_t *f = (nn_function_dropout_t *)function;
    dropout_local_context_t *ctx =
        rt_malloc_func(sizeof(dropout_local_context_t));
    ctx->p = f->p;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_dropout_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TOPKDATA
  case NN_FUNCTION_TOP_K_DATA: { // TopKData
    function_context->func.free_local_context_func =
        free_top_k_data_local_context;
    nn_function_top_k_data_t *f = (nn_function_top_k_data_t *)function;
    top_k_data_local_context_t *ctx =
        rt_malloc_func(sizeof(top_k_data_local_context_t));
    ctx->k = f->k;
    ctx->abs = f->abs;
    ctx->reduce = f->reduce;
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_top_k_data_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TOPKGRAD
  case NN_FUNCTION_TOP_K_GRAD: { // TopKGrad
    function_context->func.free_local_context_func =
        free_top_k_grad_local_context;
    nn_function_top_k_grad_t *f = (nn_function_top_k_grad_t *)function;
    top_k_grad_local_context_t *ctx =
        rt_malloc_func(sizeof(top_k_grad_local_context_t));
    ctx->k = f->k;
    ctx->abs = f->abs;
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_top_k_grad_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RAND
  case NN_FUNCTION_RAND: { // Rand
    function_context->func.free_local_context_func = free_rand_local_context;
    nn_function_rand_t *f = (nn_function_rand_t *)function;
    rand_local_context_t *ctx = rt_malloc_func(sizeof(rand_local_context_t));
    ctx->low = f->low;
    ctx->high = f->high;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_rand_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDINT
  case NN_FUNCTION_RANDINT: { // Randint
    function_context->func.free_local_context_func = free_randint_local_context;
    nn_function_randint_t *f = (nn_function_randint_t *)function;
    randint_local_context_t *ctx =
        rt_malloc_func(sizeof(randint_local_context_t));
    ctx->low = f->low;
    ctx->high = f->high;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_randint_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDN
  case NN_FUNCTION_RANDN: { // Randn
    function_context->func.free_local_context_func = free_randn_local_context;
    nn_function_randn_t *f = (nn_function_randn_t *)function;
    randn_local_context_t *ctx = rt_malloc_func(sizeof(randn_local_context_t));
    ctx->mu = f->mu;
    ctx->sigma = f->sigma;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_randn_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDBINOMIAL
  case NN_FUNCTION_RAND_BINOMIAL: { // RandBinomial
    function_context->func.free_local_context_func =
        free_rand_binomial_local_context;
    nn_function_rand_binomial_t *f = (nn_function_rand_binomial_t *)function;
    rand_binomial_local_context_t *ctx =
        rt_malloc_func(sizeof(rand_binomial_local_context_t));
    ctx->n = f->n;
    ctx->p = f->p;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_rand_binomial_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDBETA
  case NN_FUNCTION_RAND_BETA: { // RandBeta
    function_context->func.free_local_context_func =
        free_rand_beta_local_context;
    nn_function_rand_beta_t *f = (nn_function_rand_beta_t *)function;
    rand_beta_local_context_t *ctx =
        rt_malloc_func(sizeof(rand_beta_local_context_t));
    ctx->alpha = f->alpha;
    ctx->beta = f->beta;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_rand_beta_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDGAMMA
  case NN_FUNCTION_RAND_GAMMA: { // RandGamma
    function_context->func.free_local_context_func =
        free_rand_gamma_local_context;
    nn_function_rand_gamma_t *f = (nn_function_rand_gamma_t *)function;
    rand_gamma_local_context_t *ctx =
        rt_malloc_func(sizeof(rand_gamma_local_context_t));
    ctx->k = f->k;
    ctx->theta = f->theta;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_rand_gamma_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDOMCHOICE
  case NN_FUNCTION_RANDOM_CHOICE: { // RandomChoice
    function_context->func.free_local_context_func =
        free_random_choice_local_context;
    nn_function_random_choice_t *f = (nn_function_random_choice_t *)function;
    random_choice_local_context_t *ctx =
        rt_malloc_func(sizeof(random_choice_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->replace = f->replace;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_choice_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDOMCROP
  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    function_context->func.free_local_context_func =
        free_random_crop_local_context;
    nn_function_random_crop_t *f = (nn_function_random_crop_t *)function;
    random_crop_local_context_t *ctx =
        rt_malloc_func(sizeof(random_crop_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_crop_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDOMFLIP
  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    function_context->func.free_local_context_func =
        free_random_flip_local_context;
    nn_function_random_flip_t *f = (nn_function_random_flip_t *)function;
    random_flip_local_context_t *ctx =
        rt_malloc_func(sizeof(random_flip_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_flip_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDOMSHIFT
  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    function_context->func.free_local_context_func =
        free_random_shift_local_context;
    nn_function_random_shift_t *f = (nn_function_random_shift_t *)function;
    random_shift_local_context_t *ctx =
        rt_malloc_func(sizeof(random_shift_local_context_t));
    ctx->shifts = create_rt_list_from_nn_list(n, f->shifts);
    ctx->border_mode = f->border_mode;
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_shift_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_RANDOMERASE
  case NN_FUNCTION_RANDOM_ERASE_1: { // RandomErase
    function_context->func.free_local_context_func =
        free_random_erase_local_context;
    nn_function_random_erase_t *f = (nn_function_random_erase_t *)function;
    random_erase_local_context_t *ctx =
        rt_malloc_func(sizeof(random_erase_local_context_t));
    ctx->prob = f->prob;
    ctx->n = f->n;
    ctx->share = f->share;
    ctx->inplace = f->inplace;
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    ctx->channel_last = f->channel_last;
    ctx->ste_fine_grained = f->ste_fine_grained;
    function_context->func.local_context = ctx;
    allocate_random_erase_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_RANDOM_ERASE: { // RandomErase
    function_context->func.free_local_context_func =
        free_random_erase_local_context;
    nn_function_random_erase_t *f = (nn_function_random_erase_t *)function;
    random_erase_local_context_t *ctx =
        rt_malloc_func(sizeof(random_erase_local_context_t));
    ctx->prob = f->prob;
    ctx->n = f->n;
    ctx->share = f->share;
    ctx->inplace = f->inplace;
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    ctx->channel_last = f->channel_last;
    ctx->ste_fine_grained = f->ste_fine_grained;
    function_context->func.local_context = ctx;
    allocate_random_erase_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_IMAGEAUGMENTATION
  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    function_context->func.free_local_context_func =
        free_image_augmentation_local_context;
    nn_function_image_augmentation_t *f =
        (nn_function_image_augmentation_t *)function;
    image_augmentation_local_context_t *ctx =
        rt_malloc_func(sizeof(image_augmentation_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->min_scale = f->min_scale;
    ctx->max_scale = f->max_scale;
    ctx->angle = f->angle;
    ctx->aspect_ratio = f->aspect_ratio;
    ctx->distortion = f->distortion;
    ctx->flip_lr = f->flip_lr;
    ctx->flip_ud = f->flip_ud;
    ctx->brightness = f->brightness;
    ctx->brightness_each = f->brightness_each;
    ctx->contrast = f->contrast;
    ctx->contrast_center = f->contrast_center;
    ctx->contrast_each = f->contrast_each;
    ctx->noise = f->noise;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_image_augmentation_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SIGMOIDCROSSENTROPY
  case NN_FUNCTION_SIGMOID_CROSS_ENTROPY: { // SigmoidCrossEntropy
    function_context->func.free_local_context_func =
        free_sigmoid_cross_entropy_local_context;
    function_context->func.local_context = 0;
    allocate_sigmoid_cross_entropy_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYCROSSENTROPY
  case NN_FUNCTION_BINARY_CROSS_ENTROPY: { // BinaryCrossEntropy
    function_context->func.free_local_context_func =
        free_binary_cross_entropy_local_context;
    function_context->func.local_context = 0;
    allocate_binary_cross_entropy_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SOFTMAXCROSSENTROPY
  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    function_context->func.free_local_context_func =
        free_softmax_cross_entropy_local_context;
    nn_function_softmax_cross_entropy_t *f =
        (nn_function_softmax_cross_entropy_t *)function;
    softmax_cross_entropy_local_context_t *ctx =
        rt_malloc_func(sizeof(softmax_cross_entropy_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_softmax_cross_entropy_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CATEGORICALCROSSENTROPY
  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    function_context->func.free_local_context_func =
        free_categorical_cross_entropy_local_context;
    nn_function_categorical_cross_entropy_t *f =
        (nn_function_categorical_cross_entropy_t *)function;
    categorical_cross_entropy_local_context_t *ctx =
        rt_malloc_func(sizeof(categorical_cross_entropy_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_categorical_cross_entropy_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SQUAREDERROR
  case NN_FUNCTION_SQUARED_ERROR: { // SquaredError
    function_context->func.free_local_context_func =
        free_squared_error_local_context;
    function_context->func.local_context = 0;
    allocate_squared_error_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_ABSOLUTEERROR
  case NN_FUNCTION_ABSOLUTE_ERROR: { // AbsoluteError
    function_context->func.free_local_context_func =
        free_absolute_error_local_context;
    function_context->func.local_context = 0;
    allocate_absolute_error_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_HUBERLOSS
  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    function_context->func.free_local_context_func =
        free_huber_loss_local_context;
    nn_function_huber_loss_t *f = (nn_function_huber_loss_t *)function;
    huber_loss_local_context_t *ctx =
        rt_malloc_func(sizeof(huber_loss_local_context_t));
    ctx->delta = f->delta;
    function_context->func.local_context = ctx;
    allocate_huber_loss_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_EPSILONINSENSITIVELOSS
  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    function_context->func.free_local_context_func =
        free_epsilon_insensitive_loss_local_context;
    nn_function_epsilon_insensitive_loss_t *f =
        (nn_function_epsilon_insensitive_loss_t *)function;
    epsilon_insensitive_loss_local_context_t *ctx =
        rt_malloc_func(sizeof(epsilon_insensitive_loss_local_context_t));
    ctx->epsilon = f->epsilon;
    function_context->func.local_context = ctx;
    allocate_epsilon_insensitive_loss_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_KLMULTINOMIAL
  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    function_context->func.free_local_context_func =
        free_kl_multinomial_local_context;
    nn_function_kl_multinomial_t *f = (nn_function_kl_multinomial_t *)function;
    kl_multinomial_local_context_t *ctx =
        rt_malloc_func(sizeof(kl_multinomial_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_kl_multinomial_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_AFFINEGRID
  case NN_FUNCTION_AFFINE_GRID: { // AffineGrid
    function_context->func.free_local_context_func =
        free_affine_grid_local_context;
    nn_function_affine_grid_t *f = (nn_function_affine_grid_t *)function;
    affine_grid_local_context_t *ctx =
        rt_malloc_func(sizeof(affine_grid_local_context_t));
    ctx->size = create_rt_list_from_nn_list(n, f->size);
    ctx->align_corners = f->align_corners;
    function_context->func.local_context = ctx;
    allocate_affine_grid_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_WARPBYGRID
  case NN_FUNCTION_WARP_BY_GRID: { // WarpByGrid
    function_context->func.free_local_context_func =
        free_warp_by_grid_local_context;
    nn_function_warp_by_grid_t *f = (nn_function_warp_by_grid_t *)function;
    warp_by_grid_local_context_t *ctx =
        rt_malloc_func(sizeof(warp_by_grid_local_context_t));
    ctx->mode = f->mode;
    ctx->padding_mode = f->padding_mode;
    ctx->align_corners = f->align_corners;
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_warp_by_grid_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_WARPBYFLOW
  case NN_FUNCTION_WARP_BY_FLOW: { // WarpByFlow
    function_context->func.free_local_context_func =
        free_warp_by_flow_local_context;
    function_context->func.local_context = 0;
    allocate_warp_by_flow_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYSIGMOID
  case NN_FUNCTION_BINARY_SIGMOID: { // BinarySigmoid
    function_context->func.free_local_context_func =
        free_binary_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_binary_sigmoid_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYTANH
  case NN_FUNCTION_BINARY_TANH: { // BinaryTanh
    function_context->func.free_local_context_func =
        free_binary_tanh_local_context;
    function_context->func.local_context = 0;
    allocate_binary_tanh_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYCONNECTAFFINE
  case NN_FUNCTION_BINARY_CONNECT_AFFINE_0: { // BinaryConnectAffine
    function_context->func.free_local_context_func =
        free_binary_connect_affine_local_context;
    nn_function_binary_connect_affine_t *f =
        (nn_function_binary_connect_affine_t *)function;
    binary_connect_affine_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_connect_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->quantize_zero_to = 1.0;
    function_context->func.local_context = ctx;
    allocate_binary_connect_affine_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    function_context->func.free_local_context_func =
        free_binary_connect_affine_local_context;
    nn_function_binary_connect_affine_t *f =
        (nn_function_binary_connect_affine_t *)function;
    binary_connect_affine_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_connect_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->quantize_zero_to = f->quantize_zero_to;
    function_context->func.local_context = ctx;
    allocate_binary_connect_affine_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYCONNECTCONVOLUTION
  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION_0: { // BinaryConnectConvolution
    function_context->func.free_local_context_func =
        free_binary_connect_convolution_local_context;
    nn_function_binary_connect_convolution_t *f =
        (nn_function_binary_connect_convolution_t *)function;
    binary_connect_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_connect_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->quantize_zero_to = 1.0;
    function_context->func.local_context = ctx;
    allocate_binary_connect_convolution_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    function_context->func.free_local_context_func =
        free_binary_connect_convolution_local_context;
    nn_function_binary_connect_convolution_t *f =
        (nn_function_binary_connect_convolution_t *)function;
    binary_connect_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_connect_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->quantize_zero_to = f->quantize_zero_to;
    function_context->func.local_context = ctx;
    allocate_binary_connect_convolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYWEIGHTAFFINE
  case NN_FUNCTION_BINARY_WEIGHT_AFFINE_0: { // BinaryWeightAffine
    function_context->func.free_local_context_func =
        free_binary_weight_affine_local_context;
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)function;
    binary_weight_affine_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_weight_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->quantize_zero_to = 1.0;
    function_context->func.local_context = ctx;
    allocate_binary_weight_affine_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    function_context->func.free_local_context_func =
        free_binary_weight_affine_local_context;
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)function;
    binary_weight_affine_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_weight_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->quantize_zero_to = f->quantize_zero_to;
    function_context->func.local_context = ctx;
    allocate_binary_weight_affine_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYWEIGHTCONVOLUTION
  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION_0: { // BinaryWeightConvolution
    function_context->func.free_local_context_func =
        free_binary_weight_convolution_local_context;
    nn_function_binary_weight_convolution_t *f =
        (nn_function_binary_weight_convolution_t *)function;
    binary_weight_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_weight_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->quantize_zero_to = 1.0;
    function_context->func.local_context = ctx;
    allocate_binary_weight_convolution_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    function_context->func.free_local_context_func =
        free_binary_weight_convolution_local_context;
    nn_function_binary_weight_convolution_t *f =
        (nn_function_binary_weight_convolution_t *)function;
    binary_weight_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(binary_weight_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->quantize_zero_to = f->quantize_zero_to;
    function_context->func.local_context = ctx;
    allocate_binary_weight_convolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_INQAFFINE
  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    function_context->func.free_local_context_func =
        free_inq_affine_local_context;
    nn_function_inq_affine_t *f = (nn_function_inq_affine_t *)function;
    inq_affine_local_context_t *ctx =
        rt_malloc_func(sizeof(inq_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->num_bits = f->num_bits;
    ctx->inq_iterations = create_rt_list_from_nn_list(n, f->inq_iterations);
    ctx->selection_algorithm = f->selection_algorithm;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_inq_affine_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_INQCONVOLUTION
  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    function_context->func.free_local_context_func =
        free_inq_convolution_local_context;
    nn_function_inq_convolution_t *f =
        (nn_function_inq_convolution_t *)function;
    inq_convolution_local_context_t *ctx =
        rt_malloc_func(sizeof(inq_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    ctx->num_bits = f->num_bits;
    ctx->inq_iterations = create_rt_list_from_nn_list(n, f->inq_iterations);
    ctx->selection_algorithm = f->selection_algorithm;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_inq_convolution_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_FIXEDPOINTQUANTIZE
  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    function_context->func.free_local_context_func =
        free_fixed_point_quantize_local_context;
    nn_function_fixed_point_quantize_t *f =
        (nn_function_fixed_point_quantize_t *)function;
    fixed_point_quantize_local_context_t *ctx =
        rt_malloc_func(sizeof(fixed_point_quantize_local_context_t));
    ctx->sign = f->sign;
    ctx->n = f->n;
    ctx->delta = f->delta;
    ctx->ste_fine_grained = f->ste_fine_grained;
    function_context->func.local_context = ctx;
    allocate_fixed_point_quantize_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MINMAXQUANTIZE
  case NN_FUNCTION_MIN_MAX_QUANTIZE_0: { // MinMaxQuantize
    function_context->func.free_local_context_func =
        free_min_max_quantize_local_context;
    nn_function_min_max_quantize_t *f =
        (nn_function_min_max_quantize_t *)function;
    min_max_quantize_local_context_t *ctx =
        rt_malloc_func(sizeof(min_max_quantize_local_context_t));
    ctx->decay = f->decay;
    ctx->x_min_max = f->x_min_max;
    ctx->ema = f->ema;
    ctx->ste_fine_grained = f->ste_fine_grained;
    ctx->eps = 0.01;
    function_context->func.local_context = ctx;
    allocate_min_max_quantize_local_context(&function_context->func);
  } break;
  case NN_FUNCTION_MIN_MAX_QUANTIZE: { // MinMaxQuantize
    function_context->func.free_local_context_func =
        free_min_max_quantize_local_context;
    nn_function_min_max_quantize_t *f =
        (nn_function_min_max_quantize_t *)function;
    min_max_quantize_local_context_t *ctx =
        rt_malloc_func(sizeof(min_max_quantize_local_context_t));
    ctx->decay = f->decay;
    ctx->x_min_max = f->x_min_max;
    ctx->ema = f->ema;
    ctx->ste_fine_grained = f->ste_fine_grained;
    ctx->eps = f->eps;
    function_context->func.local_context = ctx;
    allocate_min_max_quantize_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_POW2QUANTIZE
  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    function_context->func.free_local_context_func =
        free_pow2_quantize_local_context;
    nn_function_pow2_quantize_t *f = (nn_function_pow2_quantize_t *)function;
    pow2_quantize_local_context_t *ctx =
        rt_malloc_func(sizeof(pow2_quantize_local_context_t));
    ctx->sign = f->sign;
    ctx->with_zero = f->with_zero;
    ctx->n = f->n;
    ctx->m = f->m;
    ctx->ste_fine_grained = f->ste_fine_grained;
    function_context->func.local_context = ctx;
    allocate_pow2_quantize_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_PRUNE
  case NN_FUNCTION_PRUNE: { // Prune
    function_context->func.free_local_context_func = free_prune_local_context;
    nn_function_prune_t *f = (nn_function_prune_t *)function;
    prune_local_context_t *ctx = rt_malloc_func(sizeof(prune_local_context_t));
    ctx->rate = f->rate;
    function_context->func.local_context = ctx;
    allocate_prune_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_QUANTIZELINEAR
  case NN_FUNCTION_QUANTIZE_LINEAR: { // QuantizeLinear
    function_context->func.free_local_context_func =
        free_quantize_linear_local_context;
    nn_function_quantize_linear_t *f =
        (nn_function_quantize_linear_t *)function;
    quantize_linear_local_context_t *ctx =
        rt_malloc_func(sizeof(quantize_linear_local_context_t));
    ctx->round_mode = f->round_mode;
    ctx->narrow_range = f->narrow_range;
    ctx->dtype = f->dtype;
    function_context->func.local_context = ctx;
    allocate_quantize_linear_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_DEQUANTIZELINEAR
  case NN_FUNCTION_DEQUANTIZE_LINEAR: { // DequantizeLinear
    function_context->func.free_local_context_func =
        free_dequantize_linear_local_context;
    function_context->func.local_context = 0;
    allocate_dequantize_linear_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_TOPNERROR
  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    function_context->func.free_local_context_func =
        free_top_n_error_local_context;
    nn_function_top_n_error_t *f = (nn_function_top_n_error_t *)function;
    top_n_error_local_context_t *ctx =
        rt_malloc_func(sizeof(top_n_error_local_context_t));
    ctx->axis = f->axis;
    ctx->n = f->n;
    function_context->func.local_context = ctx;
    allocate_top_n_error_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_BINARYERROR
  case NN_FUNCTION_BINARY_ERROR: { // BinaryError
    function_context->func.free_local_context_func =
        free_binary_error_local_context;
    function_context->func.local_context = 0;
    allocate_binary_error_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_CONFUSIONMATRIX
  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    function_context->func.free_local_context_func =
        free_confusion_matrix_local_context;
    nn_function_confusion_matrix_t *f =
        (nn_function_confusion_matrix_t *)function;
    confusion_matrix_local_context_t *ctx =
        rt_malloc_func(sizeof(confusion_matrix_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_confusion_matrix_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_VATNOISE
  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    function_context->func.free_local_context_func =
        free_vat_noise_local_context;
    nn_function_vat_noise_t *f = (nn_function_vat_noise_t *)function;
    vat_noise_local_context_t *ctx =
        rt_malloc_func(sizeof(vat_noise_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->eps = f->eps;
    function_context->func.local_context = ctx;
    allocate_vat_noise_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_UNLINK
  case NN_FUNCTION_UNLINK: { // Unlink
    function_context->func.free_local_context_func = free_unlink_local_context;
    function_context->func.local_context = 0;
    allocate_unlink_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_SINK
  case NN_FUNCTION_SINK: { // Sink
    function_context->func.free_local_context_func = free_sink_local_context;
    nn_function_sink_t *f = (nn_function_sink_t *)function;
    sink_local_context_t *ctx = rt_malloc_func(sizeof(sink_local_context_t));
    ctx->one_input_grad = f->one_input_grad;
    function_context->func.local_context = ctx;
    allocate_sink_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_NMSDETECTION2D
  case NN_FUNCTION_NMS_DETECTION2D: { // NmsDetection2d
    function_context->func.free_local_context_func =
        free_nms_detection2d_local_context;
    nn_function_nms_detection2d_t *f =
        (nn_function_nms_detection2d_t *)function;
    nms_detection2d_local_context_t *ctx =
        rt_malloc_func(sizeof(nms_detection2d_local_context_t));
    ctx->thresh = f->thresh;
    ctx->nms = f->nms;
    ctx->nms_per_class = f->nms_per_class;
    function_context->func.local_context = ctx;
    allocate_nms_detection2d_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_MAXPOOLINGBACKWARD
  case NN_FUNCTION_MAX_POOLING_BACKWARD: { // MaxPoolingBackward
    function_context->func.free_local_context_func =
        free_max_pooling_backward_local_context;
    nn_function_max_pooling_backward_t *f =
        (nn_function_max_pooling_backward_t *)function;
    max_pooling_backward_local_context_t *ctx =
        rt_malloc_func(sizeof(max_pooling_backward_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->channel_last = f->channel_last;
    function_context->func.local_context = ctx;
    allocate_max_pooling_backward_local_context(&function_context->func);
  } break;
#endif

#ifdef CONFIG_PATCHCORRELATION
  case NN_FUNCTION_PATCH_CORRELATION: { // PatchCorrelation
    function_context->func.free_local_context_func =
        free_patch_correlation_local_context;
    nn_function_patch_correlation_t *f =
        (nn_function_patch_correlation_t *)function;
    patch_correlation_local_context_t *ctx =
        rt_malloc_func(sizeof(patch_correlation_local_context_t));
    ctx->patch = create_rt_list_from_nn_list(n, f->patch);
    ctx->shift = create_rt_list_from_nn_list(n, f->shift);
    ctx->patch_step = create_rt_list_from_nn_list(n, f->patch_step);
    ctx->shift_step = create_rt_list_from_nn_list(n, f->shift_step);
    ctx->padding = create_rt_list_from_nn_list(n, f->padding);
    function_context->func.local_context = ctx;
    allocate_patch_correlation_local_context(&function_context->func);
  } break;
#endif

  default:
    function_context->func.local_context = 0;
  }
}
