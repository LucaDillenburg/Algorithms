#ifndef PROCESS_H
#define PROCESS_H

#include "board.h"
#include "specialStack.h"
#include "utils.h"
#include "vector.h"

struct PosHoriz {
  struct Position pos;
  char horiz;
};

char process(struct Board *finalBoard, struct Vector wordsStructure,
             int amntWords);
struct Vector getAvailablePaths(struct Board board,
                                struct Vector wordsStructure, int prevHoriz,
                                struct Position prevPos);

/* auxiliar */
struct PosHoriz getNextPosHoriz(struct Board board, struct Position pos,
                                char horiz);

struct WordInfo *getInfoWordFromId(struct Vector wordsStructure,
                                   struct WordId id);
struct InfoBoardSemiFilled *newInfoBoardSemiFilled(char horiz, char **matrix,
                                                   struct Position pos,
                                                   struct WordId wordId);
#endif