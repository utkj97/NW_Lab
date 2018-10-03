//Network Lab - Assignment 1
//Group 6

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int calculate(char s[]) {
        
        int n = strlen(s);
        int i = 0;
        int f = 0;
        int c1 = 0, c2 = 0;
        int op = -1;
        for(; i < n; i++)
       {
                if(s[i] >= '0' && s[i] <= '9'){
                        if(f == 0) {
                                c1 = c1*10 + (s[i] - 48);
                         }
                         else {
                                c2 = c2*10 + (s[i] - 48);
                         }
                }
                else
                {
                        if(op != -1)
                        {
                          if(op == 0)
                                c1 = c1 + c2;
                          if(op == 1)
                                c1 = c1 - c2;
                          if(op == 2)
                                c1 = c1 * c2;
                          if(op == 3)
                                c1 = c1 / c2;  
                          c2 = 0;    
                        }
                        if(s[i] == '+')
                                op = 0;
                        if(s[i] == '-')
                                op = 1;
                        if(s[i] == '*')
                                op = 2;
                        if(s[i] == '/')
                                op = 3;
                        f = 1;
                }
        
       }
       if(op != -1)
                        {
                          if(op == 0)
                                c1 = c1 + c2;
                          if(op == 1)
                                c1 = c1 - c2;
                          if(op == 2)
                                c1 = c1 * c2;
                          if(op == 3)
                                c1 = c1 / c2;      
                        }
     
        return c1;
        
}
	
main()
{
	int sockfd, newsockfd;
	int clilen, i;
	struct sockaddr_in cli_addr, serv_addr;
	char buf[100];

	if((sockfd = socket (AF_INET,SOCK_STREAM, 0)) < 0)
	{
		printf("Cannot Create Socket\n");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(5000);
	
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	{
		printf("Unable to bind local address\n");
		exit(0);
	}

	listen(sockfd, 5);

	while(1)
	{
		clilen = sizeof(cli_addr);

		newsockfd = accept (sockfd, (struct sockaddr*) &cli_addr, &clilen);

		if (newsockfd < 0)
		{
			printf ("Accept Error\n");
			exit (0);
		}
	
		recv(newsockfd, buf, 100, 0);
		printf("Received : %s\n", buf);
		
		int c = calculate(buf);
        		//s is the string format of c
       		 printf("\nthe calculated value of the expression is: %d", c);

        		char s[100];
        		//converting the integer result to string format
        		snprintf(s, sizeof(s), "%d", c);
      		  printf("The result evaluated in string format is: %s\n", s);

        		//seding the evaluated value to client.
       		 send(newsockfd, s, strlen(s) + 1, 0);
		
	}
	close(newsockfd);
}