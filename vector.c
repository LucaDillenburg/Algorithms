#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Vector createVector(int length) {
  struct Vector vector;
  vector.length = length;
  vector.last = -1;
  vector.array = (void **)malloc(sizeof(void *) * length);
  return vector;
}

void pushToVector(struct Vector *vector, void *item) {
  vector->last++;
  vector->array[vector->last] = item;
}

void *popFromVector(struct Vector *vector) {
  void *p = vector->array[vector->last];
  vector->last--;
  return p;
}

void printStrVector(struct Vector vector) {
  int i;
  for (i = 0; i <= vector.last; i++)
    printf("%s\n", (char *)vector.array[i]);
}

void freeVector(struct Vector vector) { free(vector.array); }
