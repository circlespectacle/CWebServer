#include "runhttps.h"

char sendbuf[MAXN];
char recvbuf[MAXN];
char path[MAXN];
char text[MAXF];

void runhttpsserver() {
    int srv_sock = initSrvSocket(sport);
    listen(srv_sock, 20);
    printf("listening\n");

    int cln_sock = acptClnSocket(srv_sock);
    printf("TCP connected\n");

    SSL_CTX* ctx = initSSL();
    if (ctx == NULL) return ;
    printf("ctx\n");
    SSL* ssl = SSL_new(ctx);
    if (ssl == NULL) return ;
    printf("ssl\n");
    SSL_set_fd(ssl, cln_sock);
    printf("set_fd\n"); 
    SSL_accept(ssl); 
    printf("SSL accepted");

    while (1) {
        SSL_read(ssl, recvbuf, MAXN); 
        //printf("%s\n", recvbuf);
        sendbuf[0] = '\0';

        int leng = responsehttp(recvbuf, sendbuf, text);
        SSL_write(ssl, sendbuf, strlen(sendbuf));
        //printf("%s\n", sendbuf);
        if (leng > 0) {
            SSL_write(ssl, text, leng);
        }
    }

    FreeSSL(ssl, ctx);

    close(cln_sock);
    close(srv_sock); 
}