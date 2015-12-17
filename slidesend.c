#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
main()
{
	int std, len, choice, i,j,status,sendsize,port,recvsize,temp1;
	char str[20], frame[20],  ack[20];
	char *msg="network programming " ; 
	struct sockaddr_in saddr, caddr;
	port=5000;
	printf("Enter the port address");
	scanf("%d", &port);
	std = socket(AF_INET, SOCK_STREAM, 0);
	if(std<0)
		perror("Error");
	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);
	saddr.sin_port = htons(port);
	connect(std, (struct sockaddr *)&saddr, sizeof(saddr));
	printf("\n msg= %s ",msg);
	printf("\n len = %d ",strlen(msg) );
	i = 0;
	sendsize=5;
	while(i<strlen(msg))
	{

		memset(frame, 0, 20); 
		strncpy(frame, msg+i, sendsize);
		printf("\n\nSending frame = %s , Sending WINDOW: start seqno= %d end seqno= %d ",frame ,i , i+sendsize );
		send(std, frame, strlen(frame), 0) ;
		printf("\n sending data and wait for ack");
		memset(ack, 0, 20);
		recv(std, ack, 100, 0) ;
		sscanf(ack, "%d", &status);
		printf("\n recvd ack no = %d ",status);
		
		i=status;
		
	} 
	write(std, "Exit", sizeof("Exit"));
	printf("\nExitting!\n");
	close(std);
}
