// Copyright 2018,2019,2020,2021 Sony Corporation.
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
    printf("NNB: Function type:    Convolution(265)\n");
  } break;
  case NN_FUNCTION_FUSED_CONVOLUTION: { // FusedConvolution
    printf("NNB: Function type:    FusedConvolution(346)\n");
  } break;
  case NN_FUNCTION_DEPTHWISE_CONVOLUTION: { // DepthwiseConvolution
    printf("NNB: Function type:    DepthwiseConvolution(2)\n");
  } break;
  case NN_FUNCTION_DECONVOLUTION: { // Deconvolution
    printf("NNB: Function type:    Deconvolution(292)\n");
  } break;
  case NN_FUNCTION_DEPTHWISE_DECONVOLUTION: { // DepthwiseDeconvolution
    printf("NNB: Function type:    DepthwiseDeconvolution(4)\n");
  } break;
  case NN_FUNCTION_DEFORMABLE_CONVOLUTION: { // DeformableConvolution
    printf("NNB: Function type:    DeformableConvolution(329)\n");
  } break;
  case NN_FUNCTION_ADAPTIVE_SEPARABLE_CONVOLUTION: { // AdaptiveSeparableConvolution
    printf("NNB: Function type:    AdaptiveSeparableConvolution(278)\n");
  } break;
  case NN_FUNCTION_MAX_POOLING: { // MaxPooling
    printf("NNB: Function type:    MaxPooling(266)\n");
  } break;
  case NN_FUNCTION_AVERAGE_POOLING: { // AveragePooling
    printf("NNB: Function type:    AveragePooling(267)\n");
  } break;
  case NN_FUNCTION_GLOBAL_AVERAGE_POOLING: { // GlobalAveragePooling
    printf("NNB: Function type:    GlobalAveragePooling(7)\n");
  } break;
  case NN_FUNCTION_SUM_POOLING: { // SumPooling
    printf("NNB: Function type:    SumPooling(268)\n");
  } break;
  case NN_FUNCTION_UNPOOLING: { // Unpooling
    printf("NNB: Function type:    Unpooling(287)\n");
  } break;
  case NN_FUNCTION_EMBED: { // Embed
    printf("NNB: Function type:    Embed(10)\n");
  } break;
  case NN_FUNCTION_ROI_ALIGN: { // RoiAlign
    printf("NNB: Function type:    RoiAlign(338)\n");
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
  case NN_FUNCTION_LOG_SOFTMAX: { // LogSoftmax
    printf("NNB: Function type:    LogSoftmax(269)\n");
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
  case NN_FUNCTION_MISH: { // Mish
    printf("NNB: Function type:    Mish(298)\n");
  } break;
  case NN_FUNCTION_RELU6: { // ReLU6
    printf("NNB: Function type:    ReLU6(256)\n");
  } break;
  case NN_FUNCTION_HARD_SIGMOID: { // HardSigmoid
    printf("NNB: Function type:    HardSigmoid(259)\n");
  } break;
  case NN_FUNCTION_HARD_TANH: { // HardTanh
    printf("NNB: Function type:    HardTanh(261)\n");
  } break;
  case NN_FUNCTION_LOG_SIGMOID: { // LogSigmoid
    printf("NNB: Function type:    LogSigmoid(251)\n");
  } break;
  case NN_FUNCTION_SOFTPLUS: { // SoftPlus
    printf("NNB: Function type:    SoftPlus(335)\n");
  } break;
  case NN_FUNCTION_SOFTSIGN: { // SoftSign
    printf("NNB: Function type:    SoftSign(253)\n");
  } break;
  case NN_FUNCTION_TANH_SHRINK: { // TanhShrink
    printf("NNB: Function type:    TanhShrink(254)\n");
  } break;
  case NN_FUNCTION_SINC: { // Sinc
    printf("NNB: Function type:    Sinc(255)\n");
  } break;
  case NN_FUNCTION_FUSED_BATCH_NORMALIZATION: { // FusedBatchNormalization
    printf("NNB: Function type:    FusedBatchNormalization(270)\n");
  } break;
  case NN_FUNCTION_BATCH_NORMALIZATION: { // BatchNormalization
    printf("NNB: Function type:    BatchNormalization(326)\n");
  } break;
  case NN_FUNCTION_GROUP_NORMALIZATION: { // GroupNormalization
    printf("NNB: Function type:    GroupNormalization(321)\n");
  } break;
  case NN_FUNCTION_INSTANCE_NORMALIZATION: { // InstanceNormalization
    printf("NNB: Function type:    InstanceNormalization(322)\n");
  } break;
  case NN_FUNCTION_LAYER_NORMALIZATION: { // LayerNormalization
    printf("NNB: Function type:    LayerNormalization(323)\n");
  } break;
  case NN_FUNCTION_NORM_NORMALIZATION: { // NormNormalization
    printf("NNB: Function type:    NormNormalization(317)\n");
  } break;
  case NN_FUNCTION_SYNC_BATCH_NORMALIZATION: { // SyncBatchNormalization
    printf("NNB: Function type:    SyncBatchNormalization(263)\n");
  } break;
  case NN_FUNCTION_TENSOR_NORMALIZATION: { // TensorNormalization
    printf("NNB: Function type:    TensorNormalization(324)\n");
  } break;
  case NN_FUNCTION_WEIGHT_NORMALIZATION: { // WeightNormalization
    printf("NNB: Function type:    WeightNormalization(304)\n");
  } break;
  case NN_FUNCTION_WEIGHT_STANDARDIZATION: { // WeightStandardization
    printf("NNB: Function type:    WeightStandardization(325)\n");
  } break;
  case NN_FUNCTION_SPECTRAL_NORM: { // SpectralNorm
    printf("NNB: Function type:    SpectralNorm(337)\n");
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
  case NN_FUNCTION_CUMSUM: { // CumSum
    printf("NNB: Function type:    CumSum(331)\n");
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
  case NN_FUNCTION_NORM: { // Norm
    printf("NNB: Function type:    Norm(318)\n");
  } break;
  case NN_FUNCTION_PROD: { // Prod
    printf("NNB: Function type:    Prod(28)\n");
  } break;
  case NN_FUNCTION_CUMPROD: { // CumProd
    printf("NNB: Function type:    CumProd(332)\n");
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
  case NN_FUNCTION_ADD_N: { // AddN
    printf("NNB: Function type:    AddN(281)\n");
  } break;
  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    printf("NNB: Function type:    BcAdd2(307)\n");
  } break;
  case NN_FUNCTION_SUB2: { // Sub2
    printf("NNB: Function type:    Sub2(308)\n");
  } break;
  case NN_FUNCTION_MUL2: { // Mul2
    printf("NNB: Function type:    Mul2(309)\n");
  } break;
  case NN_FUNCTION_MUL_N: { // MulN
    printf("NNB: Function type:    MulN(282)\n");
  } break;
  case NN_FUNCTION_DIV2: { // Div2
    printf("NNB: Function type:    Div2(310)\n");
  } break;
  case NN_FUNCTION_POW2: { // Pow2
    printf("NNB: Function type:    Pow2(311)\n");
  } break;
  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    printf("NNB: Function type:    AddScalar(312)\n");
  } break;
  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    printf("NNB: Function type:    MulScalar(313)\n");
  } break;
  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    printf("NNB: Function type:    PowScalar(314)\n");
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
  case NN_FUNCTION_SEARCHSORTED: { // SearchSorted
    printf("NNB: Function type:    SearchSorted(333)\n");
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
  case NN_FUNCTION_LINSPACE: { // Linspace
    printf("NNB: Function type:    Linspace(343)\n");
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
  case NN_FUNCTION_ERF: { // Erf
    printf("NNB: Function type:    Erf(349)\n");
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
  case NN_FUNCTION_TILE: { // Tile
    printf("NNB: Function type:    Tile(247)\n");
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
  case NN_FUNCTION_SHAPE: { // Shape
    printf("NNB: Function type:    Shape(348)\n");
  } break;
  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
    printf("NNB: Function type:    MatrixDiag(84)\n");
  } break;
  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
    printf("NNB: Function type:    MatrixDiagPart(85)\n");
  } break;
  case NN_FUNCTION_MESHGRID: { // Meshgrid
    printf("NNB: Function type:    Meshgrid(334)\n");
  } break;
  case NN_FUNCTION_BATCH_DET: { // BatchDet
    printf("NNB: Function type:    BatchDet(276)\n");
  } break;
  case NN_FUNCTION_BATCH_INV: { // BatchInv
    printf("NNB: Function type:    BatchInv(275)\n");
  } break;
  case NN_FUNCTION_BATCH_LOGDET: { // BatchLogdet
    printf("NNB: Function type:    BatchLogdet(319)\n");
  } break;
  case NN_FUNCTION_BATCH_CHOLESKY: { // BatchCholesky
    printf("NNB: Function type:    BatchCholesky(347)\n");
  } break;
  case NN_FUNCTION_ASSIGN: { // Assign
    printf("NNB: Function type:    Assign(248)\n");
  } break;
  case NN_FUNCTION_GATHER: { // Gather
    printf("NNB: Function type:    Gather(303)\n");
  } break;
  case NN_FUNCTION_GATHER_ND: { // GatherNd
    printf("NNB: Function type:    GatherNd(264)\n");
  } break;
  case NN_FUNCTION_BOOL_GATHER: { // BoolGather
    printf("NNB: Function type:    BoolGather(339)\n");
  } break;
  case NN_FUNCTION_SCATTER_ND: { // ScatterNd
    printf("NNB: Function type:    ScatterNd(342)\n");
  } break;
  case NN_FUNCTION_SCATTER_ADD: { // ScatterAdd
    printf("NNB: Function type:    ScatterAdd(315)\n");
  } break;
  case NN_FUNCTION_BOOL_SCATTER: { // BoolScatter
    printf("NNB: Function type:    BoolScatter(340)\n");
  } break;
  case NN_FUNCTION_BOOL_FILL: { // BoolFill
    printf("NNB: Function type:    BoolFill(341)\n");
  } break;
  case NN_FUNCTION_PACK_PADDED_SEQUENCE: { // PackPaddedSequence
    printf("NNB: Function type:    PackPaddedSequence(305)\n");
  } break;
  case NN_FUNCTION_PAD_PACKED_SEQUENCE: { // PadPackedSequence
    printf("NNB: Function type:    PadPackedSequence(306)\n");
  } break;
  case NN_FUNCTION_NONZERO: { // NonZero
    printf("NNB: Function type:    NonZero(351)\n");
  } break;
  case NN_FUNCTION_INTERPOLATE: { // Interpolate
    printf("NNB: Function type:    Interpolate(291)\n");
  } break;
  case NN_FUNCTION_ONNX_RESIZE: { // ONNXResize
    printf("NNB: Function type:    ONNXResize(352)\n");
  } break;
  case NN_FUNCTION_FFT: { // FFT
    printf("NNB: Function type:    FFT(158)\n");
  } break;
  case NN_FUNCTION_IFFT: { // IFFT
    printf("NNB: Function type:    IFFT(159)\n");
  } break;
  case NN_FUNCTION_STFT: { // STFT
    printf("NNB: Function type:    STFT(344)\n");
  } break;
  case NN_FUNCTION_ISTFT: { // ISTFT
    printf("NNB: Function type:    ISTFT(345)\n");
  } break;
  case NN_FUNCTION_DROPOUT: { // Dropout
    printf("NNB: Function type:    Dropout(336)\n");
  } break;
  case NN_FUNCTION_TOP_K_DATA: { // TopKData
    printf("NNB: Function type:    TopKData(350)\n");
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
  case NN_FUNCTION_RAND_BINOMIAL: { // RandBinomial
    printf("NNB: Function type:    RandBinomial(289)\n");
  } break;
  case NN_FUNCTION_RAND_BETA: { // RandBeta
    printf("NNB: Function type:    RandBeta(288)\n");
  } break;
  case NN_FUNCTION_RAND_GAMMA: { // RandGamma
    printf("NNB: Function type:    RandGamma(290)\n");
  } break;
  case NN_FUNCTION_RANDOM_CHOICE: { // RandomChoice
    printf("NNB: Function type:    RandomChoice(246)\n");
  } break;
  case NN_FUNCTION_RANDOM_CROP: { // RandomCrop
    printf("NNB: Function type:    RandomCrop(92)\n");
  } break;
  case NN_FUNCTION_RANDOM_FLIP: { // RandomFlip
    printf("NNB: Function type:    RandomFlip(93)\n");
  } break;
  case NN_FUNCTION_RANDOM_SHIFT: { // RandomShift
    printf("NNB: Function type:    RandomShift(320)\n");
  } break;
  case NN_FUNCTION_RANDOM_ERASE: { // RandomErase
    printf("NNB: Function type:    RandomErase(285)\n");
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
  case NN_FUNCTION_AFFINE_GRID: { // AffineGrid
    printf("NNB: Function type:    AffineGrid(296)\n");
  } break;
  case NN_FUNCTION_WARP_BY_GRID: { // WarpByGrid
    printf("NNB: Function type:    WarpByGrid(297)\n");
  } break;
  case NN_FUNCTION_WARP_BY_FLOW: { // WarpByFlow
    printf("NNB: Function type:    WarpByFlow(277)\n");
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
  case NN_FUNCTION_MIN_MAX_QUANTIZE: { // MinMaxQuantize
    printf("NNB: Function type:    MinMaxQuantize(274)\n");
  } break;
  case NN_FUNCTION_POW2_QUANTIZE: { // Pow2Quantize
    printf("NNB: Function type:    Pow2Quantize(114)\n");
  } break;
  case NN_FUNCTION_PRUNE: { // Prune
    printf("NNB: Function type:    Prune(135)\n");
  } break;
  case NN_FUNCTION_QUANTIZE_LINEAR: { // QuantizeLinear
    printf("NNB: Function type:    QuantizeLinear(293)\n");
  } break;
  case NN_FUNCTION_DEQUANTIZE_LINEAR: { // DequantizeLinear
    printf("NNB: Function type:    DequantizeLinear(294)\n");
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
  case NN_FUNCTION_ONNX_NON_MAX_SUPPRESSION: { // ONNXNonMaxSuppression
    printf("NNB: Function type:    ONNXNonMaxSuppression(353)\n");
  } break;
  case NN_FUNCTION_MAX_POOLING_BACKWARD: { // MaxPoolingBackward
    printf("NNB: Function type:    MaxPoolingBackward(272)\n");
  } break;
  case NN_FUNCTION_PATCH_CORRELATION: { // PatchCorrelation
    printf("NNB: Function type:    PatchCorrelation(280)\n");
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_FUSED_CONVOLUTION: { // FusedConvolution
    nn_function_fused_convolution_t *f =
        (nn_function_fused_convolution_t *)func;
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
    printf("NNB: Function argument decay_rate: %f\n", f->decay_rate);
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument batch_stat: %d\n", f->batch_stat);
    printf("NNB: Function argument nonlinearity: %d\n", f->nonlinearity);
    printf("NNB: Function argument pad_mode: %d\n", f->pad_mode);
    printf("NNB: Function argument constant_value: %f\n", f->constant_value);
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
    printf("NNB: Function argument output_padding: (");
    list = (int *)NN_GET(net, f->output_padding.list);
    for (i = 0; i < f->output_padding.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
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
  case NN_FUNCTION_DEFORMABLE_CONVOLUTION: { // DeformableConvolution
    nn_function_deformable_convolution_t *f =
        (nn_function_deformable_convolution_t *)func;
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
    printf("NNB: Function argument deformable_group: %d\n",
           f->deformable_group);
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_ADAPTIVE_SEPARABLE_CONVOLUTION: { // AdaptiveSeparableConvolution
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_UNPOOLING: { // Unpooling
    nn_function_unpooling_t *f = (nn_function_unpooling_t *)func;
    printf("NNB: Function argument kernel: (");
    list = (int *)NN_GET(net, f->kernel.list);
    for (i = 0; i < f->kernel.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_EMBED: { // Embed
  } break;
  case NN_FUNCTION_ROI_ALIGN: { // RoiAlign
    nn_function_roi_align_t *f = (nn_function_roi_align_t *)func;
    printf("NNB: Function argument output_size: (");
    list = (int *)NN_GET(net, f->output_size.list);
    for (i = 0; i < f->output_size.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument sampling_ratio: %d\n", f->sampling_ratio);
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
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
  case NN_FUNCTION_LOG_SOFTMAX: { // LogSoftmax
    nn_function_log_softmax_t *f = (nn_function_log_softmax_t *)func;
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
  case NN_FUNCTION_MISH: { // Mish
  } break;
  case NN_FUNCTION_RELU6: { // ReLU6
  } break;
  case NN_FUNCTION_HARD_SIGMOID: { // HardSigmoid
  } break;
  case NN_FUNCTION_HARD_TANH: { // HardTanh
  } break;
  case NN_FUNCTION_LOG_SIGMOID: { // LogSigmoid
  } break;
  case NN_FUNCTION_SOFTPLUS: { // SoftPlus
    nn_function_softplus_t *f = (nn_function_softplus_t *)func;
    printf("NNB: Function argument beta: %f\n", f->beta);
  } break;
  case NN_FUNCTION_SOFTSIGN: { // SoftSign
  } break;
  case NN_FUNCTION_TANH_SHRINK: { // TanhShrink
  } break;
  case NN_FUNCTION_SINC: { // Sinc
  } break;
  case NN_FUNCTION_FUSED_BATCH_NORMALIZATION: { // FusedBatchNormalization
    nn_function_fused_batch_normalization_t *f =
        (nn_function_fused_batch_normalization_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument decay_rate: %f\n", f->decay_rate);
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument batch_stat: %d\n", f->batch_stat);
    printf("NNB: Function argument nonlinearity: %d\n", f->nonlinearity);
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
    printf("NNB: Function argument no_scale: %d\n", f->no_scale);
    printf("NNB: Function argument no_bias: %d\n", f->no_bias);
  } break;
  case NN_FUNCTION_GROUP_NORMALIZATION: { // GroupNormalization
    nn_function_group_normalization_t *f =
        (nn_function_group_normalization_t *)func;
    printf("NNB: Function argument num_groups: %d\n", f->num_groups);
    printf("NNB: Function argument channel_axis: %d\n", f->channel_axis);
    printf("NNB: Function argument batch_axis: (");
    list = (int *)NN_GET(net, f->batch_axis.list);
    for (i = 0; i < f->batch_axis.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument no_scale: %d\n", f->no_scale);
    printf("NNB: Function argument no_bias: %d\n", f->no_bias);
  } break;
  case NN_FUNCTION_INSTANCE_NORMALIZATION: { // InstanceNormalization
    nn_function_instance_normalization_t *f =
        (nn_function_instance_normalization_t *)func;
    printf("NNB: Function argument channel_axis: %d\n", f->channel_axis);
    printf("NNB: Function argument batch_axis: (");
    list = (int *)NN_GET(net, f->batch_axis.list);
    for (i = 0; i < f->batch_axis.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument no_scale: %d\n", f->no_scale);
    printf("NNB: Function argument no_bias: %d\n", f->no_bias);
  } break;
  case NN_FUNCTION_LAYER_NORMALIZATION: { // LayerNormalization
    nn_function_layer_normalization_t *f =
        (nn_function_layer_normalization_t *)func;
    printf("NNB: Function argument batch_axis: (");
    list = (int *)NN_GET(net, f->batch_axis.list);
    for (i = 0; i < f->batch_axis.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument no_scale: %d\n", f->no_scale);
    printf("NNB: Function argument no_bias: %d\n", f->no_bias);
  } break;
  case NN_FUNCTION_NORM_NORMALIZATION: { // NormNormalization
    nn_function_norm_normalization_t *f =
        (nn_function_norm_normalization_t *)func;
    printf("NNB: Function argument p: %f\n", f->p);
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument eps: %f\n", f->eps);
  } break;
  case NN_FUNCTION_SYNC_BATCH_NORMALIZATION: { // SyncBatchNormalization
    nn_function_sync_batch_normalization_t *f =
        (nn_function_sync_batch_normalization_t *)func;
    printf("NNB: Function argument group: %d\n", f->group);
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
  case NN_FUNCTION_TENSOR_NORMALIZATION: { // TensorNormalization
    nn_function_tensor_normalization_t *f =
        (nn_function_tensor_normalization_t *)func;
    printf("NNB: Function argument axes: (");
    list = (int *)NN_GET(net, f->axes.list);
    for (i = 0; i < f->axes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument no_scale: %d\n", f->no_scale);
    printf("NNB: Function argument no_bias: %d\n", f->no_bias);
  } break;
  case NN_FUNCTION_WEIGHT_NORMALIZATION: { // WeightNormalization
    nn_function_weight_normalization_t *f =
        (nn_function_weight_normalization_t *)func;
    printf("NNB: Function argument dim: %d\n", f->dim);
    printf("NNB: Function argument eps: %f\n", f->eps);
  } break;
  case NN_FUNCTION_WEIGHT_STANDARDIZATION: { // WeightStandardization
    nn_function_weight_standardization_t *f =
        (nn_function_weight_standardization_t *)func;
    printf("NNB: Function argument channel_axis: %d\n", f->channel_axis);
    printf("NNB: Function argument eps: %f\n", f->eps);
  } break;
  case NN_FUNCTION_SPECTRAL_NORM: { // SpectralNorm
    nn_function_spectral_norm_t *f = (nn_function_spectral_norm_t *)func;
    printf("NNB: Function argument dim: %d\n", f->dim);
    printf("NNB: Function argument itr: %d\n", f->itr);
    printf("NNB: Function argument eps: %f\n", f->eps);
    printf("NNB: Function argument test: %d\n", f->test);
    printf("NNB: Function argument output_u: %d\n", f->output_u);
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
  case NN_FUNCTION_CUMSUM: { // CumSum
    nn_function_cumsum_t *f = (nn_function_cumsum_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
    printf("NNB: Function argument exclusive: %d\n", f->exclusive);
    printf("NNB: Function argument reverse: %d\n", f->reverse);
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
  case NN_FUNCTION_NORM: { // Norm
    nn_function_norm_t *f = (nn_function_norm_t *)func;
    printf("NNB: Function argument p: %f\n", f->p);
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
  case NN_FUNCTION_CUMPROD: { // CumProd
    nn_function_cumprod_t *f = (nn_function_cumprod_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
    printf("NNB: Function argument exclusive: %d\n", f->exclusive);
    printf("NNB: Function argument reverse: %d\n", f->reverse);
  } break;
  case NN_FUNCTION_REDUCE_SUM: { // ReduceSum
  } break;
  case NN_FUNCTION_REDUCE_MEAN: { // ReduceMean
  } break;
  case NN_FUNCTION_ADD2: { // Add2
    nn_function_add2_t *f = (nn_function_add2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_ADD_N: { // AddN
  } break;
  case NN_FUNCTION_BC_ADD2: { // BcAdd2
    nn_function_bc_add2_t *f = (nn_function_bc_add2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_SUB2: { // Sub2
    nn_function_sub2_t *f = (nn_function_sub2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_MUL2: { // Mul2
    nn_function_mul2_t *f = (nn_function_mul2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_MUL_N: { // MulN
  } break;
  case NN_FUNCTION_DIV2: { // Div2
    nn_function_div2_t *f = (nn_function_div2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_POW2: { // Pow2
    nn_function_pow2_t *f = (nn_function_pow2_t *)func;
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_ADD_SCALAR: { // AddScalar
    nn_function_add_scalar_t *f = (nn_function_add_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_MUL_SCALAR: { // MulScalar
    nn_function_mul_scalar_t *f = (nn_function_mul_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
    printf("NNB: Function argument inplace: %d\n", f->inplace);
  } break;
  case NN_FUNCTION_POW_SCALAR: { // PowScalar
    nn_function_pow_scalar_t *f = (nn_function_pow_scalar_t *)func;
    printf("NNB: Function argument val: %f\n", f->val);
    printf("NNB: Function argument inplace: %d\n", f->inplace);
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
  case NN_FUNCTION_SEARCHSORTED: { // SearchSorted
    nn_function_searchsorted_t *f = (nn_function_searchsorted_t *)func;
    printf("NNB: Function argument right: %d\n", f->right);
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
  case NN_FUNCTION_LINSPACE: { // Linspace
    nn_function_linspace_t *f = (nn_function_linspace_t *)func;
    printf("NNB: Function argument start: %f\n", f->start);
    printf("NNB: Function argument stop: %f\n", f->stop);
    printf("NNB: Function argument num: %d\n", f->num);
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
  case NN_FUNCTION_ERF: { // Erf
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
  case NN_FUNCTION_TILE: { // Tile
    nn_function_tile_t *f = (nn_function_tile_t *)func;
    printf("NNB: Function argument reps: (");
    list = (int *)NN_GET(net, f->reps.list);
    for (i = 0; i < f->reps.size; i++) {
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
  case NN_FUNCTION_SHAPE: { // Shape
    nn_function_shape_t *f = (nn_function_shape_t *)func;
    printf("NNB: Function argument start: %d\n", f->start);
    printf("NNB: Function argument end: %d\n", f->end);
  } break;
  case NN_FUNCTION_MATRIX_DIAG: { // MatrixDiag
  } break;
  case NN_FUNCTION_MATRIX_DIAG_PART: { // MatrixDiagPart
  } break;
  case NN_FUNCTION_MESHGRID: { // Meshgrid
    nn_function_meshgrid_t *f = (nn_function_meshgrid_t *)func;
    printf("NNB: Function argument ij_indexing: %d\n", f->ij_indexing);
  } break;
  case NN_FUNCTION_BATCH_DET: { // BatchDet
  } break;
  case NN_FUNCTION_BATCH_INV: { // BatchInv
  } break;
  case NN_FUNCTION_BATCH_LOGDET: { // BatchLogdet
  } break;
  case NN_FUNCTION_BATCH_CHOLESKY: { // BatchCholesky
    nn_function_batch_cholesky_t *f = (nn_function_batch_cholesky_t *)func;
    printf("NNB: Function argument upper: %d\n", f->upper);
  } break;
  case NN_FUNCTION_ASSIGN: { // Assign
  } break;
  case NN_FUNCTION_GATHER: { // Gather
    nn_function_gather_t *f = (nn_function_gather_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
    printf("NNB: Function argument batch_dims: %d\n", f->batch_dims);
  } break;
  case NN_FUNCTION_GATHER_ND: { // GatherNd
  } break;
  case NN_FUNCTION_BOOL_GATHER: { // BoolGather
  } break;
  case NN_FUNCTION_SCATTER_ND: { // ScatterNd
    nn_function_scatter_nd_t *f = (nn_function_scatter_nd_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument add: %d\n", f->add);
  } break;
  case NN_FUNCTION_SCATTER_ADD: { // ScatterAdd
    nn_function_scatter_add_t *f = (nn_function_scatter_add_t *)func;
    printf("NNB: Function argument axis: %d\n", f->axis);
  } break;
  case NN_FUNCTION_BOOL_SCATTER: { // BoolScatter
  } break;
  case NN_FUNCTION_BOOL_FILL: { // BoolFill
    nn_function_bool_fill_t *f = (nn_function_bool_fill_t *)func;
    printf("NNB: Function argument value: %f\n", f->value);
  } break;
  case NN_FUNCTION_PACK_PADDED_SEQUENCE: { // PackPaddedSequence
    nn_function_pack_padded_sequence_t *f =
        (nn_function_pack_padded_sequence_t *)func;
    printf("NNB: Function argument batch_first: %d\n", f->batch_first);
  } break;
  case NN_FUNCTION_PAD_PACKED_SEQUENCE: { // PadPackedSequence
    nn_function_pad_packed_sequence_t *f =
        (nn_function_pad_packed_sequence_t *)func;
    printf("NNB: Function argument batch_first: %d\n", f->batch_first);
    printf("NNB: Function argument padding_value: %f\n", f->padding_value);
    printf("NNB: Function argument total_length: %d\n", f->total_length);
  } break;
  case NN_FUNCTION_NONZERO: { // NonZero
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
    printf("NNB: Function argument half_pixel: %d\n", f->half_pixel);
    printf("NNB: Function argument half_pixel_for_nn: %d\n",
           f->half_pixel_for_nn);
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_ONNX_RESIZE: { // ONNXResize
    nn_function_onnx_resize_t *f = (nn_function_onnx_resize_t *)func;
    printf("NNB: Function argument sizes: (");
    list = (int *)NN_GET(net, f->sizes.list);
    for (i = 0; i < f->sizes.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument mode: %d\n", f->mode);
    printf("NNB: Function argument coordinate_transformation_mode: %d\n",
           f->coordinate_transformation_mode);
    printf("NNB: Function argument cubic_coeff_a: %f\n", f->cubic_coeff_a);
    printf("NNB: Function argument exclude_outside: %d\n", f->exclude_outside);
    printf("NNB: Function argument extrapolation_value: %f\n",
           f->extrapolation_value);
    printf("NNB: Function argument nearest_mode: %d\n", f->nearest_mode);
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
  case NN_FUNCTION_STFT: { // STFT
    nn_function_stft_t *f = (nn_function_stft_t *)func;
    printf("NNB: Function argument window_size: %d\n", f->window_size);
    printf("NNB: Function argument stride: %d\n", f->stride);
    printf("NNB: Function argument fft_size: %d\n", f->fft_size);
    printf("NNB: Function argument window_type: %d\n", f->window_type);
    printf("NNB: Function argument center: %d\n", f->center);
    printf("NNB: Function argument pad_mode: %d\n", f->pad_mode);
    printf("NNB: Function argument as_istft_backward: %d\n",
           f->as_istft_backward);
  } break;
  case NN_FUNCTION_ISTFT: { // ISTFT
    nn_function_istft_t *f = (nn_function_istft_t *)func;
    printf("NNB: Function argument window_size: %d\n", f->window_size);
    printf("NNB: Function argument stride: %d\n", f->stride);
    printf("NNB: Function argument fft_size: %d\n", f->fft_size);
    printf("NNB: Function argument window_type: %d\n", f->window_type);
    printf("NNB: Function argument center: %d\n", f->center);
    printf("NNB: Function argument pad_mode: %d\n", f->pad_mode);
    printf("NNB: Function argument as_stft_backward: %d\n",
           f->as_stft_backward);
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
    printf("NNB: Function argument largest: %d\n", f->largest);
    printf("NNB: Function argument with_index: %d\n", f->with_index);
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
  case NN_FUNCTION_RAND_BINOMIAL: { // RandBinomial
    nn_function_rand_binomial_t *f = (nn_function_rand_binomial_t *)func;
    printf("NNB: Function argument n: %d\n", f->n);
    printf("NNB: Function argument p: %f\n", f->p);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RAND_BETA: { // RandBeta
    nn_function_rand_beta_t *f = (nn_function_rand_beta_t *)func;
    printf("NNB: Function argument alpha: %f\n", f->alpha);
    printf("NNB: Function argument beta: %f\n", f->beta);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RAND_GAMMA: { // RandGamma
    nn_function_rand_gamma_t *f = (nn_function_rand_gamma_t *)func;
    printf("NNB: Function argument k: %f\n", f->k);
    printf("NNB: Function argument theta: %f\n", f->theta);
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDOM_CHOICE: { // RandomChoice
    nn_function_random_choice_t *f = (nn_function_random_choice_t *)func;
    printf("NNB: Function argument shape: (");
    list = (int *)NN_GET(net, f->shape.list);
    for (i = 0; i < f->shape.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument replace: %d\n", f->replace);
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
    printf("NNB: Function argument constant_value: %f\n", f->constant_value);
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument seed: %d\n", f->seed);
  } break;
  case NN_FUNCTION_RANDOM_ERASE: { // RandomErase
    nn_function_random_erase_t *f = (nn_function_random_erase_t *)func;
    printf("NNB: Function argument prob: %f\n", f->prob);
    printf("NNB: Function argument n: %d\n", f->n);
    printf("NNB: Function argument share: %d\n", f->share);
    printf("NNB: Function argument inplace: %d\n", f->inplace);
    printf("NNB: Function argument base_axis: %d\n", f->base_axis);
    printf("NNB: Function argument seed: %d\n", f->seed);
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
    printf("NNB: Function argument ste_fine_grained: %d\n",
           f->ste_fine_grained);
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
  case NN_FUNCTION_AFFINE_GRID: { // AffineGrid
    nn_function_affine_grid_t *f = (nn_function_affine_grid_t *)func;
    printf("NNB: Function argument size: (");
    list = (int *)NN_GET(net, f->size.list);
    for (i = 0; i < f->size.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument align_corners: %d\n", f->align_corners);
  } break;
  case NN_FUNCTION_WARP_BY_GRID: { // WarpByGrid
    nn_function_warp_by_grid_t *f = (nn_function_warp_by_grid_t *)func;
    printf("NNB: Function argument mode: %d\n", f->mode);
    printf("NNB: Function argument padding_mode: %d\n", f->padding_mode);
    printf("NNB: Function argument align_corners: %d\n", f->align_corners);
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_WARP_BY_FLOW: { // WarpByFlow
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
  case NN_FUNCTION_MIN_MAX_QUANTIZE: { // MinMaxQuantize
    nn_function_min_max_quantize_t *f = (nn_function_min_max_quantize_t *)func;
    printf("NNB: Function argument decay: %f\n", f->decay);
    printf("NNB: Function argument x_min_max: %d\n", f->x_min_max);
    printf("NNB: Function argument ema: %d\n", f->ema);
    printf("NNB: Function argument ste_fine_grained: %d\n",
           f->ste_fine_grained);
    printf("NNB: Function argument eps: %f\n", f->eps);
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
  case NN_FUNCTION_QUANTIZE_LINEAR: { // QuantizeLinear
    nn_function_quantize_linear_t *f = (nn_function_quantize_linear_t *)func;
    printf("NNB: Function argument round_mode: %d\n", f->round_mode);
    printf("NNB: Function argument narrow_range: %d\n", f->narrow_range);
    printf("NNB: Function argument dtype: %d\n", f->dtype);
  } break;
  case NN_FUNCTION_DEQUANTIZE_LINEAR: { // DequantizeLinear
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
  case NN_FUNCTION_ONNX_NON_MAX_SUPPRESSION: { // ONNXNonMaxSuppression
    nn_function_onnx_non_max_suppression_t *f =
        (nn_function_onnx_non_max_suppression_t *)func;
    printf("NNB: Function argument center_point_box: %d\n",
           f->center_point_box);
    printf("NNB: Function argument max_output_boxes_per_class: %d\n",
           f->max_output_boxes_per_class);
    printf("NNB: Function argument iou_threshold: %f\n", f->iou_threshold);
    printf("NNB: Function argument score_threshold: %f\n", f->score_threshold);
  } break;
  case NN_FUNCTION_MAX_POOLING_BACKWARD: { // MaxPoolingBackward
    nn_function_max_pooling_backward_t *f =
        (nn_function_max_pooling_backward_t *)func;
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
    printf("NNB: Function argument channel_last: %d\n", f->channel_last);
  } break;
  case NN_FUNCTION_PATCH_CORRELATION: { // PatchCorrelation
    nn_function_patch_correlation_t *f =
        (nn_function_patch_correlation_t *)func;
    printf("NNB: Function argument patch: (");
    list = (int *)NN_GET(net, f->patch.list);
    for (i = 0; i < f->patch.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument shift: (");
    list = (int *)NN_GET(net, f->shift.list);
    for (i = 0; i < f->shift.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument patch_step: (");
    list = (int *)NN_GET(net, f->patch_step.list);
    for (i = 0; i < f->patch_step.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument shift_step: (");
    list = (int *)NN_GET(net, f->shift_step.list);
    for (i = 0; i < f->shift_step.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
    printf("NNB: Function argument padding: (");
    list = (int *)NN_GET(net, f->padding.list);
    for (i = 0; i < f->padding.size; i++) {
      printf(" %d", *(list + i));
    }
    printf(" )\n");
  } break;
  default:;
  }
}
