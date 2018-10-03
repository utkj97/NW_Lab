// Assignment 3
// Utkarsh Jaiswal RollNo= 15/CS/11
// Raunak Kumar Singha   RollNo= 15/CS/09

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // Internet family of protocols
#include <arpa/inet.h>
#include <unistd.h>

#define SERVERIP "127.0.0.1"
#define PORT 50026
#define BUFFSIZE 1024
int main(){
int socDes ;
struct sockaddr_in thatAddr ;
char buff[BUFFSIZE] = "NIT DURGAPUR" ;
int dataBytes = 1000, dataSent ;
if((socDes = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
perror("cannot create socket") ;
return 0 ;
}
thatAddr.sin_family = PF_INET ;
thatAddr.sin_addr.s_addr = inet_addr(SERVERIP) ;
thatAddr.sin_port = htons(PORT) ;
int thatAddrLen = sizeof(thatAddr) ;
while(1)
{
printf("Enter the Arithmetic Expression\n");
gets(buff);
char buf[BUFFSIZE];
int m=0;
for(int j=0;j<strlen(buff)+1;j++)
{
	if(buff[j]!=' ')
	{
		buf[m]=buff[j];
		m++;
	}
}
char f[10]="-1";
if(strcmp(buf,f)==0)
	break;
if((dataSent = sendto(socDes, buf, dataBytes, 0,
(struct sockaddr *)&thatAddr, sizeof(thatAddr))) < 0) {
perror("cannot send") ;
return 0 ;
}
char si[100];
if((dataBytes=recvfrom(socDes, si, BUFFSIZE-1, 0,
	(struct sockaddr *)&thatAddr, &thatAddrLen)) < 0) {
	perror("cannot receive") ;
	return 0 ;
	}
printf("Received by client = %s\n",si);

}

close(socDes) ;
return 0 ;
}
