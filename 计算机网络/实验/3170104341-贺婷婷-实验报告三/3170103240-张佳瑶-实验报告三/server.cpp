
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<pthread.h>
#include<vector>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

using namespace std;
#define BUFFER_LENGTH 1024
#define HOSTNAME_LENGTH 1024
#define IP_LENGTH 20
#define MESSAGE_LENGTH 2048
//id,IP,port
typedef struct clientInfo
{
	int conn;
	char ip[IP_LENGTH];
	int port;
}Item;
vector<Item> clientList;
int sendMessage(int conn, char * msg);
void* clientHandleThread(void* arg);
int analyseMessage(int conn, char * data);

int main()
{
	struct sockaddr_in serverAddr;
	//My studentid is 3170104341
	int port = 4341;
	int sockfd;
	puts("Server:I'm starting!Please wait a few seconds~");
	puts("Server:Initilizing...");
	//initialize
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		fprintf(stderr, "Something wrong happends while Initilizing (T＿T)Please try again.\n");
		exit(-1);
	}
	puts("Server:Binding...");
	//Bind the server
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	//uint32_t s_addr;
	//INADDR_ANY（ linux下的socket INADDR_ANY表示的是一个服务器上所有的网卡（服务器可能不止一个网卡） 多个本地ip地址都进行绑定端口号，进行侦听。
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (-1 == bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		fprintf(stderr, "Something wrong happends while binding (T＿T)Please try again.\n");
		exit(-1);
	}
	puts("Server: Listening...");
	//int listen(int sockfd, int backlog);最大连接个数
	if (-1 == listen(sockfd, 10))
	{
		fprintf(stderr, "Something wrong happends while listening (T＿T)Please try again.\n");
		exit(-1);
	}
	//start working;
	puts("Server：I'm working now╰(￣▽￣)╭");
	//waiting for the connections and cycle to handle them.
	while (true)
	{
		//get the conn of client
		struct sockaddr_in clientAddr;
		socklen_t addrLength = sizeof(clientAddr);
		//conn- the TCP connection socket descriptor
		int conn = accept(sockfd, (struct sockaddr*)&clientAddr, &addrLength);
		if (-1 == conn)
		{
			fprintf(stderr, "Server: I can't connect the client, is there something wrong?\n");
			continue;//ignore this client and continue the loop
		}
		printf("Server: Now we've got a new client[%d]!A thread prepared for it is creating.\n", conn);
		pthread_t pid; 
		pthread_t thread;
		//create a thread for the client to handle its requests
		if (pthread_create(&thread, NULL, clientHandleThread, &conn) != 0)//创建子线程  
		{
			fprintf(stderr, "Server: There's somthing wrong while creating the thread!\n");
			break;
		}
		//get the ip of the client to create a client list
		Item a;
		a.conn = conn;
		strcpy(a.ip, inet_ntoa(clientAddr.sin_addr));
		a.port = ntohs(clientAddr.sin_port);
		clientList.push_back(a);
		//这边的内存分配还有点问题我不太清楚，待解决。注意关闭后要vec.erase(i).

	}
}

//处理一些用户连接的准备事宜，比如在服务器端存储该用户的昵称，在屏幕上显示用户的连接信息，以及匿名处理等等。
//调用handleMessage函数处理用户的请求,如果此时收到了关闭连接的请求的话，会跳出for循环。之后用户连接将不复存在，这个进程也会被关闭，

void* clientHandleThread(void* arg)
{
	int conn = *(int*)arg;
	char data[BUFFER_LENGTH] = { 0 };
	int recvResult;
	bool isRunning = true;
	int lastBeatTime;
	int i;
	printf("Client[%d]: Create thread successfully.\n", conn);
	while (true)
	{
		memset(data, 0, BUFFER_LENGTH);
		recvResult = recv(conn, data, sizeof(data), 0);
		switch (recvResult)
		{
		case 0:
			printf("Client[%d]: Client has been closed.\n", conn);
			isRunning = false;
			break;
		case -1:
			printf("Client[%d]: Read error!\n", conn);
			isRunning = false;
			break;
		default:
			break;
		}
		if (isRunning == false)
		{
			break;
		}
		else
		{
			if (strcmp(data, "quit") == 0)
			{
				printf("Client[%d]: Client chose to quit the program.\n", conn);
				break;
			}
			else
			{
				if (-1 == analyseMessage(conn, data))
				{
					printf("Client[%d]: Wrong format of request.\n", conn);
				}

			}
		}
	}
	//Clear
	printf("Client[%d]: Terminating.\n", conn);
	pthread_exit(NULL);   //terminate calling thread!
	//clear the clientLst;
	i=0;
	for (vector<Item>::iterator it = clientList.begin(); it != clientList.end(); it++, i++)
	{
		if ((*it).conn == conn)
		{
			clientList.erase(clientList.begin() + i);
		}
	}
}


//analyse the message,decide use which function to use according to the format 
int analyseMessage(int conn, char * data)
{
	//Wrong format
	if(data[0]=='\n'&&data[1]=='\t')
	{

	}
	return 0;
}

int sendMessage(int conn, char * msg)
{

	send(conn,msg,strlen(msg),0);
	//ssize_t send(int sock, const void *buf, size_t len, int flags);
}