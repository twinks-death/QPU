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

// Simple line:col matrix
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

/* Token array instance:
     *token   - pointer to tokens stored in heap
     count    - total of tokens stored
     capacity - bytes allocated to *token in heap (256 by default, if out of heap then *= 2)
*/
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

// PRIVATE FUNCTIONS
static void         lexer_skip_whitespace ( lexer_t* l );
static void         add_token ( token_data_t* dest, token_t type, const char* value, size_t length );
static token_data_t lexer_next ( lexer_t* l );

static inline bool
is_symbol_start ( char x ) { return isalpha(x) || x == '_'; }

static inline bool
is_symbol ( char x ) { return isalnum(x) || x == '_'; }

static inline const char*
token_id ( token_data_t* t )
{
    switch (t->type) {
        case TOK_EOF: return "EOF";
        case TOK_MNEMONIC: return "Mnemonic";
        case TOK_REGISTER: return "Register";

        case TOK_NOT: return "Not";
        case TOK_AND: return "And";
        case TOK_OR: return "Or";
        case TOK_XOR: return "Xor";

        case TOK_LPAREN: return "LParen";
        case TOK_RPAREN: return "RParen";
        case TOK_LBRACKET: return "LBracket";
        case TOK_RBRACKET: return "RBracket";
        case TOK_COMMA: return "Comma";

        case TOK_PLUS: return "Plus";
        case TOK_MINUS: return "Minus";
        case TOK_STAR: return "Star";
        case TOK_SLASH: return "Slash";
        case TOK_MOD: return "Mod";
        case TOK_POINT: return "Point";
        case TOK_LEFTSHIFT: return "LeftShift";
        case TOK_RIGHTSHIFT: return "RightShift";

        case TOK_DIRECTIVE: return "Directive";
        case TOK_TYPE: return "Type";
        case TOK_CHAR: return "Char";
        case TOK_STRING: return "String";
        case TOK_INTEGER: return "Integer";
        case TOK_IDENTIFIER: return "Identifier";

        default: return "Unknown";
    }
}

/**
 * Prints all tokens from a given token array to the console. Each token is
 * displayed with its type (as a string), value, and location (line and column).
 *
 * @param t Pointer to a token array structure containing the tokens to be printed.
 *          The `token_array_t` should be properly initialized, with `token`,
 *          `count`, and `capacity` appropriately set.
 */
static inline void
print_tokens ( token_array_t* t )
{
    for (int i = 0; i < t->count; i++) {
        printf("\n[%s, '%.*s', (%llu:%llu)]", token_id(&t->token[i]), (int) t->token[i].length, t->token[i].value,
               t->token[i].location.line, t->token[i].location.col);
    }
}

/**
 * Prints a token's details, including its type, location, and value, to the console.
 * If the token is of an unknown type, an error message is printed to `stderr`.
 * For tokens with a non-null value, the text of the token is included in the output.
 * The output format varies depending on the token type and presence of a value.
 *
 * @param t Pointer to the token_data_t structure representing the token to be printed.
 *          The structure must contain a valid `type`, `location` (line and column),
 *          and optionally `value` and `length` if applicable.
 */
static inline void
print_t ( token_data_t* t )
{
    const char* type = token_id(t);
    if (t->value != NULL) {
        if (t->type == TOK_UNKNOWN) fprintf(stderr, "\n%s at [%llu:%llu], text: '%.*s...'", type, t->location.line, t->location.col, 5, t->value);
        else printf("\n%s at [%llu:%llu], text: '%.*s'", type, t->location.line, t->location.col, (int) t->length, t->value);
    } else {
        printf("\n%s at [%llu:%llu]", type, t->location.line, t->location.col);
    }
}

// PUBLIC FUNCTIONS

/**
 * Initializes a lexer structure for processing an input string. The lexer is
 * used to tokenize the input and keeps track of the current parsing position
 * and location within the input buffer.
 *
 * @param input Pointer to the input buffer containing the data to be tokenized.
 *              This buffer should be null-terminated or provide a valid size
 *              specified by `input_size`.
 * @param input_size The size of the input buffer in bytes. This defines the
 *                   total number of characters available for tokenization.
 * @return A fully initialized `lexer_t` structure, configured to start
 *         tokenizing from the beginning of the input buffer.
 */
lexer_t lexer_init ( const char* input, size_t input_size );

/**
 * Tokenizes the input provided to a lexer object and populates the given token array
 * with detected tokens. The function reads input until the end is reached, ensuring
 * that the token array has sufficient memory to store all tokens. Detected tokens
 * include their type, value, length, and location information.
 *
 * @param lexer Pointer to the `lexer_t` structure initialized with an input buffer and input size.
 *              It tracks the current position and state during tokenization.
 * @param tokens The `token_array_t` structure where tokens will be stored. The structure should
 *               have its `token`, `count`, and `capacity` fields properly initialized before calling.
 *               If the token array reaches capacity during tokenization, it is resized automatically.
 * @return The updated `token_array_t` structure with all discovered tokens populated. The final token
 *         added will be the end-of-file (EOF) token.
 */
token_array_t lex ( lexer_t* lexer, token_array_t tokens );

#endif // LEXER_H
