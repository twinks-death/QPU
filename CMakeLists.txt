cmake_minimum_required(VERSION 3.31)
project(qpu8_emu C)

set(CMAKE_C_STANDARD 23)

# Add SDL3 paths
set(SDL3_DIR "${PROJECT_SOURCE_DIR}/include/sdl3")
set(SDL3_LIBRARIES "${SDL3_DIR}/lib")

# Add SDL include directory
include_directories(include/sdl3/include)

# Link directories where SDL static libs are located
link_directories(${SDL3_LIBRARIES})

# Define the executable
add_executable(qpu8_emu)

# Include directories (for headers)
target_include_directories(qpu8_emu PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Grab all C source files under src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/src/*.c
)

# Add sources to the target
target_sources(qpu8_emu PRIVATE ${SRC_FILES})


target_compile_options(qpu8_emu PRIVATE
        -O3
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wshadow
        -Wformat=2
        -Wundef
        -Wconversion
        -Wuninitialized
        -Wfloat-equal
        -Wlogical-op
        -Wshift-overflow=2
        -Wduplicated-cond
        -Wduplicated-branches
        -Wnull-dereference
        -Wdouble-promotion
        -Wmisleading-indentation
        -Wcast-qual
        -Wcast-align
        -Wsuggest-final-types
        -Wsuggest-final-methods
        -v
)

# Link SDL3 static libraries
target_link_libraries(qpu8_emu PRIVATE
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