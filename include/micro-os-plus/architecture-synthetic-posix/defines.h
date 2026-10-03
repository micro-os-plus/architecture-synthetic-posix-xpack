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
 *
 * The synthetic POSIX platform needs no such definitions, so the file is
 * currently empty; it is kept for symmetry with the other architecture
 * ports.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_DEFINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_DEFINES_H_

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_DEFINES_H_

// ----------------------------------------------------------------------------
