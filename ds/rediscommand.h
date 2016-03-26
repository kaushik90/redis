#ifndef REDISCOMMAND_H_   /* Include guard */
#define REDISCOMMAND_H_
#include "hashmap.h"

typedef struct redisCommand
{
  char *cmd;
  struct cmdResult *(*f_ptr)();
  size_t args_count;
  size_t ds_type;
  struct redisCommand *next;
}redisCommand;

typedef struct redisCommandList
{
  struct redisCommand *head;
  struct redisCommand *tail;
}redisCommandList;


hashTable* initializeCommandTable();
redisCommand* getCommand(hashTable*, newString *);
void setCommand(hashTable*, redisCommand *);

#endif