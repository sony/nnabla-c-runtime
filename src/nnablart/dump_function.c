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

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "../runtime/runtime_internal.h"
#include "dump.h"
#include "dump_function.h"

void dump_function(nn_network_t *net, nn_function_t *func) {
  unsigned int i;
  int *list;

  switch (func->type) {
  case NN_FUNCTION_AFFINE: { // Affine
    printf("NNB: Function type:    Affine(0)\n");
  } break;
  case NN_FUNCTION_RNN: { // RNN
    printf("NNB: Function type:    RNN(244)\n");
  } break;
  case NN_FUNCTION_LSTM: { // LSTM
    printf("NNB: Function type:    LSTM(242)\n");
  } break;
  case NN_FUNCTION_GRU: { // GRU
    printf("NNB: Function type:    GRU(243)\n");
  } break;
  case NN_FUNCTION_CONVOLUTION: { // Convolution
    printf("NNB: Function type:    Convolution(1)\n");
  } break;
  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    printf("NNB: Function type:    DepthwiseConvolution(2)\n");
  } break;
  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    printf("NNB: Function type:    Deconvolution(3)\n");
  } break;
  case NN_FUNCTION_DEPTHWISE_DECONVOLUTION: { // DepthwiseDeconvolution
    printf("NNB: Function type:    DepthwiseDeconvolution(4)\n");
  } break;
  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    printf("NNB: Function type:    MaxPooling(5)\n");
  } break;
  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    printf("NNB: Function type:    AveragePooling(6)\n");
  } break;
  case NN_FUNCTION_GLOBAL_AVERAGE_POOLING: { // GlobalAveragePooling
    printf("NNB: Function type:    GlobalAveragePooling(7)\n");
  } break;
  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    printf("NNB: Function type:    SumPooling(8)\n");
  } break;
  case NN_FUNCTION_UNPOOLING: { // Unpooling
    printf("NNB: Function type:    Unpooling(9)\n");
  } break;
  case NN_FUNCTION_EMBED: { // Embed
    printf("NNB: Function type:    Embed(10)\n");
  } break;
  case NN_FUNCTION_SIGMOID: { // Sigmoid
    printf("NNB: Function type:    Sigmoid(11)\n");
  } break;
  case NN_FUNCTION_SWISH: { // Swish
    printf("NNB: Function type:    Swish(12)\n");
  } break;
  case NN_FUNCTION_TANH: { // Tanh
    printf("NNB: Function type:    Tanh(13)\n");
  } break;
  case NN_FUNCTION_RELU: { // ReLU
    printf("NNB: Function type:    ReLU(14)\n");
  } break;
  case NN_FUNCTION_LEAKY_RELU: { // LeakyReLU
    printf("NNB: Function type:    LeakyReLU(128)\n");
  } break;
  case NN_FUNCTION_SOFTMAX: { // Softmax
    printf("NNB: Function type:    Softmax(16)\n");
  } break;
  case NN_FUNCTION_ELU: { // ELU
    printf("NNB: Function type:    ELU(17)\n");
  } break;
  case NN_FUNCTION_SELU: { // SELU
    printf("NNB: Function type:    SELU(18)\n");
  } break;
  case NN_FUNCTION_CRELU: { // CReLU
    printf("NNB: Function type:    CReLU(19)\n");
  } break;
  case NN_FUNCTION_CELU: { // CELU
    printf("NNB: Function type:    CELU(20)\n");
  } break;
  case NN_FUNCTION_PRELU: { // PReLU
    printf("NNB: Function type:    PReLU(21)\n");
  } break;
  case NN_FUNCTION_GELU: { // GELU
    printf("NNB: Function type:    GELU(245)\n");
  } break;
  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    printf("NNB: Function type:    BatchNormalization(22)\n");
  } break;
  case NN_FUNCTION_MEAN_SUBTRACTION: { // MeanSubtraction
    printf("NNB: Function type:    MeanSubtraction(23)\n");
  } break;
  case NN_FUNCTION_CLIP_GRAD_BY_VALUE: { // ClipGradByValue
    printf("NNB: Function type:    ClipGradByValue(121)\n");
  } break;
  case NN_FUNCTION_CLIP_GRAD_BY_NORM: { // ClipGradByNorm
    printf("NNB: Function type:    ClipGradByNorm(122)\n");
  } break;
  case NN_FUNCTION_SUM: { // Sum
    printf("NNB: Function type:    Sum(24)\n");
  } break;
  case NN_FUNCTION_MEAN: { // Mean
    printf("NNB: Function type:    Mean(25)\n");
  } break;
  case NN_FUNCTION_MAX: { // Max
    printf("NNB: Function type:    Max(132)\n");
  } break;
  case NN_FUNCTION_MIN: { // Min
    printf("NNB: Function type:    Min(130)\n");
  } break;
  case NN_FUNCTION_PROD: { // Prod
    printf("NNB: Function type:    Prod(28)\n");
  } break;
  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
    printf("NNB: Function type:    ReduceSum(29)\n");
  } break;
  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
    printf("NNB: Function type:    ReduceMean(30)\n");
  } break;
  case NN_FUNCTION_ADD2: { // Add2
    printf("NNB: Function type:    Add2(31)\n");
  } break;
  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    printf("NNB: Function type:    BcAdd2(32)\n");
  } break;
  case NN_FUNCTION_SUB2: { // Sub2
    printf("NNB: Function type:    Sub2(33)\n");
  } break;
  case NN_FUNCTION_MUL2: { // Mul2
    printf("NNB: Function type:    Mul2(34)\n");
  } break;
  case NN_FUNCTION_DIV2: { // Div2
    printf("NNB: Function type:    Div2(35)\n");
  } break;
  case NN_FUNCTION_POW2: { // Pow2
    printf("NNB: Function type:    Pow2(36)\n");
  } break;
  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    printf("NNB: Function type:    AddScalar(37)\n");
  } break;
  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    printf("NNB: Function type:    MulScalar(38)\n");
  } break;
  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    printf("NNB: Function type:    PowScalar(39)\n");
  } break;
  case NN_FUNCTION_R_SUB_SCALAR: { // RSubScalar
    printf("NNB: Function type:    RSubScalar(40)\n");
  } break;
  case NN_FUNCTION_R_DIV_SCALAR: { // RDivScalar
    printf("NNB: Function type:    RDivScalar(41)\n");
  } break;
  case NN_FUNCTION_R_POW_SCALAR: { // RPowScalar
    printf("NNB: Function type:    RPowScalar(42)\n");
  } break;
  case NN_FUNCTION_SIGN: { // Sign
    printf("NNB: Function type:    Sign(43)\n");
  } break;
  case NN_FUNCTION_MINIMUM2: { // Minimum2
    printf("NNB: Function type:    Minimum2(44)\n");
  } break;
  case NN_FUNCTION_MAXIMUM2: { // Maximum2
    printf("NNB: Function type:    Maximum2(45)\n");
  } break;
  case NN_FUNCTION_MINIMUM_SCALAR: { // MinimumScalar
    printf("NNB: Function type:    MinimumScalar(46)\n");
  } break;
  case NN_FUNCTION_MAXIMUM_SCALAR: { // MaximumScalar
    printf("NNB: Function type:    MaximumScalar(47)\n");
  } break;
  case NN_FUNCTION_LOGICAL_AND: { // LogicalAnd
    printf("NNB: Function type:    LogicalAnd(48)\n");
  } break;
  case NN_FUNCTION_LOGICAL_OR: { // LogicalOr
    printf("NNB: Function type:    LogicalOr(49)\n");
  } break;
  case NN_FUNCTION_LOGICAL_XOR: { // LogicalXor
    printf("NNB: Function type:    LogicalXor(50)\n");
  } break;
  case NN_FUNCTION_EQUAL: { // Equal
    printf("NNB: Function type:    Equal(51)\n");
  } break;
  case NN_FUNCTION_NOT_EQUAL: { // NotEqual
    printf("NNB: Function type:    NotEqual(52)\n");
  } break;
  case NN_FUNCTION_GREATER_EQUAL: { // GreaterEqual
    printf("NNB: Function type:    GreaterEqual(53)\n");
  } break;
  case NN_FUNCTION_GREATER: { // Greater
    printf("NNB: Function type:    Greater(54)\n");
  } break;
  case NN_FUNCTION_LESS_EQUAL: { // LessEqual
    printf("NNB: Function type:    LessEqual(55)\n");
  } break;
  case NN_FUNCTION_LESS: { // Less
    printf("NNB: Function type:    Less(56)\n");
  } break;
  case NN_FUNCTION_LOGICAL_AND_SCALAR: { // LogicalAndScalar
    printf("NNB: Function type:    LogicalAndScalar(57)\n");
  } break;
  case NN_FUNCTION_LOGICAL_OR_SCALAR: { // LogicalOrScalar
    printf("NNB: Function type:    LogicalOrScalar(58)\n");
  } break;
  case NN_FUNCTION_LOGICAL_XOR_SCALAR: { // LogicalXorScalar
    printf("NNB: Function type:    LogicalXorScalar(59)\n");
  } break;
  case NN_FUNCTION_EQUAL_SCALAR: { // EqualScalar
    printf("NNB: Function type:    EqualScalar(60)\n");
  } break;
  case NN_FUNCTION_NOT_EQUAL_SCALAR: { // NotEqualScalar
    printf("NNB: Function type:    NotEqualScalar(61)\n");
  } break;
  case NN_FUNCTION_GREATER_EQUAL_SCALAR: { // GreaterEqualScalar
    printf("NNB: Function type:    GreaterEqualScalar(62)\n");
  } break;
  case NN_FUNCTION_GREATER_SCALAR: { // GreaterScalar
    printf("NNB: Function type:    GreaterScalar(63)\n");
  } break;
  case NN_FUNCTION_LESS_EQUAL_SCALAR: { // LessEqualScalar
    printf("NNB: Function type:    LessEqualScalar(64)\n");
  } break;
  case NN_FUNCTION_LESS_SCALAR: { // LessScalar
    printf("NNB: Function type:    LessScalar(65)\n");
  } break;
  case NN_FUNCTION_LOGICAL_NOT: { // LogicalNot
    printf("NNB: Function type:    LogicalNot(66)\n");
  } break;
  case NN_FUNCTION_ISNAN: { // IsNaN
    printf("NNB: Function type:    IsNaN(236)\n");
  } break;
  case NN_FUNCTION_ISINF: { // IsInf
    printf("NNB: Function type:    IsInf(237)\n");
  } break;
  case NN_FUNCTION_RESET_NAN: { // ResetNaN
    printf("NNB: Function type:    ResetNaN(238)\n");
  } break;
  case NN_FUNCTION_RESET_INF: { // ResetInf
    printf("NNB: Function type:    ResetInf(239)\n");
  } break;
  case NN_FUNCTION_WHERE: { // Where
    printf("NNB: Function type:    Where(240)\n");
  } break;
  case NN_FUNCTION_CONSTANT: { // Constant
    printf("NNB: Function type:    Constant(67)\n");
  } break;
  case NN_FUNCTION_ARANGE: { // Arange
    printf("NNB: Function type:    Arange(131)\n");
  } break;
  case NN_FUNCTION_ABS: { // Abs
    printf("NNB: Function type:    Abs(68)\n");
  } break;
  case NN_FUNCTION_EXP: { // Exp
    printf("NNB: Function type:    Exp(69)\n");
  } break;
  case NN_FUNCTION_LOG: { // Log
    printf("NNB: Function type:    Log(70)\n");
  } break;
  case NN_FUNCTION_IDENTITY: { // Identity
    printf("NNB: Function type:    Identity(71)\n");
  } break;
  case NN_FUNCTION_BATCH_MATMUL: { // BatchMatmul
    printf("NNB: Function type:    BatchMatmul(72)\n");
  } break;
  case NN_FUNCTION_ROUND: { // Round
    printf("NNB: Function type:    Round(73)\n");
  } break;
  case NN_FUNCTION_CEIL: { // Ceil
    printf("NNB: Function type:    Ceil(124)\n");
  } break;
  case NN_FUNCTION_FLOOR: { // Floor
    printf("NNB: Function type:    Floor(125)\n");
  } break;
  case NN_FUNCTION_SIN: { // Sin
    printf("NNB: Function type:    Sin(173)\n");
  } break;
  case NN_FUNCTION_COS: { // Cos
    printf("NNB: Function type:    Cos(174)\n");
  } break;
  case NN_FUNCTION_TAN: { // Tan
    printf("NNB: Function type:    Tan(175)\n");
  } break;
  case NN_FUNCTION_SINH: { // Sinh
    printf("NNB: Function type:    Sinh(176)\n");
  } break;
  case NN_FUNCTION_COSH: { // Cosh
    printf("NNB: Function type:    Cosh(177)\n");
  } break;
  case NN_FUNCTION_ASIN: { // ASin
    printf("NNB: Function type:    ASin(178)\n");
  } break;
  case NN_FUNCTION_ACOS: { // ACos
    printf("NNB: Function type:    ACos(179)\n");
  } break;
  case NN_FUNCTION_ATAN: { // ATan
    printf("NNB: Function type:    ATan(180)\n");
  } break;
  case NN_FUNCTION_ATAN2: { // ATan2
    printf("NNB: Function type:    ATan2(241)\n");
  } break;
  case NN_FUNCTION_ASINH: { // ASinh
    printf("NNB: Function type:    ASinh(181)\n");
  } break;
  case NN_FUNCTION_ACOSH: { // ACosh
    printf("NNB: Function type:    ACosh(182)\n");
  } break;
  case NN_FUNCTION_ATANH: { // ATanh
    printf("NNB: Function type:    ATanh(183)\n");
  } break;
  case NN_FUNCTION_CONCATENATE: { // Concatenate
    printf("NNB: Function type:    Concatenate(74)\n");
  } break;
  case NN_FUNCTION_SPLIT: { // Split
    printf("NNB: Function type:    Split(75)\n");
  } break;
  case NN_FUNCTION_STACK: { // Stack
    printf("NNB: Function type:    Stack(76)\n");
  } break;
  case NN_FUNCTION_SLICE: { // Slice
    printf("NNB: Function type:    Slice(77)\n");
  } break;
  case NN_FUNCTION_PAD: { // Pad
    printf("NNB: Function type:    Pad(123)\n");
  } break;
  case NN_FUNCTION_TRANSPOSE: { // Transpose
    printf("NNB: Function type:    Transpose(78)\n");
  } break;
  case NN_FUNCTION_BROADCAST: { // Broadcast
    printf("NNB: Function type:    Broadcast(79)\n");
  } break;
  case NN_FUNCTION_BROADCAST_TO: { // BroadcastTo
    printf("NNB: Function type:    BroadcastTo(184)\n");
  } break;
  case NN_FUNCTION_ONE_HOT: { // OneHot
    printf("NNB: Function type:    OneHot(80)\n");
  } break;
  case NN_FUNCTION_FLIP: { // Flip
    printf("NNB: Function type:    Flip(81)\n");
  } break;
  case NN_FUNCTION_SHIFT: { // Shift
    printf("NNB: Function type:    Shift(82)\n");
  } break;
  case NN_FUNCTION_SORT: { // Sort
    printf("NNB: Function type:    Sort(129)\n");
  } break;
  case NN_FUNCTION_RESHAPE: { // Reshape
    printf("NNB: Function type:    Reshape(126)\n");
  } break;
  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
    printf("NNB: Function type:    MatrixDiag(84)\n");
  } break;
  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
    printf("NNB: Function type:    MatrixDiagPart(85)\n");
  } break;
  case NN_FUNCTION_INTERPOLATE: { // Interpolate
    printf("NNB: Function type:    Interpolate(127)\n");
  } break;
  case NN_FUNCTION_FFT: { // FFT
    printf("NNB: Function type:    FFT(158)\n");
  } break;
  case NN_FUNCTION_IFFT: { // IFFT
    printf("NNB: Function type:    IFFT(159)\n");
  } break;
  case NN_FUNCTION_DROPOUT: { // Dropout
    printf("NNB: Function type:    Dropout(86)\n");
  } break;
  case NN_FUNCTION_TOP_K_DATA: { // TopKData
    printf("NNB: Function type:    TopKData(87)\n");
  } break;
  case NN_FUNCTION_TOP_K_GRAD: { // TopKGrad
    printf("NNB: Function type:    TopKGrad(88)\n");
  } break;
  case NN_FUNCTION_RAND: { // Rand
    printf("NNB: Function type:    Rand(89)\n");
  } break;
  case NN_FUNCTION_RANDINT: { // Randint
    printf("NNB: Function type:    Randint(90)\n");
  } break;
  case NN_FUNCTION_RANDN: { // Randn
    printf("NNB: Function type:    Randn(91)\n");
  } break;
  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    printf("NNB: Function type:    RandomCrop(92)\n");
  } break;
  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    printf("NNB: Function type:    RandomFlip(93)\n");
  } break;
  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    printf("NNB: Function type:    RandomShift(94)\n");
  } break;
  case NN_FUNCTION_IMAGE_AUGMENTATION: { // ImageAugmentation
    printf("NNB: Function type:    ImageAugmentation(95)\n");
  } break;
  case NN_FUNCTION_SIGMOID_CROSS_ENTROPY: { // SigmoidCrossEntropy
    printf("NNB: Function type:    SigmoidCrossEntropy(96)\n");
  } break;
  case NN_FUNCTION_BINARY_CROSS_ENTROPY: { // BinaryCrossEntropy
    printf("NNB: Function type:    BinaryCrossEntropy(97)\n");
  } break;
  case NN_FUNCTION_SOFTMAX_CROSS_ENTROPY: { // SoftmaxCrossEntropy
    printf("NNB: Function type:    SoftmaxCrossEntropy(98)\n");
  } break;
  case NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY: { // CategoricalCrossEntropy
    printf("NNB: Function type:    CategoricalCrossEntropy(99)\n");
  } break;
  case NN_FUNCTION_SQUARED_ERROR: { // SquaredError
    printf("NNB: Function type:    SquaredError(100)\n");
  } break;
  case NN_FUNCTION_ABSOLUTE_ERROR: { // AbsoluteError
    printf("NNB: Function type:    AbsoluteError(101)\n");
  } break;
  case NN_FUNCTION_HUBER_LOSS: { // HuberLoss
    printf("NNB: Function type:    HuberLoss(102)\n");
  } break;
  case NN_FUNCTION_EPSILON_INSENSITIVE_LOSS: { // EpsilonInsensitiveLoss
    printf("NNB: Function type:    EpsilonInsensitiveLoss(103)\n");
  } break;
  case NN_FUNCTION_KL_MULTINOMIAL: { // KLMultinomial
    printf("NNB: Function type:    KLMultinomial(104)\n");
  } break;
  case NN_FUNCTION_BINARY_SIGMOID: { // BinarySigmoid
    printf("NNB: Function type:    BinarySigmoid(105)\n");
  } break;
  case NN_FUNCTION_BINARY_TANH: { // BinaryTanh
    printf("NNB: Function type:    BinaryTanh(106)\n");
  } break;
  case NN_FUNCTION_BINARY_CONNECT_AFFINE: { // BinaryConnectAffine
    printf("NNB: Function type:    BinaryConnectAffine(235)\n");
  } break;
  case NN_FUNCTION_BINARY_CONNECT_CONVOLUTION: { // BinaryConnectConvolution
    printf("NNB: Function type:    BinaryConnectConvolution(233)\n");
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    printf("NNB: Function type:    BinaryWeightAffine(234)\n");
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION: { // BinaryWeightConvolution
    printf("NNB: Function type:    BinaryWeightConvolution(232)\n");
  } break;
  case NN_FUNCTION_INQ_AFFINE: { // INQAffine
    printf("NNB: Function type:    INQAffine(111)\n");
  } break;
  case NN_FUNCTION_INQ_CONVOLUTION: { // INQConvolution
    printf("NNB: Function type:    INQConvolution(112)\n");
  } break;
  case NN_FUNCTION_FIXED_POINT_QUANTIZE: { // FixedPointQuantize
    printf("NNB: Function type:    FixedPointQuantize(113)\n");
  } break;
  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    printf("NNB: Function type:    Pow2Quantize(114)\n");
  } break;
  case NN_FUNCTION_PRUNE: { // Prune
    printf("NNB: Function type:    Prune(135)\n");
  } break;
  case NN_FUNCTION_TOP_N_ERROR: { // TopNError
    printf("NNB: Function type:    TopNError(115)\n");
  } break;
  case NN_FUNCTION_BINARY_ERROR: { // BinaryError
    printf("NNB: Function type:    BinaryError(116)\n");
  } break;
  case NN_FUNCTION_CONFUSION_MATRIX: { // ConfusionMatrix
    printf("NNB: Function type:    ConfusionMatrix(117)\n");
  } break;
  case NN_FUNCTION_VAT_NOISE: { // VATNoise
    printf("NNB: Function type:    VATNoise(118)\n");
  } break;
  case NN_FUNCTION_UNLINK: { // Unlink
    printf("NNB: Function type:    Unlink(119)\n");
  } break;
  case NN_FUNCTION_SINK: { // Sink
    printf("NNB: Function type:    Sink(120)\n");
  } break;
  case NN_FUNCTION_NMS_DETECTION2D: { // NmsDetection2d
    printf("NNB: Function type:    NmsDetection2d(231)\n");
  } break;
  default:;
  }

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
  case NN_FUNCTION_RNN: { // RNN
    nn_function_rnn_t *f = (nn_function_rnn_t *)func;
    printf("NNB: Function argument num_layers: %d\n", f->num_layers);
    printf("NNB: Function argument nonlinearity: %d\n", f->nonlinearity);
    printf("NNB: Function argument dropout: %f\n", f->dropout);
    printf("NNB: Function argument bidirectional: %d\n", f->bidirectional);
    printf("NNB: Function argument training: %d\n", f->training);
  } break;
  case NN_FUNCTION_LSTM: { // LSTM
    nn_function_lstm_t *f = (nn_function_lstm_t *)func;
    printf("NNB: Function argument num_layers: %d\n", f->num_layers);
    printf("NNB: Function argument dropout: %f\n", f->dropout);
    printf("NNB: Function argument bidirectional: %d\n", f->bidirectional);
    printf("NNB: Function argument training: %d\n", f->training);
  } break;
  case NN_FUNCTION_GRU: { // GRU
    nn_function_gru_t *f = (nn_function_gru_t *)func;
    printf("NNB: Function argument num_layers: %d\n", f->num_layers);
    printf("NNB: Function argument dropout: %f\n", f->dropout);
    printf("NNB: Function argument bidirectional: %d\n", f->bidirectional);
    printf("NNB: Function argument training: %d\n", f->training);
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
  case NN_FUNCTION_DEPTHWISE_DECONVOLUTION: { // DepthwiseDeconvolution
    nn_function_depthwise_deconvolution_t *f =
        (nn_function_depthwise_deconvolution_t *)func;
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
    printf("NNB: Function argument divisor: %d\n", f->divisor);
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
  case NN_FUNCTION_GLOBAL_AVERAGE_POOLING: { // GlobalAveragePooling
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
    printf("NNB: Function argument inplace: %d\n", f->inplace);
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
  case NN_FUNCTION_GELU: { // GELU
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
  case NN_FUNCTION_CLIP_GRAD_BY_VALUE: { // ClipGradByValue
  } break;
  case NN_FUNCTION_CLIP_GRAD_BY_NORM: { // ClipGradByNorm
    nn_function_clip_grad_by_norm_t *f =
        (nn_function_clip_grad_by_norm_t *)func;
    printf("NNB: Function argument clip_norm: %f\n", f->clip_norm);
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
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
    printf("NNB: Function argument with_index: %d\n", f->with_index);
    printf("NNB: Function argument only_index: %d\n", f->only_index);
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
    printf("NNB: Function argument with_index: %d\n", f->with_index);
    printf("NNB: Function argument only_index: %d\n", f->only_index);
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
  case NN_FUNCTION_ISNAN: { // IsNaN
  } break;
  case NN_FUNCTION_ISINF: { // IsInf
  } break;
  case NN_FUNCTION_RESET_NAN: { // ResetNaN
    nn_function_reset_nan_t *f = (nn_function_reset_nan_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_RESET_INF: { // ResetInf
    nn_function_reset_inf_t *f = (nn_function_reset_inf_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
  } break;
  case NN_FUNCTION_WHERE: { // Where
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
  case NN_FUNCTION_ARANGE: { // Arange
    nn_function_arange_t *f = (nn_function_arange_t *)func;
    printf("NNB: Function argument start: %f\n", f->start);
    printf("NNB: Function argument stop: %f\n", f->stop);
    printf("NNB: Function argument step: %f\n", f->step);
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
  case NN_FUNCTION_ROUND: { // Round
  } break;
  case NN_FUNCTION_CEIL: { // Ceil
  } break;
  case NN_FUNCTION_FLOOR: { // Floor
  } break;
  case NN_FUNCTION_SIN: { // Sin
  } break;
  case NN_FUNCTION_COS: { // Cos
  } break;
  case NN_FUNCTION_TAN: { // Tan
  } break;
  case NN_FUNCTION_SINH: { // Sinh
  } break;
  case NN_FUNCTION_COSH: { // Cosh
  } break;
  case NN_FUNCTION_ASIN: { // ASin
  } break;
  case NN_FUNCTION_ACOS: { // ACos
  } break;
  case NN_FUNCTION_ATAN: { // ATan
  } break;
  case NN_FUNCTION_ATAN2: { // ATan2
  } break;
  case NN_FUNCTION_ASINH: { // ASinh
  } break;
  case NN_FUNCTION_ACOSH: { // ACosh
  } break;
  case NN_FUNCTION_ATANH: { // ATanh
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
  case NN_FUNCTION_PAD: { // Pad
    nn_function_pad_t *f = (nn_function_pad_t *)func;
    printf("NNB: Function argument pad_width: (");
    list = (int *)NN_GET(net, f->pad_width.list);
    for (i = 0; i < f->pad_width.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument mode: %d\n", f->mode);
    printf("NNB: Function argument constant_value: %f\n", f->constant_value);
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
  case NN_FUNCTION_BROADCAST_TO: { // BroadcastTo
    nn_function_broadcast_to_t *f = (nn_function_broadcast_to_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
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
  case NN_FUNCTION_SORT: { // Sort
    nn_function_sort_t *f = (nn_function_sort_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
    printf("NNB: Function argument reverse: %d\n", f->reverse);
    printf("NNB: Function argument with_index: %d\n", f->with_index);
    printf("NNB: Function argument only_index: %d\n", f->only_index);
  } break;
  case NN_FUNCTION_RESHAPE: { // Reshape
    nn_function_reshape_t *f = (nn_function_reshape_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
  } break;
  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
  } break;
  case NN_FUNCTION_INTERPOLATE: { // Interpolate
    nn_function_interpolate_t *f = (nn_function_interpolate_t *)func;
    printf("NNB: Function argument output_size: (");
    list = (int *)NN_GET(net, f->output_size.list);
    for (i = 0; i < f->output_size.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument mode: %d\n", f->mode);
    printf("NNB: Function argument align_corners: %d\n", f->align_corners);
  } break;
  case NN_FUNCTION_FFT: { // FFT
    nn_function_fft_t *f = (nn_function_fft_t *)func;
    printf("NNB: Function argument signal_ndim: %d\n", f->signal_ndim);
    printf("NNB: Function argument normalized: %d\n", f->normalized);
  } break;
  case NN_FUNCTION_IFFT: { // IFFT
    nn_function_ifft_t *f = (nn_function_ifft_t *)func;
    printf("NNB: Function argument signal_ndim: %d\n", f->signal_ndim);
    printf("NNB: Function argument normalized: %d\n", f->normalized);
  } break;
  case NN_FUNCTION_DROPOUT: { // Dropout
    nn_function_dropout_t *f = (nn_function_dropout_t *)func;
    printf("NNB: Function argument p: %f\n", f->p);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_TOP_K_DATA: { // TopKData
    nn_function_top_k_data_t *f = (nn_function_top_k_data_t *)func;
    printf("NNB: Function argument k: %d\n", f->k);
    printf("NNB: Function argument abs: %d\n", f->abs);
    printf("NNB: Function argument reduce: %d\n", f->reduce);
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
  } break;
  case NN_FUNCTION_TOP_K_GRAD: { // TopKGrad
    nn_function_top_k_grad_t *f = (nn_function_top_k_grad_t *)func;
    printf("NNB: Function argument k: %d\n", f->k);
    printf("NNB: Function argument abs: %d\n", f->abs);
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
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
    printf("NNB: Function argument quantize_zero_to: %f\n",
           f->quantize_zero_to);
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
    printf("NNB: Function argument quantize_zero_to: %f\n",
           f->quantize_zero_to);
  } break;
  case NN_FUNCTION_BINARY_WEIGHT_AFFINE: { // BinaryWeightAffine
    nn_function_binary_weight_affine_t *f =
        (nn_function_binary_weight_affine_t *)func;
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument quantize_zero_to: %f\n",
           f->quantize_zero_to);
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
    printf("NNB: Function argument quantize_zero_to: %f\n",
           f->quantize_zero_to);
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
  case NN_FUNCTION_PRUNE: { // Prune
    nn_function_prune_t *f = (nn_function_prune_t *)func;
    printf("NNB: Function argument rate: %f\n", f->rate);
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
  case NN_FUNCTION_NMS_DETECTION2D: { // NmsDetection2d
    nn_function_nms_detection2d_t *f = (nn_function_nms_detection2d_t *)func;
    printf("NNB: Function argument thresh: %f\n", f->thresh);
    printf("NNB: Function argument nms: %f\n", f->nms);
    printf("NNB: Function argument nms_per_class: %d\n", f->nms_per_class);
  } break;
  default:;
  }
}
