#include "sock.h"


int Init(SOCKADDR_IN *Server_add){
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData; //��汾��Ϣ�ṹ
	char ip[50];
	int port;
	int error=WSAStartup(wVersionRequested,&wsaData);
	if(error){
		printf("�����׽���ʧ�ܣ�\n");
		return 1; 
	} 
	if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2){
		printf("�汾��Ϣ�����ϣ���\n"); 
		WSACleanup();
		return 1; 
	} 
	puts("�������������ip��ַ��");gets(ip);
	puts("������������Ӷ˿ںţ�");scanf("%d",&port);
	(*Server_add).sin_family=AF_INET; //��ַ���� 
	(*Server_add).sin_addr.S_un.S_addr=inet_addr(ip);
	(*Server_add).sin_port=htons(port);
	return 0;	
}

int create_sock(SOCKET*socket_server,SOCKADDR_IN*Server_add){//�󶨶˿� 
*socket_server=socket(AF_INET,SOCK_STREAM,0);
if(bind(*socket_server,(SOCKADDR*)Server_add,sizeof(SOCKADDR))==SOCKET_ERROR){
	printf("�󶨶˿�ʧ��!!\n");
	closesocket(*socket_server); 
    WSACleanup();
	return 1;
}
return 0;
} 

int Listen(SOCKET*socket_server){//�����׽���Ϊ����״̬
printf("�ȴ�������..\n");
if(listen(*socket_server,5)<0){
	printf("����ʧ��!!\n");
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
	    printf("��������ʧ��!!\n");
		return 1; 
	} 
	printf("���ӳɹ�!!\n\n");
	return 0;
}

int talk(SOCKET* socket_receive){
	int i,data=0;
	memset(buffer,0,sizeof(buffer));
	int ReceiveLen=recv(*socket_receive,buffer,100,0);
	if(ReceiveLen<=0){
       return -1;
	} 
	printf("���ܵ����ݣ�%s\n",buffer);
	for(i=ReceiveLen-1;i>=0;i--){
		data+=(buffer[i]-48)*base[ReceiveLen-1-i]; 
	}
	return data;
	
} 

void Sendmsg(SOCKET *socket_receive,int data){
    printf("���͵�����: %d\n\n",data);
	sprintf(buffer,"%d",data);
	send(*socket_receive,buffer,10,0);
}
