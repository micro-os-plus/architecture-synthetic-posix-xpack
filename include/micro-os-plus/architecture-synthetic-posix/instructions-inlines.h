/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
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
  posix_architecture_nop (void)
  {
  }

  static inline __attribute__ ((always_inline)) void
  posix_architecture_bkpt (void)
  {
  }

  static inline __attribute__ ((always_inline)) void
  posix_architecture_wfi (void)
  {
  }

  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_nop (void)
  {
    posix_architecture_nop ();
  }

  /**
   * `break` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_brk (void)
  {
    posix_architecture_bkpt ();
  }

  /**
   * `wfi` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_wfi (void)
  {
    posix_architecture_wfi ();
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace posix
{
  namespace architecture
  {
    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) void
    nop (void)
    {
      posix_architecture_nop ();
    }

    inline __attribute__ ((always_inline)) void
    bkpt (void)
    {
      posix_architecture_bkpt ();
    }

    inline __attribute__ ((always_inline)) void
    wfi (void)
    {
      posix_architecture_wfi ();
    }

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace posix

// ----------------------------------------------------------------------------

namespace micro_os_plus
{
  namespace architecture
  {
    // ------------------------------------------------------------------------

    inline __attribute__ ((always_inline)) void
    nop (void)
    {
      posix::architecture::nop ();
    }

    inline __attribute__ ((always_inline)) void
    brk (void)
    {
      posix::architecture::bkpt ();
    }

    inline __attribute__ ((always_inline)) void
    wfi (void)
    {
      posix::architecture::wfi ();
    }

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace micro_os_plus

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_POSIX_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
