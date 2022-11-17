// std
#include <stdio.h>
#include <string.h>
// custom
#include "lexer/lexer.h"
#include "../lib/filetools/filetools.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("[ERROR] Invalid arguments.\n");
        printf("[INFOR] Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    if (!fileExists(argv[1]))
    {
        printf("File `%s` does not exist.\n", argv[1]);
        exit(1);
    }

    char *source = readFile(argv[1]);
    lexer(argv[1], source);

    return 0;
}