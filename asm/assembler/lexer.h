#ifndef LEXER_H
#define LEXER_H

// Header kindly adapted from https://github.com/wzid/phi/blob/main/include/lexer.h
// Written by wzid, or Brain Tickle on YT.

typedef enum {
    // End of file
    TOK_EOF = 0,

    // Opcode - Operands
    TOK_MNEMONIC,
    TOK_REGISTER,

    // Bitwise operations
    TOK_NOT,                // !
    TOK_AND,                // &
    TOK_OR,                 // |
    TOK_XOR,                // ^

    // Separators, or punctuation
    TOK_LPAREN,             // (
    TOK_RPAREN,             // )
    TOK_LBRACKET,           // [
    TOK_RBRACKET,           // ]
    TOK_COMMA,              // ,

    // Operators
    TOK_PLUS,               // +
    TOK_MINUS,              // -
    TOK_STAR,               // *
    TOK_SLASH,              // /
    TOK_MOD,                // %
    TOK_POINT,              // >
    TOK_LEFTSHIFT,          // <<
    TOK_RIGHTSHIFT,         // >>

    // Special
    TOK_DIRECTIVE,          // .org .text .data .define .include
    TOK_TYPE,               // db, dw, dd
    TOK_CHAR,               // 'a'
    TOK_STRING,             // "hi"
    TOK_INTEGER,            // 0x, 0d, or 0b
    TOK_IDENTIFIER          // Name of variable or label
} token_t;

typedef struct {
    size_t line;
    size_t col;
} location_t;

typedef struct {
    token_t type;           // The type of the token
    char *val;              // The value of the token
    location_t location;    // The location of the token
} token_data_t;

typedef struct {
    char *start_tok;
    char *cur_tok;
    token_data_t *tokens;
    size_t token_count;
    size_t capacity;
    size_t line_number;
    char *line_start;
} lexer_t;

#endif //LEXER_H
