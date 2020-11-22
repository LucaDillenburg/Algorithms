#ifndef UTILS_SORT_H
#define UTILS_SORT_H

typedef struct InfoSortExec {
  int amntComparisons;
  int amntSwitches;
} infoSortExec;

infoSortExec createInfoSortExec();
void swap(int *a, int *b);
int *newIntArray(int length);
int *newArrayOf(int *array, int begin, int last);

#endif