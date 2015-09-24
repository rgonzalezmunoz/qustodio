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
   LogScanner::activityList mActivityList;

   if (!checkArgs(argc, argv))
   {
      return -1;
   }

   mLogScanner.setLogFileName(argv[1]);
   int numQuestionableActivities = mLogScanner.findQuestionableActivities(mActivityList);
   if (numQuestionableActivities == 0)
   {
      cout << "No questionable activities found" << endl;
      return 0;
   }
   else if (numQuestionableActivities < 0)
   {
      cout << "Error searching for questionable activities" << endl;
      return -1;
   }

   result = mClientSocket.initClientSocket();
   if (result != Socket::OK)
   {
      cout << Socket::getError(result) << endl;
      return -1;
   }

   for ( LogScanner::activityList::iterator it=mActivityList.begin(); it!=mActivityList.end(); ++it)
   {
      //Sends the activity or event
      result = mClientSocket.sendMsg(it->getActivityString());
      if (result != Socket::OK)
      {
         cout << Socket::getError(result) << endl;
         return -1;
      }
      cout << "SENT: " << it->getActivityString() << endl;

      //Waits until activity confirmation
      result = mClientSocket.receiveMsg(msg);
      if (result != Socket::OK)
      {
         cout << Socket::getError(result) << endl;
         return -1;
      }
      cout << "RECV: " << msg << endl;

   }

   mClientSocket.finiSocket();
   return 0;
}
