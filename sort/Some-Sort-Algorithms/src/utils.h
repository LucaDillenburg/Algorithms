#ifndef UTILS_SORT_H
#define UTILS_SORT_H

typedef struct InfoSortExec {
  int amntComparisons;
  int amntMoves;
} infoSortExec;

infoSortExec createInfoSortExec();
void swap(int *a, int *b);
int *newIntArray(int length);
double randBetween(double min, double max);
void printArray(int *array, int length);
int *copyOf(int *array, int begin, int last);

#endif