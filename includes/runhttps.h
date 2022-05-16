#ifndef _runhttps_h_
#define _runhttps_h_

#include "http.h"
#include "iSSL.h"
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#define spoolsize 25

pthread_t spool[spoolsize];

void runhttpsserver();
void slistening(int, SSL_CTX *);
void* sservering(void *);

#endif