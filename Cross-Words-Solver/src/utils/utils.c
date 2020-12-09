#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
  if (a > b)
    return a;
  else
    return b;
}

char **cloneMatrix(char **base, int lines, int columns) {
  int i;
  char **matrix = (char **)malloc(sizeof(char *) * lines);
  for (i = 0; i < lines; i++) {
    int j;
    matrix[i] = (char *)malloc(sizeof(char) * columns);
    for (j = 0; j < columns; j++)
      matrix[i][j] = base[i][j];
  }
  return matrix;
}

void freeMatrix(char **matrix, int lines) {
  int i;
  for (i = 0; i < lines; i++)
    free(matrix[i]);
  free(matrix);
}
