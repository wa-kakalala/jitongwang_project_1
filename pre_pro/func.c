#include "sock.h"

int Init(SOCKADDR_IN *Server_add){
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData; //库版本信息结构
	char ip[50];
	int port;
	int error=WSAStartup(wVersionRequested,&wsaData);
	if(error){
		printf("加载套接字失败！\n");
		return 1; 
	} 
	if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2){
		printf("版本信息不符合！！\n"); 
		WSACleanup();
		return 1; 
	} 
	puts("输入服务器ip地址：");gets(ip);
	puts("输入服务器端口号：");scanf("%d",&port);
	(*Server_add).sin_family=AF_INET; //地址家族 
	(*Server_add).sin_addr.S_un.S_addr=inet_addr(ip);
	(*Server_add).sin_port=htons(port);
	return 0;	
}

int Connect(SOCKET*socket_send,SOCKADDR_IN *Server_add){
	(*socket_send)=socket(AF_INET,SOCK_STREAM,0);
    if(connect(*socket_send,(SOCKADDR*)Server_add,sizeof(SOCKADDR))==SOCKET_ERROR){
	    printf("连接失败！！\n"); return 1;}  
    return 0;
}
