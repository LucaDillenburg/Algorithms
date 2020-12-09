#include "insertionSort.h"
#include <stdio.h>
#include <stdlib.h>

void sortedInsert(int *array, int lastSorted, infoSortExec *infoSortExec,
                  int value) {
  int i;
  int insertIndex = 0;

  for (i = lastSorted; i >= 0; i--) {
    infoSortExec->amntComparisons++;
    if (value >= array[i]) {
      insertIndex = i + 1;
      break;
    }
  }

  if (insertIndex == lastSorted + 1)
    return;

  for (i = lastSorted + 1; i > insertIndex; i--) {
    infoSortExec->amntMoves++;
    array[i] = array[i - 1];
  }
  array[insertIndex] = value;
  infoSortExec->amntMoves++;
}

void insertionSort(int *array, int length, infoSortExec *infoSortExec) {
  int i;
  for (i = 1; i < length; i++)
    sortedInsert(array, i - 1, infoSortExec, array[i]);
}
