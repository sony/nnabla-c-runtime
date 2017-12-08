cmake_minimum_required(VERSION 2.8)
project(nnablart_runtime)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(nnablart_runtime STATIC
  runtime.c)



