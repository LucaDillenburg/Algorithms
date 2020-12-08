#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

#define MAX_LENGTH_WORD 100

char *nextWordInFile(FILE *file);
unsigned int hashForString(char *str);

#endif