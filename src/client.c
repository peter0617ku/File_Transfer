#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUF_SIZE 1024

int main(){
	int clientSocket, portNum, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	char *filename = "/home/tensorflow/test.txt";  //文件名
	FILE *fp = fopen(filename, "rb");  //以二进制方式打开文件
	if(fp == NULL){
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);//插上插座

	serverAddr.sin_family = AF_INET;//TCP本機連線
	serverAddr.sin_port = htons(7891);//設定port
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//設定IP
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);//撥號碼 打給server
	
	strcpy(buffer,"starting");
	nBytes = strlen(buffer) + 1;
	send(clientSocket,buffer,nBytes,0);//對server講話

	char buffer_file[BUF_SIZE] = {0};  //裝檔案的buffer
    	int nCount;
	while( (nCount = fread(buffer_file, 1, BUF_SIZE, fp)) > 0 ){//讀檔
		send(clientSocket, buffer_file, nCount, 0);//傳送檔案
	}
	fclose(fp);//關閉file descriptor

	printf("Client End!\n");
	return 0;
} 
