#include "serverSocket.h"

serverSocket::serverSocket(const int port = 42422, const char *address = "127.0.0.1");
   serverSocket::~serverSocket();

   resultType serverSocket::initSocket();
   resultType serverSocket::sendMsg(const char *message);
   resultType serverSocket::receiveMsg(char *message);
   resultType serverSocket::finiSocket();

   static const char* serverSocket::getError(resultType error);
