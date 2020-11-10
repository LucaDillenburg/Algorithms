#include "process.h"
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

struct DataToProcess {
  struct Board board;
  struct Vector wordsStructure;
  int amntWords;
};

struct DataToProcess *readDataToProcess();
void freeDataToProcess(struct DataToProcess *);
void printWords(struct Vector wordsStructure);

int main() {
  int instance;
  struct Vector dataToProcessVector =
      createVector(1); /* TODO: change this value */
  for (instance = 0;; instance++) {
    struct DataToProcess *dataToProcess = readDataToProcess();
    if (dataToProcess == NULL)
      break;
    pushToVector(&dataToProcessVector, dataToProcess);
  }

  printf("\n");

  for (instance = 0; instance <= dataToProcessVector.last; instance++) {
    struct DataToProcess *curDataToProcess =
        dataToProcessVector.array[instance];
    char hasSolution =
        process(&curDataToProcess->board, curDataToProcess->wordsStructure,
                curDataToProcess->amntWords);

    printf("Instancia %d\n", instance + 1);
    if (hasSolution)
      printBoard(curDataToProcess->board);
    else
      printf("nao ha solucao");
    printf("\n");

    /* ################################################################## */
    freeDataToProcess(curDataToProcess);
  }

  freeVector(dataToProcessVector);

  return 0;
}

struct DataToProcess *readDataToProcess() {
  struct DataToProcess *dataToProcess = malloc(sizeof(struct DataToProcess));
  int i, maxLengthWord;

  /* Board */
  dataToProcess->board = readBoard();
  if (dataToProcess->board.lines == 0 || dataToProcess->board.columns == 0)
    return NULL;

  /* Amnt wordsStructure */
  scanf("%d", &dataToProcess->amntWords);

  /* Alloc wordsStructure */
  maxLengthWord =
      max(dataToProcess->board.columns, dataToProcess->board.lines) + 1;
  dataToProcess->wordsStructure = createVector(maxLengthWord);
  for (i = 0; i < dataToProcess->wordsStructure.length; i++) {
    struct Vector *vector = (struct Vector *)malloc(sizeof(struct Vector));
    *vector = createVector(dataToProcess->amntWords);
    pushToVector(&dataToProcess->wordsStructure, vector);
  }

  /* Populate wordsStructure */
  for (i = 0; i < dataToProcess->amntWords; i++) {
    struct WordInfo *wordInfo =
        (struct WordInfo *)malloc(sizeof(struct WordInfo));
    unsigned long lengthWord;

    char *word = (char *)malloc(sizeof(char) * maxLengthWord);
    scanf("%s", word);

    wordInfo->available = 1;
    wordInfo->word = word;

    lengthWord = strlen(word);
    pushToVector(
        (struct Vector *)dataToProcess->wordsStructure.array[lengthWord],
        wordInfo);
  }

  return dataToProcess;
}

void freeDataToProcess(struct DataToProcess *dataToProcess) {
  int i;

  /* Free wordsStructure */
  for (i = 0; i <= dataToProcess->wordsStructure.last; i++) {
    struct Vector *curWordsArray = dataToProcess->wordsStructure.array[i];
    int j;
    for (j = 0; j <= curWordsArray->last; j++) {
      free(((struct WordInfo *)curWordsArray->array[j])
               ->word);              /* string malloc */
      free(curWordsArray->array[j]); /* WordInfo malloc */
    }
    freeVector(*curWordsArray); /* create vectors inside wordsStructure */
    free(curWordsArray);        /* malloc vectors inside wordsStructure */
  }
  freeVector(dataToProcess->wordsStructure); /* create wordsStructure vector */

  /* Free Matrix */
  freeBoard(&dataToProcess->board);

  /* Free DataToProcess */
  free(dataToProcess);
}

/* ######################################################################### */

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
