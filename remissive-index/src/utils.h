#ifndef _UTILS_H
#define _UTILS_H

#include "data_structures/hashtable.h"
#include <stdio.h>

#define MAX_LENGTH_WORD 100

char *nextWordInFile(FILE *file, int *next_word_line_index);
unsigned int hashForString(char *str);
char stringIsEqualTo(char *str1, char *str2);
void sortCells(struct hashcell **array, int last);

#endif