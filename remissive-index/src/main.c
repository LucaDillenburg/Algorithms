#include "data_structures/hashtable.h"
#include "data_structures/vector.h"
#include "tests/tests.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_FILE_NAME 200
#define AVG_WORDS 2000

typedef struct wordOccurance {
  int line;
  int amount;
} wordOccurance;

void printWords(struct vector word_cells_ptrs);
void printHashTable(struct hashtable table);

void freeString(char *str);
void freeListOccurances(struct list *list);

struct wordOccurance *newWordOccurance(int line);
struct wordOccurance *getOccuranceInLine(struct list list_of_occurances,
                                         int line);

int main() {
  FILE *file;
  struct hashtable table =
      createHashTable((unsigned int (*)(void *))hashForString,
                      (char (*)(void *, void *))stringIsEqualTo);
  int cur_line = 1;
  struct vector word_cells_ptrs = createVector(AVG_WORDS);

  char file_name[MAX_LENGTH_FILE_NAME];
  scanf(" %[^\n]", file_name);

  file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Error: couldn't open file '%s'!\n", file_name);
    return 1;
  }

  while (1) {
    int next_word_line_index = cur_line;
    char *str = nextWordInFile(file, &next_word_line_index);
    struct list *list_of_occurances = NULL;
    if (str == NULL)
      break;

    list_of_occurances = (struct list *)getValueFromKey(table, str);
    if (list_of_occurances == NULL) {
      struct list *new_list_of_occurances =
          (struct list *)malloc(sizeof(struct list));
      struct hashcell *cell;
      *new_list_of_occurances = createList();
      pushToList(new_list_of_occurances, newWordOccurance(cur_line));
      cell = pushToHashTable(table, str, new_list_of_occurances);
      pushToVector(&word_cells_ptrs, cell);
    } else {
      struct wordOccurance *occurance_in_line =
          getOccuranceInLine(*list_of_occurances, cur_line);
      if (occurance_in_line == NULL)
        pushToList(list_of_occurances, newWordOccurance(cur_line));
      else
        occurance_in_line->amount++;
    }
    cur_line = next_word_line_index;
  }

  sortCells((struct hashcell **)word_cells_ptrs.array, word_cells_ptrs.last);
  printWords(word_cells_ptrs);

  freeInsideVector(word_cells_ptrs);
  freeInsideHashTable(table, (void (*)(void *))freeString,
                      (void (*)(void *))freeListOccurances);

  return 0;
}

/* MAIN */

struct wordOccurance *getOccuranceInLine(struct list list_of_occurances,
                                         int line) {
  goToFirstNode(&list_of_occurances);
  while (currentNodeExist(&list_of_occurances)) {
    struct wordOccurance *cur_occurance =
        (struct wordOccurance *)getCurrentInfo(list_of_occurances);
    if (cur_occurance->line == line)
      return cur_occurance;
    goToNextNode(&list_of_occurances);
  }
  return NULL;
}

struct wordOccurance *newWordOccurance(int line) {
  struct wordOccurance *new_occurance =
      (struct wordOccurance *)malloc(sizeof(struct wordOccurance));
  new_occurance->amount = 1;
  new_occurance->line = line;
  return new_occurance;
}

void printStrVector(struct vector vector) {
  int i;
  for (i = 0; i <= vector.last; i++)
    printf("'%s', ", (char *)vector.array[i]);
}

/* FREE */

void freeString(char *str) { free(str); }
void freeListOccurances(struct list *list) {
  return;
  goToFirstNode(list);
  while (currentNodeExist(list)) {
    struct wordOccurance *cur_occurance =
        (struct wordOccurance *)getCurrentInfo(*list);
    free(cur_occurance);
    goToNextNode(list);
  }
  free(list);
}

/* PRINTING */

void printWords(struct vector word_cells_ptrs) {
  int i;
  for (i = 0; i <= word_cells_ptrs.last; i++) {
    struct hashcell *cur_cell = word_cells_ptrs.array[i];
    struct list *list_of_occurances;
    printf("%s: ", (char *)cur_cell->key);

    list_of_occurances = cur_cell->value;
    for (goToFirstNode(list_of_occurances);
         currentNodeExist(list_of_occurances);
         goToNextNode(list_of_occurances)) {
      struct wordOccurance *cur_occurance =
          (struct wordOccurance *)getCurrentInfo(*list_of_occurances);
      if (cur_occurance->amount == 1)
        printf("%d ", cur_occurance->line);
      else
        printf("%d(%d) ", cur_occurance->line, cur_occurance->amount);
    }

    printf("\n");
  }
}
