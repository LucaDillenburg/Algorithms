#include "tests/tests.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_FILE_NAME 100

int main() {
  testGetWord();
  return 0;
}

int maina() {
  char file_name[MAX_LENGTH_FILE_NAME];
  FILE *file;

  scanf("%s", file_name);

  file = fopen(file_name, "r");
  while (1) {
    char *str = nextWordInFile(file);
    if (str == NULL)
      break;
    printf("'%s'\n", str);
    free(str);
  }

  return 0;
}
