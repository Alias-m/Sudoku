#include <stdio.h>
#include <stdlib.h>
#include "utils/File.h"
#include "Grid.h"

int main()
{
    Grid g;
    int size = 0;
    char* code = readFile("file.sdk", &size);
    parseSDK(&g, code, size);
    show(&g);
    printf("---\n\n\n");
    solve(&g);
    show(&g);
    return 0;
}
