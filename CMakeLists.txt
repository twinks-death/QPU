cmake_minimum_required(VERSION 3.31)
project(qpu8_emu C)

set(CMAKE_C_STANDARD 11)

# Use Debug as default build type if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug/Release/RelWithDebInfo/MinSizeRel)" FORCE)
endif ()

# Enable debug flags for Debug config, optimization for Release
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

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
        #-Wall
        #-Wextra
        -Wpedantic
        #-Werror
        #-Wshadow
        #-Wformat=2
        #-Wundef
        #-Wconversion
        #-Wuninitialized
        #-Wfloat-equal
        #-Wlogical-op
        #-Wshift-overflow=2
        #-Wduplicated-cond
        #-Wduplicated-branches
        #-Wnull-dereference
        #-Wdouble-promotion
        #-Wmisleading-indentation
        #-Wcast-qual
        #-Wcast-align
        #-Wsuggest-final-types
        #-Wsuggest-final-methods
        -v
)