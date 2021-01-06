#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char isCharWord(char c) {
  if (c >= 'a' && c <= 'z')
    return 1;
  if (c >= 'A' && c <= 'Z')
    return 1;
  if (c >= '0' && c <= '9')
    return 1;
  return 0;
}

char *nextWordInFile(FILE *file, int *cur_word_line_index) {
  char *buff = (char *)malloc(sizeof(char) * MAX_LENGTH_WORD);
  int length = 0;

  while (1) {
    char c = fgetc(file);
    if (c == EOF) {
      if (length == 0)
        return NULL;
      break;
    }

    if ((c == '-' && length != 0) || isCharWord(c)) {
      buff[length] = c;
      length++;
    } else {
      if (length != 0) {
        ungetc(c, file);
        break;
      } else if (c == '\n')
        (*cur_word_line_index)++;
    }
  }

  while (buff[length - 1] == '-')
    length--;
  buff[length] = '\0';
  return buff;
}

#define HASH_MULTIPLIER 31
#define INITIAL_NUMBER_HASH 0

/* Algorithm developed by Bernstein (1991). More information in
 * http://www.cse.yorku.ca/~oz/hash.html (cit. on p. 9). */
unsigned int hashForString(char *str) {
  unsigned int hash = INITIAL_NUMBER_HASH;
  int i;
  for (i = 0; str[i] != '\0'; i++)
    hash = hash * HASH_MULTIPLIER + (int)str[i];
  return hash;
}

char stringIsEqualTo(char *str1, char *str2) { return !strcmp(str1, str2); }

void swap(struct hashcell **a, struct hashcell **b) {
  struct hashcell *x = *a;
  *a = *b;
  *b = x;
}

int cellscmp(struct hashcell *a, struct hashcell *b) {
  return strcmp((char *)a->key, (char *)b->key);
}

void quickSort(struct hashcell **array, int begin, int last) {
  struct hashcell *pivot;
  int nextSmaller, indexPivot, i;

  if (begin >= last)
    return;
  if (begin + 1 == last) {
    if (cellscmp(array[begin], array[last]) > 0)
      swap(&array[begin], &array[last]);
    return;
  }

  pivot = array[last];

  nextSmaller = begin;
  for (i = begin; i <= last; i++)
    if (cellscmp(array[i], pivot) <= 0)
      swap(&array[i], &array[nextSmaller++]);

  indexPivot = nextSmaller - 1;
  quickSort(array, begin, indexPivot - 1);
  quickSort(array, indexPivot + 1, last);
}

/* Using QuickSort algorithm */
void sortCells(struct hashcell **array, int last) { quickSort(array, 0, last); }
