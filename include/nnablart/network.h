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

#ifndef H_NETWORK_H__
#define H_NETWORK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h> // for fixed bit length integer type
#include <stdlib.h> // for size_t

#define NN_NNABLA_VERSION ("1.34.0.dev1")
#define NN_C_RUNTIME_VERSION ("1.2.0.dev1_c1")
#define NN_BINARY_FORMAT_MINIMUM_VERSION (2)
#define NN_BINARY_FORMAT_VERSION (3)
#define NN_API_LEVEL (44)
#define NN_API_LEVEL_MAX (5000)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Network Internal network representation
/// @{

typedef int32_t pointer_index_t; ///< Index of data.
typedef uint32_t nn_size_t;      ///< Size of data.

/// @brief List of integer
typedef struct {
  nn_size_t size;       ///< Size of list.
  pointer_index_t list; ///< Index of list data.
} nn_list_t;

/// @brief Data types.
typedef enum {
  NN_DATA_TYPE_FLOAT, ///< 32bit float.
  NN_DATA_TYPE_INT16, ///< 16bit integer.
  NN_DATA_TYPE_INT8,  ///<  8bit integer.
  NN_DATA_TYPE_SIGN,  ///< Binary.
  END_OF_NN_DATA_TYPE
} nn_data_type_t;

/// @brief Definition of Variable.
typedef struct {
  uint32_t id;             ///< Identifier
  nn_list_t shape;         ///< Shape
  nn_data_type_t type : 4; ///< Type of param values
  unsigned int fp_pos : 4; ///< floating point position.
  int32_t data_index;      ///< Location of data. If negative, it means data
                           /// buffer index. Otherwise it means location of data
                           /// in memory.
} nn_variable_t;

