#include "changeLogWords.h"
#include "utils.h"
#include <stdlib.h>

struct ChangeLogWords createChangeLog(int amntWords, int linesMatrix) {
  struct ChangeLogWords changeLog;
  changeLog.allWordsAdded = createVector(amntWords);
  changeLog.amntAddedEachIteration = createVector(amntWords);
  changeLog.matrixesAllocated = createVector(amntWords);
  changeLog.linesMatrix = linesMatrix;
  return changeLog;
}

void pushWordsAdded(struct ChangeLogWords *changeLog, struct Vector wordsToAdd,
                    char **matrix) {
  int *amntWordsAdded = (int *)malloc(sizeof(int));
  *amntWordsAdded = wordsToAdd.last + 1;
  pushToVector(&changeLog->amntAddedEachIteration, amntWordsAdded);
  pushToVector(&changeLog->matrixesAllocated, matrix);
  pushItemsToVector(&changeLog->allWordsAdded, wordsToAdd);
}

void removeOptionsAddedLast(struct ChangeLogWords *changeLog) {
  int i,
      *amntWordsAbandoned = popFromVector(&changeLog->amntAddedEachIteration);

  char **copiedMatrix = popFromVector(&changeLog->matrixesAllocated);
  freeMatrix(copiedMatrix, changeLog->linesMatrix);

  for (i = 0; i < *amntWordsAbandoned; i++) {
    struct InfoBoardSemiFilled *cur = popFromVector(&changeLog->allWordsAdded);
    free(cur);
  }

  free(amntWordsAbandoned);
}

void freeChangeLogWords(struct ChangeLogWords *changeLog) {
  while (!vectorIsEmpty(changeLog->amntAddedEachIteration))
    removeOptionsAddedLast(changeLog);
  freeVector(changeLog->allWordsAdded);
  freeVector(changeLog->matrixesAllocated);
  freeVector(changeLog->amntAddedEachIteration);
}