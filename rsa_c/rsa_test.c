#include "rsa_aes.h"

// 注意：部分函数没有进行错误处理，仅供测试使用。
// 使用方法：./rsa_test publicKey.pem privateKey.pem $file
// 命令行一共有3个参数，第一个为公匙路径，第二个为私匙路径，第三个为需要测试的文件。
int main(int argc, char *argv[]) {

    if (argc < 4) {
        fprintf(stderr,
                "Usage: %s <PEM RSA Public Key File> <PEM RSA Private Key File> <Test File>\n",
                argv[0]);
        exit(1);
    }

    EVP_PKEY *pubkey = EVP_PKEY_new();
    EVP_PKEY *prikey = EVP_PKEY_new();
    if (!get_rsa_pub_key(argv[1], pubkey)) return -1;
    if (!get_rsa_pri_key(argv[2], prikey)) return -1;

    FILE *fp = fopen(argv[3], "rb");
    fseek(fp, 0L, SEEK_END);
    unsigned sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    unsigned char *data = (unsigned char*) malloc(sz);
    fread(data, 1, sz, fp);

    int seal_out_size = get_evp_seal_out_size(sz);
    unsigned int unseal_out_size = get_evp_unseal_safe_out_size(seal_out_size);
    unsigned char *seal_out = (unsigned char*) malloc(seal_out_size);
    unsigned char *unseal_out = (unsigned char*) malloc(unseal_out_size);

    //进行加密
    //输入原始数据data，和公匙pubkey，得到加密结果seal_out
    do_evp_seal(pubkey, data, sz, seal_out);
    //进行解密
    //输入加密数据seal_out，和私匙prikey，得到解密结果unseal_out和解密结果长度unseal_out_size
    do_evp_unseal(prikey, seal_out, seal_out_size, unseal_out, &unseal_out_size);

    //将解密结果输出到命令行
    fwrite(unseal_out, 1, unseal_out_size, stdout);

    //将解密结果输出到文件
    // FILE *fp0 = fopen("encrypted_output", "wb");
    // fwrite(seal_out, 1, seal_out_size, fp0);
    // fclose(fp0);

    EVP_PKEY_free(pubkey);
    EVP_PKEY_free(prikey);

    return 0;
}

