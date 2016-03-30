#include <login.h>


int username_repeat(link_info *l,char *username)
{
	link_info *temp=l;
	while(temp->next!=NULL)
	{
		if(strcmp(temp->next->username,username)==0)
			return IS_REPEAT;
		temp=temp->next;
	}
	return NOT_REPEAT;
}

int qq_login(link_info *l,char *username,char *password,link_info *myinfo,struct sockaddr_in *peeraddr)
{
	link_info *temp=l,*temp1;

	while(temp->next!=NULL)
	{
		if(strcmp(temp->next->username,username)==0 && strcmp(temp->next->password,password)==0)
		{
			temp->next->addr=*peeraddr;
			printf("ip : %s\n",inet_ntoa(temp->next->addr.sin_addr));
			temp->next->is_online=SU_LOG;
			*myinfo=*(temp->next);
			break;
		}
		temp=temp->next;
	}

	if(temp->next==NULL)
	{
		return FA_LOG;
		printf("Input error\n");
	}else
		printf("%s login now\n",username);
	return SU_LOG;
}

int qq_register(link_info *l,char *username,char *password,link_info *myinfo)
{
	int rep;
	rep=username_repeat(l,username);
	if(rep==6)
	{
		link_info_insert(l,username,password);
		save_file(l->next);
		printf("%s finish register\n",l->next->username);
		return SU_REG;
	}
	return FA_REG;
}

int qq_dispaly(link_info *l)
{
	link_info *temp=l;
	while(temp->next!=NULL)
	{
		printf("%s\n",temp->next->username);
		temp=temp->next;
	}
	return 0;
}

int save_file(link_info *temp)
{
	FILE *fp;
	if((fp=fopen("userinfo","a+"))<0)
	{
		perror("Fail to open file ");
		exit(-1);
	}
	fwrite(temp,sizeof(link_info),1,fp);
	fclose(fp);
	return 0;
}

int read_file(link_info *l)
{
	link_info user_info;
	int n;
	FILE *fp;
	if((fp=fopen("userinfo","a+"))<0)
	{
		perror("Fail to open file ");
		exit(-1);
	}
	while(1)
	{
		n=fread(&user_info,sizeof(user_info),1,fp);
		if(n==0)
			break;
		link_info_insert(l,user_info.username,user_info.password);
	}
    printf("yang\n");
	fclose(fp);
	return 0;
}

link_info client_login_register(int *client_sockfd)
{
	char username[64];
	char password[64];
	char password_again[64];
	int cmd;
	int rt;
	int client_fd;
	link_info myinfo;
	struct sockaddr_in server_addr;

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr=inet_addr("192.168.1.106");


	printf("1 login \n");
	printf("2 register \n");
	scanf("%d",&cmd);
	printf("Prease input the username:\n");
	scanf("%s",username);
	printf("Prease input the password:\n");
	scanf("%s",password);
	strcpy(myinfo.username,username);
	strcpy(myinfo.password,password);

	if((client_fd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("fail to socket");
		exit(-1);
	}
	*client_sockfd=client_fd;

	if(cmd==1)
	{
		myinfo.log_or_reg=LOG;
	}
	if(cmd==2)
	{
		myinfo.log_or_reg=REG;
again:
		printf("Please input the password again\n");
		scanf("%s",password_again);
		if(strcmp(password_again,password)!=0)
		{
			printf("Two different input\n");
			goto again;
		}
	}

	if(sendto(client_fd,&myinfo,sizeof(myinfo),0,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)
	{
		perror("Fail to send");
		exit(-1);
	}
	printf("send\n");
	recvfrom(client_fd,&myinfo,sizeof(myinfo),0,NULL,NULL);
	printf("recv\n");
	switch(myinfo.is_online)
	{
		case SU_LOG:
			printf("Success to login\n");
			break;
		case FA_LOG:
			printf("Fail to login\n");
			break;
		case SU_REG:
			printf("Success to register\n");
			exit(-1);
		case FA_REG:
			printf("Fail to register,mybe uername repeat! \n");
			exit(-1);
	}

	return myinfo;
}

int server_init(struct sockaddr_in *s_addr)
{
    int server_fd;
	struct sockaddr_in server_addr,peer_addr;
	if((server_fd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Fail to socket");
		exit(-1);
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr=inet_addr("172.21.19.229");
	if(bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("Fail to bind");
		exit(-1);
	}
	*s_addr=server_addr;

	int on=1;
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
	{
		perror("Fail to setsockopt");
		exit(-1);
	}
	return server_fd;
}

void server_login_register(link_info *l,link_info *myinfo,int server_fd)
{
	int rt;
	link_info peerinfo;
	struct sockaddr_in peer_addr;
	int addrlen=sizeof(struct sockaddr_in);
	read_file(l);
    qq_dispaly(l);
	if(recvfrom(server_fd,&peerinfo,sizeof(peerinfo),0,(struct sockaddr *)&peer_addr,&addrlen)<0)
	{
		perror("Fail to recv");
		exit(-1);
	}
	printf("recv\n");

	if(peerinfo.log_or_reg==1)
	{
		printf("peername : %s\n",peerinfo.username);
		rt=qq_login(l,peerinfo.username,peerinfo.password,myinfo,&peer_addr);
		if(rt==1)
			peerinfo.is_online=SU_LOG;
		if(rt==2)
			peerinfo.is_online=FA_LOG;
	}

	if(peerinfo.log_or_reg==2)
	{
		rt=qq_register(l,peerinfo.username,peerinfo.password,myinfo);
		if(rt==3)
			peerinfo.is_online=SU_REG;
		if(rt==4)
			peerinfo.is_online=FA_REG;
	}

	sendto(server_fd,&peerinfo,sizeof(peerinfo),0,(struct sockaddr *)&peer_addr,sizeof(struct sockaddr));
	printf("send\n");
}

