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

Total 61/142


## Neural Network Layer
Count 8/11

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|          Affine          |     yes      |     yes      |     yes      |
|       Convolution        |     yes      |     yes      |     yes      |
|   DepthwiseConvolution   |     yes      |     yes      |     yes      |
|      Deconvolution       |     yes      |     yes      |     yes      |
|  DepthwiseDeconvolution  |      no      |      -       |      -       |
|        MaxPooling        |     yes      |     yes      |     yes      |
|      AveragePooling      |     yes      |     yes      |     yes      |
|   GlobalAveragePooling   |      no      |      -       |      -       |
|        SumPooling        |     yes      |     yes      |     yes      |
|        Unpooling         |     yes      |     yes      |     yes      |
|          Embed           |      no      |      -       |      -       |

## Neural Network Activation Functions
Count 11/11

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Sigmoid          |     yes      |     yes      |     yes      |
|          Swish           |     yes      |     yes      |     yes      |
|           Tanh           |     yes      |     yes      |     yes      |
|           ReLU           |     yes      |     yes      |     yes      |
|        LeakyReLU         |     yes      |     yes      |     yes      |
|         Softmax          |     yes      |     yes      |     yes      |
|           ELU            |     yes      |     yes      |     yes      |
|           SELU           |     yes      |     yes      |     yes      |
|          CReLU           |     yes      |     yes      |     yes      |
|           CELU           |     yes      |     yes      |     yes      |
|          PReLU           |     yes      |     yes      |     yes      |

## Normalization
Count 2/4

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|    BatchNormalization    |     yes      |     yes      |     yes      |
|     MeanSubtraction      |     yes      |     yes      |     yes      |
|     ClipGradByValue      |      no      |      -       |      -       |
|      ClipGradByNorm      |      no      |      -       |      -       |

## Reduction
Count 1/7

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Sum            |     yes      |     yes      |     yes      |
|           Mean           |      no      |      -       |      -       |
|           Max            |      no      |      -       |      -       |
|           Min            |      no      |      -       |      -       |
|           Prod           |      no      |      -       |      -       |
|        ReduceSum         |      no      |      -       |      -       |
|        ReduceMean        |      no      |      -       |      -       |

## Arithmetic
Count 11/12

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Add2           |     yes      |     yes      |     yes      |
|          BcAdd2          |      no      |      -       |      -       |
|           Sub2           |     yes      |     yes      |     yes      |
|           Mul2           |     yes      |     yes      |     yes      |
|           Div2           |     yes      |     yes      |     yes      |
|           Pow2           |     yes      |     yes      |     yes      |
|        AddScalar         |     yes      |     yes      |     yes      |
|        MulScalar         |     yes      |     yes      |     yes      |
|        PowScalar         |     yes      |     yes      |     yes      |
|        RSubScalar        |     yes      |     yes      |     yes      |
|        RDivScalar        |     yes      |     yes      |     yes      |
|        RPowScalar        |     yes      |     yes      |     yes      |

## Logical
Count 5/24

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Sign           |     yes      |     yes      |     yes      |
|         Minimum2         |     yes      |     yes      |     yes      |
|         Maximum2         |     yes      |     yes      |     yes      |
|      MinimumScalar       |     yes      |     yes      |     yes      |
|      MaximumScalar       |     yes      |     yes      |     yes      |
|        LogicalAnd        |      no      |      -       |      -       |
|        LogicalOr         |      no      |      -       |      -       |
|        LogicalXor        |      no      |      -       |      -       |
|          Equal           |      no      |      -       |      -       |
|         NotEqual         |      no      |      -       |      -       |
|       GreaterEqual       |      no      |      -       |      -       |
|         Greater          |      no      |      -       |      -       |
|        LessEqual         |      no      |      -       |      -       |
|           Less           |      no      |      -       |      -       |
|     LogicalAndScalar     |      no      |      -       |      -       |
|     LogicalOrScalar      |      no      |      -       |      -       |
|     LogicalXorScalar     |      no      |      -       |      -       |
|       EqualScalar        |      no      |      -       |      -       |
|      NotEqualScalar      |      no      |      -       |      -       |
|    GreaterEqualScalar    |      no      |      -       |      -       |
|      GreaterScalar       |      no      |      -       |      -       |
|     LessEqualScalar      |      no      |      -       |      -       |
|        LessScalar        |      no      |      -       |      -       |
|        LogicalNot        |      no      |      -       |      -       |

