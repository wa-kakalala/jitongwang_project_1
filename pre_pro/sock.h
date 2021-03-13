#ifndef __SOCK_H__
#define __SOCK_H__
#endif

#include<stdio.h>
#include<time.h>
#include<winsock.h>
#define N 20
#define S_T 10

extern int data[N];
extern float sum_time;
int Init(SOCKADDR_IN *Server_add);
int Connect(SOCKET*socket_send,SOCKADDR_IN *Server_add);




