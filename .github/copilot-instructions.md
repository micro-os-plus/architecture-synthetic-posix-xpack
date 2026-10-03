# Copilot Instructions

## Project Overview

This is the **µOS++ Synthetic POSIX architecture** project, part of
µOS++.

## General

- Avoid sycophantic behaviour; for all conversation, never soften criticism
  to protect the person's ego.
- If something has a flaw, say so directly.
- When you're uncertain, say so rather than presenting guesses as facts.
- This applies to every response.

## Language and Tone

- Use British English spelling and grammar (e.g., "behaviour", "colour",
  "organise", "analyse", "favour", "initialise", etc.)
- Maintain a professional and formal tone in all generated content
- Avoid colloquialisms, slang, or informal expressions
- Avoid humour, jokes, or casual remarks
- Use clear, precise, and professional language appropriate for technical
  documentation
- Avoid contractions (e.g., use "do not" instead of "don't")
- Use the Oxford comma in lists for clarity
- Maintain consistency in terminology throughout the codebase
- Prefer "folder" to "directory"

## Code Style

- Follow the existing C++ code style defined in the .clang-format file.
- Use consistent formatting and naming conventions based on prettier and
  clang-format configurations.
- For C/C++, the naming convention is snake_case.

## Documentation

- Add comprehensive documentation comments accepted by Doxygen
- Document all classes, methods, properties, parameters, and return types.
- The declarations should be in the headers, the definitions in the `src`
  folder, and the inline definitions in the `inlines` folder.
- Add @details sections to all declarations and definitions.
- The @brief and @details sections are displayed sequentially, so ensure the
  @details section expands on the @brief without repeating it. The @brief
  should be a concise summary of the member's purpose, whilst the @details
  should provide a more in-depth explanation, including any relevant
  information about the implementation, usage, or edge cases.
- Document private and protected members as well
- Keep the line length below 80 characters
- If the code already includes documentation, review and possibly improve it.

## Folder Structure

- `/src`: Contains the C++ source code
- `/include`: Contains the C++ header files
- `/tests`: Contains the test suites and test cases
- `/website`: Contains the project documentation and guides

When adding new source files, place them in the appropriate `src` or `include`
folder, and add corresponding entries in the top CMake and Meson configurations.

## Testing

Note: Tests are not yet available. They are performed indirectly in
other projects.

CI tests are disabled for this project.

## Code Review

- When asked for a code review, follow the separate instructions in
  `.github/skills/code-review/SKILL.md` for a thorough and uncompromising
  review of the codebase.

## Version Control

When making changes to the codebase, follow these guidelines for version control:

- Use descriptive commit messages that clearly explain the purpose of the changes

## xcdl

The `xcdl` tool is not yet available; `xcdl-package.jsonc` is used only to
generate the top-level CMake and Meson files (`xpm run xcdl-export`). Only
`publicIncludeFolders`, `sourceFiles`, and `dependencies` affect the
generated files; all other properties (`generatedFile`, `activeIf`,
`defaultValue`, `implements`, and the commented-out `defaultDefine`
entries) are informative only.

In particular, no `*-defines.h` file is generated, so a commented-out
`defaultDefine` does not mean that the macro is disabled. Its name
documents the macro that the application must define itself, either in
`micro-os-plus/project-config.h` or in project-specific header files
(e.g., `micro-os-plus/startup-defines.h`).
