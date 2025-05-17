cmake_minimum_required(VERSION 3.31)
project(qpu C)

set(CMAKE_C_STANDARD 23)

add_executable(qpu src/qpu.c
        src/qpu-lib.h)
