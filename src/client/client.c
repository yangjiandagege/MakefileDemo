#include <login.h>

int main()
{
	link_info myinfo;
	int client_sockfd;
	int addrlen=sizeof(struct sockaddr_in);
	char name[64];
	pid_t pid;
	MSG msg;
	MSG msg1;
	struct sockaddr_in client_addr,server_addr;
	myinfo=client_login_register(&client_sockfd);

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr=inet_addr("172.21.19.229");

	if((pid=fork())<0)
	{
		perror("Fail to fork");
		exit(-1);
	}

	if(pid==0)
	{
		while(1)
		{
			recvfrom(client_sockfd,&msg1,sizeof(msg1),0,(struct sockaddr *)&server_addr,&addrlen);
			printf("txt  : %s\n",msg1.buf);
		}
	}

	if(pid>0)
	{
		printf("Who do you want to talk to ?\n");
		scanf("%s",name);
		strcpy(msg.peer_name,name);
		while(1)
		{
			fgets(msg.buf,sizeof(msg.buf),stdin);
			msg.buf[strlen(msg.buf)-1]='\0';
			sendto(client_sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
			if(msg.type==CLIENT_QUIT)
				break;
		}
	}

	exit(0);
}
