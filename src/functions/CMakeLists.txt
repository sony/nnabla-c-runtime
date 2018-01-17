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

  # Functions
  implements/neural_network/affine.c
  implements/activation/sigmoid.c
  implements/unimplemented.c)
