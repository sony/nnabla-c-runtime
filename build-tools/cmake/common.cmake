#-------------------------------------------------------------------------------
# CMake Settings.
#-------------------------------------------------------------------------------
cmake_policy(SET CMP0002 OLD)
set(CMAKE_INSTALL_PREFIX ${project_root}/dist)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

#-------------------------------------------------------------------------------
# Compiler Settings.
#-------------------------------------------------------------------------------

if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
  if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g -O4 -D__STDC_CONSTANT_MACROS")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")  ## Strip binary
  elseif(MSVC)
  endif()
else()
  include(${CMAKE_TOOLCHAIN_FILE})
endif()
