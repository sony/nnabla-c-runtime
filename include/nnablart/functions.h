// -*- coding:utf-8 -*-
#ifndef H_FUNCTIONS_H__
#define H_FUNCTIONS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdio.h>

#include <nnablart/network.h>

// Definitions.
#define INT8_BIT_LENGTH (8)
#define INT16_BIT_LENGTH (16)

// version of cforwardprop library
#define NNABLART_MAJOR_VERSION (1)
#define NNABLART_MINOR_VERSION (0)

typedef struct {
  int size;
  int *data;
} rt_list_t;

typedef struct rt_param_t {
  rt_list_t shape;
  nn_param_type_t type; ///< Type of param values
  float coefficient;    ///< Coefficient value for convert int to float.
  void *data;           ///< Pointer to param data
  float (*get)(struct rt_param_t *, nn_size_t); ///< Get data from position
  void (*set)(struct rt_param_t *, nn_size_t,
              float); ///< Get data from position
} rt_param_t;

#define GET_FLOAT(xParam, xPos) (*((float *)((xParam)->data) + (xPos)))
float getFloat(rt_param_t *param, nn_size_t pos);
#define GET_INT16(xParam, xPos)                                                \
  ((xParam)->coefficient * (float)(*((int16_t *)((xParam)->data) + (xPos))))
float getInt16(rt_param_t *param, nn_size_t pos);
#define GET_INT8(xParam, xPos)                                                 \
  ((xParam)->coefficient * (float)(*((int8_t *)((xParam)->data) + (xPos))))
float getInt8(rt_param_t *param, nn_size_t pos);
#define GET_SIGN(xParam, xPos) getSign(xParam, xPos)
float getSign(rt_param_t *param, nn_size_t pos);

void setFloat(rt_param_t *param, nn_size_t pos, float value);
void setInt16(rt_param_t *param, nn_size_t pos, float value);
void setInt8(rt_param_t *param, nn_size_t pos, float value);
void setSign(rt_param_t *param, nn_size_t pos, float value);

typedef enum {
  RT_BUFFER_ALLOCATE_TYPE_MALLOC = 0,
  RT_BUFFER_ALLOCATE_TYPE_STINGY,
  RT_BUFFER_ALLOCATE_TYPE_INPUT,
  RT_BUFFER_ALLOCATE_TYPE_OUTPUT,
} rt_buffer_allocate_type_t;

typedef struct {
  rt_list_t shape;
  rt_buffer_allocate_type_t allocate_type;
  float *buffer;
} Variable;

typedef struct {
  int num_of_inputs;
  Variable **inputs;

  int num_of_outputs;
  Variable **outputs;

  void *config;
} Function;

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

// Affine
typedef struct {
  int32_t base_axis;
  void *local_context;
} AffineConfig;
void initAffineConfig(AffineConfig *config, int32_t base_axis);
void initAffineLocalContext(Function *f);
void freeAffineLocalContext(Function *f);
void execAffine(Function *f);

// Convolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} ConvolutionConfig;
void initConvolutionConfig(ConvolutionConfig *config, int32_t base_axis,
                           rt_list_t pad, rt_list_t stride, rt_list_t dilation,
                           int32_t group);
void initConvolutionLocalContext(Function *f);
void freeConvolutionLocalContext(Function *f);
void execConvolution(Function *f);

// DepthwiseConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t multiplier;
  void *local_context;
} DepthwiseConvolutionConfig;
void initDepthwiseConvolutionConfig(DepthwiseConvolutionConfig *config,
                                    int32_t base_axis, rt_list_t pad,
                                    rt_list_t stride, rt_list_t dilation,
                                    int32_t multiplier);
void initDepthwiseConvolutionLocalContext(Function *f);
void freeDepthwiseConvolutionLocalContext(Function *f);
void execDepthwiseConvolution(Function *f);

// Deconvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} DeconvolutionConfig;
void initDeconvolutionConfig(DeconvolutionConfig *config, int32_t base_axis,
                             rt_list_t pad, rt_list_t stride,
                             rt_list_t dilation, int32_t group);
void initDeconvolutionLocalContext(Function *f);
void freeDeconvolutionLocalContext(Function *f);
void execDeconvolution(Function *f);

// MaxPooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  void *local_context;
} MaxPoolingConfig;
void initMaxPoolingConfig(MaxPoolingConfig *config, rt_list_t kernel,
                          rt_list_t stride, uint8_t ignore_border,
                          rt_list_t pad);
void initMaxPoolingLocalContext(Function *f);
void freeMaxPoolingLocalContext(Function *f);
void execMaxPooling(Function *f);

// AveragePooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  uint8_t including_pad;
  void *local_context;
} AveragePoolingConfig;
void initAveragePoolingConfig(AveragePoolingConfig *config, rt_list_t kernel,
                              rt_list_t stride, uint8_t ignore_border,
                              rt_list_t pad, uint8_t including_pad);
void initAveragePoolingLocalContext(Function *f);
void freeAveragePoolingLocalContext(Function *f);
void execAveragePooling(Function *f);

// SumPooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  rt_list_t stride; ///< Original type is [Shape]
  uint8_t ignore_border;
  rt_list_t pad; ///< Original type is [Shape]
  void *local_context;
} SumPoolingConfig;
void initSumPoolingConfig(SumPoolingConfig *config, rt_list_t kernel,
                          rt_list_t stride, uint8_t ignore_border,
                          rt_list_t pad);
void initSumPoolingLocalContext(Function *f);
void freeSumPoolingLocalContext(Function *f);
void execSumPooling(Function *f);

// Unpooling
typedef struct {
  rt_list_t kernel; ///< Original type is [Shape]
  void *local_context;
} UnpoolingConfig;
void initUnpoolingConfig(UnpoolingConfig *config, rt_list_t kernel);
void initUnpoolingLocalContext(Function *f);
void freeUnpoolingLocalContext(Function *f);
void execUnpooling(Function *f);

// Embed
void execEmbed(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Sigmoid
void execSigmoid(Function *f);

// Swish
void execSwish(Function *f);

// Tanh
void execTanh(Function *f);

// ReLU
typedef struct {
  uint8_t inplace;
  void *local_context;
} ReLUConfig;
void initReLUConfig(ReLUConfig *config, uint8_t inplace);
void initReLULocalContext(Function *f);
void freeReLULocalContext(Function *f);
void execReLU(Function *f);

// LeakyReLU
typedef struct {
  float alpha;
  void *local_context;
} LeakyReLUConfig;
void initLeakyReLUConfig(LeakyReLUConfig *config, float alpha);
void initLeakyReLULocalContext(Function *f);
void freeLeakyReLULocalContext(Function *f);
void execLeakyReLU(Function *f);

// Softmax
typedef struct {
  int32_t axis;
  void *local_context;
} SoftmaxConfig;
void initSoftmaxConfig(SoftmaxConfig *config, int32_t axis);
void initSoftmaxLocalContext(Function *f);
void freeSoftmaxLocalContext(Function *f);
void execSoftmax(Function *f);

// ELU
typedef struct {
  float alpha;
  void *local_context;
} ELUConfig;
void initELUConfig(ELUConfig *config, float alpha);
void initELULocalContext(Function *f);
void freeELULocalContext(Function *f);
void execELU(Function *f);

// SELU
typedef struct {
  float scale;
  float alpha;
  void *local_context;
} SELUConfig;
void initSELUConfig(SELUConfig *config, float scale, float alpha);
void initSELULocalContext(Function *f);
void freeSELULocalContext(Function *f);
void execSELU(Function *f);

// CReLU
typedef struct {
  int32_t axis;
  void *local_context;
} CReLUConfig;
void initCReLUConfig(CReLUConfig *config, int32_t axis);
void initCReLULocalContext(Function *f);
void freeCReLULocalContext(Function *f);
void execCReLU(Function *f);

// CELU
typedef struct {
  float alpha;
  int32_t axis;
  void *local_context;
} CELUConfig;
void initCELUConfig(CELUConfig *config, float alpha, int32_t axis);
void initCELULocalContext(Function *f);
void freeCELULocalContext(Function *f);
void execCELU(Function *f);

// PReLU
typedef struct {
  int32_t base_axis;
  void *local_context;
} PReLUConfig;
void initPReLUConfig(PReLUConfig *config, int32_t base_axis);
void initPReLULocalContext(Function *f);
void freePReLULocalContext(Function *f);
void execPReLU(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  float decay_rate;
  float eps;
  uint8_t batch_stat;
  void *local_context;
} BatchNormalizationConfig;
void initBatchNormalizationConfig(BatchNormalizationConfig *config,
                                  rt_list_t axes, float decay_rate, float eps,
                                  uint8_t batch_stat);
void initBatchNormalizationLocalContext(Function *f);
void freeBatchNormalizationLocalContext(Function *f);
void execBatchNormalization(Function *f);

// MeanSubtraction
typedef struct {
  int32_t base_axis;
  uint8_t update_running_mean;
  void *local_context;
} MeanSubtractionConfig;
void initMeanSubtractionConfig(MeanSubtractionConfig *config, int32_t base_axis,
                               uint8_t update_running_mean);
void initMeanSubtractionLocalContext(Function *f);
void freeMeanSubtractionLocalContext(Function *f);
void execMeanSubtraction(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} SumConfig;
void initSumConfig(SumConfig *config, rt_list_t axes, uint8_t keep_dims);
void initSumLocalContext(Function *f);
void freeSumLocalContext(Function *f);
void execSum(Function *f);

// Mean
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} MeanConfig;
void initMeanConfig(MeanConfig *config, rt_list_t axes, uint8_t keep_dims);
void initMeanLocalContext(Function *f);
void freeMeanLocalContext(Function *f);
void execMean(Function *f);

