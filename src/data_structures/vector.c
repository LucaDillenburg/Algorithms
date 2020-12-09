#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

#define INCREASE_RATIO 2

struct vector createVector(int length) {
  struct vector vector;
  vector.length = length;
  vector.last = -1;
  vector.array = (void **)malloc(sizeof(void *) * length);
  return vector;
}

void increaseVector(struct vector *vector, int newLength) {
  void **newArray = (void **)malloc(sizeof(void *) * newLength);
  int i;
  vector->length = newLength;
  for (i = 0; i <= vector->last; i++)
    newArray[i] = vector->array[i];
  free(vector->array);
  vector->array = newArray;
}

void pushToVector(struct vector *vector, void *item) {
  if (vector->last == vector->length - 1)
    increaseVector(vector, vector->length * INCREASE_RATIO);

  vector->last++;
  vector->array[vector->last] = item;
}

void freeInsideVector(struct vector vector) { free(vector.array); }
