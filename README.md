[![GitHub package.json version](https://img.shields.io/github/package-json/v/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/blob/xpack/package.json)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/tags/)
[![npm (scoped)](https://img.shields.io/npm/v/@micro-os-plus/architecture-synthetic-posix.svg?color=blue)](https://www.npmjs.com/package/@micro-os-plus/architecture-synthetic-posix/)
[![license](https://img.shields.io/github/license/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/blob/xpack/LICENSE)
[![CI on Push](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions/workflows/CI.yml/badge.svg)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions/workflows/CI.yml)

# A source library xPack with the µOS++ synthetic POSIX platform

This project provides the **architecture-synthetic-posix** source library as an xPack
dependency and includes files specific for running on POSIX platforms.

The project is hosted on GitHub as
[micro-os-plus/architecture-synthetic-posix-xpack](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack).

## Maintainer info

This page is addressed to developers who plan to include this source
library into their own projects.

For maintainer info, please see the
[README-MAINTAINER](README-MAINTAINER.md) file.

## Install

As a source library xPack, the easiest way to add it to a project is via
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

Note: the package will be available from npmjs.com at a later date.

For now, it can be installed from GitHub:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install github:micro-os-plus/architecture-synthetic-posix-xpack
```

When ready, this package will be available as
[`@micro-os-plus/architecture-synthetic-posix`](https://www.npmjs.com/package/@micro-os-plus/architecture-synthetic-posix)
from the `npmjs.com` registry:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install @micro-os-plus/architecture-synthetic-posix@latest

ls -l xpacks/micro-os-plus-architecture-synthetic-posix
```

### Git submodule

If, for any reason, **xpm** is not available, the next recommended
solution is to link it as a Git submodule below an `xpacks` folder.

```sh
cd my-project
git init # Unless already a Git project
mkdir -p xpacks

git submodule add https://github.com/micro-os-plus/architecture-synthetic-posix-xpack.git \
  xpacks/micro-os-plus-architecture-synthetic-posix
```

## Branches

Apart from the unused `master` branch, there are two active branches:

- `xpack`, with the latest stable version (default)
- `xpack-develop`, with the current development version

All development is done in the `xpack-develop` branch, and contributions via
Pull Requests should be directed to this branch.

When new releases are published, the `xpack-develop` branch is merged
into `xpack`.

## Developer info

### Overview

This xPack provides the implementation for the µOS++ scheduler,
running on a synthetic POSIX platform, as an user mode process under
macOS and GNU/Linux.

### Status

The **architecture-synthetic-posix** source library is fully functional

### Build & integration info

The project is written in C++ and it is expected
to be used in [C and] C++ projects.

The source code was compiled with GCC 11, clang 12, clang 13
and should be warning free.

To ease the integration of this package into user projects, there
are already made CMake and meson configuration files (see below).

For other build systems, consider the following details:

#### Include folders

The following folders should be passed to the compiler during the build:

- `include`

The header files to be included in user projects are:

```c++
#include <micro-os-plus/architecture.h>
```

#### Source files

The source files to be added to user projects are:

- `src/trace-posix.cpp`

#### Preprocessor definitions

For the build to pass, the following definitions should be passed to the
complier:

- `_XOPEN_SOURCE=700L`

#### C++ Namespaces

- `micro_os_plus::architecture`

#### C++ Classes

TBD

#### Dependencies

- the `@micro-os-plus/diag-trace` package, for the trace definitions.

#### CMake

To integrate the architecture-synthetic-posix source library into a CMake application,
add this folder to the build:

```cmake
add_subdirectory("xpacks/micro-os-plus-architecture-synthetic-posix")`
```

The result is an interface library that can be added as an application
dependency with:

```cmake
target_link_libraries(your-target PRIVATE

  micro-os-plus::architecture-synthetic-posix
)
```

#### meson

To integrate the architecture-synthetic-posix source library into a meson application,
add this folder to the build:

```meson
subdir('xpacks/micro-os-plus-architecture-synthetic-posix')
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
    micro_os_plus_architecture_synthetic_posix_dependency,
  ]
)
```

### Examples

TBD

### Known problems

- none

### Tests

TBD

## Change log - incompatible changes

According to [semver](https://semver.org) rules:

> Major version X (X.y.z | X > 0) MUST be incremented if any
backwards incompatible changes are introduced to the public API.

The incompatible changes, in reverse chronological order,
are:

- v4.x: move rtos-port to separate package
- v3.x: separate rtos-port folder
- v2.x: rename micro_os_plus
- v1.x: initial content from the single repo

## License

The original content is released under the
[MIT License](https://opensource.org/licenses/MIT/),
with all rights reserved to
[Liviu Ionescu](https://github.com/ilg-ul/).
