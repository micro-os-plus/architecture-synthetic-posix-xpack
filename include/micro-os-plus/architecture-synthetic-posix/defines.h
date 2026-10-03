/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2021-2026 Liviu Ionescu. All rights reserved.
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
 * @brief Preprocessor definitions for the synthetic POSIX platform.
 *
 * @details
 * The place for the architecture definitions that must also be visible
 * to assembly files, since `micro-os-plus/architecture.h` includes it
 * even when `__ASSEMBLER__` is defined; it must therefore contain only
 * preprocessor definitions.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_DEFINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_DEFINES_H_

// ----------------------------------------------------------------------------

/**
 * @brief Specifiers for the always inlined architecture wrappers.
 *
 * @details
 * Used on both the declarations and the definitions of the functions
 * wrapping architecture instructions, in C and in C++.
 *
 * In C, the functions are `static inline`, since plain `inline` would
 * require an external definition in one translation unit.
 *
 * In C++, the functions are `inline` with external linkage, so that the
 * external linkage C++ wrappers refer to the same entity in all
 * translation units, as required by the One Definition Rule; with
 * `static`, each translation unit would get a distinct function.
 *
 * In both languages, inlining is forced, also in non-optimised builds;
 * in C++ with the standard attribute syntax (`[[gnu::always_inline]]`),
 * in C with `__attribute__ ((always_inline))`, since C11 has no standard
 * attribute syntax.
 *
 * In C++ the macro expands to an attribute, therefore it must be the
 * first element of the declaration, after any other standard attributes
 * such as `[[nodiscard]]`.
 *
 * The same definition is used by the RISC-V, AArch32, and AArch64
 * architecture packages.
 */
#if defined(__cplusplus)
#define MICRO_OS_PLUS_ALWAYS_INLINE [[gnu::always_inline]] inline
#else // !defined(__cplusplus)
#define MICRO_OS_PLUS_ALWAYS_INLINE \
  static inline __attribute__ ((always_inline))
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_DEFINES_H_

// ----------------------------------------------------------------------------
