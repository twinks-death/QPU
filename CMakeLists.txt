cmake_minimum_required(VERSION 3.31)
project(qpu C)

set(CMAKE_C_STANDARD 23)

# Add SDL3 paths
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3")
set(SDL3_LIBRARIES "${SDL3_DIR}/lib")

# Add SDL include directory
include_directories(lib/SDL3/include)

# Link directories where SDL static libs are located
link_directories(${SDL3_LIBRARIES})

add_executable(qpu src/qpu.c src/qpu-lib.h)

target_compile_options(qpu PRIVATE
        -Wall      # Enable all warnings
        -Wextra    # Enable extra warnings
        -Wpedantic # Enable strict ISO C warnings
        -O3
        -static
)

# Link SDL3 static libraries
target_link_libraries(qpu PRIVATE
    ${SDL3_LIBRARIES}/libSDL3.dll.a
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