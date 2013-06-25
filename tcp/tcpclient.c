/***********tcpclient.c***********/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main(int argc, char *argv[])
{
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	struct hostent *host;
	int portnumber, nbytes;
	if(argc!=3)
		{
		fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
		exit(1);
		}
	if((host = gethostbyname(argv[1])) == NULL )
	server_addr.sin_family=AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);

/**********客户程序发起连接请求**************/
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
		{
		fprintf(stderr,"Connect error:%s\n\a",strerror(errno));
		exit(1);
		}
/*********连接成功了*****************/
	if((nbytes=read(sockfd,buffer,1024))==-1)
		{
		fprintf(stderr,"Read error:%s\n\a",strerror(errno));
		exit(1);
		}
	buffer[nbytes]='\0';
	printf("I have recevied:%s \n",buffer);
	/*************结束通信********/
	close(sockfd);
	exit(0);	
}

