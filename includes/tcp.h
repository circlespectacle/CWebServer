#ifndef _tcp_h_
#define _tcp_h_

#include "global.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define lhost "127.0.0.1"
#define lport 8090
#define sport 9080

int initSrvSocket(int); 
int acptClnSocket(int); 

#endif