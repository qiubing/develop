/*********tcpserver.c*********/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define MAXLINE 4096


int main(int argc, char *argv[])
{
	int sockfd,new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sin_size,portnumber;
	const char hello[]="Hello \n";
	if(argc!=2)
		{
		fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
		exit(1);
		}
	if((portnumber = atoi(argv[1]))<0)
		{
		fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
		exit(1);
		}
   printf("%d\n",portnumber);//输出端口号
/******服务器端开始建立socket描述符**********/
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))== -1)
	{
	fprintf(stderr,"Socket error:%s portnumber \a\n",strerror(errno));
	exit(1);
	}
/**********输出描述符*********/
	printf("%d\n",sockfd);

/*******服务器端开始填充sockaddr结构**********/
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(portnumber);

	printf("server_addr create success\n");
/**********捆绑socket描述符******************/
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(server_addr)) == -1)
		{
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
		exit(1);
		}

	printf("bind success\n");//绑定成功

/*********监听sockfd描述符*****************/
	if(listen(sockfd,5)==-1)
		{
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
		exit(1);
		}

	printf("listening now\n");//正在监听

	while(1)
	{
	/********服务器阻塞，直到客户程序建立链接****/
		sin_size = sizeof(struct sockaddr_in);
		if((new_fd = accept(sockfd,(struct sockaddr *)(&client_addr), &sin_size)) ==-1)
		{
		fprintf(stderr, "Accept error:%s\n\a", strerror(errno));
		exit(1);
		}
		fprintf(stderr,"Server get connection from %d\n", inet_ntoa(client_addr.sin_addr));
		if( write(new_fd, hello, strlen(hello)) == -1 )
		{
		fprintf(stderr,"write error:%s\n",strerror(errno));
		exit(1);
		}
		/******通信结束**********/
		close(new_fd);
	}
	/*******循环下一个***********/
		close(sockfd);
		exit(0);
}
