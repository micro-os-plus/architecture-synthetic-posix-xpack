/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2015 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__)

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_INCLUDE_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // MICRO_OS_PLUS_INCLUDE_CONFIG_H

#if defined(MICRO_OS_PLUS_TRACE)

// ----------------------------------------------------------------------------

#include <micro-os-plus/diag/trace.h>
#include <cstddef>
#include <unistd.h>

// ----------------------------------------------------------------------------

namespace micro_os_plus
{
  namespace trace
  {
    // ------------------------------------------------------------------------

    void
    initialize (void)
    {
      // For POSIX no inits are required, STDOUT & STDERR are always available.
    }

    // ------------------------------------------------------------------------

    ssize_t
    write (const void* buf, std::size_t nbyte)
    {
#if defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT)
      return ::write (1, buf, nbyte); // Forward to STDOUT.
#elif defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR)
      return ::write (2, buf, nbyte); // Forward to STDERR.
#else
#warning "No trace output channel."
      buf = buf;
      return nbyte;
#endif
    }

    void
    flush (void)
    {
#if defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDOUT)
      fsync (1); // Sync STDOUT.
#elif defined(MICRO_OS_PLUS_USE_TRACE_POSIX_STDERR)
      fsync (2); // Sync STDERR.
#else
      ;
#endif
    }

    // ------------------------------------------------------------------------
  } // namespace trace
} // namespace micro_os_plus

#endif // defined(MICRO_OS_PLUS_TRACE)

// ----------------------------------------------------------------------------

#endif // Unix

// ----------------------------------------------------------------------------
