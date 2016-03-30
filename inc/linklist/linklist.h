#ifndef __LISTLINK_H__
#define __LISTLINK_H__
#include <sys/types.h>	       /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef struct usersinfo
{
	int is_online;
	char username[64];
	char password[64];
	int log_or_reg;
	struct sockaddr_in addr;
	struct usersinfo *next;
}link_info;

#define SU_LOG 1
#define FA_LOG 2
#define SU_REG 3
#define FA_REG 4
#define LOG 1;
#define REG 2;
#define IS_REPEAT 5;
#define NOT_REPEAT 6;

extern link_info *link_info_create();
extern void link_info_insert(link_info *l,char *username,char *password);
extern int link_info_del(link_info *l,char *username,char *password);
#endif
