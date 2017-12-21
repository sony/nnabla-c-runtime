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

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "runtime_internal.h"

rt_function_context_t create_function_context(nn_network_t *n, rt_context_t *c,
                                              nn_function_t *function) {
  int i; // Iterator

  rt_function_context_t func;
  func.type = function->type;

  rt_list_t inputs = create_rt_list_from_nn_list(n, function->inputs);
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
    WHOAMI("Affine\n");
    nn_function_affine_t *f = (nn_function_affine_t *)function;
    affine_config_t *conf = malloc(sizeof(affine_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CONVOLUTION: { // Convolution
    WHOAMI("Convolution\n");
    nn_function_convolution_t *f = (nn_function_convolution_t *)function;
    convolution_config_t *conf = malloc(sizeof(convolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    WHOAMI("DepthwiseConvolution\n");
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
  } break;
  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    WHOAMI("Deconvolution\n");
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)function;
    deconvolution_config_t *conf = malloc(sizeof(deconvolution_config_t));
    conf->base_axis = f->base_axis;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->dilation = create_rt_list_from_nn_list(n, f->dilation);
    conf->group = f->group;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    WHOAMI("MaxPooling\n");
    nn_function_max_pooling_t *f = (nn_function_max_pooling_t *)function;
    max_pooling_config_t *conf = malloc(sizeof(max_pooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->ignore_border = f->ignore_border;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    WHOAMI("AveragePooling\n");
    nn_function_average_pooling_t *f =
        (nn_function_average_pooling_t *)function;
    average_pooling_config_t *conf = malloc(sizeof(average_pooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->ignore_border = f->ignore_border;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    conf->including_pad = f->including_pad;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    WHOAMI("SumPooling\n");
    nn_function_sum_pooling_t *f = (nn_function_sum_pooling_t *)function;
    sum_pooling_config_t *conf = malloc(sizeof(sum_pooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    conf->stride = create_rt_list_from_nn_list(n, f->stride);
    conf->ignore_border = f->ignore_border;
    conf->pad = create_rt_list_from_nn_list(n, f->pad);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_UNPOOLING: { // Unpooling
    WHOAMI("Unpooling\n");
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)function;
    unpooling_config_t *conf = malloc(sizeof(unpooling_config_t));
    conf->kernel = create_rt_list_from_nn_list(n, f->kernel);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RELU: { // ReLU
    WHOAMI("ReLU\n");
    nn_function_relu_t *f = (nn_function_relu_t *)function;
    relu_config_t *conf = malloc(sizeof(relu_config_t));
    conf->inplace = f->inplace;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    WHOAMI("LeakyReLU\n");
    nn_function_leaky_relu_t *f = (nn_function_leaky_relu_t *)function;
    leaky_relu_config_t *conf = malloc(sizeof(leaky_relu_config_t));
    conf->alpha = f->alpha;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SOFTMAX: { // Softmax
    WHOAMI("Softmax\n");
    nn_function_softmax_t *f = (nn_function_softmax_t *)function;
    softmax_config_t *conf = malloc(sizeof(softmax_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_ELU: { // ELU
    WHOAMI("ELU\n");
    nn_function_elu_t *f = (nn_function_elu_t *)function;
    elu_config_t *conf = malloc(sizeof(elu_config_t));
    conf->alpha = f->alpha;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SELU: { // SELU
    WHOAMI("SELU\n");
    nn_function_selu_t *f = (nn_function_selu_t *)function;
    selu_config_t *conf = malloc(sizeof(selu_config_t));
    conf->scale = f->scale;
    conf->alpha = f->alpha;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CRELU: { // CReLU
    WHOAMI("CReLU\n");
    nn_function_crelu_t *f = (nn_function_crelu_t *)function;
    crelu_config_t *conf = malloc(sizeof(crelu_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CELU: { // CELU
    WHOAMI("CELU\n");
    nn_function_celu_t *f = (nn_function_celu_t *)function;
    celu_config_t *conf = malloc(sizeof(celu_config_t));
    conf->alpha = f->alpha;
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_PRELU: { // PReLU
    WHOAMI("PReLU\n");
    nn_function_prelu_t *f = (nn_function_prelu_t *)function;
    prelu_config_t *conf = malloc(sizeof(prelu_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    WHOAMI("BatchNormalization\n");
    nn_function_batch_normalization_t *f =
        (nn_function_batch_normalization_t *)function;
    batch_normalization_config_t *conf =
        malloc(sizeof(batch_normalization_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->decay_rate = f->decay_rate;
    conf->eps = f->eps;
    conf->batch_stat = f->batch_stat;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    WHOAMI("MeanSubtraction\n");
    nn_function_mean_subtraction_t *f =
        (nn_function_mean_subtraction_t *)function;
    mean_subtraction_config_t *conf = malloc(sizeof(mean_subtraction_config_t));
    conf->base_axis = f->base_axis;
    conf->update_running_mean = f->update_running_mean;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SUM: { // Sum
    WHOAMI("Sum\n");
    nn_function_sum_t *f = (nn_function_sum_t *)function;
    sum_config_t *conf = malloc(sizeof(sum_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MEAN: { // Mean
    WHOAMI("Mean\n");
    nn_function_mean_t *f = (nn_function_mean_t *)function;
    mean_config_t *conf = malloc(sizeof(mean_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MAX: { // Max
    WHOAMI("Max\n");
    nn_function_max_t *f = (nn_function_max_t *)function;
    max_config_t *conf = malloc(sizeof(max_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MIN: { // Min
    WHOAMI("Min\n");
    nn_function_min_t *f = (nn_function_min_t *)function;
    min_config_t *conf = malloc(sizeof(min_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_PROD: { // Prod
    WHOAMI("Prod\n");
    nn_function_prod_t *f = (nn_function_prod_t *)function;
    prod_config_t *conf = malloc(sizeof(prod_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->keep_dims = f->keep_dims;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_ADD2: { // Add2
    WHOAMI("Add2\n");
    nn_function_add2_t *f = (nn_function_add2_t *)function;
    add2_config_t *conf = malloc(sizeof(add2_config_t));
    conf->inplace = f->inplace;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    WHOAMI("AddScalar\n");
    nn_function_add_scalar_t *f = (nn_function_add_scalar_t *)function;
    add_scalar_config_t *conf = malloc(sizeof(add_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    WHOAMI("MulScalar\n");
    nn_function_mul_scalar_t *f = (nn_function_mul_scalar_t *)function;
    mul_scalar_config_t *conf = malloc(sizeof(mul_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    WHOAMI("PowScalar\n");
    nn_function_pow_scalar_t *f = (nn_function_pow_scalar_t *)function;
    pow_scalar_config_t *conf = malloc(sizeof(pow_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    WHOAMI("RSubScalar\n");
    nn_function_r_sub_scalar_t *f = (nn_function_r_sub_scalar_t *)function;
    r_sub_scalar_config_t *conf = malloc(sizeof(r_sub_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    WHOAMI("RDivScalar\n");
    nn_function_r_div_scalar_t *f = (nn_function_r_div_scalar_t *)function;
    r_div_scalar_config_t *conf = malloc(sizeof(r_div_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    WHOAMI("RPowScalar\n");
    nn_function_r_pow_scalar_t *f = (nn_function_r_pow_scalar_t *)function;
    r_pow_scalar_config_t *conf = malloc(sizeof(r_pow_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SIGN: { // Sign
    WHOAMI("Sign\n");
    nn_function_sign_t *f = (nn_function_sign_t *)function;
    sign_config_t *conf = malloc(sizeof(sign_config_t));
    conf->alpha = f->alpha;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    WHOAMI("MinimumScalar\n");
    nn_function_minimum_scalar_t *f = (nn_function_minimum_scalar_t *)function;
    minimum_scalar_config_t *conf = malloc(sizeof(minimum_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    WHOAMI("MaximumScalar\n");
    nn_function_maximum_scalar_t *f = (nn_function_maximum_scalar_t *)function;
    maximum_scalar_config_t *conf = malloc(sizeof(maximum_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    WHOAMI("LogicalAndScalar\n");
    nn_function_logical_and_scalar_t *f =
        (nn_function_logical_and_scalar_t *)function;
    logical_and_scalar_config_t *conf =
        malloc(sizeof(logical_and_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    WHOAMI("LogicalOrScalar\n");
    nn_function_logical_or_scalar_t *f =
        (nn_function_logical_or_scalar_t *)function;
    logical_or_scalar_config_t *conf =
        malloc(sizeof(logical_or_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    WHOAMI("LogicalXorScalar\n");
    nn_function_logical_xor_scalar_t *f =
        (nn_function_logical_xor_scalar_t *)function;
    logical_xor_scalar_config_t *conf =
        malloc(sizeof(logical_xor_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    WHOAMI("EqualScalar\n");
    nn_function_equal_scalar_t *f = (nn_function_equal_scalar_t *)function;
    equal_scalar_config_t *conf = malloc(sizeof(equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    WHOAMI("NotEqualScalar\n");
    nn_function_not_equal_scalar_t *f =
        (nn_function_not_equal_scalar_t *)function;
    not_equal_scalar_config_t *conf = malloc(sizeof(not_equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    WHOAMI("GreaterEqualScalar\n");
    nn_function_greater_equal_scalar_t *f =
        (nn_function_greater_equal_scalar_t *)function;
    greater_equal_scalar_config_t *conf =
        malloc(sizeof(greater_equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    WHOAMI("GreaterScalar\n");
    nn_function_greater_scalar_t *f = (nn_function_greater_scalar_t *)function;
    greater_scalar_config_t *conf = malloc(sizeof(greater_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    WHOAMI("LessEqualScalar\n");
    nn_function_less_equal_scalar_t *f =
        (nn_function_less_equal_scalar_t *)function;
    less_equal_scalar_config_t *conf =
        malloc(sizeof(less_equal_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    WHOAMI("LessScalar\n");
    nn_function_less_scalar_t *f = (nn_function_less_scalar_t *)function;
    less_scalar_config_t *conf = malloc(sizeof(less_scalar_config_t));
    conf->val = f->val;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CONSTANT: { // Constant
    WHOAMI("Constant\n");
    nn_function_constant_t *f = (nn_function_constant_t *)function;
    constant_config_t *conf = malloc(sizeof(constant_config_t));
    conf->val = f->val;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    WHOAMI("BatchMatmul\n");
    nn_function_batch_matmul_t *f = (nn_function_batch_matmul_t *)function;
    batch_matmul_config_t *conf = malloc(sizeof(batch_matmul_config_t));
    conf->transpose_a = f->transpose_a;
    conf->transpose_b = f->transpose_b;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CONCATENATE: { // Concatenate
    WHOAMI("Concatenate\n");
    nn_function_concatenate_t *f = (nn_function_concatenate_t *)function;
    concatenate_config_t *conf = malloc(sizeof(concatenate_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SPLIT: { // Split
    WHOAMI("Split\n");
    nn_function_split_t *f = (nn_function_split_t *)function;
    split_config_t *conf = malloc(sizeof(split_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_STACK: { // Stack
    WHOAMI("Stack\n");
    nn_function_stack_t *f = (nn_function_stack_t *)function;
    stack_config_t *conf = malloc(sizeof(stack_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SLICE: { // Slice
    WHOAMI("Slice\n");
    nn_function_slice_t *f = (nn_function_slice_t *)function;
    slice_config_t *conf = malloc(sizeof(slice_config_t));
    conf->start = create_rt_list_from_nn_list(n, f->start);
    conf->stop = create_rt_list_from_nn_list(n, f->stop);
    conf->step = create_rt_list_from_nn_list(n, f->step);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_TRANSPOSE: { // Transpose
    WHOAMI("Transpose\n");
    nn_function_transpose_t *f = (nn_function_transpose_t *)function;
    transpose_config_t *conf = malloc(sizeof(transpose_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_BROADCAST: { // Broadcast
    WHOAMI("Broadcast\n");
    nn_function_broadcast_t *f = (nn_function_broadcast_t *)function;
    broadcast_config_t *conf = malloc(sizeof(broadcast_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_ONE_HOT: { // OneHot
    WHOAMI("OneHot\n");
    nn_function_one_hot_t *f = (nn_function_one_hot_t *)function;
    one_hot_config_t *conf = malloc(sizeof(one_hot_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_FLIP: { // Flip
    WHOAMI("Flip\n");
    nn_function_flip_t *f = (nn_function_flip_t *)function;
    flip_config_t *conf = malloc(sizeof(flip_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SHIFT: { // Shift
    WHOAMI("Shift\n");
    nn_function_shift_t *f = (nn_function_shift_t *)function;
    shift_config_t *conf = malloc(sizeof(shift_config_t));
    conf->shifts = create_rt_list_from_nn_list(n, f->shifts);
    conf->border_mode = f->border_mode;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RESHAPE: { // Reshape
    WHOAMI("Reshape\n");
    nn_function_reshape_t *f = (nn_function_reshape_t *)function;
    reshape_config_t *conf = malloc(sizeof(reshape_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    func.func.config = conf;
  } break;
  case NN_FUNCTION_DROPOUT: { // Dropout
    WHOAMI("Dropout\n");
    nn_function_dropout_t *f = (nn_function_dropout_t *)function;
    dropout_config_t *conf = malloc(sizeof(dropout_config_t));
    conf->p = f->p;
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RAND: { // Rand
    WHOAMI("Rand\n");
    nn_function_rand_t *f = (nn_function_rand_t *)function;
    rand_config_t *conf = malloc(sizeof(rand_config_t));
    conf->low = f->low;
    conf->high = f->high;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RANDINT: { // Randint
    WHOAMI("Randint\n");
    nn_function_randint_t *f = (nn_function_randint_t *)function;
    randint_config_t *conf = malloc(sizeof(randint_config_t));
    conf->low = f->low;
    conf->high = f->high;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RANDN: { // Randn
    WHOAMI("Randn\n");
    nn_function_randn_t *f = (nn_function_randn_t *)function;
    randn_config_t *conf = malloc(sizeof(randn_config_t));
    conf->mu = f->mu;
    conf->sigma = f->sigma;
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    WHOAMI("RandomCrop\n");
    nn_function_random_crop_t *f = (nn_function_random_crop_t *)function;
    random_crop_config_t *conf = malloc(sizeof(random_crop_config_t));
    conf->shape = create_rt_list_from_nn_list(n, f->shape);
    conf->base_axis = f->base_axis;
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    WHOAMI("RandomFlip\n");
    nn_function_random_flip_t *f = (nn_function_random_flip_t *)function;
    random_flip_config_t *conf = malloc(sizeof(random_flip_config_t));
    conf->axes = create_rt_list_from_nn_list(n, f->axes);
    conf->base_axis = f->base_axis;
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    WHOAMI("RandomShift\n");
    nn_function_random_shift_t *f = (nn_function_random_shift_t *)function;
    random_shift_config_t *conf = malloc(sizeof(random_shift_config_t));
    conf->shifts = create_rt_list_from_nn_list(n, f->shifts);
    conf->border_mode = f->border_mode;
    conf->base_axis = f->base_axis;
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    WHOAMI("ImageAugmentation\n");
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
  } break;
  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    WHOAMI("SoftmaxCrossEntropy\n");
    nn_function_softmax_cross_entropy_t *f =
        (nn_function_softmax_cross_entropy_t *)function;
    softmax_cross_entropy_config_t *conf =
        malloc(sizeof(softmax_cross_entropy_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    WHOAMI("CategoricalCrossEntropy\n");
    nn_function_categorical_cross_entropy_t *f =
        (nn_function_categorical_cross_entropy_t *)function;
    categorical_cross_entropy_config_t *conf =
        malloc(sizeof(categorical_cross_entropy_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    WHOAMI("HuberLoss\n");
    nn_function_huber_loss_t *f = (nn_function_huber_loss_t *)function;
    huber_loss_config_t *conf = malloc(sizeof(huber_loss_config_t));
    conf->delta = f->delta;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    WHOAMI("EpsilonInsensitiveLoss\n");
    nn_function_epsilon_insensitive_loss_t *f =
        (nn_function_epsilon_insensitive_loss_t *)function;
    epsilon_insensitive_loss_config_t *conf =
        malloc(sizeof(epsilon_insensitive_loss_config_t));
    conf->epsilon = f->epsilon;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    WHOAMI("KLMultinomial\n");
    nn_function_kl_multinomial_t *f = (nn_function_kl_multinomial_t *)function;
    kl_multinomial_config_t *conf = malloc(sizeof(kl_multinomial_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    WHOAMI("BinaryConnectAffine\n");
    nn_function_binary_connect_affine_t *f =
        (nn_function_binary_connect_affine_t *)function;
    binary_connect_affine_config_t *conf =
        malloc(sizeof(binary_connect_affine_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    WHOAMI("BinaryConnectConvolution\n");
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
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    WHOAMI("BinaryWeightAffine\n");
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)function;
    binary_weight_affine_config_t *conf =
        malloc(sizeof(binary_weight_affine_config_t));
    conf->base_axis = f->base_axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    WHOAMI("BinaryWeightConvolution\n");
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
  } break;
  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    WHOAMI("INQAffine\n");
    nn_function_inq_affine_t *f = (nn_function_inq_affine_t *)function;
    inq_affine_config_t *conf = malloc(sizeof(inq_affine_config_t));
    conf->base_axis = f->base_axis;
    conf->num_bits = f->num_bits;
    conf->inq_iterations = create_rt_list_from_nn_list(n, f->inq_iterations);
    conf->selection_algorithm = f->selection_algorithm;
    conf->seed = f->seed;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    WHOAMI("INQConvolution\n");
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
  } break;
  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    WHOAMI("FixedPointQuantize\n");
    nn_function_fixed_point_quantize_t *f =
        (nn_function_fixed_point_quantize_t *)function;
    fixed_point_quantize_config_t *conf =
        malloc(sizeof(fixed_point_quantize_config_t));
    conf->sign = f->sign;
    conf->n = f->n;
    conf->delta = f->delta;
    conf->ste_fine_grained = f->ste_fine_grained;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    WHOAMI("Pow2Quantize\n");
    nn_function_pow2_quantize_t *f = (nn_function_pow2_quantize_t *)function;
    pow2_quantize_config_t *conf = malloc(sizeof(pow2_quantize_config_t));
    conf->sign = f->sign;
    conf->with_zero = f->with_zero;
    conf->n = f->n;
    conf->m = f->m;
    conf->ste_fine_grained = f->ste_fine_grained;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    WHOAMI("TopNError\n");
    nn_function_top_n_error_t *f = (nn_function_top_n_error_t *)function;
    top_n_error_config_t *conf = malloc(sizeof(top_n_error_config_t));
    conf->axis = f->axis;
    conf->n = f->n;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    WHOAMI("ConfusionMatrix\n");
    nn_function_confusion_matrix_t *f =
        (nn_function_confusion_matrix_t *)function;
    confusion_matrix_config_t *conf = malloc(sizeof(confusion_matrix_config_t));
    conf->axis = f->axis;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    WHOAMI("VATNoise\n");
    nn_function_vat_noise_t *f = (nn_function_vat_noise_t *)function;
    vat_noise_config_t *conf = malloc(sizeof(vat_noise_config_t));
    conf->base_axis = f->base_axis;
    conf->eps = f->eps;
    func.func.config = conf;
  } break;
  case NN_FUNCTION_SINK: { // Sink
    WHOAMI("Sink\n");
    nn_function_sink_t *f = (nn_function_sink_t *)function;
    sink_config_t *conf = malloc(sizeof(sink_config_t));
    conf->one_input_grad = f->one_input_grad;
    func.func.config = conf;
  } break;
  default:
    func.func.config = 0;
  }

  return func;
}
