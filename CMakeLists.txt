#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# Permission to use, copy, modify, and/or distribute this software
# for any purpose is hereby granted, under the terms of the MIT license.
#
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# https://cmake.org/cmake/help/v3.20/
cmake_minimum_required(VERSION 3.20)

project(micro-os-plus-architecture-synthetic-posix
  DESCRIPTION "µOS++ architecture-synthetic-posix"
)

if(COMMAND xpack_get_package_name_and_version)
  xpack_get_package_name_and_version("${CMAKE_CURRENT_SOURCE_DIR}/package.json")
  message(VERBOSE "Processing xPack ${PACKAGE_JSON_NAME}@${PACKAGE_JSON_VERSION}...")
endif()

# -----------------------------------------------------------------------------
# Local dependencies.

if(MICRO_OS_PLUS_INCLUDE_RTOS)
include("${CMAKE_CURRENT_LIST_DIR}/../rtos-port/meta/config.cmake")
endif()

# -----------------------------------------------------------------------------
## The project library definitions ##

add_library(micro-os-plus-architecture-synthetic-posix-interface INTERFACE EXCLUDE_FROM_ALL)

# -----------------------------------------------------------------------------
# Target settings.

target_include_directories(micro-os-plus-architecture-synthetic-posix-interface INTERFACE
  "include"
)

target_sources(micro-os-plus-architecture-synthetic-posix-interface INTERFACE
  "src/diag/trace-posix.cpp"
)

target_compile_definitions(micro-os-plus-architecture-synthetic-posix-interface INTERFACE
  # None.
)

target_compile_options(micro-os-plus-architecture-synthetic-posix-interface INTERFACE
  # None.
)

target_link_libraries(micro-os-plus-architecture-synthetic-posix-interface INTERFACE
  # None.
)

if (COMMAND xpack_display_target_lists)
  xpack_display_target_lists(micro-os-plus-architecture-synthetic-posix-interface)
endif()

# -----------------------------------------------------------------------------
# Aliases.

# https://cmake.org/cmake/help/v3.20/command/add_library.html#alias-libraries
add_library(micro-os-plus::architecture-synthetic-posix ALIAS micro-os-plus-architecture-synthetic-posix-interface)
message(STATUS "=> micro-os-plus::architecture-synthetic-posix")
add_library(micro-os-plus::architecture ALIAS micro-os-plus-architecture-synthetic-posix-interface)
message(STATUS "=> micro-os-plus::architecture")

# -----------------------------------------------------------------------------
