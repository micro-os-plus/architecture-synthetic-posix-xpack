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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INSTRUCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-synthetic-posix/defines.h"

#include <stdint.h>

// ----------------------------------------------------------------------------

/*
 * Declarations of POSIX functions to wrap architecture instructions.
 */

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // Architecture assembly instructions in C.

  /**
   * @brief No operation.
   *
   * @details
   * On the synthetic POSIX platform this is an empty function; there is
   * no reason to emit a host `nop` instruction in a hosted process.
   */
  static void
  posix_architecture_nop (void);

  /**
   * @brief Breakpoint; does nothing on this platform.
   *
   * @details
   * On bare-metal platforms the `bkpt` instruction stops the processor
   * when a debugger is attached. On the synthetic POSIX platform this is
   * an empty function, so execution continues; to stop at this point,
   * set a breakpoint on the caller in the host debugger.
   *
   * It is not implemented with `raise (SIGTRAP)` or
   * `__builtin_debugtrap ()` because, without a debugger attached, these
   * would terminate the process.
   */
  static void
  posix_architecture_bkpt (void);

  /**
   * @brief Wait for interrupt; does nothing on this platform.
   *
   * @details
   * On bare-metal platforms the `wfi` instruction suspends the processor
   * until an interrupt occurs. On the synthetic POSIX platform this is an
   * empty function, so a loop that calls it busy-waits.
   *
   * It is not implemented with `pause ()`, because when the interrupts
   * (the signals) are disabled, `pause ()` would never return, whereas
   * `wfi` on Cortex-M also wakes on pending masked interrupts. The µOS++
   * POSIX scheduler port does not use this function; it waits for the
   * clock tick with `pause ()` directly.
   */
  static void
  posix_architecture_wfi (void);

  /**
   * Data barrier; a sequentially consistent atomic thread fence.
   */
  static void
  posix_architecture_data_barrier (void);

  /**
   * Instruction barrier; a compiler barrier only.
   */
  static void
  posix_architecture_instruction_barrier (void);

  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C.

  /**
   * @brief No operation.
   *
   * @details
   * The portable name of `posix_architecture_nop()`; on the synthetic
   * POSIX platform it does nothing.
   */
  static void
  micro_os_plus_architecture_nop (void);

  /**
   * @brief Breakpoint.
   *
   * @details
   * The portable name of `posix_architecture_bkpt()`; on the synthetic
   * POSIX platform it does nothing, and execution continues.
   */
  static void
  micro_os_plus_architecture_brk (void);

  /**
   * @brief Wait for interrupt.
   *
   * @details
   * The portable name of `posix_architecture_wfi()`; on the synthetic
   * POSIX platform it does nothing, so a loop that calls it busy-waits.
   */
  static void
  micro_os_plus_architecture_wfi (void);

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * Ensures that all memory accesses issued before this call are ordered
   * before any memory access after it, both for the compiler and for
   * the host processor.
   *
   * On the synthetic POSIX platform, it is implemented with
   * `__atomic_thread_fence (__ATOMIC_SEQ_CST)`.
   */
  static void
  micro_os_plus_architecture_data_barrier (void);

  /**
   * @brief Instruction synchronisation barrier.
   *
   * @details
   * On a hosted process there is no user-level equivalent of an
   * instruction synchronisation barrier; the host operating system is
   * responsible for instruction cache coherency.
   *
   * On the synthetic POSIX platform, it is implemented only as a
   * compiler barrier.
   */
  static void
  micro_os_plus_architecture_instruction_barrier (void);

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
    // Architecture assembly instructions in C++.

    /**
     * @brief No operation.
     *
     * @details
     * The C++ equivalent of `posix_architecture_nop()`; it does nothing.
     */
    void
    nop (void);

    /**
     * @brief Breakpoint; does nothing on this platform.
     *
     * @details
     * The C++ equivalent of `posix_architecture_bkpt()`; it does nothing,
     * and execution continues.
     */
    void
    bkpt (void);

    /**
     * @brief Wait for interrupt; does nothing on this platform.
     *
     * @details
     * The C++ equivalent of `posix_architecture_wfi()`; it does nothing,
     * so a loop that calls it busy-waits.
     */
    void
    wfi (void);

    /**
     * Data barrier; a sequentially consistent atomic thread fence.
     */
    void
    data_barrier (void);

    /**
     * Instruction barrier; a compiler barrier only.
     */
    void
    instruction_barrier (void);

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace posix

// ----------------------------------------------------------------------------

namespace micro_os_plus
{
  namespace architecture
  {
    // ------------------------------------------------------------------------
    // Portable architecture assembly instructions in C++.

    /**
     * @brief No operation.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_nop()`; on the
     * synthetic POSIX platform it does nothing.
     */
    void
    nop (void);

    /**
     * @brief Breakpoint.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_brk()`; on the
     * synthetic POSIX platform it does nothing, and execution continues.
     */
    void
    brk (void);

    /**
     * @brief Wait for interrupt.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_wfi()`; on the
     * synthetic POSIX platform it does nothing, so a loop that calls it
     * busy-waits.
     */
    void
    wfi (void);

    /**
     * @brief Data synchronisation barrier.
     *
     * @details
     * The C++ equivalent of `micro_os_plus_architecture_data_barrier()`;
     * on the synthetic POSIX platform, it is a sequentially consistent
     * atomic thread fence.
     */
    void
    data_barrier (void);

    /**
     * @brief Instruction synchronisation barrier.
     *
     * @details
     * The C++ equivalent of
     * `micro_os_plus_architecture_instruction_barrier()`; on the
     * synthetic POSIX platform, it is only a compiler barrier.
     */
    void
    instruction_barrier (void);

    // ------------------------------------------------------------------------
  } // namespace architecture
} // namespace micro_os_plus

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/instructions-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------
