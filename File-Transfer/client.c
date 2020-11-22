/* Program to implement File transfer in networks using C Language */
//file_client.c
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#define PORT 8080
#define MAX 1024
#define SA struct sockaddr
int main()
{
int sockfd, n = 0;
struct sockaddr_in servaddr, cliaddr;
char fname[1000];
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
{
printf("Connection with the server failed..\n");
exit(0);
}
else
{
printf("Connected to the server..\n");
}
printf("Enter the path of file: ");
scanf("%s", buff);
n = write(sockfd, buff, sizeof(buff));
char new_path[100];
printf("Save the file in path: ");
scanf("%s", new_path);
int fd = creat(new_path, S_IRWXU);
n = read(sockfd, buff, sizeof(buff));
write(fd, buff, strlen(buff));
printf("File transferred\n");
close(fd);
close(sockfd);
return 0;
}
