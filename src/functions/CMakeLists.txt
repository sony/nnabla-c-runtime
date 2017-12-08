cmake_minimum_required(VERSION 2.8)
project(nnablart_functions)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(nnablart_functions STATIC
  # Utilities
  utilities.c
  vector.c

  # Functions
  implements/affine.c
  implements/unimplemented.c)
