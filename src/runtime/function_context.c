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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <nnablart/functions.h>
#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "runtime_internal.h"

rt_function_context_t allocate_function_context(nn_network_t *n,
                                                rt_context_t *c,
                                                nn_function_t *function) {
  int i; // Iterator

  rt_function_context_t func;
  func.type = function->type;

  rt_list_t inputs = create_rt_list_from_nn_list(n, function->inputs);
  func.func.num_of_inputs = inputs.size;
  func.func.inputs = malloc(sizeof(rt_variable_t *) * inputs.size);
  if (func.func.inputs) {
    for (i = 0; i < inputs.size; i++) {
      int index = *(inputs.data + i);
      if (index < c->num_of_variables) {
        func.func.inputs[i] = &(c->variables[index]);
      } else {
        func.func.inputs[i] = 0;
      }
    }
  }

  rt_list_t outputs = create_rt_list_from_nn_list(n, function->outputs);
  func.func.num_of_outputs = outputs.size;
  func.func.outputs = malloc(sizeof(rt_variable_t *) * outputs.size);
  if (func.func.outputs) {
    for (i = 0; i < outputs.size; i++) {
      int index = *(outputs.data + i);
      if (index < c->num_of_variables) {
        func.func.outputs[i] = &(c->variables[index]);
      } else {
        func.func.outputs[i] = 0;
      }
    }
  }

  switch (function->type) {
  case NN_FUNCTION_AFFINE: { // Affine
    func.exec_func = exec_affine;
    nn_function_affine_t *f = (nn_function_affine_t *)function;
    affine_config_t *conf = malloc(sizeof(affine_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
    allocate_affine_config(&func.func);
  } break;

  case NN_FUNCTION_CONVOLUTION: { // Convolution
    func.exec_func = exec_convolution;
    nn_function_convolution_t *f = (nn_function_convolution_t *)function;
    convolution_config_t *conf = malloc(sizeof(convolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    func.func.config = conf;
    allocate_convolution_config(&func.func);
  } break;

  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    func.exec_func = exec_depthwise_convolution;
    nn_function_depthwise_convolution_t *f =
        (nn_function_depthwise_convolution_t *)function;
    depthwise_convolution_config_t *conf =
        malloc(sizeof(depthwise_convolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->multiplier = f->multiplier;
    func.func.config = conf;
    allocate_depthwise_convolution_config(&func.func);
  } break;

  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    func.exec_func = exec_deconvolution;
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)function;
    deconvolution_config_t *conf = malloc(sizeof(deconvolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    func.func.config = conf;
    allocate_deconvolution_config(&func.func);
  } break;

  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    func.exec_func = exec_max_pooling;
    nn_function_max_pooling_t *f = (nn_function_max_pooling_t *)function;
    max_pooling_config_t *conf = malloc(sizeof(max_pooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->ignore_border = f->ignore_border;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    func.func.config = conf;
    allocate_max_pooling_config(&func.func);
  } break;

  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    func.exec_func = exec_average_pooling;
    nn_function_average_pooling_t *f =
        (nn_function_average_pooling_t *)function;
    average_pooling_config_t *conf = malloc(sizeof(average_pooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->ignore_border = f->ignore_border;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->including_pad = f->including_pad;
    func.func.config = conf;
    allocate_average_pooling_config(&func.func);
  } break;

  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    func.exec_func = exec_sum_pooling;
    nn_function_sum_pooling_t *f = (nn_function_sum_pooling_t *)function;
    sum_pooling_config_t *conf = malloc(sizeof(sum_pooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->ignore_border = f->ignore_border;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    func.func.config = conf;
    allocate_sum_pooling_config(&func.func);
  } break;

  case NN_FUNCTION_UNPOOLING: { // Unpooling
    func.exec_func = exec_unpooling;
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)function;
    unpooling_config_t *conf = malloc(sizeof(unpooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    func.func.config = conf;
    allocate_unpooling_config(&func.func);
  } break;

  case NN_FUNCTION_EMBED: { // Embed
    func.exec_func = exec_embed;
    allocate_embed_config(&func.func);
  } break;

  case NN_FUNCTION_SIGMOID: { // Sigmoid
    func.exec_func = exec_sigmoid;
    allocate_sigmoid_config(&func.func);
  } break;

  case NN_FUNCTION_SWISH: { // Swish
    func.exec_func = exec_swish;
    allocate_swish_config(&func.func);
  } break;

  case NN_FUNCTION_TANH: { // Tanh
    func.exec_func = exec_tanh;
    allocate_tanh_config(&func.func);
  } break;

  case NN_FUNCTION_RELU: { // ReLU
    func.exec_func = exec_relu;
    nn_function_relu_t *f = (nn_function_relu_t *)function;
    relu_config_t *conf = malloc(sizeof(relu_config_t));
    conf->inplace = f->inplace;
    func.func.config = conf;
    allocate_relu_config(&func.func);
  } break;

  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    func.exec_func = exec_leaky_relu;
    nn_function_leaky_relu_t *f = (nn_function_leaky_relu_t *)function;
    leaky_relu_config_t *conf = malloc(sizeof(leaky_relu_config_t));
    conf->alpha = f->alpha;
    func.func.config = conf;
    allocate_leaky_relu_config(&func.func);
  } break;

  case NN_FUNCTION_SOFTMAX: { // Softmax
    func.exec_func = exec_softmax;
    nn_function_softmax_t *f = (nn_function_softmax_t *)function;
    softmax_config_t *conf = malloc(sizeof(softmax_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_softmax_config(&func.func);
  } break;

  case NN_FUNCTION_ELU: { // ELU
    func.exec_func = exec_elu;
    nn_function_elu_t *f = (nn_function_elu_t *)function;
    elu_config_t *conf = malloc(sizeof(elu_config_t));
    conf->alpha = f->alpha;
    func.func.config = conf;
    allocate_elu_config(&func.func);
  } break;

  case NN_FUNCTION_SELU: { // SELU
    func.exec_func = exec_selu;
    nn_function_selu_t *f = (nn_function_selu_t *)function;
    selu_config_t *conf = malloc(sizeof(selu_config_t));
    conf->scale = f->scale;
    conf->alpha = f->alpha;
    func.func.config = conf;
    allocate_selu_config(&func.func);
  } break;

  case NN_FUNCTION_CRELU: { // CReLU
    func.exec_func = exec_crelu;
    nn_function_crelu_t *f = (nn_function_crelu_t *)function;
    crelu_config_t *conf = malloc(sizeof(crelu_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_crelu_config(&func.func);
  } break;

  case NN_FUNCTION_CELU: { // CELU
    func.exec_func = exec_celu;
    nn_function_celu_t *f = (nn_function_celu_t *)function;
    celu_config_t *conf = malloc(sizeof(celu_config_t));
    conf->alpha = f->alpha;
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_celu_config(&func.func);
  } break;

  case NN_FUNCTION_PRELU: { // PReLU
    func.exec_func = exec_prelu;
    nn_function_prelu_t *f = (nn_function_prelu_t *)function;
    prelu_config_t *conf = malloc(sizeof(prelu_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
    allocate_prelu_config(&func.func);
  } break;

  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    func.exec_func = exec_batch_normalization;
    nn_function_batch_normalization_t *f =
        (nn_function_batch_normalization_t *)function;
    batch_normalization_config_t *conf =
        malloc(sizeof(batch_normalization_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->decay_rate = f->decay_rate;
    conf->eps = f->eps;
    conf->batch_stat = f->batch_stat;
    func.func.config = conf;
    allocate_batch_normalization_config(&func.func);
  } break;

  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    func.exec_func = exec_mean_subtraction;
    nn_function_mean_subtraction_t *f =
        (nn_function_mean_subtraction_t *)function;
    mean_subtraction_config_t *conf = malloc(sizeof(mean_subtraction_config_t));
    conf->base_axis = f->base_axis;
    conf->update_running_mean = f->update_running_mean;
    func.func.config = conf;
    allocate_mean_subtraction_config(&func.func);
  } break;

  case NN_FUNCTION_SUM: { // Sum
    func.exec_func = exec_sum;
    nn_function_sum_t *f = (nn_function_sum_t *)function;
    sum_config_t *conf = malloc(sizeof(sum_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
    allocate_sum_config(&func.func);
  } break;

  case NN_FUNCTION_MEAN: { // Mean
    func.exec_func = exec_mean;
    nn_function_mean_t *f = (nn_function_mean_t *)function;
    mean_config_t *conf = malloc(sizeof(mean_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
    allocate_mean_config(&func.func);
  } break;

  case NN_FUNCTION_MAX: { // Max
    func.exec_func = exec_max;
    nn_function_max_t *f = (nn_function_max_t *)function;
    max_config_t *conf = malloc(sizeof(max_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
    allocate_max_config(&func.func);
  } break;

  case NN_FUNCTION_MIN: { // Min
    func.exec_func = exec_min;
    nn_function_min_t *f = (nn_function_min_t *)function;
    min_config_t *conf = malloc(sizeof(min_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
    allocate_min_config(&func.func);
  } break;

  case NN_FUNCTION_PROD: { // Prod
    func.exec_func = exec_prod;
    nn_function_prod_t *f = (nn_function_prod_t *)function;
    prod_config_t *conf = malloc(sizeof(prod_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
    allocate_prod_config(&func.func);
  } break;

  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
    func.exec_func = exec_reduce_sum;
    allocate_reduce_sum_config(&func.func);
  } break;

  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
    func.exec_func = exec_reduce_mean;
    allocate_reduce_mean_config(&func.func);
  } break;

  case NN_FUNCTION_ADD2: { // Add2
    func.exec_func = exec_add2;
    nn_function_add2_t *f = (nn_function_add2_t *)function;
    add2_config_t *conf = malloc(sizeof(add2_config_t));
    conf->inplace = f->inplace;
    func.func.config = conf;
    allocate_add2_config(&func.func);
  } break;

  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    func.exec_func = exec_bc_add2;
    allocate_bc_add2_config(&func.func);
  } break;

  case NN_FUNCTION_SUB2: { // Sub2
    func.exec_func = exec_sub2;
    allocate_sub2_config(&func.func);
  } break;

  case NN_FUNCTION_MUL2: { // Mul2
    func.exec_func = exec_mul2;
    allocate_mul2_config(&func.func);
  } break;

  case NN_FUNCTION_DIV2: { // Div2
    func.exec_func = exec_div2;
    allocate_div2_config(&func.func);
  } break;

  case NN_FUNCTION_POW2: { // Pow2
    func.exec_func = exec_pow2;
    allocate_pow2_config(&func.func);
  } break;

  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    func.exec_func = exec_add_scalar;
    nn_function_add_scalar_t *f = (nn_function_add_scalar_t *)function;
    add_scalar_config_t *conf = malloc(sizeof(add_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_add_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    func.exec_func = exec_mul_scalar;
    nn_function_mul_scalar_t *f = (nn_function_mul_scalar_t *)function;
    mul_scalar_config_t *conf = malloc(sizeof(mul_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_mul_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    func.exec_func = exec_pow_scalar;
    nn_function_pow_scalar_t *f = (nn_function_pow_scalar_t *)function;
    pow_scalar_config_t *conf = malloc(sizeof(pow_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_pow_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    func.exec_func = exec_r_sub_scalar;
    nn_function_r_sub_scalar_t *f = (nn_function_r_sub_scalar_t *)function;
    r_sub_scalar_config_t *conf = malloc(sizeof(r_sub_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_r_sub_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    func.exec_func = exec_r_div_scalar;
    nn_function_r_div_scalar_t *f = (nn_function_r_div_scalar_t *)function;
    r_div_scalar_config_t *conf = malloc(sizeof(r_div_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_r_div_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    func.exec_func = exec_r_pow_scalar;
    nn_function_r_pow_scalar_t *f = (nn_function_r_pow_scalar_t *)function;
    r_pow_scalar_config_t *conf = malloc(sizeof(r_pow_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_r_pow_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_SIGN: { // Sign
    func.exec_func = exec_sign;
    nn_function_sign_t *f = (nn_function_sign_t *)function;
    sign_config_t *conf = malloc(sizeof(sign_config_t));
    conf->alpha = f->alpha;
    func.func.config = conf;
    allocate_sign_config(&func.func);
  } break;

  case NN_FUNCTION_MINIMUM2: { // Minimum2
    func.exec_func = exec_minimum2;
    allocate_minimum2_config(&func.func);
  } break;

  case NN_FUNCTION_MAXIMUM2: { // Maximum2
    func.exec_func = exec_maximum2;
    allocate_maximum2_config(&func.func);
  } break;

  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    func.exec_func = exec_minimum_scalar;
    nn_function_minimum_scalar_t *f = (nn_function_minimum_scalar_t *)function;
    minimum_scalar_config_t *conf = malloc(sizeof(minimum_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_minimum_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    func.exec_func = exec_maximum_scalar;
    nn_function_maximum_scalar_t *f = (nn_function_maximum_scalar_t *)function;
    maximum_scalar_config_t *conf = malloc(sizeof(maximum_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_maximum_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_AND: { // LogicalAnd
    func.exec_func = exec_logical_and;
    allocate_logical_and_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_OR: { // LogicalOr
    func.exec_func = exec_logical_or;
    allocate_logical_or_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_XOR: { // LogicalXor
    func.exec_func = exec_logical_xor;
    allocate_logical_xor_config(&func.func);
  } break;

  case NN_FUNCTION_EQUAL: { // Equal
    func.exec_func = exec_equal;
    allocate_equal_config(&func.func);
  } break;

  case NN_FUNCTION_NOT_EQUAL: { // NotEqual
    func.exec_func = exec_not_equal;
    allocate_not_equal_config(&func.func);
  } break;

  case NN_FUNCTION_GREATER_EQUAL: { // GreaterEqual
    func.exec_func = exec_greater_equal;
    allocate_greater_equal_config(&func.func);
  } break;

  case NN_FUNCTION_GREATER: { // Greater
    func.exec_func = exec_greater;
    allocate_greater_config(&func.func);
  } break;

  case NN_FUNCTION_LESS_EQUAL: { // LessEqual
    func.exec_func = exec_less_equal;
    allocate_less_equal_config(&func.func);
  } break;

  case NN_FUNCTION_LESS: { // Less
    func.exec_func = exec_less;
    allocate_less_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    func.exec_func = exec_logical_and_scalar;
    nn_function_logical_and_scalar_t *f =
        (nn_function_logical_and_scalar_t *)function;
    logical_and_scalar_config_t *conf =
        malloc(sizeof(logical_and_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_logical_and_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    func.exec_func = exec_logical_or_scalar;
    nn_function_logical_or_scalar_t *f =
        (nn_function_logical_or_scalar_t *)function;
    logical_or_scalar_config_t *conf =
        malloc(sizeof(logical_or_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_logical_or_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    func.exec_func = exec_logical_xor_scalar;
    nn_function_logical_xor_scalar_t *f =
        (nn_function_logical_xor_scalar_t *)function;
    logical_xor_scalar_config_t *conf =
        malloc(sizeof(logical_xor_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_logical_xor_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    func.exec_func = exec_equal_scalar;
    nn_function_equal_scalar_t *f = (nn_function_equal_scalar_t *)function;
    equal_scalar_config_t *conf = malloc(sizeof(equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_equal_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    func.exec_func = exec_not_equal_scalar;
    nn_function_not_equal_scalar_t *f =
        (nn_function_not_equal_scalar_t *)function;
    not_equal_scalar_config_t *conf = malloc(sizeof(not_equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_not_equal_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    func.exec_func = exec_greater_equal_scalar;
    nn_function_greater_equal_scalar_t *f =
        (nn_function_greater_equal_scalar_t *)function;
    greater_equal_scalar_config_t *conf =
        malloc(sizeof(greater_equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_greater_equal_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    func.exec_func = exec_greater_scalar;
    nn_function_greater_scalar_t *f = (nn_function_greater_scalar_t *)function;
    greater_scalar_config_t *conf = malloc(sizeof(greater_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_greater_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    func.exec_func = exec_less_equal_scalar;
    nn_function_less_equal_scalar_t *f =
        (nn_function_less_equal_scalar_t *)function;
    less_equal_scalar_config_t *conf =
        malloc(sizeof(less_equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_less_equal_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    func.exec_func = exec_less_scalar;
    nn_function_less_scalar_t *f = (nn_function_less_scalar_t *)function;
    less_scalar_config_t *conf = malloc(sizeof(less_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
    allocate_less_scalar_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_NOT: { // LogicalNot
    func.exec_func = exec_logical_not;
    allocate_logical_not_config(&func.func);
  } break;

  case NN_FUNCTION_CONSTANT: { // Constant
    func.exec_func = exec_constant;
    nn_function_constant_t *f = (nn_function_constant_t *)function;
    constant_config_t *conf = malloc(sizeof(constant_config_t));
    conf->val = f->val;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
    allocate_constant_config(&func.func);
  } break;

  case NN_FUNCTION_ABS: { // Abs
    func.exec_func = exec_abs;
    allocate_abs_config(&func.func);
  } break;

  case NN_FUNCTION_EXP: { // Exp
    func.exec_func = exec_exp;
    allocate_exp_config(&func.func);
  } break;

  case NN_FUNCTION_LOG: { // Log
    func.exec_func = exec_log;
    allocate_log_config(&func.func);
  } break;

  case NN_FUNCTION_IDENTITY: { // Identity
    func.exec_func = exec_identity;
    allocate_identity_config(&func.func);
  } break;

  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    func.exec_func = exec_batch_matmul;
    nn_function_batch_matmul_t *f = (nn_function_batch_matmul_t *)function;
    batch_matmul_config_t *conf = malloc(sizeof(batch_matmul_config_t));
    conf->transpose_a = f->transpose_a;
    conf->transpose_b = f->transpose_b;
    func.func.config = conf;
    allocate_batch_matmul_config(&func.func);
  } break;

  case NN_FUNCTION_CONCATENATE: { // Concatenate
    func.exec_func = exec_concatenate;
    nn_function_concatenate_t *f = (nn_function_concatenate_t *)function;
    concatenate_config_t *conf = malloc(sizeof(concatenate_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_concatenate_config(&func.func);
  } break;

  case NN_FUNCTION_SPLIT: { // Split
    func.exec_func = exec_split;
    nn_function_split_t *f = (nn_function_split_t *)function;
    split_config_t *conf = malloc(sizeof(split_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_split_config(&func.func);
  } break;

  case NN_FUNCTION_STACK: { // Stack
    func.exec_func = exec_stack;
    nn_function_stack_t *f = (nn_function_stack_t *)function;
    stack_config_t *conf = malloc(sizeof(stack_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_stack_config(&func.func);
  } break;

  case NN_FUNCTION_SLICE: { // Slice
    func.exec_func = exec_slice;
    nn_function_slice_t *f = (nn_function_slice_t *)function;
    slice_config_t *conf = malloc(sizeof(slice_config_t));
    conf->start = create_rt_list_from_nn_list(n, f->start);
    conf->stop = create_rt_list_from_nn_list(n, f->stop);
    conf->step = create_rt_list_from_nn_list(n, f->step);
    func.func.config = conf;
    allocate_slice_config(&func.func);
  } break;

  case NN_FUNCTION_TRANSPOSE: { // Transpose
    func.exec_func = exec_transpose;
    nn_function_transpose_t *f = (nn_function_transpose_t *)function;
    transpose_config_t *conf = malloc(sizeof(transpose_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    func.func.config = conf;
    allocate_transpose_config(&func.func);
  } break;

  case NN_FUNCTION_BROADCAST: { // Broadcast
    func.exec_func = exec_broadcast;
    nn_function_broadcast_t *f = (nn_function_broadcast_t *)function;
    broadcast_config_t *conf = malloc(sizeof(broadcast_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
    allocate_broadcast_config(&func.func);
  } break;

  case NN_FUNCTION_ONE_HOT: { // OneHot
    func.exec_func = exec_one_hot;
    nn_function_one_hot_t *f = (nn_function_one_hot_t *)function;
    one_hot_config_t *conf = malloc(sizeof(one_hot_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
    allocate_one_hot_config(&func.func);
  } break;

  case NN_FUNCTION_FLIP: { // Flip
    func.exec_func = exec_flip;
    nn_function_flip_t *f = (nn_function_flip_t *)function;
    flip_config_t *conf = malloc(sizeof(flip_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    func.func.config = conf;
    allocate_flip_config(&func.func);
  } break;

  case NN_FUNCTION_SHIFT: { // Shift
    func.exec_func = exec_shift;
    nn_function_shift_t *f = (nn_function_shift_t *)function;
    shift_config_t *conf = malloc(sizeof(shift_config_t));
    conf->shifts = create_rt_list_from_nn_list(n, f->shifts);
    conf->border_mode = f->border_mode;
    func.func.config = conf;
    allocate_shift_config(&func.func);
  } break;

  case NN_FUNCTION_RESHAPE: { // Reshape
    func.exec_func = exec_reshape;
    nn_function_reshape_t *f = (nn_function_reshape_t *)function;
    reshape_config_t *conf = malloc(sizeof(reshape_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
    allocate_reshape_config(&func.func);
  } break;

  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
    func.exec_func = exec_matrix_diag;
    allocate_matrix_diag_config(&func.func);
  } break;

  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
    func.exec_func = exec_matrix_diag_part;
    allocate_matrix_diag_part_config(&func.func);
  } break;

  case NN_FUNCTION_DROPOUT: { // Dropout
    func.exec_func = exec_dropout;
    nn_function_dropout_t *f = (nn_function_dropout_t *)function;
    dropout_config_t *conf = malloc(sizeof(dropout_config_t));
    conf->p = f->p;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_dropout_config(&func.func);
  } break;

  case NN_FUNCTION_RAND: { // Rand
    func.exec_func = exec_rand;
    nn_function_rand_t *f = (nn_function_rand_t *)function;
    rand_config_t *conf = malloc(sizeof(rand_config_t));
    conf->low = f->low;
    conf->high = f->high;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_rand_config(&func.func);
  } break;

  case NN_FUNCTION_RANDINT: { // Randint
    func.exec_func = exec_randint;
    nn_function_randint_t *f = (nn_function_randint_t *)function;
    randint_config_t *conf = malloc(sizeof(randint_config_t));
    conf->low = f->low;
    conf->high = f->high;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_randint_config(&func.func);
  } break;

  case NN_FUNCTION_RANDN: { // Randn
    func.exec_func = exec_randn;
    nn_function_randn_t *f = (nn_function_randn_t *)function;
    randn_config_t *conf = malloc(sizeof(randn_config_t));
    conf->mu = f->mu;
    conf->sigma = f->sigma;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_randn_config(&func.func);
  } break;

  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    func.exec_func = exec_random_crop;
    nn_function_random_crop_t *f = (nn_function_random_crop_t *)function;
    random_crop_config_t *conf = malloc(sizeof(random_crop_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->base_axis = f->base_axis;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_random_crop_config(&func.func);
  } break;

  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    func.exec_func = exec_random_flip;
    nn_function_random_flip_t *f = (nn_function_random_flip_t *)function;
    random_flip_config_t *conf = malloc(sizeof(random_flip_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->base_axis = f->base_axis;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_random_flip_config(&func.func);
  } break;

  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    func.exec_func = exec_random_shift;
    nn_function_random_shift_t *f = (nn_function_random_shift_t *)function;
    random_shift_config_t *conf = malloc(sizeof(random_shift_config_t));
    conf->shifts = create_rt_list_from_nn_list(n, f->shifts);
    conf->border_mode = f->border_mode;
    conf->base_axis = f->base_axis;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_random_shift_config(&func.func);
  } break;

  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    func.exec_func = exec_image_augmentation;
    nn_function_image_augmentation_t *f =
        (nn_function_image_augmentation_t *)function;
    image_augmentation_config_t *conf =
        malloc(sizeof(image_augmentation_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->min_scale = f->min_scale;
    conf->max_scale = f->max_scale;
    conf->angle = f->angle;
    conf->aspect_ratio = f->aspect_ratio;
    conf->distortion = f->distortion;
    conf->flip_lr = f->flip_lr;
    conf->flip_ud = f->flip_ud;
    conf->brightness = f->brightness;
    conf->brightness_each = f->brightness_each;
    conf->contrast = f->contrast;
    conf->contrast_center = f->contrast_center;
    conf->contrast_each = f->contrast_each;
    conf->noise = f->noise;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_image_augmentation_config(&func.func);
  } break;

  case NN_FUNCTION_SIGMOID_CROSS_ENTROPY: { // SigmoidCrossEntropy
    func.exec_func = exec_sigmoid_cross_entropy;
    allocate_sigmoid_cross_entropy_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_CROSS_ENTROPY: { // BinaryCrossEntropy
    func.exec_func = exec_binary_cross_entropy;
    allocate_binary_cross_entropy_config(&func.func);
  } break;

  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    func.exec_func = exec_softmax_cross_entropy;
    nn_function_softmax_cross_entropy_t *f =
        (nn_function_softmax_cross_entropy_t *)function;
    softmax_cross_entropy_config_t *conf =
        malloc(sizeof(softmax_cross_entropy_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_softmax_cross_entropy_config(&func.func);
  } break;

  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    func.exec_func = exec_categorical_cross_entropy;
    nn_function_categorical_cross_entropy_t *f =
        (nn_function_categorical_cross_entropy_t *)function;
    categorical_cross_entropy_config_t *conf =
        malloc(sizeof(categorical_cross_entropy_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_categorical_cross_entropy_config(&func.func);
  } break;

  case NN_FUNCTION_SQUARED_ERROR: { // SquaredError
    func.exec_func = exec_squared_error;
    allocate_squared_error_config(&func.func);
  } break;

  case NN_FUNCTION_ABSOLUTE_ERROR: { // AbsoluteError
    func.exec_func = exec_absolute_error;
    allocate_absolute_error_config(&func.func);
  } break;

  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    func.exec_func = exec_huber_loss;
    nn_function_huber_loss_t *f = (nn_function_huber_loss_t *)function;
    huber_loss_config_t *conf = malloc(sizeof(huber_loss_config_t));
    conf->delta = f->delta;
    func.func.config = conf;
    allocate_huber_loss_config(&func.func);
  } break;

  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    func.exec_func = exec_epsilon_insensitive_loss;
    nn_function_epsilon_insensitive_loss_t *f =
        (nn_function_epsilon_insensitive_loss_t *)function;
    epsilon_insensitive_loss_config_t *conf =
        malloc(sizeof(epsilon_insensitive_loss_config_t));
    conf->epsilon = f->epsilon;
    func.func.config = conf;
    allocate_epsilon_insensitive_loss_config(&func.func);
  } break;

  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    func.exec_func = exec_kl_multinomial;
    nn_function_kl_multinomial_t *f = (nn_function_kl_multinomial_t *)function;
    kl_multinomial_config_t *conf = malloc(sizeof(kl_multinomial_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
    allocate_kl_multinomial_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_SIGMOID: { // BinarySigmoid
    func.exec_func = exec_binary_sigmoid;
    allocate_binary_sigmoid_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_TANH: { // BinaryTanh
    func.exec_func = exec_binary_tanh;
    allocate_binary_tanh_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    func.exec_func = exec_binary_connect_affine;
    nn_function_binary_connect_affine_t *f =
        (nn_function_binary_connect_affine_t *)function;
    binary_connect_affine_config_t *conf =
        malloc(sizeof(binary_connect_affine_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
    allocate_binary_connect_affine_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    func.exec_func = exec_binary_connect_convolution;
    nn_function_binary_connect_convolution_t *f =
        (nn_function_binary_connect_convolution_t *)function;
    binary_connect_convolution_config_t *conf =
        malloc(sizeof(binary_connect_convolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    func.func.config = conf;
    allocate_binary_connect_convolution_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    func.exec_func = exec_binary_weight_affine;
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)function;
    binary_weight_affine_config_t *conf =
        malloc(sizeof(binary_weight_affine_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
    allocate_binary_weight_affine_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    func.exec_func = exec_binary_weight_convolution;
    nn_function_binary_weight_convolution_t *f =
        (nn_function_binary_weight_convolution_t *)function;
    binary_weight_convolution_config_t *conf =
        malloc(sizeof(binary_weight_convolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    func.func.config = conf;
    allocate_binary_weight_convolution_config(&func.func);
  } break;

  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    func.exec_func = exec_inq_affine;
    nn_function_inq_affine_t *f = (nn_function_inq_affine_t *)function;
    inq_affine_config_t *conf = malloc(sizeof(inq_affine_config_t));
    conf->base_axis = f->base_axis;
    conf->num_bits = f->num_bits;
    conf->inq_iterations = create_rt_list_from_nn_list(n, f->inq_iterations);
    conf->selection_algorithm = f->selection_algorithm;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_inq_affine_config(&func.func);
  } break;

  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    func.exec_func = exec_inq_convolution;
    nn_function_inq_convolution_t *f =
        (nn_function_inq_convolution_t *)function;
    inq_convolution_config_t *conf = malloc(sizeof(inq_convolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    conf->num_bits = f->num_bits;
    conf->inq_iterations = create_rt_list_from_nn_list(n, f->inq_iterations);
    conf->selection_algorithm = f->selection_algorithm;
    conf->seed = f->seed;
    func.func.config = conf;
    allocate_inq_convolution_config(&func.func);
  } break;

  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    func.exec_func = exec_fixed_point_quantize;
    nn_function_fixed_point_quantize_t *f =
        (nn_function_fixed_point_quantize_t *)function;
    fixed_point_quantize_config_t *conf =
        malloc(sizeof(fixed_point_quantize_config_t));
    conf->sign = f->sign;
    conf->n = f->n;
    conf->delta = f->delta;
    conf->ste_fine_grained = f->ste_fine_grained;
    func.func.config = conf;
    allocate_fixed_point_quantize_config(&func.func);
  } break;

  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    func.exec_func = exec_pow2_quantize;
    nn_function_pow2_quantize_t *f = (nn_function_pow2_quantize_t *)function;
    pow2_quantize_config_t *conf = malloc(sizeof(pow2_quantize_config_t));
    conf->sign = f->sign;
    conf->with_zero = f->with_zero;
    conf->n = f->n;
    conf->m = f->m;
    conf->ste_fine_grained = f->ste_fine_grained;
    func.func.config = conf;
    allocate_pow2_quantize_config(&func.func);
  } break;

  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    func.exec_func = exec_top_n_error;
    nn_function_top_n_error_t *f = (nn_function_top_n_error_t *)function;
    top_n_error_config_t *conf = malloc(sizeof(top_n_error_config_t));
    conf->axis = f->axis;
    conf->n = f->n;
    func.func.config = conf;
    allocate_top_n_error_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_ERROR: { // BinaryError
    func.exec_func = exec_binary_error;
    allocate_binary_error_config(&func.func);
  } break;

  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    func.exec_func = exec_confusion_matrix;
    nn_function_confusion_matrix_t *f =
        (nn_function_confusion_matrix_t *)function;
    confusion_matrix_config_t *conf = malloc(sizeof(confusion_matrix_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
    allocate_confusion_matrix_config(&func.func);
  } break;

  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    func.exec_func = exec_vat_noise;
    nn_function_vat_noise_t *f = (nn_function_vat_noise_t *)function;
    vat_noise_config_t *conf = malloc(sizeof(vat_noise_config_t));
    conf->base_axis = f->base_axis;
    conf->eps = f->eps;
    func.func.config = conf;
    allocate_vat_noise_config(&func.func);
  } break;

  case NN_FUNCTION_UNLINK: { // Unlink
    func.exec_func = exec_unlink;
    allocate_unlink_config(&func.func);
  } break;

  case NN_FUNCTION_SINK: { // Sink
    func.exec_func = exec_sink;
    nn_function_sink_t *f = (nn_function_sink_t *)function;
    sink_config_t *conf = malloc(sizeof(sink_config_t));
    conf->one_input_grad = f->one_input_grad;
    func.func.config = conf;
    allocate_sink_config(&func.func);
  } break;

  default:
    func.func.config = 0;
  }

  return func;
}

void free_function_context(rt_context_t *c, rt_function_context_t func) {
  switch (func.type) {
  case NN_FUNCTION_AFFINE: { // Affine
    free_affine_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_CONVOLUTION: { // Convolution
    free_convolution_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    free_depthwise_convolution_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    free_deconvolution_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    free_max_pooling_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    free_average_pooling_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    free_sum_pooling_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_UNPOOLING: { // Unpooling
    free_unpooling_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_EMBED: { // Embed
    free_embed_config(&func.func);
  } break;

  case NN_FUNCTION_SIGMOID: { // Sigmoid
    free_sigmoid_config(&func.func);
  } break;

  case NN_FUNCTION_SWISH: { // Swish
    free_swish_config(&func.func);
  } break;

  case NN_FUNCTION_TANH: { // Tanh
    free_tanh_config(&func.func);
  } break;

  case NN_FUNCTION_RELU: { // ReLU
    free_relu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    free_leaky_relu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SOFTMAX: { // Softmax
    free_softmax_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_ELU: { // ELU
    free_elu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SELU: { // SELU
    free_selu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_CRELU: { // CReLU
    free_crelu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_CELU: { // CELU
    free_celu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_PRELU: { // PReLU
    free_prelu_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    free_batch_normalization_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    free_mean_subtraction_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SUM: { // Sum
    free_sum_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MEAN: { // Mean
    free_mean_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MAX: { // Max
    free_max_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MIN: { // Min
    free_min_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_PROD: { // Prod
    free_prod_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
    free_reduce_sum_config(&func.func);
  } break;

  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
    free_reduce_mean_config(&func.func);
  } break;

  case NN_FUNCTION_ADD2: { // Add2
    free_add2_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    free_bc_add2_config(&func.func);
  } break;

  case NN_FUNCTION_SUB2: { // Sub2
    free_sub2_config(&func.func);
  } break;

  case NN_FUNCTION_MUL2: { // Mul2
    free_mul2_config(&func.func);
  } break;

  case NN_FUNCTION_DIV2: { // Div2
    free_div2_config(&func.func);
  } break;

  case NN_FUNCTION_POW2: { // Pow2
    free_pow2_config(&func.func);
  } break;

  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    free_add_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    free_mul_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    free_pow_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    free_r_sub_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    free_r_div_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    free_r_pow_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SIGN: { // Sign
    free_sign_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MINIMUM2: { // Minimum2
    free_minimum2_config(&func.func);
  } break;

  case NN_FUNCTION_MAXIMUM2: { // Maximum2
    free_maximum2_config(&func.func);
  } break;

  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    free_minimum_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    free_maximum_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LOGICAL_AND: { // LogicalAnd
    free_logical_and_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_OR: { // LogicalOr
    free_logical_or_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_XOR: { // LogicalXor
    free_logical_xor_config(&func.func);
  } break;

  case NN_FUNCTION_EQUAL: { // Equal
    free_equal_config(&func.func);
  } break;

  case NN_FUNCTION_NOT_EQUAL: { // NotEqual
    free_not_equal_config(&func.func);
  } break;

  case NN_FUNCTION_GREATER_EQUAL: { // GreaterEqual
    free_greater_equal_config(&func.func);
  } break;

  case NN_FUNCTION_GREATER: { // Greater
    free_greater_config(&func.func);
  } break;

  case NN_FUNCTION_LESS_EQUAL: { // LessEqual
    free_less_equal_config(&func.func);
  } break;

  case NN_FUNCTION_LESS: { // Less
    free_less_config(&func.func);
  } break;

  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    free_logical_and_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    free_logical_or_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    free_logical_xor_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    free_equal_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    free_not_equal_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    free_greater_equal_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    free_greater_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    free_less_equal_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    free_less_scalar_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_LOGICAL_NOT: { // LogicalNot
    free_logical_not_config(&func.func);
  } break;

  case NN_FUNCTION_CONSTANT: { // Constant
    free_constant_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_ABS: { // Abs
    free_abs_config(&func.func);
  } break;

  case NN_FUNCTION_EXP: { // Exp
    free_exp_config(&func.func);
  } break;

  case NN_FUNCTION_LOG: { // Log
    free_log_config(&func.func);
  } break;

  case NN_FUNCTION_IDENTITY: { // Identity
    free_identity_config(&func.func);
  } break;

  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    free_batch_matmul_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_CONCATENATE: { // Concatenate
    free_concatenate_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SPLIT: { // Split
    free_split_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_STACK: { // Stack
    free_stack_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SLICE: { // Slice
    free_slice_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_TRANSPOSE: { // Transpose
    free_transpose_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BROADCAST: { // Broadcast
    free_broadcast_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_ONE_HOT: { // OneHot
    free_one_hot_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_FLIP: { // Flip
    free_flip_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SHIFT: { // Shift
    free_shift_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RESHAPE: { // Reshape
    free_reshape_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
    free_matrix_diag_config(&func.func);
  } break;

  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
    free_matrix_diag_part_config(&func.func);
  } break;

  case NN_FUNCTION_DROPOUT: { // Dropout
    free_dropout_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RAND: { // Rand
    free_rand_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RANDINT: { // Randint
    free_randint_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RANDN: { // Randn
    free_randn_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    free_random_crop_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    free_random_flip_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    free_random_shift_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    free_image_augmentation_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SIGMOID_CROSS_ENTROPY: { // SigmoidCrossEntropy
    free_sigmoid_cross_entropy_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_CROSS_ENTROPY: { // BinaryCrossEntropy
    free_binary_cross_entropy_config(&func.func);
  } break;

  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    free_softmax_cross_entropy_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    free_categorical_cross_entropy_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_SQUARED_ERROR: { // SquaredError
    free_squared_error_config(&func.func);
  } break;

  case NN_FUNCTION_ABSOLUTE_ERROR: { // AbsoluteError
    free_absolute_error_config(&func.func);
  } break;

  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    free_huber_loss_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    free_epsilon_insensitive_loss_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    free_kl_multinomial_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BINARY_SIGMOID: { // BinarySigmoid
    free_binary_sigmoid_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_TANH: { // BinaryTanh
    free_binary_tanh_config(&func.func);
  } break;

  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    free_binary_connect_affine_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    free_binary_connect_convolution_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    free_binary_weight_affine_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    free_binary_weight_convolution_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    free_inq_affine_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    free_inq_convolution_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    free_fixed_point_quantize_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    free_pow2_quantize_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    free_top_n_error_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_BINARY_ERROR: { // BinaryError
    free_binary_error_config(&func.func);
  } break;

  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    free_confusion_matrix_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    free_vat_noise_config(&func.func);
    free(func.func.config);
  } break;

  case NN_FUNCTION_UNLINK: { // Unlink
    free_unlink_config(&func.func);
  } break;

  case NN_FUNCTION_SINK: { // Sink
    free_sink_config(&func.func);
    free(func.func.config);
  } break;

  default:
    break;
  }
}
