#ifndef LEXER_H
#define LEXER_H

// Header kindly adapted from https://github.com/wzid/phi/blob/main/include/lexer.h
// Written by wzid, or Brain Tickle on YT.

// Standard library
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "emulator/emu.h"


typedef enum {
    // Opcode - Operands
    TOK_MNEMONIC = 0,
    TOK_REGISTER,

    // Bitwise operations
    TOK_NOT,        // !
    TOK_AND,        // &
    TOK_OR,         // |
    TOK_XOR,        // ^

    // Separators, or punctuation
    TOK_LPAREN,     // (
    TOK_RPAREN,     // )
    TOK_LBRACKET,   // [
    TOK_RBRACKET,   // ]
    TOK_COMMA,      // ,

    // Operators
    TOK_PLUS,       // +
    TOK_MINUS,      // -
    TOK_STAR,       // *
    TOK_SLASH,      // /
    TOK_MOD,        // %
    TOK_POINT,      // >
    TOK_LEFTSHIFT,  // <<
    TOK_RIGHTSHIFT, // >>

    // Special
    TOK_DIRECTIVE,  // .org .text .data .define .include
    TOK_TYPE,       // db, dw, dd
    TOK_CHAR,       // 'a'
    TOK_STRING,     // "hi"
    TOK_INTEGER,    // 0x, 0d, or 0b
    TOK_IDENTIFIER, // Name of variable or label

    // End of file
    TOK_EOF
} token_t;

// Simple line:col matrix
typedef struct {
    size_t line;
    size_t col;
} location_t;

// Info per token
typedef struct {
    token_t    type;
    char*      value;
    location_t location;
} token_data_t;

typedef struct {
    token_data_t* token;
    size_t        count;
    size_t        capacity;
} token_array_t;

// Lexer instance structure
typedef struct {
    const char* input;      // pointer to input buffer (declared in asm.c)
    size_t      input_size; // Input size in bytes
    location_t  location;   // Location of current token being tokenized
    size_t      index;      // Current index of lexer
} lexer_t;

// PRIVATE
static const char*  token_id              (token_t* t);
static void         print_token           (token_data_t* t);
static void         lexer_skip_whitespcae (lexer_t* l);
static token_data_t add_token             (lexer_t* l);

// PUBLIC
lexer_t       lexer_init (const char* input, size_t input_size);
token_array_t lexer      (lexer_t* lexer);

#endif //LEXER_H
