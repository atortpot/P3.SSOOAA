#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 5000
#define BUF_SIZE 128

long factorial(int n){ /* igual */ }

void *handle(void *arg){
    int client = (int)(long)arg;
    char buf[BUF_SIZE];
    ssize_t r = read(client, buf, BUF_SIZE-1);
    /* parsear y calcular */
    write(client, buf, strlen(buf));
    close(client);
    return NULL;
}

int main(void){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { /* igual */ };
    bind(sock,(struct sockaddr*)&addr,sizeof(addr));
    listen(sock,5);
    printf("ServidorHebTCP en puerto %d\n",PORT);

    while (1) {
        int client = accept(sock,NULL,NULL);
        pthread_t t;
        pthread_create(&t, NULL, handle, (void*)(long)client);
        pthread_detach(t);
    }
    return 0;
}

