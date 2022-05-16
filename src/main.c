/*
#include "global.h"
#include "tcp.h"
#include "fileholder.h"
#include "http.h"
#include "iSSL.h"
*/
#include "runhttp.h"
#include "runhttps.h"

void disconnect_occurred() {
    printf("A service has done.\n");
}

int main() {
    //signal(SIGINT, disconnect_occurred());
    signal(SIGPIPE, disconnect_occurred);

    int pid = fork();
    if (pid) runhttpserver();
    else runhttpsserver();


    return 0; 
}