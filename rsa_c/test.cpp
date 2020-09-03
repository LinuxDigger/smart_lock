#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include<fcntl.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
using namespace std;
//类型宏定义


// #4096算是非常强的密匙长度了，目前我们就用4096。如果需要超级安全我们再用12288
// #linux命令行生成rsa密匙
// openssl genrsa -out privateKey.pem 4096
// openssl rsa -in privateKey.pem -pubout > publicKey.pem

#define PUBLICKEY "./publicKey.pem"
#define PRIVATEKEY "./privateKey.pem"

#define PASS "8888" //口令

typedef unsigned char     uint8;
typedef unsigned long    uint32;

//定义编码字典
static uint8 alphabet_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//定义解码字典
static uint8 reverse_map[] =
{
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255, 255, 255, 255, 255,
    255,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255,
    255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 255, 255, 255, 255, 255
};

/*
*  编码
*     传入需要编码的数据地址和数据长度
*  返回:解码后的数据
*/
uint8* base64_encode(const uint8 *text, uint32 text_len)
{
    //计算解码后的数据长度
    //由以上可知  Base64就是将3个字节的数据(24位)，拆成4个6位的数据，然后前两位补零
    //将其转化为0-63的数据  然后根据编码字典进行编码
    int encode_length = text_len / 3 * 4;
    if (text_len % 3 > 0)
    {
        encode_length += 4;
    }

    //为编码后数据存放地址申请内存
    uint8 *encode = (uint8*)malloc(encode_length);

    //编码
    uint32 i, j;
    for (i = 0, j = 0; i + 3 <= text_len; i += 3)
    {
        encode[j++] = alphabet_map[text[i] >> 2];                           //取出第一个字符的前6位并找出对应的结果字符
        encode[j++] = alphabet_map[((text[i] << 4) & 0x30) | (text[i + 1] >> 4)]; //将第一个字符的后2位与第二个字符的前4位进行组合并找到对应的结果字符
        encode[j++] = alphabet_map[((text[i + 1] << 2) & 0x3c) | (text[i + 2] >> 6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        encode[j++] = alphabet_map[text[i + 2] & 0x3f];                     //取出第三个字符的后6位并找出结果字符
    }

    /*for (int l = 0; l < j; l++) {
        printf("%c", encode[l]);
    }
    printf("\n");*/

    //对于最后不够3个字节的  进行填充
    if (i < text_len)
    {
        uint32 tail = text_len - i;
        if (tail == 1)
        {
            encode[j++] = alphabet_map[text[i] >> 2];
            encode[j++] = alphabet_map[(text[i] << 4) & 0x30];
            encode[j++] = '=';
            encode[j++] = '=';
        }
        else //tail==2
        {
            encode[j++] = alphabet_map[text[i] >> 2];
            encode[j++] = alphabet_map[((text[i] << 4) & 0x30) | (text[i + 1] >> 4)];
            encode[j++] = alphabet_map[(text[i + 1] << 2) & 0x3c];
            encode[j++] = '=';
        }
    }
    encode[j++] = '\0';
    /*printf("debug\n");
    for (int l = 0; l < j; l++) {
        printf("%c", encode[l]);
    }
    printf("\ndebug\n");*/
    return encode;
}



uint8* base64_decode(const uint8 *code, uint32 code_len)
{
    //由编码处可知，编码后的base64数据一定是4的倍数个字节
    assert((code_len & 0x03) == 0); //如果它的条件返回错误，则终止程序执行。4的倍数。

    //为解码后的数据地址申请内存
    uint8 *plain = (uint8*)malloc(code_len / 4 * 3);

    //开始解码
    uint32 i, j = 0;
    uint8 quad[4];
    for (i = 0; i < code_len; i += 4)
    {
        for (uint32 k = 0; k < 4; k++)
        {
            quad[k] = reverse_map[code[i + k]]; //分组，每组四个分别依次转换为base64表内的十进制数
        }

        assert(quad[0] < 64 && quad[1] < 64);

        plain[j++] = (quad[0] << 2) | (quad[1] >> 4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的前2位进行组合

        if (quad[2] >= 64)
            break;
        else if (quad[3] >= 64)
        {
            plain[j++] = (quad[1] << 4) | (quad[2] >> 2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应base64表的十进制数的前4位进行组合
            break;
        }
        else
        {
            plain[j++] = (quad[1] << 4) | (quad[2] >> 2);
            plain[j++] = (quad[2] << 6) | quad[3]; //取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
        }
    }
    return plain;
}



int main(int argc, char const *argv[])
{
    /* code */
    //unsigned char * ch = (unsigned char *)
    //string str = "0010111000100100010011001001011010011010010100100111011011110110111110101110100111010111110101111000110001001110000111000100010100010010000110010001110000001001100100100001000001110110100100010101101101001001111110100011000111001111111011010101100001101110010111000100001111011011000111001010000010001110111000000010110001001001111000011001001101110100000011100000000100110000111001000101011011011010001001000000100111010110001000010111001001011011110010010110011001101001100111001000001001100001101000100011110010001001111101011000010011010011001100011101111011010010111110100010001010101010111000010111101001011010001110101001001010010110011110011100110011001101100101100100101010001101001111000010110000010101101110010110010000011111110010101110110101110010000111001000100010001010111010010001000100110111101101100001000110010000110101101010100100000011000000111110000001001011001001011011101010000000100000100100001111001101111111011011011001100011111111000100001100011111001010100011011001001110011100111010110110011100";

    //这里对的，是8*1024位
    //注意一个char是8位二进制
    unsigned char * ch = (unsigned char *)malloc(1024 * sizeof(unsigned char));
    srand((unsigned)time(NULL));
    for (int i = 0; i < 1024; i++) {
        //这里不对了，你生成的是像001011100010010001这样的一个字符串。
        //这样的话，每一位ch要么是48（二进制:0110000)（ascii）要么是49（二进制:0110001),
        //只有最后一位在变化，其他位都未改变，随机性就小了。
        // ch[i] = (unsigned char)(rand() % (1 - 0 + 1) + 0) + '0';
        //应该这样。
        //这样的话它就是每一位ch就是0~256(二进制:00000000~11111111)每一位都有取0、1的可能;
        ch[i] = (unsigned char)(rand() % 256);
        //ch[i] = str[i];
    }
    string credit = "./credit";

    unsigned char* encodeData = base64_encode((unsigned char*)ch, 1024);
    string data = (char*)encodeData;
    int fout = open(credit.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fout > 0) {
        //cout << "yes" << endl;
        //这里存储的credit是base64编码的二进制
        // write(fout, (unsigned char*)data.c_str(), data.length());
        //其实可以不用base64编码存储，直接存储为二进制。
        //此时存储的credit刚好1kB 1k*8bits=1024*8位
        write(fout, ch, 1024);
    }
    close(fout);
    //string data = "";
    //int sum = 0;
    /*for (int i = 0; encodeData[i] != '\0'; i++) {
        //data += (char)encodeData[i];
        printf("%c", encodeData[i]);
        sum ++;
    }*/
    //cout << "sum is " << sum << endl;
    //data.pop_back();
    //data.pop_back();
    //write(fout, (unsigned char*)data.c_str(), data.length());
    //cout << data.size() << endl;
    cout << "<<凭证已生成并存放到credit文件中>>" << endl << "凭证的base64编码如下:" << endl;
    //cout << "data is " << endl << data << endl;
    cout << "base64 encode is " << endl;
    for (int i = 0; i < 1024; i++) {
        printf("%c", encodeData[i]);
    }
    unsigned char* decode = base64_decode((unsigned char*)data.c_str(), (int)data.length());
    return 0;
}
