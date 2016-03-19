#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "tcpsocket/soket.h"

int shutdownServer();
void actionBeforeExit();
void sig_handler(int);

int ConnectFD;
int SocketFD;

int main(void)
{
  int resultSize;
  int buffSize = 1000;
  char buff[buffSize];
  int port = 1505;

  signal(SIGINT, sig_handler);

  ConnectFD = createSocket(port);
  if (ConnectFD == -1) {
    perror("Socket Creation Failed");
    return (EXIT_FAILURE);
  }
  
  while(1){
    memset(buff, '\0', buffSize);

    if(read(ConnectFD, buff, buffSize) < 0){
      perror("reading failed");
    }else{
      resultSize = strlen(buff);
      if(write(ConnectFD,buff,resultSize) < 0 ){
        perror("ERROR writing to socket");
      }
    }
  }

  return EXIT_SUCCESS;  
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