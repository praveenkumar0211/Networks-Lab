/*program to implement simple client server connection in C Programming language */
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc, char **argv)
{
int len;
int sockfd, n;
struct sockaddr_in servaddr, cliaddr;
char buff[1024];
char str[1000];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd<0)
perror("Cannot create socket");
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr(argv[1]);
servaddr.sin_port = htons(7229);
connect(sockfd,(struct sockaddr*) &servaddr, sizeof(servaddr));
//sending msg
printf("Client: ");
scanf("%s", buff);
n = write(sockfd, buff, sizeof(buff));
n = read(sockfd, buff, sizeof(buff));
printf("Message from server: %s\n", buff);
close(sockfd);
return 0;}
