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

  # Functions
  implements/neural_network/affine/affine.c
  implements/neural_network/affine/affine_generic.c
  implements/neural_network/affine/affine_float.c
  implements/neural_network/max_pooling.c
  implements/neural_network/sum_pooling.c
  implements/activation/sigmoid.c
  implements/activation/tanh.c
  implements/activation/softmax.c
  implements/math/abs.c
  implements/quantization/binary_sigmoid.c
  implements/unimplemented.c)