/// @brief Function types.
typedef enum {
  NN_FUNCTION_AFFINE = 0, ///< Affine
  NN_FUNCTION_RNN = 244,  ///< RNN
  NN_FUNCTION_LSTM = 242, ///< LSTM
  NN_FUNCTION_GRU = 243,  ///< GRU
  NN_FUNCTION_CONVOLUTION_0 =
      1, ///< Recent version of Convolution has arg [iiIiIiIi]
  NN_FUNCTION_CONVOLUTION = 265, ///< Convolution
  NN_FUNCTION_FUSED_CONVOLUTION_0 =
      295, ///< Recent version of FusedConvolution has arg [iiIiIiIiBffBifF]
  NN_FUNCTION_FUSED_CONVOLUTION = 346,   ///< FusedConvolution
  NN_FUNCTION_DEPTHWISE_CONVOLUTION = 2, ///< DepthwiseConvolution
  NN_FUNCTION_DECONVOLUTION_0 =
      3, ///< Recent version of Deconvolution has arg [iiIiIiIi]
  NN_FUNCTION_DECONVOLUTION_1 =
      279, ///< Recent version of Deconvolution has arg [iiIiIiIiB]
  NN_FUNCTION_DECONVOLUTION = 292,          ///< Deconvolution
  NN_FUNCTION_DEPTHWISE_DECONVOLUTION = 4,  ///< DepthwiseDeconvolution
  NN_FUNCTION_DEFORMABLE_CONVOLUTION = 329, ///< DeformableConvolution
  NN_FUNCTION_ADAPTIVE_SEPARABLE_CONVOLUTION =
      278, ///< AdaptiveSeparableConvolution
  NN_FUNCTION_MAX_POOLING_0 =
      5, ///< Recent version of MaxPooling has arg [iIiIBiI]
  NN_FUNCTION_MAX_POOLING = 266, ///< MaxPooling
  NN_FUNCTION_AVERAGE_POOLING_0 =
      6, ///< Recent version of AveragePooling has arg [iIiIBiIB]
  NN_FUNCTION_AVERAGE_POOLING = 267,      ///< AveragePooling
  NN_FUNCTION_GLOBAL_AVERAGE_POOLING = 7, ///< GlobalAveragePooling
  NN_FUNCTION_SUM_POOLING_0 =
      8, ///< Recent version of SumPooling has arg [iIiIBiI]
  NN_FUNCTION_SUM_POOLING = 268, ///< SumPooling
  NN_FUNCTION_UNPOOLING_0 = 9,   ///< Recent version of Unpooling has arg [iI]
  NN_FUNCTION_UNPOOLING = 287,   ///< Unpooling
  NN_FUNCTION_EMBED = 10,        ///< Embed
  NN_FUNCTION_ROI_ALIGN = 338,   ///< RoiAlign
  NN_FUNCTION_SIGMOID = 11,      ///< Sigmoid
  NN_FUNCTION_SWISH = 12,        ///< Swish
  NN_FUNCTION_TANH = 13,         ///< Tanh
  NN_FUNCTION_RELU = 14,         ///< ReLU
  NN_FUNCTION_LEAKY_RELU_0 = 15, ///< Recent version of LeakyReLU has arg [f]
  NN_FUNCTION_LEAKY_RELU = 128,  ///< LeakyReLU
  NN_FUNCTION_SOFTMAX = 16,      ///< Softmax
  NN_FUNCTION_LOG_SOFTMAX = 269, ///< LogSoftmax
  NN_FUNCTION_ELU = 17,          ///< ELU
  NN_FUNCTION_SELU = 18,         ///< SELU
  NN_FUNCTION_CRELU = 19,        ///< CReLU
  NN_FUNCTION_CELU = 20,         ///< CELU
  NN_FUNCTION_PRELU = 21,        ///< PReLU
  NN_FUNCTION_GELU = 245,        ///< GELU
  NN_FUNCTION_MISH = 298,        ///< Mish
  NN_FUNCTION_RELU6 = 256,       ///< ReLU6
  NN_FUNCTION_HARD_SIGMOID_0 =
      249, ///< Recent version of HardSigmoid has arg [Empty]
  NN_FUNCTION_HARD_SIGMOID = 259, ///< HardSigmoid
  NN_FUNCTION_HARD_TANH_0 = 250,  ///< Recent version of HardTanh has arg [ii]
  NN_FUNCTION_HARD_TANH_1 = 260,  ///< Recent version of HardTanh has arg [ff]
  NN_FUNCTION_HARD_TANH = 261,    ///< HardTanh
  NN_FUNCTION_LOG_SIGMOID = 251,  ///< LogSigmoid
  NN_FUNCTION_SOFTPLUS_0 = 252,   ///< Recent version of SoftPlus has arg [ii]
  NN_FUNCTION_SOFTPLUS_1 = 262,  ///< Recent version of SoftPlus has arg [Empty]
  NN_FUNCTION_SOFTPLUS = 335,    ///< SoftPlus
  NN_FUNCTION_SOFTSIGN = 253,    ///< SoftSign
  NN_FUNCTION_TANH_SHRINK = 254, ///< TanhShrink
  NN_FUNCTION_SINC = 255,        ///< Sinc
  NN_FUNCTION_FUSED_BATCH_NORMALIZATION = 270, ///< FusedBatchNormalization
  NN_FUNCTION_BATCH_NORMALIZATION_0 =
      22, ///< Recent version of BatchNormalization has arg [iIffB]
  NN_FUNCTION_BATCH_NORMALIZATION = 326,      ///< BatchNormalization
  NN_FUNCTION_GROUP_NORMALIZATION = 321,      ///< GroupNormalization
  NN_FUNCTION_INSTANCE_NORMALIZATION = 322,   ///< InstanceNormalization
  NN_FUNCTION_LAYER_NORMALIZATION = 323,      ///< LayerNormalization
  NN_FUNCTION_NORM_NORMALIZATION = 317,       ///< NormNormalization
  NN_FUNCTION_SYNC_BATCH_NORMALIZATION = 263, ///< SyncBatchNormalization
  NN_FUNCTION_TENSOR_NORMALIZATION = 324,     ///< TensorNormalization
  NN_FUNCTION_WEIGHT_NORMALIZATION = 304,     ///< WeightNormalization
  NN_FUNCTION_WEIGHT_STANDARDIZATION = 325,   ///< WeightStandardization
  NN_FUNCTION_SPECTRAL_NORM_0 =
      330, ///< Recent version of SpectralNorm has arg [iifB]
  NN_FUNCTION_SPECTRAL_NORM = 337,      ///< SpectralNorm
  NN_FUNCTION_MEAN_SUBTRACTION = 23,    ///< MeanSubtraction
  NN_FUNCTION_CLIP_GRAD_BY_VALUE = 121, ///< ClipGradByValue
  NN_FUNCTION_CLIP_GRAD_BY_NORM = 122,  ///< ClipGradByNorm
  NN_FUNCTION_SUM = 24,                 ///< Sum
  NN_FUNCTION_CUMSUM = 331,             ///< CumSum
  NN_FUNCTION_MEAN = 25,                ///< Mean
  NN_FUNCTION_MAX_0 = 26,               ///< Recent version of Max has arg [iIB]
  NN_FUNCTION_MAX = 132,                ///< Max
  NN_FUNCTION_MIN_0 = 27,               ///< Recent version of Min has arg [iIB]
  NN_FUNCTION_MIN = 130,                ///< Min
  NN_FUNCTION_NORM = 318,               ///< Norm
  NN_FUNCTION_PROD = 28,                ///< Prod
  NN_FUNCTION_CUMPROD = 332,            ///< CumProd
  NN_FUNCTION_REDUCE_SUM = 29,          ///< ReduceSum
  NN_FUNCTION_REDUCE_MEAN = 30,         ///< ReduceMean
  NN_FUNCTION_ADD2 = 31,                ///< Add2
  NN_FUNCTION_ADD_N = 281,              ///< AddN
  NN_FUNCTION_BC_ADD2_0 = 32,      ///< Recent version of BcAdd2 has arg [Empty]
  NN_FUNCTION_BC_ADD2 = 307,       ///< BcAdd2
  NN_FUNCTION_SUB2_0 = 33,         ///< Recent version of Sub2 has arg [Empty]
  NN_FUNCTION_SUB2 = 308,          ///< Sub2
  NN_FUNCTION_MUL2_0 = 34,         ///< Recent version of Mul2 has arg [Empty]
  NN_FUNCTION_MUL2 = 309,          ///< Mul2
  NN_FUNCTION_MUL_N = 282,         ///< MulN
  NN_FUNCTION_DIV2_0 = 35,         ///< Recent version of Div2 has arg [Empty]
  NN_FUNCTION_DIV2 = 310,          ///< Div2
  NN_FUNCTION_POW2_0 = 36,         ///< Recent version of Pow2 has arg [Empty]
  NN_FUNCTION_POW2 = 311,          ///< Pow2
  NN_FUNCTION_ADD_SCALAR_0 = 37,   ///< Recent version of AddScalar has arg [f]
  NN_FUNCTION_ADD_SCALAR = 312,    ///< AddScalar
  NN_FUNCTION_MUL_SCALAR_0 = 38,   ///< Recent version of MulScalar has arg [f]
  NN_FUNCTION_MUL_SCALAR = 313,    ///< MulScalar
  NN_FUNCTION_POW_SCALAR_0 = 39,   ///< Recent version of PowScalar has arg [f]
  NN_FUNCTION_POW_SCALAR = 314,    ///< PowScalar
  NN_FUNCTION_R_SUB_SCALAR = 40,   ///< RSubScalar
  NN_FUNCTION_R_DIV_SCALAR = 41,   ///< RDivScalar
  NN_FUNCTION_R_POW_SCALAR = 42,   ///< RPowScalar
  NN_FUNCTION_SIGN = 43,           ///< Sign
  NN_FUNCTION_MINIMUM2 = 44,       ///< Minimum2
  NN_FUNCTION_MAXIMUM2 = 45,       ///< Maximum2
  NN_FUNCTION_MINIMUM_SCALAR = 46, ///< MinimumScalar
  NN_FUNCTION_MAXIMUM_SCALAR = 47, ///< MaximumScalar
  NN_FUNCTION_LOGICAL_AND = 48,    ///< LogicalAnd
  NN_FUNCTION_LOGICAL_OR = 49,     ///< LogicalOr
  NN_FUNCTION_LOGICAL_XOR = 50,    ///< LogicalXor
  NN_FUNCTION_EQUAL = 51,          ///< Equal
  NN_FUNCTION_NOT_EQUAL = 52,      ///< NotEqual
  NN_FUNCTION_GREATER_EQUAL = 53,  ///< GreaterEqual
  NN_FUNCTION_GREATER = 54,        ///< Greater
  NN_FUNCTION_LESS_EQUAL = 55,     ///< LessEqual
  NN_FUNCTION_LESS = 56,           ///< Less
  NN_FUNCTION_SEARCHSORTED = 333,  ///< SearchSorted
  NN_FUNCTION_LOGICAL_AND_SCALAR = 57,   ///< LogicalAndScalar
  NN_FUNCTION_LOGICAL_OR_SCALAR = 58,    ///< LogicalOrScalar
  NN_FUNCTION_LOGICAL_XOR_SCALAR = 59,   ///< LogicalXorScalar
  NN_FUNCTION_EQUAL_SCALAR = 60,         ///< EqualScalar
  NN_FUNCTION_NOT_EQUAL_SCALAR = 61,     ///< NotEqualScalar
  NN_FUNCTION_GREATER_EQUAL_SCALAR = 62, ///< GreaterEqualScalar
  NN_FUNCTION_GREATER_SCALAR = 63,       ///< GreaterScalar
  NN_FUNCTION_LESS_EQUAL_SCALAR = 64,    ///< LessEqualScalar
  NN_FUNCTION_LESS_SCALAR = 65,          ///< LessScalar
  NN_FUNCTION_LOGICAL_NOT = 66,          ///< LogicalNot
  NN_FUNCTION_ISNAN = 236,               ///< IsNaN
  NN_FUNCTION_ISINF = 237,               ///< IsInf
  NN_FUNCTION_RESET_NAN = 238,           ///< ResetNaN
  NN_FUNCTION_RESET_INF = 239,           ///< ResetInf
  NN_FUNCTION_WHERE = 240,               ///< Where
  NN_FUNCTION_CONSTANT = 67,             ///< Constant
  NN_FUNCTION_ARANGE = 131,              ///< Arange
  NN_FUNCTION_LINSPACE = 343,            ///< Linspace
  NN_FUNCTION_ABS = 68,                  ///< Abs
  NN_FUNCTION_EXP = 69,                  ///< Exp
  NN_FUNCTION_LOG = 70,                  ///< Log
  NN_FUNCTION_IDENTITY = 71,             ///< Identity
  NN_FUNCTION_BATCH_MATMUL = 72,         ///< BatchMatmul
  NN_FUNCTION_ROUND = 73,                ///< Round
  NN_FUNCTION_CEIL = 124,                ///< Ceil
  NN_FUNCTION_FLOOR = 125,               ///< Floor
  NN_FUNCTION_SIN = 173,                 ///< Sin
  NN_FUNCTION_COS = 174,                 ///< Cos
  NN_FUNCTION_TAN = 175,                 ///< Tan
  NN_FUNCTION_SINH = 176,                ///< Sinh
  NN_FUNCTION_COSH = 177,                ///< Cosh
  NN_FUNCTION_ASIN = 178,                ///< ASin
  NN_FUNCTION_ACOS = 179,                ///< ACos
  NN_FUNCTION_ATAN = 180,                ///< ATan
  NN_FUNCTION_ATAN2 = 241,               ///< ATan2
  NN_FUNCTION_ASINH = 181,               ///< ASinh
  NN_FUNCTION_ACOSH = 182,               ///< ACosh
  NN_FUNCTION_ATANH = 183,               ///< ATanh
  NN_FUNCTION_ERF = 349,                 ///< Erf
  NN_FUNCTION_CONCATENATE = 74,          ///< Concatenate
  NN_FUNCTION_SPLIT = 75,                ///< Split
  NN_FUNCTION_STACK = 76,                ///< Stack
  NN_FUNCTION_SLICE = 77,                ///< Slice
  NN_FUNCTION_PAD = 123,                 ///< Pad
  NN_FUNCTION_TRANSPOSE = 78,            ///< Transpose
  NN_FUNCTION_BROADCAST = 79,            ///< Broadcast
  NN_FUNCTION_BROADCAST_TO = 184,        ///< BroadcastTo
  NN_FUNCTION_TILE = 247,                ///< Tile
  NN_FUNCTION_ONE_HOT = 80,              ///< OneHot
  NN_FUNCTION_FLIP = 81,                 ///< Flip
  NN_FUNCTION_SHIFT = 82,                ///< Shift
  NN_FUNCTION_SORT = 129,                ///< Sort
  NN_FUNCTION_RESHAPE_0 = 83,        ///< Recent version of Reshape has arg [iI]
  NN_FUNCTION_RESHAPE = 126,         ///< Reshape
  NN_FUNCTION_SHAPE = 348,           ///< Shape
  NN_FUNCTION_MATRIX_DIAG = 84,      ///< MatrixDiag
  NN_FUNCTION_MATRIX_DIAG_PART = 85, ///< MatrixDiagPart
  NN_FUNCTION_MESHGRID = 334,        ///< Meshgrid
  NN_FUNCTION_BATCH_DET = 276,       ///< BatchDet
  NN_FUNCTION_BATCH_INV = 275,       ///< BatchInv
  NN_FUNCTION_BATCH_LOGDET = 319,    ///< BatchLogdet
  NN_FUNCTION_BATCH_CHOLESKY = 347,  ///< BatchCholesky
  NN_FUNCTION_ASSIGN = 248,          ///< Assign
  NN_FUNCTION_GATHER_0 = 302,        ///< Recent version of Gather has arg [iiI]
  NN_FUNCTION_GATHER = 303,          ///< Gather
  NN_FUNCTION_GATHER_ND = 264,       ///< GatherNd
  NN_FUNCTION_BOOL_GATHER = 339,     ///< BoolGather
  NN_FUNCTION_SCATTER_ND_0 = 271, ///< Recent version of ScatterNd has arg [iI]
  NN_FUNCTION_SCATTER_ND = 342,   ///< ScatterNd
  NN_FUNCTION_SCATTER_ADD = 315,  ///< ScatterAdd
  NN_FUNCTION_BOOL_SCATTER = 340, ///< BoolScatter
  NN_FUNCTION_BOOL_FILL = 341,    ///< BoolFill
  NN_FUNCTION_PACK_PADDED_SEQUENCE = 305, ///< PackPaddedSequence
  NN_FUNCTION_PAD_PACKED_SEQUENCE = 306,  ///< PadPackedSequence
  NN_FUNCTION_NONZERO = 351,              ///< NonZero
  NN_FUNCTION_INTERPOLATE_0 =
      127, ///< Recent version of Interpolate has arg [iIiB]
  NN_FUNCTION_INTERPOLATE_1 =
      286, ///< Recent version of Interpolate has arg [iIiBB]
  NN_FUNCTION_INTERPOLATE = 291, ///< Interpolate
  NN_FUNCTION_ONNX_RESIZE = 352, ///< ONNXResize
  NN_FUNCTION_FFT = 158,         ///< FFT
  NN_FUNCTION_IFFT = 159,        ///< IFFT
  NN_FUNCTION_STFT_0 = 327,      ///< Recent version of STFT has arg [iiiiBi]
  NN_FUNCTION_STFT = 344,        ///< STFT
  NN_FUNCTION_ISTFT_0 = 328,     ///< Recent version of ISTFT has arg [iiiiB]
  NN_FUNCTION_ISTFT = 345,       ///< ISTFT
  NN_FUNCTION_DROPOUT_0 = 86,    ///< Recent version of Dropout has arg [fi]
  NN_FUNCTION_DROPOUT = 336,     ///< Dropout
  NN_FUNCTION_TOP_K_DATA_0 = 87, ///< Recent version of TopKData has arg [iBBi]
  NN_FUNCTION_TOP_K_DATA = 350,  ///< TopKData
  NN_FUNCTION_TOP_K_GRAD = 88,   ///< TopKGrad
  NN_FUNCTION_RAND = 89,         ///< Rand
  NN_FUNCTION_RANDINT = 90,      ///< Randint
  NN_FUNCTION_RANDN = 91,        ///< Randn
  NN_FUNCTION_RAND_BINOMIAL = 289, ///< RandBinomial
  NN_FUNCTION_RAND_BETA = 288,     ///< RandBeta
  NN_FUNCTION_RAND_GAMMA = 290,    ///< RandGamma
  NN_FUNCTION_RANDOM_CHOICE = 246, ///< RandomChoice
  NN_FUNCTION_RANDOM_CROP = 92,    ///< RandomCrop
  NN_FUNCTION_RANDOM_FLIP = 93,    ///< RandomFlip
  NN_FUNCTION_RANDOM_SHIFT_0 =
      94, ///< Recent version of RandomShift has arg [iIiii]
  NN_FUNCTION_RANDOM_SHIFT = 320, ///< RandomShift
  NN_FUNCTION_RANDOM_ERASE_0 =
      283, ///< Recent version of RandomErase has arg [ffFfFiBfFBiiB]
  NN_FUNCTION_RANDOM_ERASE_1 =
      284, ///< Recent version of RandomErase has arg [ffFfFfFiBBiiB]
  NN_FUNCTION_RANDOM_ERASE = 285,             ///< RandomErase
  NN_FUNCTION_IMAGE_AUGMENTATION = 95,        ///< ImageAugmentation
  NN_FUNCTION_SIGMOID_CROSS_ENTROPY = 96,     ///< SigmoidCrossEntropy
  NN_FUNCTION_BINARY_CROSS_ENTROPY = 97,      ///< BinaryCrossEntropy
  NN_FUNCTION_SOFTMAX_CROSS_ENTROPY = 98,     ///< SoftmaxCrossEntropy
  NN_FUNCTION_CATEGORICAL_CROSS_ENTROPY = 99, ///< CategoricalCrossEntropy
  NN_FUNCTION_SQUARED_ERROR = 100,            ///< SquaredError
  NN_FUNCTION_ABSOLUTE_ERROR = 101,           ///< AbsoluteError
  NN_FUNCTION_HUBER_LOSS = 102,               ///< HuberLoss
  NN_FUNCTION_EPSILON_INSENSITIVE_LOSS = 103, ///< EpsilonInsensitiveLoss
  NN_FUNCTION_KL_MULTINOMIAL = 104,           ///< KLMultinomial
  NN_FUNCTION_AFFINE_GRID = 296,              ///< AffineGrid
  NN_FUNCTION_WARP_BY_GRID = 297,             ///< WarpByGrid
  NN_FUNCTION_WARP_BY_FLOW = 277,             ///< WarpByFlow
  NN_FUNCTION_BINARY_SIGMOID = 105,           ///< BinarySigmoid
  NN_FUNCTION_BINARY_TANH = 106,              ///< BinaryTanh
  NN_FUNCTION_BINARY_CONNECT_AFFINE_0 =
      107, ///< Recent version of BinaryConnectAffine has arg [i]
  NN_FUNCTION_BINARY_CONNECT_AFFINE = 235, ///< BinaryConnectAffine
  NN_FUNCTION_BINARY_CONNECT_CONVOLUTION_0 =
      108, ///< Recent version of BinaryConnectConvolution has arg [iiIiIiIi]
  NN_FUNCTION_BINARY_CONNECT_CONVOLUTION = 233, ///< BinaryConnectConvolution
  NN_FUNCTION_BINARY_WEIGHT_AFFINE_0 =
      109, ///< Recent version of BinaryWeightAffine has arg [i]
  NN_FUNCTION_BINARY_WEIGHT_AFFINE = 234, ///< BinaryWeightAffine
  NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION_0 =
      110, ///< Recent version of BinaryWeightConvolution has arg [iiIiIiIi]
  NN_FUNCTION_BINARY_WEIGHT_CONVOLUTION = 232, ///< BinaryWeightConvolution
  NN_FUNCTION_INQ_AFFINE = 111,                ///< INQAffine
  NN_FUNCTION_INQ_CONVOLUTION = 112,           ///< INQConvolution
  NN_FUNCTION_FIXED_POINT_QUANTIZE = 113,      ///< FixedPointQuantize
  NN_FUNCTION_MIN_MAX_QUANTIZE_0 =
      273, ///< Recent version of MinMaxQuantize has arg [fBBB]
  NN_FUNCTION_MIN_MAX_QUANTIZE = 274,         ///< MinMaxQuantize
  NN_FUNCTION_POW2_QUANTIZE = 114,            ///< Pow2Quantize
  NN_FUNCTION_PRUNE = 135,                    ///< Prune
  NN_FUNCTION_QUANTIZE_LINEAR = 293,          ///< QuantizeLinear
  NN_FUNCTION_DEQUANTIZE_LINEAR = 294,        ///< DequantizeLinear
  NN_FUNCTION_TOP_N_ERROR = 115,              ///< TopNError
  NN_FUNCTION_BINARY_ERROR = 116,             ///< BinaryError
  NN_FUNCTION_CONFUSION_MATRIX = 117,         ///< ConfusionMatrix
  NN_FUNCTION_VAT_NOISE = 118,                ///< VATNoise
  NN_FUNCTION_UNLINK = 119,                   ///< Unlink
  NN_FUNCTION_SINK = 120,                     ///< Sink
  NN_FUNCTION_NMS_DETECTION2D = 231,          ///< NmsDetection2d
  NN_FUNCTION_ONNX_NON_MAX_SUPPRESSION = 353, ///< ONNXNonMaxSuppression
  NN_FUNCTION_MAX_POOLING_BACKWARD = 272,     ///< MaxPoolingBackward
  NN_FUNCTION_PATCH_CORRELATION = 280,        ///< PatchCorrelation
  NN_END_OF_FUNCTION = 65535                  // Ensure this type has 16bits
} nn_function_type_t;

