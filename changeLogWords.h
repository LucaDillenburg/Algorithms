#ifndef CHANGED_WORDS_H
#define CHANGED_WORDS_H

#include "vector.h"

struct ChangeLogWords {
  struct Vector allWordsAdded;
  struct Vector matrixesAllocated;
  struct Vector amntAddedEachIteration;
  int linesMatrix;
};

struct ChangeLogWords createChangeLog(int amntWords, int linesMatrix);

void pushWordsAdded(struct ChangeLogWords *changeLog, struct Vector wordsToAdd,
                    char **matrix);                            /* TODO: TEST */
void removeOptionsAddedLast(struct ChangeLogWords *changeLog); /* TODO: TEST */

void freeChangeLogWords(struct ChangeLogWords *changeLog); /* TODO: TEST */

#endif