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
	printf("连接成功！！\n\n"); 
    return 0;
}

int check_wait(SOCKET socket){
	int ret;
	interval.tv_sec = 0;//秒 
	interval.tv_usec = TIME;  //微秒 
	//select 执行完后会清空 interval  
	
	FD_ZERO(&readset);//清空 
	FD_SET(socket, &readset);
	ret = select(socket+1, &readset, NULL, NULL, &interval); 
	if(ret > 0)  return 1;  //有数据要接收 
    if(!ret)  return 2; //超时 
    return 0;//出错了 
    
} 

void Sendmsg(SOCKET *socket,int data){
    printf("发送数据: %d\n\n",data);
	sprintf(buffer,"%d",data);
	send(*socket,buffer,10,0);
}

int if_on(){
	float inv=(float)(time(0)-Time_init)*1000;
	printf("已经用时：%f ms\n",inv);
	if(inv>=sum_time) return 0;
	if((sum_time-inv)> Hal_T) return 1;
	return 0;
}

char* recdata(SOCKET *socket){
	recv(*socket,buffer,10,0);
	return buffer;
}
