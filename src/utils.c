#include "utils.h"
#include <stdlib.h>

/* TODO: REMOVE THIS */
char *newString(char *str) {
  char *new_str = (char *)malloc(sizeof(char) * 100);
  int i;
  for (i = 0;; i++)
    if (str[i] == '\0')
      break;
    else
      new_str[i] = str[i];
  return new_str;
}

void printString(char *str) { printf("%s", str); }
