/* Program to implement Stop and wait protocol in C language */
// The code runs successfully for 3 ACK and 2 NACK
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <string.h>

#define PORT	 8080 
#define MAX 1024 

/*structure for packet */

typedef struct packet {
int flag;
int frameno;
char data[20];
}p;

int main() {
p no_of_entries;
int sockfd;
int n,len;
char buffer[MAX];
struct sockaddr_in servaddr, cliaddr;
/*  creating socket with udp connection  */
sockfd=socket(AF_INET, SOCK_DGRAM, 0);
if(sockfd < 0)
{
perror("error in socket creation");
exit(0);
}
printf("Socket created successfully...\n");
printf("waiting for clients.....\n");

bzero(&servaddr , sizeof(servaddr));
bzero(&cliaddr , sizeof(cliaddr));
char *ack = "ACK";
char *noack="NACK";
/* information regarding connection */
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr= INADDR_ANY;
if(bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
{
perror("BIND FAILED");
exit(0);
}


len = sizeof(cliaddr); 
for(int i=0;i<7;i++){
printf("\n");
n = recvfrom(sockfd, &no_of_entries, sizeof(p),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
printf("\nData: ");
printf("%s",no_of_entries.data);
printf("\nFrame number");
printf("%d",no_of_entries.frameno+1);
if(no_of_entries.flag==0){
printf("\n%s",ack);
printf("\n");
sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
}
else if(no_of_entries.flag==1){
printf("\n%s",noack);
sendto(sockfd, (const char *)noack, strlen(noack), MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);  
}
}

return 0;
}
	
