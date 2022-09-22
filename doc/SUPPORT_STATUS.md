<!--
 Copyright (c) 2017 Sony Corporation. All Rights Reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 *WARNING*
 THIS FILE IS AUTO-GENERATED DUMMY CODE BY CODE GENERATOR.
-->

# Implement status

Total 62/219


## Neural Network Layer
Count 8/18

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|            Affine            |     yes      |     yes      |     yes      |
|             RNN              |      no      |      -       |      -       |
|             LSTM             |      no      |      -       |      -       |
|             GRU              |      no      |      -       |      -       |
|         Convolution          |     yes      |     yes      |     yes      |
|       FusedConvolution       |      no      |      -       |      -       |
|     DepthwiseConvolution     |     yes      |     yes      |     yes      |
|        Deconvolution         |     yes      |     yes      |     yes      |
|    DepthwiseDeconvolution    |      no      |      -       |      -       |
|    DeformableConvolution     |      no      |      -       |      -       |
| AdaptiveSeparableConvolution |      no      |      -       |      -       |
|          MaxPooling          |     yes      |     yes      |     yes      |
|        AveragePooling        |     yes      |     yes      |     yes      |
|     GlobalAveragePooling     |      no      |      -       |      -       |
|          SumPooling          |     yes      |     yes      |     yes      |
|          Unpooling           |     yes      |     yes      |     yes      |
|            Embed             |      no      |      -       |      -       |
|           RoiAlign           |      no      |      -       |      -       |

## Neural Network Activation Functions
Count 11/22

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|           Sigmoid            |     yes      |     yes      |     yes      |
|            Swish             |     yes      |     yes      |     yes      |
|             Tanh             |     yes      |     yes      |     yes      |
|             ReLU             |     yes      |     yes      |     yes      |
|          LeakyReLU           |     yes      |     yes      |     yes      |
|           Softmax            |     yes      |     yes      |     yes      |
|          LogSoftmax          |      no      |      -       |      -       |
|             ELU              |     yes      |     yes      |     yes      |
|             SELU             |     yes      |     yes      |     yes      |
|            CReLU             |     yes      |     yes      |     yes      |
|             CELU             |     yes      |     yes      |     yes      |
|            PReLU             |     yes      |     yes      |     yes      |
|             GELU             |      no      |      -       |      -       |
|             Mish             |      no      |      -       |      -       |
|            ReLU6             |      no      |      -       |      -       |
|         HardSigmoid          |      no      |      -       |      -       |
|           HardTanh           |      no      |      -       |      -       |
|          LogSigmoid          |      no      |      -       |      -       |
|           SoftPlus           |      no      |      -       |      -       |
|           SoftSign           |      no      |      -       |      -       |
|          TanhShrink          |      no      |      -       |      -       |
|             Sinc             |      no      |      -       |      -       |

## Normalization
Count 2/14

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|   FusedBatchNormalization    |      no      |      -       |      -       |
|      BatchNormalization      |     yes      |     yes      |     yes      |
|      GroupNormalization      |      no      |      -       |      -       |
|    InstanceNormalization     |      no      |      -       |      -       |
|      LayerNormalization      |      no      |      -       |      -       |
|      NormNormalization       |      no      |      -       |      -       |
|    SyncBatchNormalization    |      no      |      -       |      -       |
|     TensorNormalization      |      no      |      -       |      -       |
|     WeightNormalization      |      no      |      -       |      -       |
|    WeightStandardization     |      no      |      -       |      -       |
|         SpectralNorm         |      no      |      -       |      -       |
|       MeanSubtraction        |     yes      |     yes      |     yes      |
|       ClipGradByValue        |      no      |      -       |      -       |
|        ClipGradByNorm        |      no      |      -       |      -       |

## Reduction
Count 1/10

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|             Sum              |     yes      |     yes      |     yes      |
|            CumSum            |      no      |      -       |      -       |
|             Mean             |      no      |      -       |      -       |
|             Max              |      no      |      -       |      -       |
|             Min              |      no      |      -       |      -       |
|             Norm             |      no      |      -       |      -       |
|             Prod             |      no      |      -       |      -       |
|           CumProd            |      no      |      -       |      -       |
|          ReduceSum           |      no      |      -       |      -       |
|          ReduceMean          |      no      |      -       |      -       |

