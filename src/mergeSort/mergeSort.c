#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int *mergeSort(int *array, int lengthArray, infoSortExec *infoSortExec) {
  int middle, lengthLeft, lengthRight, *left, *right, *sortedLeft, *sortedRight,
      *sorted, iSorted, i, j;

  if (lengthArray <= 1)
    return array;

  middle = lengthArray / 2;

  left = copyOf(array, 0, middle);
  right = copyOf(array, middle, lengthArray);
  lengthLeft = middle;
  lengthRight = lengthArray - middle;
  infoSortExec->amntMoves += lengthLeft + lengthRight;

  sortedLeft = mergeSort(left, lengthLeft, infoSortExec);
  sortedRight = mergeSort(right, lengthRight, infoSortExec);

  sorted = newIntArray(lengthArray);
  iSorted = 0, i = 0, j = 0;
  while (i < lengthLeft && j < lengthRight) {
    infoSortExec->amntComparisons++;
    if (sortedLeft[i] < sortedRight[j]) {
      infoSortExec->amntMoves++;
      sorted[iSorted++] = sortedLeft[i++];
    } else if (sortedLeft[i] > sortedRight[j]) {
      infoSortExec->amntMoves++;
      sorted[iSorted++] = sortedRight[j++];
    } else {
      infoSortExec->amntMoves += 2;
      sorted[iSorted++] = sortedLeft[i++];
      sorted[iSorted++] = sortedRight[j++];
    }
  }

  while (i < lengthLeft) {
    infoSortExec->amntMoves++;
    sorted[iSorted++] = sortedLeft[i++];
  }
  while (j < lengthRight) {
    infoSortExec->amntMoves++;
    sorted[iSorted++] = sortedRight[j++];
  }

  free(left);
  free(right);

  return sorted;
}
