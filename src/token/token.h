enum TokenType
{
    TOKENTYPE_EOF,
    TOKENTYPE_INT,
    TOKENTYPE_FLOAT,
    TOKENTYPE_STRING,
    TOKENTYPE_CHAR,
    TOKENTYPE_IDENTIFIER,
    TOKENTYPE_KEYWORD,
    TOKENTYPE_OPERATOR,
};

struct token
{
    int line;
    int type;
    char *value;
};