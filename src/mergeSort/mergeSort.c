#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int *newArrayOf(int *array, int begin, int last) {
  int *ret = newIntArray(last - begin + 1);
  int i;
  for (i = begin; i <= last; i++) {
    ret[i - begin] = array[i];
  }
  return ret;
}

int *mergeSort(int *array, int lengthArray, infoSortExec *infoSortExec) {
  int middle, lengthLeft, lengthRight, *left, *right, *sortedLeft, *sortedRight,
      *sorted, iSorted, i, j;

  if (lengthArray <= 1)
    return array;

  middle = lengthArray / 2;

  left = newArrayOf(array, 0, middle);
  right = newArrayOf(array, middle, lengthArray);
  lengthLeft = middle;
  lengthRight = lengthArray - middle;
  infoSortExec->amntSwitches += lengthLeft + lengthRight;

  sortedLeft = mergeSort(left, lengthLeft, infoSortExec);
  sortedRight = mergeSort(right, lengthRight, infoSortExec);

  printf("\n\nlength: %d", lengthArray);
  printf("\nSorted Array: ");
  for (i = 0; i < lengthLeft; i++)
    printf("%d ", sortedLeft[i]);
  printf("\nSorted Array: ");
  for (i = 0; i < lengthRight; i++)
    printf("%d ", array[i]);

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

  free(left);
  free(right);

  return sorted;
}
