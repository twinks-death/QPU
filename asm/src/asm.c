#include "../include/asm.h"
#include "../include/lexer.h"

assembled_result_t assemble( const char* input_file )
{
    FILE* file = fopen(input_file, "r");

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // Allocate buffer
    char *input_buffer = malloc(file_size + 1);
    if (!input_buffer)
    {
        perror("Error allocating memory");
        fclose(file);
        exit(1);
    }

    free(input_buffer);
    return (assembled_result_t){nullptr,0};
}