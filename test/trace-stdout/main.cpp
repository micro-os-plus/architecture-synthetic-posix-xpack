/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2015 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#include <micro-os-plus/diag/trace.h>

#include <cstdio>
#include <cassert>
#include <cstring>

// ----------------------------------------------------------------------------

using namespace micro_os_plus;

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int
main (int argc, char* argv[])
{

  trace::initialize ();
  trace::puts ("C++ Message");

  trace_puts ("C Message");

  return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
