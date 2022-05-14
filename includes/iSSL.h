#ifndef _iSSL_h_
#define _iSSL_h_

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include "http.h"

#define CERTF "SSL/server/server-cert.pem"
#define KEYF "SSL/server/server-key.pem"
#define CA "SSL/ca/ca-cert.pem"

SSL_CTX* initSSL(); 
void FreeSSL(SSL*, SSL_CTX*);

#endif