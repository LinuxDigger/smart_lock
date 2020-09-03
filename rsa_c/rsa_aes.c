// openssl versoin
// OpenSSL 1.1.0l  10 Sep 2019

// openssl genrsa -out privateKey.pem 4096
// openssl rsa -in privateKey.pem -pubout > publicKey.pem
// view rsa file info
// openssl rsa -in private.key -text -noout

#include <stdbool.h>
#include <string.h>
#include "rsa_aes.h"

#define RSA_KEY_SIZE (4096/8)
#define AES_BLOCK_SIZE (128/8)

#define ek_size  512
#define iv_size  EVP_MAX_IV_LENGTH

//获取加密结果的长度。
int get_evp_seal_out_size(int in_size) {
    int aes_out_size = in_size + (AES_BLOCK_SIZE - (in_size % AES_BLOCK_SIZE));
    return aes_out_size + ek_size + iv_size;
}
//获取大概的解密结果长度，保证返回的结果大于等于结果的长度。
int get_evp_unseal_safe_out_size(int in_size) {
    return in_size - ek_size - iv_size;
}

/*
ras-aes解密
pkey：公匙
in：输入内容
in_size：输入内容长度
out：输出内容（加密结果）
*/
int do_evp_seal(EVP_PKEY *pkey, unsigned char *in, int in_size,
                unsigned char *out) {
    int retval = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len_out;
    unsigned char *ek;
    int eklen;
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned int out_location = 0;

    EVP_CIPHER_CTX_init(ctx);
    ek = (unsigned char*) malloc(RSA_KEY_SIZE);

    //rsa密匙的长度必须为4096
    //此时eklen=512;不然就会出错。
    //EVP_SealInit会随机生成一个AES密匙和iv数组，其中的ek（长度4096）是使用rsa公匙加密AES密匙过后的结果。
    if (!EVP_SealInit(ctx, EVP_aes_256_cbc(), &ek, &eklen, iv, &pkey, 1)
            || RSA_KEY_SIZE != eklen) {
        retval = 3;
        goto out_free;
    }

    //将AES密匙ek复制入结果数组中
    memcpy((out + out_location), ek, RSA_KEY_SIZE);
    out_location += RSA_KEY_SIZE;
    //将iv复制入结果数组中
    memcpy(out + out_location, iv, EVP_MAX_IV_LENGTH);
    out_location += EVP_MAX_IV_LENGTH;

    //AES加密数据 并将数据直接保存到结果数组中
    if (!EVP_SealUpdate(ctx, out + out_location, &len_out, in, in_size)) {
        retval = 3;
        goto out_free;
    }
    out_location += len_out;

    //AES加密数据 并将数据直接保存到结果数组中
    if (!EVP_SealFinal(ctx, out + out_location, &len_out)) {
        retval = 3;
        goto out_free;
    }
    out_location += len_out;

    //用来验证程序是否出错。
    //已经测试了3596+个文件，没有发现错误。
    if (get_evp_seal_out_size(in_size) != (int) out_location) {
        // Fatal error!
        exit(1111);
    }

out_free: EVP_CIPHER_CTX_free(ctx);
    free(ek);

    return retval;
}

/*
ras-aes解密
pkey：私匙
in：输入内容
in_size：输入内容长度
out：输出内容
out_size：输出内容长度
*/
int do_evp_unseal(EVP_PKEY *pkey, unsigned char *in, int in_size,
                  unsigned char *out, unsigned int *out_size) {
    int retval = 0;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len_out;
    unsigned char *ek;
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned int in_location = 0;
    unsigned int out_location = 0;

    EVP_CIPHER_CTX_init(ctx);
    ek = (unsigned char*) malloc(RSA_KEY_SIZE);

    //读取in中的ek
    memcpy(ek, in + in_location, RSA_KEY_SIZE);
    in_location += RSA_KEY_SIZE;
    //读取in中的iv
    memcpy(iv, in + in_location, EVP_MAX_IV_LENGTH);
    in_location += EVP_MAX_IV_LENGTH;


    //EVP_OpenInit通过私匙解密ek得到AES密匙。
    if (!EVP_OpenInit(ctx, EVP_aes_256_cbc(), ek, RSA_KEY_SIZE, iv, pkey)) {
        ERR_print_errors_fp(stderr);
        retval = 3;
        goto out_free;
    }

    //输入密文，进行解密。解密结果直接保存到out。
    if (!EVP_OpenUpdate(ctx, out + out_location, &len_out, in + in_location,
                        in_size - in_location)) {
        retval = 3;
        goto out_free;
    }
    out_location += len_out;

    //解密。解密结果直接保存到out。
    if (!EVP_OpenFinal(ctx, out + out_location, &len_out)) {
        retval = 3;
        goto out_free;
    }
    out_location += len_out;
    *out_size = out_location;

out_free: EVP_CIPHER_CTX_free(ctx);
    free(ek);

    return retval;
}

//从文件读入公匙
bool get_rsa_pub_key(char *file_name, EVP_PKEY *pkey) {
    RSA *rsa_pkey = NULL;
    FILE *rsa_key_file = fopen(file_name, "rb");
    if (!PEM_read_RSA_PUBKEY(rsa_key_file, &rsa_pkey, NULL, NULL)) {
        return false;
    }
    if (!EVP_PKEY_assign_RSA(pkey, rsa_pkey))
        return false;
    return true;
}

//从文件读入私匙
bool get_rsa_pri_key(char *file_name, EVP_PKEY *pkey) {
    RSA *rsa_pkey = NULL;
    FILE *rsa_key_file = fopen(file_name, "rb");
    if (!PEM_read_RSAPrivateKey(rsa_key_file, &rsa_pkey, NULL, NULL)) {
        return false;
    }
    if (!EVP_PKEY_assign_RSA(pkey, rsa_pkey))
        return false;
    return true;
}
