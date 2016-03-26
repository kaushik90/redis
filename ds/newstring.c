#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "newstring.h"

newString* buildNewString(void *source, long len){
  newString *str = (newString*)malloc(sizeof (newString)+ len + 1);
  str->len = len;
  if (len) {
    if (source) memcpy(str->buf, source, len);
    else memset(str->buf,0,len);
  }
  str->buf[len] = '\0';
  return str;
}

void printString(newString* str){
  if(!str) return;
  else{
    printf("%s\n", str->buf );
    printf("%s %ld\n","Size: ", str->len);
  }
}

// int main(){
//   int i,n,l;
//   char s[100];
//   newString *str;
//   scanf("%d", &n);
//   for(i=0;i<n;i++){
//     scanf("%s", s);
//     l = strlen(s);
//     str = buildNewString(s,l);
//     printString(str);
//     free(str);
//   }
// }