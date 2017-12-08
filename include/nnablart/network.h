// -*- coding:utf-8 -*-
#ifndef H_NETWORK_H__
#define H_NETWORK_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h> // for fixed bit length integer type
#include <stdlib.h> // for size_t

#define NN_BINARY_FORMAT_VERSION 3d4ae1acb9d6eedc8ab53416ec16cbe7

/// @defgroup NetworkDefinitions Internal network representation
///
/// ネットワークの構造をメモリ上に格納するための構造体と、データにアク
/// セスするためのマクロ群から構成されています。ネットワークデータを保
/// 存する際にシリアライズを不要にするため、データへのアクセスは全てポ
/// インタではなく、データバッファ内のインデックスを用いて行います。
///
///
/// @{

typedef int32_t pointer_index_t; ///< データの場所を示すインデックス
typedef uint32_t nn_size_t; ///< データの場所を示すインデックス

/// @brief 整数のリスト
typedef struct {
  nn_size_t size;       ///< リストのサイズ
  pointer_index_t list; ///< リストデータへのインデックス
} nn_list_t;

/// @brief Parameter types.
typedef enum {
  NN_PARAM_TYPE_FLOAT, ///< 32bit float.
  NN_PARAM_TYPE_INT16, ///< 16bit integer.
  NN_PARAM_TYPE_INT8,  ///<  8bit integer.
  NN_PARAM_TYPE_SIGN   ///< Binary.
} nn_param_type_t;

/// @brief Definition of Parameter.
typedef struct {
  uint32_t variable_id; ///< Variable that uses this parameter.
  nn_list_t shape;      ///< Shape of param
  nn_param_type_t type; ///< Type of param values
  nn_size_t scale;      ///< Scale of param values
  pointer_index_t data; ///< Location of param data
} nn_param_t;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Functions エッジの定義
/// @brief Definitions for functions.
/// @{

