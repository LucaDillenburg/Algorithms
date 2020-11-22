#include "insertionSort.h"
#include <stdlib.h>

void sortedInsert(int *array, int lastSorted, infoSortExec *infoSortExec,
                  int value) {
  int i;
  int insertIndex = -1;

  for (i = lastSorted; i >= 0; i--) {
    infoSortExec->amntComparisons++;
    if (value >= array[i]) {
      insertIndex = i;
      break;
    }
  }

  for (i = lastSorted + 1; i > insertIndex; i--) {
    infoSortExec->amntSwitches++;
    array[i] = array[i - 1];
  }
  array[insertIndex] = value;
  infoSortExec->amntSwitches++;
}

void insertionSort(int *array, int length, infoSortExec *infoSortExec) {
  int i;
  for (i = 0; i < length; i++)
    sortedInsert(array, i - 1, infoSortExec, array[i]);
}
