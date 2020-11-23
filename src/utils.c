#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

infoSortExec createInfoSortExec() {
  infoSortExec ret;
  ret.amntComparisons = 0;
  ret.amntSwitches = 0;
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
