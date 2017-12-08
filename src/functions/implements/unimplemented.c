// -*- coding:utf-8 -*-

#include <nnablart/functions.h>

////////////////////////////////////////////////////////////////////////////////
// Neural Network Layer
////////////////////////////////////////////////////////////////////////////////

// Convolution
void initConvolutionConfig(ConvolutionConfig *config, int32_t base_axis,
                           rt_list_t pad, rt_list_t stride, rt_list_t dilation, int32_t group) {}
void initConvolutionLocalContext(Function *f) {}
void freeConvolutionLocalContext(Function *f) {}
void execConvolution(Function *f) {}

// DepthwiseConvolution
void initDepthwiseConvolutionConfig(DepthwiseConvolutionConfig *config,
                                    int32_t base_axis, rt_list_t pad, rt_list_t stride,
                                    rt_list_t dilation, int32_t multiplier) {}
void initDepthwiseConvolutionLocalContext(Function *f) {}
void freeDepthwiseConvolutionLocalContext(Function *f) {}
void execDepthwiseConvolution(Function *f) {}

// Deconvolution
void initDeconvolutionConfig(DeconvolutionConfig *config, int32_t base_axis,
                             rt_list_t pad, rt_list_t stride, rt_list_t dilation,
                             int32_t group) {}
void initDeconvolutionLocalContext(Function *f) {}
void freeDeconvolutionLocalContext(Function *f) {}
void execDeconvolution(Function *f) {}

// MaxPooling
void initMaxPoolingConfig(MaxPoolingConfig *config, rt_list_t kernel, rt_list_t stride,
                          uint8_t ignore_border, rt_list_t pad) {}
void initMaxPoolingLocalContext(Function *f) {}
void freeMaxPoolingLocalContext(Function *f) {}
void execMaxPooling(Function *f) {}

// AveragePooling
void initAveragePoolingConfig(AveragePoolingConfig *config, rt_list_t kernel,
                              rt_list_t stride, uint8_t ignore_border, rt_list_t pad,
                              uint8_t including_pad) {}
void initAveragePoolingLocalContext(Function *f) {}
void freeAveragePoolingLocalContext(Function *f) {}
void execAveragePooling(Function *f) {}

// SumPooling
void initSumPoolingConfig(SumPoolingConfig *config, rt_list_t kernel, rt_list_t stride,
                          uint8_t ignore_border, rt_list_t pad) {}
void initSumPoolingLocalContext(Function *f) {}
void freeSumPoolingLocalContext(Function *f) {}
void execSumPooling(Function *f) {}

// Unpooling
void initUnpoolingConfig(UnpoolingConfig *config, rt_list_t kernel) {}
void initUnpoolingLocalContext(Function *f) {}
void freeUnpoolingLocalContext(Function *f) {}
void execUnpooling(Function *f) {}

