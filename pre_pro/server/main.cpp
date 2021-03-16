#include "sock.h"

char buffer[10]={0};//缓冲区
int base[3]={1,10,100};

int main() {
	int data=0,res=0;	
	SOCKET socket_server;  //定义服务器套接字 
	SOCKET socket_receive; //定义用于连接的套接字
	SOCKADDR_IN Server_add;//服务器地址信息结构 
	SOCKADDR_IN Client_add; //客户端地址信息结构
	
	if(Init(&Server_add))  exit(0);
	if(create_sock(&socket_server,&Server_add)) exit(0); 
	if(Listen(&socket_server)) exit(0);
	if(Accept(&socket_server,&socket_receive,&Client_add)) exit(0);
	while(1){
		printf("---------------------\n"); 
	    data=talk(&socket_receive);
		if(data==-1) break;
		
		res=data+(rand()%500+1);
		printf("计算结果为:%d \n",res); 

		if(res>100)  Sendmsg(&socket_receive,res);	
		printf("---------------------\n\n");
	}
	closesocket(socket_receive);
	closesocket(socket_server);
	WSACleanup();
	printf("通信结束!!\n");
	
	system("pause");
	return 0;
}
