#include "bubbleSort/bubbleSort.h"
#include "insertionSort/insertionSort.h"
#include "mergeSort/mergeSort.h"
#include "quickSort/quickSort.h"
#include <stdio.h>

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

int *newSpecificArray(int length, int arrayType);

int main() {
  int length, sortAlgorithm, arrayType;
  int i;
  int *array;
  infoSortExec infoSortExec;

  printf("Array length: ");
  scanf("%d", &length);

  printf("\n\n");

  printf("Array type (random=%d, crescent=%d, decrescent=%d): ", RANDOM_ARRAY,
         CRESCENT_ORDERED_ARRAY, DECRESCENT_ORDERED_ARRAY);
  scanf("%d", &arrayType);

  printf("\n\n");

  printf(
      "Sort algorithm (quick sort=%d, merge sort=%d, insertion sort=%d, bubble "
      "sort=%d): ",
      QUICK_SORT, MERGE_SORT, INSERTION_SORT, BUBBLE_SORT);
  scanf("%d", &sortAlgorithm);

  array = newSpecificArray(length, arrayType);
  printf("Array: ");
  for (i = 0; i < length; i++)
    printf("%d ", array[i]);

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
  printf("\nAmnt Switches: %d", infoSortExec.amntSwitches);

  free(array);

  return 0;
}

int *newSpecificArray(int length, int arrayType) {
  int *array = newIntArray(length);
  int i;
  for (i = 0; i < length; i++)
    array[i] = rand() % (HIGH_MAX_INT + 1);

  if (arrayType == CRESCENT_ORDERED_ARRAY ||
      arrayType == DECRESCENT_ORDERED_ARRAY) {
    infoSortExec info;
    quickSort(array, 0, length - 1, &info);
    if (arrayType == DECRESCENT_ORDERED_ARRAY) {
      int i;
      for (i = 0; i < length / 2; i++)
        swap(&array[i], &array[length - i]);
    }
  }
  return array;
}
