#ifndef FILE_H
#define FILE_H
#define FILE_DEBUG 0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEBUG_OUVERTURE printf("File loaded : %d bytes.\n", *size);
#define DEBUG_CLOSURE printf("\nCode closed.\n");
#define ERROR_NOT_FOUND "File not found : %s\n"
#define ERROR_NOT_ENOUGH_MEMORY "Not enough memory."

char* readFile(const char* fileName, int* size);
char* readLine(const char* code, int* i);
void closeCode(char* code);
char* append(char *input, const char c);
char* xcalloc(const int element);
#endif // FILE_H
