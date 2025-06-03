#include "assembler/asm.h"
#include "assembler/lexer.h"

assembled_result_t assemble(const char* input_file)
{
    FILE* file = fopen(input_file, "r");

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // Allocate buffer
    char* input_buffer = malloc(file_size + 1);
    if (!input_buffer)
    {
        perror("Malloc failed bruh");
        fclose(file);
        exit(1);
    }

    // Copy all of input_file into input_buffer and add null terminator
    fread(input_buffer, 1, file_size, file);
    input_buffer[file_size] = '\0';
    fclose(file);

    // create lexer instance
    lexer_t lexer = lexer_init(file_size);

    free(input_buffer);
    return (assembled_result_t){nullptr,0};
}