/// @brief Function implement type.
typedef enum {
  /// User defined implement has implement type 0 to 99.
  NN_END_OF_USER_DEFINED_FUNCTION_IMPLEMENT = 99,
  /// Select functions automatically with input type.
  NN_FUNCTION_IMPLEMENT_AUTO,
  /// RESERVED: Calculate with 32bit floating point.
  NN_FUNCTION_IMPLEMENT_FLOAT,
  /// RESERVED: Calculate with 16bit fixed point.
  NN_FUNCTION_IMPLEMENT_FIXED16,
  /// RESERVED: Calculate with 8bit fixed point.
  NN_FUNCTION_IMPLEMENT_FIXED8,
  /// Ensure this type has 16bits
  NN_END_OF_IMPLEMENT = 65535
} nn_function_implement_t;

/// @brief Common definition of Function.
/// This type is to be used for the function does not have arguments.

typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_t;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup IndividualFunctions Individual Functions
/// @brief Individual function definitions
/// @{

/// @brief Affine function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis; ///< Original type is [int64]
} nn_function_affine_t;

/// @}

/// @brief RNN function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t num_layers;    ///< Original type is [int64]
  uint32_t nonlinearity; ///< Original type is [string]
  float dropout;         ///< Original type is [float]
  uint8_t bidirectional; ///< Original type is [bool]
  uint8_t training;      ///< Original type is [bool]
} nn_function_rnn_t;

