#include "process.h"
#include "changeLogWords.h"
#include <stdlib.h>

#define FIRST_DIRECTION 1

char process(struct Board *finalBoard, struct Vector wordsStructure,
             int amntWords) {
  /* declare variables and add first item */
  struct Vector stack = createVector(
      1); /* TODO: CHANGE PARAM to finalBoard->columns*finalBoard->lines */
  int i;
  struct ChangeLogWords changeLogWords = createChangeLogWords();
  char foundPath = 0;
  struct Position initialPos;
  initialPos.line = 0;
  initialPos.column = 0;
  pushItemsToVector(&stack, getAvailablePaths(*finalBoard, wordsStructure,
                                              FIRST_DIRECTION, initialPos));
  finalBoard->matrix = NULL;

  /* processing */
  while (!vectorIsEmpty(stack)) {
    struct InfoBoardSemiFilled *curInfoBoardSemiFilled = popFromVector(&stack);
    struct Vector possiblePathsFromCur;
    struct Board momentaryBoard;
    struct WordInfo *curInfoWord;

    if (curInfoBoardSemiFilled->pos.column < 0 &&
        curInfoBoardSemiFilled->pos.line < 0) {
      finalBoard->matrix = curInfoBoardSemiFilled->matrix;
      free(curInfoBoardSemiFilled);
      foundPath = 1;
      break;
    }

    momentaryBoard.matrix =
        cloneMatrix(finalBoard->matrix, finalBoard->lines, finalBoard->columns);
    ;

    curInfoWord =
        getInfoWordFromId(wordsStructure, curInfoBoardSemiFilled->wordId);
    curInfoWord->available = 0;
    addWord(momentaryBoard, curInfoWord->word,
            curInfoBoardSemiFilled->wordId.length, curInfoBoardSemiFilled->pos,
            curInfoBoardSemiFilled->horiz);

    possiblePathsFromCur = getAvailablePaths(momentaryBoard, wordsStructure,
                                             curInfoBoardSemiFilled->horiz,
                                             curInfoBoardSemiFilled->pos);

    if (vectorIsEmpty(possiblePathsFromCur))
      pathWasAbandoned(&changeLogWords);
    else {
      pushItemsToVector(&stack, possiblePathsFromCur);
      wordsAdded(&changeLogWords, possiblePathsFromCur);
    }

    freeVector(possiblePathsFromCur);
    free(curInfoBoardSemiFilled);
  }

  /* frees */
  /* TODO: free matrixes */
  for (i = 0; i <= stack.last; i++)
    free(stack.array[i]);
  freeVector(stack);
  freeChangeLogWords(changeLogWords);

  return foundPath;
}

struct Vector getAvailablePaths(struct Board board,
                                struct Vector wordsStructure, int prevHoriz,
                                struct Position prevPos) {
  for (;;) {
    struct Vector filteredPaths, *unfilteredWords;
    char nextHoriz;
    int lengthWord, i;
    struct Position nextPos;

    /* direction */
    if (prevHoriz) {
      nextHoriz = 0;
      nextPos = prevPos;
    } else {
      nextHoriz = 1;
      nextPos = nextPositionBoard(board, prevPos);
    }

    /* end of board */
    if (!isInsideBoard(board, nextPos)) {
      struct WordId blankWordId;
      blankWordId.length = -1;
      blankWordId.index = -1;
      filteredPaths = createVector(1);
      pushToVector(&filteredPaths,
                   newInfoBoardSemiFilled(nextHoriz, board.matrix, nextPos,
                                          blankWordId));
      return filteredPaths;
    }

    /* length word */
    lengthWord = shouldAddWord(board, prevPos, prevHoriz);

    /* not a word */
    if (lengthWord < 2) {
      prevPos = nextPos;
      prevHoriz = nextHoriz;
      continue;
    }

    /* preparation and create vector */
    unfilteredWords = (struct Vector *)wordsStructure.array[lengthWord];
    filteredPaths = createVector(unfilteredWords->length);

    /* add words */
    for (i = 0; i <= unfilteredWords->last; i++) {
      struct WordInfo *infoWord = unfilteredWords->array[i];
      if (infoWord->available &&
          canAddThisWord(board, infoWord->word, lengthWord, prevPos,
                         prevHoriz)) {
        struct WordId id;
        id.length = lengthWord;
        id.index = i;
        pushToVector(&filteredPaths, newInfoBoardSemiFilled(
                                         nextHoriz, board.matrix, nextPos, id));
      }
    }

    /* the vector can be empty */
    return filteredPaths;
  }
}

struct WordInfo *getInfoWordFromId(struct Vector wordsStructure,
                                   struct WordId id) {
  struct Vector *wordWithLength = wordsStructure.array[id.length];
  return wordWithLength->array[id.index];
}

struct InfoBoardSemiFilled *newInfoBoardSemiFilled(char horiz, char **matrix,
                                                   struct Position pos,
                                                   struct WordId wordId) {
  struct InfoBoardSemiFilled *ptr =
      (struct InfoBoardSemiFilled *)malloc(sizeof(struct InfoBoardSemiFilled));
  ptr->horiz = horiz;
  ptr->matrix = matrix;
  ptr->pos = pos;
  return ptr;
}
