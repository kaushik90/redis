#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "tcpsocket/soket.h"
#include "ds/utils.h"
#include "ds/hashmap.h"
#include "ds/rediscommand.h"

int shutdownServer();
void actionBeforeExit();
void sig_handler(int);

int ConnectFD;
int SocketFD;
newString* executeCommand(redisCommand*, token*, hashTable*);

int main(void)
{
  char new_line = '\n';
  long bytesread;
  newString *result;
  token *tkn;
  redisCommand* cmd;
  int buffSize = 1000,i;
  char buf[buffSize];
  int port = 1500;

  signal(SIGINT, sig_handler);

  ConnectFD = createSocket(port);
  if (ConnectFD == -1) {
    perror("Socket Creation Failed");
    return (EXIT_FAILURE);
  }
  hashTable* ht_command = initializeCommandTable();
  hashTable* hash_map = newHashMap();
  while(1){
    bytesread = read(ConnectFD, buf, buffSize);
    if( bytesread < 3){
      perror("ILLEGAL .... HAVE TO HANDLE");
    }else{

      tkn = tokenizeString(buf,bytesread-1);

      cmd = getCommand(ht_command, tkn->tokens[0]);

      if(cmd && tkn->count && cmd->args_count == tkn->count - 1){
        switch(cmd->ds_type){
          case DS_HASH_MAP:
            result = executeCommand(cmd, tkn, hash_map);
            break;
          default:
          // -ERR unknown command 'fet'
          // -ERR wrong number of arguments for 'get' command
            result = buildNewString("Coming soon...",14);
        }
      }else{
        result = buildNewString("ERROR: Command not supported",28);
      }

      result->buf[result->len] = '\n';
      if(write(ConnectFD,result->buf,result->len+1) < 0 ){
        perror("ERROR writing to socket");
      }
    }
  }

  return EXIT_SUCCESS;  
}

newString* executeCommand(redisCommand* cmd, token* tkn, hashTable* hash_map){
  cmdResult *res;
  switch (cmd->args_count){
    case 1:
      res = cmd->f_ptr(hash_map, tkn->tokens[1]);
    case 2:
      res = cmd->f_ptr(hash_map, tkn->tokens[1], tkn->tokens[2]);
  }

  if(res){
    return res->res_str;
  }else{
    return buildNewString("X",1);
  }
}

void sig_handler(int signo) {
  if (signo == SIGINT){
    printf("received SIGINT\n");
    if(-1 == shutdownServer()){
      perror("Cannot shutdown server properly.");
    }else{
      actionBeforeExit();
      printf("%s\n", "Server shutdown successfully.");
    }
  }
  exit(0);
}

int  shutdownServer(){
  printf(" %s\n","Shutting Down server...");
  return shutdownSocketConnection(ConnectFD, SocketFD);
}

void actionBeforeExit(){
  printf("%s\n","I will do some work before exit.");
  return;
}