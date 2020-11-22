/* Program to implement chat in C language (i.e multiple clients ) */ 
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080
#define MAX 1024
#define SA struct sockaddr
int main(int argc, char **argv)
{
int len;
int sockfd, n = 0;
struct sockaddr_in servaddr, cliaddr;
char str[1000];
char buff[1024];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd == -1)
{
printf("socket creation falied..\n");
exit(0);
}
else
{
printf("Socket successfully created.\n");
}
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(PORT);
if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0)
{printf("Connection with the server failed..\n");
exit(0);
}
else
{
printf("Connected to the server..\n");
}
while(1) {
bzero(buff,MAX);
printf("Enter Message to Server: ");
int s=0;
while((buff[s++]=getchar())!='\n');
n = write(sockfd, buff, sizeof(buff));
if(strncmp(buff,"exit",4)==0)
break;
bzero(buff,MAX);
read(sockfd,buff,sizeof(buff));
printf("Message from server: %s",buff);
}
close(sockfd);
return 0;
}
