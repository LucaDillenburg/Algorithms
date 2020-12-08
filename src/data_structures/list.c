#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list createList() {
  list created_list;
  created_list.first_node = NULL;
  created_list.last_node = NULL;
  created_list.current_node = NULL;
  return created_list;
}

void freeInsideList(list list) {
  listNode *cur_node = list.first_node;
  while (cur_node != NULL) {
    listNode *next = cur_node->next;
    free(cur_node);
    cur_node = next;
  }
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

void goToFirstNode(struct list *list) { list->current_node = list->first_node; }
void goToNextNode(struct list *list) {
  list->current_node = list->current_node->next;
}
char currentNodeExist(struct list *list) { return list->current_node != NULL; }
void *getCurrentInfo(struct list list) { return list.current_node->info; }
