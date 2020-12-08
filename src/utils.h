#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>

char *newString(char *str);
void printString(char *str);

char *nextWordInFile(FILE *file);
int strhashing(char *str);

#endif