#include "Socket.h"

Socket::Socket()
{
   server_sock = -1;
   client_sock = -1;
   PORT_SERVER = -1;
   IP_ADDRESS_SERVER = "";
}

Socket::~Socket()
{
}

Socket::resultType Socket::initServerSocket(const int port)
{
   PORT_SERVER = port;

   //Create socket
   server_sock = socket(AF_INET , SOCK_STREAM , 0);
   if (server_sock == -1)
      return ERROR_SOCKET;

   //Initiate address structure
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons( PORT_SERVER );

   //Bind
   if( bind(server_sock,(struct sockaddr *)&server , sizeof(server)) < 0)
      return ERROR_BIND;

   //Listen
   if( listen(server_sock, 3) < 0)
      return ERROR_LISTEN;

   return OK;
}

Socket::resultType Socket::initClientSocket(const int port, const string &address)
{
   PORT_SERVER = port;
   IP_ADDRESS_SERVER = address;

   //Create socket
   client_sock = socket(AF_INET, SOCK_STREAM, 0);
   if (client_sock == -1)
      return ERROR_SOCKET;

   //Initiate address structure
   server.sin_addr.s_addr = inet_addr( IP_ADDRESS_SERVER.c_str() );
   server.sin_family = AF_INET;
   server.sin_port = htons( PORT_SERVER );

   //Connect to remote server
   if (connect(client_sock , (struct sockaddr *)&server , sizeof(server)) < 0)
      return ERROR_CONNECT;

   return OK;
}

Socket::resultType Socket::acceptConnect()
{
   int c = sizeof(struct sockaddr_in);

   client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c);
   if(client_sock < 0)
      return ERROR_ACCEPT;
   return OK;
}

Socket::resultType Socket::sendMsg(const string &message)
{
   if( send(client_sock, message.c_str(), message.size(), 0) < 0)
       return ERROR_SEND;
   return OK;
}

Socket::resultType Socket::receiveMsg(string &message)
{
   int sizeResp;
   char aux[RCV_MSG_LEN];

   sizeResp = recv(client_sock, aux, RCV_MSG_LEN, 0);
   if( sizeResp < 0 )
      return ERROR_RECEIVE;
   else if ( sizeResp == 0 )
      return OK_DISCONNECTED;
   else
      message = string(aux, sizeResp);

   return OK;
}

Socket::resultType Socket::finiSocket()
{
   if (server_sock != -1)
      close(server_sock);
   if (client_sock != -1)
      close(client_sock);

   return OK;
}

const char* Socket::getError(resultType error)
{
   switch (error)
   {
   case ERROR_SOCKET:  return "Could not create socket";
   case ERROR_CONNECT: return "Connect failed";
   case ERROR_SEND:    return "Send failed";
   case ERROR_RECEIVE: return "Receive failed";
   case ERROR_BIND:    return "Bind failed";
   case ERROR_LISTEN:  return "Listen failed";
   case ERROR_ACCEPT:  return "Accept failed";
   case OK:
   case OK_DISCONNECTED:
   default: return "No error";
   }
   return "No error";
}
