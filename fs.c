#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define MAXLINE 4096
int main(){
	int readfd,writefd,n;
	FILE *fd;
	char buf[MAXLINE+1];

	printf("\nCreating pipe1(FIFO1)");
	mkfifo(FIFO1,0666);
	printf("\nCreating pipe2(FIFO2)");
	mkfifo(FIFO2,0666);

	readfd=open(FIFO1,O_RDONLY,0);
	writefd=open(FIFO2,O_WRONLY,0);

	read(readfd,buf,MAXLINE);

	printf("\nReading from FIFO1.... The filename is %s\n",buf);

	if((fd=fopen(buf,"r"))==NULL){
		strcpy(buf,"SERVER ERROR: File dose not exist\n");
		printf("SERVER ERROR: File dose not exist\n");
		n=strlen(buf);
		write(writefd,buf,n);
		return 0;
	}

	printf("\nReading from file %s and writting to FIFO2\n",buf);

	while((fgets(buf,79,fd))!=NULL){
		write(writefd,buf,79);
		printf("%s\n",buf);
	}

	fclose(fd);
	return 0;
}
