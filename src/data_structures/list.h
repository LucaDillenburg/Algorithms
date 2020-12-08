#ifndef _UTILS_H
#define _UTILS_H

typedef struct List {
  struct List *next;
  void *info;
} list;

list *newList(void *first_elem);
void pushToList(list list, void *elem);
void printList(list list);
void freeList(list *list);

#endif