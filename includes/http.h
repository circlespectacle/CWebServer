#ifndef _http_h_
#define _http_h_

#include "tcp.h"
#include "fileholder.h"
#include "stdlib.h"
#include "global.h"
#include <string.h>

typedef enum http_status {
    S_200,
    E_400,
    E_404,
    E_500,
    E_501
} http_status;

int responsehttp(char *, char *, char *);
void setheader(http_status, char *, char *);
void setfilecontext(char *, char *);

#endif