// Embed
void execEmbed(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Neural Network Activation Functions
////////////////////////////////////////////////////////////////////////////////

// Sigmoid
void execSigmoid(Function *f) {}

// Swish
void execSwish(Function *f) {}

// Tanh
void execTanh(Function *f) {}

// ReLU
void initReLUConfig(ReLUConfig *config, uint8_t inplace) {}
void initReLULocalContext(Function *f) {}
void freeReLULocalContext(Function *f) {}
void execReLU(Function *f) {}

// LeakyReLU
void initLeakyReLUConfig(LeakyReLUConfig *config, float alpha) {}
void initLeakyReLULocalContext(Function *f) {}
void freeLeakyReLULocalContext(Function *f) {}
void execLeakyReLU(Function *f) {}

// Softmax
void initSoftmaxConfig(SoftmaxConfig *config, int32_t axis) {}
void initSoftmaxLocalContext(Function *f) {}
void freeSoftmaxLocalContext(Function *f) {}
void execSoftmax(Function *f) {}

// ELU
void initELUConfig(ELUConfig *config, float alpha) {}
void initELULocalContext(Function *f) {}
void freeELULocalContext(Function *f) {}
void execELU(Function *f) {}

// SELU
void initSELUConfig(SELUConfig *config, float scale, float alpha) {}
void initSELULocalContext(Function *f) {}
void freeSELULocalContext(Function *f) {}
void execSELU(Function *f) {}

// CReLU
void initCReLUConfig(CReLUConfig *config, int32_t axis) {}
void initCReLULocalContext(Function *f) {}
void freeCReLULocalContext(Function *f) {}
void execCReLU(Function *f) {}

// CELU
void initCELUConfig(CELUConfig *config, float alpha, int32_t axis) {}
void initCELULocalContext(Function *f) {}
void freeCELULocalContext(Function *f) {}
void execCELU(Function *f) {}

// PReLU
void initPReLUConfig(PReLUConfig *config, int32_t base_axis) {}
void initPReLULocalContext(Function *f) {}
void freePReLULocalContext(Function *f) {}
void execPReLU(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Normalization
////////////////////////////////////////////////////////////////////////////////

// BatchNormalization
void initBatchNormalizationConfig(BatchNormalizationConfig *config, rt_list_t axes,
                                  float decay_rate, float eps,
                                  uint8_t batch_stat) {}
void initBatchNormalizationLocalContext(Function *f) {}
void freeBatchNormalizationLocalContext(Function *f) {}
void execBatchNormalization(Function *f) {}

// MeanSubtraction
void initMeanSubtractionConfig(MeanSubtractionConfig *config, int32_t base_axis,
                               uint8_t update_running_mean) {}
void initMeanSubtractionLocalContext(Function *f) {}
void freeMeanSubtractionLocalContext(Function *f) {}
void execMeanSubtraction(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Reduction
////////////////////////////////////////////////////////////////////////////////

// Sum
void initSumConfig(SumConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initSumLocalContext(Function *f) {}
void freeSumLocalContext(Function *f) {}
void execSum(Function *f) {}

// Mean
void initMeanConfig(MeanConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initMeanLocalContext(Function *f) {}
void freeMeanLocalContext(Function *f) {}
void execMean(Function *f) {}

// Max
void initMaxConfig(MaxConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initMaxLocalContext(Function *f) {}
void freeMaxLocalContext(Function *f) {}
void execMax(Function *f) {}

// Min
void initMinConfig(MinConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initMinLocalContext(Function *f) {}
void freeMinLocalContext(Function *f) {}
void execMin(Function *f) {}

// Prod
void initProdConfig(ProdConfig *config, rt_list_t axes, uint8_t keep_dims) {}
void initProdLocalContext(Function *f) {}
void freeProdLocalContext(Function *f) {}
void execProd(Function *f) {}

// ReduceSum
void execReduceSum(Function *f) {}

// ReduceMean
void execReduceMean(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Arithmetic
////////////////////////////////////////////////////////////////////////////////

// Add2
void initAdd2Config(Add2Config *config, uint8_t inplace) {}
void initAdd2LocalContext(Function *f) {}
void freeAdd2LocalContext(Function *f) {}
void execAdd2(Function *f) {}

// BcAdd2
void execBcAdd2(Function *f) {}

// Sub2
void execSub2(Function *f) {}

// Mul2
void execMul2(Function *f) {}

// Div2
void execDiv2(Function *f) {}

// Pow2
void execPow2(Function *f) {}

// AddScalar
void initAddScalarConfig(AddScalarConfig *config, float val) {}
void initAddScalarLocalContext(Function *f) {}
void freeAddScalarLocalContext(Function *f) {}
void execAddScalar(Function *f) {}

// MulScalar
void initMulScalarConfig(MulScalarConfig *config, float val) {}
void initMulScalarLocalContext(Function *f) {}
void freeMulScalarLocalContext(Function *f) {}
void execMulScalar(Function *f) {}

// PowScalar
void initPowScalarConfig(PowScalarConfig *config, float val) {}
void initPowScalarLocalContext(Function *f) {}
void freePowScalarLocalContext(Function *f) {}
void execPowScalar(Function *f) {}

// RSubScalar
void initRSubScalarConfig(RSubScalarConfig *config, float val) {}
void initRSubScalarLocalContext(Function *f) {}
void freeRSubScalarLocalContext(Function *f) {}
void execRSubScalar(Function *f) {}

// RDivScalar
void initRDivScalarConfig(RDivScalarConfig *config, float val) {}
void initRDivScalarLocalContext(Function *f) {}
void freeRDivScalarLocalContext(Function *f) {}
void execRDivScalar(Function *f) {}

// RPowScalar
void initRPowScalarConfig(RPowScalarConfig *config, float val) {}
void initRPowScalarLocalContext(Function *f) {}
void freeRPowScalarLocalContext(Function *f) {}
void execRPowScalar(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Logical
////////////////////////////////////////////////////////////////////////////////

// Sign
void initSignConfig(SignConfig *config, float alpha) {}
void initSignLocalContext(Function *f) {}
void freeSignLocalContext(Function *f) {}
void execSign(Function *f) {}

// Minimum2
void execMinimum2(Function *f) {}

// Maximum2
void execMaximum2(Function *f) {}

// MinimumScalar
void initMinimumScalarConfig(MinimumScalarConfig *config, float val) {}
void initMinimumScalarLocalContext(Function *f) {}
void freeMinimumScalarLocalContext(Function *f) {}
void execMinimumScalar(Function *f) {}

// MaximumScalar
void initMaximumScalarConfig(MaximumScalarConfig *config, float val) {}
void initMaximumScalarLocalContext(Function *f) {}
void freeMaximumScalarLocalContext(Function *f) {}
void execMaximumScalar(Function *f) {}

// LogicalAnd
void execLogicalAnd(Function *f) {}

// LogicalOr
void execLogicalOr(Function *f) {}

// LogicalXor
void execLogicalXor(Function *f) {}

// Equal
void execEqual(Function *f) {}

// NotEqual
void execNotEqual(Function *f) {}

// GreaterEqual
void execGreaterEqual(Function *f) {}

// Greater
void execGreater(Function *f) {}

// LessEqual
void execLessEqual(Function *f) {}

// Less
void execLess(Function *f) {}

// LogicalAndScalar
void initLogicalAndScalarConfig(LogicalAndScalarConfig *config, uint8_t val) {}
void initLogicalAndScalarLocalContext(Function *f) {}
void freeLogicalAndScalarLocalContext(Function *f) {}
void execLogicalAndScalar(Function *f) {}

// LogicalOrScalar
void initLogicalOrScalarConfig(LogicalOrScalarConfig *config, uint8_t val) {}
void initLogicalOrScalarLocalContext(Function *f) {}
void freeLogicalOrScalarLocalContext(Function *f) {}
void execLogicalOrScalar(Function *f) {}

// LogicalXorScalar
void initLogicalXorScalarConfig(LogicalXorScalarConfig *config, uint8_t val) {}
void initLogicalXorScalarLocalContext(Function *f) {}
void freeLogicalXorScalarLocalContext(Function *f) {}
void execLogicalXorScalar(Function *f) {}

// EqualScalar
void initEqualScalarConfig(EqualScalarConfig *config, float val) {}
void initEqualScalarLocalContext(Function *f) {}
void freeEqualScalarLocalContext(Function *f) {}
void execEqualScalar(Function *f) {}

// NotEqualScalar
void initNotEqualScalarConfig(NotEqualScalarConfig *config, float val) {}
void initNotEqualScalarLocalContext(Function *f) {}
void freeNotEqualScalarLocalContext(Function *f) {}
void execNotEqualScalar(Function *f) {}

// GreaterEqualScalar
void initGreaterEqualScalarConfig(GreaterEqualScalarConfig *config, float val) {}
void initGreaterEqualScalarLocalContext(Function *f) {}
void freeGreaterEqualScalarLocalContext(Function *f) {}
void execGreaterEqualScalar(Function *f) {}

// GreaterScalar
void initGreaterScalarConfig(GreaterScalarConfig *config, float val) {}
void initGreaterScalarLocalContext(Function *f) {}
void freeGreaterScalarLocalContext(Function *f) {}
void execGreaterScalar(Function *f) {}

// LessEqualScalar
void initLessEqualScalarConfig(LessEqualScalarConfig *config, float val) {}
void initLessEqualScalarLocalContext(Function *f) {}
void freeLessEqualScalarLocalContext(Function *f) {}
void execLessEqualScalar(Function *f) {}

// LessScalar
void initLessScalarConfig(LessScalarConfig *config, float val) {}
void initLessScalarLocalContext(Function *f) {}
void freeLessScalarLocalContext(Function *f) {}
void execLessScalar(Function *f) {}

// LogicalNot
void execLogicalNot(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////

// Constant
void initConstantConfig(ConstantConfig *config, float val, rt_list_t shape) {}
void initConstantLocalContext(Function *f) {}
void freeConstantLocalContext(Function *f) {}
void execConstant(Function *f) {}

// Abs
void execAbs(Function *f) {}

// Exp
void execExp(Function *f) {}

// Log
void execLog(Function *f) {}

// Identity
void execIdentity(Function *f) {}

// BatchMatmul
void initBatchMatmulConfig(BatchMatmulConfig *config, uint8_t transpose_a,
                           uint8_t transpose_b) {}
void initBatchMatmulLocalContext(Function *f) {}
void freeBatchMatmulLocalContext(Function *f) {}
void execBatchMatmul(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Array Manipulation
////////////////////////////////////////////////////////////////////////////////

// Concatenate
void initConcatenateConfig(ConcatenateConfig *config, int32_t axis) {}
void initConcatenateLocalContext(Function *f) {}
void freeConcatenateLocalContext(Function *f) {}
void execConcatenate(Function *f) {}

// Split
void initSplitConfig(SplitConfig *config, int32_t axis) {}
void initSplitLocalContext(Function *f) {}
void freeSplitLocalContext(Function *f) {}
void execSplit(Function *f) {}

// Stack
void initStackConfig(StackConfig *config, int32_t axis) {}
void initStackLocalContext(Function *f) {}
void freeStackLocalContext(Function *f) {}
void execStack(Function *f) {}

// Slice
void initSliceConfig(SliceConfig *config, rt_list_t start, rt_list_t stop, rt_list_t step) {}
void initSliceLocalContext(Function *f) {}
void freeSliceLocalContext(Function *f) {}
void execSlice(Function *f) {}

// Transpose
void initTransposeConfig(TransposeConfig *config, rt_list_t axes) {}
void initTransposeLocalContext(Function *f) {}
void freeTransposeLocalContext(Function *f) {}
void execTranspose(Function *f) {}

// Broadcast
void initBroadcastConfig(BroadcastConfig *config, rt_list_t shape) {}
void initBroadcastLocalContext(Function *f) {}
void freeBroadcastLocalContext(Function *f) {}
void execBroadcast(Function *f) {}

// OneHot
void initOneHotConfig(OneHotConfig *config, rt_list_t shape) {}
void initOneHotLocalContext(Function *f) {}
void freeOneHotLocalContext(Function *f) {}
void execOneHot(Function *f) {}

// Flip
void initFlipConfig(FlipConfig *config, rt_list_t axes) {}
void initFlipLocalContext(Function *f) {}
void freeFlipLocalContext(Function *f) {}
void execFlip(Function *f) {}

// Shift
void initShiftConfig(ShiftConfig *config, rt_list_t shifts, uint32_t border_mode) {}
void initShiftLocalContext(Function *f) {}
void freeShiftLocalContext(Function *f) {}
void execShift(Function *f) {}

// Reshape
void initReshapeConfig(ReshapeConfig *config, rt_list_t shape) {}
void initReshapeLocalContext(Function *f) {}
void freeReshapeLocalContext(Function *f) {}
void execReshape(Function *f) {}

// MatrixDiag
void execMatrixDiag(Function *f) {}

// MatrixDiagPart
void execMatrixDiagPart(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Stochasticity
////////////////////////////////////////////////////////////////////////////////

// Dropout
void initDropoutConfig(DropoutConfig *config, float p, int32_t seed) {}
void initDropoutLocalContext(Function *f) {}
void freeDropoutLocalContext(Function *f) {}
void execDropout(Function *f) {}

// Rand
void initRandConfig(RandConfig *config, float low, float high, rt_list_t shape,
                    int32_t seed) {}
void initRandLocalContext(Function *f) {}
void freeRandLocalContext(Function *f) {}
void execRand(Function *f) {}

// Randint
void initRandintConfig(RandintConfig *config, int32_t low, int32_t high,
                       rt_list_t shape, int32_t seed) {}
void initRandintLocalContext(Function *f) {}
void freeRandintLocalContext(Function *f) {}
void execRandint(Function *f) {}

// Randn
void initRandnConfig(RandnConfig *config, float mu, float sigma, rt_list_t shape,
                     int32_t seed) {}
void initRandnLocalContext(Function *f) {}
void freeRandnLocalContext(Function *f) {}
void execRandn(Function *f) {}

// RandomCrop
void initRandomCropConfig(RandomCropConfig *config, rt_list_t shape,
                          int32_t base_axis, int32_t seed) {}
void initRandomCropLocalContext(Function *f) {}
void freeRandomCropLocalContext(Function *f) {}
void execRandomCrop(Function *f) {}

// RandomFlip
void initRandomFlipConfig(RandomFlipConfig *config, rt_list_t axes,
                          int32_t base_axis, int32_t seed) {}
void initRandomFlipLocalContext(Function *f) {}
void freeRandomFlipLocalContext(Function *f) {}
void execRandomFlip(Function *f) {}

// RandomShift
void initRandomShiftConfig(RandomShiftConfig *config, rt_list_t shifts,
                           uint32_t border_mode, int32_t base_axis,
                           int32_t seed) {}
void initRandomShiftLocalContext(Function *f) {}
void freeRandomShiftLocalContext(Function *f) {}
void execRandomShift(Function *f) {}

// ImageAugmentation
void initImageAugmentationConfig(ImageAugmentationConfig *config, rt_list_t shape,
                                 rt_list_t pad, float min_scale, float max_scale,
                                 float angle, float aspect_ratio,
                                 float distortion, uint8_t flip_lr,
                                 uint8_t flip_ud, float brightness,
                                 uint8_t brightness_each, float contrast,
                                 float contrast_center, uint8_t contrast_each,
                                 float noise, int32_t seed) {}
void initImageAugmentationLocalContext(Function *f) {}
void freeImageAugmentationLocalContext(Function *f) {}
void execImageAugmentation(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Loss Functions
////////////////////////////////////////////////////////////////////////////////

// SigmoidCrossEntropy
void execSigmoidCrossEntropy(Function *f) {}

// BinaryCrossEntropy
void execBinaryCrossEntropy(Function *f) {}

// SoftmaxCrossEntropy
void initSoftmaxCrossEntropyConfig(SoftmaxCrossEntropyConfig *config,
                                   int32_t axis) {}
void initSoftmaxCrossEntropyLocalContext(Function *f) {}
void freeSoftmaxCrossEntropyLocalContext(Function *f) {}
void execSoftmaxCrossEntropy(Function *f) {}

// CategoricalCrossEntropy
void initCategoricalCrossEntropyConfig(CategoricalCrossEntropyConfig *config,
                                       int32_t axis) {}
void initCategoricalCrossEntropyLocalContext(Function *f) {}
void freeCategoricalCrossEntropyLocalContext(Function *f) {}
void execCategoricalCrossEntropy(Function *f) {}

// SquaredError
void execSquaredError(Function *f) {}

// AbsoluteError
void execAbsoluteError(Function *f) {}

// HuberLoss
void initHuberLossConfig(HuberLossConfig *config, float delta) {}
void initHuberLossLocalContext(Function *f) {}
void freeHuberLossLocalContext(Function *f) {}
void execHuberLoss(Function *f) {}

// EpsilonInsensitiveLoss
void initEpsilonInsensitiveLossConfig(EpsilonInsensitiveLossConfig *config,
                                      float epsilon) {}
void initEpsilonInsensitiveLossLocalContext(Function *f) {}
void freeEpsilonInsensitiveLossLocalContext(Function *f) {}
void execEpsilonInsensitiveLoss(Function *f) {}

// KLMultinomial
void initKLMultinomialConfig(KLMultinomialConfig *config, int32_t base_axis) {}
void initKLMultinomialLocalContext(Function *f) {}
void freeKLMultinomialLocalContext(Function *f) {}
void execKLMultinomial(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Quantization Neural Network Layers
////////////////////////////////////////////////////////////////////////////////

// BinarySigmoid
void execBinarySigmoid(Function *f) {}

// BinaryTanh
void execBinaryTanh(Function *f) {}

// BinaryConnectAffine
void initBinaryConnectAffineConfig(BinaryConnectAffineConfig *config,
                                   int32_t base_axis) {}
void initBinaryConnectAffineLocalContext(Function *f) {}
void freeBinaryConnectAffineLocalContext(Function *f) {}
void execBinaryConnectAffine(Function *f) {}

// BinaryConnectConvolution
void initBinaryConnectConvolutionConfig(BinaryConnectConvolutionConfig *config,
                                        int32_t base_axis, rt_list_t pad,
                                        rt_list_t stride, rt_list_t dilation,
                                        int32_t group) {}
void initBinaryConnectConvolutionLocalContext(Function *f) {}
void freeBinaryConnectConvolutionLocalContext(Function *f) {}
void execBinaryConnectConvolution(Function *f) {}

// BinaryWeightAffine
void initBinaryWeightAffineConfig(BinaryWeightAffineConfig *config,
                                  int32_t base_axis) {}
void initBinaryWeightAffineLocalContext(Function *f) {}
void freeBinaryWeightAffineLocalContext(Function *f) {}
void execBinaryWeightAffine(Function *f) {}

// BinaryWeightConvolution
void initBinaryWeightConvolutionConfig(BinaryWeightConvolutionConfig *config,
                                       int32_t base_axis, rt_list_t pad, rt_list_t stride,
                                       rt_list_t dilation, int32_t group) {}
void initBinaryWeightConvolutionLocalContext(Function *f) {}
void freeBinaryWeightConvolutionLocalContext(Function *f) {}
void execBinaryWeightConvolution(Function *f) {}

// INQAffine
void initINQAffineConfig(INQAffineConfig *config, int32_t base_axis,
                         int32_t num_bits, rt_list_t inq_iterations,
                         uint32_t selection_algorithm, int32_t seed) {}
void initINQAffineLocalContext(Function *f) {}
void freeINQAffineLocalContext(Function *f) {}
void execINQAffine(Function *f) {}

// INQConvolution
void initINQConvolutionConfig(INQConvolutionConfig *config, int32_t base_axis,
                              rt_list_t pad, rt_list_t stride, rt_list_t dilation,
                              int32_t group, int32_t num_bits,
                              rt_list_t inq_iterations, uint32_t selection_algorithm,
                              int32_t seed) {}
void initINQConvolutionLocalContext(Function *f) {}
void freeINQConvolutionLocalContext(Function *f) {}
void execINQConvolution(Function *f) {}

// FixedPointQuantize
void initFixedPointQuantizeConfig(FixedPointQuantizeConfig *config,
                                  uint8_t sign, int32_t n, float delta,
                                  uint8_t ste_fine_grained) {}
void initFixedPointQuantizeLocalContext(Function *f) {}
void freeFixedPointQuantizeLocalContext(Function *f) {}
void execFixedPointQuantize(Function *f) {}

// Pow2Quantize
void initPow2QuantizeConfig(Pow2QuantizeConfig *config, uint8_t sign,
                            uint8_t with_zero, int32_t n, int32_t m,
                            uint8_t ste_fine_grained) {}
void initPow2QuantizeLocalContext(Function *f) {}
void freePow2QuantizeLocalContext(Function *f) {}
void execPow2Quantize(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Validation
////////////////////////////////////////////////////////////////////////////////

// TopNError
void initTopNErrorConfig(TopNErrorConfig *config, int32_t axis, int32_t n) {}
void initTopNErrorLocalContext(Function *f) {}
void freeTopNErrorLocalContext(Function *f) {}
void execTopNError(Function *f) {}

// BinaryError
void execBinaryError(Function *f) {}

// ConfusionMatrix
void initConfusionMatrixConfig(ConfusionMatrixConfig *config, int32_t axis) {}
void initConfusionMatrixLocalContext(Function *f) {}
void freeConfusionMatrixLocalContext(Function *f) {}
void execConfusionMatrix(Function *f) {}

////////////////////////////////////////////////////////////////////////////////
// Unsupported, Special Use
////////////////////////////////////////////////////////////////////////////////

// VATNoise
void initVATNoiseConfig(VATNoiseConfig *config, int32_t base_axis, float eps) {}
void initVATNoiseLocalContext(Function *f) {}
void freeVATNoiseLocalContext(Function *f) {}
void execVATNoise(Function *f) {}

// Unlink
void execUnlink(Function *f) {}

// Sink
void initSinkConfig(SinkConfig *config, uint8_t one_input_grad) {}
void initSinkLocalContext(Function *f) {}
void freeSinkLocalContext(Function *f) {}
void execSink(Function *f) {}
