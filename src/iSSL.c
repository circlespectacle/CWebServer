#include "iSSL.h"

SSL_CTX* initSSL() {
    SSL_library_init();
    SSL_load_error_strings();

    SSL_CTX *ctx = SSL_CTX_new(TLSv1_2_server_method()); 

    SSL_CTX_load_verify_locations(ctx, CA, NULL);

    if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0)
        return NULL; 
    if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0)
        return NULL; 
    if (!SSL_CTX_check_private_key(ctx)) 
        return NULL; 
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY); 
    return ctx;
} 

void FreeSSL(SSL* ssl, SSL_CTX* ctx) {
    if (!ssl) {
        SSL_shutdown(ssl); 
        SSL_free(ssl); 
        ssl = NULL;
    } 

    if (!ctx) {
        SSL_CTX_free(ctx);
        ctx = NULL;
    }
}