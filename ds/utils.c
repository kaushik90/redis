#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

unsigned long getPrimaryHash(char *str){
  unsigned long hash = 5381;
  int c;
  while (*str != '\0'){
    c = *str++;
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash % INITIAL_SIZE;
}

unsigned long getSecondaryHash(char *str){
  unsigned long hash = 0;
  int c;
  while (*str != '\0'){
    c = *str++;
    hash = c + (hash << 6) + (hash << 16) - hash;
  }
  return hash % INITIAL_SIZE;
}
