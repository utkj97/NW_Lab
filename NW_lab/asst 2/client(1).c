//Network Lab - Assignment 1
//Group 6

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
main()
{
	int sockfd;
	struct sockaddr_in serv_addr;
	int i;
	char buf[100], result[100];
	
	while(1) {

		printf("\nenter the expression to be evaluated or press 'q' to quit:\n");
		scanf("%s", buf);
		if(buf[0] == 'q')
			break;

		if((sockfd = socket (AF_INET,SOCK_STREAM,0) ) < 0)
		{
			printf("Cannot Create Socket\n");
			exit(0);
		}
		
		serv_addr.sin_family 		= AF_INET;
		serv_addr.sin_addr.s_addr   = inet_addr("127.0.0.1");
		serv_addr.sin_port 			= htons(5000);

		if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		{
			printf("Unable to connect to server\n");
			exit(0);
		}

		send(sockfd, buf, strlen(buf) + 1, 0);

		recv(sockfd, result, 100, 0);
		printf("Server evaluated the expression as %s\n", result);

	}	
	close(sockfd);
}

