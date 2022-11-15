// std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// custom
#include "lexer.h"
#include "../token/token.h"
#include "../../lib/vc_vector/vc_vector.h"

// lexer
void lexer(char *file, char *source)
{
    int sourceLength = strlen(source);

    vc_vector *tokens = vc_vector_create(0, sizeof(struct token), NULL);

    if (!tokens)
    {
        printf("[INTERNAL ERROR]: lexer: Could not create vc_vector `tokens`.");
    }

    int line = 1;

    for (int i = 0; i < sourceLength; i++)
    {
        switch (source[i])
        {
        case ' ':
            break;
        case '\t':
            break;
        case '\r':
            break;
        case '\n':
            line++;
            break;
        case '+':
        {
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "+";
            vc_vector_push_back(tokens, &tok);
        }
        break;
        case '/':
        {
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "/";
            vc_vector_push_back(tokens, &tok);
        }
        break;
        default:
            printf("[ERROR] %s:%d, Illegal character `%c`\n", file, line, source[i]);
            break;
        }
    }

    for (void *i = vc_vector_begin(tokens); i != vc_vector_end(tokens); i = vc_vector_next(tokens, i))
    {
        printf("%s", ((struct token *)i)->value);
    }

    vc_vector_release(tokens);
}