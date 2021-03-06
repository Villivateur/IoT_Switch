#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT  10081
#define QUEUE   20
#define BUFFER_SIZE 1024

int main()
{
	while (1)
	{
		int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);


		struct sockaddr_in server_sockaddr;
		server_sockaddr.sin_family = AF_INET;
		server_sockaddr.sin_port = htons(MYPORT);
		server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
		{
			perror("bind");
		}

		///listen，成功返回0，出错返回-1
		if(listen(server_sockfd,QUEUE) == -1)
		{
			perror("listen");
		}

		///客户端套接字
		char buffer[BUFFER_SIZE];
		struct sockaddr_in client_addr;
		socklen_t length = sizeof(client_addr);

		///成功返回非负描述字，出错返回-1
		int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
		if(conn<0)
		{
			perror("connect");
		}

		while(1)
		{
			memset(buffer,0,sizeof(buffer));
			int len = recv(conn, buffer, sizeof(buffer),0);	  
			//printf("recive message from client:\n");
			//fputs(buffer,stdout);
			if (buffer[0]!='6') break;
			//printf("\n");
			FILE *ctrl=fopen("ctrl.in","r");
			buffer[0]=fgetc(ctrl);
			fclose(ctrl);
			//buffer[0]='1';
			//printf("Send messsge to client:\n");
			//fputs(buffer,stdout);
			//printf("\n"); 
			send(conn, buffer, len, 0);
		}
		close(conn);
		close(server_sockfd);
	}
	return 0;
}
