/* Send Multicast Datagram Program */
#include<string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
       
int main ()
{
  struct sockaddr_in groupSock;
  int sd;
  sd = socket(AF_INET, SOCK_DGRAM, 0);
  printf("Opening the datagram socket...OK.\n");
  /* group address of 225.1.1.1 and port 5555. */
  bzero((char *) &groupSock,sizeof(groupSock));
  groupSock.sin_family = AF_INET;
  groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
  groupSock.sin_port = htons(4321);
  printf("Setting the local interface...OK\n");
  sendto(sd,"Hi..This is Multicast msg", 27, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)); 
  printf("Sending datagram message...OK\n");
  return 0;
}
