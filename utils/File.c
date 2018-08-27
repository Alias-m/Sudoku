#include "File.h"

char* xcalloc(const int element)
{
    char *ptr = NULL;
    if( (ptr = (char*)calloc(element, sizeof(char))) == NULL)
    {
        printf(ERROR_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

char* append(char *input, const char c)
{
    char *newStr, *ptr;
    newStr = xcalloc((strlen(input) + 2));
    ptr = newStr;
    int i;
    for(i = 0; input[i] ; ++i)
        *(ptr++) = input[i];
    *(ptr++) = c;
    *ptr = 0;
    free(input);
    return newStr;
}


char* readLine(const char* code, int* i)
{
    char* line = xcalloc(1);
    for(; code[*i] != '\n' && code[*i]; (*i)++)
        line = append(line, code[*i]);
    return line;
}

char* readFile(const char* fileName, int* size)
{
    FILE* file = NULL;
    file = fopen(fileName, "r");
    char* code = xcalloc(20);
    if (file != NULL)
    {
        char i;
        while((i=fgetc(file))!=EOF)
        {
            code = append(code, i);
            (*size)++;
        }
    }
    else
        printf(ERROR_NOT_FOUND, fileName);
    fclose(file);
    #if FILE_DEBUG
        DEBUG_OUVERTURE
    #endif // FILE_DEBUG
    return code;
}

void closeCode(char* code)
{
    free(code);
    #if FILE_DEBUG
        DEBUG_CLOSURE
    #endif // FILE_DEBUG
}
