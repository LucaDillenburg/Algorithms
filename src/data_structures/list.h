#ifndef _LIST_H
#define _LIST_H

typedef struct list {
  struct listNode *first_node;
  struct listNode *last_node;
} list;

typedef struct listNode {
  struct listNode *next;
  void *info;
} listNode;

struct list *newList();
void freeList(list *list, void (*freeItem)(void *, void *args), void *args);

void pushToList(struct list *list, void *elem);

void forEachList(list list, void (*function)(int, void *));

#endif