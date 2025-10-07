/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2015-2025 Liviu Ionescu. All rights reserved.
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

#if defined(MICRO_OS_PLUS_INCLUDE_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // MICRO_OS_PLUS_INCLUDE_CONFIG_H

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

namespace micro_os_plus::trace
{
  // --------------------------------------------------------------------------

  void __attribute__ ((constructor))
  initialize (void)
  {
    const char* msg = "micro_os_plus::trace::initialize()\n";
    write (msg, strlen (msg));
    // STDOUT & STDERR are always available in POSIX; no inits are required.
  }

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

#else
#error "No trace output channel. Define either MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT or MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR."
#endif // defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STD*)
#endif // defined(MICRO_OS_PLUS_TRACE)

// ----------------------------------------------------------------------------

#endif // Unix || mingw32

// ----------------------------------------------------------------------------
