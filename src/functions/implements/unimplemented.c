// -*- coding:utf-8 -*-

#include <nnablart/functions.h>

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

// Convolution
void initConvolutionConfig(ConvolutionConfig *config, int32_t base_axis,
                           rt_list_t pad, rt_list_t stride, rt_list_t dilation,
                           int32_t group) {}
void initConvolutionLocalContext(rt_function_t *f) {}
void freeConvolutionLocalContext(rt_function_t *f) {}
void execConvolution(rt_function_t *f) {}

// DepthwiseConvolution
void initDepthwiseConvolutionConfig(DepthwiseConvolutionConfig *config,
                                    int32_t base_axis, rt_list_t pad,
                                    rt_list_t stride, rt_list_t dilation,
                                    int32_t multiplier) {}
void initDepthwiseConvolutionLocalContext(rt_function_t *f) {}
void freeDepthwiseConvolutionLocalContext(rt_function_t *f) {}
void execDepthwiseConvolution(rt_function_t *f) {}

// Deconvolution
void initDeconvolutionConfig(DeconvolutionConfig *config, int32_t base_axis,
                             rt_list_t pad, rt_list_t stride,
                             rt_list_t dilation, int32_t group) {}
void initDeconvolutionLocalContext(rt_function_t *f) {}
void freeDeconvolutionLocalContext(rt_function_t *f) {}
void execDeconvolution(rt_function_t *f) {}

// MaxPooling
void initMaxPoolingConfig(MaxPoolingConfig *config, rt_list_t kernel,
                          rt_list_t stride, uint8_t ignore_border,
                          rt_list_t pad) {}
void initMaxPoolingLocalContext(rt_function_t *f) {}
void freeMaxPoolingLocalContext(rt_function_t *f) {}
void execMaxPooling(rt_function_t *f) {}

// AveragePooling
void initAveragePoolingConfig(AveragePoolingConfig *config, rt_list_t kernel,
                              rt_list_t stride, uint8_t ignore_border,
                              rt_list_t pad, uint8_t including_pad) {}
void initAveragePoolingLocalContext(rt_function_t *f) {}
void freeAveragePoolingLocalContext(rt_function_t *f) {}
void execAveragePooling(rt_function_t *f) {}

// SumPooling
void initSumPoolingConfig(SumPoolingConfig *config, rt_list_t kernel,
                          rt_list_t stride, uint8_t ignore_border,
                          rt_list_t pad) {}
void initSumPoolingLocalContext(rt_function_t *f) {}
void freeSumPoolingLocalContext(rt_function_t *f) {}
void execSumPooling(rt_function_t *f) {}

// Unpooling
void initUnpoolingConfig(UnpoolingConfig *config, rt_list_t kernel) {}
void initUnpoolingLocalContext(rt_function_t *f) {}
void freeUnpoolingLocalContext(rt_function_t *f) {}
void execUnpooling(rt_function_t *f) {}

