/* Program to implement Stop and wait protocol in C language */
// The code runs successfully for 3 ACK and 2 NACK
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX 1024

/*creating structure */

typedef struct packet {
int flag;
int frameno;
char data[20];
}p;
p input();
int main() {

int sockfd;
int n,len;
char buffer[MAX];
int fno = 0;
int option;
struct sockaddr_in servaddr, cliaddr;
/*  creating socket with udp connection  */
sockfd=socket(AF_INET, SOCK_DGRAM, 0);
if(sockfd < 0)
{
perror("error in socket creation");
exit(0);
}
bzero(&servaddr , sizeof(servaddr));
printf("SOCKET CREATED...\n");
printf("Enter 5 8 bit data....\n");
printf("********************\n\n");
p no_of_entries[5];

/* information regarding connection */
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr= INADDR_ANY;

for ( int i=0;i<5;i++)
{
no_of_entries[fno] = input();
if(i%2==0)
no_of_entries[fno].frameno=0;
else if(i%2 !=0)
no_of_entries[fno].frameno=1;

fno+=1;
}
fno=0;

for(int i=0;i<5;i++) {
printf("\n");
printf("\n For the Data %d Do you want to transmit with or withour error",i+1);
printf("\n For errorless transmission press 1");
printf("\n For error transmission press 2\n");
printf("\n your option: ");
scanf("%d",&option);
if(option == 1)
no_of_entries[fno].flag=0;
else if(option == 2 )
no_of_entries[fno].flag=1;

/* msg sent to server */
sendto(sockfd,&no_of_entries[fno],sizeof(p),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 

/*msg from client */
n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

buffer[n]= '\0';
printf("************************");
printf("\n msg from server : %s\n",buffer);
printf("************************");
/*  ****************** */
if(no_of_entries[fno].flag == 1)
{
printf("\n NACK received . Frame has to be retransmitted.. \n");
no_of_entries[fno].flag=0;
sendto(sockfd,&no_of_entries[fno],sizeof(p),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 

n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

buffer[n]= '\0';
printf("************************");
printf("\nmsg from server : %s\n",buffer);
printf("************************");
}
fno +=1;
}


close(sockfd);
return 0;
}

p input()
{
p temp;
printf("Enter 8 bit data : ");
scanf("%s",temp.data);
printf("\n");
return temp;
}
