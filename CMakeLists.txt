cmake_minimum_required(VERSION 3.20)

project(file_management_system LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT WIN32)
    message(FATAL_ERROR "This project uses Windows-specific APIs and must be built on Windows.")
endif()

add_executable(file_management_system
    src/file_management_system.c
)

add_executable(server
    src/server.c
)

target_link_libraries(file_management_system PRIVATE ws2_32)
target_link_libraries(server PRIVATE ws2_32)

if(MSVC)
    target_compile_options(file_management_system PRIVATE /W4)
    target_compile_options(server PRIVATE /W4)
endif()
