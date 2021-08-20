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

set(project_root "${CMAKE_CURRENT_SOURCE_DIR}")
include(${project_root}/build-tools/cmake/common.cmake)

project(nnabla-c-runtime)

file(STRINGS ${project_root}/VERSION.txt versions NEWLINE_CONSUME)
string(REGEX REPLACE [[^.*C_RUNTIME_VERSION: ([A-z0-9.\-_]+).*$]] [[\1]] c_runtime_version ${versions})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\1]] c_runtime_version_major ${c_runtime_version})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\2]] c_runtime_version_minor ${c_runtime_version})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\3]] c_runtime_version_patch ${c_runtime_version})
string(REGEX REPLACE [[^.*NNB_VERSION: ([0-9]+).*$]] [[\1]] nnb_version ${versions})

add_subdirectory(src/runtime)
add_subdirectory(src/functions)
add_subdirectory(src/nnablart)

set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Sony")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Neural Network Libraries C runtime.")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "nnabla@googlegroups.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${c_runtime_version_major})
set(CPACK_PACKAGE_VERSION_MINOR ${c_runtime_version_minor})
set(CPACK_PACKAGE_VERSION_PATCH ${c_runtime_version_patch})

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${PROJECT_NAME}-Source-${CPACK_PACKAGE_VERSION})

install(FILES PACKAGE_README.md DESTINATION . RENAME README.md)
install(FILES doc/SUPPORT_STATUS.md DESTINATION doc)

include(CPack)
