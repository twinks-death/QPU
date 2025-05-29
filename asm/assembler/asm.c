#include "asm.h"
#include "lexer.c"

assembled_result_t assemble( char* input_file )
{
    printf("\nI'm gonna do sumn with %s", input_file);

    // Open the file and check if it exists
    FILE* file = fopen(input_file, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate buffer
    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        exit(1);
    }

    // TODO: remove later

    free(buffer);
    return {nullptr,0};
}