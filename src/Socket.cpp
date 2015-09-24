#include "Socket.h"

Socket::Socket()
{
   mServerSock = -1;
   mClientSock = -1;
   mPortServer = -1;
   mIPAddressServer = "";
}

Socket::~Socket()
{
}

Socket::resultType Socket::initServerSocket(const int lPort)
{
   mPortServer = lPort;

   //Create socket
   mServerSock = socket(AF_INET , SOCK_STREAM , 0);
   if (mServerSock == -1)
      return ERROR_SOCKET;

   //Initiate address structure
   mServerAddr.sin_family = AF_INET;
   mServerAddr.sin_addr.s_addr = INADDR_ANY;
   mServerAddr.sin_port = htons( mPortServer );

   //Bind
   if( bind(mServerSock,(struct sockaddr *)&mServerAddr , sizeof(mServerAddr)) < 0)
      return ERROR_BIND;

   //Listen
   if( listen(mServerSock, 3) < 0)
      return ERROR_LISTEN;

   return OK;
}

Socket::resultType Socket::initClientSocket(const int lPort, const string &lAddress)
{
   mPortServer = lPort;
   mIPAddressServer = lAddress;

   //Create socket
   mClientSock = socket(AF_INET, SOCK_STREAM, 0);
   if (mClientSock == -1)
      return ERROR_SOCKET;

   //Initiate address structure
   mClientAddr.sin_addr.s_addr = inet_addr( mIPAddressServer.c_str() );
   mClientAddr.sin_family = AF_INET;
   mClientAddr.sin_port = htons( mPortServer );

   //Connect to remote server
   if (connect(mClientSock , (struct sockaddr *)&mClientAddr , sizeof(mClientAddr)) < 0)
      return ERROR_CONNECT;

   return OK;
}

Socket::resultType Socket::acceptConnect()
{
   int c = sizeof(struct sockaddr_in);

   mClientSock = accept(mServerSock, (struct sockaddr *)&mClientAddr, (socklen_t*)&c);
   if(mClientSock < 0)
      return ERROR_ACCEPT;
   return OK;
}

Socket::resultType Socket::sendMsg(const string &lMsg)
{
   if( send(mClientSock, lMsg.c_str(), lMsg.size(), 0) < 0)
       return ERROR_SEND;
   return OK;
}

Socket::resultType Socket::receiveMsg(string &lMsg)
{
   int sizeResp;
   char aux[RCV_MSG_LEN];

   sizeResp = recv(mClientSock, aux, RCV_MSG_LEN, 0);
   if( sizeResp < 0 )
      return ERROR_RECEIVE;
   else if ( sizeResp == 0 )
      return OK_DISCONNECTED;
   else
      lMsg = string(aux, sizeResp);

   return OK;
}

Socket::resultType Socket::closeSocket()
{
   if (mServerSock != -1)
      close(mServerSock);
   if (mClientSock != -1)
      close(mClientSock);

   return OK;
}

const char* Socket::getError(resultType lError)
{
   switch (lError)
   {
   case ERROR_SOCKET:    return "Could not create socket";
   case ERROR_CONNECT:   return "Connect failed";
   case ERROR_SEND:      return "Send failed";
   case ERROR_RECEIVE:   return "Receive failed";
   case ERROR_BIND:      return "Bind failed";
   case ERROR_LISTEN:    return "Listen failed";
   case ERROR_ACCEPT:    return "Accept failed";
   case OK_DISCONNECTED: return "Client disconnected";
   case OK:
   default: return "No error";
   }
   return "No error";
}
