[![license](https://img.shields.io/github/license/micro-os-plus/posix-arch-xpack.svg)](https://github.com/micro-os-plus/posix-arch-xpack/blob/xpack/LICENSE)
[![Travis](https://img.shields.io/travis/micro-os-plus/posix-arch-xpack.svg)](https://travis-ci.org/micro-os-plus/posix-arch-xpack)
[![GitHub issues](https://img.shields.io/github/issues/micro-os-plus/posix-arch-xpack.svg)](https://github.com/micro-os-plus/posix-arch-xpack/issues)
[![GitHub pulls](https://img.shields.io/github/issues-pr/micro-os-plus/posix-arch-xpack.svg)](https://github.com/micro-os-plus/posix-arch-xpack/pulls)

# µOS++ POSIX architecture support

A source xPack with the **µOS++** files specific to the synthetic POSIX port.
The project is hosted on GitHub as
[micro-os-plus/posix-arch-xpack](https://github.com/micro-os-plus/posix-arch-xpack).

## Purpose

This xPack provides the implementation for the µOS++ scheduler,
running on a synthetic POSIX platform, as an user mode process under
macOS and GNU/Linux.

## Status

The µOS++ synthetic POSIX scheduler port is fully functional.

## Configuration

To include this µOS++ port in a project, consider the following details.

### Include folders

- `include`

### Source folders

- `src`

### Symbols

- `_XOPEN_SOURCE=700L`

## Limitations

When running on a synthetic POSIX platform, the µOS++ scheduler runs
in cooperative mode only.

## Tests

None.

## License

The original content is released under the
[MIT License](https://opensource.org/licenses/MIT), with all rights reserved to
[Liviu Ionescu](https://github.com/ilg-ul).
