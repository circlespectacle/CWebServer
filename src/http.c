#include "http.h"

int responsehttp(char *req, char *hdr, char *ctxt) {
    char arg[2][45];
    char tmp[45]; tmp[0] = 0;
    sscanf(req, "%s %s", arg[0], arg[1]);
    if (strcmp(arg[1], "/") == 0) strcat(arg[1], "index.html");
    strcat(tmp, FILEDIR); strcat(tmp, arg[1]);
    arg[1][0] = 0; strcat(arg[1], tmp);

    if (strcmp(arg[0], "GET") == 0) {
        int len = getfilelen(arg[1]); 
        if (getfilelen(arg[1]) < 0) setheader(E_404, hdr, NULL);
        else {
            setheader(S_200, hdr, arg[1]); 
            setfilecontext(arg[1], ctxt);
        }
        return len; 
    } else {
        setheader(E_500, hdr, NULL);
    }
    return -1;
}

void setheader(http_status st, char *hdr, char *path) {
    hdr[0] = 0; 
    if (st == S_200) {
        strcat(hdr, "HTTP/1.1 200 OK\r\n");
        strcat(hdr, "Server: C http server 1.0\r\n");
        strcat(hdr, "Connection: keep-alive\r\n");
        strcat(hdr, "Content-Type: text/html\r\n");
        
        char tmp[50];
        sprintf(tmp, "Content-Length: %d\r\n", getfilelen(path)); 
        strcat(hdr, tmp);
        strcat(hdr, "\r\n");
    } else if (st == E_404) {
        strcat(hdr, "HTTP/1.1 404 NOT FOUND\r\n");
        strcat(hdr, "\r\n");
    } else if (st == E_501) {
        strcat(hdr, "HTTP/1.1 500 Internal Server Error\r\n");
        strcat(hdr, "\r\n");
    } else ;
}

void setfilecontext(char *path, char *buf) {
    // printf("%s\n", path);
    buf[0] = 0;
    int len = getfilelen(path);
    read_file(path, buf, len);
}