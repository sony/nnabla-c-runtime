cmake_minimum_required(VERSION 2.8)
project(nnablart)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

link_libraries(nnablart_functions)
link_libraries(nnablart_runtime)

add_executable(nnablart
  main.c
  infer.c
  dump.c
  dump_function.c)

