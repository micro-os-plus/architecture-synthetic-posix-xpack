/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2015-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__) \
    || defined(__MINGW32__)

// ----------------------------------------------------------------------------

// Borrowed from architecture-synthetic-posix.
// TODO: get it via dependencies.

#include <micro-os-plus/diag/trace.h>

#include <cstddef>
#include <unistd.h>
#include <cstring>

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_DIAG_TRACE_ENABLED)

#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED) \
    || defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
// #pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wpre-c++17-compat"
#endif

namespace micro_os_plus::trace::detail
{
  // --------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
  void __attribute__ ((constructor))
  implementation::initialise (void) noexcept
  {
    static const char msg[] = "micro_os_plus::trace::initialise()\n";
    write (msg, sizeof (msg) - 1);
    // STDOUT & STDERR are always available in POSIX; no inits are required.
  }
#pragma GCC diagnostic pop

  // --------------------------------------------------------------------------

  ssize_t
  implementation::write (const void* buf, std::size_t nbyte) noexcept
  {
#pragma GCC diagnostic push

#if defined(__MINGW32__)
// warning: conversion from 'std::size_t' {aka 'long long unsigned int'} to
// 'unsigned int' may change value [-Wconversion]
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED)
    return ::write (1, buf, nbyte); // Forward to STDOUT.
#elif defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)
    return ::write (2, buf, nbyte); // Forward to STDERR.
#else
#warning "No trace output channel."
    buf = buf;
    return nbyte;
#endif

#pragma GCC diagnostic pop
  }

  void
  implementation::flush (void) noexcept
  {
#if !defined(__MINGW32__)
#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED)
    fsync (1); // Sync STDOUT.
#elif defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)
    fsync (2); // Sync STDERR.
#else
    // Nothing.
#endif
#else
// error: 'fsync' was not declared in this scope
#endif
  }

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::trace::detail

#pragma GCC diagnostic pop

#else
#error #    "No trace output channel. Define either MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED or MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED."
#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STD*)

#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_ENABLED)

// ----------------------------------------------------------------------------

#endif // Unix || mingw32

// ----------------------------------------------------------------------------
