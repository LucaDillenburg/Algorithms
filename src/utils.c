#include "utils.h"
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

int *newArrayOf(int *array, int begin, int last) {
  int *ret = newIntArray(last - begin + 1);
  int i;
  for (i = begin; i <= last; i++) {
    ret[i - begin] = array[i];
  }
  return ret;
}