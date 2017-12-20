cmake_minimum_required(VERSION 2.8)
project(nnablart)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_executable(nnablart
  main.c
  dump.c
  dump_function.c)

link_libraries(nnablart_functions)
link_libraries(nnablart_runtime)
