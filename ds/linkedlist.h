#ifndef LINKEDLIST_H_   /* Include guard */
#define LINKEDLIST_H_

#include "newstring.h"

typedef struct listNode{
  newString *key;
  newString *value;
  struct listNode *next;
}listNode;

typedef struct linked_list{
  struct listNode *head;
  struct listNode *tail;
  int size;
}linked_list;

linked_list* newLinkedList();
listNode* newNode(newString *, newString *);
void addNodeToList(linked_list *, listNode *);
void printList(linked_list *);
listNode* findNode(newString *key, linked_list *list);
void replaceValue(listNode *tmp, newString *value);

#endif