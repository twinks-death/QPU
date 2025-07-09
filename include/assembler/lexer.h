/*==============================================================================
 Copyright (c) 2025 Twink's Death
 SPDX-License-Identifier: BSD-3-Clause
 See the LICENSE file in repo's root for details.

 qpu8_emu: lexer.h
 =============================================================================*/

#ifndef LEXER_H
#define LEXER_H

// Standard library
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Project headers
#include "emulator/emu.h"

typedef enum {
    // End of file
    TOK_EOF = 0,

    // Opcode - Operands
    TOK_MNEMONIC,
    TOK_REGISTER,

    // Bitwise operations
    TOK_NOT, // !
    TOK_AND, // &
    TOK_OR,  // |
    TOK_XOR, // ^

    // Separators, or punctuation
    TOK_LPAREN,   // (
    TOK_RPAREN,   // )
    TOK_LBRACKET, // [
    TOK_RBRACKET, // ]
    TOK_COMMA,    // ,

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
    TOK_UNKNOWN
} token_t;

// Simple line:col vector
typedef struct {
    size_t line;
    size_t col;
} location_t;

// Info per token
typedef struct {
    token_t     type;
    const char* value;
    size_t      length;
    location_t  location;
} token_data_t;

// Token array instance
typedef struct {
    token_data_t* token;    // pointer to tokens stored in heap
    size_t        count;    // total of tokens stored
    size_t        capacity; // bytes allocated to *token in heap (256 by default, if out of heap, then *= 2)
} token_array_t;

// Lexer instance structure
typedef struct {
    const char* input;      // pointer to input buffer (declared in asm.c)
    size_t      input_size; // Input size in bytes
    location_t  location;   // Location of the current token being tokenised
    size_t      index;      // Current index of lexer
} lexer_t;

// PRIVATE FUNCTIONS
static void         lexer_skip_whitespace ( lexer_t* l );
static void         add_token ( token_data_t* dest, token_t type, const char* value, size_t length );
static token_data_t lexer_next ( lexer_t* l );

static inline bool
is_symbol_start ( char x ) { return isalpha(x) || x == '_'; }

static inline bool
is_symbol ( char x ) { return isalnum(x) || x == '_'; }

static inline void
lexer_advance ( lexer_t* l )
{
    l->index++;
    l->location.col++;
}



// PUBLIC FUNCTIONS

lexer_t       lexer_init ( const char* input, size_t input_size );
token_array_t lex ( lexer_t* lexer, token_array_t tokens );

#endif // LEXER_H
