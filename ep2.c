#include "board.h"
#include "changeLogWords.h"
#include "utils.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Observavoes
- Backtracking com Pilha
- Podem sobrar palavras na lista
- Outro: verificar se a palavra nao se cruza com nenhuma outra
- Otimizacao: Ter um vetor de vetores em que em cada posicao do vetor maior ha
as palavras do vetor menor
*/

char process(struct Board *board, struct Vector wordsStructure, int amntWords);
void printWords(struct Vector wordsStructure);

struct WordInfo {
  char *word;
  char available;
};

int main() {
  int instance;
  for (instance = 1;; instance++) {
    struct Board board;
    int amntWords, i;
    struct Vector wordsStructure;
    int maxLengthWord;
    char hasSolution;

    /* Board */
    board = readBoard();
    if (board.lines == 0 || board.columns == 0)
      break;

    /* Amnt wordsStructure */
    scanf("%d", &amntWords);

    /* Alloc wordsStructure */
    maxLengthWord = max(board.columns, board.lines) + 1;
    wordsStructure = createVector(maxLengthWord);
    for (i = 0; i < wordsStructure.length; i++) {
      struct Vector *vector = (struct Vector *)malloc(sizeof(struct Vector));
      *vector = createVector(amntWords);
      pushToVector(&wordsStructure, vector);
    }

    /* Populate wordsStructure */
    for (i = 0; i < amntWords; i++) {
      struct WordInfo *wordInfo =
          (struct WordInfo *)malloc(sizeof(struct WordInfo));
      unsigned long lengthWord;

      char *word = (char *)malloc(sizeof(char) * maxLengthWord);
      scanf("%s", word);

      wordInfo->available = 1;
      wordInfo->word = word;

      lengthWord = strlen(word);
      pushToVector((struct Vector *)wordsStructure.array[lengthWord], wordInfo);
    }

    /* ####################################################################################
     */

    hasSolution = process(&board, wordsStructure, amntWords);

    printf("Instancia %d\n", instance);
    if (hasSolution)
      printBoard(board);
    else
      printf("nao ha solucao");
    printf("\n");

    /* ####################################################################################
     */

    /* Free wordsStructure */
    for (i = 0; i <= wordsStructure.last; i++) {
      struct Vector *curWordsArray = wordsStructure.array[i];
      int j;
      for (j = 0; j <= curWordsArray->last; j++) {
        free(((struct WordInfo *)curWordsArray->array[j])
                 ->word);              /* string malloc */
        free(curWordsArray->array[j]); /* WordInfo malloc */
      }
      freeVector(*curWordsArray); /* create vectors inside wordsStructure */
      free(curWordsArray);        /* malloc vectors inside wordsStructure */
    }
    freeVector(wordsStructure); /* create wordsStructure vector */

    /* Free Matrix */
    freeBoard(board);
  }

  return 0;
}

char recProcess(struct Board *board, struct Vector wordsStructure,
                struct Position pos, char horiz) {
  int lengthWord, i;
  struct Vector *possibleWords;

  struct Position nextPos = horiz ? pos : nextPositionBoard(*board, pos);
  char nextHoriz = !horiz;

  if (pos.line < 0 && pos.column < 0)
    return 1;

  lengthWord = shouldAddWord(*board, pos, horiz);
  if (lengthWord < 2)
    return recProcess(board, wordsStructure, nextPos, nextHoriz);

  possibleWords = wordsStructure.array[lengthWord];

  for (i = 0; i <= possibleWords->last; i++) {
    struct WordInfo *infoWord = possibleWords->array[i];
    if (infoWord->available &&
        canAddThisWord(*board, infoWord->word, lengthWord, pos, horiz)) {
      char **copiedMatrix =
          cloneMatrix(board->matrix, board->lines, board->columns);
      char recRes;

      infoWord->available = 0;
      addWord(*board, infoWord->word, lengthWord, pos, horiz);

      recRes = recProcess(board, wordsStructure, nextPos, nextHoriz);

      if (recRes) {
        freeMatrix(copiedMatrix, board->lines);
        return 1;
      }

      infoWord->available = 1;
      freeMatrix(board->matrix, board->lines);
      board->matrix = copiedMatrix;
    }
  }

  return 0;
}

char process(struct Board *board, struct Vector wordsStructure, int amntWords) {
  struct Position pos;
  pos.line = 0;
  pos.column = 0;
  return recProcess(board, wordsStructure, pos, 1);
}

struct WordId {
  int length;
  int index;
};

struct WordInfo *getInfoWordFromId(struct Vector wordsStructure,
                                   struct WordId id) {
  struct Vector *wordWithLength = wordsStructure.array[id.length];
  return wordWithLength->array[id.index];
}

struct InfoBoardSemiFilled {
  char horiz;
  char **matrix;
  struct Position pos;
  struct WordId wordId;
};

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

#define FIRST_DIRECTION 1
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

char iterativeprocess(struct Board *finalBoard, struct Vector wordsStructure,
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
