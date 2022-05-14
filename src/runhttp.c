#include "runhttp.h"

char sendbuf[MAXN];
char recvbuf[MAXN];
char path[MAXN];
char text[MAXF];

void runhttpserver() {
    int srv_sock = initSrvSocket(lport);
    listen(srv_sock, 20);
    printf("listening\n");

    int cln_sock = acptClnSocket(srv_sock);

    while (1) {
        read(cln_sock, recvbuf, MAXN); 
        printf("%s\n", recvbuf);
        sendbuf[0] = '\0';

        int leng = responsehttp(recvbuf, sendbuf, text);
        write(cln_sock, sendbuf, strlen(sendbuf));
        printf("%s\n", sendbuf);
        if (leng > 0) {
            write(cln_sock, text, leng);
        }
    }

    close(cln_sock);

    close(srv_sock); 
}