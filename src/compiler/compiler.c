// std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// custom
#include "../../lib/filetools/filetools.h"
#include "../../lib/vc_vector/vc_vector.h"
#include "../token/token.h"
// def
#define OUTPUT_FILE "./build.exe"

void writeOutput(char *val) {
    char *content;
    strcat(content, "\n");
    writeFile(OUTPUT_FILE, content);
}

void compiler(vc_vector *tokens)
{
    if (!fileExists(OUTPUT_FILE))
    {
        createFile(OUTPUT_FILE);
    }
    emptyFile(OUTPUT_FILE);

    for (void *i = vc_vector_begin(tokens); i != vc_vector_end(tokens); i = vc_vector_next(tokens, i))
    {
        char *value = (((struct token *)i)->value);
        int type = (((struct token *)i)->type);
        int line = (((struct token *)i)->line);
    
        writeOutput(value);
    }
}