#include <iostream>
#include <string.h>
#include <pthread.h>
#include "tcp.h"

using namespace std;

int live = 1;

void *ui_thread_func(void *args);
void *listen_thread_func(void *args);

void *handle_message(void * args);

int main(int argc, char *argv[])
{
    int trackerPort = atoi(argv[2]);
    pthread_t ui_thread, listen_thread;

    if(InitClient(argv[1], trackerPort) != true)
    {
        cout << "Error initializing system" << endl;
        return -1;
    }

}

void *ui_thread_func(void *args)
{
    char buffer[MAX_LEN];
    int menu_choice;

    printf("Welcome\n");

    while(live)
    {
        memset(buffer, '\0', MAX_LEN);
        printf("What do you want to do? %s\n%s\n%s",
                "1 - Send test",
                "2 - Exit", 
                "> ");

        scanf("%d", &menu_choice);

        // Flush input buffer
        int c;
        while((c == getchar()) != '\n' && c != EOF) {}

        switch(menu_choice)
        {
            case 1:
                printf("Send test\n");
                break;
            case 2:
                printf("Exiting\n");
                live = 0;
                break;
            default:
                printf("Invalid input");
                break;
        }
    }

    return NULL;
}

void *listen_thread_func(void *args)
{
    int sock;
    sockaddr_in other;
    cout << "Listening for incomming connections..." << endl;
    int c = sizeof(struct sockaddr_in);

    while( live && (sock = accept(getListenSocket(), (struct sockaddr *)&other, (socklen_t*)&c)) )
    {
        pthread_t handleThread;
        int *newSocket = (int *)malloc(sizeof(int));
        *newSocket = sock;

        printf("New Connection\n");

        if(pthread_create(&handleThread, NULL, handle_message, (void *)newSocket) < 0) {
            printf("Cannot creatre thread\n");
        }

    }

    return NULL;

}

void *handle_message(void * args)
{
    int sock = *((int *) args);

    // TODO
    // If from tracker, do one thing
    // else if from another client, handle that transaction

    free(args);

    return NULL;
}
