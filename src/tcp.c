#include "tcp.h"

int initSrvSocket(int pt) {
    int srv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in srv_addr; 
    memset(&srv_addr, 0, sizeof(srv_addr));  
    srv_addr.sin_family = AF_INET;  
    srv_addr.sin_addr.s_addr = inet_addr(lhost);  
    srv_addr.sin_port = htons(pt);  
    bind(srv_sock, (struct sockaddr*)&srv_addr, sizeof(srv_addr));

    return srv_sock;
}

int acptClnSocket(int srv_sock) {
    struct sockaddr_in cln_addr; 
    socklen_t cln_addr_size = sizeof(cln_addr);
    int cln_sock = accept(srv_sock, (struct sockaddr*) &cln_addr, &cln_addr_size); 
    
    return cln_sock;
}