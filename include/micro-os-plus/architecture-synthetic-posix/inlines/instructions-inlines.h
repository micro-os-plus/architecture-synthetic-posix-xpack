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

// ----------------------------------------------------------------------------

/**
 * @file
 * @brief Inline definitions of the architecture instructions for the
 * synthetic POSIX platform.
 *
 * @details
 * The declarations and the user documentation are in `instructions.h`,
 * which includes this file at its end; the comments here describe only
 * the implementation. This file should not be included directly.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INLINES_INSTRUCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INLINES_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  /**
   * @brief No operation.
   *
   * @details
   * Implemented as an empty function, which the compiler removes
   * completely.
   */
  static inline __attribute__ ((always_inline)) void
  posix_architecture_nop (void)
  {
  }

  /**
   * @brief Breakpoint; does nothing on this platform.
   *
   * @details
   * Implemented as an empty function, which the compiler removes
   * completely; execution continues.
   */
  static inline __attribute__ ((always_inline)) void
  posix_architecture_bkpt (void)
  {
  }

  /**
   * @brief Wait for interrupt; does nothing on this platform.
   *
   * @details
   * Implemented as an empty function, which the compiler removes
   * completely; the caller continues without waiting.
   */
  static inline __attribute__ ((always_inline)) void
  posix_architecture_wfi (void)
  {
  }

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * Implemented with `__atomic_thread_fence (__ATOMIC_SEQ_CST)`, a
   * sequentially consistent fence that orders memory accesses both for
   * the compiler and for the host processor.
   */
  static inline __attribute__ ((always_inline)) void
  posix_architecture_data_barrier (void)
  {
    __atomic_thread_fence (__ATOMIC_SEQ_CST);
  }

  /**
   * @brief Instruction synchronisation barrier; a compiler barrier only.
   *
   * @details
   * Implemented with an empty `asm volatile` statement with a `memory`
   * clobber, which prevents the compiler from moving memory accesses
   * across it, and generates no instruction.
   */
  static inline __attribute__ ((always_inline)) void
  posix_architecture_instruction_barrier (void)
  {
    __asm__ volatile (""
                      : /* Outputs */
                      : /* Inputs */
                      : "memory" /* Clobbers */
    );
  }

  /**
   * @brief No operation.
   *
   * @details
   * Implemented by forwarding to `posix_architecture_nop()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_nop (void)
  {
    posix_architecture_nop ();
  }

  /**
   * @brief Breakpoint.
   *
   * @details
   * Implemented by forwarding to `posix_architecture_bkpt()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_brk (void)
  {
    posix_architecture_bkpt ();
  }

  /**
   * @brief Wait for interrupt.
   *
   * @details
   * Implemented by forwarding to `posix_architecture_wfi()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_wfi (void)
  {
    posix_architecture_wfi ();
  }

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * Implemented by forwarding to `posix_architecture_data_barrier()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_data_barrier (void)
  {
    posix_architecture_data_barrier ();
  }

  /**
   * @brief Instruction synchronisation barrier.
   *
   * @details
   * Implemented by forwarding to `posix_architecture_instruction_barrier()`.
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

    /**
     * @details
     * Implemented by calling `posix_architecture_nop()`.
     */
    inline __attribute__ ((always_inline)) void
    nop (void)
    {
      posix_architecture_nop ();
    }

    /**
     * @details
     * Implemented by calling `posix_architecture_bkpt()`.
     */
    inline __attribute__ ((always_inline)) void
    bkpt (void)
    {
      posix_architecture_bkpt ();
    }

    /**
     * @details
     * Implemented by calling `posix_architecture_wfi()`.
     */
    inline __attribute__ ((always_inline)) void
    wfi (void)
    {
      posix_architecture_wfi ();
    }

    /**
     * @details
     * Implemented by calling `posix_architecture_data_barrier()`.
     */
    inline __attribute__ ((always_inline)) void
    data_barrier (void)
    {
      posix_architecture_data_barrier ();
    }

    /**
     * @details
     * Implemented by calling `posix_architecture_instruction_barrier()`.
     */
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

    /**
     * @details
     * Implemented by forwarding to `posix::architecture::nop()`.
     */
    inline __attribute__ ((always_inline)) void
    nop (void)
    {
      posix::architecture::nop ();
    }

    /**
     * @details
     * Implemented by forwarding to `posix::architecture::bkpt()`.
     */
    inline __attribute__ ((always_inline)) void
    brk (void)
    {
      posix::architecture::bkpt ();
    }

    /**
     * @details
     * Implemented by forwarding to `posix::architecture::wfi()`.
     */
    inline __attribute__ ((always_inline)) void
    wfi (void)
    {
      posix::architecture::wfi ();
    }

    /**
     * @details
     * Implemented by forwarding to `posix::architecture::data_barrier()`.
     */
    inline __attribute__ ((always_inline)) void
    data_barrier (void)
    {
      posix::architecture::data_barrier ();
    }

    /**
     * @details
     * Implemented by forwarding to
     * `posix::architecture::instruction_barrier()`.
     */
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
