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

# https://cmake.org/cmake/help/v3.18/
# https://cmake.org/cmake/help/v3.18/manual/cmake-packages.7.html#package-configuration-file

if(micro-os-plus-architecture-synthetic-posix-included)
  return()
endif()

set(micro-os-plus-architecture-synthetic-posix-included TRUE)

message(STATUS "Including micro-os-plus-architecture-synthetic-posix...")

# -----------------------------------------------------------------------------
# The current folder.

get_filename_component(xpack_current_folder ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# -----------------------------------------------------------------------------

if(NOT TARGET micro-os-plus-architecture-synthetic-posix-interface)

  add_library(micro-os-plus-architecture-synthetic-posix-interface INTERFACE EXCLUDE_FROM_ALL)

  # ---------------------------------------------------------------------------
  # Target settings.

  file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "${xpack_current_folder}/src/*.c*")

  target_sources(
    micro-os-plus-architecture-synthetic-posix-interface

    INTERFACE
      ${source_files}
  )

  target_include_directories(
    micro-os-plus-architecture-synthetic-posix-interface

    INTERFACE
      ${xpack_current_folder}/include
  )

  target_compile_definitions(
    micro-os-plus-architecture-synthetic-posix-interface

    INTERFACE
      _XOPEN_SOURCE=700L
      $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT>
  )

  # ---------------------------------------------------------------------------
  # Aliases.

  add_library(micro-os-plus::architecture-synthetic-posix ALIAS micro-os-plus-architecture-synthetic-posix-interface)
  message(STATUS "micro-os-plus::architecture-synthetic-posix")
  add_library(micro-os-plus::architecture ALIAS micro-os-plus-architecture-synthetic-posix-interface)
  message(STATUS "micro-os-plus::architecture")

endif()

# -----------------------------------------------------------------------------
