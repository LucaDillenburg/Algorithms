#include "data_structures/list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void printStrList(struct list list) {
  int i;
  for (i = 0, goToFirstNode(&list); currentNodeExist(&list);
       goToNextNode(&list), i++) {
    char *str = (char *)getCurrentInfo(list);
    printf("%d: %s\n", i, str);
  }
}

void _freeListElem(char *str, void *args) { free(str); }

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

int main() {
  testList();
  return 0;
}