// Embed
void execEmbed(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation rt_function_ts
////////////////////////////////////////////////////////////////////////////////

// Sigmoid
void execSigmoid(rt_function_t *f) {}

// Swish
void execSwish(rt_function_t *f) {}

// Tanh
void execTanh(rt_function_t *f) {}

// ReLU
void initReLUConfig(ReLUConfig *config, uint8_t inplace) {}
void initReLULocalContext(rt_function_t *f) {}
void freeReLULocalContext(rt_function_t *f) {}
void execReLU(rt_function_t *f) {}

// LeakyReLU
void initLeakyReLUConfig(LeakyReLUConfig *config, float alpha) {}
void initLeakyReLULocalContext(rt_function_t *f) {}
void freeLeakyReLULocalContext(rt_function_t *f) {}
void execLeakyReLU(rt_function_t *f) {}

// Softmax
void initSoftmaxConfig(SoftmaxConfig *config, int32_t axis) {}
void initSoftmaxLocalContext(rt_function_t *f) {}
void freeSoftmaxLocalContext(rt_function_t *f) {}
void execSoftmax(rt_function_t *f) {}

// ELU
void initELUConfig(ELUConfig *config, float alpha) {}
void initELULocalContext(rt_function_t *f) {}
void freeELULocalContext(rt_function_t *f) {}
void execELU(rt_function_t *f) {}

// SELU
void initSELUConfig(SELUConfig *config, float scale, float alpha) {}
void initSELULocalContext(rt_function_t *f) {}
void freeSELULocalContext(rt_function_t *f) {}
void execSELU(rt_function_t *f) {}

// CReLU
void initCReLUConfig(CReLUConfig *config, int32_t axis) {}
void initCReLULocalContext(rt_function_t *f) {}
void freeCReLULocalContext(rt_function_t *f) {}
void execCReLU(rt_function_t *f) {}

// CELU
void initCELUConfig(CELUConfig *config, float alpha, int32_t axis) {}
void initCELULocalContext(rt_function_t *f) {}
void freeCELULocalContext(rt_function_t *f) {}
void execCELU(rt_function_t *f) {}

// PReLU
void initPReLUConfig(PReLUConfig *config, int32_t base_axis) {}
void initPReLULocalContext(rt_function_t *f) {}
void freePReLULocalContext(rt_function_t *f) {}
void execPReLU(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
void initBatchNormalizationConfig(BatchNormalizationConfig *config,
                                  rt_list_t axes, float decay_rate, float eps,
                                  uint8_t batch_stat) {}
void initBatchNormalizationLocalContext(rt_function_t *f) {}
void freeBatchNormalizationLocalContext(rt_function_t *f) {}
void execBatchNormalization(rt_function_t *f) {}

// MeanSubtraction
void initMeanSubtractionConfig(MeanSubtractionConfig *config, int32_t base_axis,
                               uint8_t update_running_mean) {}
void initMeanSubtractionLocalContext(rt_function_t *f) {}
void freeMeanSubtractionLocalContext(rt_function_t *f) {}
void execMeanSubtraction(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
void initSumConfig(SumConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initSumLocalContext(rt_function_t *f) {}
void freeSumLocalContext(rt_function_t *f) {}
void execSum(rt_function_t *f) {}

// Mean
void initMeanConfig(MeanConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initMeanLocalContext(rt_function_t *f) {}
void freeMeanLocalContext(rt_function_t *f) {}
void execMean(rt_function_t *f) {}

// Max
void initMaxConfig(MaxConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initMaxLocalContext(rt_function_t *f) {}
void freeMaxLocalContext(rt_function_t *f) {}
void execMax(rt_function_t *f) {}

// Min
void initMinConfig(MinConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initMinLocalContext(rt_function_t *f) {}
void freeMinLocalContext(rt_function_t *f) {}
void execMin(rt_function_t *f) {}

// Prod
void initProdConfig(ProdConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initProdLocalContext(rt_function_t *f) {}
void freeProdLocalContext(rt_function_t *f) {}
void execProd(rt_function_t *f) {}

// ReduceSum
void execReduceSum(rt_function_t *f) {}

// ReduceMean
void execReduceMean(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
void initAdd2Config(Add2Config *config, uint8_t inplace) {}
void initAdd2LocalContext(rt_function_t *f) {}
void freeAdd2LocalContext(rt_function_t *f) {}
void execAdd2(rt_function_t *f) {}

// BcAdd2
void execBcAdd2(rt_function_t *f) {}

// Sub2
void execSub2(rt_function_t *f) {}

// Mul2
void execMul2(rt_function_t *f) {}

// Div2
void execDiv2(rt_function_t *f) {}

// Pow2
void execPow2(rt_function_t *f) {}

// AddScalar
void initAddScalarConfig(AddScalarConfig *config, float val) {}
void initAddScalarLocalContext(rt_function_t *f) {}
void freeAddScalarLocalContext(rt_function_t *f) {}
void execAddScalar(rt_function_t *f) {}

// MulScalar
void initMulScalarConfig(MulScalarConfig *config, float val) {}
void initMulScalarLocalContext(rt_function_t *f) {}
void freeMulScalarLocalContext(rt_function_t *f) {}
void execMulScalar(rt_function_t *f) {}

// PowScalar
void initPowScalarConfig(PowScalarConfig *config, float val) {}
void initPowScalarLocalContext(rt_function_t *f) {}
void freePowScalarLocalContext(rt_function_t *f) {}
void execPowScalar(rt_function_t *f) {}

// RSubScalar
void initRSubScalarConfig(RSubScalarConfig *config, float val) {}
void initRSubScalarLocalContext(rt_function_t *f) {}
void freeRSubScalarLocalContext(rt_function_t *f) {}
void execRSubScalar(rt_function_t *f) {}

// RDivScalar
void initRDivScalarConfig(RDivScalarConfig *config, float val) {}
void initRDivScalarLocalContext(rt_function_t *f) {}
void freeRDivScalarLocalContext(rt_function_t *f) {}
void execRDivScalar(rt_function_t *f) {}

// RPowScalar
void initRPowScalarConfig(RPowScalarConfig *config, float val) {}
void initRPowScalarLocalContext(rt_function_t *f) {}
void freeRPowScalarLocalContext(rt_function_t *f) {}
void execRPowScalar(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
void initSignConfig(SignConfig *config, float alpha) {}
void initSignLocalContext(rt_function_t *f) {}
void freeSignLocalContext(rt_function_t *f) {}
void execSign(rt_function_t *f) {}

// Minimum2
void execMinimum2(rt_function_t *f) {}

// Maximum2
void execMaximum2(rt_function_t *f) {}

// MinimumScalar
void initMinimumScalarConfig(MinimumScalarConfig *config, float val) {}
void initMinimumScalarLocalContext(rt_function_t *f) {}
void freeMinimumScalarLocalContext(rt_function_t *f) {}
void execMinimumScalar(rt_function_t *f) {}

// MaximumScalar
void initMaximumScalarConfig(MaximumScalarConfig *config, float val) {}
void initMaximumScalarLocalContext(rt_function_t *f) {}
void freeMaximumScalarLocalContext(rt_function_t *f) {}
void execMaximumScalar(rt_function_t *f) {}

// LogicalAnd
void execLogicalAnd(rt_function_t *f) {}

// LogicalOr
void execLogicalOr(rt_function_t *f) {}

// LogicalXor
void execLogicalXor(rt_function_t *f) {}

// Equal
void execEqual(rt_function_t *f) {}

// NotEqual
void execNotEqual(rt_function_t *f) {}

// GreaterEqual
void execGreaterEqual(rt_function_t *f) {}

// Greater
void execGreater(rt_function_t *f) {}

// LessEqual
void execLessEqual(rt_function_t *f) {}

// Less
void execLess(rt_function_t *f) {}

// LogicalAndScalar
void initLogicalAndScalarConfig(LogicalAndScalarConfig *config, uint8_t val) {}
void initLogicalAndScalarLocalContext(rt_function_t *f) {}
void freeLogicalAndScalarLocalContext(rt_function_t *f) {}
void execLogicalAndScalar(rt_function_t *f) {}

// LogicalOrScalar
void initLogicalOrScalarConfig(LogicalOrScalarConfig *config, uint8_t val) {}
void initLogicalOrScalarLocalContext(rt_function_t *f) {}
void freeLogicalOrScalarLocalContext(rt_function_t *f) {}
void execLogicalOrScalar(rt_function_t *f) {}

// LogicalXorScalar
void initLogicalXorScalarConfig(LogicalXorScalarConfig *config, uint8_t val) {}
void initLogicalXorScalarLocalContext(rt_function_t *f) {}
void freeLogicalXorScalarLocalContext(rt_function_t *f) {}
void execLogicalXorScalar(rt_function_t *f) {}

// EqualScalar
void initEqualScalarConfig(EqualScalarConfig *config, float val) {}
void initEqualScalarLocalContext(rt_function_t *f) {}
void freeEqualScalarLocalContext(rt_function_t *f) {}
void execEqualScalar(rt_function_t *f) {}

// NotEqualScalar
void initNotEqualScalarConfig(NotEqualScalarConfig *config, float val) {}
void initNotEqualScalarLocalContext(rt_function_t *f) {}
void freeNotEqualScalarLocalContext(rt_function_t *f) {}
void execNotEqualScalar(rt_function_t *f) {}

// GreaterEqualScalar
void initGreaterEqualScalarConfig(GreaterEqualScalarConfig *config, float val) {
}
void initGreaterEqualScalarLocalContext(rt_function_t *f) {}
void freeGreaterEqualScalarLocalContext(rt_function_t *f) {}
void execGreaterEqualScalar(rt_function_t *f) {}

// GreaterScalar
void initGreaterScalarConfig(GreaterScalarConfig *config, float val) {}
void initGreaterScalarLocalContext(rt_function_t *f) {}
void freeGreaterScalarLocalContext(rt_function_t *f) {}
void execGreaterScalar(rt_function_t *f) {}

// LessEqualScalar
void initLessEqualScalarConfig(LessEqualScalarConfig *config, float val) {}
void initLessEqualScalarLocalContext(rt_function_t *f) {}
void freeLessEqualScalarLocalContext(rt_function_t *f) {}
void execLessEqualScalar(rt_function_t *f) {}

// LessScalar
void initLessScalarConfig(LessScalarConfig *config, float val) {}
void initLessScalarLocalContext(rt_function_t *f) {}
void freeLessScalarLocalContext(rt_function_t *f) {}
void execLessScalar(rt_function_t *f) {}

// LogicalNot
void execLogicalNot(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
void initConstantConfig(ConstantConfig *config, float val, rt_list_t shape) {}
void initConstantLocalContext(rt_function_t *f) {}
void freeConstantLocalContext(rt_function_t *f) {}
void execConstant(rt_function_t *f) {}

// Abs
void execAbs(rt_function_t *f) {}

// Exp
void execExp(rt_function_t *f) {}

// Log
void execLog(rt_function_t *f) {}

// Identity
void execIdentity(rt_function_t *f) {}

// BatchMatmul
void initBatchMatmulConfig(BatchMatmulConfig *config, uint8_t transpose_a,
                           uint8_t transpose_b) {}
void initBatchMatmulLocalContext(rt_function_t *f) {}
void freeBatchMatmulLocalContext(rt_function_t *f) {}
void execBatchMatmul(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
void initConcatenateConfig(ConcatenateConfig *config, int32_t axis) {}
void initConcatenateLocalContext(rt_function_t *f) {}
void freeConcatenateLocalContext(rt_function_t *f) {}
void execConcatenate(rt_function_t *f) {}

// Split
void initSplitConfig(SplitConfig *config, int32_t axis) {}
void initSplitLocalContext(rt_function_t *f) {}
void freeSplitLocalContext(rt_function_t *f) {}
void execSplit(rt_function_t *f) {}

// Stack
void initStackConfig(StackConfig *config, int32_t axis) {}
void initStackLocalContext(rt_function_t *f) {}
void freeStackLocalContext(rt_function_t *f) {}
void execStack(rt_function_t *f) {}

// Slice
void initSliceConfig(SliceConfig *config, rt_list_t start, rt_list_t stop,
                     rt_list_t step) {}
void initSliceLocalContext(rt_function_t *f) {}
void freeSliceLocalContext(rt_function_t *f) {}
void execSlice(rt_function_t *f) {}

// Transpose
void initTransposeConfig(TransposeConfig *config, rt_list_t axes) {}
void initTransposeLocalContext(rt_function_t *f) {}
void freeTransposeLocalContext(rt_function_t *f) {}
void execTranspose(rt_function_t *f) {}

// Broadcast
void initBroadcastConfig(BroadcastConfig *config, rt_list_t shape) {}
void initBroadcastLocalContext(rt_function_t *f) {}
void freeBroadcastLocalContext(rt_function_t *f) {}
void execBroadcast(rt_function_t *f) {}

// OneHot
void initOneHotConfig(OneHotConfig *config, rt_list_t shape) {}
void initOneHotLocalContext(rt_function_t *f) {}
void freeOneHotLocalContext(rt_function_t *f) {}
void execOneHot(rt_function_t *f) {}

// Flip
void initFlipConfig(FlipConfig *config, rt_list_t axes) {}
void initFlipLocalContext(rt_function_t *f) {}
void freeFlipLocalContext(rt_function_t *f) {}
void execFlip(rt_function_t *f) {}

// Shift
void initShiftConfig(ShiftConfig *config, rt_list_t shifts,
                     uint32_t border_mode) {}
void initShiftLocalContext(rt_function_t *f) {}
void freeShiftLocalContext(rt_function_t *f) {}
void execShift(rt_function_t *f) {}

// Reshape
void initReshapeConfig(ReshapeConfig *config, rt_list_t shape) {}
void initReshapeLocalContext(rt_function_t *f) {}
void freeReshapeLocalContext(rt_function_t *f) {}
void execReshape(rt_function_t *f) {}

// MatrixDiag
void execMatrixDiag(rt_function_t *f) {}

// MatrixDiagPart
void execMatrixDiagPart(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
void initDropoutConfig(DropoutConfig *config, float p, int32_t seed) {}
void initDropoutLocalContext(rt_function_t *f) {}
void freeDropoutLocalContext(rt_function_t *f) {}
void execDropout(rt_function_t *f) {}

// Rand
void initRandConfig(RandConfig *config, float low, float high, rt_list_t shape,
                    int32_t seed) {}
void initRandLocalContext(rt_function_t *f) {}
void freeRandLocalContext(rt_function_t *f) {}
void execRand(rt_function_t *f) {}

// Randint
void initRandintConfig(RandintConfig *config, int32_t low, int32_t high,
                       rt_list_t shape, int32_t seed) {}
void initRandintLocalContext(rt_function_t *f) {}
void freeRandintLocalContext(rt_function_t *f) {}
void execRandint(rt_function_t *f) {}

// Randn
void initRandnConfig(RandnConfig *config, float mu, float sigma,
                     rt_list_t shape, int32_t seed) {}
void initRandnLocalContext(rt_function_t *f) {}
void freeRandnLocalContext(rt_function_t *f) {}
void execRandn(rt_function_t *f) {}

// RandomCrop
void initRandomCropConfig(RandomCropConfig *config, rt_list_t shape,
                          int32_t base_axis, int32_t seed) {}
void initRandomCropLocalContext(rt_function_t *f) {}
void freeRandomCropLocalContext(rt_function_t *f) {}
void execRandomCrop(rt_function_t *f) {}

// RandomFlip
void initRandomFlipConfig(RandomFlipConfig *config, rt_list_t axes,
                          int32_t base_axis, int32_t seed) {}
void initRandomFlipLocalContext(rt_function_t *f) {}
void freeRandomFlipLocalContext(rt_function_t *f) {}
void execRandomFlip(rt_function_t *f) {}

// RandomShift
void initRandomShiftConfig(RandomShiftConfig *config, rt_list_t shifts,
                           uint32_t border_mode, int32_t base_axis,
                           int32_t seed) {}
void initRandomShiftLocalContext(rt_function_t *f) {}
void freeRandomShiftLocalContext(rt_function_t *f) {}
void execRandomShift(rt_function_t *f) {}

// ImageAugmentation
void initImageAugmentationConfig(
    ImageAugmentationConfig *config, rt_list_t shape, rt_list_t pad,
    float min_scale, float max_scale, float angle, float aspect_ratio,
    float distortion, uint8_t flip_lr, uint8_t flip_ud, float brightness,
    uint8_t brightness_each, float contrast, float contrast_center,
    uint8_t contrast_each, float noise, int32_t seed) {}
void initImageAugmentationLocalContext(rt_function_t *f) {}
void freeImageAugmentationLocalContext(rt_function_t *f) {}
void execImageAugmentation(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Loss rt_function_ts
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy
void execSigmoidCrossEntropy(rt_function_t *f) {}

// BinaryCrossEntropy
void execBinaryCrossEntropy(rt_function_t *f) {}

// SoftmaxCrossEntropy
void initSoftmaxCrossEntropyConfig(SoftmaxCrossEntropyConfig *config,
                                   int32_t axis) {}
void initSoftmaxCrossEntropyLocalContext(rt_function_t *f) {}
void freeSoftmaxCrossEntropyLocalContext(rt_function_t *f) {}
void execSoftmaxCrossEntropy(rt_function_t *f) {}

// CategoricalCrossEntropy
void initCategoricalCrossEntropyConfig(CategoricalCrossEntropyConfig *config,
                                       int32_t axis) {}
void initCategoricalCrossEntropyLocalContext(rt_function_t *f) {}
void freeCategoricalCrossEntropyLocalContext(rt_function_t *f) {}
void execCategoricalCrossEntropy(rt_function_t *f) {}

// SquaredError
void execSquaredError(rt_function_t *f) {}

// AbsoluteError
void execAbsoluteError(rt_function_t *f) {}

// HuberLoss
void initHuberLossConfig(HuberLossConfig *config, float delta) {}
void initHuberLossLocalContext(rt_function_t *f) {}
void freeHuberLossLocalContext(rt_function_t *f) {}
void execHuberLoss(rt_function_t *f) {}

// EpsilonInsensitiveLoss
void initEpsilonInsensitiveLossConfig(EpsilonInsensitiveLossConfig *config,
                                      float epsilon) {}
void initEpsilonInsensitiveLossLocalContext(rt_function_t *f) {}
void freeEpsilonInsensitiveLossLocalContext(rt_function_t *f) {}
void execEpsilonInsensitiveLoss(rt_function_t *f) {}

// KLMultinomial
void initKLMultinomialConfig(KLMultinomialConfig *config, int32_t base_axis) {}
void initKLMultinomialLocalContext(rt_function_t *f) {}
void freeKLMultinomialLocalContext(rt_function_t *f) {}
void execKLMultinomial(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid
void execBinarySigmoid(rt_function_t *f) {}

// BinaryTanh
void execBinaryTanh(rt_function_t *f) {}

// BinaryConnectAffine
void initBinaryConnectAffineConfig(BinaryConnectAffineConfig *config,
                                   int32_t base_axis) {}
void initBinaryConnectAffineLocalContext(rt_function_t *f) {}
void freeBinaryConnectAffineLocalContext(rt_function_t *f) {}
void execBinaryConnectAffine(rt_function_t *f) {}

// BinaryConnectConvolution
void initBinaryConnectConvolutionConfig(BinaryConnectConvolutionConfig *config,
                                        int32_t base_axis, rt_list_t pad,
                                        rt_list_t stride, rt_list_t dilation,
                                        int32_t group) {}
void initBinaryConnectConvolutionLocalContext(rt_function_t *f) {}
void freeBinaryConnectConvolutionLocalContext(rt_function_t *f) {}
void execBinaryConnectConvolution(rt_function_t *f) {}

// BinaryWeightAffine
void initBinaryWeightAffineConfig(BinaryWeightAffineConfig *config,
                                  int32_t base_axis) {}
void initBinaryWeightAffineLocalContext(rt_function_t *f) {}
void freeBinaryWeightAffineLocalContext(rt_function_t *f) {}
void execBinaryWeightAffine(rt_function_t *f) {}

// BinaryWeightConvolution
void initBinaryWeightConvolutionConfig(BinaryWeightConvolutionConfig *config,
                                       int32_t base_axis, rt_list_t pad,
                                       rt_list_t stride, rt_list_t dilation,
                                       int32_t group) {}
void initBinaryWeightConvolutionLocalContext(rt_function_t *f) {}
void freeBinaryWeightConvolutionLocalContext(rt_function_t *f) {}
void execBinaryWeightConvolution(rt_function_t *f) {}

// INQAffine
void initINQAffineConfig(INQAffineConfig *config, int32_t base_axis,
                         int32_t num_bits, rt_list_t inq_iterations,
                         uint32_t selection_algorithm, int32_t seed) {}
void initINQAffineLocalContext(rt_function_t *f) {}
void freeINQAffineLocalContext(rt_function_t *f) {}
void execINQAffine(rt_function_t *f) {}

// INQConvolution
void initINQConvolutionConfig(INQConvolutionConfig *config, int32_t base_axis,
                              rt_list_t pad, rt_list_t stride,
                              rt_list_t dilation, int32_t group,
                              int32_t num_bits, rt_list_t inq_iterations,
                              uint32_t selection_algorithm, int32_t seed) {}
void initINQConvolutionLocalContext(rt_function_t *f) {}
void freeINQConvolutionLocalContext(rt_function_t *f) {}
void execINQConvolution(rt_function_t *f) {}

// FixedPointQuantize
void initFixedPointQuantizeConfig(FixedPointQuantizeConfig *config,
                                  uint8_t sign, int32_t n, float delta,
                                  uint8_t ste_fine_grained) {}
void initFixedPointQuantizeLocalContext(rt_function_t *f) {}
void freeFixedPointQuantizeLocalContext(rt_function_t *f) {}
void execFixedPointQuantize(rt_function_t *f) {}

// Pow2Quantize
void initPow2QuantizeConfig(Pow2QuantizeConfig *config, uint8_t sign,
                            uint8_t with_zero, int32_t n, int32_t m,
                            uint8_t ste_fine_grained) {}
void initPow2QuantizeLocalContext(rt_function_t *f) {}
void freePow2QuantizeLocalContext(rt_function_t *f) {}
void execPow2Quantize(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
void initTopNErrorConfig(TopNErrorConfig *config, int32_t axis, int32_t n) {}
void initTopNErrorLocalContext(rt_function_t *f) {}
void freeTopNErrorLocalContext(rt_function_t *f) {}
void execTopNError(rt_function_t *f) {}

// BinaryError
void execBinaryError(rt_function_t *f) {}

// ConfusionMatrix
void initConfusionMatrixConfig(ConfusionMatrixConfig *config, int32_t axis) {}
void initConfusionMatrixLocalContext(rt_function_t *f) {}
void freeConfusionMatrixLocalContext(rt_function_t *f) {}
void execConfusionMatrix(rt_function_t *f) {}

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
void initVATNoiseConfig(VATNoiseConfig *config, int32_t base_axis, float eps) {}
void initVATNoiseLocalContext(rt_function_t *f) {}
void freeVATNoiseLocalContext(rt_function_t *f) {}
void execVATNoise(rt_function_t *f) {}

// Unlink
void execUnlink(rt_function_t *f) {}

// Sink
void initSinkConfig(SinkConfig *config, uint8_t one_input_grad) {}
void initSinkLocalContext(rt_function_t *f) {}
void freeSinkLocalContext(rt_function_t *f) {}
void execSink(rt_function_t *f) {}
