#include "sock.h"

int data[N]={0};
float sum_time=(float)S_T;

int main(){
	srand(time(0));
	int i;
	for(i=0;i<N;(data[i++]=rand()%500+1)>100?sum_time-=0.5:sum_time);
	
	SOCKET socket_send;  //�����׽��� 	
	SOCKADDR_IN Server_add;//��������ַ��Ϣ�ṹ 
    if(Init(&Server_add))  exit(0);
    if(Connect(&socket_send,&Server_add)) exit(0);
	return 0;
}





