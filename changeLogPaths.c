#include "changeLogPaths.h"
#include "process.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

struct ChangeLogPaths createChangeLog(int amntWords, int linesMatrix) {
  struct ChangeLogPaths changeLog;
  changeLog.allWordsAdded = createVector(amntWords);
  changeLog.amntAddedEachIteration = createVector(amntWords);
  changeLog.matrixesAllocated = createVector(amntWords);
  changeLog.linesMatrix = linesMatrix;
  return changeLog;
}

void pushWordsAdded(struct ChangeLogPaths *changeLog, struct Vector wordsToAdd,
                    char **matrix) {
  int *amntWordsAdded = (int *)malloc(sizeof(int));
  *amntWordsAdded = wordsToAdd.last + 1;
  pushToVector(&changeLog->amntAddedEachIteration, amntWordsAdded);
  pushToVector(&changeLog->matrixesAllocated, matrix);
  pushItemsToVector(&changeLog->allWordsAdded, wordsToAdd);
}

void removeLastOptionsGroup(struct ChangeLogPaths *changeLog) {
  int i,
      *amntWordsAbandoned = popFromVector(&changeLog->amntAddedEachIteration);

  char **copiedMatrix = popFromVector(&changeLog->matrixesAllocated);
  if (copiedMatrix != NULL)
    freeMatrix(copiedMatrix, changeLog->linesMatrix);

  for (i = 0; i < *amntWordsAbandoned; i++) {
    struct InfoBoardSemiFilled *cur =
        (struct InfoBoardSemiFilled *)popFromVector(&changeLog->allWordsAdded);
    free(cur);
  }

  free(amntWordsAbandoned);
}

void freeChangeLogWords(struct ChangeLogPaths *changeLog) {
  while (!vectorIsEmpty(changeLog->amntAddedEachIteration))
    removeLastOptionsGroup(changeLog);

  freeVector(changeLog->allWordsAdded);
  freeVector(changeLog->matrixesAllocated);
  freeVector(changeLog->amntAddedEachIteration);
}