## Arithmetic
Count 11/14

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|             Add2             |     yes      |     yes      |     yes      |
|             AddN             |      no      |      -       |      -       |
|            BcAdd2            |      no      |      -       |      -       |
|             Sub2             |     yes      |     yes      |     yes      |
|             Mul2             |     yes      |     yes      |     yes      |
|             MulN             |      no      |      -       |      -       |
|             Div2             |     yes      |     yes      |     yes      |
|             Pow2             |     yes      |     yes      |     yes      |
|          AddScalar           |     yes      |     yes      |     yes      |
|          MulScalar           |     yes      |     yes      |     yes      |
|          PowScalar           |     yes      |     yes      |     yes      |
|          RSubScalar          |     yes      |     yes      |     yes      |
|          RDivScalar          |     yes      |     yes      |     yes      |
|          RPowScalar          |     yes      |     yes      |     yes      |

## Logical
Count 5/30

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|             Sign             |     yes      |     yes      |     yes      |
|           Minimum2           |     yes      |     yes      |     yes      |
|           Maximum2           |     yes      |     yes      |     yes      |
|        MinimumScalar         |     yes      |     yes      |     yes      |
|        MaximumScalar         |     yes      |     yes      |     yes      |
|          LogicalAnd          |      no      |      -       |      -       |
|          LogicalOr           |      no      |      -       |      -       |
|          LogicalXor          |      no      |      -       |      -       |
|            Equal             |      no      |      -       |      -       |
|           NotEqual           |      no      |      -       |      -       |
|         GreaterEqual         |      no      |      -       |      -       |
|           Greater            |      no      |      -       |      -       |
|          LessEqual           |      no      |      -       |      -       |
|             Less             |      no      |      -       |      -       |
|         SearchSorted         |      no      |      -       |      -       |
|       LogicalAndScalar       |      no      |      -       |      -       |
|       LogicalOrScalar        |      no      |      -       |      -       |
|       LogicalXorScalar       |      no      |      -       |      -       |
|         EqualScalar          |      no      |      -       |      -       |
|        NotEqualScalar        |      no      |      -       |      -       |
|      GreaterEqualScalar      |      no      |      -       |      -       |
|        GreaterScalar         |      no      |      -       |      -       |
|       LessEqualScalar        |      no      |      -       |      -       |
|          LessScalar          |      no      |      -       |      -       |
|          LogicalNot          |      no      |      -       |      -       |
|            IsNaN             |      no      |      -       |      -       |
|            IsInf             |      no      |      -       |      -       |
|           ResetNaN           |      no      |      -       |      -       |
|           ResetInf           |      no      |      -       |      -       |
|            Where             |      no      |      -       |      -       |

## Math
Count 6/24

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|           Constant           |      no      |      -       |      -       |
|            Arange            |      no      |      -       |      -       |
|           Linspace           |      no      |      -       |      -       |
|             Abs              |     yes      |     yes      |     yes      |
|             Exp              |     yes      |     yes      |     yes      |
|             Log              |     yes      |     yes      |     yes      |
|           Identity           |     yes      |     yes      |     yes      |
|         BatchMatmul          |     yes      |     yes      |     yes      |
|            Round             |     yes      |     yes      |     yes      |
|             Ceil             |      no      |      -       |      -       |
|            Floor             |      no      |      -       |      -       |
|             Sin              |      no      |      -       |      -       |
|             Cos              |      no      |      -       |      -       |
|             Tan              |      no      |      -       |      -       |
|             Sinh             |      no      |      -       |      -       |
|             Cosh             |      no      |      -       |      -       |
|             ASin             |      no      |      -       |      -       |
|             ACos             |      no      |      -       |      -       |
|             ATan             |      no      |      -       |      -       |
|            ATan2             |      no      |      -       |      -       |
|            ASinh             |      no      |      -       |      -       |
|            ACosh             |      no      |      -       |      -       |
|            ATanh             |      no      |      -       |      -       |
|             Erf              |      no      |      -       |      -       |

## Array Manipulation
Count 11/32

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|         Concatenate          |     yes      |     yes      |     yes      |
|            Split             |     yes      |     yes      |     yes      |
|            Stack             |     yes      |     yes      |     yes      |
|            Slice             |     yes      |     yes      |     yes      |
|             Pad              |     yes      |     yes      |     yes      |
|          Transpose           |     yes      |     yes      |     yes      |
|          Broadcast           |      no      |      -       |      -       |
|         BroadcastTo          |      no      |      -       |      -       |
|             Tile             |      no      |      -       |      -       |
|            OneHot            |      no      |      -       |      -       |
|             Flip             |     yes      |     yes      |     yes      |
|            Shift             |     yes      |     yes      |     yes      |
|             Sort             |      no      |      -       |      -       |
|           Reshape            |     yes      |     yes      |     yes      |
|            Shape             |      no      |      -       |      -       |
|          MatrixDiag          |     yes      |     yes      |     yes      |
|        MatrixDiagPart        |     yes      |     yes      |     yes      |
|           Meshgrid           |      no      |      -       |      -       |
|           BatchDet           |      no      |      -       |      -       |
|           BatchInv           |      no      |      -       |      -       |
|         BatchLogdet          |      no      |      -       |      -       |
|        BatchCholesky         |      no      |      -       |      -       |
|            Assign            |      no      |      -       |      -       |
|            Gather            |      no      |      -       |      -       |
|           GatherNd           |      no      |      -       |      -       |
|          BoolGather          |      no      |      -       |      -       |
|          ScatterNd           |      no      |      -       |      -       |
|          ScatterAdd          |      no      |      -       |      -       |
|         BoolScatter          |      no      |      -       |      -       |
|           BoolFill           |      no      |      -       |      -       |
|      PackPaddedSequence      |      no      |      -       |      -       |
|      PadPackedSequence       |      no      |      -       |      -       |

