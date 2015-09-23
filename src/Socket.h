#ifndef Socket_h
#define Socket_h

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
using namespace std;

class Socket
{
public:

   enum resultType {
      OK              = 0,
      OK_DISCONNECTED = 1,
      ERROR_SOCKET    = 2,
      ERROR_CONNECT   = 3,
      ERROR_SEND      = 4,
      ERROR_RECEIVE   = 5,
      ERROR_BIND      = 6,
      ERROR_LISTEN    = 7,
      ERROR_ACCEPT    = 8
   };

private:

   static const unsigned int RCV_MSG_LEN = 5000;

public:

   Socket();
   ~Socket();

   Socket::resultType initServerSocket(const int port = 42422);
   Socket::resultType initClientSocket(const int port = 42422, const string &address = "127.0.0.1");
   Socket::resultType acceptConnect();
   Socket::resultType sendMsg(const string &message);
   Socket::resultType receiveMsg(string &message);
   Socket::resultType finiSocket();

   static const char* getError(Socket::resultType error);

private:

   string             IP_ADDRESS_SERVER;
   int                PORT_SERVER;
   int                server_sock, client_sock;
   struct sockaddr_in server, client;
};

#endif
