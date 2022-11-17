// std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// custom
#include "parser.h"
#include "../token/token.h"
#include "../../lib/vc_vector/vc_vector.h"

char *btos(int b) {
    return b ? "true" : "false";
}

void parser(vc_vector *tokens)
{
    vc_vector *AST = vc_vector_create(0, sizeof(struct token), NULL);

    for (void *i = vc_vector_begin(tokens); i != vc_vector_end(tokens); i = vc_vector_next(tokens, i))
    {
        bool isAtEnd() { return i == vc_vector_end(tokens); }
        char *value = (((struct token *)i)->value);
        int type = (((struct token *)i)->type);
        int line = (((struct token *)i)->line);

        {
            // printf("%s" );
            printf("%s\n", btos(isAtEnd()));
            // struct token tok;
            // tok.line = line;
            // tok.type = type;
            // tok.value = value;
            // vc_vector_push_back(tokens, &tok);
        }
    }
}