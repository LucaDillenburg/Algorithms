#include "specialStack.h"
#include "../process.h"
#include "../utils/utils.h"
#include "../vector/vector.h"
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
  struct StackGroup *stackGroup = newEmptyStackGroup();
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
  struct StackGroup *curStackGroup,
      *lastStackGroup = stack->groups.array[stack->groups.last];
  struct InfoBoardSemiFilled *lastAvailableOption =
      popFromVector(&lastStackGroup->availableOptions);
  free(lastAvailableOption);

  if (vectorIsEmpty(lastStackGroup->availableOptions)) {
    freeMatrix(lastStackGroup->allocatedMatrix, stack->amntLines);
    freeVector(lastStackGroup->availableOptions);
  } else {
    struct StackGroup *newGroup = newEmptyStackGroup();
    newGroup->selectedWords = createVector(stack->amntWords);
    newGroup->allocatedMatrix = NULL;
    pushToVector(&stack->groups, newGroup);
  }

  curStackGroup = stack->groups.array[stack->groups.last];
  curStackGroup->availableOptions = availableOptions;
  pushToVector(&curStackGroup->selectedWords, selectedWord);
  curStackGroup->allocatedMatrix = matrix;
}

/* when there is no going forward with the last item */
void popItemInPathGroup(struct SpecialStack *stack,
                        struct Vector wordsStructure) {
  char wasLastItem;
  struct StackGroup *lastStackGroup = stack->groups.array[stack->groups.last];
  struct InfoBoardSemiFilled *lastInfoBoardSemiFilled =
      popFromVector(&lastStackGroup->availableOptions);
  free(lastInfoBoardSemiFilled);

  wasLastItem = vectorIsEmpty(lastStackGroup->availableOptions);
  if (wasLastItem) {
    int i;
    for (i = 0; i <= lastStackGroup->selectedWords.last; i++) {
      struct WordId *curWordId = lastStackGroup->selectedWords.array[i];
      struct Vector *wordsSameLength = wordsStructure.array[curWordId->length];
      struct WordInfo *curWordInfo = wordsSameLength->array[curWordId->index];
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
  struct StackGroup *lastStackGroup = popFromVector(&stack->groups);

  freeMatrix(lastStackGroup->allocatedMatrix, stack->amntLines);

  while (!vectorIsEmpty(lastStackGroup->availableOptions)) {
    struct InfoBoardSemiFilled *curInfoBoardSemiFilled =
        popFromVector(&lastStackGroup->availableOptions);
    free(curInfoBoardSemiFilled);
  }
  freeVector(lastStackGroup->availableOptions);

  while (!vectorIsEmpty(lastStackGroup->selectedWords)) {
    struct WordId *curWordId = popFromVector(&lastStackGroup->selectedWords);
    free(curWordId);
  }
  freeVector(lastStackGroup->selectedWords);

  free(lastStackGroup);
}

struct StackGroup *newEmptyStackGroup() {
  struct StackGroup *stackGroup = malloc(sizeof(struct StackGroup));
  return stackGroup;
}

/* test */

void printSpecialStack(struct SpecialStack stack) {
  int i;
  printf("$$$$ TOP $$$$ \n");
  printf("-----------\n");
  for (i = stack.groups.last; i >= 0; i--) {
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
  printf("$$$$ BOTTOM $$$$ \n");
  printf("\n ");
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
