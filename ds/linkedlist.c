#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

linkedList* newLinkedList(){
  linkedList* ll = (linkedList*)malloc(sizeof(linkedList));
  ll->head = NULL;
  ll->tail = NULL;
  ll->size = 0;
  return ll;
}

listNode* newNode(newString *key,newString *value){
  listNode* tmp = (listNode*)malloc(sizeof( listNode));
  tmp->key = key;
  tmp->value = value;
  tmp->next = NULL;
  return tmp;
}

void addNodeToList(linkedList *list, listNode *temp){
  if(list->head){
    list->tail->next = temp;
    list->tail = list->tail->next;
  }else{
    list->head = temp;
    list->tail = list->head;
  }
  list->size++;
}

void printList(linkedList *list){
  listNode *tmp = list->head;
  printf("%s %d\n","Size: ", list->size);
  while(tmp){
    printf("%s %s\n", tmp->key->buf, tmp->value->buf);
    tmp = tmp->next;
  }
  free(tmp);
}

listNode* findNode(newString *key, linkedList *list){
  listNode* tmp = list->head;
  int len = key->len;
  int result;
  while(tmp){
    result = memcmp(tmp->key->buf, key->buf, len);
    if(!result) return tmp;
    tmp = tmp->next;
  }
  return tmp;
}

void replaceValue(listNode *node, newString *newvalue){
  newString *tmp;
  if(!node) return;
  else{
    tmp = node->value;
    node->value = newvalue;
    free(tmp);
  }
}

// int main(){
//  int i, n,l;
//  newString *k;
//  newString *v;
//  scanf("%d", &n);
//  listNode *temp;
//  char key[100]; 
//  char value[100]; 

//  linkedList* list = newLinkedList();
  
//  for(i = 0; i<n; i++){
//     scanf("%s", key);
//     scanf("%s", value);
//     l = strlen(key);
//     k = buildNewString(key, l);
//     l = strlen(value);
//     v = buildNewString(value,l);
//     temp = newNode(k, v);
//     addNodeToList(list, temp);
//  }
//  printList(list);
//  free(temp);
//  return 0;
// }