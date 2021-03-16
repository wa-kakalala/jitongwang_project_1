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
	puts("输入服务器连接ip地址：");gets(ip);
	puts("输入服务器连接端口号：");scanf("%d",&port);
	(*Server_add).sin_family=AF_INET; //地址家族 
	(*Server_add).sin_addr.S_un.S_addr=inet_addr(ip);
	(*Server_add).sin_port=htons(port);
	return 0;	
}

int create_sock(SOCKET*socket_server,SOCKADDR_IN*Server_add){//绑定端口 
*socket_server=socket(AF_INET,SOCK_STREAM,0);
if(bind(*socket_server,(SOCKADDR*)Server_add,sizeof(SOCKADDR))==SOCKET_ERROR){
	printf("绑定端口失败!!\n");
	closesocket(*socket_server); 
    WSACleanup();
	return 1;
}
return 0;
} 

int Listen(SOCKET*socket_server){//设置套接字为监听状态
printf("等待连接中..\n");
if(listen(*socket_server,5)<0){
	printf("监听失败!!\n");
	closesocket(*socket_server); 
    WSACleanup();
	return 1;
}	
return 0;
} 

int Accept(SOCKET*socket_server,SOCKET*socket_receive,SOCKADDR_IN*Client_add){
	int Length=sizeof(SOCKADDR);
    *socket_receive=accept(*socket_server,(SOCKADDR*)Client_add,&Length);
    if(*socket_receive==SOCKET_ERROR){
    	closesocket(*socket_receive);
        closesocket(*socket_server);
        WSACleanup();
	    printf("接受连接失败!!\n");
		return 1; 
	} 
	printf("连接成功!!\n\n");
	return 0;
}

int talk(SOCKET* socket_receive){
	int i,data=0;
	memset(buffer,0,sizeof(buffer));
	int ReceiveLen=recv(*socket_receive,buffer,100,0);
	if(ReceiveLen<=0){
       return -1;
	} 
	printf("接受的数据：%s\n",buffer);
	for(i=ReceiveLen-1;i>=0;i--){
		data+=(buffer[i]-48)*base[ReceiveLen-1-i]; 
	}
	return data;
	
} 

void Sendmsg(SOCKET *socket_receive,int data){
    printf("发送的数据: %d\n\n",data);
	sprintf(buffer,"%d",data);
	send(*socket_receive,buffer,10,0);
}
