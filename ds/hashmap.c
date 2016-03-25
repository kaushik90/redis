#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashmap.h"

hashTable* newHashMap(){
  int i,j;
  hashTable* ht = newHashTable();
  for(i=0;i<INITIAL_SIZE;i++){
    for(j=0;j<INITIAL_SIZE;j++){
      ht->table->rooms[i]->list[j] = newLinkedList();
    }
  }
  return ht;
}

void set(newString *key, newString *value, hashTable* ht){
  linkedList* ll;
  listNode *tmp=NULL;
  unsigned long p_hash = getPrimaryHash(key->buf);
  unsigned long s_hash = getSecondaryHash(key->buf);
  ll = ht->table->rooms[p_hash]->list[s_hash];
  if(ll->head){
    tmp = findNode(key, ll);
  }
  if(tmp){
    replaceValue(tmp, value);
  }else{
    tmp = newNode(key, value);
    addNodeToList(ll, tmp);
    ht->key_count++;
  }
}

char* get(newString *key, hashTable* ht){
  unsigned long p_hash = getPrimaryHash(key->buf) % INITIAL_SIZE;
  unsigned long s_hash = getSecondaryHash(key->buf) % INITIAL_SIZE;
  linkedList* ll = ht->table->rooms[p_hash]->list[s_hash];
  listNode* tmp=NULL;
  if(ll->head){
    tmp = findNode(key, ll);
  }
  if(tmp){
    return tmp->value->buf;
  }else{
    return NULL;
  }
}

void printHashTable(hashTable* ht){
  int i=0, j=0;
  linkedList* ll;
  printf("%s %ld\n", "No of keys: ",ht->key_count );
  for(i = 0; i<INITIAL_SIZE; i++){
    for(j = 0; j<INITIAL_SIZE; j++){
      ll = ht->table->rooms[i]->list[j];
      printf("%d %d %s\n", i, j, "----------------------- START ----------------------------" );
      printList(ll);
      printf("%d %d %s\n", i, j, "----------------------- END ------------------------------" );
    }
  }
}

int main(){
 int i,l,n;
 newString *k;
 newString *v;
 hashTable* ht = newHashMap();
 scanf("%d", &n);
 char key[100];
 char value[100];
 char *res;
 for(i=0;i<n;i++){
   scanf("%s", key);
   scanf("%s", value);
   l = strlen(key);
   k = buildNewString(key, l);
   l = strlen(value);
   v = buildNewString(value,l);
   printf("%s %s %s\n","saving...", k->buf, v->buf);
   set(k, v, ht);
 }

 printHashTable(ht);

 for(i=0;i<n;i++){
   scanf("%s", key);
   l = strlen(key);
   k = buildNewString(key, l);
   res = get(k, ht);
   if(res){
     printf("%s\n", res);
   }else{

   }
 }

}