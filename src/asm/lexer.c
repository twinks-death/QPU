#include "assembler/lexer.h"

// Pass: address to token
// Return: type of token as a char*
static const char*
token_id (token_data_t* t)
{
    switch (t->type)
    {
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

        case TOK_EOF: return "EOF";
        default: return "Unknown";
    }
}

// Pass:   address to token
// Return: formatted
static void
print_token (token_data_t* t)
{
    const char* type = token_id(t);
    printf("\n[%llu:%llu] - %s: ", t->location.line, t->location.col, type);
    if (t->value != NULL)
        printf("'%s'", t->value);
}

// Initialize all values inside of lexer struct, and return lexer_t for caller
lexer_t lexer_init (const char* input, size_t input_size)
{
    lexer_t lexer;
    lexer.input      = input;
    lexer.input_size = input_size;
    lexer.location   = (location_t){.line = 0, .col = 1};
    lexer.index      = 0;

    return lexer;
}

// Increment lexer index smartly, reset collumn & increment line num if new line and skip whitespace
// Pass: lexer instance
static void
lexer_skip_whitespace (lexer_t* l)
{
    while (l->index < l->input_size)
    {
        char c = l->input[l->index++];
        if ( c == ' ' || c == '\t' || c == '\r' || c == '\n' ) {
            if (c == '\n' || c == '\r') {
                l->location.line++;
                l->location.col = 1;
            } else {
                l->location.col++;
            }
            l->index++;
        } else {
            break;
        }
    }
}

static token_data_t
add_token (lexer_t* l)
{
    token_data_t token = {.location = l->location};
    return token;
}

token_array_t
lexer (lexer_t* lexer)
{
    token_array_t tokens =
    {.count = 0, .capacity = 256, .token = malloc(sizeof(token_data_t) * 256)};

    while (tokens.token->type != TOK_EOF)
    {
        token_data_t new_token = add_token(lexer);

        // check if tokens is out of heap
        if (tokens.count >= tokens.capacity)
        {
            tokens.capacity *= 2;
            tokens.token = realloc(tokens.token, sizeof(token_data_t) * tokens.capacity);
            if (!tokens.token)
            {
                perror("Out of memory for tokens");
                exit(1);
            }
        }

        tokens.token[tokens.count++] = new_token;
        lexer_advance(lexer);
    }

    return tokens;
}

