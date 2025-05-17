cmake_minimum_required(VERSION 3.31)
project(qpu C)

set(CMAKE_C_STANDARD 23)

# Add SDL3 paths
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3")
set(SDL3_INCLUDE_DIRS "${SDL3_DIR}/include")
set(SDL3_LIBRARIES "${SDL3_DIR}/lib")

# Add SDL include directory
include_directories(${SDL3_INCLUDE_DIRS})

# Link directories where SDL static libs are located
link_directories(${SDL3_LIBRARIES})

add_executable(qpu src/qpu.c src/qpu-lib.h)

# Link SDL3 static libraries
target_link_libraries(qpu PRIVATE
    ${SDL3_LIBRARIES}/libSDL3.a
    ${SDL3_LIBRARIES}/libSDL3main.a
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