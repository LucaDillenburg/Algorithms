#ifndef _TESTS
#define _TESTS

#include "../data_structures/hashtable.h"
#include "../data_structures/list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
