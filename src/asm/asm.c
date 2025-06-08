/*==============================================================================
 qpu8_emu: asm.c, 2025-06-08, Sun 21:06+0100

 Copyright (C) 2025 Twink's Death

 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 =============================================================================*/

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
