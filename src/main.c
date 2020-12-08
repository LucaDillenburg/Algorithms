#include "data_structures/list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct list *list = newList();
  pushToList(list, newString("This is the first one"));
  pushToList(list, newString("That's the SECOND"));
  pushToList(list, newString("Now the THIRD"));
  pushToList(list, newString("4TH"));
  pushToList(list, newString("THAT'S THE LAST ONE (the 5th)"));
  printList(*list, (void (*)(void *))printString);
  return 0;
}