[![GitHub package.json version](https://img.shields.io/github/package-json/v/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/blob/xpack/package.json)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/tags/)
[![npm (scoped)](https://img.shields.io/npm/v/@micro-os-plus/architecture-synthetic-posix.svg?color=blue)](https://www.npmjs.com/package/@micro-os-plus/architecture-synthetic-posix/)
[![license](https://img.shields.io/github/license/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/blob/xpack/LICENSE)
[![CI on Push](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions/workflows/ci.yml/badge.svg)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions/workflows/ci.yml)

# A source code library with the µOS++ synthetic POSIX platform

This project provides the **architecture-synthetic-posix** source library as an `xpm`
dependency and includes files specific for running on POSIX platforms.

The project is hosted on GitHub as
[micro-os-plus/architecture-synthetic-posix-xpack](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack).

## Maintainer info

This page is addressed to developers who plan to include this source
library into their own projects.

For maintainer info, please see the
[README-MAINTAINER](README-MAINTAINER.md) file.

## Install

As a source library xpm package, the easiest way to add it to a project is via
**xpm**, but it can also be used as any Git project, for example as a submodule.

### Prerequisites

A recent [xpm](https://xpack.github.io/xpm/),
which is a portable [Node.js](https://nodejs.org/) command line application.

It is recommended to update to the latest version with:

```sh
npm install --global xpm@latest
```

For details please follow the instructions in the
[xPack install](https://xpack.github.io/install/) page.

### xpm

This package is available as
[`@micro-os-plus/architecture-synthetic-posix`](https://www.npmjs.com/package/@micro-os-plus/architecture-synthetic-posix)
from the `npmjs.com` registry:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install @micro-os-plus/architecture-synthetic-posix@latest

ls -l xpacks/@micro-os-plus/architecture-synthetic-posix
```

### Git submodule

If, for any reason, **xpm** is not available, the next recommended
solution is to link it as a Git submodule below an `xpacks` folder.

```sh
cd my-project
git init # Unless already a Git project
mkdir -p xpacks

git submodule add https://github.com/micro-os-plus/architecture-synthetic-posix-xpack.git \
  xpacks/@micro-os-plus/architecture-synthetic-posix
```

## Branches

Apart from the unused `master` branch, there are two active branches:

- `xpack`, with the latest stable version (default)
- `xpack-development`, with the current development version

All development is done in the `xpack-development` branch, and contributions via
Pull Requests should be directed to this branch.

When new releases are published, the `xpack-development` branch is merged
into `xpack`.

## Developer info

### Overview

This source xpm package provides the µOS++ architecture definitions for
the synthetic POSIX platform, which runs µOS++ applications as user mode
processes under macOS and GNU/Linux: the architecture instructions (as
functions callable from C and C++), and the implementation of the
`diag-trace` output channel over the standard output or standard error.

The µOS++ scheduler port for this platform is provided by the separate
[`@micro-os-plus/rtos-synthetic-posix`](https://github.com/micro-os-plus/rtos-synthetic-posix-xpack)
package.

### Status

The **architecture-synthetic-posix** source library is fully functional.

### Build & integration info

The project is written in C++ and it is expected
to be used in [C and] C++ projects.

The source code is compiled with clang and gcc and should be warning free.

To ease the integration of this package into user projects, there
are already made CMake and meson configuration files (see below).

For other build systems, consider the following details:

#### Include folders

The following folders should be passed to the compiler during the build:

- `include`

The header files to be included in user projects are:

```c++
#include "micro-os-plus/architecture.h"
```

#### Source files

The source files to be added to user projects are:

- `src/diag/trace-posix.cpp`

#### Preprocessor definitions

The architecture headers are enabled only when the following macro is
defined:

- `MICRO_OS_PLUS_ARCHITECTURES_SYNTHETIC_POSIX_ENABLED`

As for all µOS++ configuration macros, the preferred place to define it
is `micro-os-plus/project-config.h` or the package specific
`micro-os-plus/architecture-defines.h`; both are optional headers,
included by `micro-os-plus/architecture.h` if present. Defining it on the
compiler command line (`-D`) also works. It will be
generated by the xcdl tool when that becomes available; until then, it
must be defined manually.

If it is missing, `micro-os-plus/architecture.h` declares nothing, and
the compiler reports the architecture functions as undeclared where they
are called.

The trace output definitions are described in the next section.

This package does not require `_XOPEN_SOURCE`; the RTOS port, which uses
`ucontext`, defines it in its own build configuration.

#### Trace output

When `MICRO_OS_PLUS_DIAG_TRACE_ENABLED` is defined, the trace output
channel must be selected by defining exactly one of:

- `MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDOUT_ENABLED`
- `MICRO_OS_PLUS_DIAG_TRACE_POSIX_STDERR_ENABLED`

The preferred place to define these macros is
`micro-os-plus/project-config.h` or the package specific
`micro-os-plus/diag/trace-defines.h`, both included by
`micro-os-plus/diag/trace.h` if present; `-D` on the compiler command line
also works.

The trace messages are written via the standard I/O library and flushed
after each message, so they are correctly interleaved with the
application output (`printf()`, `std::cout`), even when the output is
redirected to a file or a pipe, and are not lost if the process crashes.

With STDOUT, the trace messages are mixed with the application output on
the standard output. To keep them separate, for example when the
application output is processed by other tools, select STDERR.

The trace is initialised automatically, by a constructor that runs before
`main()`; there is no need to call `trace::initialise()` explicitly.

#### C++ Namespaces

- `micro_os_plus::architecture` (the portable functions)
- `posix::architecture` (the platform-specific functions)

#### C++ Classes

TBD

#### Dependencies

- the `@micro-os-plus/diag-trace` package, for the trace definitions.

#### CMake

To integrate the architecture-synthetic-posix source library into a CMake application,
add this folder to the build:

```cmake
add_subdirectory("xpacks/@micro-os-plus/architecture-synthetic-posix")
```

The result is an interface library that can be added as an application
dependency with:

```cmake
target_link_libraries(your-target PRIVATE
  micro-os-plus::architecture
)
```

`micro-os-plus::architecture` is an alias of
`micro-os-plus::architectures-synthetic-posix`; either name can be used.
It also brings in the trace output channel
(`micro-os-plus::diag-trace-posix`) and requires the
`micro-os-plus::diag-trace` target, from the `@micro-os-plus/diag-trace`
package.

#### meson

To integrate the architecture-synthetic-posix source library into a meson application,
add this folder to the build:

```meson
subdir('xpacks/@micro-os-plus/architecture-synthetic-posix')
```

The result is a dependency object that can be added
to an application with:

```meson
exe = executable(
  your-target,
  link_with: [
    # Nothing, not static.
  ],
  dependencies: [
    micro_os_plus_architecture_dependency,
  ]
)
```

`micro_os_plus_architecture_dependency` is equivalent to
`micro_os_plus_architectures_synthetic_posix_dependency`; either name can
be used. It also brings in the trace output channel
(`micro_os_plus_diag_trace_posix_dependency`), and it refers to
`micro_os_plus_diag_trace_dependency`, so the `@micro-os-plus/diag-trace`
folder must be processed with `subdir()` before this one.

### Examples

TBD

### Known problems

- none

### Tests

TBD

## Change log - incompatible changes

According to [semver](https://semver.org) rules:

> Major version X (X.y.z | X > 0) MUST be incremented if any
> backwards incompatible changes are introduced to the public API.

The incompatible changes, in reverse chronological order,
are:

- v5.x: updates for xcdl
- v4.x: move rtos-port to separate package
- v3.x: separate rtos-port folder
- v2.x: rename micro_os_plus
- v1.x: initial content from the single repo

## License

Unless otherwise stated, the content is released under the terms of the
[MIT License](https://opensource.org/licenses/mit),
with all rights reserved to
[Liviu Ionescu](https://github.com/ilg-ul).
