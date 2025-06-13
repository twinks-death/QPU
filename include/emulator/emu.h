/*==============================================================================
 Copyright (c) 2025 Twink's Death
 SPDX-License-Identifier: BSD-3-Clause
 See the LICENSE file in repo's root for details.

 qpu8_emu: emu.h
 =============================================================================*/

#ifndef EMU_H
#define EMU_H

// Standard library
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

// Types
typedef uint8_t  byte;
typedef uint16_t word;

// Emulator flags
typedef struct {
    bool  assemble;
    bool  disassemble;
    bool  test;
    byte  speed;
    char* input_file;
} emu_flags_t;

// In emu.c
void parse_flags ( int argc, char** argv, emu_flags_t* emu_flags );

#endif //EMU_H
