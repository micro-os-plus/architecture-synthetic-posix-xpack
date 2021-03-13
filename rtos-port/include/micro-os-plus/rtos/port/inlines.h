/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_INLINES_H_

// ----------------------------------------------------------------------------

/*
 * This file contains the scheduler implementation that uses
 * functions from the POSIX API (macOS and GNU/Linux).
 *
 * This file is included in all src/os-*.cpp files.
 */

#ifdef __cplusplus

// ----------------------------------------------------------------------------

#if defined(HAVE_MICRO_OS_PLUS_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // HAVE_MICRO_OS_PLUS_CONFIG_H

// ----------------------------------------------------------------------------

#include <micro-os-plus/rtos/declarations-c.h>

#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/time.h>

// For Linux
#include <unistd.h>

#include <micro-os-plus/diag/trace.h>

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wc++98-compat"
#endif
#pragma GCC diagnostic ignored "-Wunused-parameter"

extern "C" uint32_t signal_nesting;

namespace micro_os_plus
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace scheduler
      {

        inline __attribute__ ((always_inline)) void
        greeting (void)
        {
          utsname name;
          if (::uname (&name) != -1)
            {
              trace::printf ("Synthetic POSIX, running on %s %s %s",
                             name.machine, name.sysname, name.release);
            }
          else
            {
              trace::printf ("Synthetic POSIX");
            }

          trace::puts ("; non-preemptive.");
        }

        inline __attribute__ ((always_inline)) port::scheduler::state_t
        lock (void)
        {
          return locked (state::locked);
        }

        inline __attribute__ ((always_inline)) port::scheduler::state_t
        unlock (void)
        {
          return locked (state::unlocked);
        }

        inline __attribute__ ((always_inline)) bool
        locked (void)
        {
          return lock_state != state::unlocked;
        }

        inline __attribute__ ((always_inline)) void
        wait_for_interrupt (void)
        {
#if defined(MICRO_OS_PLUS_TRACE_RTMICRO_OS_PLUS_THREAD_CONTEXT)
          trace::printf ("%s() \n", __func__);
#endif
          pause ();
        }

      } // namespace scheduler

      namespace interrupts
      {

        inline __attribute__ ((always_inline)) bool
        in_handler_mode (void)
        {
          return (signal_nesting > 0);
        }

        inline __attribute__ ((always_inline)) bool
        is_priority_valid (void)
        {
          return true;
        }

        // Enter an IRQ critical section
        inline __attribute__ ((always_inline)) rtos::interrupts::state_t
        critical_section::enter (void)
        {
          sigset_t old;
          sigprocmask (SIG_BLOCK, &clock_set, &old);

          return sigismember (&old, clock::signal_number);
        }

        // Exit an IRQ critical section
        inline __attribute__ ((always_inline)) void
        critical_section::exit (rtos::interrupts::state_t state)
        {
          sigprocmask (state ? SIG_BLOCK : SIG_UNBLOCK, &clock_set, nullptr);
        }

        // ====================================================================

        // Enter an IRQ uncritical section
        inline __attribute__ ((always_inline)) rtos::interrupts::state_t
        uncritical_section::enter (void)
        {
          sigset_t old;
          sigprocmask (SIG_UNBLOCK, &clock_set, &old);

          return sigismember (&old, clock::signal_number);
        }

        // Exit an IRQ critical section
        inline __attribute__ ((always_inline)) void
        uncritical_section::exit (rtos::interrupts::state_t state)
        {
          sigprocmask (state ? SIG_BLOCK : SIG_UNBLOCK, &clock_set, nullptr);
        }

      } // namespace interrupts

      // ======================================================================

      namespace this_thread
      {
        inline __attribute__ ((always_inline)) void
        prepare_suspend (void)
        {
          ;
        }

      } // namespace this_thread

      // ======================================================================
    } // namespace port
  } // namespace rtos
} // namespace micro_os_plus

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#endif // __cplusplus

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_INLINES_H_

// ----------------------------------------------------------------------------
