cmake_minimum_required(VERSION 3.31)
project(qpu C)

set(CMAKE_C_STANDARD 23)

# Add SDL3 paths
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/includes/SDL3")
set(SDL3_LIBRARIES "${SDL3_DIR}/lib")

# Add SDL include directory
include_directories(includes/SDL3/include)

# Link directories where SDL static libs are located
link_directories(${SDL3_LIBRARIES})

add_executable(qpu includes/qpu.h
        src/main.c)

target_compile_options(qpu PRIVATE
        -O3
        -Werror
        -Wall
        -Wpedantic
        -static
        -v
)

# Link SDL3 static libraries
target_link_libraries(qpu PRIVATE
    ${SDL3_LIBRARIES}/libSDL3.a
    ${SDL3_LIBRARIES}/libSDL3_test.a
    # Additional system libraries required by SDL
    mingw32
    user32
    gdi32
    winmm
    imm32
    ole32
    oleaut32
    version
    uuid
    advapi32
    setupapi
    shell32
)