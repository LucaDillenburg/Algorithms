#ifndef _MAIN_TESTS_H
#define _MAIN_TESTS_H

#include "../data_structures/hashtable.h"
#include "../data_structures/list.h"

char *newString(char *str);
void printStrList(struct list list);
void testList();
int fakeHashingFunction(char *str);
void freeString(char *str);
void freeIntPtr(int *d);
int *newInt(int d);
void printCellsList(struct list);
void printHashTable(struct hashtable);
void testHashTable();

#endif
