#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

infoSortExec createInfoSortExec() {
  infoSortExec ret;
  ret.amntComparisons = 0;
  ret.amntMoves = 0;
  return ret;
}

void swap(int *a, int *b) {
  int x = *a;
  *a = *b;
  *b = x;
}

int *newIntArray(int length) { return (int *)malloc(sizeof(int) * length); }

double randBetween(double min, double max) {
  double r = (double)rand();
  double div = r / RAND_MAX;
  double result = min - div * min + div * max;
  return result;
}

void printArray(int *array, int length) {
  int i;
  for (i = 0; i < length; i++)
    printf("%d ", array[i]);
}

int *copyOf(int *array, int begin, int last) {
  int *ret = newIntArray(last - begin + 1);
  int i;
  for (i = begin; i <= last; i++) {
    ret[i - begin] = array[i];
  }
  return ret;
}
