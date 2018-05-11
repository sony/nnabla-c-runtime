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

#include <nnablart/functions.h>
#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "runtime_internal.h"

void allocate_function_context(nn_network_t *n, nn_function_t *function,
                               rt_function_context_t *function_context) {
  switch (function_context->type) {
  case NN_FUNCTION_AFFINE: { // Affine
    function_context->func.exec_func = exec_affine;
    function_context->func.free_local_context_func = free_affine_local_context;
    nn_function_affine_t *f = (nn_function_affine_t *)function;
    affine_local_context_t *ctx = malloc(sizeof(affine_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_affine_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CONVOLUTION: { // Convolution
    function_context->func.exec_func = exec_convolution;
    function_context->func.free_local_context_func =
        free_convolution_local_context;
    nn_function_convolution_t *f = (nn_function_convolution_t *)function;
    convolution_local_context_t *ctx =
        malloc(sizeof(convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    function_context->func.local_context = ctx;
    allocate_convolution_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    function_context->func.exec_func = exec_depthwise_convolution;
    function_context->func.free_local_context_func =
        free_depthwise_convolution_local_context;
    nn_function_depthwise_convolution_t *f =
        (nn_function_depthwise_convolution_t *)function;
    depthwise_convolution_local_context_t *ctx =
        malloc(sizeof(depthwise_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->multiplier = f->multiplier;
    function_context->func.local_context = ctx;
    allocate_depthwise_convolution_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    function_context->func.exec_func = exec_deconvolution;
    function_context->func.free_local_context_func =
        free_deconvolution_local_context;
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)function;
    deconvolution_local_context_t *ctx =
        malloc(sizeof(deconvolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    function_context->func.local_context = ctx;
    allocate_deconvolution_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_DEPTHWISE_DECONVOLUTION: { // DepthwiseDeconvolution
    function_context->func.exec_func = exec_depthwise_deconvolution;
    function_context->func.free_local_context_func =
        free_depthwise_deconvolution_local_context;
    nn_function_depthwise_deconvolution_t *f =
        (nn_function_depthwise_deconvolution_t *)function;
    depthwise_deconvolution_local_context_t *ctx =
        malloc(sizeof(depthwise_deconvolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->divisor = f->divisor;
    function_context->func.local_context = ctx;
    allocate_depthwise_deconvolution_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    function_context->func.exec_func = exec_max_pooling;
    function_context->func.free_local_context_func =
        free_max_pooling_local_context;
    nn_function_max_pooling_t *f = (nn_function_max_pooling_t *)function;
    max_pooling_local_context_t *ctx =
        malloc(sizeof(max_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    function_context->func.local_context = ctx;
    allocate_max_pooling_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    function_context->func.exec_func = exec_average_pooling;
    function_context->func.free_local_context_func =
        free_average_pooling_local_context;
    nn_function_average_pooling_t *f =
        (nn_function_average_pooling_t *)function;
    average_pooling_local_context_t *ctx =
        malloc(sizeof(average_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->including_pad = f->including_pad;
    function_context->func.local_context = ctx;
    allocate_average_pooling_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_GLOBAL_AVERAGE_POOLING: { // GlobalAveragePooling
    function_context->func.exec_func = exec_global_average_pooling;
    function_context->func.free_local_context_func =
        free_global_average_pooling_local_context;
    function_context->func.local_context = 0;
    allocate_global_average_pooling_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    function_context->func.exec_func = exec_sum_pooling;
    function_context->func.free_local_context_func =
        free_sum_pooling_local_context;
    nn_function_sum_pooling_t *f = (nn_function_sum_pooling_t *)function;
    sum_pooling_local_context_t *ctx =
        malloc(sizeof(sum_pooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->ignore_border = f->ignore_border;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    function_context->func.local_context = ctx;
    allocate_sum_pooling_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_UNPOOLING: { // Unpooling
    function_context->func.exec_func = exec_unpooling;
    function_context->func.free_local_context_func =
        free_unpooling_local_context;
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)function;
    unpooling_local_context_t *ctx = malloc(sizeof(unpooling_local_context_t));
    ctx->kernel = create_rt_list_from_nn_list(n, f->kernel);
    function_context->func.local_context = ctx;
    allocate_unpooling_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_EMBED: { // Embed
    function_context->func.exec_func = exec_embed;
    function_context->func.free_local_context_func = free_embed_local_context;
    function_context->func.local_context = 0;
    allocate_embed_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SIGMOID: { // Sigmoid
    function_context->func.exec_func = exec_sigmoid;
    function_context->func.free_local_context_func = free_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_sigmoid_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SWISH: { // Swish
    function_context->func.exec_func = exec_swish;
    function_context->func.free_local_context_func = free_swish_local_context;
    function_context->func.local_context = 0;
    allocate_swish_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_TANH: { // Tanh
    function_context->func.exec_func = exec_tanh;
    function_context->func.free_local_context_func = free_tanh_local_context;
    function_context->func.local_context = 0;
    allocate_tanh_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RELU: { // ReLU
    function_context->func.exec_func = exec_relu;
    function_context->func.free_local_context_func = free_relu_local_context;
    nn_function_relu_t *f = (nn_function_relu_t *)function;
    relu_local_context_t *ctx = malloc(sizeof(relu_local_context_t));
    ctx->inplace = f->inplace;
    function_context->func.local_context = ctx;
    allocate_relu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    function_context->func.exec_func = exec_leaky_relu;
    function_context->func.free_local_context_func =
        free_leaky_relu_local_context;
    nn_function_leaky_relu_t *f = (nn_function_leaky_relu_t *)function;
    leaky_relu_local_context_t *ctx =
        malloc(sizeof(leaky_relu_local_context_t));
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_leaky_relu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SOFTMAX: { // Softmax
    function_context->func.exec_func = exec_softmax;
    function_context->func.free_local_context_func = free_softmax_local_context;
    nn_function_softmax_t *f = (nn_function_softmax_t *)function;
    softmax_local_context_t *ctx = malloc(sizeof(softmax_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_softmax_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ELU: { // ELU
    function_context->func.exec_func = exec_elu;
    function_context->func.free_local_context_func = free_elu_local_context;
    nn_function_elu_t *f = (nn_function_elu_t *)function;
    elu_local_context_t *ctx = malloc(sizeof(elu_local_context_t));
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_elu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SELU: { // SELU
    function_context->func.exec_func = exec_selu;
    function_context->func.free_local_context_func = free_selu_local_context;
    nn_function_selu_t *f = (nn_function_selu_t *)function;
    selu_local_context_t *ctx = malloc(sizeof(selu_local_context_t));
    ctx->scale = f->scale;
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_selu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CRELU: { // CReLU
    function_context->func.exec_func = exec_crelu;
    function_context->func.free_local_context_func = free_crelu_local_context;
    nn_function_crelu_t *f = (nn_function_crelu_t *)function;
    crelu_local_context_t *ctx = malloc(sizeof(crelu_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_crelu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CELU: { // CELU
    function_context->func.exec_func = exec_celu;
    function_context->func.free_local_context_func = free_celu_local_context;
    nn_function_celu_t *f = (nn_function_celu_t *)function;
    celu_local_context_t *ctx = malloc(sizeof(celu_local_context_t));
    ctx->alpha = f->alpha;
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_celu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_PRELU: { // PReLU
    function_context->func.exec_func = exec_prelu;
    function_context->func.free_local_context_func = free_prelu_local_context;
    nn_function_prelu_t *f = (nn_function_prelu_t *)function;
    prelu_local_context_t *ctx = malloc(sizeof(prelu_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_prelu_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    function_context->func.exec_func = exec_batch_normalization;
    function_context->func.free_local_context_func =
        free_batch_normalization_local_context;
    nn_function_batch_normalization_t *f =
        (nn_function_batch_normalization_t *)function;
    batch_normalization_local_context_t *ctx =
        malloc(sizeof(batch_normalization_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->decay_rate = f->decay_rate;
    ctx->eps = f->eps;
    ctx->batch_stat = f->batch_stat;
    function_context->func.local_context = ctx;
    allocate_batch_normalization_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    function_context->func.exec_func = exec_mean_subtraction;
    function_context->func.free_local_context_func =
        free_mean_subtraction_local_context;
    nn_function_mean_subtraction_t *f =
        (nn_function_mean_subtraction_t *)function;
    mean_subtraction_local_context_t *ctx =
        malloc(sizeof(mean_subtraction_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->update_running_mean = f->update_running_mean;
    function_context->func.local_context = ctx;
    allocate_mean_subtraction_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SUM: { // Sum
    function_context->func.exec_func = exec_sum;
    function_context->func.free_local_context_func = free_sum_local_context;
    nn_function_sum_t *f = (nn_function_sum_t *)function;
    sum_local_context_t *ctx = malloc(sizeof(sum_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_sum_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MEAN: { // Mean
    function_context->func.exec_func = exec_mean;
    function_context->func.free_local_context_func = free_mean_local_context;
    nn_function_mean_t *f = (nn_function_mean_t *)function;
    mean_local_context_t *ctx = malloc(sizeof(mean_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_mean_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MAX: { // Max
    function_context->func.exec_func = exec_max;
    function_context->func.free_local_context_func = free_max_local_context;
    nn_function_max_t *f = (nn_function_max_t *)function;
    max_local_context_t *ctx = malloc(sizeof(max_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_max_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MIN: { // Min
    function_context->func.exec_func = exec_min;
    function_context->func.free_local_context_func = free_min_local_context;
    nn_function_min_t *f = (nn_function_min_t *)function;
    min_local_context_t *ctx = malloc(sizeof(min_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_min_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_PROD: { // Prod
    function_context->func.exec_func = exec_prod;
    function_context->func.free_local_context_func = free_prod_local_context;
    nn_function_prod_t *f = (nn_function_prod_t *)function;
    prod_local_context_t *ctx = malloc(sizeof(prod_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->keep_dims = f->keep_dims;
    function_context->func.local_context = ctx;
    allocate_prod_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
    function_context->func.exec_func = exec_reduce_sum;
    function_context->func.free_local_context_func =
        free_reduce_sum_local_context;
    function_context->func.local_context = 0;
    allocate_reduce_sum_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
    function_context->func.exec_func = exec_reduce_mean;
    function_context->func.free_local_context_func =
        free_reduce_mean_local_context;
    function_context->func.local_context = 0;
    allocate_reduce_mean_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ADD2: { // Add2
    function_context->func.exec_func = exec_add2;
    function_context->func.free_local_context_func = free_add2_local_context;
    nn_function_add2_t *f = (nn_function_add2_t *)function;
    add2_local_context_t *ctx = malloc(sizeof(add2_local_context_t));
    ctx->inplace = f->inplace;
    function_context->func.local_context = ctx;
    allocate_add2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    function_context->func.exec_func = exec_bc_add2;
    function_context->func.free_local_context_func = free_bc_add2_local_context;
    function_context->func.local_context = 0;
    allocate_bc_add2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SUB2: { // Sub2
    function_context->func.exec_func = exec_sub2;
    function_context->func.free_local_context_func = free_sub2_local_context;
    function_context->func.local_context = 0;
    allocate_sub2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MUL2: { // Mul2
    function_context->func.exec_func = exec_mul2;
    function_context->func.free_local_context_func = free_mul2_local_context;
    function_context->func.local_context = 0;
    allocate_mul2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_DIV2: { // Div2
    function_context->func.exec_func = exec_div2;
    function_context->func.free_local_context_func = free_div2_local_context;
    function_context->func.local_context = 0;
    allocate_div2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_POW2: { // Pow2
    function_context->func.exec_func = exec_pow2;
    function_context->func.free_local_context_func = free_pow2_local_context;
    function_context->func.local_context = 0;
    allocate_pow2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    function_context->func.exec_func = exec_add_scalar;
    function_context->func.free_local_context_func =
        free_add_scalar_local_context;
    nn_function_add_scalar_t *f = (nn_function_add_scalar_t *)function;
    add_scalar_local_context_t *ctx =
        malloc(sizeof(add_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_add_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    function_context->func.exec_func = exec_mul_scalar;
    function_context->func.free_local_context_func =
        free_mul_scalar_local_context;
    nn_function_mul_scalar_t *f = (nn_function_mul_scalar_t *)function;
    mul_scalar_local_context_t *ctx =
        malloc(sizeof(mul_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_mul_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    function_context->func.exec_func = exec_pow_scalar;
    function_context->func.free_local_context_func =
        free_pow_scalar_local_context;
    nn_function_pow_scalar_t *f = (nn_function_pow_scalar_t *)function;
    pow_scalar_local_context_t *ctx =
        malloc(sizeof(pow_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_pow_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    function_context->func.exec_func = exec_r_sub_scalar;
    function_context->func.free_local_context_func =
        free_r_sub_scalar_local_context;
    nn_function_r_sub_scalar_t *f = (nn_function_r_sub_scalar_t *)function;
    r_sub_scalar_local_context_t *ctx =
        malloc(sizeof(r_sub_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_r_sub_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    function_context->func.exec_func = exec_r_div_scalar;
    function_context->func.free_local_context_func =
        free_r_div_scalar_local_context;
    nn_function_r_div_scalar_t *f = (nn_function_r_div_scalar_t *)function;
    r_div_scalar_local_context_t *ctx =
        malloc(sizeof(r_div_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_r_div_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    function_context->func.exec_func = exec_r_pow_scalar;
    function_context->func.free_local_context_func =
        free_r_pow_scalar_local_context;
    nn_function_r_pow_scalar_t *f = (nn_function_r_pow_scalar_t *)function;
    r_pow_scalar_local_context_t *ctx =
        malloc(sizeof(r_pow_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_r_pow_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SIGN: { // Sign
    function_context->func.exec_func = exec_sign;
    function_context->func.free_local_context_func = free_sign_local_context;
    nn_function_sign_t *f = (nn_function_sign_t *)function;
    sign_local_context_t *ctx = malloc(sizeof(sign_local_context_t));
    ctx->alpha = f->alpha;
    function_context->func.local_context = ctx;
    allocate_sign_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MINIMUM2: { // Minimum2
    function_context->func.exec_func = exec_minimum2;
    function_context->func.free_local_context_func =
        free_minimum2_local_context;
    function_context->func.local_context = 0;
    allocate_minimum2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MAXIMUM2: { // Maximum2
    function_context->func.exec_func = exec_maximum2;
    function_context->func.free_local_context_func =
        free_maximum2_local_context;
    function_context->func.local_context = 0;
    allocate_maximum2_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    function_context->func.exec_func = exec_minimum_scalar;
    function_context->func.free_local_context_func =
        free_minimum_scalar_local_context;
    nn_function_minimum_scalar_t *f = (nn_function_minimum_scalar_t *)function;
    minimum_scalar_local_context_t *ctx =
        malloc(sizeof(minimum_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_minimum_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    function_context->func.exec_func = exec_maximum_scalar;
    function_context->func.free_local_context_func =
        free_maximum_scalar_local_context;
    nn_function_maximum_scalar_t *f = (nn_function_maximum_scalar_t *)function;
    maximum_scalar_local_context_t *ctx =
        malloc(sizeof(maximum_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_maximum_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_AND: { // LogicalAnd
    function_context->func.exec_func = exec_logical_and;
    function_context->func.free_local_context_func =
        free_logical_and_local_context;
    function_context->func.local_context = 0;
    allocate_logical_and_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_OR: { // LogicalOr
    function_context->func.exec_func = exec_logical_or;
    function_context->func.free_local_context_func =
        free_logical_or_local_context;
    function_context->func.local_context = 0;
    allocate_logical_or_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_XOR: { // LogicalXor
    function_context->func.exec_func = exec_logical_xor;
    function_context->func.free_local_context_func =
        free_logical_xor_local_context;
    function_context->func.local_context = 0;
    allocate_logical_xor_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_EQUAL: { // Equal
    function_context->func.exec_func = exec_equal;
    function_context->func.free_local_context_func = free_equal_local_context;
    function_context->func.local_context = 0;
    allocate_equal_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_NOT_EQUAL: { // NotEqual
    function_context->func.exec_func = exec_not_equal;
    function_context->func.free_local_context_func =
        free_not_equal_local_context;
    function_context->func.local_context = 0;
    allocate_not_equal_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_GREATER_EQUAL: { // GreaterEqual
    function_context->func.exec_func = exec_greater_equal;
    function_context->func.free_local_context_func =
        free_greater_equal_local_context;
    function_context->func.local_context = 0;
    allocate_greater_equal_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_GREATER: { // Greater
    function_context->func.exec_func = exec_greater;
    function_context->func.free_local_context_func = free_greater_local_context;
    function_context->func.local_context = 0;
    allocate_greater_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LESS_EQUAL: { // LessEqual
    function_context->func.exec_func = exec_less_equal;
    function_context->func.free_local_context_func =
        free_less_equal_local_context;
    function_context->func.local_context = 0;
    allocate_less_equal_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LESS: { // Less
    function_context->func.exec_func = exec_less;
    function_context->func.free_local_context_func = free_less_local_context;
    function_context->func.local_context = 0;
    allocate_less_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    function_context->func.exec_func = exec_logical_and_scalar;
    function_context->func.free_local_context_func =
        free_logical_and_scalar_local_context;
    nn_function_logical_and_scalar_t *f =
        (nn_function_logical_and_scalar_t *)function;
    logical_and_scalar_local_context_t *ctx =
        malloc(sizeof(logical_and_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_logical_and_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    function_context->func.exec_func = exec_logical_or_scalar;
    function_context->func.free_local_context_func =
        free_logical_or_scalar_local_context;
    nn_function_logical_or_scalar_t *f =
        (nn_function_logical_or_scalar_t *)function;
    logical_or_scalar_local_context_t *ctx =
        malloc(sizeof(logical_or_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_logical_or_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    function_context->func.exec_func = exec_logical_xor_scalar;
    function_context->func.free_local_context_func =
        free_logical_xor_scalar_local_context;
    nn_function_logical_xor_scalar_t *f =
        (nn_function_logical_xor_scalar_t *)function;
    logical_xor_scalar_local_context_t *ctx =
        malloc(sizeof(logical_xor_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_logical_xor_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    function_context->func.exec_func = exec_equal_scalar;
    function_context->func.free_local_context_func =
        free_equal_scalar_local_context;
    nn_function_equal_scalar_t *f = (nn_function_equal_scalar_t *)function;
    equal_scalar_local_context_t *ctx =
        malloc(sizeof(equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_equal_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    function_context->func.exec_func = exec_not_equal_scalar;
    function_context->func.free_local_context_func =
        free_not_equal_scalar_local_context;
    nn_function_not_equal_scalar_t *f =
        (nn_function_not_equal_scalar_t *)function;
    not_equal_scalar_local_context_t *ctx =
        malloc(sizeof(not_equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_not_equal_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    function_context->func.exec_func = exec_greater_equal_scalar;
    function_context->func.free_local_context_func =
        free_greater_equal_scalar_local_context;
    nn_function_greater_equal_scalar_t *f =
        (nn_function_greater_equal_scalar_t *)function;
    greater_equal_scalar_local_context_t *ctx =
        malloc(sizeof(greater_equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_greater_equal_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    function_context->func.exec_func = exec_greater_scalar;
    function_context->func.free_local_context_func =
        free_greater_scalar_local_context;
    nn_function_greater_scalar_t *f = (nn_function_greater_scalar_t *)function;
    greater_scalar_local_context_t *ctx =
        malloc(sizeof(greater_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_greater_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    function_context->func.exec_func = exec_less_equal_scalar;
    function_context->func.free_local_context_func =
        free_less_equal_scalar_local_context;
    nn_function_less_equal_scalar_t *f =
        (nn_function_less_equal_scalar_t *)function;
    less_equal_scalar_local_context_t *ctx =
        malloc(sizeof(less_equal_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_less_equal_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    function_context->func.exec_func = exec_less_scalar;
    function_context->func.free_local_context_func =
        free_less_scalar_local_context;
    nn_function_less_scalar_t *f = (nn_function_less_scalar_t *)function;
    less_scalar_local_context_t *ctx =
        malloc(sizeof(less_scalar_local_context_t));
    ctx->val = f->val;
    function_context->func.local_context = ctx;
    allocate_less_scalar_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOGICAL_NOT: { // LogicalNot
    function_context->func.exec_func = exec_logical_not;
    function_context->func.free_local_context_func =
        free_logical_not_local_context;
    function_context->func.local_context = 0;
    allocate_logical_not_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CONSTANT: { // Constant
    function_context->func.exec_func = exec_constant;
    function_context->func.free_local_context_func =
        free_constant_local_context;
    nn_function_constant_t *f = (nn_function_constant_t *)function;
    constant_local_context_t *ctx = malloc(sizeof(constant_local_context_t));
    ctx->val = f->val;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_constant_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ABS: { // Abs
    function_context->func.exec_func = exec_abs;
    function_context->func.free_local_context_func = free_abs_local_context;
    function_context->func.local_context = 0;
    allocate_abs_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_EXP: { // Exp
    function_context->func.exec_func = exec_exp;
    function_context->func.free_local_context_func = free_exp_local_context;
    function_context->func.local_context = 0;
    allocate_exp_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_LOG: { // Log
    function_context->func.exec_func = exec_log;
    function_context->func.free_local_context_func = free_log_local_context;
    function_context->func.local_context = 0;
    allocate_log_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_IDENTITY: { // Identity
    function_context->func.exec_func = exec_identity;
    function_context->func.free_local_context_func =
        free_identity_local_context;
    function_context->func.local_context = 0;
    allocate_identity_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    function_context->func.exec_func = exec_batch_matmul;
    function_context->func.free_local_context_func =
        free_batch_matmul_local_context;
    nn_function_batch_matmul_t *f = (nn_function_batch_matmul_t *)function;
    batch_matmul_local_context_t *ctx =
        malloc(sizeof(batch_matmul_local_context_t));
    ctx->transpose_a = f->transpose_a;
    ctx->transpose_b = f->transpose_b;
    function_context->func.local_context = ctx;
    allocate_batch_matmul_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ROUND: { // Round
    function_context->func.exec_func = exec_round;
    function_context->func.free_local_context_func = free_round_local_context;
    function_context->func.local_context = 0;
    allocate_round_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CONCATENATE: { // Concatenate
    function_context->func.exec_func = exec_concatenate;
    function_context->func.free_local_context_func =
        free_concatenate_local_context;
    nn_function_concatenate_t *f = (nn_function_concatenate_t *)function;
    concatenate_local_context_t *ctx =
        malloc(sizeof(concatenate_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_concatenate_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SPLIT: { // Split
    function_context->func.exec_func = exec_split;
    function_context->func.free_local_context_func = free_split_local_context;
    nn_function_split_t *f = (nn_function_split_t *)function;
    split_local_context_t *ctx = malloc(sizeof(split_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_split_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_STACK: { // Stack
    function_context->func.exec_func = exec_stack;
    function_context->func.free_local_context_func = free_stack_local_context;
    nn_function_stack_t *f = (nn_function_stack_t *)function;
    stack_local_context_t *ctx = malloc(sizeof(stack_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_stack_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SLICE: { // Slice
    function_context->func.exec_func = exec_slice;
    function_context->func.free_local_context_func = free_slice_local_context;
    nn_function_slice_t *f = (nn_function_slice_t *)function;
    slice_local_context_t *ctx = malloc(sizeof(slice_local_context_t));
    ctx->start = create_rt_list_from_nn_list(n, f->start);
    ctx->stop = create_rt_list_from_nn_list(n, f->stop);
    ctx->step = create_rt_list_from_nn_list(n, f->step);
    function_context->func.local_context = ctx;
    allocate_slice_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_TRANSPOSE: { // Transpose
    function_context->func.exec_func = exec_transpose;
    function_context->func.free_local_context_func =
        free_transpose_local_context;
    nn_function_transpose_t *f = (nn_function_transpose_t *)function;
    transpose_local_context_t *ctx = malloc(sizeof(transpose_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    function_context->func.local_context = ctx;
    allocate_transpose_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BROADCAST: { // Broadcast
    function_context->func.exec_func = exec_broadcast;
    function_context->func.free_local_context_func =
        free_broadcast_local_context;
    nn_function_broadcast_t *f = (nn_function_broadcast_t *)function;
    broadcast_local_context_t *ctx = malloc(sizeof(broadcast_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_broadcast_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ONE_HOT: { // OneHot
    function_context->func.exec_func = exec_one_hot;
    function_context->func.free_local_context_func = free_one_hot_local_context;
    nn_function_one_hot_t *f = (nn_function_one_hot_t *)function;
    one_hot_local_context_t *ctx = malloc(sizeof(one_hot_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_one_hot_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_FLIP: { // Flip
    function_context->func.exec_func = exec_flip;
    function_context->func.free_local_context_func = free_flip_local_context;
    nn_function_flip_t *f = (nn_function_flip_t *)function;
    flip_local_context_t *ctx = malloc(sizeof(flip_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    function_context->func.local_context = ctx;
    allocate_flip_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SHIFT: { // Shift
    function_context->func.exec_func = exec_shift;
    function_context->func.free_local_context_func = free_shift_local_context;
    nn_function_shift_t *f = (nn_function_shift_t *)function;
    shift_local_context_t *ctx = malloc(sizeof(shift_local_context_t));
    ctx->shifts = create_rt_list_from_nn_list(n, f->shifts);
    ctx->border_mode = f->border_mode;
    function_context->func.local_context = ctx;
    allocate_shift_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RESHAPE: { // Reshape
    function_context->func.exec_func = exec_reshape;
    function_context->func.free_local_context_func = free_reshape_local_context;
    nn_function_reshape_t *f = (nn_function_reshape_t *)function;
    reshape_local_context_t *ctx = malloc(sizeof(reshape_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    function_context->func.local_context = ctx;
    allocate_reshape_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
    function_context->func.exec_func = exec_matrix_diag;
    function_context->func.free_local_context_func =
        free_matrix_diag_local_context;
    function_context->func.local_context = 0;
    allocate_matrix_diag_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
    function_context->func.exec_func = exec_matrix_diag_part;
    function_context->func.free_local_context_func =
        free_matrix_diag_part_local_context;
    function_context->func.local_context = 0;
    allocate_matrix_diag_part_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_DROPOUT: { // Dropout
    function_context->func.exec_func = exec_dropout;
    function_context->func.free_local_context_func = free_dropout_local_context;
    nn_function_dropout_t *f = (nn_function_dropout_t *)function;
    dropout_local_context_t *ctx = malloc(sizeof(dropout_local_context_t));
    ctx->p = f->p;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_dropout_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_TOP_K_DATA: { // TopKData
    function_context->func.exec_func = exec_top_k_data;
    function_context->func.free_local_context_func =
        free_top_k_data_local_context;
    nn_function_top_k_data_t *f = (nn_function_top_k_data_t *)function;
    top_k_data_local_context_t *ctx =
        malloc(sizeof(top_k_data_local_context_t));
    ctx->k = f->k;
    ctx->abs = f->abs;
    ctx->reduce = f->reduce;
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_top_k_data_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_TOP_K_GRAD: { // TopKGrad
    function_context->func.exec_func = exec_top_k_grad;
    function_context->func.free_local_context_func =
        free_top_k_grad_local_context;
    nn_function_top_k_grad_t *f = (nn_function_top_k_grad_t *)function;
    top_k_grad_local_context_t *ctx =
        malloc(sizeof(top_k_grad_local_context_t));
    ctx->k = f->k;
    ctx->abs = f->abs;
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_top_k_grad_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RAND: { // Rand
    function_context->func.exec_func = exec_rand;
    function_context->func.free_local_context_func = free_rand_local_context;
    nn_function_rand_t *f = (nn_function_rand_t *)function;
    rand_local_context_t *ctx = malloc(sizeof(rand_local_context_t));
    ctx->low = f->low;
    ctx->high = f->high;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_rand_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RANDINT: { // Randint
    function_context->func.exec_func = exec_randint;
    function_context->func.free_local_context_func = free_randint_local_context;
    nn_function_randint_t *f = (nn_function_randint_t *)function;
    randint_local_context_t *ctx = malloc(sizeof(randint_local_context_t));
    ctx->low = f->low;
    ctx->high = f->high;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_randint_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RANDN: { // Randn
    function_context->func.exec_func = exec_randn;
    function_context->func.free_local_context_func = free_randn_local_context;
    nn_function_randn_t *f = (nn_function_randn_t *)function;
    randn_local_context_t *ctx = malloc(sizeof(randn_local_context_t));
    ctx->mu = f->mu;
    ctx->sigma = f->sigma;
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_randn_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    function_context->func.exec_func = exec_random_crop;
    function_context->func.free_local_context_func =
        free_random_crop_local_context;
    nn_function_random_crop_t *f = (nn_function_random_crop_t *)function;
    random_crop_local_context_t *ctx =
        malloc(sizeof(random_crop_local_context_t));
    ctx->shape = create_rt_list_from_nn_list(n, f->shape);
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_crop_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    function_context->func.exec_func = exec_random_flip;
    function_context->func.free_local_context_func =
        free_random_flip_local_context;
    nn_function_random_flip_t *f = (nn_function_random_flip_t *)function;
    random_flip_local_context_t *ctx =
        malloc(sizeof(random_flip_local_context_t));
    ctx->axes = create_rt_list_from_nn_list(n, f->axes);
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_flip_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    function_context->func.exec_func = exec_random_shift;
    function_context->func.free_local_context_func =
        free_random_shift_local_context;
    nn_function_random_shift_t *f = (nn_function_random_shift_t *)function;
    random_shift_local_context_t *ctx =
        malloc(sizeof(random_shift_local_context_t));
    ctx->shifts = create_rt_list_from_nn_list(n, f->shifts);
    ctx->border_mode = f->border_mode;
    ctx->base_axis = f->base_axis;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_random_shift_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    function_context->func.exec_func = exec_image_augmentation;
    function_context->func.free_local_context_func =
        free_image_augmentation_local_context;
    nn_function_image_augmentation_t *f =
        (nn_function_image_augmentation_t *)function;
    image_augmentation_local_context_t *ctx =
        malloc(sizeof(image_augmentation_local_context_t));
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

  case NN_FUNCTION_SIGMOID_CROSS_ENTROPY: { // SigmoidCrossEntropy
    function_context->func.exec_func = exec_sigmoid_cross_entropy;
    function_context->func.free_local_context_func =
        free_sigmoid_cross_entropy_local_context;
    function_context->func.local_context = 0;
    allocate_sigmoid_cross_entropy_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_CROSS_ENTROPY: { // BinaryCrossEntropy
    function_context->func.exec_func = exec_binary_cross_entropy;
    function_context->func.free_local_context_func =
        free_binary_cross_entropy_local_context;
    function_context->func.local_context = 0;
    allocate_binary_cross_entropy_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    function_context->func.exec_func = exec_softmax_cross_entropy;
    function_context->func.free_local_context_func =
        free_softmax_cross_entropy_local_context;
    nn_function_softmax_cross_entropy_t *f =
        (nn_function_softmax_cross_entropy_t *)function;
    softmax_cross_entropy_local_context_t *ctx =
        malloc(sizeof(softmax_cross_entropy_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_softmax_cross_entropy_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    function_context->func.exec_func = exec_categorical_cross_entropy;
    function_context->func.free_local_context_func =
        free_categorical_cross_entropy_local_context;
    nn_function_categorical_cross_entropy_t *f =
        (nn_function_categorical_cross_entropy_t *)function;
    categorical_cross_entropy_local_context_t *ctx =
        malloc(sizeof(categorical_cross_entropy_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_categorical_cross_entropy_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SQUARED_ERROR: { // SquaredError
    function_context->func.exec_func = exec_squared_error;
    function_context->func.free_local_context_func =
        free_squared_error_local_context;
    function_context->func.local_context = 0;
    allocate_squared_error_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_ABSOLUTE_ERROR: { // AbsoluteError
    function_context->func.exec_func = exec_absolute_error;
    function_context->func.free_local_context_func =
        free_absolute_error_local_context;
    function_context->func.local_context = 0;
    allocate_absolute_error_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    function_context->func.exec_func = exec_huber_loss;
    function_context->func.free_local_context_func =
        free_huber_loss_local_context;
    nn_function_huber_loss_t *f = (nn_function_huber_loss_t *)function;
    huber_loss_local_context_t *ctx =
        malloc(sizeof(huber_loss_local_context_t));
    ctx->delta = f->delta;
    function_context->func.local_context = ctx;
    allocate_huber_loss_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    function_context->func.exec_func = exec_epsilon_insensitive_loss;
    function_context->func.free_local_context_func =
        free_epsilon_insensitive_loss_local_context;
    nn_function_epsilon_insensitive_loss_t *f =
        (nn_function_epsilon_insensitive_loss_t *)function;
    epsilon_insensitive_loss_local_context_t *ctx =
        malloc(sizeof(epsilon_insensitive_loss_local_context_t));
    ctx->epsilon = f->epsilon;
    function_context->func.local_context = ctx;
    allocate_epsilon_insensitive_loss_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    function_context->func.exec_func = exec_kl_multinomial;
    function_context->func.free_local_context_func =
        free_kl_multinomial_local_context;
    nn_function_kl_multinomial_t *f = (nn_function_kl_multinomial_t *)function;
    kl_multinomial_local_context_t *ctx =
        malloc(sizeof(kl_multinomial_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_kl_multinomial_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_SIGMOID: { // BinarySigmoid
    function_context->func.exec_func = exec_binary_sigmoid;
    function_context->func.free_local_context_func =
        free_binary_sigmoid_local_context;
    function_context->func.local_context = 0;
    allocate_binary_sigmoid_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_TANH: { // BinaryTanh
    function_context->func.exec_func = exec_binary_tanh;
    function_context->func.free_local_context_func =
        free_binary_tanh_local_context;
    function_context->func.local_context = 0;
    allocate_binary_tanh_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    function_context->func.exec_func = exec_binary_connect_affine;
    function_context->func.free_local_context_func =
        free_binary_connect_affine_local_context;
    nn_function_binary_connect_affine_t *f =
        (nn_function_binary_connect_affine_t *)function;
    binary_connect_affine_local_context_t *ctx =
        malloc(sizeof(binary_connect_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_binary_connect_affine_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    function_context->func.exec_func = exec_binary_connect_convolution;
    function_context->func.free_local_context_func =
        free_binary_connect_convolution_local_context;
    nn_function_binary_connect_convolution_t *f =
        (nn_function_binary_connect_convolution_t *)function;
    binary_connect_convolution_local_context_t *ctx =
        malloc(sizeof(binary_connect_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    function_context->func.local_context = ctx;
    allocate_binary_connect_convolution_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    function_context->func.exec_func = exec_binary_weight_affine;
    function_context->func.free_local_context_func =
        free_binary_weight_affine_local_context;
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)function;
    binary_weight_affine_local_context_t *ctx =
        malloc(sizeof(binary_weight_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    function_context->func.local_context = ctx;
    allocate_binary_weight_affine_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    function_context->func.exec_func = exec_binary_weight_convolution;
    function_context->func.free_local_context_func =
        free_binary_weight_convolution_local_context;
    nn_function_binary_weight_convolution_t *f =
        (nn_function_binary_weight_convolution_t *)function;
    binary_weight_convolution_local_context_t *ctx =
        malloc(sizeof(binary_weight_convolution_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->pad = create_rt_list_from_nn_list(n, f->pad);
    ctx->stride = create_rt_list_from_nn_list(n, f->stride);
    ctx->dilation = create_rt_list_from_nn_list(n, f->dilation);
    ctx->group = f->group;
    function_context->func.local_context = ctx;
    allocate_binary_weight_convolution_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    function_context->func.exec_func = exec_inq_affine;
    function_context->func.free_local_context_func =
        free_inq_affine_local_context;
    nn_function_inq_affine_t *f = (nn_function_inq_affine_t *)function;
    inq_affine_local_context_t *ctx =
        malloc(sizeof(inq_affine_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->num_bits = f->num_bits;
    ctx->inq_iterations = create_rt_list_from_nn_list(n, f->inq_iterations);
    ctx->selection_algorithm = f->selection_algorithm;
    ctx->seed = f->seed;
    function_context->func.local_context = ctx;
    allocate_inq_affine_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    function_context->func.exec_func = exec_inq_convolution;
    function_context->func.free_local_context_func =
        free_inq_convolution_local_context;
    nn_function_inq_convolution_t *f =
        (nn_function_inq_convolution_t *)function;
    inq_convolution_local_context_t *ctx =
        malloc(sizeof(inq_convolution_local_context_t));
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

  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    function_context->func.exec_func = exec_fixed_point_quantize;
    function_context->func.free_local_context_func =
        free_fixed_point_quantize_local_context;
    nn_function_fixed_point_quantize_t *f =
        (nn_function_fixed_point_quantize_t *)function;
    fixed_point_quantize_local_context_t *ctx =
        malloc(sizeof(fixed_point_quantize_local_context_t));
    ctx->sign = f->sign;
    ctx->n = f->n;
    ctx->delta = f->delta;
    ctx->ste_fine_grained = f->ste_fine_grained;
    function_context->func.local_context = ctx;
    allocate_fixed_point_quantize_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    function_context->func.exec_func = exec_pow2_quantize;
    function_context->func.free_local_context_func =
        free_pow2_quantize_local_context;
    nn_function_pow2_quantize_t *f = (nn_function_pow2_quantize_t *)function;
    pow2_quantize_local_context_t *ctx =
        malloc(sizeof(pow2_quantize_local_context_t));
    ctx->sign = f->sign;
    ctx->with_zero = f->with_zero;
    ctx->n = f->n;
    ctx->m = f->m;
    ctx->ste_fine_grained = f->ste_fine_grained;
    function_context->func.local_context = ctx;
    allocate_pow2_quantize_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    function_context->func.exec_func = exec_top_n_error;
    function_context->func.free_local_context_func =
        free_top_n_error_local_context;
    nn_function_top_n_error_t *f = (nn_function_top_n_error_t *)function;
    top_n_error_local_context_t *ctx =
        malloc(sizeof(top_n_error_local_context_t));
    ctx->axis = f->axis;
    ctx->n = f->n;
    function_context->func.local_context = ctx;
    allocate_top_n_error_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_BINARY_ERROR: { // BinaryError
    function_context->func.exec_func = exec_binary_error;
    function_context->func.free_local_context_func =
        free_binary_error_local_context;
    function_context->func.local_context = 0;
    allocate_binary_error_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    function_context->func.exec_func = exec_confusion_matrix;
    function_context->func.free_local_context_func =
        free_confusion_matrix_local_context;
    nn_function_confusion_matrix_t *f =
        (nn_function_confusion_matrix_t *)function;
    confusion_matrix_local_context_t *ctx =
        malloc(sizeof(confusion_matrix_local_context_t));
    ctx->axis = f->axis;
    function_context->func.local_context = ctx;
    allocate_confusion_matrix_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    function_context->func.exec_func = exec_vat_noise;
    function_context->func.free_local_context_func =
        free_vat_noise_local_context;
    nn_function_vat_noise_t *f = (nn_function_vat_noise_t *)function;
    vat_noise_local_context_t *ctx = malloc(sizeof(vat_noise_local_context_t));
    ctx->base_axis = f->base_axis;
    ctx->eps = f->eps;
    function_context->func.local_context = ctx;
    allocate_vat_noise_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_UNLINK: { // Unlink
    function_context->func.exec_func = exec_unlink;
    function_context->func.free_local_context_func = free_unlink_local_context;
    function_context->func.local_context = 0;
    allocate_unlink_local_context(&function_context->func);
  } break;

  case NN_FUNCTION_SINK: { // Sink
    function_context->func.exec_func = exec_sink;
    function_context->func.free_local_context_func = free_sink_local_context;
    nn_function_sink_t *f = (nn_function_sink_t *)function;
    sink_local_context_t *ctx = malloc(sizeof(sink_local_context_t));
    ctx->one_input_grad = f->one_input_grad;
    function_context->func.local_context = ctx;
    allocate_sink_local_context(&function_context->func);
  } break;

  default:
    function_context->func.local_context = 0;
  }
}
