cmake_minimum_required(VERSION 2.8)

set(project_root "${CMAKE_CURRENT_SOURCE_DIR}/../..")
include(${project_root}/build-tools/cmake/common.cmake)

project(nnablart_functions)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(nnablart_functions STATIC
  # Utilities
  utilities/accessor.c
  utilities/list.c
  utilities/shape.c
  utilities/vector.c
  utilities/pooling.c
  utilities/arithmetic.c

  # Functions
  implements/neural_network/affine/affine.c
  implements/neural_network/affine/affine_generic.c
  implements/neural_network/affine/affine_float.c
  implements/neural_network/max_pooling.c
  implements/neural_network/sum_pooling.c
  implements/neural_network/average_pooling.c
  implements/activation/sigmoid.c
  implements/activation/tanh.c
  implements/activation/softmax.c
  implements/quantization/binary_tanh.c
  implements/activation/prelu.c
  implements/math/abs.c
  implements/arithmetic/add_scalar.c
  implements/math/identity.c
  implements/quantization/binary_sigmoid.c
  implements/quantization/binary_connect_affine.c
  implements/arithmetic/mul_scalar.c
  implements/arithmetic/r_sub_scalar.c
  implements/arithmetic/r_div_scalar.c
  implements/arithmetic/pow_scalar.c
  implements/arithmetic/r_pow_scalar.c
  implements/logical/maximum_scalar.c
  implements/logical/minimum_scalar.c
  implements/array/reshape.c
  implements/normalization/batch_normalization.c
  implements/unimplemented.c)
