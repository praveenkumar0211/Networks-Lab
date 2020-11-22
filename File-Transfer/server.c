/* Program to implement File transfer in networks using C Language */
//file_server.c
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#define PORT 8080
#define MAX 1024
#define SA struct sockaddr
int main(int argc, char **argv)
{
int len;
int sockfd, newfd, n;
struct sockaddr_in servaddr, cliaddr;
char buff[1024];
char str[1000];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
printf("Server Socket is created.\n");
if(sockfd < 0)
perror("Cannot create socket!\n");
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY; //htonl("127.0.0.1");
servaddr.sin_port = htons(PORT);
if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0)
{
printf("Socket bind failed..\n");exit(0);
}
printf("Socket successfully binded..\n");
if(listen(sockfd, 5) == 0){
printf("Listening....\n");
}
else{
printf("Error in binding.\n");
}
len = sizeof(cliaddr);
newfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
n = read(newfd, buff, sizeof(buff));
printf("File name: %s\n", buff);
int fd = open(buff, O_RDONLY);
if(fd < 0)
strcpy(buff, "Does not exist!\n");
else
{
n = 0;
bzero(buff, sizeof(buff));
read(fd, buff, sizeof(buff));
close(fd);
}
n = write(newfd, buff, sizeof(buff));
printf("File transferred\n");
close(newfd);
close(sockfd);
return 0;
}
