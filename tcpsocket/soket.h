#ifndef SOKET_H_   /* Include guard */
#define SOKET_H_

int createSocket(int port); // Returns socket connection on given port
void makeSocketKeepAlive(int socket);
int shutdownSocketConnection(int ConnectFD, int SocketFD);

#endif // SOKET_H_