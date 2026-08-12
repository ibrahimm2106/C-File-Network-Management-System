# C File & Network Management System

A Windows-focused C application developed for an Operating Systems university coursework project.

## Overview

This project implements a menu-driven file management utility in C with file operations, validation, basic encryption/decryption, permission handling, authentication, and TCP file-transfer functionality.

The coursework focused on operating-system protection/security, layered error handling, input validation, and client-server socket programming.

## Implemented Features

- Create and delete files
- Check whether a file exists before protected operations
- Change file permissions
- Merge two files using buffered file I/O
- Encrypt and decrypt files using password-based XOR processing
- Validate menu and permission input
- Authenticate a user before network file transfer
- Connect to a remote server using TCP sockets
- Transfer file data using Winsock2
- Handle file, socket, connection, and input errors
- Menu-driven command-line interface

## Networking

The application uses the Windows **Winsock2** API to initialise Winsock, create a TCP socket, connect to a specified IP address and port, open a file in binary mode, transmit data, and clean up resources.

## Security & Validation

The project demonstrates file-existence validation, authentication before file transmission, password-based XOR encryption/decryption, explicit error reporting, and input validation for menu selections and permission values.

> The directory-monitoring menu option in the coursework source is a **stub implementation** and is intentionally not presented as a completed feature.

## Technologies

C • Standard C file I/O • Windows `_access` / `_chmod` • Winsock2 • TCP/IP sockets • Visual Studio

## Project Structure

```text
src/
  file_management_system.c
BUILD.md
```

## Build on Windows

Using the Visual Studio Developer Command Prompt:

```cmd
cl src\file_management_system.c /Fe:file_management_system.exe ws2_32.lib
```

Then run:

```cmd
file_management_system.exe
```

## Academic Context

Based on Operating Systems coursework at the University of Roehampton. The assessment required C programming across file reading/writing, encryption/decryption, file creation/deletion, input validation, error handling, operating-system protection/security, and client-server socket programming.

## Author

Mohamed Ibrahim  
BEng Software Engineering, University of Roehampton
