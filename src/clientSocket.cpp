#include "clientSocket.h"

clientSocket::clientSocket(const int port, const char *address)
{
   sock        = -1;
   PORT_SERVER = port;
   strncpy(IP_ADDRESS_SERVER, address, strlen(address));
}

clientSocket::~clientSocket()
{
   if (sock > 0)
      close(sock);
}

clientSocket::resultType clientSocket::initSocket()
{
   //Create socket
   sock = socket(AF_INET , SOCK_STREAM , 0);
   if (sock == -1)
      return ERROR_SOCKET;

   //Initiate address structure
   server.sin_addr.s_addr = inet_addr( IP_ADDRESS_SERVER );
   server.sin_family = AF_INET;
   server.sin_port = htons( PORT_SERVER );

   //Connect to remote server
   if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
      return ERROR_CONNECT;

   return OK;
}

clientSocket::resultType clientSocket::sendMsg(const char *message)
{
   if( send(sock, message, MSG_LEN, 0) < 0)
       return ERROR_SEND;
   return OK;
}

clientSocket::resultType clientSocket::receiveMsg(char *message)
{
   int sizeResp;

   sizeResp = recv(sock, message, MSG_LEN, 0);
   if( sizeResp < 0 )
      return ERROR_RECEIVE;
   else
      message[sizeResp] = '\0';

   return OK;
}

clientSocket::resultType clientSocket::finiSocket()
{
   close(sock);
   return OK;
}

const char* clientSocket::getError(resultType error)
{
   switch (error)
   {
   case ERROR_SOCKET:  return "Could not create socket";
   case ERROR_CONNECT: return "Connect failed";
   case ERROR_SEND:    return "Send failed";
   case ERROR_RECEIVE: return "Receive failed";
   case OK:
   default: return "No error";
   }
   return "No error";
}
