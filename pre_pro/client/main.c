#include "sock.h"

int data[N]={0};
float sum_time=S_T;
fd_set readset;//fd_set �ṹ�� 
struct timeval interval;//timeout ʱ�� 
char buffer[10]={0};//������ 
long Time_init=0;

int main(){
	srand(time(0));
	int i,ret,flag=1;//��������������ı��� 
	for(i=0;i<N;(data[i++]=rand()%500+1)>100?sum_time-=0.5:sum_time);
	sum_time*=1000;//ת��Ϊ���� 
	printf("��ʱ�䣺%f ms\n",sum_time);
	SOCKET socket_send;  //�����׽��� 	
	SOCKADDR_IN Server_add;//��������ַ��Ϣ�ṹ 
    if(Init(&Server_add))  exit(0);
    if(Connect(&socket_send,&Server_add)) exit(0);
    Time_init=time(0);//��ʱ��ʼ 
    
    i=0;
    while(if_on()&&i<20){
    	if(flag)
    	Sendmsg(&socket_send,data[i]);
    	ret=check_wait(socket_send);
    	if(!ret) {
    		printf("������!!\n");
			break;
		}
    	if(ret==1){
    		recdata(&socket_send);
    		printf("���յ������ݣ�%s\n",buffer);
    		Sendmsg(&socket_send,rand()%500+1);
    		flag=0;
    		continue;
		}  
    	i++;
		flag=1; 
	}
	
	
	printf("ͨ�Ž�����\n");
	closesocket(socket_send);//�ͷ��׽��� 
    WSACleanup();
    
    system("pause");
	return 0;
}