/// @brief Function types.
typedef enum {
  NN_FUNCTION_AFFINE,                   ///< Affine
  NN_FUNCTION_CONVOLUTION,              ///< Convolution
  NN_FUNCTION_DEPTHWISECONVOLUTION,     ///< DepthwiseConvolution
  NN_FUNCTION_DECONVOLUTION,            ///< Deconvolution
  NN_FUNCTION_MAXPOOLING,               ///< MaxPooling
  NN_FUNCTION_AVERAGEPOOLING,           ///< AveragePooling
  NN_FUNCTION_SUMPOOLING,               ///< SumPooling
  NN_FUNCTION_UNPOOLING,                ///< Unpooling
  NN_FUNCTION_EMBED,                    ///< Embed
  NN_FUNCTION_SIGMOID,                  ///< Sigmoid
  NN_FUNCTION_SWISH,                    ///< Swish
  NN_FUNCTION_TANH,                     ///< Tanh
  NN_FUNCTION_RELU,                     ///< ReLU
  NN_FUNCTION_LEAKYRELU,                ///< LeakyReLU
  NN_FUNCTION_SOFTMAX,                  ///< Softmax
  NN_FUNCTION_ELU,                      ///< ELU
  NN_FUNCTION_SELU,                     ///< SELU
  NN_FUNCTION_CRELU,                    ///< CReLU
  NN_FUNCTION_CELU,                     ///< CELU
  NN_FUNCTION_PRELU,                    ///< PReLU
  NN_FUNCTION_BATCHNORMALIZATION,       ///< BatchNormalization
  NN_FUNCTION_MEANSUBTRACTION,          ///< MeanSubtraction
  NN_FUNCTION_SUM,                      ///< Sum
  NN_FUNCTION_MEAN,                     ///< Mean
  NN_FUNCTION_MAX,                      ///< Max
  NN_FUNCTION_MIN,                      ///< Min
  NN_FUNCTION_PROD,                     ///< Prod
  NN_FUNCTION_REDUCESUM,                ///< ReduceSum
  NN_FUNCTION_REDUCEMEAN,               ///< ReduceMean
  NN_FUNCTION_ADD2,                     ///< Add2
  NN_FUNCTION_BCADD2,                   ///< BcAdd2
  NN_FUNCTION_SUB2,                     ///< Sub2
  NN_FUNCTION_MUL2,                     ///< Mul2
  NN_FUNCTION_DIV2,                     ///< Div2
  NN_FUNCTION_POW2,                     ///< Pow2
  NN_FUNCTION_ADDSCALAR,                ///< AddScalar
  NN_FUNCTION_MULSCALAR,                ///< MulScalar
  NN_FUNCTION_POWSCALAR,                ///< PowScalar
  NN_FUNCTION_RSUBSCALAR,               ///< RSubScalar
  NN_FUNCTION_RDIVSCALAR,               ///< RDivScalar
  NN_FUNCTION_RPOWSCALAR,               ///< RPowScalar
  NN_FUNCTION_SIGN,                     ///< Sign
  NN_FUNCTION_MINIMUM2,                 ///< Minimum2
  NN_FUNCTION_MAXIMUM2,                 ///< Maximum2
  NN_FUNCTION_MINIMUMSCALAR,            ///< MinimumScalar
  NN_FUNCTION_MAXIMUMSCALAR,            ///< MaximumScalar
  NN_FUNCTION_LOGICALAND,               ///< LogicalAnd
  NN_FUNCTION_LOGICALOR,                ///< LogicalOr
  NN_FUNCTION_LOGICALXOR,               ///< LogicalXor
  NN_FUNCTION_EQUAL,                    ///< Equal
  NN_FUNCTION_NOTEQUAL,                 ///< NotEqual
  NN_FUNCTION_GREATEREQUAL,             ///< GreaterEqual
  NN_FUNCTION_GREATER,                  ///< Greater
  NN_FUNCTION_LESSEQUAL,                ///< LessEqual
  NN_FUNCTION_LESS,                     ///< Less
  NN_FUNCTION_LOGICALANDSCALAR,         ///< LogicalAndScalar
  NN_FUNCTION_LOGICALORSCALAR,          ///< LogicalOrScalar
  NN_FUNCTION_LOGICALXORSCALAR,         ///< LogicalXorScalar
  NN_FUNCTION_EQUALSCALAR,              ///< EqualScalar
  NN_FUNCTION_NOTEQUALSCALAR,           ///< NotEqualScalar
  NN_FUNCTION_GREATEREQUALSCALAR,       ///< GreaterEqualScalar
  NN_FUNCTION_GREATERSCALAR,            ///< GreaterScalar
  NN_FUNCTION_LESSEQUALSCALAR,          ///< LessEqualScalar
  NN_FUNCTION_LESSSCALAR,               ///< LessScalar
  NN_FUNCTION_LOGICALNOT,               ///< LogicalNot
  NN_FUNCTION_CONSTANT,                 ///< Constant
  NN_FUNCTION_ABS,                      ///< Abs
  NN_FUNCTION_EXP,                      ///< Exp
  NN_FUNCTION_LOG,                      ///< Log
  NN_FUNCTION_IDENTITY,                 ///< Identity
  NN_FUNCTION_BATCHMATMUL,              ///< BatchMatmul
  NN_FUNCTION_CONCATENATE,              ///< Concatenate
  NN_FUNCTION_SPLIT,                    ///< Split
  NN_FUNCTION_STACK,                    ///< Stack
  NN_FUNCTION_SLICE,                    ///< Slice
  NN_FUNCTION_TRANSPOSE,                ///< Transpose
  NN_FUNCTION_BROADCAST,                ///< Broadcast
  NN_FUNCTION_ONEHOT,                   ///< OneHot
  NN_FUNCTION_FLIP,                     ///< Flip
  NN_FUNCTION_SHIFT,                    ///< Shift
  NN_FUNCTION_RESHAPE,                  ///< Reshape
  NN_FUNCTION_MATRIXDIAG,               ///< MatrixDiag
  NN_FUNCTION_MATRIXDIAGPART,           ///< MatrixDiagPart
  NN_FUNCTION_DROPOUT,                  ///< Dropout
  NN_FUNCTION_RAND,                     ///< Rand
  NN_FUNCTION_RANDINT,                  ///< Randint
  NN_FUNCTION_RANDN,                    ///< Randn
  NN_FUNCTION_RANDOMCROP,               ///< RandomCrop
  NN_FUNCTION_RANDOMFLIP,               ///< RandomFlip
  NN_FUNCTION_RANDOMSHIFT,              ///< RandomShift
  NN_FUNCTION_IMAGEAUGMENTATION,        ///< ImageAugmentation
  NN_FUNCTION_SIGMOIDCROSSENTROPY,      ///< SigmoidCrossEntropy
  NN_FUNCTION_BINARYCROSSENTROPY,       ///< BinaryCrossEntropy
  NN_FUNCTION_SOFTMAXCROSSENTROPY,      ///< SoftmaxCrossEntropy
  NN_FUNCTION_CATEGORICALCROSSENTROPY,  ///< CategoricalCrossEntropy
  NN_FUNCTION_SQUAREDERROR,             ///< SquaredError
  NN_FUNCTION_ABSOLUTEERROR,            ///< AbsoluteError
  NN_FUNCTION_HUBERLOSS,                ///< HuberLoss
  NN_FUNCTION_EPSILONINSENSITIVELOSS,   ///< EpsilonInsensitiveLoss
  NN_FUNCTION_KLMULTINOMIAL,            ///< KLMultinomial
  NN_FUNCTION_BINARYSIGMOID,            ///< BinarySigmoid
  NN_FUNCTION_BINARYTANH,               ///< BinaryTanh
  NN_FUNCTION_BINARYCONNECTAFFINE,      ///< BinaryConnectAffine
  NN_FUNCTION_BINARYCONNECTCONVOLUTION, ///< BinaryConnectConvolution
  NN_FUNCTION_BINARYWEIGHTAFFINE,       ///< BinaryWeightAffine
  NN_FUNCTION_BINARYWEIGHTCONVOLUTION,  ///< BinaryWeightConvolution
  NN_FUNCTION_INQAFFINE,                ///< INQAffine
  NN_FUNCTION_INQCONVOLUTION,           ///< INQConvolution
  NN_FUNCTION_FIXEDPOINTQUANTIZE,       ///< FixedPointQuantize
  NN_FUNCTION_POW2QUANTIZE,             ///< Pow2Quantize
  NN_FUNCTION_TOPNERROR,                ///< TopNError
  NN_FUNCTION_BINARYERROR,              ///< BinaryError
  NN_FUNCTION_CONFUSIONMATRIX,          ///< ConfusionMatrix
  NN_FUNCTION_VATNOISE,                 ///< VATNoise
  NN_FUNCTION_UNLINK,                   ///< Unlink
  NN_FUNCTION_SINK,                     ///< Sink
} nn_function_type_t;