## Signal Processing
Count 0/5

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|         Interpolate          |      no      |      -       |      -       |
|             FFT              |      no      |      -       |      -       |
|             IFFT             |      no      |      -       |      -       |
|             STFT             |      no      |      -       |      -       |
|            ISTFT             |      no      |      -       |      -       |

## Stochasticity
Count 1/15

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|           Dropout            |     yes      |     yes      |     yes      |
|           TopKData           |      no      |      -       |      -       |
|           TopKGrad           |      no      |      -       |      -       |
|             Rand             |      no      |      -       |      -       |
|           Randint            |      no      |      -       |      -       |
|            Randn             |      no      |      -       |      -       |
|         RandBinomial         |      no      |      -       |      -       |
|           RandBeta           |      no      |      -       |      -       |
|          RandGamma           |      no      |      -       |      -       |
|         RandomChoice         |      no      |      -       |      -       |
|          RandomCrop          |      no      |      -       |      -       |
|          RandomFlip          |      no      |      -       |      -       |
|         RandomShift          |      no      |      -       |      -       |
|         RandomErase          |      no      |      -       |      -       |
|      ImageAugmentation       |      no      |      -       |      -       |

## Loss Functions
Count 0/9

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|     SigmoidCrossEntropy      |      no      |      -       |      -       |
|      BinaryCrossEntropy      |      no      |      -       |      -       |
|     SoftmaxCrossEntropy      |      no      |      -       |      -       |
|   CategoricalCrossEntropy    |      no      |      -       |      -       |
|         SquaredError         |      no      |      -       |      -       |
|        AbsoluteError         |      no      |      -       |      -       |
|          HuberLoss           |      no      |      -       |      -       |
|    EpsilonInsensitiveLoss    |      no      |      -       |      -       |
|        KLMultinomial         |      no      |      -       |      -       |

## Geometric Neural Network Layers
Count 0/3

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|          AffineGrid          |      no      |      -       |      -       |
|          WarpByGrid          |      no      |      -       |      -       |
|          WarpByFlow          |      no      |      -       |      -       |

## Quantization Neural Network Layers
Count 6/14

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|        BinarySigmoid         |     yes      |     yes      |     yes      |
|          BinaryTanh          |     yes      |     yes      |     yes      |
|     BinaryConnectAffine      |     yes      |     yes      |     yes      |
|   BinaryConnectConvolution   |     yes      |     yes      |     yes      |
|      BinaryWeightAffine      |     yes      |     yes      |     yes      |
|   BinaryWeightConvolution    |     yes      |     yes      |     yes      |
|          INQAffine           |      no      |      -       |      -       |
|        INQConvolution        |      no      |      -       |      -       |
|      FixedPointQuantize      |      no      |      -       |      -       |
|        MinMaxQuantize        |      no      |      -       |      -       |
|         Pow2Quantize         |      no      |      -       |      -       |
|            Prune             |      no      |      -       |      -       |
|        QuantizeLinear        |      no      |      -       |      -       |
|       DequantizeLinear       |      no      |      -       |      -       |

## Validation
Count 0/3

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|          TopNError           |      no      |      -       |      -       |
|         BinaryError          |      no      |      -       |      -       |
|       ConfusionMatrix        |      no      |      -       |      -       |

## Unsupported, Special Use
Count 0/6

|           Function           |  Available   |    float     |   generic    |
|------------------------------|--------------|--------------|--------------|
|           VATNoise           |      no      |      -       |      -       |
|            Unlink            |      no      |      -       |      -       |
|             Sink             |      no      |      -       |      -       |
|        NmsDetection2d        |      no      |      -       |      -       |
|      MaxPoolingBackward      |      no      |      -       |      -       |
|       PatchCorrelation       |      no      |      -       |      -       |