/// @}

/// @brief LSTM function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t num_layers;    ///< Original type is [int64]
  float dropout;         ///< Original type is [float]
  uint8_t bidirectional; ///< Original type is [bool]
  uint8_t training;      ///< Original type is [bool]
} nn_function_lstm_t;

/// @}

/// @brief GRU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t num_layers;    ///< Original type is [int64]
  float dropout;         ///< Original type is [float]
  uint8_t bidirectional; ///< Original type is [bool]
  uint8_t training;      ///< Original type is [bool]
} nn_function_gru_t;

/// @}

/// @brief Convolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;    ///< Original type is [int64]
  nn_list_t pad;        ///< Original type is [Shape]
  nn_list_t stride;     ///< Original type is [Shape]
  nn_list_t dilation;   ///< Original type is [Shape]
  int32_t group;        ///< Original type is [int64]
  uint8_t channel_last; ///< Original type is [bool]
} nn_function_convolution_t;

/// @}

/// @brief FusedConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;     ///< Original type is [int64]
  nn_list_t pad;         ///< Original type is [Shape]
  nn_list_t stride;      ///< Original type is [Shape]
  nn_list_t dilation;    ///< Original type is [Shape]
  int32_t group;         ///< Original type is [int64]
  uint8_t channel_last;  ///< Original type is [bool]
  float decay_rate;      ///< Original type is [float]
  float eps;             ///< Original type is [float]
  uint8_t batch_stat;    ///< Original type is [bool]
  uint32_t nonlinearity; ///< Original type is [string]
  uint32_t pad_mode;     ///< Original type is [string]
  float constant_value;  ///< Original type is [float]
} nn_function_fused_convolution_t;

/// @}

/// @brief DepthwiseConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;  ///< Original type is [int64]
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t multiplier; ///< Original type is [int64]
} nn_function_depthwise_convolution_t;

/// @}

/// @brief Deconvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;        ///< Original type is [int64]
  nn_list_t pad;            ///< Original type is [Shape]
  nn_list_t stride;         ///< Original type is [Shape]
  nn_list_t dilation;       ///< Original type is [Shape]
  int32_t group;            ///< Original type is [int64]
  uint8_t channel_last;     ///< Original type is [bool]
  nn_list_t output_padding; ///< Original type is [Shape]
} nn_function_deconvolution_t;

/// @}

/// @brief DepthwiseDeconvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;  ///< Original type is [int64]
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t divisor;    ///< Original type is [int64]
} nn_function_depthwise_deconvolution_t;

/// @}

/// @brief DeformableConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;        ///< Original type is [int64]
  nn_list_t pad;            ///< Original type is [Shape]
  nn_list_t stride;         ///< Original type is [Shape]
  nn_list_t dilation;       ///< Original type is [Shape]
  int32_t group;            ///< Original type is [int64]
  int32_t deformable_group; ///< Original type is [int64]
  uint8_t channel_last;     ///< Original type is [bool]
} nn_function_deformable_convolution_t;

/// @}

/// @brief AdaptiveSeparableConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_adaptive_separable_convolution_t;

/// @}

/// @brief MaxPooling function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel;      ///< Original type is [Shape]
  nn_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< Original type is [bool]
  nn_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< Original type is [bool]
} nn_function_max_pooling_t;

/// @}

/// @brief AveragePooling function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel;      ///< Original type is [Shape]
  nn_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< Original type is [bool]
  nn_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< Original type is [bool]
  uint8_t including_pad; ///< Original type is [bool]
} nn_function_average_pooling_t;

/// @}

/// @brief GlobalAveragePooling function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_global_average_pooling_t;

/// @}

/// @brief SumPooling function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel;      ///< Original type is [Shape]
  nn_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< Original type is [bool]
  nn_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< Original type is [bool]
} nn_function_sum_pooling_t;

/// @}

/// @brief Unpooling function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel;     ///< Original type is [Shape]
  uint8_t channel_last; ///< Original type is [bool]
} nn_function_unpooling_t;

/// @}

/// @brief Embed function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_embed_t;

/// @}

/// @brief RoiAlign function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t output_size;  ///< Original type is [Shape]
  int32_t sampling_ratio; ///< Original type is [int64]
  uint8_t channel_last;   ///< Original type is [bool]
} nn_function_roi_align_t;

