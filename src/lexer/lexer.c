// std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// custom
#include "lexer.h"
#include "../token/token.h"
#include "../parser/parser.h"
#include "../compiler/compiler.h"
#include "../../lib/vc_vector/vc_vector.h"

// lexer
void lexer(char *file, char *source)
{
    int sourceLength = strlen(source);

    vc_vector *tokens = vc_vector_create(0, sizeof(struct token), NULL);

    if (!tokens)
    {
        printf("[INTERNAL ERROR]: lexer: Could not create vc_vector `tokens`.\n");
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
            if (i != sourceLength)
            {
                if (source[i + 1] == '+')
                {
                    i++;
                    struct token tok;
                    tok.line = line;
                    tok.type = TOKENTYPE_OPERATOR;
                    tok.value = "++";
                    vc_vector_push_back(tokens, &tok);
                    break;
                }
            }
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "+";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '-':
        {
            if (i != sourceLength)
            {
                if (source[i + 1] == '-')
                {
                    i++;
                    struct token tok;
                    tok.line = line;
                    tok.type = TOKENTYPE_OPERATOR;
                    tok.value = "--";
                    vc_vector_push_back(tokens, &tok);
                    break;
                }
                else if (source[i + 1] >= '0' && source[i + 1] <= '9')
                {
                    i++;
                    char *number = malloc(1);
                    number[0] = '-';
                    int numberLength = 1;
                    while (source[i] >= '0' && source[i] <= '9')
                    {
                        number = realloc(number, numberLength + 1);
                        number[numberLength] = source[i];
                        numberLength++;
                        i++;
                    }
                    number = realloc(number, numberLength + 1);
                    number[numberLength] = '\0';
                    struct token tok;
                    tok.line = line;
                    tok.type = TOKENTYPE_INT;
                    tok.value = number;
                    vc_vector_push_back(tokens, &tok);
                    break;
                }
            }
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "-";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '*':
        {
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "*";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '/':
        {
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "/";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '%':
        {
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "%";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '=':
        {
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "=";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '!':
        {
            if (i != sourceLength)
            {
                if (source[i + 1] == '=')
                {
                    i++;
                    struct token tok;
                    tok.line = line;
                    tok.type = TOKENTYPE_OPERATOR;
                    tok.value = "!=";
                    vc_vector_push_back(tokens, &tok);
                    break;
                }
            }
            printf("[ERROR] %s:%d, Illegal character `!`.\n", file, line);
            break;
        }
        case '>':
        {
            if (i != sourceLength)
            {
                if (source[i + 1] == '=')
                {
                    i++;
                    struct token tok;
                    tok.line = line;
                    tok.type = TOKENTYPE_OPERATOR;
                    tok.value = ">=";
                    vc_vector_push_back(tokens, &tok);
                    break;
                }
            }
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = ">";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '<':
        {
            if (i != sourceLength)
            {
                if (source[i + 1] == '=')
                {
                    i++;
                    struct token tok;
                    tok.line = line;
                    tok.type = TOKENTYPE_OPERATOR;
                    tok.value = "<=";
                    vc_vector_push_back(tokens, &tok);
                    break;
                }
            }
            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_OPERATOR;
            tok.value = "<";
            vc_vector_push_back(tokens, &tok);
            break;
        }
        case '"':
        {
            int startLine = line;
            i++;
            int start = i;
            while (source[i] != '"')
            {
                if (source[i] == '\n')
                    line++;
                i++;
                if (i == sourceLength)
                {
                    printf("[ERROR] %s:%d, Unterminated string.\n", file, startLine);
                    return;
                }
            }

            int end = i;

            char *value = malloc(end - start);
            if (!value)
            {
                printf("[INTERNAL ERROR]: lexer: Could not allocate memory for token value.");
            }
            memcpy(value, source + start, end - start);
            value[end - start] = '\0';

            struct token tok;
            tok.line = line;
            tok.type = TOKENTYPE_STRING;
            tok.value = value;
            vc_vector_push_back(tokens, &tok);
            break;
        }

        default:
        {
            if (source[i] >= '0' && source[i] <= '9')
            {
                int dots = 0;
                bool fastBreak = false;
                bool isFloat = false;
                char *number = malloc(1);
                number[0] = source[i];
                int numberLength = 1;
                while (source[i + 1] >= '0' && source[i + 1] <= '9' || source[i + 1] == '.')
                {
                    i++;
                    if (source[i] == '.')
                    {
                        if (dots == 0)
                        {
                            dots++;
                            isFloat = true;
                        }
                        else if (dots == 1)
                        {
                            printf("[ERROR] %s:%d, Illegal character `.`.\n", file, line);
                            fastBreak = true;
                            break;
                        }
                    }
                    number = realloc(number, numberLength + 1);
                    number[numberLength] = source[i];
                    numberLength++;
                }
                if (fastBreak)
                    break;

                number = realloc(number, numberLength + 1);
                number[numberLength] = '\0';
                struct token tok;
                tok.line = line;
                if (isFloat)
                {
                    tok.type = TOKENTYPE_FLOAT;
                }
                else
                {
                    tok.type = TOKENTYPE_INT;
                }
                tok.value = number;
                vc_vector_push_back(tokens, &tok);
                break;
            }
            else if (source[i] >= 'a' && source[i] <= 'z' || source[i] >= 'A' && source[i] <= 'Z' || source[i] == '_')
            {
                char *identifier = malloc(1);
                identifier[0] = source[i];
                int identifierLength = 1;
                while (source[i + 1] >= 'a' && source[i + 1] <= 'z' || source[i + 1] >= 'A' && source[i + 1] <= 'Z' || source[i + 1] >= '0' && source[i + 1] <= '9' || source[i + 1] == '_')
                {
                    i++;
                    identifier = realloc(identifier, identifierLength + 1);
                    identifier[identifierLength] = source[i];
                    identifierLength++;
                }
                identifier = realloc(identifier, identifierLength + 1);
                identifier[identifierLength] = '\0';
                struct token tok;
                tok.line = line;
                tok.type = TOKENTYPE_IDENTIFIER;
                tok.value = identifier;
                vc_vector_push_back(tokens, &tok);
                break;
            }
            else
            {
                printf("[ERROR] %s:%d, Illegal character `%c`.\n", file, line, source[i]);
                break;
            }
        }
        }
    }

    // lexer(tokens);
    compiler(tokens);
    vc_vector_release(tokens);
}