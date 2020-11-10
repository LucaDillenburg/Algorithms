#ifndef CHANGE_LOG_PATHS_H
#define CHANGE_LOG_PATHS_H

#include "vector.h"

struct ChangeLogPaths {
  struct Vector allWordsAdded;
  struct Vector matrixesAllocated;
  struct Vector amntAddedEachIteration;
  int linesMatrix;
};

struct ChangeLogPaths createChangeLog(int amntWords, int linesMatrix);

void pushWordsAdded(struct ChangeLogPaths *changeLog, struct Vector wordsToAdd,
                    char **matrix);                            /* TODO: TEST */
void removeLastOptionsGroup(struct ChangeLogPaths *changeLog); /* TODO: TEST */
void removeLastOption(struct ChangeLogPaths *changeLog);       /* TODO: TEST */

void freeChangeLogWords(struct ChangeLogPaths *changeLog); /* TODO: TEST */

#endif