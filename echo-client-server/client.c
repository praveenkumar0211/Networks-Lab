/* Program to implement echo client server in C Programming language */
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 100
#define PORT 8081
#define SA struct sockaddr
int main()
{
int sockfd, connfd;
struct sockaddr_in servaddr, cli;
char buff[MAX];
int n;
// socket create and varification
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));
// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(PORT);
// connect the client socket to server socket
if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
// function for chat
//func(sockfd);
bzero(buff, sizeof(buff));
printf("Client : ");
n = 0;
while ((buff[n++] = getchar()) != '*');
//scanf("%s",buff);
write(sockfd, buff, sizeof(buff));
read(sockfd, buff, sizeof(buff));
printf("\nEchoed message: %s\n", buff);
//bzero(buff, MAX);
// close the socket
close(sockfd);
}
