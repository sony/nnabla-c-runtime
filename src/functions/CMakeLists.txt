cmake_minimum_required(VERSION 2.8)

set(project_root "${CMAKE_CURRENT_SOURCE_DIR}/../..")
include(${project_root}/build-tools/cmake/common.cmake)

project(nnablart_functions)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(nnablart_functions STATIC
  # Utilities
  utilities/accessor.c
  utilities/fixedpoint.c
  utilities/list.c
  utilities/shape.c

  # Functions
  implements/neural_network/pooling.c
  implements/neural_network/affine/affine.c
  implements/neural_network/affine/affine_fixed8.c
  implements/neural_network/affine/affine_fixed16.c
  implements/neural_network/affine/affine_generic.c
  implements/neural_network/max_pooling.c
  implements/neural_network/sum_pooling.c
  implements/neural_network/average_pooling.c
  implements/neural_network/unpooling.c
  implements/neural_network/convolution/convolution.c
  implements/neural_network/convolution/convolution_generic.c
  implements/neural_network/convolution/convolution_float.c
  implements/neural_network/convolution/convolution_int8.c
  implements/neural_network/convolution/convolution_int16.c
  implements/neural_network/convolution/convolution_common.c
  implements/neural_network/convolution/binary_connect_convolution.c
  implements/neural_network/convolution/binary_weight_convolution.c
  implements/neural_network/convolution/depthwise_convolution.c
  implements/neural_network/deconvolution.c

  implements/activation/sigmoid.c
  implements/activation/relu.c
  implements/activation/tanh.c
  implements/activation/softmax.c
  implements/activation/selu.c
  implements/activation/elu.c
  implements/activation/prelu.c
  implements/activation/leakyrelu.c
  implements/activation/elu.c
  implements/activation/selu.c
  implements/activation/crelu.c
  implements/activation/celu.c
  implements/activation/swish.c

  implements/math/abs.c
  implements/math/batch_matmul.c
  implements/math/exp.c
  implements/math/identity.c
  implements/math/log.c
  implements/math/round.c

  implements/quantization/binary_tanh.c
  implements/quantization/binary_sigmoid.c
  implements/quantization/binary_connect_affine.c
  implements/quantization/binary_weight_affine.c

  implements/arithmetic/add_scalar.c
  implements/arithmetic/arithmetic.c
  implements/arithmetic/arithmetic_fixed.c
  implements/arithmetic/arithmetic_generic.c
  implements/arithmetic/div2.c
  implements/arithmetic/mul2.c
  implements/arithmetic/mul_scalar.c
  implements/arithmetic/pow2.c
  implements/arithmetic/pow_scalar.c
  implements/arithmetic/r_div_scalar.c
  implements/arithmetic/r_pow_scalar.c
  implements/arithmetic/r_sub_scalar.c
  implements/arithmetic/sub2.c
  implements/arithmetic/add2.c
  
  implements/logical/maximum_scalar.c
  implements/logical/minimum_scalar.c
  implements/logical/maximum2.c
  implements/logical/minimum2.c  
  implements/logical/sign.c

  implements/array/matrix_diag.c
  implements/array/matrix_diag_part.c
  implements/array/reshape.c
  implements/array/concatenate.c
  implements/array/split.c
  implements/array/stack.c
  implements/array/shift.c
  implements/array/slice.c
  implements/array/flip.c
  implements/array/transpose.c
  implements/array/pad.c

  implements/normalization/batch_normalization.c
  implements/normalization/mean_subtraction.c

  implements/stochasticity/dropout.c
  implements/reduction/sum.c
  
  implements/unimplemented.c)

install(FILES ../../include/nnablart/functions.h DESTINATION include/nnablart)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
