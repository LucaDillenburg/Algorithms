#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

#define INCREASE_RATIO 2

struct Vector createVector(int length) {
  struct Vector vector;
  vector.length = length;
  vector.last = -1;
  vector.array = (void **)malloc(sizeof(void *) * length);
  return vector;
}

void increaseVector(struct Vector *vector, int newLength) {
  void **newArray = (void **)malloc(sizeof(void *) * newLength);
  int i;
  for (i = 0; i <= vector->last; i++)
    newArray[i] = vector->array[i];
  free(vector->array);
  vector->array = newArray;
}

void pushToVector(struct Vector *vector, void *item) {
  if (vector->last == vector->length - 1)
    increaseVector(vector, vector->length * INCREASE_RATIO);

  vector->last++;
  vector->array[vector->last] = item;
}

void pushItemsToVector(struct Vector *vector, struct Vector items) {
  int i;
  for (i = 0; i <= items.last; i++)
    pushToVector(vector, items.array[i]);
}

void *popFromVector(struct Vector *vector) {
  void *p = vector->array[vector->last];
  vector->last--;
  return p;
}

void printStrVector(struct Vector vector) {
  int i;
  for (i = 0; i <= vector.last; i++)
    printf("'%s', ", (char *)vector.array[i]);
}

char vectorIsEmpty(struct Vector vector) { return vector.last < 0; }

void freeVector(struct Vector vector) { free(vector.array); }
