#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <cstdlib>
#include <pthread.h>
#include <iosfwd>
#include <sstream>
#include <set>
using namespace std;

#include "Socket.h"


class EventTable
{
public:
	EventTable(){};

	bool insertEvent(string lEvent)
	{
		pair<set<string>::iterator,bool> ret;
		ret = myset.insert(lEvent);
		return (ret.second);
	};
	string getNumEvents()
	{
		ostringstream oss;
		oss << myset.size();
		return oss.str();
	};

private:
	set<string> myset;
};

EventTable gEventTable;

void *connectionHandler(void *);

int main(int argc , char *argv[])
{
   Socket mServerSocket, *mpServerSocket;
   Socket::resultType result;


   result = mServerSocket.initServerSocket();
   if (result != Socket::OK)
   {
      cout << Socket::getError(result) << endl;
      return -1;
   }

   while( true )
   {
      result = mServerSocket.acceptConnect();
      if (result != Socket::OK)
      {
          cout << Socket::getError(result) << endl;
          return -1;
      }

      mpServerSocket = &mServerSocket;

      pthread_t clientThread;
      if( pthread_create( &clientThread, NULL, connectionHandler, (void*)mpServerSocket) < 0)
         return -1;
   }

   return 0;
}

/*
 * This will handle connection for each client
 * */
void *connectionHandler(void *lpServerSocket)
{
   Socket lServerSocket = *(Socket*)lpServerSocket;
   Socket::resultType result;
   string msg;

   do {
      //Receive a message from client
      result = lServerSocket.receiveMsg(msg);
      if ( result == Socket::OK )
      {
         cout << "RECEIVED: " << msg << endl;

         //Insert the message
         string insertion;
         if (gEventTable.insertEvent(msg))           // Insertion successful
            insertion = "TRUE";
         else
            insertion = "FALSE";

         //Send the response
         insertion += gEventTable.getNumEvents();
         lServerSocket.sendMsg(insertion);

         cout << "SENT: " << msg << endl;
      }
      else if (result == Socket::OK_DISCONNECTED)
      {
         cout << "Client disconnected" << endl;
         fflush(stdout);
      }
      else
      {
         cout << Socket::getError(result) << endl;
         fflush(stdout);
      }
   }
   while (result == Socket::OK);

   pthread_exit(NULL);
}
