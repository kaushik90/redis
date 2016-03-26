#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rediscommand.h"

struct redisCommand redisCommandTable[] = {
  {"get", getHashMap, 1, DS_HASH_MAP, NULL},
  {"set", setHashMap, 2, DS_HASH_MAP, NULL},
};

redisCommandList* newCommandList(){
  redisCommandList* cl = (redisCommandList*)malloc(sizeof(redisCommandList));
  cl->head = NULL;
  cl->tail = NULL;
  return cl;
}

hashTable* newCommandTable(){
  int i,j;
  hashTable* ht = newHashTable();
  for(i=0;i<CMD_TABLE_SIZE;i++){
    for(j=0;j<CMD_TABLE_SIZE;j++){
      ht->table->rooms[i]->list[j] = newCommandList();
    }
  }
  return ht;
}

void addCommandToList(redisCommandList *list, redisCommand *cmd){
  if(list->head){
    list->tail->next = cmd;
    list->tail = list->tail->next;
  }else{
    list->head = cmd;
    list->tail = list->head;
  }
}

redisCommand* findCommandNode(redisCommandList* cmd_list, newString *key){
  redisCommand* tmp = cmd_list->head;
    int len = key->len;
    int result;
    while(tmp){
      result = memcmp(tmp->cmd, key->buf, len);
      if(!result) return tmp;
      tmp = tmp->next;
    }
  return tmp;
}

void setCommand(hashTable* ht, redisCommand *c){
  redisCommandList* cmd_list;
  unsigned long p_hash = getPrimaryHash(c->cmd);
  unsigned long s_hash = getSecondaryHash(c->cmd);
  cmd_list = ht->table->rooms[p_hash]->list[s_hash];
  addCommandToList(cmd_list, c);
  ht->key_count++;
}

redisCommand* getCommand(hashTable* ht, newString *key){
  unsigned long p_hash = getPrimaryHash(key->buf) % INITIAL_SIZE;
  unsigned long s_hash = getSecondaryHash(key->buf) % INITIAL_SIZE;
  redisCommandList* cmd_list = ht->table->rooms[p_hash]->list[s_hash];
  redisCommand* tmp=NULL;
  if(cmd_list->head){
    tmp = findCommandNode(cmd_list, key);
  }
  return tmp;
}

hashTable* initializeCommandTable(){
  hashTable* ht = newCommandTable();
  int i,numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
  for (i = 0; i < numcommands; i++) {
    redisCommand *c = redisCommandTable+i;
    setCommand(ht, c);
  }
  return ht;
}

// int main(){

//   redisCommand *tmp;
//   hashTable* ht = initializeCommandTable();

//   newString *str1 = buildNewString("set", 3);
//   newString *str2 = buildNewString("get", 3);
//   newString *str3 = buildNewString("foo", 3);


//   tmp = getCommand(ht, str1);
//   if(tmp){
//     printf("%s %s %ld\n","GOT COMMAND NODE", tmp->cmd, tmp->args_count);
//     printf("%s\n","-----------------" );
//   }else{
//     printf("%s\n", "NAHI MILA BHAI");
//   }

//   tmp = getCommand(ht, str2);
//   if(tmp){
//     printf("%s %s %ld\n","GOT COMMAND NODE", tmp->cmd, tmp->args_count);
//     printf("%s\n","-----------------" );
//   }else{
//     printf("%s\n", "NAHI MILA BHAI");
//   }

//   tmp = getCommand(ht, str3);
//   if(tmp){
//     printf("%s %s %ld\n","GOT COMMAND NODE", tmp->cmd, tmp->args_count);
//     printf("%s\n","-----------------" );
//   }else{
//     printf("%s\n", "NAHI MILA BHAI");
//   }

// }