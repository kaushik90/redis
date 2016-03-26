#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

unsigned long getPrimaryHash(char *str){
  unsigned long hash = 5381;
  int c, l = PRIMARY_HASH_LEN;

  while (*str != '\0' && l-- > 0){
    c = *str++;
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash % INITIAL_SIZE;
}

unsigned long getSecondaryHash(char *str){
  unsigned long hash = 0;
  int c, l = SECONDARY_HASH_LEN;

  while (*str != '\0' && l-- > 0){
    c = *str++;
    hash = c + (hash << 6) + (hash << 16) - hash;
  }
  return hash % INITIAL_SIZE;
}

token* tokenizeString(char *str, long len){
  token *tkn = (token*)malloc(sizeof (token)*8);
  tkn->count = 0;
  long token_size = 0, index = 0;
  char *runner = str;

  while(index < len){
    while(*runner == ' '){
      runner++;
      str++;
      index++;
    }
    token_size = 0;
    while(*runner != ' ' && *runner != '\0' && *runner != '\n' && index<len){
      runner++;
      token_size++;
      index++;
    }
    if(index==len)token_size -= 1;
    if(token_size){
      tkn->tokens[tkn->count++] = buildNewString(str, token_size);
    }
    str = runner;
    if(tkn->count > 3)break;
  }
  return tkn;
}

// int main(){
//   long i,l;
//   char *str = "set foo bar               wtf\0";
//   l=strlen(str)+1;
//   printf("%s %ld\n","wtf here len is", l );
//   token *tkn = tokenizeString(str,l);
//   for(i=0;i<tkn->count;i++){
//     printString(tkn->tokens[i]);
//   }
// }