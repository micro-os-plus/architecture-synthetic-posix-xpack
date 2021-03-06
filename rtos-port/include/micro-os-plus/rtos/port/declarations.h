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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_DECLS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_DECLS_H_

// ----------------------------------------------------------------------------

/*
 * This file is included in `micro-os-plus/rtos.h` to customise
 * it with POSIX specific declarations.
 */

#if defined(HAVE_MICRO_OS_PLUS_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // HAVE_MICRO_OS_PLUS_CONFIG_H

// ----------------------------------------------------------------------------

#include <micro-os-plus/rtos/port/declarations-c.h>

// ----------------------------------------------------------------------------

#if !defined(MICRO_OS_PLUS_INTEGER_SYSTICK_FREQUENCY_HZ)
#define MICRO_OS_PLUS_INTEGER_SYSTICK_FREQUENCY_HZ (1000)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES)
#define MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES (SIGSTKSZ)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES)
#if defined(__linux__)
#define MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES (2 * SIGSTKSZ)
#else
#define MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES (SIGSTKSZ)
#endif // defined(__linux__)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES)
#define MICRO_OS_PLUS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES \
  (MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_IDLE_STACK_SIZE_BYTES)
#define MICRO_OS_PLUS_INTEGER_RTOS_IDLE_STACK_SIZE_BYTES \
  (MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES)
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus

// ----------------------------------------------------------------------------

#include <signal.h>
// Platform definitions
#include <sys/time.h>

#include <cstdint>
#include <cstddef>

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wc++98-compat"
#endif

namespace micro_os_plus
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace stack
      {
        // Assume 64-bits core.
        using element_t = micro_os_plus_port_thread_stack_element_t;

        // Align stack to 8 bytes.
        using allocation_element_t
            = micro_os_plus_port_thread_stack_allocation_element_t;

        // Initial value for the minimum stack size in bytes.
        constexpr std::size_t min_size_bytes
            = MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES;

        // Initial value for the default stack size in bytes.
        constexpr std::size_t default_size_bytes
            = MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES;

        constexpr element_t magic = 0xEFBEADDEEFBEADDE;
      } // namespace stack

      namespace interrupts
      {
        // True if signal blocked
        using state_t = micro_os_plus_port_interrupts_state_t;

        namespace state
        {
          constexpr state_t init = false;
        }

        extern sigset_t clock_set;

      } // namespace interrupts

      namespace scheduler
      {
        using state_t = micro_os_plus_port_scheduler_state_t;

        namespace state
        {
          constexpr state_t locked = true;
          constexpr state_t unlocked = false;
          constexpr state_t init = unlocked;
        } // namespace state

        extern state_t lock_state;

      } // namespace scheduler

      namespace clock
      {
        constexpr int signal_number = SIGALRM;
      }

      using thread_context_t = struct thread_context_s
      {
        // On POSIX, the context is saved on standard (although deprecated)
        // ucontext_t structures. It requires _XOPEN_SOURCE=700L to compile.
        ucontext_t ucontext; //
      };

      // ----------------------------------------------------------------------
    } // namespace port
  } // namespace rtos
} // namespace micro_os_plus

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#endif // __cplusplus

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_DECLS_H_

// ----------------------------------------------------------------------------