/// @brief Common definition of Function.
/// This type is to be used for the function does not have arguements.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_t;

/// @}

/// @brief Affine function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
} nn_function_affine_t;

/// @}

/// @brief Convolution function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t group;
} nn_function_convolution_t;

/// @}

/// @brief DepthwiseConvolution function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t multiplier;
} nn_function_depthwise_convolution_t;

/// @}

/// @brief Deconvolution function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t group;
} nn_function_deconvolution_t;

/// @}

/// @brief MaxPooling function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel; ///< Original type is [Shape]
  nn_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  nn_list_t pad; ///< Original type is [Shape]
} nn_function_max_pooling_t;

/// @}

/// @brief AveragePooling function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel; ///< Original type is [Shape]
  nn_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  nn_list_t pad; ///< Original type is [Shape]
  uint8_t including_pad;
} nn_function_average_pooling_t;

/// @}

/// @brief SumPooling function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel; ///< Original type is [Shape]
  nn_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  nn_list_t pad; ///< Original type is [Shape]
} nn_function_sum_pooling_t;

/// @}

/// @brief Unpooling function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t kernel; ///< Original type is [Shape]
} nn_function_unpooling_t;

/// @}

/// @brief Embed function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_embed_t;

/// @}

/// @brief Sigmoid function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_sigmoid_t;