/// @}

/// @brief Sigmoid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_sigmoid_t;

/// @}

/// @brief Swish function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_swish_t;

/// @}

/// @brief Tanh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_tanh_t;

/// @}

/// @brief ReLU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_relu_t;

/// @}

/// @brief LeakyReLU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float alpha;     ///< Original type is [float]
  uint8_t inplace; ///< Original type is [bool]
} nn_function_leaky_relu_t;

/// @}

/// @brief Softmax function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_softmax_t;

/// @}

/// @brief LogSoftmax function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_log_softmax_t;

/// @}

/// @brief ELU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float alpha; ///< Original type is [double]
} nn_function_elu_t;

/// @}

/// @brief SELU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float scale; ///< Original type is [double]
  float alpha; ///< Original type is [double]
} nn_function_selu_t;

/// @}

/// @brief CReLU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_crelu_t;

/// @}

/// @brief CELU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float alpha;  ///< Original type is [double]
  int32_t axis; ///< Original type is [int64]
} nn_function_celu_t;

/// @}

/// @brief PReLU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis; ///< Original type is [int64]
} nn_function_prelu_t;

/// @}

/// @brief GELU function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_gelu_t;

/// @}

/// @brief Mish function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_mish_t;

/// @}

/// @brief ReLU6 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_relu6_t;

/// @}

/// @brief HardSigmoid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_hard_sigmoid_t;

/// @}

/// @brief HardTanh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_hard_tanh_t;

/// @}

/// @brief LogSigmoid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_log_sigmoid_t;

/// @}

/// @brief SoftPlus function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float beta; ///< Original type is [double]
} nn_function_softplus_t;

/// @}

/// @brief SoftSign function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_softsign_t;

/// @}

/// @brief TanhShrink function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_tanh_shrink_t;

/// @}

/// @brief Sinc function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_sinc_t;

/// @}

/// @brief FusedBatchNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;        ///< Original type is [repeated int64]
  float decay_rate;      ///< Original type is [float]
  float eps;             ///< Original type is [float]
  uint8_t batch_stat;    ///< Original type is [bool]
  uint32_t nonlinearity; ///< Original type is [string]
} nn_function_fused_batch_normalization_t;

/// @}

/// @brief BatchNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;     ///< Original type is [repeated int64]
  float decay_rate;   ///< Original type is [float]
  float eps;          ///< Original type is [float]
  uint8_t batch_stat; ///< Original type is [bool]
  uint8_t no_scale;   ///< Original type is [bool]
  uint8_t no_bias;    ///< Original type is [bool]
} nn_function_batch_normalization_t;

/// @}

/// @brief GroupNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t num_groups;   ///< Original type is [int64]
  int32_t channel_axis; ///< Original type is [int64]
  nn_list_t batch_axis; ///< Original type is [repeated int64]
  float eps;            ///< Original type is [float]
  uint8_t no_scale;     ///< Original type is [bool]
  uint8_t no_bias;      ///< Original type is [bool]
} nn_function_group_normalization_t;

/// @}

/// @brief InstanceNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t channel_axis; ///< Original type is [int64]
  nn_list_t batch_axis; ///< Original type is [repeated int64]
  float eps;            ///< Original type is [float]
  uint8_t no_scale;     ///< Original type is [bool]
  uint8_t no_bias;      ///< Original type is [bool]
} nn_function_instance_normalization_t;

/// @}

/// @brief LayerNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t batch_axis; ///< Original type is [repeated int64]
  float eps;            ///< Original type is [float]
  uint8_t no_scale;     ///< Original type is [bool]
  uint8_t no_bias;      ///< Original type is [bool]
} nn_function_layer_normalization_t;

/// @}

/// @brief NormNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float p;        ///< Original type is [float]
  nn_list_t axes; ///< Original type is [repeated int64]
  float eps;      ///< Original type is [float]
} nn_function_norm_normalization_t;

/// @}

/// @brief SyncBatchNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint32_t group;     ///< Original type is [string]
  nn_list_t axes;     ///< Original type is [repeated int64]
  float decay_rate;   ///< Original type is [float]
  float eps;          ///< Original type is [float]
  uint8_t batch_stat; ///< Original type is [bool]
} nn_function_sync_batch_normalization_t;

/// @}

/// @brief TensorNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;   ///< Original type is [repeated int64]
  float eps;        ///< Original type is [float]
  uint8_t no_scale; ///< Original type is [bool]
  uint8_t no_bias;  ///< Original type is [bool]
} nn_function_tensor_normalization_t;

/// @}

/// @brief WeightNormalization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t dim; ///< Original type is [int64]
  float eps;   ///< Original type is [float]
} nn_function_weight_normalization_t;

/// @}

/// @brief WeightStandardization function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t channel_axis; ///< Original type is [int64]
  float eps;            ///< Original type is [float]
} nn_function_weight_standardization_t;

/// @}

/// @brief SpectralNorm function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t dim;      ///< Original type is [int64]
  int32_t itr;      ///< Original type is [int64]
  float eps;        ///< Original type is [float]
  uint8_t test;     ///< Original type is [bool]
  uint8_t output_u; ///< Original type is [bool]
} nn_function_spectral_norm_t;

/// @}

/// @brief MeanSubtraction function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;           ///< Original type is [int64]
  uint8_t update_running_mean; ///< Original type is [bool]
} nn_function_mean_subtraction_t;

/// @}

/// @brief ClipGradByValue function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_clip_grad_by_value_t;

/// @}

/// @brief ClipGradByNorm function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float clip_norm; ///< Original type is [float]
  nn_list_t axes;  ///< Original type is [repeated int64]
} nn_function_clip_grad_by_norm_t;

/// @}

/// @brief Sum function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< Original type is [bool]
} nn_function_sum_t;

/// @}

/// @brief CumSum function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis;      ///< Original type is [int64]
  uint8_t exclusive; ///< Original type is [bool]
  uint8_t reverse;   ///< Original type is [bool]
} nn_function_cumsum_t;

/// @}

/// @brief Mean function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< Original type is [bool]
} nn_function_mean_t;

/// @}

/// @brief Max function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;     ///< Original type is [repeated int64]
  uint8_t keep_dims;  ///< Original type is [bool]
  uint8_t with_index; ///< Original type is [bool]
  uint8_t only_index; ///< Original type is [bool]
} nn_function_max_t;

/// @}

/// @brief Min function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;     ///< Original type is [repeated int64]
  uint8_t keep_dims;  ///< Original type is [bool]
  uint8_t with_index; ///< Original type is [bool]
  uint8_t only_index; ///< Original type is [bool]
} nn_function_min_t;

/// @}

/// @brief Norm function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float p;           ///< Original type is [float]
  nn_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< Original type is [bool]
} nn_function_norm_t;

/// @}

/// @brief Prod function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;    ///< Original type is [repeated int64]
  uint8_t keep_dims; ///< Original type is [bool]
} nn_function_prod_t;

/// @}

/// @brief CumProd function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis;      ///< Original type is [int64]
  uint8_t exclusive; ///< Original type is [bool]
  uint8_t reverse;   ///< Original type is [bool]
} nn_function_cumprod_t;

/// @}

/// @brief ReduceSum function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_reduce_sum_t;

/// @}

/// @brief ReduceMean function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_reduce_mean_t;

/// @}

/// @brief Add2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_add2_t;

/// @}

/// @brief AddN function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_add_n_t;

/// @}

/// @brief BcAdd2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_bc_add2_t;

/// @}

/// @brief Sub2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_sub2_t;

/// @}

/// @brief Mul2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_mul2_t;

/// @}

/// @brief MulN function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_mul_n_t;

/// @}

/// @brief Div2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_div2_t;

/// @}

/// @brief Pow2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace; ///< Original type is [bool]
} nn_function_pow2_t;

/// @}

/// @brief AddScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val;       ///< Original type is [double]
  uint8_t inplace; ///< Original type is [bool]
} nn_function_add_scalar_t;

