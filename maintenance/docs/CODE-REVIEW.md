# Code Review — µOS++ Synthetic POSIX architecture

- Date: 2026-10-02, revised 2026-10-03
- Branch: `xpack-development` at `302b854`
- Scope: `include/`, `src/`, `tests/`, plus the build metadata and
  documentation that describe them (`xcdl-package.jsonc`, `README.md`,
  `NOTES.md`, `CHANGELOG.md`, `package.json`, the CI workflow)

This document lists only the issues that are still open, and the
decisions taken not to fix some of them. Fixed issues have been removed;
the numbering of the remaining ones is unchanged, so earlier references
remain valid.

## Verification performed

- All sources compiled with xPack clang 21.1.8 and Apple clang 17 with
  `-Werror -Weverything`, excluding only `-Wc++98-compat`, `-Wpadded`,
  and `-Wpoison-system-directories`, against the sibling
  `diag-trace-xpack.git` headers:
  - `architecture.h` and `device.h` as C11, C++20, and assembler, in files
    that call every instruction function and in files that only include
    the headers, with repeated inclusion;
  - `src/diag/trace-posix.cpp` for both trace channels, and with neither
    or both channel macros defined (both fail with the intended `#error`).
- At `-O0`, all calls to the instruction functions are inlined.
- `micro-test-plus-xpack.git/tests/build/native-cmake-clang21-debug`,
  which links this working copy, builds, and all 80 tests pass.
- Doxygen 1.17 with all warnings enabled (`WARN_IF_UNDOCUMENTED`,
  `WARN_IF_INCOMPLETE_DOC`, `WARN_NO_PARAMDOC`): no warnings for this
  package when run together with the `diag-trace` headers.
- The trace ordering with `printf ()` and `std::cout` output was checked
  with output redirected to a file and to a pipe, for both channels.
- **GCC was not available** on this machine; see "Not reviewed".

## Summary

The architecture headers and the trace channel are small, correct,
documented, and compile warning-free. The remaining open points are:

