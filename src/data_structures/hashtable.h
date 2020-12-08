#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include "list.h"

#define HASH_TABLE_LENGTH 25000

typedef struct hashtable {
  struct list *array;
  unsigned int (*hashingFunction)(void *);
  char (*keyIsEqualTo)(void *, void *);
} hashtable;

typedef struct {
  void *key;
  void *value;
} hashcell;

struct hashtable createHashTable(unsigned int (*hashingFunction)(void *),
                                 char (*keyIsEqualTo)(void *, void *));
void freeInsideHashTable(struct hashtable table, void (*freeKey)(void *),
                         void (*freeItem)(void *));

void pushToHashTable(struct hashtable table, void *key, void *value);
void *getValueFromKey(struct hashtable table,
                      void *key); /* returns NULL if the Key doesn't exist */

#endif