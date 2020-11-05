#include "board.h"
#include <stdio.h>
#include <stdlib.h>

struct Board readBoard() {
  struct Board board;
  int i;

  /* Amnt Matrix */
  scanf("%d %d", &board.lines, &board.columns);
  if (board.lines == 0 || board.columns == 0) {
    board.matrix = NULL;
    return board;
  }

  /* Alloc and Populate matrix */
  board.matrix = (char **)malloc(sizeof(char *) * board.lines);
  for (i = 0; i < board.lines; i++) {
    int j;
    board.matrix[i] = (char *)malloc(sizeof(char) * board.columns);
    for (j = 0; j < board.columns; j++) {
      int d;
      scanf("%d", &d);
      if (d < 0)
        board.matrix[i][j] = NOT_LETTER_CELL;
      else
        board.matrix[i][j] = EMPTY_CELL;
    }
  }

  return board;
}

void freeBoard(struct Board board) {
  int i;
  for (i = 0; i < board.lines; i++) {
    free(board.matrix[i]);
  }
  free(board.matrix);
}

void printBoard(struct Board board) {
  int i;
  for (i = 0; i < board.lines; i++) {
    int j;
    for (j = 0; j < board.columns; j++)
      printf("%c ", board.matrix[i][j]);
    printf("\n");
  }
}

char isInsideBoard(struct Board board, struct Position pos) {
  return pos.line >= 0 && pos.column >= 0 && pos.column < board.columns &&
         pos.line < board.lines;
}

char isLetterPosition(struct Board board, struct Position pos) {
  return board.matrix[pos.line][pos.column] != NOT_LETTER_CELL;
}

position nextPositionBoard(struct Board board, struct Position pos) {
  pos.line++;
  if (isInsideBoard(board, pos))
    return pos;

  pos.line = 0;
  pos.column++;
  if (isInsideBoard(board, pos))
    return pos;

  pos.line = 0;
  pos.column = 0;
  return pos;
}

/*
char isBeginningOfWord(board board, int i, int j, char horiz) {
        pair posBefore;
        if (horiz) {
                posBefore.first = i-1;
                posBefore.second = j;
        } else {
                posBefore.first = i;
                posBefore.second = j-1;
        }
}
*/