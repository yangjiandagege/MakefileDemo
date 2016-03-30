#include <login.h>

int main()
{
	link_info peerinfo;

	int server_sockfd;
	int addrlen=sizeof(struct sockaddr_in);
	pid_t pid;
	MSG msg;
	struct sockaddr_in server_addr,peer_addr;
	link_info *l=link_info_create();
	link_info *temp=l;
	server_sockfd=server_init(&server_addr);
		while(1)
		{
			server_login_register(l,&peerinfo,server_sockfd);
		}
	exit(0);
}
