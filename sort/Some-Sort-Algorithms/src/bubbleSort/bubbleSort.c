#include "bubbleSort.h"
#include <stdlib.h>

void bubbleSort(int *array, int length, infoSortExec *infoSortExec) {
  int i, j;
  for (i = 0; i < length; i++)
    for (j = i + 1; j < length; j++) {
      infoSortExec->amntComparisons++;
      if (array[j] < array[i]) {
        swap(&array[i], &array[j]);
        infoSortExec->amntMoves++;
      }
    }
}