// Max
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} MaxConfig;
void initMaxConfig(MaxConfig *config, rt_list_t axes, uint8_t keep_dims);
void initMaxLocalContext(Function *f);
void freeMaxLocalContext(Function *f);
void execMax(Function *f);

// Min
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} MinConfig;
void initMinConfig(MinConfig *config, rt_list_t axes, uint8_t keep_dims);
void initMinLocalContext(Function *f);
void freeMinLocalContext(Function *f);
void execMin(Function *f);

// Prod
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  uint8_t keep_dims;
  void *local_context;
} ProdConfig;
void initProdConfig(ProdConfig *config, rt_list_t axes, uint8_t keep_dims);
void initProdLocalContext(Function *f);
void freeProdLocalContext(Function *f);
void execProd(Function *f);

// ReduceSum
void execReduceSum(Function *f);

// ReduceMean
void execReduceMean(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
typedef struct {
  uint8_t inplace;
  void *local_context;
} Add2Config;
void initAdd2Config(Add2Config *config, uint8_t inplace);
void initAdd2LocalContext(Function *f);
void freeAdd2LocalContext(Function *f);
void execAdd2(Function *f);

// BcAdd2
void execBcAdd2(Function *f);

// Sub2
void execSub2(Function *f);

// Mul2
void execMul2(Function *f);

// Div2
void execDiv2(Function *f);

// Pow2
void execPow2(Function *f);

// AddScalar
typedef struct {
  float val;
  void *local_context;
} AddScalarConfig;
void initAddScalarConfig(AddScalarConfig *config, float val);
void initAddScalarLocalContext(Function *f);
void freeAddScalarLocalContext(Function *f);
void execAddScalar(Function *f);

// MulScalar
typedef struct {
  float val;
  void *local_context;
} MulScalarConfig;
void initMulScalarConfig(MulScalarConfig *config, float val);
void initMulScalarLocalContext(Function *f);
void freeMulScalarLocalContext(Function *f);
void execMulScalar(Function *f);

// PowScalar
typedef struct {
  float val;
  void *local_context;
} PowScalarConfig;
void initPowScalarConfig(PowScalarConfig *config, float val);
void initPowScalarLocalContext(Function *f);
void freePowScalarLocalContext(Function *f);
void execPowScalar(Function *f);

// RSubScalar
typedef struct {
  float val;
  void *local_context;
} RSubScalarConfig;
void initRSubScalarConfig(RSubScalarConfig *config, float val);
void initRSubScalarLocalContext(Function *f);
void freeRSubScalarLocalContext(Function *f);
void execRSubScalar(Function *f);

// RDivScalar
typedef struct {
  float val;
  void *local_context;
} RDivScalarConfig;
void initRDivScalarConfig(RDivScalarConfig *config, float val);
void initRDivScalarLocalContext(Function *f);
void freeRDivScalarLocalContext(Function *f);
void execRDivScalar(Function *f);

// RPowScalar
typedef struct {
  float val;
  void *local_context;
} RPowScalarConfig;
void initRPowScalarConfig(RPowScalarConfig *config, float val);
void initRPowScalarLocalContext(Function *f);
void freeRPowScalarLocalContext(Function *f);
void execRPowScalar(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
typedef struct {
  float alpha;
  void *local_context;
} SignConfig;
void initSignConfig(SignConfig *config, float alpha);
void initSignLocalContext(Function *f);
void freeSignLocalContext(Function *f);
void execSign(Function *f);

// Minimum2
void execMinimum2(Function *f);

// Maximum2
void execMaximum2(Function *f);

// MinimumScalar
typedef struct {
  float val;
  void *local_context;
} MinimumScalarConfig;
void initMinimumScalarConfig(MinimumScalarConfig *config, float val);
void initMinimumScalarLocalContext(Function *f);
void freeMinimumScalarLocalContext(Function *f);
void execMinimumScalar(Function *f);

// MaximumScalar
typedef struct {
  float val;
  void *local_context;
} MaximumScalarConfig;
void initMaximumScalarConfig(MaximumScalarConfig *config, float val);
void initMaximumScalarLocalContext(Function *f);
void freeMaximumScalarLocalContext(Function *f);
void execMaximumScalar(Function *f);

// LogicalAnd
void execLogicalAnd(Function *f);

// LogicalOr
void execLogicalOr(Function *f);

// LogicalXor
void execLogicalXor(Function *f);

// Equal
void execEqual(Function *f);

// NotEqual
void execNotEqual(Function *f);

// GreaterEqual
void execGreaterEqual(Function *f);

// Greater
void execGreater(Function *f);

// LessEqual
void execLessEqual(Function *f);

// Less
void execLess(Function *f);

// LogicalAndScalar
typedef struct {
  uint8_t val;
  void *local_context;
} LogicalAndScalarConfig;
void initLogicalAndScalarConfig(LogicalAndScalarConfig *config, uint8_t val);
void initLogicalAndScalarLocalContext(Function *f);
void freeLogicalAndScalarLocalContext(Function *f);
void execLogicalAndScalar(Function *f);

// LogicalOrScalar
typedef struct {
  uint8_t val;
  void *local_context;
} LogicalOrScalarConfig;
void initLogicalOrScalarConfig(LogicalOrScalarConfig *config, uint8_t val);
void initLogicalOrScalarLocalContext(Function *f);
void freeLogicalOrScalarLocalContext(Function *f);
void execLogicalOrScalar(Function *f);

// LogicalXorScalar
typedef struct {
  uint8_t val;
  void *local_context;
} LogicalXorScalarConfig;
void initLogicalXorScalarConfig(LogicalXorScalarConfig *config, uint8_t val);
void initLogicalXorScalarLocalContext(Function *f);
void freeLogicalXorScalarLocalContext(Function *f);
void execLogicalXorScalar(Function *f);

// EqualScalar
typedef struct {
  float val;
  void *local_context;
} EqualScalarConfig;
void initEqualScalarConfig(EqualScalarConfig *config, float val);
void initEqualScalarLocalContext(Function *f);
void freeEqualScalarLocalContext(Function *f);
void execEqualScalar(Function *f);

// NotEqualScalar
typedef struct {
  float val;
  void *local_context;
} NotEqualScalarConfig;
void initNotEqualScalarConfig(NotEqualScalarConfig *config, float val);
void initNotEqualScalarLocalContext(Function *f);
void freeNotEqualScalarLocalContext(Function *f);
void execNotEqualScalar(Function *f);

// GreaterEqualScalar
typedef struct {
  float val;
  void *local_context;
} GreaterEqualScalarConfig;
void initGreaterEqualScalarConfig(GreaterEqualScalarConfig *config, float val);
void initGreaterEqualScalarLocalContext(Function *f);
void freeGreaterEqualScalarLocalContext(Function *f);
void execGreaterEqualScalar(Function *f);

// GreaterScalar
typedef struct {
  float val;
  void *local_context;
} GreaterScalarConfig;
void initGreaterScalarConfig(GreaterScalarConfig *config, float val);
void initGreaterScalarLocalContext(Function *f);
void freeGreaterScalarLocalContext(Function *f);
void execGreaterScalar(Function *f);

// LessEqualScalar
typedef struct {
  float val;
  void *local_context;
} LessEqualScalarConfig;
void initLessEqualScalarConfig(LessEqualScalarConfig *config, float val);
void initLessEqualScalarLocalContext(Function *f);
void freeLessEqualScalarLocalContext(Function *f);
void execLessEqualScalar(Function *f);

// LessScalar
typedef struct {
  float val;
  void *local_context;
} LessScalarConfig;
void initLessScalarConfig(LessScalarConfig *config, float val);
void initLessScalarLocalContext(Function *f);
void freeLessScalarLocalContext(Function *f);
void execLessScalar(Function *f);

// LogicalNot
void execLogicalNot(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
typedef struct {
  float val;
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} ConstantConfig;
void initConstantConfig(ConstantConfig *config, float val, rt_list_t shape);
void initConstantLocalContext(Function *f);
void freeConstantLocalContext(Function *f);
void execConstant(Function *f);

// Abs
void execAbs(Function *f);

// Exp
void execExp(Function *f);

// Log
void execLog(Function *f);

// Identity
void execIdentity(Function *f);

// BatchMatmul
typedef struct {
  uint8_t transpose_a;
  uint8_t transpose_b;
  void *local_context;
} BatchMatmulConfig;
void initBatchMatmulConfig(BatchMatmulConfig *config, uint8_t transpose_a,
                           uint8_t transpose_b);
void initBatchMatmulLocalContext(Function *f);
void freeBatchMatmulLocalContext(Function *f);
void execBatchMatmul(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
typedef struct {
  int32_t axis;
  void *local_context;
} ConcatenateConfig;
void initConcatenateConfig(ConcatenateConfig *config, int32_t axis);
void initConcatenateLocalContext(Function *f);
void freeConcatenateLocalContext(Function *f);
void execConcatenate(Function *f);

// Split
typedef struct {
  int32_t axis;
  void *local_context;
} SplitConfig;
void initSplitConfig(SplitConfig *config, int32_t axis);
void initSplitLocalContext(Function *f);
void freeSplitLocalContext(Function *f);
void execSplit(Function *f);

// Stack
typedef struct {
  int32_t axis;
  void *local_context;
} StackConfig;
void initStackConfig(StackConfig *config, int32_t axis);
void initStackLocalContext(Function *f);
void freeStackLocalContext(Function *f);
void execStack(Function *f);

// Slice
typedef struct {
  rt_list_t start; ///< Original type is [repeated int64]
  rt_list_t stop;  ///< Original type is [repeated int64]
  rt_list_t step;  ///< Original type is [repeated int64]
  void *local_context;
} SliceConfig;
void initSliceConfig(SliceConfig *config, rt_list_t start, rt_list_t stop,
                     rt_list_t step);
void initSliceLocalContext(Function *f);
void freeSliceLocalContext(Function *f);
void execSlice(Function *f);

// Transpose
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *local_context;
} TransposeConfig;
void initTransposeConfig(TransposeConfig *config, rt_list_t axes);
void initTransposeLocalContext(Function *f);
void freeTransposeLocalContext(Function *f);
void execTranspose(Function *f);

// Broadcast
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} BroadcastConfig;
void initBroadcastConfig(BroadcastConfig *config, rt_list_t shape);
void initBroadcastLocalContext(Function *f);
void freeBroadcastLocalContext(Function *f);
void execBroadcast(Function *f);

// OneHot
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} OneHotConfig;
void initOneHotConfig(OneHotConfig *config, rt_list_t shape);
void initOneHotLocalContext(Function *f);
void freeOneHotLocalContext(Function *f);
void execOneHot(Function *f);

// Flip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  void *local_context;
} FlipConfig;
void initFlipConfig(FlipConfig *config, rt_list_t axes);
void initFlipLocalContext(Function *f);
void freeFlipLocalContext(Function *f);
void execFlip(Function *f);