/// @}

/// @brief Swish function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_swish_t;

/// @}

/// @brief Tanh function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_tanh_t;

/// @}

/// @brief ReLU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace;
} nn_function_relu_t;

/// @}

/// @brief LeakyReLU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float alpha;
} nn_function_leaky_relu_t;

/// @}

/// @brief Softmax function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_softmax_t;

/// @}

/// @brief ELU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float alpha;
} nn_function_elu_t;

/// @}

/// @brief SELU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float scale;
  float alpha;
} nn_function_selu_t;

/// @}

/// @brief CReLU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_crelu_t;

/// @}

/// @brief CELU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float alpha;
  int32_t axis;
} nn_function_celu_t;

/// @}

/// @brief PReLU function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
} nn_function_prelu_t;

/// @}

/// @brief BatchNormalization function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  float decay_rate;
  float eps;
  uint8_t batch_stat;
} nn_function_batch_normalization_t;

/// @}

/// @brief MeanSubtraction function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  uint8_t update_running_mean;
} nn_function_mean_subtraction_t;

/// @}

/// @brief Sum function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
} nn_function_sum_t;

/// @}

/// @brief Mean function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
} nn_function_mean_t;

/// @}

/// @brief Max function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
} nn_function_max_t;

/// @}

/// @brief Min function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
} nn_function_min_t;

/// @}

/// @brief Prod function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
} nn_function_prod_t;

/// @}

/// @brief ReduceSum function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_reduce_sum_t;

/// @}

/// @brief ReduceMean function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_reduce_mean_t;

/// @}

/// @brief Add2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t inplace;
} nn_function_add2_t;

/// @}

/// @brief BcAdd2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_bc_add2_t;

/// @}

/// @brief Sub2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_sub2_t;

/// @}

/// @brief Mul2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_mul2_t;

/// @}

/// @brief Div2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_div2_t;

/// @}

/// @brief Pow2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_pow2_t;

/// @}

/// @brief AddScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_add_scalar_t;

/// @}

/// @brief MulScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_mul_scalar_t;

/// @}

/// @brief PowScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_pow_scalar_t;

/// @}

/// @brief RSubScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_r_sub_scalar_t;

/// @}

/// @brief RDivScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_r_div_scalar_t;

/// @}

/// @brief RPowScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_r_pow_scalar_t;

/// @}

/// @brief Sign function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float alpha;
} nn_function_sign_t;

/// @}

/// @brief Minimum2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_minimum2_t;

/// @}

/// @brief Maximum2 function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_maximum2_t;

/// @}

/// @brief MinimumScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_minimum_scalar_t;

/// @}

/// @brief MaximumScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_maximum_scalar_t;

/// @}

/// @brief LogicalAnd function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_logical_and_t;

/// @}

/// @brief LogicalOr function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_logical_or_t;

/// @}

/// @brief LogicalXor function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_logical_xor_t;

/// @}

/// @brief Equal function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_equal_t;

/// @}

/// @brief NotEqual function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_not_equal_t;

/// @}

/// @brief GreaterEqual function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_greater_equal_t;

/// @}

/// @brief Greater function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_greater_t;

/// @}

/// @brief LessEqual function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_less_equal_t;

/// @}

/// @brief Less function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_less_t;

/// @}

/// @brief LogicalAndScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t val;
} nn_function_logical_and_scalar_t;

/// @}

/// @brief LogicalOrScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t val;
} nn_function_logical_or_scalar_t;

/// @}

/// @brief LogicalXorScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t val;
} nn_function_logical_xor_scalar_t;

/// @}

/// @brief EqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_equal_scalar_t;

