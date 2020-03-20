#include <include/openssl/aes.h>
#include "src/sdk/MiHoYoSDK.h"

// AES加密
MiHoYoSDK::Bytes MiHoYoSDK::AESEncode(const Bytes &src, const std::string &key)
{
    int block_count = 0;
    int quotient = src.length() / AES_BLOCK_SIZE;
    int mod = src.length() % AES_BLOCK_SIZE;
    block_count = quotient + 1;
    int out_size = AES_BLOCK_SIZE * block_count;

    //填充数据
    int padding = AES_BLOCK_SIZE - mod;
    char *in = new char[out_size];
    memset(in, padding, out_size);
    memcpy(in, src.c_str(), src.length());

    //out
    char *out = new char[out_size];
    memset(out, 0, out_size);

    //初始向量为全0
    uchar iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE);

    //获取密匙
    AES_KEY aes;
    if (AES_set_encrypt_key((uchar *)key.c_str(), key.length() * 8, &aes) < 0)
        RT("AE Error") && CCC("AESEncode Error!");

    //加密
    AES_cbc_encrypt((uchar *)in, (uchar *)out, out_size, &aes, iv, AES_ENCRYPT);

    Bytes result(out, out_size);
    delete[] out;
    delete[] in;
    return result;
}

// AES解密
MiHoYoSDK::Bytes MiHoYoSDK::AESDecode(const Bytes &src, const std::string &key)
{
    //初始向量为全0
    uchar iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE);

    //密匙
    AES_KEY aes;
    if (AES_set_decrypt_key((uchar *)key.c_str(), key.length() * 8, &aes) < 0)
        RT("AD Error") && CCC("AESDecrypt Error!");

    const int src_len = src.length();
    char *tmp = new char[src_len];
    memset(tmp, 0, src_len);
    AES_cbc_encrypt((uchar *)src.c_str(), (uchar *)tmp, src_len, &aes, iv, AES_DECRYPT);

    //PKCS5 UNPADDING
    int unpadding = tmp[src_len - 1];
    int out_len = src_len - unpadding;

    Bytes result(tmp, out_len);
    delete[] tmp;
    return result;
}
