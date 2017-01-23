/*
 *  -----------------------------------------
 *  TCP Test Server 1.00
 *  -----------------------------------------
 *  Author: Adam Blaszczyk
 *          http://wyciekpamieci.blogspot.com
 *  Date:   2017-01-23
 *  -----------------------------------------
 *  
 *  Compilation (Windows):
 *         gcc tcp-test-server-win.c -o tcp-test-server -lws2_32
 *
 *  Usage:
 *         tcp-test-server
 *         - default port is 6996
 *
 *         tcp-test-server.exe port_number
 *
 */

#include <stdio.h>
#include <winsock2.h>
  
int main(int argc , char **argv)
{
  WSADATA wsa;
  SOCKET socket1, socket2;
  struct sockaddr_in server, client;
  int port_number;
  int b;
  char *message;

  printf("\n");
  printf("+------------------------+\n");
  printf("|  TCP TEST SERVER 1.00  |\n");
  printf("+------------------------+\n");
  printf("\n");
  printf("[Ctrl]+[C] to exit server\n");
  printf("\n");

  port_number = 6996;  //default port_number
  if(argc == 2)
    port_number = atoi(argv[1]);

  printf("Initialising Winsock...");
  if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
    printf("Failed. Error Code : %d", WSAGetLastError());
    return 1;
  }    
  printf("Initialised\n");
     
  //Create a socket
  if((socket1 = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
    printf("Could not create socket : %d" , WSAGetLastError());
  } 
  printf("Socket created\n");
     
  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port_number);
     
  //Bind
  if( bind(socket1 ,(struct sockaddr *) &server , sizeof(server)) == SOCKET_ERROR) {
    printf("Bind failed with error code : %d" , WSAGetLastError());
    exit(EXIT_FAILURE);
  }     
  puts("Bind done");
 
  //Listen to incoming connections
  listen(socket1, 3);
     
  //Accept and incoming connection
  printf("Waiting for incoming connections on port %d...\n", port_number);
     
  b = sizeof(struct sockaddr_in);
     
  while( (socket2 = accept(socket1 , (struct sockaddr *) &client, &b)) != INVALID_SOCKET ) {
    puts("Connection accepted");
    //Reply to the client
    message = "Hello";
    send(socket2 , message , strlen(message) , 0);
  }
     
  if (socket2 == INVALID_SOCKET) {
    printf("Accept failed with error code : %d" , WSAGetLastError());
    return 1;
  }
 
  closesocket(socket1);
  WSACleanup();
     
  return 0;
}
