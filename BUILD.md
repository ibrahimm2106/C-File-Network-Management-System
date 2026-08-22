# Build notes

## Requirements

- Windows
- Visual Studio Build Tools or Visual Studio with C/C++ support
- Developer Command Prompt for Visual Studio
- Optional: CMake 3.20+

## Quick build with MSVC

Open **Developer Command Prompt for Visual Studio** in the repository root and run:

```cmd
cl src\file_management_system.c /Fe:file_management_system.exe
cl src\server.c /Fe:server.exe
```

Both source files use `#pragma comment(lib, "ws2_32.lib")`, so MSVC links Winsock automatically.

## Run the programs

Start the receiver first:

```cmd
server.exe
```

Then, in a second terminal, start the client application:

```cmd
file_management_system.exe
```

Use the following values for the client network-transfer option:

- Username: `admin`
- Password: `securepass`
- Server IP address: `127.0.0.1`
- Server port: `8080`

## Build with CMake

```cmd
cmake -S . -B build -A x64
cmake --build build --config Release
```

With the current `CMakeLists.txt`, both the client and server targets are built.
