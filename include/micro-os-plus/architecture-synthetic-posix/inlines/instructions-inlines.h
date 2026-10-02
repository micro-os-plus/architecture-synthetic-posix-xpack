/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2017-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INLINES_INSTRUCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INLINES_INSTRUCTIONS_INLINES_H_

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
  posix_architecture_data_barrier (void)
  {
    __atomic_thread_fence (__ATOMIC_SEQ_CST);
  }

  static inline __attribute__ ((always_inline)) void
  posix_architecture_instruction_barrier (void)
  {
    __asm__ volatile (""
                      : /* Outputs */
                      : /* Inputs */
                      : "memory" /* Clobbers */
    );
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

  /**
   * Data synchronisation barrier (atomic thread fence).
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_data_barrier (void)
  {
    posix_architecture_data_barrier ();
  }

  /**
   * Instruction synchronisation barrier (compiler barrier).
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_instruction_barrier (void)
  {
    posix_architecture_instruction_barrier ();
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

    inline __attribute__ ((always_inline)) void
    data_barrier (void)
    {
      posix_architecture_data_barrier ();
    }

    inline __attribute__ ((always_inline)) void
    instruction_barrier (void)
    {
      posix_architecture_instruction_barrier ();
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

    inline __attribute__ ((always_inline)) void
    data_barrier (void)
    {
      posix::architecture::data_barrier ();
    }

    inline __attribute__ ((always_inline)) void
    instruction_barrier (void)
    {
      posix::architecture::instruction_barrier ();
    }

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace micro_os_plus

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INLINES_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
