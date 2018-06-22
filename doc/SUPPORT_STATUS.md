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

Total 57/136


## Neural Network Layer
Count 6/11

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|          Affine          |     yes      |      -       |     yes      |
|       Convolution        |     yes      |     yes      |     yes      |
|   DepthwiseConvolution   |      no      |      -       |      -       |
|      Deconvolution       |      no      |      -       |      -       |
|  DepthwiseDeconvolution  |      no      |      -       |      -       |
|        MaxPooling        |     yes      |      -       |      -       |
|      AveragePooling      |     yes      |      -       |      -       |
|   GlobalAveragePooling   |      no      |      -       |      -       |
|        SumPooling        |     yes      |      -       |      -       |
|        Unpooling         |     yes      |      -       |      -       |
|          Embed           |      no      |      -       |      -       |

## Neural Network Activation Functions
Count 11/11

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Sigmoid          |     yes      |      -       |     yes      |
|          Swish           |     yes      |      -       |     yes      |
|           Tanh           |     yes      |      -       |     yes      |
|           ReLU           |     yes      |      -       |     yes      |
|        LeakyReLU         |     yes      |      -       |     yes      |
|         Softmax          |     yes      |      -       |     yes      |
|           ELU            |     yes      |      -       |     yes      |
|           SELU           |     yes      |      -       |     yes      |
|          CReLU           |     yes      |      -       |     yes      |
|           CELU           |     yes      |      -       |     yes      |
|          PReLU           |     yes      |      -       |     yes      |

## Normalization
Count 2/4

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|    BatchNormalization    |     yes      |      -       |     yes      |
|     MeanSubtraction      |     yes      |      -       |     yes      |
|     ClipGradByValue      |      no      |      -       |      -       |
|      ClipGradByNorm      |      no      |      -       |      -       |

## Reduction
Count 1/7

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Sum            |     yes      |      -       |     yes      |
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
|           Add2           |     yes      |      -       |     yes      |
|          BcAdd2          |      no      |      -       |      -       |
|           Sub2           |     yes      |      -       |     yes      |
|           Mul2           |     yes      |      -       |     yes      |
|           Div2           |     yes      |      -       |     yes      |
|           Pow2           |     yes      |      -       |     yes      |
|        AddScalar         |     yes      |      -       |     yes      |
|        MulScalar         |     yes      |      -       |     yes      |
|        PowScalar         |     yes      |      -       |     yes      |
|        RSubScalar        |     yes      |      -       |     yes      |
|        RDivScalar        |     yes      |      -       |     yes      |
|        RPowScalar        |     yes      |      -       |     yes      |

## Logical
Count 5/24

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Sign           |     yes      |      -       |     yes      |
|         Minimum2         |     yes      |      -       |     yes      |
|         Maximum2         |     yes      |      -       |     yes      |
|      MinimumScalar       |     yes      |      -       |     yes      |
|      MaximumScalar       |     yes      |      -       |     yes      |
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
Count 6/18

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Constant         |      no      |      -       |      -       |
|           Abs            |     yes      |      -       |     yes      |
|           Exp            |     yes      |      -       |     yes      |
|           Log            |     yes      |      -       |     yes      |
|         Identity         |     yes      |      -       |     yes      |
|       BatchMatmul        |     yes      |      -       |     yes      |
|          Round           |     yes      |      -       |     yes      |
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
Count 8/13

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|       Concatenate        |     yes      |      -       |     yes      |
|          Split           |     yes      |      -       |     yes      |
|          Stack           |     yes      |      -       |     yes      |
|          Slice           |     yes      |      -       |     yes      |
|           Pad            |      no      |      -       |      -       |
|        Transpose         |      no      |      -       |      -       |
|        Broadcast         |      no      |      -       |      -       |
|          OneHot          |      no      |      -       |      -       |
|           Flip           |      no      |      -       |      -       |
|          Shift           |     yes      |      -       |     yes      |
|         Reshape          |     yes      |      -       |     yes      |
|        MatrixDiag        |     yes      |      -       |     yes      |
|      MatrixDiagPart      |     yes      |      -       |     yes      |

## Stochasticity
Count 1/10

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Dropout          |     yes      |      -       |     yes      |
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
|      BinarySigmoid       |     yes      |      -       |     yes      |
|        BinaryTanh        |     yes      |      -       |     yes      |
|   BinaryConnectAffine    |     yes      |      -       |      -       |
| BinaryConnectConvolution |     yes      |      -       |      -       |
|    BinaryWeightAffine    |     yes      |      -       |      -       |
| BinaryWeightConvolution  |     yes      |      -       |      -       |
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

