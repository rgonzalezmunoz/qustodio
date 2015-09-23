#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <cstdlib>
#include <pthread.h>
#include <iostream>
using namespace std;

#include "Socket.h"

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

   //Receive a message from client
   result = lServerSocket.receiveMsg(msg);
   if ( result == Socket::OK )
   {
      cout << "QUE: " << msg << endl;

      //Send the message back to client
      lServerSocket.sendMsg(msg);
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

   pthread_exit(NULL);
}