// Shift
typedef struct {
  rt_list_t shifts;     ///< Original type is [repeated int64]
  uint32_t border_mode; ///< Original type is [string]
  void *local_context;
} ShiftConfig;
void initShiftConfig(ShiftConfig *config, rt_list_t shifts,
                     uint32_t border_mode);
void initShiftLocalContext(Function *f);
void freeShiftLocalContext(Function *f);
void execShift(Function *f);

// Reshape
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  void *local_context;
} ReshapeConfig;
void initReshapeConfig(ReshapeConfig *config, rt_list_t shape);
void initReshapeLocalContext(Function *f);
void freeReshapeLocalContext(Function *f);
void execReshape(Function *f);

// MatrixDiag
void execMatrixDiag(Function *f);

// MatrixDiagPart
void execMatrixDiagPart(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
typedef struct {
  float p;
  int32_t seed;
  void *local_context;
} DropoutConfig;
void initDropoutConfig(DropoutConfig *config, float p, int32_t seed);
void initDropoutLocalContext(Function *f);
void freeDropoutLocalContext(Function *f);
void execDropout(Function *f);

// Rand
typedef struct {
  float low;
  float high;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *local_context;
} RandConfig;
void initRandConfig(RandConfig *config, float low, float high, rt_list_t shape,
                    int32_t seed);
void initRandLocalContext(Function *f);
void freeRandLocalContext(Function *f);
void execRand(Function *f);

// Randint
typedef struct {
  int32_t low;
  int32_t high;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *local_context;
} RandintConfig;
void initRandintConfig(RandintConfig *config, int32_t low, int32_t high,
                       rt_list_t shape, int32_t seed);
void initRandintLocalContext(Function *f);
void freeRandintLocalContext(Function *f);
void execRandint(Function *f);

// Randn
typedef struct {
  float mu;
  float sigma;
  rt_list_t shape; ///< Original type is [Shape]
  int32_t seed;
  void *local_context;
} RandnConfig;
void initRandnConfig(RandnConfig *config, float mu, float sigma,
                     rt_list_t shape, int32_t seed);
void initRandnLocalContext(Function *f);
void freeRandnLocalContext(Function *f);
void execRandn(Function *f);

// RandomCrop
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  int32_t base_axis;
  int32_t seed;
  void *local_context;
} RandomCropConfig;
void initRandomCropConfig(RandomCropConfig *config, rt_list_t shape,
                          int32_t base_axis, int32_t seed);
