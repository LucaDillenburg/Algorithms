#ifndef _LIST_H
#define _LIST_H

typedef struct list {
  struct listNode *first_node;
  struct listNode *last_node;
  struct listNode *current_node;
} list;

typedef struct listNode {
  struct listNode *next;
  void *info;
} listNode;

struct list createList();
void freeInsideList(list list);

void pushToList(struct list *list, void *elem);

void goToFirstNode(struct list *list);
void goToNextNode(struct list *list);
char currentNodeExist(struct list *list);
void *getCurrentInfo(struct list list);

#endif