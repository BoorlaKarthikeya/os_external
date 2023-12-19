#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
int sfd,newsfd,s,len,n,i; char buff[100];
struct sockaddr_in servaddr, ca, client;
sfd=socket(AF_INET, SOCK_STREAM,0); //creates a socket
if(sfd<0)
{
perror("socket() error:");
exit(-1);
}
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[1]));
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_addr=inet_addr("172.16.0.100");
s=bind(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
//bind the server with the specified address
if(s<0)
{
perror("bind() error:"); exit(-1);
}
s=listen(sfd,5);
if(s<0) //tells its readiness to TCP if(s<0)
{
perror("listen() error:"); exit(-1);
}
printf("Server is ready and waiting for client requests...........\n");
newsfd=accept(sfd,(struct sockaddr*)&ca,&len); //server blocks fr connection request
if(newsfd<0)
{
perror("accept() error:");
exit(-1);
}
printf("Connected to client........");
n=recv(newsfd,&buff,100,0); //reads data into ‘buff’ from the scoket
buff[n]='\0';
printf("\nMessage from client: %s",buff); //displays the data on to the terminal
for(i=0;buff[i]!='\0';++i)
buff[i]=toupper(buff[i]); //converts the data in the ‘buff’ to upper case
send(newsfd,&buff, n,0); //writes the data from ‘buff’ over to socket.
close(sfd); close(newsfd); //close the connection
return 0;
}
