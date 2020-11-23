#include "bubbleSort/bubbleSort.h"
#include "insertionSort/insertionSort.h"
#include "mergeSort/mergeSort.h"
#include "quickSort/quickSort.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUICK_SORT 1
#define MERGE_SORT 2
#define INSERTION_SORT 3
#define BUBBLE_SORT 4

#define RANDOM_ARRAY 1
#define CRESCENT_ORDERED_ARRAY 2
#define DECRESCENT_ORDERED_ARRAY 3

#define LOW_MAX_INT 50
#define MEDIUM_MAX_INT 500
#define HIGH_MAX_INT 5000
#define MAX_INT LOW_MAX_INT

int *newSpecificArray(int length, int arrayType);

int main(int argc, char **argv) {
  int i;
  infoSortExec infoSortExec;
  int *array;

  int length = atoi(argv[1]);
  int arrayType = atoi(argv[2]);
  int sortAlgorithm = atoi(argv[3]);

  printf("Length: %d, Type: %d, Algorithm: %d", length, arrayType,
         sortAlgorithm);

  array = newSpecificArray(length, arrayType);
  printf("\nArray       : ");
  for (i = 0; i < length; i++)
    printf("%d ", array[i]);

  infoSortExec.amntComparisons = 0;
  infoSortExec.amntSwitches = 0;

  switch (sortAlgorithm) {
  case QUICK_SORT:
    quickSort(array, 0, length - 1, &infoSortExec);
    break;
  case MERGE_SORT:
    array = mergeSort(array, length, &infoSortExec);
    break;
  case INSERTION_SORT:
    insertionSort(array, length, &infoSortExec);
    break;
  case BUBBLE_SORT:
    bubbleSort(array, length, &infoSortExec);
    break;
  }

  printf("\n\nSorted Array: ");
  for (i = 0; i < length; i++)
    printf("%d ", array[i]);

  printf("\n\nAmnt Comparisons: %d", infoSortExec.amntComparisons);
  printf("\nAmnt Switches: %d\n", infoSortExec.amntSwitches);

  free(array);

  return 0;
}

int *newSpecificArray(int length, int arrayType) {
  int *array = newIntArray(length);
  int i;

  printf("\nMAX_INT: %d\n", MAX_INT);

  srand(time(NULL));
  for (i = 0; i < length; i++)
    array[i] = (int)randBetween(0, MAX_INT + 1);

  if (arrayType == CRESCENT_ORDERED_ARRAY ||
      arrayType == DECRESCENT_ORDERED_ARRAY) {
    infoSortExec info;
    quickSort(array, 0, length - 1, &info);
    if (arrayType == DECRESCENT_ORDERED_ARRAY) {
      int i;
      for (i = 0; i < (length - 1) / 2; i++)
        swap(&array[i], &array[length - i - 1]);
    }
  }
  return array;
}
