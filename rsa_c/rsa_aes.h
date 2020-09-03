#ifndef RSA_AES_H
#define RSA_AES_H

#include <stdbool.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

int get_evp_seal_out_size(int in_size);
int get_evp_unseal_safe_out_size(int in_size) ;
int do_evp_seal(EVP_PKEY *pkey, unsigned char *in, int in_size,
                unsigned char *out) ;
int do_evp_unseal(EVP_PKEY *pkey, unsigned char *in, int in_size,
                  unsigned char *out, unsigned int *out_size);
bool get_rsa_pub_key(char *file_name, EVP_PKEY *pkey);
bool get_rsa_pri_key(char *file_name, EVP_PKEY *pkey);

#endif