/// @}

/// @brief MulScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val;       ///< Original type is [double]
  uint8_t inplace; ///< Original type is [bool]
} nn_function_mul_scalar_t;

/// @}

/// @brief PowScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val;       ///< Original type is [double]
  uint8_t inplace; ///< Original type is [bool]
} nn_function_pow_scalar_t;

/// @}

/// @brief RSubScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_r_sub_scalar_t;

/// @}

/// @brief RDivScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_r_div_scalar_t;

/// @}

/// @brief RPowScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_r_pow_scalar_t;

/// @}

/// @brief Sign function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float alpha; ///< Original type is [float]
} nn_function_sign_t;

/// @}

/// @brief Minimum2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_minimum2_t;

/// @}

/// @brief Maximum2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_maximum2_t;

/// @}

/// @brief MinimumScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_minimum_scalar_t;

/// @}

/// @brief MaximumScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_maximum_scalar_t;

/// @}

/// @brief LogicalAnd function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_logical_and_t;

/// @}

/// @brief LogicalOr function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_logical_or_t;

/// @}

/// @brief LogicalXor function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_logical_xor_t;

/// @}

/// @brief Equal function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_equal_t;

/// @}

/// @brief NotEqual function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_not_equal_t;

/// @}

/// @brief GreaterEqual function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_greater_equal_t;

/// @}

/// @brief Greater function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_greater_t;

/// @}

/// @brief LessEqual function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_less_equal_t;

/// @}

/// @brief Less function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_less_t;

/// @}

/// @brief SearchSorted function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t right; ///< Original type is [bool]
} nn_function_searchsorted_t;

/// @}

/// @brief LogicalAndScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t val; ///< Original type is [bool]
} nn_function_logical_and_scalar_t;

/// @}

/// @brief LogicalOrScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t val; ///< Original type is [bool]
} nn_function_logical_or_scalar_t;

/// @}

/// @brief LogicalXorScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t val; ///< Original type is [bool]
} nn_function_logical_xor_scalar_t;

/// @}

/// @brief EqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_equal_scalar_t;

/// @}

/// @brief NotEqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_not_equal_scalar_t;

/// @}

/// @brief GreaterEqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_greater_equal_scalar_t;

/// @}

/// @brief GreaterScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_greater_scalar_t;

/// @}

/// @brief LessEqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_less_equal_scalar_t;

/// @}

/// @brief LessScalar function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_less_scalar_t;

/// @}

/// @brief LogicalNot function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_logical_not_t;

/// @}

/// @brief IsNaN function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_isnan_t;

/// @}

/// @brief IsInf function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_isinf_t;

/// @}

/// @brief ResetNaN function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_reset_nan_t;

/// @}

/// @brief ResetInf function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val; ///< Original type is [double]
} nn_function_reset_inf_t;

/// @}

/// @brief Where function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_where_t;

/// @}

/// @brief Constant function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float val;       ///< Original type is [float]
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_constant_t;

/// @}

/// @brief Arange function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float start; ///< Original type is [float]
  float stop;  ///< Original type is [float]
  float step;  ///< Original type is [float]
} nn_function_arange_t;

/// @}

/// @brief Linspace function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float start; ///< Original type is [float]
  float stop;  ///< Original type is [float]
  int32_t num; ///< Original type is [int64]
} nn_function_linspace_t;

/// @}

/// @brief Abs function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_abs_t;

/// @}

/// @brief Exp function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_exp_t;

/// @}

/// @brief Log function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_log_t;

/// @}

/// @brief Identity function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_identity_t;

/// @}

/// @brief BatchMatmul function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t transpose_a; ///< Original type is [bool]
  uint8_t transpose_b; ///< Original type is [bool]
} nn_function_batch_matmul_t;

/// @}

/// @brief Round function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_round_t;

/// @}

/// @brief Ceil function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_ceil_t;

/// @}

/// @brief Floor function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_floor_t;

/// @}

/// @brief Sin function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_sin_t;

/// @}

/// @brief Cos function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_cos_t;

/// @}

/// @brief Tan function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_tan_t;

/// @}

/// @brief Sinh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_sinh_t;

/// @}

/// @brief Cosh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_cosh_t;

/// @}

/// @brief ASin function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_asin_t;

/// @}

/// @brief ACos function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_acos_t;

/// @}

/// @brief ATan function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_atan_t;

/// @}

/// @brief ATan2 function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_atan2_t;

/// @}

/// @brief ASinh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_asinh_t;

/// @}

/// @brief ACosh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_acosh_t;

/// @}

/// @brief ATanh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_atanh_t;

/// @}

/// @brief Erf function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_erf_t;

/// @}

/// @brief Concatenate function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_concatenate_t;

/// @}

/// @brief Split function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_split_t;

/// @}

/// @brief Stack function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_stack_t;

/// @}

/// @brief Slice function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t start; ///< Original type is [repeated int64]
  nn_list_t stop;  ///< Original type is [repeated int64]
  nn_list_t step;  ///< Original type is [repeated int64]
} nn_function_slice_t;

/// @}

/// @brief Pad function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t pad_width;  ///< Original type is [repeated int64]
  uint32_t mode;        ///< Original type is [string]
  float constant_value; ///< Original type is [float]
} nn_function_pad_t;

/// @}

/// @brief Transpose function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
} nn_function_transpose_t;

/// @}

/// @brief Broadcast function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_broadcast_t;

/// @}

/// @brief BroadcastTo function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_broadcast_to_t;

/// @}

/// @brief Tile function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t reps; ///< Original type is [repeated int64]
} nn_function_tile_t;

/// @}

/// @brief OneHot function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_one_hot_t;

/// @}

/// @brief Flip function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
} nn_function_flip_t;

/// @}

/// @brief Shift function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shifts;     ///< Original type is [repeated int64]
  uint32_t border_mode; ///< Original type is [string]
} nn_function_shift_t;

/// @}

/// @brief Sort function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis;       ///< Original type is [int64]
  uint8_t reverse;    ///< Original type is [bool]
  uint8_t with_index; ///< Original type is [bool]
  uint8_t only_index; ///< Original type is [bool]
} nn_function_sort_t;

/// @}

/// @brief Reshape function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
  uint8_t inplace; ///< Original type is [bool]
} nn_function_reshape_t;

/// @}

/// @brief Shape function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t start; ///< Original type is [int64]
  int32_t end;   ///< Original type is [int64]
} nn_function_shape_t;

/// @}

/// @brief MatrixDiag function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_matrix_diag_t;

/// @}

/// @brief MatrixDiagPart function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_matrix_diag_part_t;

/// @}

/// @brief Meshgrid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t ij_indexing; ///< Original type is [bool]
} nn_function_meshgrid_t;

/// @}

/// @brief BatchDet function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_batch_det_t;

/// @}

/// @brief BatchInv function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_batch_inv_t;

/// @}

/// @brief BatchLogdet function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_batch_logdet_t;

/// @}

/// @brief BatchCholesky function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t upper; ///< Original type is [bool]
} nn_function_batch_cholesky_t;

/// @}

/// @brief Assign function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_assign_t;

/// @}

/// @brief Gather function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis;       ///< Original type is [int64]
  int32_t batch_dims; ///< Original type is [int64]
} nn_function_gather_t;

/// @}

/// @brief GatherNd function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_gather_nd_t;

/// @}

/// @brief BoolGather function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_bool_gather_t;

/// @}

/// @brief ScatterNd function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [repeated int64]
  uint8_t add;     ///< Original type is [bool]
} nn_function_scatter_nd_t;

/// @}

/// @brief ScatterAdd function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_scatter_add_t;

/// @}

/// @brief BoolScatter function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_bool_scatter_t;

/// @}

/// @brief BoolFill function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float value; ///< Original type is [float]
} nn_function_bool_fill_t;

/// @}

