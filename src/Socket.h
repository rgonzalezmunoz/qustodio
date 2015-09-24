#ifndef Socket_h
#define Socket_h

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

   Socket::resultType initServerSocket(const int lPort = 42422);
   Socket::resultType initClientSocket(const int lPort = 42422, const string &lAddress = "127.0.0.1");
   Socket::resultType acceptConnect();
   Socket::resultType sendMsg(const string &lMsg);
   Socket::resultType receiveMsg(string &lMsg);
   Socket::resultType closeSocket();

   static const char* getError(Socket::resultType lError);

private:

   string             mIPAddressServer;
   int                mPortServer;
   int                mServerSock, mClientSock;
   struct sockaddr_in mServerAddr, mClientAddr;
};

#endif