void initRandomCropLocalContext(Function *f);
void freeRandomCropLocalContext(Function *f);
void execRandomCrop(Function *f);

// RandomFlip
typedef struct {
  rt_list_t axes; ///< Original type is [repeated int64]
  int32_t base_axis;
  int32_t seed;
  void *local_context;
} RandomFlipConfig;
void initRandomFlipConfig(RandomFlipConfig *config, rt_list_t axes,
                          int32_t base_axis, int32_t seed);
void initRandomFlipLocalContext(Function *f);
void freeRandomFlipLocalContext(Function *f);
void execRandomFlip(Function *f);

// RandomShift
typedef struct {
  rt_list_t shifts;     ///< Original type is [repeated int64]
  uint32_t border_mode; ///< Original type is [string]
  int32_t base_axis;
  int32_t seed;
  void *local_context;
} RandomShiftConfig;
void initRandomShiftConfig(RandomShiftConfig *config, rt_list_t shifts,
                           uint32_t border_mode, int32_t base_axis,
                           int32_t seed);
void initRandomShiftLocalContext(Function *f);
void freeRandomShiftLocalContext(Function *f);
void execRandomShift(Function *f);

// ImageAugmentation
typedef struct {
  rt_list_t shape; ///< Original type is [Shape]
  rt_list_t pad;   ///< Original type is [Shape]
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
  void *local_context;
} ImageAugmentationConfig;
void initImageAugmentationConfig(
    ImageAugmentationConfig *config, rt_list_t shape, rt_list_t pad,
    float min_scale, float max_scale, float angle, float aspect_ratio,
    float distortion, uint8_t flip_lr, uint8_t flip_ud, float brightness,
    uint8_t brightness_each, float contrast, float contrast_center,
    uint8_t contrast_each, float noise, int32_t seed);
