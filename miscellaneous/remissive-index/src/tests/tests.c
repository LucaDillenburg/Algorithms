#include "tests.h"
#include "../data_structures/hashtable.h"
#include "../data_structures/list.h"
#include "../data_structures/vector.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ######################### UTILS ######################### */

char *newString(char *str) {
  char *new_str = (char *)malloc(sizeof(char) * 100);
  int i;
  for (i = 0;; i++)
    if (str[i] == '\0')
      break;
    else
      new_str[i] = str[i];
  return new_str;
}

/* ######################### TEST LIST ######################### */

void printStrList(struct list list) {
  int i;
  for (i = 0, goToFirstNode(&list); currentNodeExist(&list);
       goToNextNode(&list), i++) {
    char *str = (char *)getCurrentInfo(list);
    printf("%d: %s\n", i, str);
  }
}

void testList() {
  struct list list = createList();
  pushToList(&list, newString("This is the first one"));
  pushToList(&list, newString("That's the SECOND"));
  pushToList(&list, newString("Now the THIRD"));
  pushToList(&list, newString("4TH"));
  pushToList(&list, newString("THAT'S THE LAST ONE (the 5th)"));
  printStrList(list);
  freeInsideList(list);
}

/* ######################### TEST HASHTABLE ######################### */

unsigned int fakeHashingFunction(char *str) {
  if (!strcmp(str, "Hello World"))
    return 1;
  if (!strcmp(str, "str"))
    return 6;
  if (!strcmp(str, "Hello Luca"))
    return 5;
  return 101;
}

void freeStringTest(char *str) { free(str); }
void freeIntPtr(int *d) { free(d); }
int *newInt(int d) {
  int *ptr = (int *)malloc(sizeof(int));
  *ptr = d;
  return ptr;
}

void printCellsList(struct list cells_list) {
  for (goToFirstNode(&cells_list); currentNodeExist(&cells_list);
       goToNextNode(&cells_list)) {
    hashcell *cell = (hashcell *)getCurrentInfo(cells_list);
    printf("(%s => %d), ", (char *)cell->key, *(int *)cell->value);
  }
}

void printHashTableTest(struct hashtable table) {
  int i;
  printf("Printing Hash...\n");
  for (i = 0; i < HASH_TABLE_LENGTH; i++) {
    struct list cur_list = table.array[i];
    if (cur_list.first_node != NULL) {
      printf("%d: ", i);
      printCellsList(cur_list);
      printf("\n");
    }
  }
  printf("\n");
}

void testHashTable() {
  struct hashtable table =
      createHashTable((unsigned int (*)(void *))fakeHashingFunction,
                      (char (*)(void *, void *))stringIsEqualTo);

  pushToHashTable(table, newString("Hello World"), newInt(1));
  pushToHashTable(table, newString("Hello Luca"), newInt(2));
  pushToHashTable(table, newString("My name is Luca"), newInt(3));
  pushToHashTable(table, newString("I want coffee"), newInt(4));
  pushToHashTable(table, newString("I am the best"), newInt(10));

  printHashTableTest(table);

  printf("\n\nValue: %d\n",
         *(int *)getValueFromKey(table, newString("I want coffee")));
  printf("Value: %d\n",
         *(int *)getValueFromKey(table, newString("My name is Luca")));
  printf("Value: %d\n",
         *(int *)getValueFromKey(table, newString("I am the best")));
  if (getValueFromKey(table, newString("str")) != NULL)
    printf("NOT NULLL!!! WRONGGG!");
  else
    printf("null, fine");

  freeInsideHashTable(table, (void (*)(void *))freeStringTest,
                      (void (*)(void *))freeIntPtr);
}

/* ######################### GET WORD FROM FILE ######################### */

void testGetWord() {
  FILE *file = fopen("./src/tests/file", "r");
  while (1) {
    int line = 0;
    char *str = nextWordInFile(file, &line);
    if (str == NULL)
      break;
    printf("'%s' | pulou linha: %d\n", str, line);
    free(str);
  }
}

/* ######################### VECTOR ######################### */

void printVectorIntPtr(struct vector vector) {
  int i;
  printf("length: %2d, last: %2d | ", vector.length, vector.last);
  for (i = 0; i <= vector.last; i++)
    printf("%d ", *(int *)vector.array[i]);
  printf("\n");
}

void testVector() {
  struct vector vector = createVector(2);

  pushToVector(&vector, newInt(1));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(2));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(3));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(4));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(5));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(6));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(7));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(8));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(9));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);
  pushToVector(&vector, newInt(10));
  printVectorIntPtr(vector);

  freeInsideVector(vector);
}

/* ######################### SORT ######################### */

void printWordsTest(struct vector word_cells_ptrs) {
  int i;
  for (i = 0; i <= word_cells_ptrs.last; i++) {
    struct hashcell *cur_cell = word_cells_ptrs.array[i];
    printf("%s\n", (char *)cur_cell->key);
  }
}

struct hashcell *newHashCell(char *key) {
  struct hashcell *cell = (struct hashcell *)malloc(sizeof(struct hashcell));
  cell->key = key;
  cell->value = (struct list *)malloc(sizeof(struct list));
  return cell;
}

void testSort() {
  struct vector vector = createVector(5);
  pushToVector(&vector, newHashCell("ola"));
  pushToVector(&vector, newHashCell("eu"));
  pushToVector(&vector, newHashCell("tres"));
  pushToVector(&vector, newHashCell("anos"));
  pushToVector(&vector, newHashCell("eh"));
  pushToVector(&vector, newHashCell("muita"));
  pushToVector(&vector, newHashCell("coisa"));
  pushToVector(&vector, newHashCell("ABC"));
  pushToVector(&vector, newHashCell("ABB"));
  pushToVector(&vector, newHashCell("ABA"));

  sortCells((struct hashcell **)vector.array, vector.last);
  printWordsTest(vector);
}
