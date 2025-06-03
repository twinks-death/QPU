#include "assembler/lexer.h"

// Initialise all values inside of lexer struct, and return lexer_t for caller
lexer_t lexer_init (size_t input_size)
{
    lexer_t lexer;
    lexer.input_size = input_size;
    lexer.location   = (location_t){0, 0};
    lexer.index      = 0;

    return lexer;
}

int is_newline(char c)
{
    return (c == '\n' || c == '\r');
}

void lexer_advance (lexer_t* lexer)
{
    if (lexer->index < lexer->input_size)
        lexer->index += 1;
    else if ()
}

const char* token_id(token_t type)
{
    switch (type)
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

void print_token(token_data_t token)
{
    const char* type = token_id(token.type);
    printf("%s ", type);
    if (token.value != NULL)
        printf("(%s)", token.value);
    printf("\n");
}