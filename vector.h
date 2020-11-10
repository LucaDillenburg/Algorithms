#ifndef ARRAY_H
#define ARRAY_H

typedef struct Vector {
  void **array;
  int length;
  int last;
} vector;

struct Vector createVector(int length);
void increaseVector(struct Vector *vector, int newLength); /* TODO: TEST */
void pushToVector(struct Vector *vector, void *item);
void pushItemsToVector(struct Vector *vector, struct Vector items);
void *popFromVector(struct Vector *vector);
void printStrVector(struct Vector vector);
char vectorIsEmpty(struct Vector vector);
void freeVector(struct Vector vector);

#endif