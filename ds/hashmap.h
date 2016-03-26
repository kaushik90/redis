#ifndef HASHMAP_H_   /* Include guard */
#define HASHMAP_H_
#include "utils.h"

hashTable* newHashMap();
cmdResult* setHashMap( hashTable*, newString *, newString *);
cmdResult* getHashMap( hashTable*, newString *);
void printHashTable(hashTable*);

#endif