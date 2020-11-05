#include "board.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/*
Observavoes
- Backtracking com Pilha
- Podem sobrar palavras na lista
- Outro: verificar se a palavra nao se cruza com nenhuma outra
- Otimizacao: Ter um vetor de vetores em que em cada posicao do vetor maior ha
as palavras do vetor menor
*/

void process(struct Board board, char **words, int amntWords);

int main() {
  int instance;
  for (instance = 1;; instance++) {
    struct Board board;
    int amntWords, i;
    char **words;
    int maxLengthWord;

    /* Board */
    board = readBoard();
    if (board.lines == 0 || board.columns == 0)
      break;

    /* Amnt Words */
    scanf("%d", &amntWords);

    /* Alloc and Populate Words */
    maxLengthWord = max(board.columns, board.lines) + 1;
    words = (char **)malloc(sizeof(char *) * amntWords);
    for (i = 0; i < amntWords; i++) {
      words[i] = (char *)malloc(sizeof(char) * maxLengthWord);
      scanf("%s", words[i]);
    }

    /* ####################################################################################
     */
    printf("Processing...\n");
    process(board, words, amntWords);

    printf("Instancia %d\n", instance);
    printBoard(board);

    /* ####################################################################################
     */
    printf("Freeing...\n");

    /* Free Words */
    for (i = 0; i < amntWords; i++) {
      free(words[i]);
    }
    free(words);

    /* Free Matrix */
    freeBoard(board);
  }

  return 0;
}

void process(struct Board board, char **words, int amntWords) {
  /*
  int j;
  printf("h (lines): %d, w (columns): %d\n", board.height, board.width);
  for (j=-2; j<=board.height; j++) {
          int i;
          printf("%d: ", j);
          for (i=-2; i<=board.width; i++)
                  if (isInsideBoard(board, i, j))
                          printf("y ");
                  else
                          printf("n ");
          printf("\n");
  }
  */
}
