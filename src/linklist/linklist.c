#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linklist.h>

link_info *link_info_create()
{
	link_info *l=(link_info *)malloc(sizeof(link_info));
	l->next=NULL;
	return l;
}

void link_info_insert(link_info *l,char *username,char *password)
{
	link_info *temp;
	temp=(link_info *)malloc(sizeof(link_info));
	temp->is_online=0;
	strcpy(temp->username,username);
	strcpy(temp->password,password);
	temp->next=l->next;
	l->next=temp;
}

int link_info_del(link_info *l,char *username,char *password)
{
	link_info *temp=l,*temp1;
	while(temp->next!=NULL)
	{
		if(strcmp(temp->next->username,username)==0 && strcmp(temp->next->password,password)==0)
			break;
		temp=temp->next;
	}
	temp1=temp->next;
	temp->next=temp1->next;
	free(temp1);
	if(temp->next==NULL)
		return -1;
}
