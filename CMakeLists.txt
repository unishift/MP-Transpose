cmake_minimum_required(VERSION 3.12)
project(transpose C)

set(CMAKE_C_STANDARD 11)

include(FindOpenMP)
if (OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
elseif()
    message("ERROR: OpenMP not found")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(transpose main.c)
