/**
 * tcp.cpp
 * Project 3 - Simple xFS
 * Aparna Mahadevan
 * Ming-Hong Yang
 * Eric Kuha
 */

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "tcp.h"

using namespace std;

int getTrackerSocket()
{
    return gTrackerSock;
}

int getListenSocket()
{
    return gListenSock;
}

bool InitClient(char *address, int port) 
{
    int listenSock, trackerSock;

    listenSock = initListenSocket(0);
    trackerSock = initTrackerSocket(address, port);

    gTrackerSock = trackerSock;
    gListenSock = listenSock;

    return true;
}

int InitTracker(int port)
{

}

int initTrackerSocket(char *address, int port) 
{
    int sock = 0;
    struct sockaddr_in tracker_addr;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1)
    {
        printf("Could not create tracker socket\n");
        return -1;
    }
    printf("Created Tracker Socket\n");

    tracker_addr.sin_family = AF_INET;
    tracker_addr.sin_addr.s_addr = inet_addr(address);
    tracker_addr.sin_port = htons(port);

    if(connect(sock, (struct sockaddr *)&tracker_addr, sizeof(tracker_addr)) < 0 )
    {
        printf("Connection failed%s\n", strerror(errno));
        return -1;
    }
    return sock;
}

int initListenSocket(int port)
{
    int listenSocket = 0;
    struct sockaddr_in listen_addr;

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == -1)
    {
        printf("Could not create listen socket\n");
    }
    printf("Created Listen Socket\n");

    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(port);

    if( bind(listenSocket, (struct sockaddr *)&tracker_addr, sizeof(tracker_addr)) < 0)
    {
        perror("bind failed. Error.");
        return 1;
    }
    printf("tracker socket bound\n");

    listen(listenSocket, 10);

    return listenSocket;
}

void sendACK(int socket)
{
    SendThroughSocket(socket, "ACK;", strlen("ACK;"));
}

bool SendThroughSocket(int socket, char *buffer, int len)
{
    int ret = 0;

    ret = send(socket, buffer, len, 0);

    if(len == ret) {
        return true;
    } else if (ret == -1) {
        printf("Send error\n");
        return false;
    } else {
        // Not sure how this would happen
        return false;
    }

}

int RecvFromSocket(int socket, char *buffer)
{
    return recv(socket, buffer, MAX_LEN, 0);

}

