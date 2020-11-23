#include "bubbleSort/bubbleSort.h"
#include "insertionSort/insertionSort.h"
#include "mergeSort/mergeSort.h"
#include "quickSort/quickSort.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUICK_SORT 0
#define MERGE_SORT 1
#define INSERTION_SORT 2
#define BUBBLE_SORT 3

#define AMOUNT_ALGORITHMS 4

#define RANDOM_ARRAY 1
#define CRESCENT_ORDERED_ARRAY 2
#define DECRESCENT_ORDERED_ARRAY 3

#define MAX_INT 5000
#define AMOUNT_ITERATIONS 50

void printAlgorithmResult(char *algorithmName, double squareAvgComparisons,
                          double avgComparisons, double squareAvgMoves,
                          double avgMoves);
infoSortExec sortAlgorithm(int *array, int length, int algorithm);
int *newSpecificArray(int length, int arrayType);

int main(int argc, char **argv) {
  int iteration, i;
  double avgSquareComparisons[AMOUNT_ALGORITHMS],
      avgComparisons[AMOUNT_ALGORITHMS], avgSquareMoves[AMOUNT_ALGORITHMS],
      avgMoves[AMOUNT_ALGORITHMS];

  int length = atoi(argv[1]);
  int arrayType = atoi(argv[2]);

  for (i = 0; i < AMOUNT_ALGORITHMS; i++) {
    avgSquareComparisons[i] = 0.0;
    avgComparisons[i] = 0.0;
    avgSquareMoves[i] = 0.0;
    avgMoves[i] = 0.0;
  }
  srand(time(NULL));

  printf("\nLength: %d, Type: %d", length, arrayType);

  for (iteration = 0; iteration < AMOUNT_ITERATIONS; iteration++) {
    int *array, iAlgorithm;
    array = newSpecificArray(length, arrayType);

    for (iAlgorithm = 0; iAlgorithm < AMOUNT_ALGORITHMS; iAlgorithm++) {
      infoSortExec curInfoSortExec = sortAlgorithm(array, length, iAlgorithm);

      avgComparisons[iAlgorithm] +=
          (double)curInfoSortExec.amntComparisons / AMOUNT_ITERATIONS;
      avgMoves[iAlgorithm] +=
          (double)curInfoSortExec.amntMoves / AMOUNT_ITERATIONS;
      avgSquareComparisons[iAlgorithm] +=
          (double)curInfoSortExec.amntComparisons *
          curInfoSortExec.amntComparisons / AMOUNT_ITERATIONS;
      avgSquareMoves[iAlgorithm] += (double)curInfoSortExec.amntMoves *
                                    curInfoSortExec.amntMoves /
                                    AMOUNT_ITERATIONS;
    }

    free(array);
  }

  printf("\n\nResult:");
  printAlgorithmResult("Quick Sort", avgSquareComparisons[QUICK_SORT],
                       avgComparisons[QUICK_SORT], avgSquareMoves[QUICK_SORT],
                       avgMoves[QUICK_SORT]);
  printAlgorithmResult("Merge Sort", avgSquareComparisons[MERGE_SORT],
                       avgComparisons[MERGE_SORT], avgSquareMoves[MERGE_SORT],
                       avgMoves[MERGE_SORT]);
  printAlgorithmResult("Insert Sort", avgSquareComparisons[INSERTION_SORT],
                       avgComparisons[INSERTION_SORT],
                       avgSquareMoves[INSERTION_SORT],
                       avgMoves[INSERTION_SORT]);
  printAlgorithmResult("Bubble Sort", avgSquareComparisons[BUBBLE_SORT],
                       avgComparisons[BUBBLE_SORT], avgSquareMoves[BUBBLE_SORT],
                       avgMoves[BUBBLE_SORT]);
  printf("\n\n");

  return 0;
}

void printAlgorithmResult(char *algorithmName, double squareAvgComparisons,
                          double avgComparisons, double squareAvgMoves,
                          double avgMoves) {
  double sdComparisons = squareAvgComparisons - avgComparisons * avgComparisons;
  double sdMoves = squareAvgMoves - avgMoves * avgMoves;
  printf("\n\\textbf{%s} & %.2f & %.2f & %.2f & %.2f \\\\", algorithmName,
         avgComparisons, sdComparisons, avgMoves, sdMoves);
}

infoSortExec sortAlgorithm(int *array, int length, int algorithm) {
  infoSortExec infoSortExec = createInfoSortExec();
  int *copy = copyOf(array, 0, length);

  switch (algorithm) {
  case QUICK_SORT:
    quickSort(copy, 0, length - 1, &infoSortExec);
    break;
  case MERGE_SORT:
    copy = mergeSort(copy, length, &infoSortExec);
    break;
  case INSERTION_SORT:
    insertionSort(copy, length, &infoSortExec);
    break;
  case BUBBLE_SORT:
    bubbleSort(copy, length, &infoSortExec);
    break;
  }

  free(copy);

  return infoSortExec;
}

int *newSpecificArray(int length, int arrayType) {
  int *array = newIntArray(length);
  int i;

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
