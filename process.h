#ifndef PROCESS_H
#define PROCESS_H

#include "board.h"
#include "utils.h"
#include "vector.h"

struct WordId {
  int length;
  int index;
};

struct WordInfo {
  char *word;
  char available;
};

struct InfoBoardSemiFilled {
  char horiz;
  char **matrix;
  struct Position pos;
  struct WordId wordId;
};

char process(struct Board *finalBoard, struct Vector wordsStructure,
             int amntWords);
struct Vector getAvailablePaths(struct Board board,
                                struct Vector wordsStructure, int prevHoriz,
                                struct Position prevPos);
struct WordInfo *getInfoWordFromId(struct Vector wordsStructure,
                                   struct WordId id);
struct InfoBoardSemiFilled *newInfoBoardSemiFilled(char horiz, char **matrix,
                                                   struct Position pos,
                                                   struct WordId wordId);
#endif