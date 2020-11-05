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

void process(struct Board board, struct Vector wordsStructure, int amntWords);
void printWords(struct Vector wordsStructure);

int main() {
  int instance;
  for (instance = 1;; instance++) {
    struct Board board;
    int amntWords, i;
    struct Vector wordsStructure;
    int maxLengthWord;

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
      char *word = (char *)malloc(sizeof(char) * maxLengthWord);
      unsigned long lengthWord;
      scanf("%s", word);
      lengthWord = strlen(word);
      pushToVector((struct Vector *)wordsStructure.array[lengthWord], word);
    }

    /* ####################################################################################
     */

    printWords(wordsStructure);

    printf("Processing...\n");
    process(board, wordsStructure, amntWords);

    printf("Instancia %d\n", instance);
    printBoard(board);

    /* ####################################################################################
     */

    /* Free wordsStructure */
    for (i = 0; i < wordsStructure.length; i++) {
      struct Vector *curWordsArray = wordsStructure.array[i];
      int j;
      for (j = 0; j <= curWordsArray->last; j++)
        free(curWordsArray->array[j]); /* string malloc */
      freeVector(*curWordsArray); /* create vectors inside wordsStructure */
      free(curWordsArray);        /* malloc vectors inside wordsStructure */
    }
    freeVector(wordsStructure); /* create wordsStructure vector */

    /* Free Matrix */
    freeBoard(board);
  }

  return 0;
}

void process(struct Board board, struct Vector wordsStructure, int amntWords) {
  struct Position pos;
  pos.line = 0;
  pos.column = 0;
  for (;;) {
    if (!isBlackPosition(board, pos)) {
      int lengthWordHoriz = lengthWordStartingAt(board, pos, 0);
      if (lengthWordHoriz >= 2) {
        /* TODO: process */
        board.matrix[pos.line][pos.column] = '+';
      }

      /*
      int lengthWordVert = lengthWordStartingAt(board, pos, 1);
      if (lengthWordVert >= 2) {
        board.matrix[pos.line][pos.column] = '+';
      }
      */
    }
    pos = nextPositionBoard(board, pos);
    if (pos.column == 0 && pos.line == 0)
      break;
  }
}

void printWords(struct Vector wordsStructure) {
  int i;
  for (i = 0; i < wordsStructure.length; i++) {
    struct Vector *curWordsArray = wordsStructure.array[i];
    int j;

    printf("%3d: | ", i);
    for (j = 0; j <= curWordsArray->last; j++) {
      if (j != 0)
        printf("     | ");
      printf("%s\n", (char *)curWordsArray->array[j]);
    }
    printf("\n");
  }
}
