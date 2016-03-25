#ifndef LINKEDLIST_H_   /* Include guard */
#define LINKEDLIST_H_

#include "newstring.h"

typedef struct listNode{
  newString *key;
  newString *value;
  struct listNode *next;
}listNode;

typedef struct linkedList{
  struct listNode *head;
  struct listNode *tail;
  int size;
}linkedList;

linkedList* newLinkedList();
listNode* newNode(newString *, newString *);
void addNodeToList(linkedList *, listNode *);
void printList(linkedList *);
listNode* findNode(newString *key, linkedList *list);
void replaceValue(listNode *tmp, newString *value);

#endif