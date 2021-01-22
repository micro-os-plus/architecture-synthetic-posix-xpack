#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# This Source Code Form is subject to the terms of the MIT License.
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

message(STATUS "Including micro-os-plus-architecture-synthetic-posix...")

# -----------------------------------------------------------------------------

function(target_sources_micro_os_plus_architecture_synthetic_posix target)

  get_filename_component(xpack_root_folder ${CMAKE_CURRENT_FUNCTION_LIST_DIR} DIRECTORY)

  target_sources(
    ${target}

    PRIVATE
      ${xpack_root_folder}/src/diag/trace-posix.cpp
      ${xpack_root_folder}/src/rtos/os-core.cpp
  )

endfunction()

# -----------------------------------------------------------------------------

function(target_include_directories_micro_os_plus_architecture_synthetic_posix target)

  get_filename_component(xpack_root_folder ${CMAKE_CURRENT_FUNCTION_LIST_DIR} DIRECTORY)

  target_include_directories(
    ${target}

    PUBLIC
      ${xpack_root_folder}/include
  )

endfunction()

# -----------------------------------------------------------------------------

function(target_compile_definitions_micro_os_plus_architecture_synthetic_posix target)

  target_compile_definitions(
    ${target}

    PUBLIC
      _XOPEN_SOURCE=700L
      $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:OS_USE_TRACE_POSIX_STDOUT>
  )

endfunction()

# -----------------------------------------------------------------------------
