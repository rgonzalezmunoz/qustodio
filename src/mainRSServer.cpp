#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sstream>
#include <iostream>

using namespace std;

/*
 * Includes
 */
#include "Socket.h"
#include "EventTable.h"

/*
 * Globals
 */
EventTable gEventTable;

/*
 * Thread handlers
 */
void *connectionHandler(void *lpServerSocket);
void *eventsMonitor(void *lpTime);


int main(int argc , char *argv[])
{
   pthread_t mMonitorThread, mClientThread;
   Socket *mpServerSocket = new Socket();
   Socket::resultType mResult;
   int *mpSleepTime = new int(5);

   mResult = mpServerSocket->initServerSocket();
   if (mResult != Socket::OK)
   {
      cout << Socket::getError(mResult) << endl;
      return -1;
   }

   //Start events monitor thread
   if( pthread_create( &mMonitorThread, NULL, eventsMonitor, (void *)mpSleepTime) < 0)
      return -1;

   while( true )
   {
      mResult = mpServerSocket->acceptConnect();
      if (mResult != Socket::OK)
      {
          cout << Socket::getError(mResult) << endl;
          return -1;
      }

      //Start connection handler thread for an incoming connection
      if( pthread_create( &mClientThread, NULL, connectionHandler, (void*)mpServerSocket) < 0)
      {
         return -1;
      }
   }
   return 0;
}


/*
 * Thread task that reports last received events
 */
void *eventsMonitor(void *lpTime)
{
   vector<string> lLastEvents;
   int *lTime = (int *)lpTime;

   while (true)
   {
      sleep(*lTime);

      lLastEvents = gEventTable.getLastEvents();
      cout << "--- Last Events Received: ---------" << endl;
      if (lLastEvents.size() != 0)
         for ( vector<string>::iterator it=lLastEvents.begin(); it!=lLastEvents.end(); ++it)
            cout << *it;
      else
         cout << "--- None during the last period ---" << endl;
      cout << "-----------------------------------" << endl;

      lLastEvents.clear();
   }

   pthread_exit(NULL);
}

/*
 * Thread task that handles a client connection
 */
void *connectionHandler(void *lpServerSocket)
{
   Socket lServerSocket = *(Socket*)lpServerSocket;
   Socket::resultType lResult;
   string lMsgRecv;
   unsigned long int lCount;
   bool bInsertResult;

   do {
      //Receive a message from client
      lResult = lServerSocket.receiveMsg(lMsgRecv);
      if ( lResult == Socket::OK )
      {
         //Insert the event and get insertion result
         bInsertResult = gEventTable.insertEvent(lMsgRecv, lCount);
         stringstream lMsgResp;
         lMsgResp << (bInsertResult ? "TRUE|" : "FALSE|") << lCount;

         //Send the response
         lServerSocket.sendMsg(lMsgResp.str());
      }
   }
   while (lResult == Socket::OK);

   if ((lResult != Socket::OK) && (lResult != Socket::OK_DISCONNECTED))
      cout << Socket::getError(lResult) << endl;

   pthread_exit(NULL);
}
