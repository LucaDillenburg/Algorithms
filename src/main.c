#include "data_structures/list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void printEachStr(int i, char *str) { printf("%d: %s\n", i, str); }

void _freeListElem(char *str, void *args) { free(str); }

void testList() {
  struct list *list = newList();
  pushToList(list, newString("This is the first one"));
  pushToList(list, newString("That's the SECOND"));
  pushToList(list, newString("Now the THIRD"));
  pushToList(list, newString("4TH"));
  pushToList(list, newString("THAT'S THE LAST ONE (the 5th)"));
  forEachList(*list, (void (*)(int, void *))printEachStr);
  freeList(list, (void (*)(void *, void *))_freeListElem, NULL);
}

int main() {
  testList();
  return 0;
}
