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

#include "micro-os-plus/diag/trace.h"

#include <atomic>
#include <cstddef>
#include <unistd.h>
#include <cstring>

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_DIAG_TRACE_ENABLED)

#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED) \
    || defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)

// ----------------------------------------------------------------------------

#if defined(__GNUC__)
#pragma GCC diagnostic push

#if defined(__clang__)
// #pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wpre-c++17-compat"
#endif // defined(__clang__)
#endif // defined(__GNUC__)

namespace micro_os_plus::trace::detail
{
  // --------------------------------------------------------------------------

  namespace
  {
    /**
     * @brief Flag set once the trace channel has been initialised.
     *
     * @details
     * It is set by the first call to `implementation::initialise()`, and
     * tested by `write()` and `flush()`, which perform the initialisation
     * themselves if it has not yet run. This covers static constructors
     * that use the trace before the initialisation constructor, which may
     * happen on platforms that ignore the constructor priority (macOS),
     * and makes repeated explicit calls to `initialise()` harmless.
     *
     * `std::atomic_flag` is used because it is the only atomic type
     * guaranteed to be lock-free, and therefore safe to access from
     * signal handlers, and because in C++20 it is constant-initialised
     * to the clear state, before any static constructor runs.
     */
    std::atomic_flag is_initialised;
  } // namespace

  // --------------------------------------------------------------------------

#if defined(__GNUC__)
#pragma GCC diagnostic push

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wglobal-constructors"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wattributes"
#endif // defined(__clang__)
#endif // defined(__GNUC__)

  // On POSIX the startup code is part of the system library, so the
  // initialisation runs as a constructor, before main(). Priority 101 is
  // the earliest available to user code (0-100 are reserved); it is
  // honoured across files on ELF platforms, but ignored on macOS, where
  // the link order decides. Subsequent calls do nothing.
  void __attribute__ ((constructor (101)))
  implementation::initialise (void) noexcept
  {
    // Set the flag before writing, since write() tests it.
    if (is_initialised.test_and_set ())
      {
        return; // Already initialised.
      }

    static const char msg[] = "micro_os_plus::trace::initialise()\n";
    write (msg, sizeof (msg) - 1);
    // STDOUT & STDERR are always available in POSIX; no inits are required.
  }

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__)

  // --------------------------------------------------------------------------

  ssize_t
  implementation::write (const void* buf, std::size_t nbyte) noexcept
  {
    if (!is_initialised.test ())
      {
        initialise ();
      }

#if defined(__GNUC__)
#pragma GCC diagnostic push

#if defined(__MINGW32__)
// warning: conversion from 'std::size_t' {aka 'long long unsigned int'} to
// 'unsigned int' may change value [-Wconversion]
#pragma GCC diagnostic ignored "-Wconversion"
#endif // defined(__MINGW32__)
#endif // defined(__GNUC__)

#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED)
    return ::write (1, buf, nbyte); // Forward to STDOUT.
#elif defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)
    return ::write (2, buf, nbyte); // Forward to STDERR.
#else
#warning "No trace output channel."
    buf = buf;
    return nbyte;
#endif

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__)
  }

  void
  implementation::flush (void) noexcept
  {
    if (!is_initialised.test ())
      {
        initialise ();
      }

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

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__)

#else
#error \
    "No trace output channel. Define either MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED or MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED."
#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STD*)

#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_ENABLED)

// ----------------------------------------------------------------------------

#endif // Unix || mingw32

// ----------------------------------------------------------------------------
