/*==============================================================================
 Copyright (c) 2025 Twink's Death
 SPDX-License-Identifier: BSD-3-Clause
 See the LICENSE file in repo's root for details.

 qpu8_emu: asm.c
 =============================================================================*/

// Project headers
#include "assembler/asm.h"
#include "assembler/lexer.h"

void
assemble ( const char* input_file )
{
    FILE* file = fopen(input_file, "rb");

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate buffer
    char* input_buffer = malloc(file_size);
    if (!input_buffer) {
        perror("Malloc failed bruh");
        fclose(file);
        exit(1);
    }

    // Copy all of input_file into input_buffer and add null terminator
    fread(input_buffer, 1, file_size, file);
    input_buffer[file_size] = '\0';
    fclose(file);

    // create lexer instance
    token_array_t tokens = {.count = 0, .capacity = 256, .token = malloc(sizeof(token_data_t) * 256)};
    lexer_t       lexer  = lexer_init(input_buffer, file_size);
    tokens               = lex(&lexer, tokens);

    free(input_buffer);
    free(lexer.input);
    free(tokens.token);
}