- the version and the change log have not been updated since `v5.0.2`,
  although 28 commits have followed, several of which change the
  interface (#28);
- the enable guard in `architecture.h` requires consumers to define a
  macro they did not need before, and a missing macro is reported far
  from the cause (#6);
- the absence of tests and CI is a declared project decision, but the
  leftover CI workflow and badges are inconsistent with it (#2);
- a few template-generated files and cross-port questions (#17, #27).

Severity: **High** — broken or misleading for users; **Medium** — incorrect
behaviour or a clear rule violation; **Low** — style, consistency, or
polish.

## Open issues

### Tests

- **#2 — Low — leftover CI workflow and dead CI badges.**
  CI tests are declared disabled (`.github/copilot-instructions.md`), and
  the absence of a `tests/` xpm package is a declared decision
  (`tests/README.md`); neither is reported as a defect. However:
  - `.github/workflows/test-ci.yml` is still present, with no
    `if: false` or other in-repository guard, and runs
    `xpm run install-ci` and `xpm run test-ci`, neither of which is
    defined in `package.json`. If the workflow is re-enabled on GitHub, or
    the repository is forked, it fails on every push.
  - The "CI on Push" badges in `README.md:5` and `README-MAINTAINER.md:2`,
    and the link in `README-MAINTAINER.md:118`, point to
    `actions/workflows/ci.yml`, which does not exist (the file is
    `test-ci.yml`); `README-MAINTAINER.md:132` points to `test-all.yml`,
    which does not exist either.

  Recommendation: stop generating `test-ci.yml` for this package (through
  `config/top-templates.json` in `npm-packages-helper`), and remove the
  badges and links, or point them at a real workflow once tests exist.

- **#3 — Low (deferred) — no test exercises the architecture
  instructions.**
  Nothing in this repository compiles `architecture.h` in C, C++, or
  assembler mode. Testing is delegated to consuming projects by decision;
  this item records that a minimal compile-only check here would cost
  little and would detect problems such as #6 at the source, if CI is
  enabled later.

### Correctness and maintainability

- **#6 — Low — consumers must add the enable macro, and a missing macro
  is reported far from the cause.**
  `include/micro-os-plus/architecture.h:58-72` (commit `cc23b44`). The
  guard itself is intentional:
  `MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_ENABLED` will be generated
  by xcdl when it becomes available. Until then it must be defined
  manually, as all µOS++ configuration macros are, preferably in
  `micro-os-plus/project-config.h` or in the package specific
  `micro-os-plus/architecture-defines.h`, both optional headers included
  by `architecture.h` (`-D` on the compiler command line also works).
  `README.md`, `NOTES.md`, and `CLAUDE.md` document this.
  Remaining points:
  - Before `cc23b44` the header worked without the macro, and a search of
    the sibling repositories under `micro-os-plus.github/xPacks/` found no
    file outside this package that defines it, so consumers that call the
    architecture functions must add it when they update (see #28).
  - If the macro is missing, the header declares nothing, and the user
    gets "undeclared function" errors at the call sites, far from the
    cause (verified in C).

  Recommendation (optional): add
  `#else` + `#error "MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_ENABLED
  is not defined"`, so that a missing definition is reported in
  `architecture.h` itself; this is safe as long as only one architecture
  package is used in a build.

### Naming and style

- **#17 — Low — inconsistent names of the breakpoint across forms.**
  The portable function is `brk`, the POSIX one is `bkpt`. Each comment
  now names the function it documents, but the naming asymmetry remains.
  The same asymmetry exists in `architecture-cortexm-xpack`, so this is a
  cross-port API question, to be decided for all ports together.

- **#18 — Low — test style.**
  `tests/*/main.cpp:26-30` suppress `-Wunused-parameter` with a pragma
  instead of declaring `int main (void)` (or using `[[maybe_unused]]`).
  Line 35 is a stray blank line after the opening brace. (The files are
  not built; see #1 under "Decisions".)

### Documentation

- **#27 — Low — the code-review skill describes a different project;
  minor defects in the Copilot instructions.**
  The skill's front matter says "µOS++ Intrusive Lists project", and its
  checklist refers to intrusive-list links and `doubly_list`. In
  `.github/copilot-instructions.md`: "project specific" should be
  "project-specific"; the xcdl section has a trailing space after
  "header files"; the continuation lines of the "Code Review" bullet are
  not indented; and `/website` is described as containing "the project
  documentation and guides", whereas it holds only a placeholder
  `README.md`. Both files come from `npm-packages-helper` templates, so
  fix them there.

### Licensing and metadata

- **#28 — Medium — version and change log not updated after `v5.0.2`.**
  `package.json` is `5.0.2`, which is already tagged (`v5.0.2`), yet 28
  commits follow the tag. `README-MAINTAINER.md` prescribes an
  `x.y.z-pre` version during development, and `CHANGELOG.md` has no entry
  for these commits. Several of them change the interface seen by
  consumers:
  - the enable guard in `architecture.h` (`cc23b44`): every application
    that calls the architecture functions must now define
    `MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_ENABLED` (#6);
  - `<stdint.h>` is no longer included by the public headers
    (`cbdbdb7`); no consumer in the sibling repositories relied on it,
    but external ones may;
  - the C functions compiled as C++ now have external linkage, the C++
    functions are `noexcept`, and the `MICRO_OS_PLUS_ALWAYS_INLINE` macro
    is new (`b6de396`, `91c41e6`, `302b854`);
  - the trace channel now writes through the standard I/O library and
    initialises itself from a priority-101 constructor (`39fa54e`,
    `6aef616`), and the channel macros are checked for exactly one
    selection.

  Under the project's semver rules, the enable guard alone is an
  incompatible change and requires a major version bump.
  Recommendation: set the version to the next `-pre` (a major one if the
  guard is kept), and add a `CHANGELOG.md` entry listing these changes.

- **#29 — Low — `CHANGELOG.md` references a commit not on any branch.**
  The 2026-09-09 entry lists `d2efa3a cmake re-format`; the branch
  history has `cf223db cmake re-format` (the commit was evidently
  amended or rebased). Regenerate the entry from `npm run git-log`.

Licence headers: all source and header files carry the identical MIT
header with plausible year ranges. No issue.

### Folder structure

No issues. Declarations are in `include/`, inline definitions in
`inlines/`, the single out-of-line definition in `src/`, and
`src/diag/trace-posix.cpp` is registered in `CMakeLists.txt` and
`meson.build` through `xcdl-package.jsonc`.

## Decisions

Issues that were deliberately not fixed.

- **#1 — ignored — the stale test files do not compile.**
  `tests/trace-stdout/main.cpp` and `tests/trace-stderr/main.cpp` still
  call `trace::initialize ()` and `trace_puts ()`, which no longer exist.
  The files are not part of any build (`tests/README.md`); they will be
  replaced when real tests are added.
- **#4 — by design — the initialisation banner on the standard output.**
  With the STDOUT channel, the banner printed by `initialise ()` is mixed
  with the application output, like any other trace message. Selecting
  STDERR keeps the trace separate; `README.md` explains this.
- **#30 — accepted — the trace is not async-signal-safe.**
  `write ()` uses the standard I/O library, which is not
  async-signal-safe. A trace call made from the µOS++ clock tick handler
  (`rtos-synthetic-posix-xpack.git/src/port.cpp:352`) while the
  interrupted code is inside a standard I/O call on the same stream may
  corrupt the stream buffer. Accepted because the trace calls in the
  handler path are compiled only with specific debug definitions (for
  example `MICRO_OS_PLUS_TRACE_RTOS_THREAD_CONTEXT`), and even then the
  tick handler traces only rarely. Blocking the signals around each
  write was rejected: it costs about 1 µs per message (measured on macOS
  with a `sigprocmask ()` pair), defers the tick while the output is
  blocked (so ticks can be lost if a pipe or terminal stalls), and would
  not protect the application's own `printf ()` calls anyway. The
  limitation and the reasons are documented in the `@details` of
  `write ()`; user timer callbacks that trace run in the handler too.

## Not reviewed, or not certain enough to report

- **GCC behaviour**: GCC was not available. In particular, it was not
  checked whether GCC honours `__attribute__ ((constructor (101)))` on a
  static member function or merely warns and ignores it; the
  `-Wattributes` suppression at `trace-posix.cpp:106-107` hints that it
  warns. Since `write ()` and `flush ()` initialise lazily, the trace
  would still work if the attribute were ignored; only the banner would
  appear later, on the first trace message.
- Consumers outside `micro-os-plus.github/xPacks/` (for example
  application templates or projects elsewhere) were not searched for
  `MICRO_OS_PLUS_ARCHITECTURE_SYNTHETIC_POSIX_ENABLED` or for reliance on
  `<stdint.h>`, and no consumer that calls the architecture functions was
  built against the current headers.
- The `prettier` devDependency in `package.json` was not checked.
- The generated files (`CMakeLists.txt`, `meson.build`, `scripts/*.mjs`,
  the CI workflow) were only checked for consistency with the sources,
  not reviewed in their own right; they belong to `npm-packages-helper`.
- The statement in `NOTES.md` that the default memory allocator uses
  `malloc ()` describes the RTOS port and was not verified.
