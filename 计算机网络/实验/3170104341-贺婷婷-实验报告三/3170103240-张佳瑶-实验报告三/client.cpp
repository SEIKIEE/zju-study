/*
 * welcome.cpp
 *
 *  Created on: 2019年10月21日
 *      Author: zjy
 */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_MEMBER 100
#define NAME_LENGTH 13
#define IP_LENGTH 20
#define PORT_LENGTH 5

void initialize();
bool startConnect();
bool quitConnect();
void *receiveMsg(void *);
void interpretMsg(char *recv);

bool quit = false;

int serverSocketFD = -1; //socket handle


void initialize()
{
    printf("+----------------------------------------------+\n");
    printf(" Welcome, honey!\n");
    printf("+-------+--------------------------------------+\n");
    printf("| Input |               Function               |\n");
    printf("+-------+--------------------------------------+\n");
    printf("|  :c   |  Connect to a server.                |\n");
    printf("|  :d   |  Disconnect from the server.         |\n");
    printf("|  :t   |  Get the current time on the server. |\n");
    printf("|  :n   |  Get who am I.                       |\n");
    printf("|  :l   |  List and update users on the server.|\n");
    printf("|  :m   |  Send a message to a specified user. |\n");
    printf("|  :q   |  Disconnect and quit.                |\n");
    printf("+-------+--------------------------------------+\n");
}

int main()
{
    bool state = false;
    char instruction[3];
    char name[NAME_LENGTH];
    initialize();
    while (true)
    {
        scanf("%s", instruction);
        if (instruction[0] != ':')
        {
            printf("Instruction format error\n");
            continue;
        }
        //on the unconnected state, only connect and quit can be choosed.
        if (!state)
        {
            switch (instruction[1])
            {
            case 'c':
                state = startConnect();
                break;
            case 'q':
                quit = true;
                printf("Client server quit...\n");
                pthread_exit(NULL);
            default:
                printf("Can't choice before connect!\n");
                break;
            }
        }
        else
        {
            char msg[BUFFER_SIZE] = {0};
            switch (instruction[1])
            {
            case 'c':
                state = startConnect();
                sprintf(msg, "::");
                break;
            case 'd':
                state = quitConnect();
                sprintf(msg, "::");
                break;
            case 't':
                sprintf(msg, ":t");
                break;
            case 'n':
                sprintf(msg, ":n");
                break;
            case 'l':
                sprintf(msg, ":c");
                break;
            case 'm':
                char recvConn[BUFFER_SIZE];
                char sendMessage[BUFFER_SIZE];

                printf("Enter receiver's conn:");
                scanf("%s", recvConn);
                printf("Enter send message:");
				scanf("%s", sendMessage);
				sprintf(msg, ":m %s %s", recvConn, sendMessage);
                break;
            case 'q':
                state = quitConnect(); //close socket
                quit = true;           //quit receive thread
                pthread_exit(NULL);    //quit send thread
            default:
                sprintf(msg, "::");
                break;
            }
            if (send(serverSocketFD, msg, BUFFER_SIZE, 0) == -1)
                printf("Send fail");
        }
    }
}

bool startConnect()
{
    char IP[IP_LENGTH];
    int port; //last four number of student ID card

    struct sockaddr_in serverAddr; //server address
    serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr,0,sizeof(serverAddr));
    printf("Enter IP address:\n");
    scanf("%s", IP);
    printf("Enter port number:\n");
    scanf("%d", &port);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET,IP, &serverAddr.sin_addr);
    //call connect function (socket, servaddr, addrlen)
    if(-1==connect(serverSocketFD, (struct sockaddr *)&serverAddr, sizeof(serverAddr)))
    {
        printf("Fail\n");
        return false;
    }
    pthread_t recvThread;
    printf("connect successful\n");
    pthread_create(&recvThread, NULL, receiveMsg, NULL); //create a receive thread for receive message
    return true;
}

bool quitConnect()
{
    //there no connect
    if (serverSocketFD < 0)
    {
        printf("No connect\n");
        return false;
    }
    close(serverSocketFD);
    printf("Connect closed\n");
    return false;
}

void *receiveMsg(void *)
{
    char msg[BUFFER_SIZE];
    int strLen;

    while (true)
    {
        if (quit)
        {
            printf("Message receive thread quit...\n");
            pthread_exit(NULL);
        }
        else
        {
            //deal with the message
            strLen = recv(serverSocketFD, msg, BUFFER_SIZE, 0);
            msg[strLen] = 0;
            interpretMsg(msg);
        }
    }
    return NULL;
}

void interpretMsg(char *recv)
{
    if (!recv || recv[0] != ':' || recv[1] == '\0' || recv[1] == '\n')
    {
        return;
    }
    switch (recv[1])
    {
    case 't':
        printf("Server Time: %s", recv + 3);
        break;
    case 'n':
        printf("Host Name: %s", recv + 3);
        break;
    case 'c':
    {
        //"%4d|%10s|%4d;" 4+1+10+1+4+; = 20
        printf("conn     ip     port\n");
        for (int i = 3; i < strlen(recv); i++)
        {
            if (recv[i] == '|')
                printf(" ");
            else if (recv[i] == ';')
                printf("\n");
            else
                printf("%c", recv[i]);
        }
        break;
    }
    case 'm':
        printf("Message: %s\n", recv + 3);
        break;
    default:
        break;
    }
}
