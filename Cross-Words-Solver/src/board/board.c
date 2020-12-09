#include "board.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

struct Board readBoard() {
  struct Board board;
  int i;

  /* Amnt Matrix */
  printf("Number of board lines: ");
  scanf("%d", &board.lines);
  printf("Number of board columns: ");
  scanf("%d", &board.columns);

  if (board.lines == 0 || board.columns == 0) {
    board.matrix = NULL;
    return board;
  }

  /* Alloc and Populate matrix */
  printf("Now write the matrix cells:\n");
  board.matrix = (char **)malloc(sizeof(char *) * board.lines);
  for (i = 0; i < board.lines; i++) {
    int j;
    board.matrix[i] = (char *)malloc(sizeof(char) * board.columns);
    for (j = 0; j < board.columns; j++) {
      int d;
      scanf("%d", &d);
      if (d < 0)
        board.matrix[i][j] = BLACK_CELL;
      else
        board.matrix[i][j] = EMPTY_CELL;
    }
  }

  return board;
}

void freeBoard(struct Board *board) {
  if (board->matrix != NULL)
    freeMatrix(board->matrix, board->lines);
  board->matrix = NULL;
}

void printBoard(struct Board board) {
  printMatrix(board.matrix, board.lines, board.columns);
}

void printMatrix(char **matrix, int lines, int columns) {
  int i;
  for (i = 0; i < lines; i++) {
    int j;
    for (j = 0; j < columns; j++)
      printf("%c ", matrix[i][j]);
    printf("\n");
  }
}

char isInsideBoard(struct Board board, struct Position pos) {
  return pos.line >= 0 && pos.column >= 0 && pos.column < board.columns &&
         pos.line < board.lines;
}

char isBlackPosition(struct Board board, struct Position pos) {
  return board.matrix[pos.line][pos.column] == BLACK_CELL;
}
char isEmptyPosition(struct Board board, struct Position pos) {
  return board.matrix[pos.line][pos.column] == EMPTY_CELL;
}
char posHasLetter(struct Board board, struct Position pos) {
  return board.matrix[pos.line][pos.column] != EMPTY_CELL &&
         board.matrix[pos.line][pos.column] != BLACK_CELL;
}

position nextPositionBoard(struct Board board, struct Position pos) {
  pos.column++;
  if (isInsideBoard(board, pos))
    return pos;

  pos.column = 0;
  pos.line++;
  if (isInsideBoard(board, pos))
    return pos;

  pos.line = -1;
  pos.column = -1;
  return pos;
}

int lengthWordStartingAt(struct Board board, struct Position pos, char horiz) {
  int length;
  struct Position prevPos = pos;
  if (horiz)
    prevPos.column--;
  else
    prevPos.line--;
  if (isInsideBoard(board, prevPos) && !isBlackPosition(board, prevPos))
    return -1;

  for (length = 0;; length++, horiz ? pos.column++ : pos.line++)
    if (!isInsideBoard(board, pos) || isBlackPosition(board, pos))
      break;
  return length;
}

int shouldAddWord(struct Board board, struct Position pos, char horiz) {
  int lengthWord;
  if (isBlackPosition(board, pos))
    return 0;

  lengthWord = lengthWordStartingAt(board, pos, horiz);

  if (lengthWord < 2)
    return 0;
  return lengthWord;
}

char canAddThisWord(struct Board board, char *word, int length,
                    struct Position pos, char horiz) {
  int i;
  for (i = 0; i < length; i++, horiz ? pos.column++ : pos.line++)
    if (board.matrix[pos.line][pos.column] != EMPTY_CELL &&
        word[i] != board.matrix[pos.line][pos.column])
      return 0;
  return 1;
}

void addWord(struct Board board, char *word, int length, struct Position pos,
             char horiz) {
  int i;
  for (i = 0; i < length; i++, horiz ? pos.column++ : pos.line++)
    board.matrix[pos.line][pos.column] = word[i];
}
