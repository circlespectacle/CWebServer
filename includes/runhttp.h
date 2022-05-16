#ifndef _runhttp_h_
#define _runhttp_h_

#include "http.h"
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#define poolsize 25

pthread_t pool[poolsize];

void runhttpserver();
void listening(int);
void* servering(void *);

#endif