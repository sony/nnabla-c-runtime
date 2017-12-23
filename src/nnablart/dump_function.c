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

#include "../runtime/runtime_internal.h"
#include "dump.h"
#include "dump_function.h"

static const char *const typenames[] = {
    "Affine",
    "Convolution",
    "DepthwiseConvolution",
    "Deconvolution",
    "MaxPooling",
    "AveragePooling",
    "SumPooling",
    "Unpooling",
    "Embed",
    "Sigmoid",
    "Swish",
    "Tanh",
    "ReLU",
    "LeakyReLU",
    "Softmax",
    "ELU",
    "SELU",
    "CReLU",
    "CELU",
    "PReLU",
    "BatchNormalization",
    "MeanSubtraction",
    "Sum",
    "Mean",
    "Max",
    "Min",
    "Prod",
    "ReduceSum",
    "ReduceMean",
    "Add2",
    "BcAdd2",
    "Sub2",
    "Mul2",
    "Div2",
    "Pow2",
    "AddScalar",
    "MulScalar",
    "PowScalar",
    "RSubScalar",
    "RDivScalar",
    "RPowScalar",
    "Sign",
    "Minimum2",
    "Maximum2",
    "MinimumScalar",
    "MaximumScalar",
    "LogicalAnd",
    "LogicalOr",
    "LogicalXor",
    "Equal",
    "NotEqual",
    "GreaterEqual",
    "Greater",
    "LessEqual",
    "Less",
    "LogicalAndScalar",
    "LogicalOrScalar",
    "LogicalXorScalar",
    "EqualScalar",
    "NotEqualScalar",
    "GreaterEqualScalar",
    "GreaterScalar",
    "LessEqualScalar",
    "LessScalar",
    "LogicalNot",
    "Constant",
    "Abs",
    "Exp",
    "Log",
    "Identity",
    "BatchMatmul",
    "Concatenate",
    "Split",
    "Stack",
    "Slice",
    "Transpose",
    "Broadcast",
    "OneHot",
    "Flip",
    "Shift",
    "Reshape",
    "MatrixDiag",
    "MatrixDiagPart",
    "Dropout",
    "Rand",
    "Randint",
    "Randn",
    "RandomCrop",
    "RandomFlip",
    "RandomShift",
    "ImageAugmentation",
    "SigmoidCrossEntropy",
    "BinaryCrossEntropy",
    "SoftmaxCrossEntropy",
    "CategoricalCrossEntropy",
    "SquaredError",
    "AbsoluteError",
    "HuberLoss",
    "EpsilonInsensitiveLoss",
    "KLMultinomial",
    "BinarySigmoid",
    "BinaryTanh",
    "BinaryConnectAffine",
    "BinaryConnectConvolution",
    "BinaryWeightAffine",
    "BinaryWeightConvolution",
    "INQAffine",
    "INQConvolution",
    "FixedPointQuantize",
    "Pow2Quantize",
    "TopNError",
    "BinaryError",
    "ConfusionMatrix",
    "VATNoise",
    "Unlink",
    "Sink",
};