/// @}

/// @brief NotEqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_not_equal_scalar_t;

/// @}

/// @brief GreaterEqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_greater_equal_scalar_t;

/// @}

/// @brief GreaterScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_greater_scalar_t;

/// @}

/// @brief LessEqualScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_less_equal_scalar_t;

/// @}

/// @brief LessScalar function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
} nn_function_less_scalar_t;

/// @}

/// @brief LogicalNot function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_logical_not_t;

/// @}

/// @brief Constant function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float val;
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_constant_t;

/// @}

/// @brief Abs function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_abs_t;

/// @}

/// @brief Exp function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_exp_t;

/// @}

/// @brief Log function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_log_t;

/// @}

/// @brief Identity function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_identity_t;

/// @}

/// @brief BatchMatmul function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t transpose_a;
  uint8_t transpose_b;
} nn_function_batch_matmul_t;

/// @}

/// @brief Concatenate function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_concatenate_t;

/// @}

/// @brief Split function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_split_t;

/// @}

/// @brief Stack function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_stack_t;

/// @}

/// @brief Slice function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t start; ///< Original type is [repeated int64]
  nn_list_t stop;  ///< Original type is [repeated int64]
  nn_list_t step;  ///< Original type is [repeated int64]
} nn_function_slice_t;

/// @}

/// @brief Transpose function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
} nn_function_transpose_t;

/// @}

/// @brief Broadcast function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_broadcast_t;

/// @}

/// @brief OneHot function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_one_hot_t;

/// @}

/// @brief Flip function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
} nn_function_flip_t;

/// @}

/// @brief Shift function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shifts;     ///< Original type is [repeated int64]
  uint32_t border_mode; ///< Original type is [string]
} nn_function_shift_t;

/// @}

/// @brief Reshape function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
} nn_function_reshape_t;

/// @}

/// @brief MatrixDiag function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_matrix_diag_t;

/// @}

/// @brief MatrixDiagPart function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_matrix_diag_part_t;

/// @}

/// @brief Dropout function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float p;
  int32_t seed;
} nn_function_dropout_t;

/// @}

/// @brief Rand function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float low;
  float high;
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;
} nn_function_rand_t;

/// @}

/// @brief Randint function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t low;
  int32_t high;
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;
} nn_function_randint_t;

/// @}

/// @brief Randn function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float mu;
  float sigma;
  nn_list_t shape; ///< Original type is [Shape]
  int32_t seed;
} nn_function_randn_t;

/// @}

/// @brief RandomCrop function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
  int32_t base_axis;
  int32_t seed;
} nn_function_random_crop_t;

/// @}

/// @brief RandomFlip function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t axes; ///< Original type is [repeated int64]
  int32_t base_axis;
  int32_t seed;
} nn_function_random_flip_t;

/// @}

/// @brief RandomShift function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shifts;     ///< Original type is [repeated int64]
  uint32_t border_mode; ///< Original type is [string]
  int32_t base_axis;
  int32_t seed;
} nn_function_random_shift_t;

/// @}

/// @brief ImageAugmentation function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  nn_list_t shape; ///< Original type is [Shape]
  nn_list_t pad;   ///< Original type is [Shape]
  float min_scale;
  float max_scale;
  float angle;
  float aspect_ratio;
  float distortion;
  uint8_t flip_lr;
  uint8_t flip_ud;
  float brightness;
  uint8_t brightness_each;
  float contrast;
  float contrast_center;
  uint8_t contrast_each;
  float noise;
  int32_t seed;
} nn_function_image_augmentation_t;

/// @}

/// @brief SigmoidCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_sigmoid_cross_entropy_t;

/// @}

/// @brief BinaryCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_binary_cross_entropy_t;

/// @}

/// @brief SoftmaxCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_softmax_cross_entropy_t;

/// @}

/// @brief CategoricalCrossEntropy function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_categorical_cross_entropy_t;

/// @}

/// @brief SquaredError function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_squared_error_t;

/// @}

