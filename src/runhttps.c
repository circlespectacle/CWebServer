#include "runhttps.h"

char sendbuf[MAXN];
char recvbuf[MAXN];
char path[MAXN];
char text[MAXF];

void runhttpsserver() {
    SSL_CTX* ctx = initSSL();
    if (ctx == NULL) return ;
    printf("ctx\n");

    int srv_sock = initSrvSocket(sport);
    slistening(srv_sock, ctx);

    FreeSSL(NULL, ctx);

    close(srv_sock); 
}

void slistening(int srvs, SSL_CTX *ctx) {
    listen(srvs, 20);
    printf("listening\n");

    while (1) {
        int cln_sock = acptClnSocket(srvs);
        //printf("TCP connected\n");

        SSL* ssl = SSL_new(ctx);
        if (ssl == NULL) return ;
        //printf("ssl\n");
        SSL_set_fd(ssl, cln_sock);
        //printf("set_fd\n"); 
        SSL_accept(ssl); 
        //printf("SSL accepted");
        int i = 0; 
        while (i < spoolsize && pthread_create(&spool[i], NULL, sservering, (void *) ssl)) i ++;
    }
}

void *sservering(void *arg) {
    SSL *ssl = (SSL *) arg;
    int cnt = 1; 
    while (cnt) {
        printf("sitb: %d\n", cnt); 
        SSL_read(ssl, recvbuf, MAXN); 
        //printf("%s\n", recvbuf);
        sendbuf[0] = '\0';

        int leng = responsehttp(recvbuf, sendbuf, text);
        int rs = SSL_write(ssl, sendbuf, strlen(sendbuf));
        //printf("%s\n", sendbuf);
        if (rs < 0) break ;
        if (leng > 0) {
            SSL_write(ssl, text, leng);
        }
        printf("sitb: %d\n", cnt);
        cnt ++;
    }

    FreeSSL(ssl, NULL);
}