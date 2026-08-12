# Build Notes

This project uses Windows-specific APIs (`Winsock2`, `_access`, and `_chmod`).

## Visual Studio Developer Command Prompt

```cmd
cl src\file_management_system.c /Fe:file_management_system.exe ws2_32.lib
```

The resulting executable is:

```text
file_management_system.exe
```
