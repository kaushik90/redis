#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "hashtable.h"

long getPrimaryHash(char *str){
  long hash = 5381;
  int c;
  while (*str != '\0'){
    c = *str++;
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}

long getSecondaryHash(char *str){
  long hash = 0;
  int c;
  while (*str != '\0'){
    c = *str++;
    hash = c + (hash << 6) + (hash << 16) - hash;
  }
  return hash;
}

int main(){
  //char s1[];
  //long res;
  printf("%s %lu\n", "char *",sizeof(char *));
  printf("%s %lu\n", "int *",sizeof(int *));
  printf("%s %lu\n", "long *",sizeof(long *));
  printf("%s %lu\n", "unsigned Long ",sizeof(unsigned long));
  printf("%s %lu\n", "newString ",sizeof(newString));
  printf("%s %lu\n", "newString * ",sizeof(newString *));
  printf("%s %lu\n", "listNode ",sizeof(listNode));
  printf("%s %lu\n", "listNode * ",sizeof(listNode *));
  printf("%s %lu\n", "linked_list ",sizeof(linked_list));
  printf("%s %lu\n", "linked_list * ",sizeof(linked_list *)); 
  printf("%s %lu\n", "primaryTable ",sizeof(primaryTable));
  printf("%s %lu\n", "primaryTable * ",sizeof(primaryTable *));
  printf("%s %lu\n", "secondaryTable ",sizeof(secondaryTable));
  printf("%s %lu\n", "secondaryTable *",sizeof(secondaryTable *));
  printf("%s %lu\n", "hashTable ",sizeof(hashTable));
  printf("%s %lu\n", "hashTable * ",sizeof(hashTable *));
  

  // res = getPrimaryHash(s1);
  // printf("%ld\n", res);

  // res = getSecondaryHash(s1);
  // printf("%ld\n", res);
  return 0;
}