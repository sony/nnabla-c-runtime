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

Total 42/121


## Neural Network Layer
Count 6/11

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|          Affine          |     yes      |     yes      |     yes      |
|       Convolution        |     yes      |      -       |     yes      |
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
|         Sigmoid          |     yes      |      -       |      -       |
|          Swish           |     yes      |      -       |      -       |
|           Tanh           |     yes      |      -       |      -       |
|           ReLU           |     yes      |      -       |      -       |
|        LeakyReLU         |     yes      |      -       |      -       |
|         Softmax          |     yes      |      -       |      -       |
|           ELU            |     yes      |      -       |      -       |
|           SELU           |     yes      |      -       |      -       |
|          CReLU           |     yes      |      -       |      -       |
|           CELU           |     yes      |      -       |      -       |
|          PReLU           |     yes      |      -       |      -       |

## Normalization
Count 2/2

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|    BatchNormalization    |     yes      |      -       |      -       |
|     MeanSubtraction      |     yes      |      -       |      -       |

## Reduction
Count 0/7

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Sum            |      no      |      -       |      -       |
|           Mean           |      no      |      -       |      -       |
|           Max            |      no      |      -       |      -       |
|           Min            |      no      |      -       |      -       |
|           Prod           |      no      |      -       |      -       |
|        ReduceSum         |      no      |      -       |      -       |
|        ReduceMean        |      no      |      -       |      -       |

## Arithmetic
Count 10/12

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Add2           |      no      |      -       |      -       |
|          BcAdd2          |      no      |      -       |      -       |
|           Sub2           |     yes      |      -       |      -       |
|           Mul2           |     yes      |      -       |      -       |
|           Div2           |     yes      |      -       |      -       |
|           Pow2           |     yes      |      -       |      -       |
|        AddScalar         |     yes      |      -       |      -       |
|        MulScalar         |     yes      |      -       |      -       |
|        PowScalar         |     yes      |      -       |      -       |
|        RSubScalar        |     yes      |      -       |      -       |
|        RDivScalar        |     yes      |      -       |      -       |
|        RPowScalar        |     yes      |      -       |      -       |

## Logical
Count 4/24

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|           Sign           |      no      |      -       |      -       |
|         Minimum2         |     yes      |      -       |      -       |
|         Maximum2         |     yes      |      -       |      -       |
|      MinimumScalar       |     yes      |      -       |      -       |
|      MaximumScalar       |     yes      |      -       |      -       |
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
Count 5/7

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Constant         |      no      |      -       |      -       |
|           Abs            |     yes      |      -       |      -       |
|           Exp            |     yes      |      -       |      -       |
|           Log            |     yes      |      -       |      -       |
|         Identity         |     yes      |      -       |      -       |
|       BatchMatmul        |      no      |      -       |      -       |
|          Round           |     yes      |      -       |      -       |

## Array Manipulation
Count 1/12

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|       Concatenate        |      no      |      -       |      -       |
|          Split           |      no      |      -       |      -       |
|          Stack           |      no      |      -       |      -       |
|          Slice           |      no      |      -       |      -       |
|        Transpose         |      no      |      -       |      -       |
|        Broadcast         |      no      |      -       |      -       |
|          OneHot          |      no      |      -       |      -       |
|           Flip           |      no      |      -       |      -       |
|          Shift           |      no      |      -       |      -       |
|         Reshape          |     yes      |      -       |      -       |
|        MatrixDiag        |      no      |      -       |      -       |
|      MatrixDiagPart      |      no      |      -       |      -       |

## Stochasticity
Count 0/10

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         Dropout          |      no      |      -       |      -       |
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
Count 3/10

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|      BinarySigmoid       |     yes      |      -       |      -       |
|        BinaryTanh        |     yes      |      -       |      -       |
|   BinaryConnectAffine    |     yes      |      -       |      -       |
| BinaryConnectConvolution |      no      |      -       |      -       |
|    BinaryWeightAffine    |      no      |      -       |      -       |
| BinaryWeightConvolution  |      no      |      -       |      -       |
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
Count 0/3

|         Function         |  Available   |    float     |   generic    |
|--------------------------|--------------|--------------|--------------|
|         VATNoise         |      no      |      -       |      -       |
|          Unlink          |      no      |      -       |      -       |
|           Sink           |      no      |      -       |      -       |

