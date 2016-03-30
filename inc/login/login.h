#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linklist.h>

typedef struct
{
	int type;
	char name[15];
	char peer_name[15];
	char buf[1024];
	struct sockaddr my_addr;
}MSG;

#define CLIENT_LOGIN 10
#define CLIENT_TALK  20
#define CLIENT_QUIT  30
#define SERVER_BORADCAST 40
#define TALK_TO 50


extern int qq_login(link_info *l,char *username,char *password,link_info *myinfo,struct sockaddr_in *peer_addr);
extern int qq_register(link_info *l,char *username,char *password,link_info *myinfo);
extern int qq_dispaly(link_info *l);
extern int save_file(link_info *temp);
extern int read_file(link_info *l);
extern link_info client_login_register(int *client_sockfd);
extern int server_init(struct sockaddr_in *s_addr);
extern void server_login_register(link_info *l,link_info *myinfo,int server_fd);
extern int username_repeat(link_info *l,char *username);
#endif
