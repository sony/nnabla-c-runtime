cmake_minimum_required(VERSION 2.8)
project(nnablart_functions)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(nnablart_functions STATIC
  # Utilities
  utilities/accessor.c
  utilities/list.c
  utilities/shape.c
  utilities/vector.c

  # Functions
  implements/neural_network/affine/affine.c
  implements/neural_network/affine/affine_generic.c
  implements/neural_network/affine/affine_float.c
  implements/activation/sigmoid.c
  implements/unimplemented.c)
