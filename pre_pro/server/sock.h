#ifndef __SOCK_H__
#define __SOCK_H__
#endif

#include<stdio.h>
#include<time.h>
#include<winsock.h>
#include<stdlib.h>

extern char buffer[10];
extern int base[3];

int Init(SOCKADDR_IN *Server_add);
int create_sock(SOCKET*socket_server,SOCKADDR_IN*Server_add);
int Listen(SOCKET*socket_server);
int Accept(SOCKET*socket_server,SOCKET*socket_receive,SOCKADDR_IN*Client_add);
int talk(SOCKET* socket_receive);
void Sendmsg(SOCKET *socket_receive,int data);
