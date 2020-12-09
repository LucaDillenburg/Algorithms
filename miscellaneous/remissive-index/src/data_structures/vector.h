#ifndef _ARRAY_H
#define _ARRAY_H

typedef struct vector {
  void **array;
  int length;
  int last;
} vector;

struct vector createVector(int length);
void pushToVector(struct vector *vector, void *item);
void freeInsideVector(struct vector vector);

#endif