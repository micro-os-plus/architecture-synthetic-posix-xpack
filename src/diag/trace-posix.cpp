/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2015 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#if defined(__APPLE__) || defined(__linux__) || defined(__unix__)

// ----------------------------------------------------------------------------

#if defined(TRACE)

// ----------------------------------------------------------------------------

#if defined(HAVE_MICRO_OS_PLUS_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // HAVE_MICRO_OS_PLUS_CONFIG_H

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

#endif // defined(TRACE)

// ----------------------------------------------------------------------------

#endif // Unix

// ----------------------------------------------------------------------------
