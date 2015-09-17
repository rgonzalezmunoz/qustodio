//============================================================================
// Name        : mainRSServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#define PORT_SERVER 42422

#include <iostream>
using namespace std;

#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write


int main(int argc , char *argv[])
{
   int socket_desc , client_sock , c , read_size;
   struct sockaddr_in server , client;
   char client_message[2000];

   //Create socket
   socket_desc = socket(AF_INET , SOCK_STREAM , 0);
   if (socket_desc == -1)
   {
      cout << "ERROR: could not create socket" << endl;
      return -1;
   }

   //Prepare sockaddr_in
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons( PORT_SERVER );

   //Bind
   if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
   {
       cout << "ERROR: bind failed" << endl;
       return -1;
   }

   //Listen
   if( listen(socket_desc , 3) < 0)
   {
       cout << "ERROR: could not listen" << endl;
       return -1;
   }

   //Accept and incoming connection
   cout << "Waiting for incoming connections..." << endl;
   c = sizeof(struct sockaddr_in);

   //Accept connection from an incoming client
   client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
   if (client_sock < 0)
   {
       cout << "ERROR: accept failed" << endl;
       return -1;
   }
   cout <<  "Connection accepted" << endl;

   //Receive a message from client
   while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
   {
       //Send the message back to client
       cout << "QUE: " << client_message << endl;
       write(client_sock , client_message , strlen(client_message));
   }

   if(read_size == 0)
   {
       cout << "Client disconnected" << endl;
       fflush(stdout);
   }
   else if(read_size == -1)
   {
       cout << "ERROR: recv failed" << endl;
       return -1;
   }

   return 0;
}
