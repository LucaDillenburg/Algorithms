#include "mergeSort.h"
#include <stdlib.h>

int *mergeSort(int *array, int lengthArray, infoSortExec *infoSortExec) {
  int middle, lengthLeft, lengthRight, *left, *right, *sortedLeft, *sortedRight,
      *sorted, iSorted, i, j;

  if (lengthArray <= 1)
    return array;

  middle = lengthArray / 2;

  lengthLeft = middle - 1;
  lengthRight = lengthArray - 1;
  left = newArrayOf(array, 0, lengthLeft);
  right = newArrayOf(array, middle, lengthRight);
  infoSortExec->amntSwitches += lengthLeft + lengthRight;

  sortedLeft = mergeSort(left, lengthLeft, infoSortExec);
  sortedRight = mergeSort(right, lengthRight, infoSortExec);

  free(left);
  free(right);

  sorted = newIntArray(lengthArray);
  iSorted = 0, i = 0, j = 0;
  while (i < lengthLeft && j < lengthRight) {
    infoSortExec->amntComparisons++;
    if (sortedLeft[i] < sortedRight[j]) {
      infoSortExec->amntSwitches++;
      sorted[iSorted++] = sortedLeft[i++];
    } else if (sortedLeft[i] > sortedRight[j]) {
      infoSortExec->amntSwitches++;
      sorted[iSorted++] = sortedRight[j++];
    } else {
      infoSortExec->amntSwitches += 2;
      sorted[iSorted++] = sortedLeft[i++];
      sorted[iSorted++] = sortedRight[j++];
    }
  }

  while (i < lengthLeft) {
    infoSortExec->amntSwitches++;
    sorted[iSorted++] = sortedLeft[i++];
  }
  while (j < lengthRight) {
    infoSortExec->amntSwitches++;
    sorted[iSorted++] = sortedRight[j++];
  }

  free(sortedLeft);
  free(sortedRight);

  return sorted;
}
