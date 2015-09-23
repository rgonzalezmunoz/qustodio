#include <iostream>
using namespace std;

#include <stdio.h>
#include <string.h>

#include "Socket.h"
#include "LogScanner.h"

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
   string msg;
   Socket mClientSocket;
   Socket::resultType result;
   LogScanner mLogScanner;
   string mQuestionableList;

   if (!checkArgs(argc, argv))
   {
      return -1;
   }

   mLogScanner.setLogFileName(argv[1]);
   if (mLogScanner.findQuestionableActivities() >= 0)
      mQuestionableList = mLogScanner.getQuestionableActivityList();


   result = mClientSocket.initClientSocket();
   if (result != Socket::OK)
   {
      cout << Socket::getError(result) << endl;
      return -1;
   }

   cout << "Enter message : ";
   //cin.getline(msg, 1000);


   //Sends the written message
   result = mClientSocket.sendMsg(mQuestionableList);
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
