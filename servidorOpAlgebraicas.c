#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define BUF_SIZE 128

long factorial(int n) {
    long f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)
    };
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    printf("Servidor aritmético escuchando en puerto %d\n", PORT);

    char buf[BUF_SIZE];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (1) {
        int client = accept(sock, (struct sockaddr*)&client_addr, &client_len);
        ssize_t r = read(client, buf, BUF_SIZE-1);
        if (r <= 0) { close(client); continue; }
        buf[r] = '\0';

        char op[16];
        long a, b, res;
        if (sscanf(buf, "%15s %ld %ld", op, &a, &b) >= 2) {
            if      (strcasecmp(op,"SUMA")==0)       res = a + b;
            else if (strcasecmp(op,"RESTA")==0)      res = a - b;
            else if (strcasecmp(op,"MULT")==0 
                  || strcasecmp(op,"MUL")==0)      res = a * b;
            else if (strcasecmp(op,"DIV")==0)        res = (b!=0? a/b: 0);
            else if (strcasecmp(op,"FACTORIAL")==0)  res = factorial(a);
            else {
                write(client,"OPERACION NO SOPORTADA\n",22);
                close(client);
                continue;
            }
            snprintf(buf, BUF_SIZE, "%ld\n", res);
        } else {
            strcpy(buf,"FORMATO INVALIDO\n");
        }

        write(client, buf, strlen(buf));
        close(client);
    }
    close(sock);
    return 0;
}

