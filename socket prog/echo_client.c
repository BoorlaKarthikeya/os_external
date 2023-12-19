#include <stdio.h>
#include <stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define MAX 1000
int main(int argc, char *argv[])
{
int sfd,newsfd,s,len,n; char buff[MAX+1];
struct sockaddr_in servaddr,sa;
sfd=socket(AF_INET, SOCK_STREAM,0);
if(sfd<0)
{
perror("socket() error:");
exit(-1);
}
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[1])); 
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
s=connect(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(s<0)
{
perror("connect() error:");
exit(-1);
}
write(1,"Enter a message: ",17);
n=read(0,&buff,100); //read a message from keyboard (i.e. From user)
send(sfd,&buff,n,0); //writes the message over to the socket from the buffer
n=recv(sfd,&buff,MAX,0); //reads a message from the socket into the buffer
write(1,"Received from server: ",22);
write(1,&buff,n); //display the message on the terminal
close(sfd);
return 0;
}
