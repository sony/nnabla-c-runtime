# Copyright 2017,2018,2019,2020,2021 Sony Corporation.
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

project(nnablart_runtime)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(nnablart_runtime STATIC
  runtime.c
  runtime_internal.c

  function_context.c)


install(FILES ../../include/nnablart/network.h DESTINATION include/nnablart)
install(FILES ../../include/nnablart/runtime.h DESTINATION include/nnablart)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
