/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2017 Liviu Ionescu.
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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_POSIX_INSTRUCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_POSIX_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

/*
 * Inline implementations for the POSIX architecture instructions.
 */

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) void
  posix_arch_nop (void)
  {
    ;
  }

  static inline __attribute__ ((always_inline)) void
  posix_arch_bkpt (void)
  {
    ;
  }

  static inline __attribute__ ((always_inline)) void
  posix_arch_wfi (void)
  {
    ;
  }

  static inline __attribute__ ((always_inline)) void
  os_arch_nop (void)
  {
    posix_arch_nop ();
  }

  /**
   * `break` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  os_arch_brk (void)
  {
    posix_arch_bkpt ();
  }

  /**
   * `wfi` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  os_arch_wfi (void)
  {
    posix_arch_wfi ();
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace posix
{
  namespace arch
  {
    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) void
    nop (void)
    {
      posix_arch_nop ();
    }

    inline __attribute__ ((always_inline)) void
    bkpt (void)
    {
      posix_arch_bkpt ();
    }

    inline __attribute__ ((always_inline)) void
    wfi (void)
    {
      posix_arch_wfi ();
    }

    // ------------------------------------------------------------------------
  } // namespace arch
} // namespace posix

namespace micro_os_plus
{
  namespace arch
  {
    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) void
    nop (void)
    {
      posix::arch::nop ();
    }

    inline __attribute__ ((always_inline)) void
    brk (void)
    {
      posix::arch::bkpt ();
    }

    inline __attribute__ ((always_inline)) void
    wfi (void)
    {
      posix::arch::wfi ();
    }

    // ------------------------------------------------------------------------
  } // namespace arch
} // namespace micro_os_plus

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_POSIX_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
