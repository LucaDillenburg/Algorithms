#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include "list.h"

typedef struct {
  struct list *array;
  int (*hashingFunction)(void *);
  int (*compareFunction)(void *, void *);
} hashtable;

typedef struct {
  void *key;
  void *value;
} hashcell;

hashtable createHashTable(int (*hashingFunction)(void *),
                          int (*compareFunction)(void *, void *));
void pushToHashTable(hashtable table, void *key, void *value);
void *getValueFromKey(hashtable table, void *key);
void freeHashTable(hashtable list);

#endif