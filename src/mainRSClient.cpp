#include <iostream>
using namespace std;

#include <stdio.h>
#include <string.h>

/*
 * Includes
 */
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
   Socket mClientSocket;
   Socket::resultType mResult;
   LogScanner mLogScanner;
   LogScanner::activityList mActivityList;
   string mMsgRecv;
   int mNumQActv = 0;                        //Number of questionable activities

   if (!checkArgs(argc, argv))
      return -1;

   mResult = mClientSocket.initClientSocket();
   if (mResult != Socket::OK)
   {
      cout << Socket::getError(mResult) << endl;
      return -1;
   }

   //Search questionable activities in all log files passed as arguments
   for (int ii = 1; ii < argc; ii++)
   {
      mLogScanner.setLogFileName(argv[ii]);
      mNumQActv = mLogScanner.findQuestionableActivities(mActivityList);

      if (mNumQActv > 0)
      {
         cout << "--- Sending questionable activities in " << argv[ii] << endl;

         for ( LogScanner::activityList::iterator it=mActivityList.begin();
               it!=mActivityList.end(); ++it)
         {
            //Sends the activity or event
            mResult = mClientSocket.sendMsg(it->getActivityString());
            if (mResult != Socket::OK)
            {
               cout << Socket::getError(mResult) << endl;
               return -1;
            }
            //TODO: REMOVE. Delay to easily test multiple clients
            sleep(1);

            //Waits until activity confirmation
            mResult = mClientSocket.receiveMsg(mMsgRecv);
            if (mResult != Socket::OK)
            {
               cout << Socket::getError(mResult) << endl;
               return -1;
            }
            cout << "Confirmation received: " << mMsgRecv << endl;
         }

         mActivityList.clear();
      }
      else if (mNumQActv == 0)
      {
         cout << "--- No questionable activities found in " << argv[ii] << endl;
      }
      else
      {
         cout << "--- Error searching for questionable activities in " << argv[ii] << endl;
      }
   }

   mClientSocket.closeSocket();
   return 0;
}
