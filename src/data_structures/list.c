#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list *newList() {
  list *new_list = (list *)malloc(sizeof(list));
  new_list->first_node = NULL;
  new_list->last_node = NULL;
  return new_list;
}

void freeList(list *list, void (*freeItem)(void *)) {
  listNode *cur_node = list->first_node;
  while (cur_node != NULL) {
    freeItem(cur_node->info);
    free(cur_node);
  }
  free(list);
}

void pushToList(list *list, void *elem) {
  listNode *new_node = (listNode *)malloc(sizeof(listNode));
  new_node->info = elem;
  new_node->next = NULL;

  if (list->first_node == NULL) {
    list->first_node = new_node;
    list->last_node = new_node;
  } else {
    list->last_node->next = new_node;
    list->last_node = new_node;
  }
}

void printList(list list, void (*printElem)(void *)) {
  listNode *cur_node = list.first_node;
  int i;
  for (i = 0; cur_node != NULL; i++, cur_node = cur_node->next) {
    printf("%d: ", i);
    printElem(cur_node->info);
    printf("\n");
  }
}
