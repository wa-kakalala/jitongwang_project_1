#ifndef __SOCK_H__
#define __SOCK_H__
#endif


#include<stdio.h>
#include<time.h>
#include<winsock.h>
#include<stdlib.h>
#define N 20
#define S_T 10
#define TIME 500000
#define Hal_T 250

extern int data[N];
extern char buffer[10];
extern float sum_time;
extern fd_set readset;
extern struct timeval interval;
extern long Time_init;

int Init(SOCKADDR_IN *Server_add);
int Connect(SOCKET*socket_send,SOCKADDR_IN *Server_add);
int check_wait(SOCKET socket); 
void Sendmsg(SOCKET *socket,int data);
int if_on();
char* recdata(SOCKET *socket);




