#include "sock.h"

int data[N]={0};
float sum_time=S_T;
fd_set readset;//fd_set 结构体 
struct timeval interval;//timeout 时间 
char buffer[10]={0};//缓存区 
long Time_init=0;

int main(){
	srand(time(0));
	int i,ret,flag=1;//最大描述符个数的变量 
	for(i=0;i<N;(data[i++]=rand()%500+1)>100?sum_time-=0.5:sum_time);
	sum_time*=1000;//转换为毫秒 
	printf("总时间：%f ms\n",sum_time);
	SOCKET socket_send;  //定义套接字 	
	SOCKADDR_IN Server_add;//服务器地址信息结构 
    if(Init(&Server_add))  exit(0);
    if(Connect(&socket_send,&Server_add)) exit(0);
    Time_init=time(0);//计时开始 
    
    i=0;
    while(if_on()&&i<20){
    	if(flag)
    	Sendmsg(&socket_send,data[i]);
    	ret=check_wait(socket_send);
    	if(!ret) {
    		printf("出错了!!\n");
			break;
		}
    	if(ret==1){
    		recdata(&socket_send);
    		printf("接收到的数据：%s\n",buffer);
    		Sendmsg(&socket_send,rand()%500+1);
    		flag=0;
    		continue;
		}  
    	i++;
		flag=1; 
	}
	
	
	printf("通信结束！\n");
	closesocket(socket_send);//释放套接字 
    WSACleanup();
    
    system("pause");
	return 0;
}





