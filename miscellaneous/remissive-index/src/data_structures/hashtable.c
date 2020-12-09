#include "hashtable.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct hashtable createHashTable(unsigned int (*hashingFunction)(void *),
                                 char (*keyIsEqualTo)(void *, void *)) {
  struct hashtable created_hash;
  int i;

  created_hash.array =
      (struct list *)malloc(sizeof(struct list) * HASH_TABLE_LENGTH);
  for (i = 0; i < HASH_TABLE_LENGTH; i++)
    created_hash.array[i] = createList();

  created_hash.hashingFunction = hashingFunction;
  created_hash.keyIsEqualTo = keyIsEqualTo;
  return created_hash;
}

void freeCellsList(struct list cells_list, void (*freeKey)(void *),
                   void (*freeValue)(void *)) {
  for (goToFirstNode(&cells_list); currentNodeExist(&cells_list);
       goToNextNode(&cells_list)) {
    hashcell *cell = (hashcell *)getCurrentInfo(cells_list);
    freeKey(cell->key);
    freeValue(cell->value);
    free(cell);
  }
}

void freeInsideHashTable(struct hashtable table, void (*freeKey)(void *),
                         void (*freeValue)(void *)) {
  int i;
  for (i = 0; i < HASH_TABLE_LENGTH; i++) {
    struct list cur_list = table.array[i];
    freeCellsList(cur_list, freeKey, freeValue);
  }
}

struct hashcell *pushToHashTable(struct hashtable table, void *key,
                                 void *value) {
  unsigned int index = (*table.hashingFunction)(key) % HASH_TABLE_LENGTH;
  struct hashcell *cell = (struct hashcell *)malloc(sizeof(struct hashcell));
  cell->key = key;
  cell->value = value;
  pushToList(&table.array[index], cell);
  return cell;
}

void *getValueFromKey(struct hashtable table, void *key) {
  unsigned int index = (*table.hashingFunction)(key) % HASH_TABLE_LENGTH;
  struct list cells_list = table.array[index];
  for (goToFirstNode(&cells_list); currentNodeExist(&cells_list);
       goToNextNode(&cells_list)) {
    hashcell *cell = (hashcell *)getCurrentInfo(cells_list);
    char cmp = (*table.keyIsEqualTo)(key, cell->key);
    if (cmp)
      return cell->value;
  }
  return NULL;
}
