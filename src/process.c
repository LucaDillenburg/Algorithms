#include "process.h"
#include <stdio.h>
#include <stdlib.h>

#define FIRST_DIRECTION 1

char process(struct Board *finalBoard, struct Vector wordsStructure,
             int amntWords) {
  /* declare variables and add first item */
  struct SpecialStack stack =
      createSpecialStack(amntWords, finalBoard->lines, finalBoard->columns);
  char foundPath = 0;

  struct Vector initialPaths;
  struct Position initialPos;
  initialPos.line = 0;
  initialPos.column = 0;
  initialPaths = getAvailablePaths(*finalBoard, wordsStructure, FIRST_DIRECTION,
                                   initialPos);
  firstPushPathGroup(&stack, initialPaths, finalBoard->matrix);
  finalBoard->matrix = NULL;

  /* processing */
  while (!specialStackIsEmpty(stack)) {
    struct Vector possiblePathsFromCur;
    struct WordInfo *curInfoWord;
    struct Board momentaryBoard;
    struct PosHoriz nextPosHoriz;

    struct InfoBoardSemiFilled *curInfoBoardSemiFilled = getTopItem(stack);

    if (curInfoBoardSemiFilled->pos.column < 0 &&
        curInfoBoardSemiFilled->pos.line < 0) {
      finalBoard->matrix = cloneMatrix(curInfoBoardSemiFilled->matrix,
                                       finalBoard->lines, finalBoard->columns);
      foundPath = 1;
      break;
    }

    momentaryBoard = *finalBoard;
    momentaryBoard.matrix = cloneMatrix(curInfoBoardSemiFilled->matrix,
                                        finalBoard->lines, finalBoard->columns);

    curInfoWord =
        getInfoWordFromId(wordsStructure, curInfoBoardSemiFilled->wordId);
    curInfoWord->available = 0;
    addWord(momentaryBoard, curInfoWord->word,
            curInfoBoardSemiFilled->wordId.length, curInfoBoardSemiFilled->pos,
            curInfoBoardSemiFilled->horiz);

    nextPosHoriz = getNextPosHoriz(momentaryBoard, curInfoBoardSemiFilled->pos,
                                   curInfoBoardSemiFilled->horiz);
    possiblePathsFromCur = getAvailablePaths(
        momentaryBoard, wordsStructure, nextPosHoriz.horiz, nextPosHoriz.pos);

    if (vectorIsEmpty(possiblePathsFromCur)) {
      freeVector(possiblePathsFromCur);
      curInfoWord->available = 1;
      freeMatrix(momentaryBoard.matrix, momentaryBoard.lines);

      popItemInPathGroup(&stack, wordsStructure);
    } else {
      struct WordId *ptrWordId = malloc(sizeof(struct WordId));
      *ptrWordId = curInfoBoardSemiFilled->wordId;
      popItemAndPushPathGroup(&stack, possiblePathsFromCur, ptrWordId,
                              momentaryBoard.matrix);
    }
  }

  /* frees */
  freeSpecialStack(&stack);

  return foundPath;
}

struct Vector getAvailablePaths(struct Board board,
                                struct Vector wordsStructure, int horiz,
                                struct Position pos) {
  for (;;) {
    struct Vector filteredPaths, *unfilteredWords;
    int lengthWord, i;

    /* end of board */
    if (!isInsideBoard(board, pos)) {
      struct WordId blankWordId;
      blankWordId.length = -1;
      blankWordId.index = -1;
      pos.column = -1;
      pos.line = -1;
      horiz = -1;
      filteredPaths = createVector(1);
      pushToVector(&filteredPaths, newInfoBoardSemiFilled(horiz, board.matrix,
                                                          pos, blankWordId));
      return filteredPaths;
    }

    /* length word */
    lengthWord = shouldAddWord(board, pos, horiz);

    /* not a word */
    if (lengthWord < 2) {
      struct PosHoriz nextPosHoriz = getNextPosHoriz(board, pos, horiz);
      pos = nextPosHoriz.pos;
      horiz = nextPosHoriz.horiz;
      continue;
    }

    /* preparation and create vector */
    unfilteredWords = (struct Vector *)wordsStructure.array[lengthWord];
    filteredPaths = createVector(unfilteredWords->length);

    /* add words */
    for (i = 0; i <= unfilteredWords->last; i++) {
      struct WordInfo *infoWord = unfilteredWords->array[i];
      if (infoWord->available &&
          canAddThisWord(board, infoWord->word, lengthWord, pos, horiz)) {
        struct WordId id;
        id.length = lengthWord;
        id.index = i;
        pushToVector(&filteredPaths,
                     newInfoBoardSemiFilled(horiz, board.matrix, pos, id));
      }
    }

    /* the vector can be empty */
    return filteredPaths;
  }
}

/* auxiliar functions */

struct PosHoriz getNextPosHoriz(struct Board board, struct Position pos,
                                char horiz) {
  struct PosHoriz nextPosHoriz;
  /* direction */
  if (horiz) {
    nextPosHoriz.horiz = 0;
    nextPosHoriz.pos = pos;
  } else {
    nextPosHoriz.horiz = 1;
    nextPosHoriz.pos = nextPositionBoard(board, pos);
  }
  return nextPosHoriz;
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
  ptr->wordId = wordId;
  return ptr;
}
