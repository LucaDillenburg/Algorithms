#include "quickSort.h"

void quickSort(int *array, int begin, int last, infoSortExec *infoSortExec) {
  int pivot, nextSmaller, indexPivot, i;

  if (begin >= last)
    return;
  if (begin + 1 == last) {
    infoSortExec->amntComparisons++;
    if (array[begin] > array[last]) {
      infoSortExec->amntSwitches++;
      swap(&array[begin], &array[last]);
    }
    return;
  }

  pivot = array[last];

  nextSmaller = begin;
  for (i = begin; i <= last; i++) {
    infoSortExec->amntComparisons++;
    if (array[i] <= pivot) {
      infoSortExec->amntSwitches++;
      swap(&array[i], &array[nextSmaller++]);
    }
  }

  indexPivot = nextSmaller - 1;
  quickSort(array, begin, indexPivot - 1, infoSortExec);
  quickSort(array, indexPivot + 1, last, infoSortExec);
}