/// @brief PackPaddedSequence function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t batch_first; ///< Original type is [bool]
} nn_function_pack_padded_sequence_t;

/// @}

/// @brief PadPackedSequence function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t batch_first;  ///< Original type is [bool]
  float padding_value;  ///< Original type is [float]
  int32_t total_length; ///< Original type is [int64]
} nn_function_pad_packed_sequence_t;

/// @}

/// @brief NonZero function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_nonzero_t;

/// @}

/// @brief Interpolate function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t output_size;     ///< Original type is [repeated int64]
  uint32_t mode;             ///< Original type is [string]
  uint8_t align_corners;     ///< Original type is [bool]
  uint8_t half_pixel;        ///< Original type is [bool]
  uint8_t half_pixel_for_nn; ///< Original type is [bool]
  uint8_t channel_last;      ///< Original type is [bool]
} nn_function_interpolate_t;

/// @}

/// @brief ONNXResize function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t sizes; ///< Original type is [repeated int64]
  uint32_t mode;   ///< Original type is [string]
  uint32_t coordinate_transformation_mode; ///< Original type is [string]
  float cubic_coeff_a;                     ///< Original type is [float]
  int32_t exclude_outside;                 ///< Original type is [int64]
  float extrapolation_value;               ///< Original type is [float]
  uint32_t nearest_mode;                   ///< Original type is [string]
} nn_function_onnx_resize_t;

/// @}

/// @brief FFT function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t signal_ndim; ///< Original type is [int64]
  uint8_t normalized;  ///< Original type is [bool]
} nn_function_fft_t;

/// @}

/// @brief IFFT function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t signal_ndim; ///< Original type is [int64]
  uint8_t normalized;  ///< Original type is [bool]
} nn_function_ifft_t;

/// @}

/// @brief STFT function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t window_size;       ///< Original type is [int64]
  int32_t stride;            ///< Original type is [int64]
  int32_t fft_size;          ///< Original type is [int64]
  uint32_t window_type;      ///< Original type is [string]
  uint8_t center;            ///< Original type is [bool]
  uint32_t pad_mode;         ///< Original type is [string]
  uint8_t as_istft_backward; ///< Original type is [bool]
} nn_function_stft_t;

/// @}

/// @brief ISTFT function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t window_size;      ///< Original type is [int64]
  int32_t stride;           ///< Original type is [int64]
  int32_t fft_size;         ///< Original type is [int64]
  uint32_t window_type;     ///< Original type is [string]
  uint8_t center;           ///< Original type is [bool]
  uint32_t pad_mode;        ///< Original type is [string]
  uint8_t as_stft_backward; ///< Original type is [bool]
} nn_function_istft_t;

/// @}

/// @brief Dropout function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float p;      ///< Original type is [double]
  int32_t seed; ///< Original type is [int64]
} nn_function_dropout_t;

/// @}

/// @brief TopKData function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t k;          ///< Original type is [int64]
  uint8_t abs;        ///< Original type is [bool]
  uint8_t reduce;     ///< Original type is [bool]
  int32_t base_axis;  ///< Original type is [int64]
  uint8_t largest;    ///< Original type is [bool]
  uint8_t with_index; ///< Original type is [bool]
} nn_function_top_k_data_t;

/// @}

/// @brief TopKGrad function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t k;         ///< Original type is [int64]
  uint8_t abs;       ///< Original type is [bool]
  int32_t base_axis; ///< Original type is [int64]
} nn_function_top_k_grad_t;

/// @}

/// @brief Rand function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float low;       ///< Original type is [float]
  float high;      ///< Original type is [float]
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< Original type is [int64]
} nn_function_rand_t;

/// @}

/// @brief Randint function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t low;     ///< Original type is [int64]
  int32_t high;    ///< Original type is [int64]
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< Original type is [int64]
} nn_function_randint_t;

/// @}

/// @brief Randn function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float mu;        ///< Original type is [float]
  float sigma;     ///< Original type is [float]
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< Original type is [int64]
} nn_function_randn_t;

/// @}

/// @brief RandBinomial function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t n;       ///< Original type is [int64]
  float p;         ///< Original type is [float]
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< Original type is [int64]
} nn_function_rand_binomial_t;

/// @}

/// @brief RandBeta function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float alpha;     ///< Original type is [float]
  float beta;      ///< Original type is [float]
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< Original type is [int64]
} nn_function_rand_beta_t;

/// @}

/// @brief RandGamma function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float k;         ///< Original type is [float]
  float theta;     ///< Original type is [float]
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;    ///< Original type is [int64]
} nn_function_rand_gamma_t;

/// @}

/// @brief RandomChoice function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
  uint8_t replace; ///< Original type is [bool]
  int32_t seed;    ///< Original type is [int64]
} nn_function_random_choice_t;

/// @}

/// @brief RandomCrop function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape;   ///< Original type is [Shape]
  int32_t base_axis; ///< Original type is [int64]
  int32_t seed;      ///< Original type is [int64]
} nn_function_random_crop_t;

/// @}

/// @brief RandomFlip function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes;    ///< Original type is [repeated int64]
  int32_t base_axis; ///< Original type is [int64]
  int32_t seed;      ///< Original type is [int64]
} nn_function_random_flip_t;

/// @}

/// @brief RandomShift function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shifts;     ///< Original type is [repeated int64]
  uint32_t border_mode; ///< Original type is [string]
  float constant_value; ///< Original type is [float]
  int32_t base_axis;    ///< Original type is [int64]
  int32_t seed;         ///< Original type is [int64]
} nn_function_random_shift_t;

/// @}

/// @brief RandomErase function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float prob;               ///< Original type is [float]
  int32_t n;                ///< Original type is [int64]
  uint8_t share;            ///< Original type is [bool]
  uint8_t inplace;          ///< Original type is [bool]
  int32_t base_axis;        ///< Original type is [int64]
  int32_t seed;             ///< Original type is [int64]
  uint8_t channel_last;     ///< Original type is [bool]
  uint8_t ste_fine_grained; ///< Original type is [bool]
} nn_function_random_erase_t;

/// @}

/// @brief ImageAugmentation function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape;         ///< Original type is [Shape]
  nn_list_t pad;           ///< Original type is [Shape]
  float min_scale;         ///< Original type is [float]
  float max_scale;         ///< Original type is [float]
  float angle;             ///< Original type is [float]
  float aspect_ratio;      ///< Original type is [float]
  float distortion;        ///< Original type is [float]
  uint8_t flip_lr;         ///< Original type is [bool]
  uint8_t flip_ud;         ///< Original type is [bool]
  float brightness;        ///< Original type is [float]
  uint8_t brightness_each; ///< Original type is [bool]
  float contrast;          ///< Original type is [float]
  float contrast_center;   ///< Original type is [float]
  uint8_t contrast_each;   ///< Original type is [bool]
  float noise;             ///< Original type is [float]
  int32_t seed;            ///< Original type is [int64]
} nn_function_image_augmentation_t;

/// @}

/// @brief SigmoidCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_sigmoid_cross_entropy_t;

/// @}

/// @brief BinaryCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_binary_cross_entropy_t;

/// @}

/// @brief SoftmaxCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_softmax_cross_entropy_t;

/// @}

/// @brief CategoricalCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_categorical_cross_entropy_t;

/// @}

/// @brief SquaredError function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_squared_error_t;

/// @}

/// @brief AbsoluteError function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_absolute_error_t;

/// @}

/// @brief HuberLoss function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float delta; ///< Original type is [float]
} nn_function_huber_loss_t;

/// @}

/// @brief EpsilonInsensitiveLoss function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float epsilon; ///< Original type is [float]
} nn_function_epsilon_insensitive_loss_t;

/// @}

/// @brief KLMultinomial function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis; ///< Original type is [int64]
} nn_function_kl_multinomial_t;

/// @}

/// @brief AffineGrid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t size;        ///< Original type is [repeated int64]
  uint8_t align_corners; ///< Original type is [bool]
} nn_function_affine_grid_t;

