#include "sock.h"

char buffer[10]={0};//������
int base[3]={1,10,100};

int main() {
	int data=0,res=0;	
	SOCKET socket_server;  //����������׽��� 
	SOCKET socket_receive; //�����������ӵ��׽���
	SOCKADDR_IN Server_add;//��������ַ��Ϣ�ṹ 
	SOCKADDR_IN Client_add; //�ͻ��˵�ַ��Ϣ�ṹ
	
	if(Init(&Server_add))  exit(0);
	if(create_sock(&socket_server,&Server_add)) exit(0); 
	if(Listen(&socket_server)) exit(0);
	if(Accept(&socket_server,&socket_receive,&Client_add)) exit(0);
	while(1){
		printf("---------------------\n"); 
	    data=talk(&socket_receive);
		if(data==-1) break;
		
		res=data+(rand()%500+1);
		printf("������Ϊ:%d \n",res); 

		if(res>100)  Sendmsg(&socket_receive,res);	
		printf("---------------------\n\n");
	}
	closesocket(socket_receive);
	closesocket(socket_server);
	WSACleanup();
	printf("ͨ�Ž���!!\n");
	
	system("pause");
	return 0;
}
