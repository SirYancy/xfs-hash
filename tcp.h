/**
 * tcp.h
 * Project 3 - Simple xFS
 * Aparna Mahadevan
 * Ming-Hong Yang
 * Eric Kuha
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_CONNECTION 10
#define MAX_LEN 1024

extern int gTrackerSock;
extern int gListenSock;

int getTrackerSocket();
int getListenSocket();

int InitClient(char *address, int port);
int InitTracker(int port);

void sendACK(int socket);

bool SendThroughSocket(int socket, char *buffer, int len);
int RecvFromSocket(int socket, char *buffer);
