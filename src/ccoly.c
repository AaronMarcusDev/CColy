#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../lib/filetools/filetools.h"
#include "../lib/boolconv/boolconv.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <file>", argv[0]);
        exit(1);
    }

    if (!fileExists(argv[1])) {
        printf("File `%s` does not exist", argv[1]);
        exit(1);
    }

    char *source = readFile(argv[1]);
    printf("%s\n", source);

    return 0;
}