void dump_function(nn_network_t *net, nn_function_t *func) {
  int i;
  int *list;

  printf("NNB: Function type:         %s(%d)\n", typenames[func->type],
         func->type);
  list = (int *)NN_GET(net, func->inputs.list);
  for (i = 0; i < func->inputs.size; i++) {
    printf("NNB: Function input[%d]:   Variable id:%d\n", i, *(list + i));
  }
  list = (int *)NN_GET(net, func->outputs.list);
  for (i = 0; i < func->outputs.size; i++) {
    printf("NNB: Function output[%d]:  Variable id:%d\n", i, *(list + i));
  }
  switch (func->type) {
  case NN_FUNCTION_AFFINE: { // Affine
    nn_function_affine_t *f = (nn_function_affine_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
  } break;
  case NN_FUNCTION_CONVOLUTION: { // Convolution
    nn_function_convolution_t *f = (nn_function_convolution_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument dilation: (");
    list = (int *)NN_GET(net, f->dilation.list);
    for (i = 0; i < f->dilation.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument group: %d\n", f->group);
  } break;
  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    nn_function_depthwise_convolution_t *f =
        (nn_function_depthwise_convolution_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument dilation: (");
    list = (int *)NN_GET(net, f->dilation.list);
    for (i = 0; i < f->dilation.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument multiplier: %d\n", f->multiplier);
  } break;
  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    nn_function_deconvolution_t *f = (nn_function_deconvolution_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument dilation: (");
    list = (int *)NN_GET(net, f->dilation.list);
    for (i = 0; i < f->dilation.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument group: %d\n", f->group);
  } break;
  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    nn_function_max_pooling_t *f = (nn_function_max_pooling_t *)func;
    printf("NNB: Function argument kernel: (");
    list = (int *)NN_GET(net, f->kernel.list);
    for (i = 0; i < f->kernel.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument ignore_border: %d\n", f->ignore_border);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    nn_function_average_pooling_t *f = (nn_function_average_pooling_t *)func;
    printf("NNB: Function argument kernel: (");
    list = (int *)NN_GET(net, f->kernel.list);
    for (i = 0; i < f->kernel.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument ignore_border: %d\n", f->ignore_border);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument including_pad: %d\n", f->including_pad);
  } break;
  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    nn_function_sum_pooling_t *f = (nn_function_sum_pooling_t *)func;
    printf("NNB: Function argument kernel: (");
    list = (int *)NN_GET(net, f->kernel.list);
    for (i = 0; i < f->kernel.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument ignore_border: %d\n", f->ignore_border);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_UNPOOLING: { // Unpooling
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)func;
    printf("NNB: Function argument kernel: (");
    list = (int *)NN_GET(net, f->kernel.list);
    for (i = 0; i < f->kernel.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_EMBED: { // Embed
  } break;
  case NN_FUNCTION_SIGMOID: { // Sigmoid
  } break;
  case NN_FUNCTION_SWISH: { // Swish
  } break;
  case NN_FUNCTION_TANH: { // Tanh
  } break;
  case NN_FUNCTION_RELU: { // ReLU
    nn_function_relu_t *f = (nn_function_relu_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    nn_function_leaky_relu_t *f = (nn_function_leaky_relu_t *)func;
    printf("NNB: Function argument alpha: %f\n", f->alpha);
  } break;
  case NN_FUNCTION_SOFTMAX: { // Softmax
    nn_function_softmax_t *f = (nn_function_softmax_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_ELU: { // ELU
    nn_function_elu_t *f = (nn_function_elu_t *)func;
    printf("NNB: Function argument alpha: %f\n", f->alpha);
  } break;
  case NN_FUNCTION_SELU: { // SELU
    nn_function_selu_t *f = (nn_function_selu_t *)func;
    printf("NNB: Function argument scale: %f\n", f->scale);
    printf("NNB: Function argument alpha: %f\n", f->alpha);
  } break;
  case NN_FUNCTION_CRELU: { // CReLU
    nn_function_crelu_t *f = (nn_function_crelu_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_CELU: { // CELU
    nn_function_celu_t *f = (nn_function_celu_t *)func;
    printf("NNB: Function argument alpha: %f\n", f->alpha);
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_PRELU: { // PReLU
    nn_function_prelu_t *f = (nn_function_prelu_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
  } break;
  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    nn_function_batch_normalization_t *f =
        (nn_function_batch_normalization_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument decay_rate: %f\n", f->decay_rate);
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument batch_stat: %d\n", f->batch_stat);
  } break;
  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    nn_function_mean_subtraction_t *f = (nn_function_mean_subtraction_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument update_running_mean: %d\n",
           f->update_running_mean);
  } break;
  case NN_FUNCTION_SUM: { // Sum
    nn_function_sum_t *f = (nn_function_sum_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument keep_dims: %d\n", f->keep_dims);
  } break;
  case NN_FUNCTION_MEAN: { // Mean
    nn_function_mean_t *f = (nn_function_mean_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument keep_dims: %d\n", f->keep_dims);
  } break;
  case NN_FUNCTION_MAX: { // Max
    nn_function_max_t *f = (nn_function_max_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument keep_dims: %d\n", f->keep_dims);
  } break;
  case NN_FUNCTION_MIN: { // Min
    nn_function_min_t *f = (nn_function_min_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument keep_dims: %d\n", f->keep_dims);
  } break;
  case NN_FUNCTION_PROD: { // Prod
    nn_function_prod_t *f = (nn_function_prod_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument keep_dims: %d\n", f->keep_dims);
  } break;
  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
  } break;
  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
  } break;
  case NN_FUNCTION_ADD2: { // Add2
    nn_function_add2_t *f = (nn_function_add2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_BC_ADD2: { // BcAdd2
  } break;
  case NN_FUNCTION_SUB2: { // Sub2
  } break;
  case NN_FUNCTION_MUL2: { // Mul2
  } break;
  case NN_FUNCTION_DIV2: { // Div2
  } break;
  case NN_FUNCTION_POW2: { // Pow2
  } break;
  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    nn_function_add_scalar_t *f = (nn_function_add_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    nn_function_mul_scalar_t *f = (nn_function_mul_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    nn_function_pow_scalar_t *f = (nn_function_pow_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    nn_function_r_sub_scalar_t *f = (nn_function_r_sub_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    nn_function_r_div_scalar_t *f = (nn_function_r_div_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    nn_function_r_pow_scalar_t *f = (nn_function_r_pow_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_SIGN: { // Sign
    nn_function_sign_t *f = (nn_function_sign_t *)func;
    printf("NNB: Function argument alpha: %f\n", f->alpha);
  } break;
  case NN_FUNCTION_MINIMUM2: { // Minimum2
  } break;
  case NN_FUNCTION_MAXIMUM2: { // Maximum2
  } break;
  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    nn_function_minimum_scalar_t *f = (nn_function_minimum_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    nn_function_maximum_scalar_t *f = (nn_function_maximum_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_LOGICAL_AND: { // LogicalAnd
  } break;
  case NN_FUNCTION_LOGICAL_OR: { // LogicalOr
  } break;
  case NN_FUNCTION_LOGICAL_XOR: { // LogicalXor
  } break;
  case NN_FUNCTION_EQUAL: { // Equal
  } break;
  case NN_FUNCTION_NOT_EQUAL: { // NotEqual
  } break;
  case NN_FUNCTION_GREATER_EQUAL: { // GreaterEqual
  } break;
  case NN_FUNCTION_GREATER: { // Greater
  } break;
  case NN_FUNCTION_LESS_EQUAL: { // LessEqual
  } break;
  case NN_FUNCTION_LESS: { // Less
  } break;
  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    nn_function_logical_and_scalar_t *f =
        (nn_function_logical_and_scalar_t *)func;
    printf("NNB: Function argument val: %d\n", f->val);
  } break;
  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    nn_function_logical_or_scalar_t *f =
        (nn_function_logical_or_scalar_t *)func;
    printf("NNB: Function argument val: %d\n", f->val);
  } break;
  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    nn_function_logical_xor_scalar_t *f =
        (nn_function_logical_xor_scalar_t *)func;
    printf("NNB: Function argument val: %d\n", f->val);
  } break;
  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    nn_function_equal_scalar_t *f = (nn_function_equal_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    nn_function_not_equal_scalar_t *f = (nn_function_not_equal_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    nn_function_greater_equal_scalar_t *f =
        (nn_function_greater_equal_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    nn_function_greater_scalar_t *f = (nn_function_greater_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    nn_function_less_equal_scalar_t *f =
        (nn_function_less_equal_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    nn_function_less_scalar_t *f = (nn_function_less_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_LOGICAL_NOT: { // LogicalNot
  } break;
  case NN_FUNCTION_CONSTANT: { // Constant
    nn_function_constant_t *f = (nn_function_constant_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_ABS: { // Abs
  } break;
  case NN_FUNCTION_EXP: { // Exp
  } break;
  case NN_FUNCTION_LOG: { // Log
  } break;
  case NN_FUNCTION_IDENTITY: { // Identity
  } break;
  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    nn_function_batch_matmul_t *f = (nn_function_batch_matmul_t *)func;
    printf("NNB: Function argument transpose_a: %d\n", f->transpose_a);
    printf("NNB: Function argument transpose_b: %d\n", f->transpose_b);
  } break;
  case NN_FUNCTION_CONCATENATE: { // Concatenate
    nn_function_concatenate_t *f = (nn_function_concatenate_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_SPLIT: { // Split
    nn_function_split_t *f = (nn_function_split_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_STACK: { // Stack
    nn_function_stack_t *f = (nn_function_stack_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_SLICE: { // Slice
    nn_function_slice_t *f = (nn_function_slice_t *)func;
    printf("NNB: Function argument start: (");
    list = (int *)NN_GET(net, f->start.list);
    for (i = 0; i < f->start.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stop: (");
    list = (int *)NN_GET(net, f->stop.list);
    for (i = 0; i < f->stop.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument step: (");
    list = (int *)NN_GET(net, f->step.list);
    for (i = 0; i < f->step.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_TRANSPOSE: { // Transpose
    nn_function_transpose_t *f = (nn_function_transpose_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_BROADCAST: { // Broadcast
    nn_function_broadcast_t *f = (nn_function_broadcast_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_ONE_HOT: { // OneHot
    nn_function_one_hot_t *f = (nn_function_one_hot_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_FLIP: { // Flip
    nn_function_flip_t *f = (nn_function_flip_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_SHIFT: { // Shift
    nn_function_shift_t *f = (nn_function_shift_t *)func;
    printf("NNB: Function argument shifts: (");
    list = (int *)NN_GET(net, f->shifts.list);
    for (i = 0; i < f->shifts.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument border_mode: %d\n", f->border_mode);
  } break;
  case NN_FUNCTION_RESHAPE: { // Reshape
    nn_function_reshape_t *f = (nn_function_reshape_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
  } break;
  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
  } break;
  case NN_FUNCTION_DROPOUT: { // Dropout
    nn_function_dropout_t *f = (nn_function_dropout_t *)func;
    printf("NNB: Function argument p: %f\n", f->p);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RAND: { // Rand
    nn_function_rand_t *f = (nn_function_rand_t *)func;
    printf("NNB: Function argument low: %f\n", f->low);
    printf("NNB: Function argument high: %f\n", f->high);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDINT: { // Randint
    nn_function_randint_t *f = (nn_function_randint_t *)func;
    printf("NNB: Function argument low: %d\n", f->low);
    printf("NNB: Function argument high: %d\n", f->high);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDN: { // Randn
    nn_function_randn_t *f = (nn_function_randn_t *)func;
    printf("NNB: Function argument mu: %f\n", f->mu);
    printf("NNB: Function argument sigma: %f\n", f->sigma);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    nn_function_random_crop_t *f = (nn_function_random_crop_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    nn_function_random_flip_t *f = (nn_function_random_flip_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    nn_function_random_shift_t *f = (nn_function_random_shift_t *)func;
    printf("NNB: Function argument shifts: (");
    list = (int *)NN_GET(net, f->shifts.list);
    for (i = 0; i < f->shifts.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument border_mode: %d\n", f->border_mode);
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    nn_function_image_augmentation_t *f =
        (nn_function_image_augmentation_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument min_scale: %f\n", f->min_scale);
    printf("NNB: Function argument max_scale: %f\n", f->max_scale);
    printf("NNB: Function argument angle: %f\n", f->angle);
    printf("NNB: Function argument aspect_ratio: %f\n", f->aspect_ratio);
    printf("NNB: Function argument distortion: %f\n", f->distortion);
    printf("NNB: Function argument flip_lr: %d\n", f->flip_lr);
    printf("NNB: Function argument flip_ud: %d\n", f->flip_ud);
    printf("NNB: Function argument brightness: %f\n", f->brightness);
    printf("NNB: Function argument brightness_each: %d\n", f->brightness_each);
    printf("NNB: Function argument contrast: %f\n", f->contrast);
    printf("NNB: Function argument contrast_center: %f\n", f->contrast_center);
    printf("NNB: Function argument contrast_each: %d\n", f->contrast_each);
    printf("NNB: Function argument noise: %f\n", f->noise);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_SIGMOID_CROSS_ENTROPY: { // SigmoidCrossEntropy
  } break;
  case NN_FUNCTION_BINARY_CROSS_ENTROPY: { // BinaryCrossEntropy
  } break;
  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    nn_function_softmax_cross_entropy_t *f =
        (nn_function_softmax_cross_entropy_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    nn_function_categorical_cross_entropy_t *f =
        (nn_function_categorical_cross_entropy_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_SQUARED_ERROR: { // SquaredError
  } break;
  case NN_FUNCTION_ABSOLUTE_ERROR: { // AbsoluteError
  } break;
  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    nn_function_huber_loss_t *f = (nn_function_huber_loss_t *)func;
    printf("NNB: Function argument delta: %f\n", f->delta);
  } break;
  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    nn_function_epsilon_insensitive_loss_t *f =
        (nn_function_epsilon_insensitive_loss_t *)func;
    printf("NNB: Function argument epsilon: %f\n", f->epsilon);
  } break;
  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    nn_function_kl_multinomial_t *f = (nn_function_kl_multinomial_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
  } break;
  case NN_FUNCTION_BINARY_SIGMOID: { // BinarySigmoid
  } break;
  case NN_FUNCTION_BINARY_TANH: { // BinaryTanh
  } break;
  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    nn_function_binary_connect_affine_t *f =
        (nn_function_binary_connect_affine_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
  } break;
  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    nn_function_binary_connect_convolution_t *f =
        (nn_function_binary_connect_convolution_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument dilation: (");
    list = (int *)NN_GET(net, f->dilation.list);
    for (i = 0; i < f->dilation.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument group: %d\n", f->group);
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    nn_function_binary_weight_convolution_t *f =
        (nn_function_binary_weight_convolution_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument dilation: (");
    list = (int *)NN_GET(net, f->dilation.list);
    for (i = 0; i < f->dilation.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument group: %d\n", f->group);
  } break;
  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    nn_function_inq_affine_t *f = (nn_function_inq_affine_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument num_bits: %d\n", f->num_bits);
    printf("NNB: Function argument inq_iterations: (");
    list = (int *)NN_GET(net, f->inq_iterations.list);
    for (i = 0; i < f->inq_iterations.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument selection_algorithm: %d\n",
           f->selection_algorithm);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    nn_function_inq_convolution_t *f = (nn_function_inq_convolution_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument pad: (");
    list = (int *)NN_GET(net, f->pad.list);
    for (i = 0; i < f->pad.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument stride: (");
    list = (int *)NN_GET(net, f->stride.list);
    for (i = 0; i < f->stride.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument dilation: (");
    list = (int *)NN_GET(net, f->dilation.list);
    for (i = 0; i < f->dilation.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument group: %d\n", f->group);
    printf("NNB: Function argument num_bits: %d\n", f->num_bits);
    printf("NNB: Function argument inq_iterations: (");
    list = (int *)NN_GET(net, f->inq_iterations.list);
    for (i = 0; i < f->inq_iterations.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument selection_algorithm: %d\n",
           f->selection_algorithm);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    nn_function_fixed_point_quantize_t *f =
        (nn_function_fixed_point_quantize_t *)func;
    printf("NNB: Function argument sign: %d\n", f->sign);
    printf("NNB: Function argument n: %d\n", f->n);
    printf("NNB: Function argument delta: %f\n", f->delta);
    printf("NNB: Function argument ste_fine_grained: %d\n",
           f->ste_fine_grained);
  } break;
  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    nn_function_pow2_quantize_t *f = (nn_function_pow2_quantize_t *)func;
    printf("NNB: Function argument sign: %d\n", f->sign);
    printf("NNB: Function argument with_zero: %d\n", f->with_zero);
    printf("NNB: Function argument n: %d\n", f->n);
    printf("NNB: Function argument m: %d\n", f->m);
    printf("NNB: Function argument ste_fine_grained: %d\n",
           f->ste_fine_grained);
  } break;
  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    nn_function_top_n_error_t *f = (nn_function_top_n_error_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
    printf("NNB: Function argument n: %d\n", f->n);
  } break;
  case NN_FUNCTION_BINARY_ERROR: { // BinaryError
  } break;
  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    nn_function_confusion_matrix_t *f = (nn_function_confusion_matrix_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    nn_function_vat_noise_t *f = (nn_function_vat_noise_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument eps: %f\n", f->eps);
  } break;
  case NN_FUNCTION_UNLINK: { // Unlink
  } break;
  case NN_FUNCTION_SINK: { // Sink
    nn_function_sink_t *f = (nn_function_sink_t *)func;
    printf("NNB: Function argument one_input_grad: %d\n", f->one_input_grad);
  } break;
  }
}
