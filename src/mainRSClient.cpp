#include <iostream>
using namespace std;

#include <stdio.h>
#include <string.h>

#include "Socket.h"

bool checkArgs(int argc, char *argv[])
{
   if (argc < 2)
   {
      cout << "Invalid arguments:" << endl;
      cout << "Correct: ./" << argv[0] << " log1 log2 ... logN" << endl;

      return false;
   }
   return true;
}

int main(int argc , char *argv[])
{
   if (!checkArgs(argc, argv))
   {
      return -1;
   }

   char msg[2000];
   Socket mClientSocket;
   Socket::resultType result;

   result = mClientSocket.initClientSocket();
   if (result != Socket::OK)
   {
      cout << Socket::getError(result) << endl;
      return -1;
   }

   cout << "Enter message : ";
   cin.getline(msg, 1000);

   //Sends the written message
   result = mClientSocket.sendMsg(msg);
   if (result != Socket::OK)
   {
      cout << Socket::getError(result) << endl;
         return -1;
   }

   //Waits until message response reception
   result = mClientSocket.receiveMsg(msg);
   if (result != Socket::OK)
   {
      cout << Socket::getError(result) << endl;
      return -1;
   }

   cout << "Server reply : " << msg << endl;

   mClientSocket.finiSocket();
   return 0;
}
