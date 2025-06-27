#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr,"Uso: %s \"OPER ACC1 [ACC2]\"\n",argv[0]);
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(PORT),
        .sin_addr.s_addr = htonl(0x7F000001)
    };
    connect(sock,(void*)&addr,sizeof(addr));
    write(sock, argv[1], strlen(argv[1]));
    char buf[128]; int r = read(sock, buf, 127);
    if (r>0) {
        buf[r]=0;
        printf("Respuesta: %s", buf);
    }
    close(sock);
    return 0;
}

