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

// Compile the trace channel only when the `diag-trace` package is
// available.
#if __has_include("micro-os-plus/diag/trace.h")

// ----------------------------------------------------------------------------

#include "micro-os-plus/diag/trace.h"

#include <atomic>
#include <cstddef>
#include <cstdio>
#include <cstring>

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_DIAG_TRACE_ENABLED)

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED) \
    && defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)
#error "Define only one MICRO_OS_PLUS_DIAG_TRACE_POSIX_*_ENABLED channel."
#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED)
// && defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)

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

    // The standard streams are set up by the C library before any
    // constructor runs, so no other initialisation is required.

    static const char msg[] = "micro_os_plus::trace::initialise()\n";
    write (msg, sizeof (msg) - 1);
  }

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__)

  // --------------------------------------------------------------------------

  /**
   * @brief Write the bytes to the trace stream and flush it.
   *
   * @param buf Pointer to the bytes to write.
   * @param nbyte The number of bytes to write.
   * @return The number of bytes written, or -1 if nothing could be
   * written because of an error.
   *
   * @details
   * The output goes through the standard I/O library, not directly to the
   * file descriptor, so that it is correctly interleaved with the
   * application output produced by `printf()`, `fprintf(stdout, ...)`, or
   * `std::cout` (which is synchronised with `stdout` by default), even
   * when the output is redirected to a file or a pipe, where `stdout` is
   * fully buffered.
   *
   * - With the STDOUT channel, the trace shares the `stdout` buffer with
   *   the application, so the order is preserved by construction; the
   *   buffer is flushed after each write, so that trace messages are not
   *   lost if the process crashes or is stopped by a debugger.
   * - With the STDERR channel, `stdout` is flushed before writing, so
   *   that when both streams are merged (for example with `2>&1`) the
   *   application output produced before the trace message precedes it;
   *   `stderr` is unbuffered.
   *
   * The standard I/O functions are not async-signal-safe; calling the
   * trace from a signal handler (for example from code run by the µOS++
   * clock tick handler) while the interrupted code is inside a standard
   * I/O call on the same stream may corrupt the stream buffer.
   *
   * Blocking the signals with `sigprocmask()` around the output was
   * considered and deliberately not implemented, for the following
   * reasons:
   * - the risk is low: the trace calls in the µOS++ tick handler path are
   *   compiled only when specific debug definitions are present, and even
   *   then the handler traces only rarely;
   * - the cost is paid by every message: the pair of system calls adds
   *   about 1 µs per message (measured on macOS);
   * - while the signals are blocked, the clock tick is deferred; if the
   *   output blocks (a stalled pipe or a paused terminal) for longer than
   *   a tick period, pending ticks are merged and lost, and the µOS++
   *   clock falls behind real time;
   * - it would protect only trace messages, not the application's own
   *   `printf()` calls interrupted by a handler that traces.
   */
  ssize_t
  implementation::write (const void* buf, std::size_t nbyte) noexcept
  {
    if (!is_initialised.test ())
      {
        initialise ();
      }

#if defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED)
    std::FILE* const stream = stdout;
#elif defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED)
    std::FILE* const stream = stderr;
    // Emit the pending application output first.
    std::fflush (stdout);
#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED)

    const std::size_t count = std::fwrite (buf, 1, nbyte, stream);
    std::fflush (stream);

    if (count == 0 && nbyte != 0)
      {
        return -1;
      }
    return static_cast<ssize_t> (count);
  }

  /**
   * @brief Flush the standard output streams.
   *
   * @details
   * Since `write()` already flushes after each message, this only
   * matters for application output still pending in the `stdout` buffer;
   * both `stdout` and `stderr` are flushed, regardless of the selected
   * channel.
   */
  void
  implementation::flush (void) noexcept
  {
    if (!is_initialised.test ())
      {
        initialise ();
      }

    std::fflush (stdout);
    std::fflush (stderr);
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

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_DIAG_TRACE_ENABLED)

// ----------------------------------------------------------------------------

#endif // __has_include("micro-os-plus/diag/trace.h")

// ----------------------------------------------------------------------------

#endif // Unix || mingw32

// ----------------------------------------------------------------------------
