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
	puts("���������ip��ַ��");gets(ip);
	puts("����������˿ںţ�");scanf("%d",&port);
	(*Server_add).sin_family=AF_INET; //��ַ���� 
	(*Server_add).sin_addr.S_un.S_addr=inet_addr(ip);
	(*Server_add).sin_port=htons(port);
	return 0;	
}

int Connect(SOCKET*socket_send,SOCKADDR_IN *Server_add){
	(*socket_send)=socket(AF_INET,SOCK_STREAM,0);
    if(connect(*socket_send,(SOCKADDR*)Server_add,sizeof(SOCKADDR))==SOCKET_ERROR){
	    printf("����ʧ�ܣ���\n"); return 1;}  
    return 0;
}