## Math
Count 6/20

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Constant         |      no      |      -       |      -       |
|           Abs            |     yes      |     yes      |     yes      |
|           Exp            |     yes      |     yes      |     yes      |
|           Log            |     yes      |     yes      |     yes      |
|         Identity         |     yes      |     yes      |     yes      |
|       BatchMatmul        |     yes      |     yes      |     yes      |
|          Round           |     yes      |     yes      |     yes      |
|           Ceil           |      no      |      -       |      -       |
|          Floor           |      no      |      -       |      -       |
|           Sin            |      no      |      -       |      -       |
|           Cos            |      no      |      -       |      -       |
|           Tan            |      no      |      -       |      -       |
|           Sinh           |      no      |      -       |      -       |
|           Cosh           |      no      |      -       |      -       |
|           ASin           |      no      |      -       |      -       |
|           ACos           |      no      |      -       |      -       |
|           ATan           |      no      |      -       |      -       |
|          ASinh           |      no      |      -       |      -       |
|          ACosh           |      no      |      -       |      -       |
|          ATanh           |      no      |      -       |      -       |

## Array Manipulation
Count 10/14

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|       Concatenate        |     yes      |     yes      |     yes      |
|          Split           |     yes      |     yes      |     yes      |
|          Stack           |     yes      |     yes      |     yes      |
|          Slice           |     yes      |     yes      |     yes      |
|           Pad            |      no      |      -       |      -       |
|        Transpose         |     yes      |     yes      |     yes      |
|        Broadcast         |      no      |      -       |      -       |
|       BroadcastTo        |      no      |      -       |      -       |
|          OneHot          |      no      |      -       |      -       |
|           Flip           |     yes      |     yes      |     yes      |
|          Shift           |     yes      |     yes      |     yes      |
|         Reshape          |     yes      |     yes      |     yes      |
|        MatrixDiag        |     yes      |     yes      |     yes      |
|      MatrixDiagPart      |     yes      |     yes      |     yes      |

## Signal Processing
Count 0/3

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|       Interpolate        |      no      |      -       |      -       |
|           FFT            |      no      |      -       |      -       |
|           IFFT           |      no      |      -       |      -       |

## Stochasticity
Count 1/10

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Dropout          |     yes      |     yes      |     yes      |
|         TopKData         |      no      |      -       |      -       |
|         TopKGrad         |      no      |      -       |      -       |
|           Rand           |      no      |      -       |      -       |
|         Randint          |      no      |      -       |      -       |
|          Randn           |      no      |      -       |      -       |
|        RandomCrop        |      no      |      -       |      -       |
|        RandomFlip        |      no      |      -       |      -       |
|       RandomShift        |      no      |      -       |      -       |
|    ImageAugmentation     |      no      |      -       |      -       |

## Loss Functions
Count 0/9

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|   SigmoidCrossEntropy    |      no      |      -       |      -       |
|    BinaryCrossEntropy    |      no      |      -       |      -       |
|   SoftmaxCrossEntropy    |      no      |      -       |      -       |
| CategoricalCrossEntropy  |      no      |      -       |      -       |
|       SquaredError       |      no      |      -       |      -       |
|      AbsoluteError       |      no      |      -       |      -       |
|        HuberLoss         |      no      |      -       |      -       |
|  EpsilonInsensitiveLoss  |      no      |      -       |      -       |
|      KLMultinomial       |      no      |      -       |      -       |

## Quantization Neural Network Layers
Count 6/10

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|      BinarySigmoid       |     yes      |     yes      |     yes      |
|        BinaryTanh        |     yes      |     yes      |     yes      |
|   BinaryConnectAffine    |     yes      |     yes      |     yes      |
| BinaryConnectConvolution |     yes      |     yes      |     yes      |
|    BinaryWeightAffine    |     yes      |     yes      |     yes      |
| BinaryWeightConvolution  |     yes      |     yes      |     yes      |
|        INQAffine         |      no      |      -       |      -       |
|      INQConvolution      |      no      |      -       |      -       |
|    FixedPointQuantize    |      no      |      -       |      -       |
|       Pow2Quantize       |      no      |      -       |      -       |

## Validation
Count 0/3

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|        TopNError         |      no      |      -       |      -       |
|       BinaryError        |      no      |      -       |      -       |
|     ConfusionMatrix      |      no      |      -       |      -       |

## Unsupported, Special Use
Count 0/4

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         VATNoise         |      no      |      -       |      -       |
|          Unlink          |      no      |      -       |      -       |
|           Sink           |      no      |      -       |      -       |
|      NmsDetection2d      |      no      |      -       |      -       |