/// @}

/// @brief WarpByGrid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint32_t mode;         ///< Original type is [string]
  uint32_t padding_mode; ///< Original type is [string]
  uint8_t align_corners; ///< Original type is [bool]
  uint8_t channel_last;  ///< Original type is [bool]
} nn_function_warp_by_grid_t;

/// @}

/// @brief WarpByFlow function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_warp_by_flow_t;

/// @}

/// @brief BinarySigmoid function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_binary_sigmoid_t;

/// @}

/// @brief BinaryTanh function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_binary_tanh_t;

/// @}

/// @brief BinaryConnectAffine function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;      ///< Original type is [int64]
  float quantize_zero_to; ///< Original type is [float]
} nn_function_binary_connect_affine_t;

/// @}

/// @brief BinaryConnectConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;      ///< Original type is [int64]
  nn_list_t pad;          ///< Original type is [Shape]
  nn_list_t stride;       ///< Original type is [Shape]
  nn_list_t dilation;     ///< Original type is [Shape]
  int32_t group;          ///< Original type is [int64]
  float quantize_zero_to; ///< Original type is [float]
} nn_function_binary_connect_convolution_t;

/// @}

/// @brief BinaryWeightAffine function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;      ///< Original type is [int64]
  float quantize_zero_to; ///< Original type is [float]
} nn_function_binary_weight_affine_t;

/// @}

/// @brief BinaryWeightConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;      ///< Original type is [int64]
  nn_list_t pad;          ///< Original type is [Shape]
  nn_list_t stride;       ///< Original type is [Shape]
  nn_list_t dilation;     ///< Original type is [Shape]
  int32_t group;          ///< Original type is [int64]
  float quantize_zero_to; ///< Original type is [float]
} nn_function_binary_weight_convolution_t;

/// @}

/// @brief INQAffine function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;            ///< Original type is [int64]
  int32_t num_bits;             ///< Original type is [int64]
  nn_list_t inq_iterations;     ///< Original type is [repeated int64]
  uint32_t selection_algorithm; ///< Original type is [string]
  int32_t seed;                 ///< Original type is [int64]
} nn_function_inq_affine_t;

/// @}

/// @brief INQConvolution function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;            ///< Original type is [int64]
  nn_list_t pad;                ///< Original type is [Shape]
  nn_list_t stride;             ///< Original type is [Shape]
  nn_list_t dilation;           ///< Original type is [Shape]
  int32_t group;                ///< Original type is [int64]
  int32_t num_bits;             ///< Original type is [int64]
  nn_list_t inq_iterations;     ///< Original type is [repeated int64]
  uint32_t selection_algorithm; ///< Original type is [string]
  int32_t seed;                 ///< Original type is [int64]
} nn_function_inq_convolution_t;

/// @}

/// @brief FixedPointQuantize function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t sign;             ///< Original type is [bool]
  int32_t n;                ///< Original type is [int64]
  float delta;              ///< Original type is [float]
  uint8_t ste_fine_grained; ///< Original type is [bool]
} nn_function_fixed_point_quantize_t;

/// @}

/// @brief MinMaxQuantize function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float decay;              ///< Original type is [float]
  uint8_t x_min_max;        ///< Original type is [bool]
  uint8_t ema;              ///< Original type is [bool]
  uint8_t ste_fine_grained; ///< Original type is [bool]
  float eps;                ///< Original type is [float]
} nn_function_min_max_quantize_t;

/// @}

/// @brief Pow2Quantize function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t sign;             ///< Original type is [bool]
  uint8_t with_zero;        ///< Original type is [bool]
  int32_t n;                ///< Original type is [int64]
  int32_t m;                ///< Original type is [int64]
  uint8_t ste_fine_grained; ///< Original type is [bool]
} nn_function_pow2_quantize_t;

/// @}

/// @brief Prune function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float rate; ///< Original type is [float]
} nn_function_prune_t;

/// @}

/// @brief QuantizeLinear function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint32_t round_mode;  ///< Original type is [string]
  uint8_t narrow_range; ///< Original type is [bool]
  int32_t dtype;        ///< Original type is [int64]
} nn_function_quantize_linear_t;

/// @}

/// @brief DequantizeLinear function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_dequantize_linear_t;

/// @}

/// @brief TopNError function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
  int32_t n;    ///< Original type is [int64]
} nn_function_top_n_error_t;

/// @}

/// @brief BinaryError function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_binary_error_t;

/// @}

/// @brief ConfusionMatrix function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t axis; ///< Original type is [int64]
} nn_function_confusion_matrix_t;

/// @}

/// @brief VATNoise function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis; ///< Original type is [int64]
  float eps;         ///< Original type is [float]
} nn_function_vat_noise_t;

/// @}

/// @brief Unlink function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
} nn_function_unlink_t;

/// @}

/// @brief Sink function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  uint8_t one_input_grad; ///< Original type is [bool]
} nn_function_sink_t;

/// @}

/// @brief NmsDetection2d function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  float thresh;          ///< Original type is [float]
  float nms;             ///< Original type is [float]
  uint8_t nms_per_class; ///< Original type is [bool]
} nn_function_nms_detection2d_t;

/// @}

/// @brief ONNXNonMaxSuppression function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  int32_t center_point_box;           ///< Original type is [int64]
  int32_t max_output_boxes_per_class; ///< Original type is [int64]
  float iou_threshold;                ///< Original type is [float]
  float score_threshold;              ///< Original type is [float]
} nn_function_onnx_non_max_suppression_t;

/// @}

/// @brief MaxPoolingBackward function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel;      ///< Original type is [Shape]
  nn_list_t stride;      ///< Original type is [Shape]
  uint8_t ignore_border; ///< Original type is [bool]
  nn_list_t pad;         ///< Original type is [Shape]
  uint8_t channel_last;  ///< Original type is [bool]
} nn_function_max_pooling_backward_t;

/// @}

/// @brief PatchCorrelation function.
/// @{
typedef struct {
  nn_function_type_t type : 16;      ///< Common: type of function.
  nn_function_implement_t impl : 16; ///< Common: function implementation.
  nn_list_t inputs;                  ///< Common: List of input variables.
  nn_list_t outputs;                 ///< Common: List of output variables.
  // End of common part.
  nn_list_t patch;      ///< Original type is [Shape]
  nn_list_t shift;      ///< Original type is [Shape]
  nn_list_t patch_step; ///< Original type is [Shape]
  nn_list_t shift_step; ///< Original type is [Shape]
  nn_list_t padding;    ///< Original type is [Shape]
} nn_function_patch_correlation_t;

/// @}

/// @}

/// Define memory size at the end of nn_network_t.
typedef struct {
  nn_size_t num_of_data; ///< Number of datum
  nn_size_t data_size;   ///< Total data size in byte
} nn_memory_t;

/// @brief Definition of Network.
///
typedef struct {
  uint32_t version;    ///< binary format version
  uint32_t api_level;  ///< function-level compatibility revision
  nn_list_t buffers;   ///< list of nn_variable_buffer_t
  nn_list_t variables; ///< list of nn_variable_t
  nn_list_t functions; ///< list of nn_function_t
  nn_list_t inputs;    ///< list of input variable ids
  nn_list_t outputs;   ///< list of output variable ids
  nn_memory_t memory;  ///< memory to store all data.
} nn_network_t;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup ErrorCodes Common Error codes
///
/// @{
#define NN_ERROR_CODE_NOERROR (0) ///< No error
/// @}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup DebugFunctions Debug functionality
///
/// @{
#ifndef WHOAMI
/// Print specified message and position itself.
#define WHOAMI(...)                                                            \
  {                                                                            \
    printf("%s:%d: ", __FILE__, __LINE__);                                     \
    printf(__VA_ARGS__);                                                       \
    printf("\n");                                                              \
    fflush(stdout);                                                            \
  }
#endif // WHOAMI
/// @}

/// @}
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // H_NETWORK_H__
