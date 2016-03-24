#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

linked_list* newLinkedList(){
  linked_list* ll = (linked_list*)malloc(sizeof(linked_list));
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

void addNodeToList(linked_list *list, listNode *temp){
  if(list->head){
    list->tail->next = temp;
    list->tail = list->tail->next;
  }else{
    list->head = temp;
    list->tail = list->head;
  }
  list->size++;
}

void printList(linked_list *list){
  listNode *tmp = list->head;
  while(tmp){
    printf("%s %s\n", tmp->key->buf, tmp->value->buf);
    tmp = tmp->next;
  }
  free(tmp);
}

listNode* findNode(newString *key, linked_list *list){
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
//  int i, n;
//  scanf("%d", &n);
//  long arr[20];
//  listNode *temp;
//  char *str1 = "Arun\0";
//  char *str2 = "Kaushik\0";

//  for(i=0;i<n;i++) scanf("%ld", &arr[i]);

//  linked_list* list = newLinkedList();
  
//  for(i = 0; i<n; i++){
//    temp = newNode(str1, str2, arr[i]);
//    addlistNodeToList(list, temp);
//  }
//  printList(list);
//  free(temp);
//  return 0;
// }