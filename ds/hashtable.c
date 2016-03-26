#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

secondaryTable* newSecondaryTable(){
  int i;
  secondaryTable* st = (secondaryTable*)malloc(sizeof(secondaryTable) + INITIAL_SIZE * sizeof(void *));
  for(i=0;i<INITIAL_SIZE;i++) st->list[i] = NULL;
  st->size = INITIAL_SIZE;
  return st;
}

primaryTable* newPrimaryTable(){
  int i;
  primaryTable* pt = (primaryTable*)malloc(sizeof(primaryTable) + INITIAL_SIZE * sizeof(secondaryTable *));
  for(i=0;i<INITIAL_SIZE;i++) pt->rooms[i]=newSecondaryTable();
  pt->size = INITIAL_SIZE;
  return pt;
}

hashTable* newHashTable(){
  int i;
  hashTable* ht = (hashTable*)malloc(sizeof(hashTable));
  ht->table = newPrimaryTable();
  ht->key_count = 0;
  ht->collision_ratio = 0;
  return ht;
}

// int main(){
//  int i,l;
//  newString *k;
//  newString *v;
//  hashTable* ht = (hashTable*)malloc(sizeof(hashTable));
//  ht = newHashTable();
//  int n;
//  scanf("%d", &n);
//  char key[100];
//  char value[100];
//  char *res;
//  for(i=0;i<n;i++){
//    scanf("%s", key);
//    scanf("%s", value);
//    l = strlen(key);
//    k = buildNewString(key, l);
//    l = strlen(value);
//    v = buildNewString(value,l);
//    printf("%s %s %s\n","saving...", k->buf, v->buf);
//    set(k, v, ht);
//  }

//  printHashTable(ht);

//  for(i=0;i<n;i++){
//    scanf("%s", key);
//    l = strlen(key);
//    k = buildNewString(key, l);
//    res = get(k, ht);
//    if(res){
//      printf("%s\n", res);
//    }else{

//    }
//  }

// }