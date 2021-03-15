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
	printf("���ӳɹ�����\n\n"); 
    return 0;
}

int check_wait(SOCKET socket){
	int ret;
	interval.tv_sec = 0;//�� 
	interval.tv_usec = TIME;  //΢�� 
	//select ִ��������� interval  
	
	FD_ZERO(&readset);//��� 
	FD_SET(socket, &readset);
	ret = select(socket+1, &readset, NULL, NULL, &interval); 
	if(ret > 0)  return 1;  //������Ҫ���� 
    if(!ret)  return 2; //��ʱ 
    return 0;//������ 
    
} 

void Sendmsg(SOCKET *socket,int data){
    printf("��������: %d\n\n",data);
	sprintf(buffer,"%d",data);
	send(*socket,buffer,10,0);
}

int if_on(){
	float inv=(float)(time(0)-Time_init)*1000;
	printf("�Ѿ���ʱ��%f ms\n",inv);
	if(inv>=sum_time) return 0;
	if((sum_time-inv)> Hal_T) return 1;
	return 0;
}

char* recdata(SOCKET *socket){
	recv(*socket,buffer,10,0);
	return buffer;
}
