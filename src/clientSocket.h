#ifndef clientSocket_h
#define clientSocket_h

#define MSG_LEN 2000

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class clientSocket
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
   clientSocket(const int port = 42422, const char *address = "127.0.0.1");
   ~clientSocket();

   resultType initSocket();
   resultType sendMsg(const char *message);
   resultType receiveMsg(char *message);
   resultType finiSocket();

   static const char* getError(resultType error);

private:
   char               IP_ADDRESS_SERVER[16];
   int                PORT_SERVER;
   int                sock;
   struct sockaddr_in server;
};

#endif