void initImageAugmentationLocalContext(Function *f);
void freeImageAugmentationLocalContext(Function *f);
void execImageAugmentation(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy
void execSigmoidCrossEntropy(Function *f);

// BinaryCrossEntropy
void execBinaryCrossEntropy(Function *f);

// SoftmaxCrossEntropy
typedef struct {
  int32_t axis;
  void *local_context;
} SoftmaxCrossEntropyConfig;
void initSoftmaxCrossEntropyConfig(SoftmaxCrossEntropyConfig *config,
                                   int32_t axis);
void initSoftmaxCrossEntropyLocalContext(Function *f);
void freeSoftmaxCrossEntropyLocalContext(Function *f);
void execSoftmaxCrossEntropy(Function *f);

// CategoricalCrossEntropy
typedef struct {
  int32_t axis;
  void *local_context;
} CategoricalCrossEntropyConfig;
void initCategoricalCrossEntropyConfig(CategoricalCrossEntropyConfig *config,
                                       int32_t axis);
void initCategoricalCrossEntropyLocalContext(Function *f);
void freeCategoricalCrossEntropyLocalContext(Function *f);
void execCategoricalCrossEntropy(Function *f);

// SquaredError
void execSquaredError(Function *f);

// AbsoluteError
void execAbsoluteError(Function *f);

// HuberLoss
typedef struct {
  float delta;
  void *local_context;
} HuberLossConfig;
void initHuberLossConfig(HuberLossConfig *config, float delta);
void initHuberLossLocalContext(Function *f);
void freeHuberLossLocalContext(Function *f);
void execHuberLoss(Function *f);

// EpsilonInsensitiveLoss
typedef struct {
  float epsilon;
  void *local_context;
} EpsilonInsensitiveLossConfig;
void initEpsilonInsensitiveLossConfig(EpsilonInsensitiveLossConfig *config,
                                      float epsilon);
void initEpsilonInsensitiveLossLocalContext(Function *f);
void freeEpsilonInsensitiveLossLocalContext(Function *f);
void execEpsilonInsensitiveLoss(Function *f);

// KLMultinomial
typedef struct {
  int32_t base_axis;
  void *local_context;
} KLMultinomialConfig;
void initKLMultinomialConfig(KLMultinomialConfig *config, int32_t base_axis);
void initKLMultinomialLocalContext(Function *f);
void freeKLMultinomialLocalContext(Function *f);
void execKLMultinomial(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid
void execBinarySigmoid(Function *f);

// BinaryTanh
void execBinaryTanh(Function *f);

// BinaryConnectAffine
typedef struct {
  int32_t base_axis;
  void *local_context;
} BinaryConnectAffineConfig;
void initBinaryConnectAffineConfig(BinaryConnectAffineConfig *config,
                                   int32_t base_axis);
void initBinaryConnectAffineLocalContext(Function *f);
void freeBinaryConnectAffineLocalContext(Function *f);
void execBinaryConnectAffine(Function *f);

// BinaryConnectConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} BinaryConnectConvolutionConfig;
void initBinaryConnectConvolutionConfig(BinaryConnectConvolutionConfig *config,
                                        int32_t base_axis, rt_list_t pad,
                                        rt_list_t stride, rt_list_t dilation,
                                        int32_t group);
void initBinaryConnectConvolutionLocalContext(Function *f);
void freeBinaryConnectConvolutionLocalContext(Function *f);
void execBinaryConnectConvolution(Function *f);

// BinaryWeightAffine
typedef struct {
  int32_t base_axis;
  void *local_context;
} BinaryWeightAffineConfig;
void initBinaryWeightAffineConfig(BinaryWeightAffineConfig *config,
                                  int32_t base_axis);
void initBinaryWeightAffineLocalContext(Function *f);
void freeBinaryWeightAffineLocalContext(Function *f);
void execBinaryWeightAffine(Function *f);

// BinaryWeightConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  void *local_context;
} BinaryWeightConvolutionConfig;
void initBinaryWeightConvolutionConfig(BinaryWeightConvolutionConfig *config,
                                       int32_t base_axis, rt_list_t pad,
                                       rt_list_t stride, rt_list_t dilation,
                                       int32_t group);
void initBinaryWeightConvolutionLocalContext(Function *f);
void freeBinaryWeightConvolutionLocalContext(Function *f);
void execBinaryWeightConvolution(Function *f);

// INQAffine
typedef struct {
  int32_t base_axis;
  int32_t num_bits;
  rt_list_t inq_iterations;     ///< Original type is [repeated int64]
  uint32_t selection_algorithm; ///< Original type is [string]
  int32_t seed;
  void *local_context;
} INQAffineConfig;
void initINQAffineConfig(INQAffineConfig *config, int32_t base_axis,
                         int32_t num_bits, rt_list_t inq_iterations,
                         uint32_t selection_algorithm, int32_t seed);
void initINQAffineLocalContext(Function *f);
void freeINQAffineLocalContext(Function *f);
void execINQAffine(Function *f);

// INQConvolution
typedef struct {
  int32_t base_axis;
  rt_list_t pad;      ///< Original type is [Shape]
  rt_list_t stride;   ///< Original type is [Shape]
  rt_list_t dilation; ///< Original type is [Shape]
  int32_t group;
  int32_t num_bits;
  rt_list_t inq_iterations;     ///< Original type is [repeated int64]
  uint32_t selection_algorithm; ///< Original type is [string]
  int32_t seed;
  void *local_context;
} INQConvolutionConfig;
void initINQConvolutionConfig(INQConvolutionConfig *config, int32_t base_axis,
                              rt_list_t pad, rt_list_t stride,
                              rt_list_t dilation, int32_t group,
                              int32_t num_bits, rt_list_t inq_iterations,
                              uint32_t selection_algorithm, int32_t seed);
void initINQConvolutionLocalContext(Function *f);
void freeINQConvolutionLocalContext(Function *f);
void execINQConvolution(Function *f);

// FixedPointQuantize
typedef struct {
  uint8_t sign;
  int32_t n;
  float delta;
  uint8_t ste_fine_grained;
  void *local_context;
} FixedPointQuantizeConfig;
void initFixedPointQuantizeConfig(FixedPointQuantizeConfig *config,
                                  uint8_t sign, int32_t n, float delta,
                                  uint8_t ste_fine_grained);
void initFixedPointQuantizeLocalContext(Function *f);
void freeFixedPointQuantizeLocalContext(Function *f);
void execFixedPointQuantize(Function *f);

// Pow2Quantize
typedef struct {
  uint8_t sign;
  uint8_t with_zero;
  int32_t n;
  int32_t m;
  uint8_t ste_fine_grained;
  void *local_context;
} Pow2QuantizeConfig;
void initPow2QuantizeConfig(Pow2QuantizeConfig *config, uint8_t sign,
                            uint8_t with_zero, int32_t n, int32_t m,
                            uint8_t ste_fine_grained);
void initPow2QuantizeLocalContext(Function *f);
void freePow2QuantizeLocalContext(Function *f);
void execPow2Quantize(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
typedef struct {
  int32_t axis;
  int32_t n;
  void *local_context;
} TopNErrorConfig;
void initTopNErrorConfig(TopNErrorConfig *config, int32_t axis, int32_t n);
void initTopNErrorLocalContext(Function *f);
void freeTopNErrorLocalContext(Function *f);
void execTopNError(Function *f);

// BinaryError
void execBinaryError(Function *f);

// ConfusionMatrix
typedef struct {
  int32_t axis;
  void *local_context;
} ConfusionMatrixConfig;
void initConfusionMatrixConfig(ConfusionMatrixConfig *config, int32_t axis);
void initConfusionMatrixLocalContext(Function *f);
void freeConfusionMatrixLocalContext(Function *f);
void execConfusionMatrix(Function *f);

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
typedef struct {
  int32_t base_axis;
  float eps;
  void *local_context;
} VATNoiseConfig;
void initVATNoiseConfig(VATNoiseConfig *config, int32_t base_axis, float eps);
void initVATNoiseLocalContext(Function *f);
void freeVATNoiseLocalContext(Function *f);
void execVATNoise(Function *f);

// Unlink
void execUnlink(Function *f);

// Sink
typedef struct {
  uint8_t one_input_grad;
  void *local_context;
} SinkConfig;
void initSinkConfig(SinkConfig *config, uint8_t one_input_grad);
void initSinkLocalContext(Function *f);
void freeSinkLocalContext(Function *f);
void execSink(Function *f);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // H_FUNCTIONS_H__
