#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include "list.h"

#define HASH_TABLE_LENGTH 500

typedef struct hashtable {
  struct list *array;
  unsigned int (*hashingFunction)(void *);
  char (*keyIsEqualTo)(void *, void *);
} hashtable;

typedef struct {
  void *key;
  void *value;
} hashcell;

hashtable createHashTable(unsigned int (*hashingFunction)(void *),
                          char (*compareFunction)(void *, void *));
void freeInsideHashTable(struct hashtable table, void (*freeKey)(void *),
                         void (*freeItem)(void *));

void pushToHashTable(struct hashtable table, void *key, void *value);
void *getValueFromKey(struct hashtable table,
                      void *key); /* returns NULL if the Key doesn't exist */

#endif