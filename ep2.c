#include "board.h"
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
struct WordChoosenInfo *getChoosenWord(struct Board board,
                                       struct Vector wordsStructure,
                                       int lengthWord, struct Position pos,
                                       int horiz);
void printWords(struct Vector wordsStructure);

struct WordInfo {
  char *word;
  char available;
};
struct WordChoosenInfo {
  int length;
  int index;
  struct Position pos;
  char horiz;
  char **matrix;
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

/*
char process(struct Board board, struct Vector wordsStructure, int amntWords) {
  struct Vector stack = createVector(amntWords+2);
  struct WordChoosenInfo first;
  first.length = -1;
  first.index = -1;
  first.pos.line = 0;
  first.pos.column = 0;
  first.pos.horiz = 0;

  for (;;) {
    printf("(%d, %d): ", pos.line, pos.column);
    if (!isBlackPosition(board, pos)) {
      char horiz;
      int lengthWord;

      horiz = 0;
      lengthWord = lengthWordStartingAt(board, pos, horiz);
      if (lengthWord >= 2) {
        struct WordChoosenInfo* choosenWord = getChoosenWord(board,
wordsStructure, lengthWord, pos, horiz); if (choosenWord != NULL)
          pushToVector(&stack, choosenWord);
        else {
          / * TODO: BACK-TRACK * /
          return 1;
        }
      }

      / * TODO: horiz=1 * /
    }
    pos = nextPositionBoard(board, pos);
    if (pos.column < 0 && pos.line < 0)
      break;
  }
  return 1;
}

struct WordChoosenInfo* getChoosenWord(struct Board board, struct Vector
wordsStructure, int lengthWord, struct Position pos, int horiz) { struct Vector
*possibleWords = wordsStructure.array[lengthWord]; int i; for (i=0;
i<=possibleWords->last; i++) { struct WordInfo *curWordInfo =
possibleWords->array[i]; if (curWordInfo->available && canAddThisWord(board,
curWordInfo->word, lengthWord, pos, horiz)) { struct WordChoosenInfo
*choosenWord;

      curWordInfo->available = 0;
      addWord(board, curWordInfo->word, lengthWord, pos, horiz);

      choosenWord = (struct WordChoosenInfo *)malloc(sizeof(struct
WordChoosenInfo)); choosenWord->length = lengthWord; choosenWord->index = i;
      choosenWord->pos = pos;
      choosenWord->horiz = horiz;
      return choosenWord;
    }
  }

  return NULL;
}
*/

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
