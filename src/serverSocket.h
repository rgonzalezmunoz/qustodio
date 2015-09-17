#ifndef serverSocket_h
#define serverSocket_h

#define MSG_LEN 2000

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class serverSocket
{
public:

   enum resultType {
      OK            = 0,
      ERROR_SOCKET  = 1,
      ERROR_CONNECT = 2,
      ERROR_SEND    = 3,
      ERROR_RECEIVE = 4
   };

public:
   serverSocket(const int port = 42422, const char *address = "127.0.0.1");
   ~serverSocket();

   resultType initSocket();
   resultType sendMsg(const char *message);
   resultType receiveMsg(char *message);
   resultType finiSocket();

   static const char* getError(resultType error);

private:
   /*
   char               IP_ADDRESS_SERVER[16];
   int                PORT_SERVER;
   int                sock;
   struct sockaddr_in server;*/

   int socket_desc , client_sock , c , read_size;
   struct sockaddr_in server , client;
   char client_message[2000];
};

#endif
