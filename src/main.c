#include "data_structures/hashtable.h"
#include "tests/tests.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_FILE_NAME 100

typedef struct wordOccurance {
  int line;
  int amount;
} wordOccurance;

struct wordOccurance *newWordOccurance(int line);
struct wordOccurance *getOccuranceInLine(struct list list_of_occurances,
                                         int line);

int main() {
  FILE *file;
  struct hashtable table =
      createHashTable((unsigned int (*)(void *))hashForString,
                      (char (*)(void *, void *))stringIsEqualTo);
  int cur_line = 0;

  char file_name[MAX_LENGTH_FILE_NAME];
  scanf("%s", file_name);

  file = fopen(file_name, "r");
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
      *new_list_of_occurances = createList();
      pushToList(new_list_of_occurances, newWordOccurance(cur_line));
      pushToHashTable(table, str, new_list_of_occurances);
    } else {
      struct wordOccurance *occurance_in_line =
          getOccuranceInLine(*list_of_occurances, cur_line);
      if (occurance_in_line == NULL)
        pushToList(list_of_occurances, newWordOccurance(cur_line));
      else
        occurance_in_line->amount++;
    }

    free(str);
    cur_line = next_word_line_index;
  }

  return 0;
}

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
