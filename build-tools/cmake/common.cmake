# Copyright (c) 2017 Sony Corporation. All Rights Reserved.
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

#-------------------------------------------------------------------------------
# CMake Settings.
#-------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX ${project_root}/dist)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

#-------------------------------------------------------------------------------
# Compiler Settings.
#-------------------------------------------------------------------------------

set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})

if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
  if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g -O4 -D__STDC_CONSTANT_MACROS -std=c99 -fPIE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")  ## Strip binary
  elseif(MSVC)
  endif()
else()
  include(${CMAKE_TOOLCHAIN_FILE})
endif()
