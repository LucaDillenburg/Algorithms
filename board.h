#ifndef BOARD_H
#define BOARD_H

#define EMPTY_CELL '-'
#define BLACK_CELL '*'

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

char isBlackPosition(struct Board board, struct Position pos);
char isEmptyPosition(struct Board board, struct Position pos);

char isInsideBoard(struct Board board, struct Position pos);
position nextPositionBoard(struct Board board, struct Position pos);
/* direction: to the right and down */

int lengthWordStartingAt(struct Board board, struct Position pos,
                         char horiz); /*TODO: TEST*/
char canAddThisWord(struct Board board, char *word, int length,
                    struct Position pos, char horiz); /*TODO: TEST*/

#endif