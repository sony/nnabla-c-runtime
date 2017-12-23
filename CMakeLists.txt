cmake_minimum_required(VERSION 2.8)

set(project_root "${CMAKE_CURRENT_SOURCE_DIR}")
include(${project_root}/build-tools/cmake/common.cmake)

project(nnablart)

add_subdirectory(src/runtime)
add_subdirectory(src/functions)
add_subdirectory(src/nnablart)
