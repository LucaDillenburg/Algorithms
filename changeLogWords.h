#ifndef CHANGED_WORDS_H
#define CHANGED_WORDS_H

#include "vector.h"

struct ChangeLogWords {
  struct Vector allWordsAdded;
  struct Vector amntAddedEachIteration;
};

struct ChangeLogWords createChangeLogWords();
void freeChangeLogWords(struct ChangeLogWords changeLog);

void wordsAdded(
    struct ChangeLogWords *changeLog,
    struct Vector /*InfoBoardSemiFilled*/ wordsToAdd);   /* TODO: TEST */
void pathWasAbandoned(struct ChangeLogWords *changeLog); /* TODO: TEST */

#endif