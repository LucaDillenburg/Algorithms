#include "changeLogWords.h"
#include <stdio.h>
#include <stdlib.h>

struct ChangeLogWords createChangeLogWords(int amntWords) {
  struct ChangeLogWords changeLog;
  changeLog.allWordsAdded = createVector(amntWords);
  changeLog.amntAddedEachIteration = createVector(amntWords);
  return changeLog;
}

void freeChangeLogWords(struct ChangeLogWords changeLog) {
  int i;
  for (i = 0; i <= changeLog.amntAddedEachIteration.last; i++)
    free(changeLog.amntAddedEachIteration.array[i]);
  freeVector(changeLog.allWordsAdded);
  freeVector(changeLog.amntAddedEachIteration);
}

void wordsAdded(struct ChangeLogWords *changeLog,
                struct Vector /*InfoBoardSemiFilled*/ wordsToAdd) {
  int i;
  int *amntWordsAdded = (int *)malloc(sizeof(int));
  *amntWordsAdded = wordsToAdd.last + 1;
  pushToVector(&changeLog->amntAddedEachIteration, amntWordsAdded);
  for (i = 0; i < *amntWordsAdded; i++)
    pushToVector(&changeLog->allWordsAdded, wordsToAdd.array[i]);
}

void pathWasAbandoned(struct ChangeLogWords *changeLog) {
  int i;
  int *amntWordsAbandoned = popFromVector(&changeLog->amntAddedEachIteration);
  for (i = 0; i < *amntWordsAbandoned; i++)
    popFromVector(&changeLog->allWordsAdded);
  free(amntWordsAbandoned);
}