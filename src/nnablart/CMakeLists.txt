# Copyright 2018,2019,2020,2021 Sony Corporation.
# Copyright 2021 Sony Group Corporation.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
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

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
