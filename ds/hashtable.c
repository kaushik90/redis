#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "constants.h"

int starting_size = INITIAL_SIZE;

secondaryTable* newSecondaryTable(){
	int i;
	secondaryTable* st = (secondaryTable*)malloc(sizeof(secondaryTable) + INITIAL_SIZE * sizeof(linked_list *));
	for(i=0;i<starting_size;i++) st->list[i] = newLinkedList();
	st->size = starting_size;
	return st;
}

primaryTable* newPrimaryTable(){
	int i;
	primaryTable* pt = (primaryTable*)malloc(sizeof(primaryTable) + INITIAL_SIZE * sizeof(secondaryTable *));
	for(i=0;i<starting_size;i++) pt->rooms[i]=newSecondaryTable();
	pt->size = starting_size;
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

unsigned long getPrimaryHash(char *str){
	unsigned long hash = 5381;
	int c;
	while (*str != '\0'){
		c = *str++;
	  hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}

unsigned long getSecondaryHash(char *str){
	unsigned long hash = 0;
	int c;
	while (*str != '\0'){
		c = *str++;
	  hash = c + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

void set(newString *key, newString *value, hashTable* ht){
	linked_list* ll;
	listNode *tmp=NULL;
	unsigned long p_hash = getPrimaryHash(key->buf) % starting_size;
	unsigned long s_hash = getSecondaryHash(key->buf) % starting_size;
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
	unsigned long p_hash = getPrimaryHash(key->buf) % starting_size;
	unsigned long s_hash = getSecondaryHash(key->buf) % starting_size;
	linked_list* ll = ht->table->rooms[p_hash]->list[s_hash];
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
	linked_list* ll;
	printf("%s %ld\n", "No of keys: ",ht->key_count );
	for(i = 0; i<starting_size; i++){
		for(j = 0; j<starting_size; j++){
			ll = ht->table->rooms[i]->list[j];
			printf("%d %d %s\n", i, j, "----------------------- START ----------------------------" );
			printList(ll);
			printf("%d %d %s\n", i, j, "----------------------- END ------------------------------" );
		}
	}
}

// int main(){
// 	int i,l;
// 	newString *k;
// 	newString *v;
// 	hashTable* ht = (hashTable*)malloc(sizeof(hashTable));
// 	ht = newHashTable();
// 	int n;
// 	scanf("%d", &n);
// 	char key[100];
// 	char value[100];
// 	char *res;
// 	for(i=0;i<n;i++){
// 		scanf("%s", key);
// 		scanf("%s", value);
// 		l = strlen(key);
// 		k = buildNewString(key, l);
// 		l = strlen(value);
// 		v = buildNewString(value,l);
// 		printf("%s %s %s\n","saving...", k->buf, v->buf);
// 		set(k, v, ht);
// 	}

// 	printHashTable(ht);

// 	for(i=0;i<n;i++){
// 		scanf("%s", key);
// 		l = strlen(key);
// 		k = buildNewString(key, l);
// 		res = get(k, ht);
// 		if(res){
// 			printf("%s\n", res);
// 		}else{

// 		}
// 	}

// }