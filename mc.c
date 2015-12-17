#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main()
{
struct sockaddr_in localSock;
struct ip_mreq group;
int sd,reuse = 1;
char databuf[1024];

sd = socket(AF_INET, SOCK_DGRAM, 0);
setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
printf("Setting SO_REUSEADDR...OK.\n");

bzero((char *) &localSock, sizeof(localSock));
localSock.sin_family = AF_INET;
localSock.sin_port = htons(4321);
localSock.sin_addr.s_addr = INADDR_ANY;

bind(sd, (struct sockaddr*)&localSock, sizeof(localSock));
printf("Binding datagram socket...OK.\n");


group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
group.imr_interface.s_addr = INADDR_ANY;
setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));

printf("Adding multicast group...OK.\n");
read(sd, databuf,1024); 

printf("Reading datagram message...OK.\n");
printf("The message from multicast server is: \"%s\"\n", databuf);
return 0;

}
