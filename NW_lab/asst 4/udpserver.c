// Assignment 3
// Utkarsh Jaiswal RollNo= 15/CS/11
// Raunak Kumar Singha   RollNo= 15/CS/09


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // Internet family of protocols
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 50026
#define BUFFSIZE 1024


int calculate(char s[]) {
        int n=strlen(s);
        printf("Server %s  and %d \n",s,n);
        int i=0;
        int f=0;
        int c1=0,c2=0;
        int op=-1;
        for(;i<n;i++)
       {
                if(s[i]>='0'&&s[i]<='9'){
                        if(f==0) {
                                c1=c1*10 + (s[i]-48);
                         }
                         else {
                                c2=c2*10 + (s[i]-48);
                         }
                }
                else
                {
                        if(op!=-1)
                        {
                          if(op==0)
                                c1=c1+c2;
                          if(op==1)
                                c1=c1-c2;
                          if(op==2)
                                c1=c1*c2;
                          if(op==3)
                                c1=c1/c2;
                          c2=0;
                        }
                        if(s[i]=='+')
                                op=0;
                        if(s[i]=='-')
                                op=1;
                        if(s[i]=='*')
                                op=2;
                        if(s[i]=='/')
                                op=3;
                        f=1;
                }

       }
       if(op!=-1)
                        {
                          if(op==0)
                                c1=c1+c2;
                          if(op==1)
                                c1=c1-c2;
                          if(op==2)
                                c1=c1*c2;
                          if(op==3)
                                c1=c1/c2;
                        }
      //  printf("chacking = %d\n",c1);
        return c1;

}



int main(){
int socDes ;
struct sockaddr_in thisAddr, thatAddr;
int dataBytes, thatAddrLen ;
char buff[BUFFSIZE] ;
int dataSent;
if((socDes = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
perror("cannot create socket") ;
return 0 ;
}
thisAddr.sin_family = PF_INET ;
thisAddr.sin_addr.s_addr = INADDR_ANY ;
thisAddr.sin_port = htons(PORT) ;

if((bind(socDes, (struct sockaddr *)&thisAddr, sizeof(thisAddr))) < 0) {
perror("cannot bind") ;
return 0 ;
}
thatAddrLen = sizeof(thatAddr) ;
while(1)
{
	if((dataBytes=recvfrom(socDes, buff, BUFFSIZE-1, 0,
	(struct sockaddr *)&thatAddr, &thatAddrLen)) < 0) {
	perror("cannot receive") ;
	return 0 ;
	}
	buff[dataBytes] = '\0' ;
	//printf("Data received: %s\n", buff) ;
	int res=calculate(buff);
	printf("Result calculated by server=%d\n",res);
	char a[100];
	sprintf(a,"%d",res);

	if((dataSent = sendto(socDes, a, 100, 0,(struct sockaddr *)&thatAddr, sizeof(thatAddr))) < 0) {
			perror("cannot send") ;
			return 0 ;
		}
}
return 0 ;
}
