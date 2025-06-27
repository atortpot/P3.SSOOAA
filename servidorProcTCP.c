#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define BUF_SIZE 128

long factorial(int n){ /* igual que antes */ }

void handle_client(int client){
    char buf[BUF_SIZE];
    ssize_t r = read(client, buf, BUF_SIZE-1);
    /* parsear y calcular idéntico a servidorOpAlgebraicas */
    write(client, buf, strlen(buf));
    close(client);
}

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { /* igual */ };
    bind(sock,(struct sockaddr*)&addr,sizeof(addr));
    listen(sock,5);
    printf("ServidorProcTCP en puerto %d\n",PORT);

    while (1) {
        int client = accept(sock,NULL,NULL);
        if (fork()==0) {
            close(sock);
            handle_client(client);
            _exit(0);
        }
        close(client);
    }
    return 0;
}

