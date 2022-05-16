#include "runhttp.h"

char sendbuf[MAXN];
char recvbuf[MAXN];
char path[MAXN];
char text[MAXF];

void runhttpserver() {
    int srv_sock = initSrvSocket(lport);
    listening(srv_sock);

    close(srv_sock); 
}

void listening(int srvs) {
    listen(srvs, 20);
    printf("listening\n");

    while (1) {
        int cln_sock = acptClnSocket(srvs);
        int i = 0; 
        printf("bp0\n");
        while (i < poolsize && pthread_create(&pool[i], NULL, servering, (void *) &cln_sock) != 0) {
            printf("%d\n", i);
            i ++;
        }
    }
}

void* servering(void* arg) {
    int cln_sock = *(int *) arg; 
    // printf("bp1\n");

    int cnt = 1; 
    while (cnt) {
        printf("itbegin: %d\n", cnt);
        int rs = read(cln_sock, recvbuf, MAXN); 
        if (rs >= 0) printf("%s\n", recvbuf);
        sendbuf[0] = '\0';

        int leng = responsehttp(recvbuf, sendbuf, text);
        rs = write(cln_sock, sendbuf, strlen(sendbuf));
        if (rs < 0) break ;
        printf("%s\n", sendbuf);
        if (leng > 0) {
            write(cln_sock, text, leng);
        }

        printf("itend: %d\n", cnt);
        cnt ++;

        // sleep(2);
    }

    close(cln_sock);
}