/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2015-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/mit.
 */

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__) \
    || defined(__MINGW32__)

// ----------------------------------------------------------------------------

#if __has_include(<micro-os-plus/project-config.h>)
#include <micro-os-plus/project-config.h>
#elif __has_include(<micro-os-plus/config.h>)
#pragma message "micro-os-plus/config.h is deprecated, rename to micro-os-plus/project-config.h and include it instead of micro-os-plus/config.h"
#include <micro-os-plus/config.h>
#endif // __has_include(<micro-os-plus/project-config.h>)

#if defined(MICRO_OS_PLUS_TRACE)
#if defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT) \
    || defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR)

// ----------------------------------------------------------------------------

// Borrowed from architecture-synthetic-posix.
// TODO: get it via dependencies.

#include <micro-os-plus/diag/trace.h>
#include <cstddef>
#include <unistd.h>
#include <cstring>

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wpre-c++17-compat"
#endif

namespace micro_os_plus::trace
{
  // --------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
  void __attribute__ ((constructor))
  initialize (void)
  {
    static const char msg[] = "micro_os_plus::trace::initialize()\n";
    write (msg, sizeof (msg) - 1);
    // STDOUT & STDERR are always available in POSIX; no inits are required.
  }
#pragma GCC diagnostic pop

  // --------------------------------------------------------------------------

  ssize_t
  write (const void* buf, std::size_t nbyte)
  {
#pragma GCC diagnostic push

#if defined(__MINGW32__)
// warning: conversion from 'std::size_t' {aka 'long long unsigned int'} to
// 'unsigned int' may change value [-Wconversion]
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#if defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT)
    return ::write (1, buf, nbyte); // Forward to STDOUT.
#elif defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR)
    return ::write (2, buf, nbyte); // Forward to STDERR.
#else
#warning "No trace output channel."
    buf = buf;
    return nbyte;
#endif

#pragma GCC diagnostic pop
  }

  void
  flush (void)
  {
#if !defined(__MINGW32__)
#if defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT)
    fsync (1); // Sync STDOUT.
#elif defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR)
    fsync (2); // Sync STDERR.
#else
    // Nothing.
#endif
#else
// error: 'fsync' was not declared in this scope
#endif
  }

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::trace

#pragma GCC diagnostic pop

#else
#error \
    "No trace output channel. Define either MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT or MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR."
#endif // defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STD*)
#endif // defined(MICRO_OS_PLUS_TRACE)

// ----------------------------------------------------------------------------

#endif // Unix || mingw32

// ----------------------------------------------------------------------------
