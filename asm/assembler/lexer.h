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
    TOK_IDENTIFIER,         // Name of variable or label
    TOK_INVALID             // Unkown token
} token_t;

// Simple line:col matrix
typedef struct {
    size_t line;
    size_t col;
} location_t;

// Info per token
typedef struct {
    token_t type;               // The type of the token
    char* string_value;         // The value of token if it's a string
    int int_value;              // The value of token if it's a integer
    size_t len;                 // Length of string value provided
    location_t location;        // The location of the token
} token_data_t;

// Lexer instance structure
typedef struct {
    char* input;                // Input buffer, read from file path
    size_t input_size;          // Input size in bytes

    token_data_t* tokens;       // Array of tokens
    size_t token_count;         // Total amount of tokens
    size_t tokens_capacity;     // Bytes allocated to tokens

    size_t line_number;         // Current line number
    size_t beginning_of_line;   // Collumn = cursor - beginning of line
    size_t cursor;              // Cursor position
} lexer_t;



#endif //LEXER_H
