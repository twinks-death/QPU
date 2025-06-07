#ifndef TESTS_H
#define TESTS_H

// Standard library
#include <stdbool.h>
#include <time.h>

// Project headers
#include <assembler/lexer.h>

// Defines for prettines
#define COLOR_RED        "\033[0;31m"
#define COLOR_GREEN      "\033[0;32m"
#define COLOR_RESET      "\033[0m"
#define PASS COLOR_GREEN "[PASS]" COLOR_RESET
#define FAIL COLOR_RED   "[FAIL]" COLOR_RESET

// For execution time
#define TOTAL_TIME ( (double)(end-start) / CLOCKS_PER_SEC )

// Test result structure, will be printed once finished
typedef struct {
    bool   passed;
    char*  message;
    double execution_time;
    // todo: add more
} test_result_t;

// In tests.c
test_result_t test_lexer ( lexer_t* lexer );

#endif //TESTS_H
