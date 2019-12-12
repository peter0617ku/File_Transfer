#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(){
	int socketfd, newSocket, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	int i;
	
	FILE *fp = fopen("receive.txt", "wb");  //開啟接收的檔案
	if(fp == NULL){
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}
	
	socketfd = socket(PF_INET, SOCK_STREAM, 0);//插上插座
	  
	serverAddr.sin_family = AF_INET;//TCP本機傳輸
	serverAddr.sin_port = htons(7891);//設定port
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//設定IP
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	bind(socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));//接上電話線

	if(listen(socketfd,5)==0)//聽頻道上有無client要連線->電話響了 拿起聽筒
		printf("Listening\n");
	else
		printf("Error\n");

	addr_size = sizeof serverStorage;

	while(1){
		newSocket = accept(socketfd, (struct sockaddr *) &serverStorage, &addr_size);//接受連線->聽client說話
		
		nBytes = recv(newSocket,buffer,1024,0);
		printf("--> %s\n",buffer);//印出收到的資料
		
		char buffer_file[BUF_SIZE] = {0};  //檔案的buffer
		int nCount;
		while( (nCount = recv(newSocket, buffer_file, BUF_SIZE, 0)) > 0 ){//接收資料
			fwrite(buffer_file, nCount, 1, fp);//將接收到的資料存進file中
		}
		puts("File transfer success!");//傳送＆寫檔成功
	}

	return 0;
} 
