#ifndef CHANGE_LOG_PATHS_H
#define CHANGE_LOG_PATHS_H

#include "board.h"
#include "vector.h"

/* Stack Related */

struct StackGroup {
  struct Vector /*<struct WordId *>*/ selectedWords;
  struct Vector /*<struct InfoBoardSemiFilled *>*/ availableOptions;
  char **allocatedMatrix;
};

struct SpecialStack {
  struct Vector /*<struct StackGroup>*/ groups;
  int amntWords;
  int amntLines;
};

/* Elements */

struct WordId {
  int length;
  int index;
};

typedef struct WordInfo {
  char *word;
  char available;
} _wordInfo;

typedef struct InfoBoardSemiFilled {
  char horiz;
  char **matrix;
  struct Position pos;
  struct WordId wordId;
} _infoBoardSemiFilled;

/* create and free */
struct SpecialStack createSpecialStack(int amountWords, int linesMatrix,
                                       int columnsMatrix);
void freeSpecialStack(struct SpecialStack *stack);

/* gets */
char specialStackIsEmpty(struct SpecialStack stack);
struct InfoBoardSemiFilled *getTopItem(struct SpecialStack stack);

/* sets */
void firstPushPathGroup(struct SpecialStack *stack,
                        struct Vector availableOptions, char **matrix);
void popItemAndPushPathGroup(struct SpecialStack *stack,
                             struct Vector availableOptions,
                             struct WordId *selectedWord, char **matrix);
void popItemInPathGroup(struct SpecialStack *stack,
                        struct Vector wordsStructure);

/* auxiliar functions */
void popAndFreeLastGroup(struct SpecialStack *stack);
struct StackGroup *newEmptyStackGroup();

/* test */
void printSpecialStack(struct SpecialStack stack);
void printWords(struct Vector wordsStructure);

#endif