/// @brief AbsoluteError function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_absolute_error_t;

/// @}

/// @brief HuberLoss function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float delta;
} nn_function_huber_loss_t;

/// @}

/// @brief EpsilonInsensitiveLoss function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  float epsilon;
} nn_function_epsilon_insensitive_loss_t;

/// @}

/// @brief KLMultinomial function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
} nn_function_kl_multinomial_t;

/// @}

/// @brief BinarySigmoid function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_binary_sigmoid_t;

/// @}

/// @brief BinaryTanh function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_binary_tanh_t;

/// @}

/// @brief BinaryConnectAffine function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
} nn_function_binary_connect_affine_t;

/// @}

/// @brief BinaryConnectConvolution function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t group;
} nn_function_binary_connect_convolution_t;

/// @}

/// @brief BinaryWeightAffine function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
} nn_function_binary_weight_affine_t;

/// @}

/// @brief BinaryWeightConvolution function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t group;
} nn_function_binary_weight_convolution_t;

/// @}

/// @brief INQAffine function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  int32_t num_bits;
  nn_list_t inq_iterations;     ///< Original type is [repeated int64]
  uint32_t selection_algorithm; ///< Original type is [string]
  int32_t seed;
} nn_function_inq_affine_t;

/// @}

/// @brief INQConvolution function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  nn_list_t pad;      ///< Original type is [Shape]
  nn_list_t stride;   ///< Original type is [Shape]
  nn_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  int32_t num_bits;
  nn_list_t inq_iterations;     ///< Original type is [repeated int64]
  uint32_t selection_algorithm; ///< Original type is [string]
  int32_t seed;
} nn_function_inq_convolution_t;

/// @}

/// @brief FixedPointQuantize function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t sign;
  int32_t n;
  float delta;
  uint8_t ste_fine_grained;
} nn_function_fixed_point_quantize_t;

/// @}

/// @brief Pow2Quantize function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t sign;
  uint8_t with_zero;
  int32_t n;
  int32_t m;
  uint8_t ste_fine_grained;
} nn_function_pow2_quantize_t;

/// @}

/// @brief TopNError function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
  int32_t n;
} nn_function_top_n_error_t;

/// @}

/// @brief BinaryError function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_binary_error_t;

/// @}

/// @brief ConfusionMatrix function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t axis;
} nn_function_confusion_matrix_t;

/// @}

/// @brief VATNoise function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  int32_t base_axis;
  float eps;
} nn_function_vat_noise_t;

/// @}

/// @brief Unlink function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
} nn_function_unlink_t;

/// @}

/// @brief Sink function.
/// @{
typedef struct {
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
  // End of common part.
  uint8_t one_input_grad;
} nn_function_sink_t;

/// @}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Network ネットワーク定義
/// @brief Definitions for network.
/// @{

/// @brief Definition of Variable.
typedef struct {
  uint32_t id;
  nn_list_t shape;
  int32_t buffer_index;
} nn_variable_t;

typedef struct {
  nn_size_t num_of_data;
  nn_size_t data_size;
} nn_memory_t;

/// @brief Definition of Network.
///
typedef struct {
  uint32_t version;     ///< nnablart version.
  nn_list_t inputs;     ///< list of nn_variable_t
  nn_list_t outputs;    ///< list of nn_variable_t
  nn_list_t functions;  ///< list of nn_function_t
  nn_list_t parameters; ///< list of nn_param_t
  nn_list_t variables;  ///< list of nn_variable_t
  nn_memory_t memory;   ///< memory to store all data.
} nn_network_t;

/// @}
/// @}
/// @}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup DebugFunctions デバッグ用
///
/// @{
#ifndef WHOAMI
#define WHOAMI(...)                                                            \
  {                                                                            \
    printf("%s:%d :", __FILE__, __LINE__);                                     \
    printf(__VA_ARGS__);                                                       \
    fflush(stdout);                                                            \
  }
#endif // WHOAMI
/// @}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // H_NETWORK_H__
