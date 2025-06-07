#ifndef ASM_H
#define ASM_H

// Standard library
#include <stdio.h>
#include <stdlib.h>

// Project headers
#include "emulator/emu.h"

// Format for the binary produced by assembler
typedef struct {
    byte*  data;
    size_t size;
} assembled_result_t;

// In asm.c
void assemble ( const char* input_file );

// In disasm.c
int disassemble ( const char* input_file );

#endif //ASM_H
