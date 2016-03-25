#ifndef HASHTABLE_H_   /* Include guard */
#define HASHTABLE_H_

typedef struct secondaryTable
{
  unsigned long size;
  struct linkedList *list[];
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

#endif