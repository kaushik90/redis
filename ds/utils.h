#ifndef UTILS_H_   /* Include guard */
#define UTILS_H_
#include "constants.h"
#include "linkedlist.h"
#include "hashtable.h"

unsigned long getPrimaryHash(char *);
unsigned long getSecondaryHash(char *);

#endif