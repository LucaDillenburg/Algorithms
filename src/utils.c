#include "utils.h"
#include <stdlib.h>

char isEndOfWord(char c, int length_before_char) {
  if (c >= 'a' && c <= 'z')
    return 0;
  if (c >= 'A' && c <= 'Z')
    return 0;
  if (c == '-' && length_before_char != 0)
    return 0;
  return 1;
}

char *nextWordInFile(FILE *file) {
  char *buff = (char *)malloc(sizeof(char) * MAX_LENGTH_WORD);
  int length = 0;

  while (1) {
    char c = fgetc(file);
    if (c == EOF) {
      if (length == 0)
        return NULL;
      break;
    }
    if (isEndOfWord(c, length)) {
      if (length > 0)
        break;
      continue;
    }

    buff[length] = c;
    length++;
  }

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
