/* Program to implement chat in C language (i.e multiple clients ) */  
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
int main(int argc, char **argv){
int len, clients[5], selsd;
int sockfd, newfd, n = 0;
struct sockaddr_in servaddr, cliaddr;
fd_set readfds;
char buff[1024];
char str[1000];
for(int i = 0; i < 5; i++)
clients[i] = 0;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
printf("Server Socket is created.\n");
if(sockfd < 0)
perror("Cannot create socket!\n");
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);
if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0)
{
printf("Socket bind failed..\n");
exit(0);
}
printf("Socket successfully binded..\n");
if(listen(sockfd, 5) == 0){
printf("Listening....\n");
}else{
printf("Error in binding.\n");
}
len = sizeof(cliaddr);
int all_clients_open =1;
while(all_clients_open==1) {FD_ZERO(&readfds);
FD_SET(sockfd, &readfds);
selsd = sockfd;
for(int i = 0; i < 5; i++) {
int sd = clients[i];
if(sd > 0) FD_SET(sd, &readfds);
if(sd > selsd) selsd = sd;
}
int activity = select(selsd + 1, &readfds, NULL, NULL,
NULL);
if(FD_ISSET(sockfd, &readfds)) {
newfd = accept(sockfd, (struct sockaddr*)&cliaddr,
&len);
for(int i = 0; i < 5; i++) {
if(clients[i] == 0) {
clients[i] = newfd;
break;
}
}
}
for(int i = 0; i < 5; i++) {
if(FD_ISSET(clients[i], &readfds))
{
read(clients[i], buff, 1024);
if(strncmp(buff,"exit",4)==0)
{
close(clients[i]);
clients[i] = 0;
printf("[-]Client %d closed!\n", i);
all_clients_open=0;
for(int k=0;k<5;k++)
{
if(clients[k]!=0)
{all_clients_open=1;break;}
}}
else {
printf("Client %d: %s \n", i, buff);
bzero(buff,MAX);
printf("To Client %d: ",i);
n=0;
while((buff[n++]=getchar())!='\n');
write(clients[i],buff,sizeof(buff));
}
}
}
}
printf("All clients are closed.. Server shutting down..\n");
close(sockfd);
return 0;
}
