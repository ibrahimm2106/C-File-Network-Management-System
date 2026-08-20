# Build Notes

This project uses Windows-specific APIs (`Winsock2`, `_access`, and `_chmod`) and is intended to be built on Windows.

## CMake

```cmd
cmake -S . -B build
cmake --build build --config Release
```

## Visual Studio Developer Command Prompt

```cmd
cl src\file_management_system.c /Fe:file_management_system.exe ws2_32.lib
```

The direct MSVC command produces:

```text
file_management_system.exe
```

## Continuous integration

`.github/workflows/windows-c-build.yml` configures and compiles the CMake project on `windows-latest` for pull requests and pushes to `main`.
