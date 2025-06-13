/*==============================================================================
 Copyright (c) 2025 Twink's Death
 SPDX-License-Identifier: BSD-3-Clause
 See the LICENSE file in repo's root for details.

 qpu8_emu: lexer.c
 =============================================================================*/

// Project headers
#include "assembler/lexer.h"

// Initialize all values inside of lexer struct, and return lexer_t for caller
lexer_t
lexer_init ( const char* input, size_t input_size )
{
    lexer_t lexer;
    lexer.input      = input;
    lexer.input_size = input_size;
    lexer.location   = (location_t){.line = 1, .col = 1};
    lexer.index      = 0;

    return lexer;
}

static const char*
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

static void
print_tokens ( token_array_t* t )
{
    for (int i = 0; i < t->count; i++) {
        printf("\n[%s, '%.*s', (%llu:%llu)]", token_id(&t->token[i]), (int) t->token[i].length, t->token[i].value,
               t->token[i].location.line, t->token[i].location.col);
    }
}

static void
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

// Increment lexer index smartly, reset collumn & increment line num if new line
// and skip whitespace Pass: lexer instance
static void
lexer_skip_whitespace ( lexer_t* l )
{
    while (l->index < l->input_size) {
        char c = l->input[l->index];
        if (c == ' ' || c == '\t') {
            l->index++;
            l->location.col++;
        } else if (c == '\r') {
            // Handle CRLF or just CR
            if (l->index + 1 < l->input_size && l->input[l->index + 1] == '\n') {
                l->index += 2;
            } else {
                l->index++;
            }
            l->location.line++;
            l->location.col = 1;
        } else if (c == '\n') {
            l->index++;
            l->location.line++;
            l->location.col = 1;
        } else {
            break;
        }
    }
}

static void
add_token ( token_data_t* dest, token_t type, const char* value, size_t length )
{
    dest->type   = type;
    dest->value  = value;
    dest->length = length;
}

static token_data_t
lexer_next ( lexer_t* l )
{
    lexer_skip_whitespace(l);

    token_data_t token = {.length = 0, .location = l->location};

    // out of chars
    if (l->index >= l->input_size) return token;
    // Directive
    if (l->input[l->index] == '.') {
        lexer_advance(l);
        if (is_symbol_start(l->input[l->index])) {
            size_t start = l->index;
            while (l->index < l->input_size && is_symbol(l->input[l->index])) {
                lexer_advance(l);
                token.length++;
            }
            add_token(&token, TOK_DIRECTIVE, &l->input[start], token.length);
            return token;
        }
        fprintf(stderr, "\nInvalid directive name! At [%llu:%llu]", l->location.line, --l->location.col);
    } else { l->index++; }

    return (token_data_t){
        .type = TOK_UNKNOWN, .value = &l->input[l->index - 1],
        .length = 5, .location = l->location
    };
}

token_array_t
lex ( lexer_t* lexer, token_array_t tokens )
{
    while (1) {
        token_data_t new_token = lexer_next(lexer);
        // check if tokens is out of heap
        if (tokens.count >= tokens.capacity) {
            tokens.capacity *= 2;
            tokens.token = realloc(tokens.token, sizeof(token_data_t) * tokens.capacity);
            if (!tokens.token) {
                perror("Out of memory for tokens");
                exit(1);
            }
        }

        tokens.token[tokens.count++] = new_token;
        if (new_token.type == TOK_EOF) break;
    }

    printf("\nInput: '%s'\nSize: %llu", lexer->input, lexer->input_size);
    print_tokens(&tokens);

    return tokens;
}
