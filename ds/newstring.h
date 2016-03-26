#ifndef NEWSTRING_H_   /* Include guard */
#define NEWSTRING_H_

typedef struct newString
{
  long len;
  char buf[];
}newString;

newString* buildNewString(void *, long);
void printString(newString*);

#endif