[![license](https://img.shields.io/github/license/micro-os-plus/architecture-synthetic-posix-xpack)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/blob/xpack/LICENSE)
[![CI on Push](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/workflows/CI%20on%20Push/badge.svg)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions?query=workflow%3A%22CI+on+Push%22)
[![GitHub issues](https://img.shields.io/github/issues/micro-os-plus/architecture-synthetic-posix-xpack.svg)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/issues/)
[![GitHub pulls](https://img.shields.io/github/issues-pr/micro-os-plus/architecture-synthetic-posix-xpack.svg)](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/pulls)

# Maintainer info

## Project repository

The project is hosted on GitHub:

- <https://github.com/micro-os-plus/architecture-synthetic-posix-xpack.git>

To clone the stable branch (`xpack`), run the following commands in a
terminal (on Windows use the _Git Bash_ console):

```sh
rm -rf ~/Work/architecture-synthetic-posix-xpack.git && \
mkdir -p ~/Work && \
git clone \
  https://github.com/micro-os-plus/architecture-synthetic-posix-xpack.git \
  ~/Work/architecture-synthetic-posix-xpack.git
```

For development purposes, clone the `xpack-develop` branch:

```sh
rm -rf ~/Work/architecture-synthetic-posix-xpack.git && \
mkdir -p ~/Work && \
git clone \
  --branch xpack-develop \
  https://github.com/micro-os-plus/architecture-synthetic-posix-xpack.git \
  ~/Work/architecture-synthetic-posix-xpack.git
```

## Prerequisites

A recent [xpm](https://xpack.github.io/xpm/), which is a portable
[Node.js](https://nodejs.org/) command line application.

## Code formatting

Code formatting is done using `clang-format --style=file`, either manually
from a script, or automatically from Visual Studio Code, or the Eclipse
CppStyle plug-in.

## Publish on the npmjs.com server

- select the `xpack-develop` branch
- commit all changes
- update versions in `README.md` and `README-MAINTAINER.md`
- update `CHANGELOG.md`
- commit with a message like _prepare v4.0.2_
- `npm pack` and check the content of the archive, which should list
  only `package.json`, `README.md`, `LICENSE`, `CHANGELOG.md`,
  the sources and CMake/meson files;
  possibly adjust `.npmignore`
- `npm version patch`, `npm version minor`, `npm version major`
- push the `xpack-develop` branch to GitHub
- the `postversion` npm script should also update tags via `git push origin --tags`
- wait for the CI job to complete
  (<https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions/workflows/CI.yml>)
- `npm publish --tag next` (use `npm publish --access public` when
  publishing for the first time)

The version is visible at:

- <https://www.npmjs.com/package/@micro-os-plus/architecture-synthetic-posix?activeTab=versions>

## Testing

The project includes unit tests.

To run them, run:

```sh
cd architecture-synthetic-posix-xpack.git
xpm run install-all
xpm run test
```

## Continuous Integration

The CI tests are performed on GitHub Actions, as the
[CI on Push](https://github.com/micro-os-plus/architecture-synthetic-posix-xpack/actions?query=workflow%3A%22CI+on+Push%22)
workflow.

## Update the repo

When the package is considered stable:

- with Sourcetree
- merge `xpack-develop` into `xpack`
- push to GitHub
- select `xpack-develop`

## Tag the npm package as `latest`

When the release is considered stable, promote it as `latest`:

- `npm dist-tag ls @micro-os-plus/architecture-synthetic-posix`
- `npm dist-tag add @micro-os-plus/architecture-synthetic-posix@4.0.2 latest`
- `npm dist-tag ls @@micro-os-plus/architecture-synthetic-posix`
