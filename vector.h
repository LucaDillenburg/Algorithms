#ifndef ARRAY_H
#define ARRAY_H

typedef struct Vector {
  void **array;
  int length;
  int last;
} vector;

struct Vector createVector(int length);
void pushToVector(struct Vector *vector, void *item);
void printStrVector(struct Vector vector);
void freeVector(struct Vector vector);

#endif