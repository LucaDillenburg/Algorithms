#ifndef BOARD_H
#define BOARD_H

#define EMPTY_CELL '-'
#define NOT_LETTER_CELL '*'

typedef struct Board {
  char **matrix;
  int lines;
  int columns;
} board;

typedef struct Position {
  int line;
  int column;
} position;

struct Board readBoard();
void freeBoard();
void printBoard(struct Board board);

char isLetterPosition(struct Board board, struct Position pos);

char isInsideBoard(struct Board board, struct Position pos);
position nextPositionBoard(struct Board board, struct Position pos);
/* direction: to the right and down */

/* char isBeginningOfWord(board board, int i, int j, char horiz); */
/* char canAddThisWord(board board, char *word, int i, int j); */

#endif