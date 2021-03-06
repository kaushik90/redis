#ifndef HASHTABLE_H_   /* Include guard */
#define HASHTABLE_H_
#include "linkedlist.h"
#include "constants.h"

typedef struct secondaryTable
{
  unsigned long size;
  void *list[];
}secondaryTable;

typedef struct primaryTable
{
  unsigned long size;
  struct secondaryTable *rooms[];
}primaryTable;

typedef struct hashTable
{
  unsigned long key_count;
  unsigned int collision_ratio;
  struct primaryTable *table;
}hashTable;

hashTable* newHashTable();
primaryTable* newPrimaryTable();
secondaryTable* newSecondaryTable();

#endif