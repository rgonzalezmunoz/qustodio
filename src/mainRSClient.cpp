#include <iostream>
using namespace std;

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "clientSocket.h"


int main(int argc , char *argv[])
{
   char msgSend[2000], msgRecieve[2000];
   clientSocket mClientSocket;
   clientSocket::resultType result;

   result = mClientSocket.initSocket();
   if (result != clientSocket::OK)
   {
      cout << clientSocket::getError(result) << endl;
      return -1;
   }

   //Keep communicating with server
   while(true)
   {
      cout << "Enter message : ";
      cin.getline(msgSend, 1000);

      //Sends the written message
      result = mClientSocket.sendMsg(msgSend);
      if (result != clientSocket::OK)
      {
           cout << clientSocket::getError(result) << endl;
           return -1;
      }

      //Waits until message response reception
      result = mClientSocket.receiveMsg(msgRecieve);
      if (result != clientSocket::OK)
      {
         cout << clientSocket::getError(result) << endl;
         return -1;
      }

      cout << "Server reply : " << msgRecieve << endl;
   }

   mClientSocket.finiSocket();
   return 0;
}
