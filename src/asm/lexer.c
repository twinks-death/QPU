#include "assembler/lexer.h"

// Initialise all values inside of lexer struct, and return lexer_t for caller
lexer_t lexer_init (const char* input, size_t input_size)
{
    lexer_t lexer;
    lexer.input      = input;
    lexer.input_size = input_size;

    lexer.location   = (location_t){1, 0};
    lexer.index      = 0;

    return lexer;
}

static int
is_newline(char c)
{
    return (c == '\n' || c == '\r');
}

// Increment lexer index smartly, reset collumn & increment line num if new line
// Pass: lexer instance
static void
lexer_advance (lexer_t* lexer)
{
    if (lexer->index < lexer->input_size)
    {
        lexer->index += 1;

        if (is_newline(lexer->input[lexer->index])) {
            lexer->location.line += 1;
            lexer->location.col = 1;
        } else {
            lexer->location.col += 1;
        }
    }
}

// Pass: address to token
// Return: type of token as a char*
static const char*
token_id (token_data_t* token)
{
    switch (token->type)
    {
        case TOK_MNEMONIC:   return "Mnemonic";
        case TOK_REGISTER:   return "Register";

        case TOK_NOT:        return "Not";
        case TOK_AND:        return "And";
        case TOK_OR:         return "Or";
        case TOK_XOR:        return "Xor";

        case TOK_LPAREN:     return "LParen";
        case TOK_RPAREN:     return "RParen";
        case TOK_LBRACKET:   return "LBracket";
        case TOK_RBRACKET:   return "RBracket";
        case TOK_COMMA:      return "Comma";

        case TOK_PLUS:       return "Plus";
        case TOK_MINUS:      return "Minus";
        case TOK_STAR:       return "Star";
        case TOK_SLASH:      return "Slash";
        case TOK_MOD:        return "Mod";
        case TOK_POINT:      return "Point";
        case TOK_LEFTSHIFT:  return "LeftShift";
        case TOK_RIGHTSHIFT: return "RightShift";

        case TOK_DIRECTIVE:  return "Directive";
        case TOK_TYPE:       return "Type";
        case TOK_CHAR:       return "Char";
        case TOK_STRING:     return "String";
        case TOK_INTEGER:    return "Integer";
        case TOK_IDENTIFIER: return "Identifier";

        case TOK_EOF:        return "EOF";
        default:             return "Unknown";
    }
}

// Pass:   token
// Return: formatted
static void
print_token(token_data_t* token)
{
    const char* type = token_id(token);
    printf("\n[%llu:%llu] - %s: ", token->location.line, token->location.col,type);
    if (token->value != NULL)
        printf("'%s'", token->value);
}

static void
add_token(lexer_t* lexer, token_data_t token)
{
    ;
}

