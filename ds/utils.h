#ifndef UTILS_H_   /* Include guard */
#define UTILS_H_
#include "constants.h"
#include "newstring.h"
#include "linkedlist.h"
#include "hashtable.h"

typedef struct cmdResult
{
  newString *res_str;
  long res_int;
  int status;
}cmdResult;

typedef struct token
{ 
  unsigned long count;
  newString* tokens[];
}token;

unsigned long getPrimaryHash(char *);
unsigned long getSecondaryHash(char *);
token* tokenizeString(char *, long);

#endif