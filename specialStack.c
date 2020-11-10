#include "specialStack.h"
#include "process.h"
#include "utils.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct SpecialStack createSpecialStack(int amountWords, int linesMatrix,
                                       int columnsMatrix) {
  struct SpecialStack stack;
  stack.groups = createVector(linesMatrix * columnsMatrix);
  stack.amntWords = amountWords;
  stack.amntLines = linesMatrix;
  return stack;
}

/* ###################################################################### */
/* GETS: */
/* ###################################################################### */

char specialStackIsEmpty(struct SpecialStack stack) {
  struct StackGroup *firstGroup;
  if (vectorIsEmpty(stack.groups))
    return 1;
  firstGroup = stack.groups.array[0];
  return stack.groups.last == 0 && vectorIsEmpty(firstGroup->availableOptions);
}

struct InfoBoardSemiFilled *getTopItem(struct SpecialStack stack) {
  struct StackGroup *lastGroup = stack.groups.array[stack.groups.last];
  return lastGroup->availableOptions.array[lastGroup->availableOptions.last];
}

void firstPushPathGroup(struct SpecialStack *stack,
                        struct Vector availableOptions, char **matrix) {
  struct StackGroup *stackGroup = newEmptyLogGroup();
  stackGroup->selectedWords = createVector(stack->amntWords);
  stackGroup->availableOptions = availableOptions;
  stackGroup->allocatedMatrix = matrix;
  pushToVector(&stack->groups, stackGroup);
}

/* ###################################################################### */
/* SETS: */
/* ###################################################################### */

void popItemAndPushPathGroup(struct SpecialStack *stack,
                             struct Vector availableOptions,
                             struct WordId *selectedWord, char **matrix) {
  struct StackGroup *curLogGroup,
      *lastLogGroup = stack->groups.array[stack->groups.last];
  popFromVector(&lastLogGroup->availableOptions);

  if (vectorIsEmpty(lastLogGroup->availableOptions))
    freeMatrix(lastLogGroup->allocatedMatrix, stack->amntLines);
  else
    pushToVector(&stack->groups, newEmptyLogGroup());

  curLogGroup = stack->groups.array[stack->groups.last];
  pushItemsToVector(&curLogGroup->availableOptions, availableOptions);
  pushToVector(&curLogGroup->selectedWords, selectedWord);
  curLogGroup->allocatedMatrix = matrix;
}

/* when there is no going forward with the last item */
void popItemInPathGroup(struct SpecialStack *stack,
                        struct Vector wordsStructure) {
  char wasLastItem;
  struct StackGroup *lastLogGroup = stack->groups.array[stack->groups.last];
  struct InfoBoardSemiFilled *lastInfoBoardSemiFilled =
      popFromVector(&lastLogGroup->availableOptions);
  free(lastInfoBoardSemiFilled);

  wasLastItem = vectorIsEmpty(lastLogGroup->availableOptions);
  if (wasLastItem) {
    while (!vectorIsEmpty(lastLogGroup->selectedWords)) {
      struct WordId *curWordId = popFromVector(&lastLogGroup->selectedWords);
      struct Vector *wordsSameLength = wordsStructure.array[curWordId->length];
      struct WordInfo *curWordInfo = wordsSameLength->array[curWordId->length];
      curWordInfo->available = 1;
    }

    popAndFreeLastGroup(stack);
  }
}

void freeSpecialStack(struct SpecialStack *stack) {
  while (!vectorIsEmpty(stack->groups))
    popAndFreeLastGroup(stack);
  freeVector(stack->groups);
}

/* ###################################################################### */
/* auxiliar functions: */
/* ###################################################################### */

void popAndFreeLastGroup(struct SpecialStack *stack) {
  struct StackGroup *lastLogGroup = popFromVector(&stack->groups);

  freeMatrix(lastLogGroup->allocatedMatrix, stack->amntLines);

  while (!vectorIsEmpty(lastLogGroup->availableOptions)) {
    struct InfoBoardSemiFilled *curInfoBoardSemiFilled =
        popFromVector(&lastLogGroup->availableOptions);
    free(curInfoBoardSemiFilled);
  }
  freeVector(lastLogGroup->availableOptions);

  while (!vectorIsEmpty(lastLogGroup->selectedWords)) {
    struct WordId *curWordId = popFromVector(&lastLogGroup->selectedWords);
    free(curWordId);
  }
  freeVector(lastLogGroup->selectedWords);

  free(lastLogGroup);
}

struct StackGroup *newEmptyLogGroup() {
  struct StackGroup *stackGroup = malloc(sizeof(struct StackGroup));
  return stackGroup;
}

/* test */

void printSpecialStack(struct SpecialStack stack) {
  int i;
  printf("-----------\n");
  for (i = 0; i <= stack.groups.last; i++) {
    struct StackGroup *curStackGroup = stack.groups.array[i];
    int j;

    struct InfoBoardSemiFilled *firstInfoBoardSemiFilled =
        curStackGroup->availableOptions.array[0];
    printf(" ## POSITION: (%d,%d) %c ##", firstInfoBoardSemiFilled->pos.line,
           firstInfoBoardSemiFilled->pos.column,
           firstInfoBoardSemiFilled->horiz ? 'H' : 'V');

    printf("\n SelectedWords: ");
    for (j = 0; j <= curStackGroup->selectedWords.last; j++) {
      struct WordId *curWordId = curStackGroup->selectedWords.array[j];
      printf("{ (L:%d, I:%d) } ; ", curWordId->length, curWordId->index);
    }

    printf("\n Available Options: ");
    for (j = 0; j <= curStackGroup->availableOptions.last; j++) {
      struct InfoBoardSemiFilled *curAvailable =
          curStackGroup->availableOptions.array[j];
      printf("{ (L:%d, I:%d) } ; ", curAvailable->wordId.length,
             curAvailable->wordId.index);
    }

    printf("\n Matrix pointer: %p\n", (void *)curStackGroup->allocatedMatrix);

    printf("-----------\n");
  }
}

void printWords(struct Vector wordsStructure) {
  int i;
  for (i = 0; i < wordsStructure.length; i++) {
    struct Vector *curWordsArray = wordsStructure.array[i];
    int j;

    printf("%3d: | ", i);
    for (j = 0; j <= curWordsArray->last; j++) {
      struct WordInfo *curWordInfo = curWordsArray->array[j];
      if (j != 0)
        printf("     | ");
      printf("%s ", curWordInfo->word);
      if (curWordInfo->available)
        printf("(available)\n");
      else
        printf("(USED)\n");
    }
    printf("\n");
  }
}
