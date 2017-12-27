cmake_minimum_required(VERSION 2.8)

set(project_root "${CMAKE_CURRENT_SOURCE_DIR}/../..")
include(${project_root}/build-tools/cmake/common.cmake)

project(nnablart)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

link_libraries(nnablart_runtime)
link_libraries(nnablart_functions)
if(NOT MSVC)
  link_libraries(m)
endif()

add_executable(nnablart
  main.c

  infer.c

  dump.c
  dump_function.c)

