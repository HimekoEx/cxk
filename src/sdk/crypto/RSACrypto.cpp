#include <include/openssl/rsa.h>
#include <include/openssl/pem.h>
#include "src/sdk/MiHoYoSDK.h"

// 构造函数
MiHoYoSDK::RSACrypto::RSACrypto(const std::string &publicKey, const std::string &privateKey)
{
    //加载公匙
    if (!publicKey.empty())
    {
        BIO *bio = NULL;

        if ((bio = BIO_new_mem_buf((void *)publicKey.c_str(), -1)) == NULL)
            RT("RC Error 0x01") && CCC("BIO NULL!");

        if ((_public = PEM_read_bio_RSA_PUBKEY(bio, &_public, NULL, NULL)) == NULL)
            RT("RC Error 0x02") && CCC("PublicRsa NULL!");

        BIO_free(bio);
    }

    //加载私匙
    if (!privateKey.empty())
    {
        BIO *bio = NULL;

        if ((bio = BIO_new_mem_buf((void *)privateKey.c_str(), -1)) == NULL)
            RT("RC Error 0x03") && CCC("BIO NULL!");

        if ((_private = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL)) == NULL)
            RT("RC Error 0x04") && CCC("PrivateRsa NULL!");

        BIO_free(bio);
    }

    //验证
    if (_public == nullptr || _private == nullptr)
        RT("RC Error") && CCC("RSA Init Error!");
}

// 公匙加密
MiHoYoSDK::Bytes MiHoYoSDK::RSACrypto::publicEncrypt(const Bytes &data)
{
    Bytes result;
    int status = 0;                                           //每次加密的长度
    int len = data.length();                                  //数据总长度
    const int key_size = RSA_size(_public);                   //密匙长度
    const int block_size = key_size - RSA_PKCS1_PADDING_SIZE; //分块加密的块大小
    uchar *buff = new uchar[key_size + 1];                    //存储加密的数据
    memset(buff, 0, key_size + 1);

    for (int i = 0; i < len; i += block_size)
    {
        status = RSA_public_encrypt(std::min(block_size, len - i),
                                    (uchar *)&data.c_str()[i], buff, _public, RSA_PKCS1_PADDING);

        if (status < 0)
            RT("PE Error") && CCC("PublicEncrypt status: " + ToString(status));

        result.append((char *)buff, status);
    }

    delete[] buff;
    return result;
}

// 公匙验证
bool MiHoYoSDK::RSACrypto::publicVerify(const Bytes &data, const Bytes &sign)
{
    EVP_MD_CTX *rsa_verify_ctx = EVP_MD_CTX_create();
    EVP_PKEY *pub_key = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pub_key, _public);

    //初始化
    if (EVP_DigestVerifyInit(rsa_verify_ctx, NULL, EVP_sha256(), NULL, pub_key) <= 0)
        return RT("PV Error 0x01") && CCC("VerifyInit Error");

    //写入数据
    if (EVP_DigestVerifyUpdate(rsa_verify_ctx, data.c_str(), data.length()) <= 0)
        return RT("PV Error 0x02") && CCC("VerifyUpdate Error");

    //验证
    if (EVP_DigestVerifyFinal(rsa_verify_ctx, (uchar *)sign.c_str(), sign.length()) <= 0)
        return RT("PV Error 0x03") && CCC("VerifyFinal Error");

    EVP_PKEY_free(pub_key);
    EVP_MD_CTX_destroy(rsa_verify_ctx);
    return false;
}

// 私匙解密
MiHoYoSDK::Bytes MiHoYoSDK::RSACrypto::privateDecrypt(const Bytes &data)
{
    Bytes result;
    int status = 0;
    const int key_size = RSA_size(_private);
    uchar *to = new uchar[key_size + 1];
    memset(to, 0, key_size + 1);

    for (int i = 0; i < data.length(); i += key_size)
    {
        status = RSA_private_decrypt(std::min(key_size, (int)data.length() - i),
                                     (uchar *)&data.c_str()[i], to, _private, RSA_PKCS1_PADDING);

        if (status < 0)
            RT("PD Error") && CCC("PrivateDecrypt status: " + ToString(status));

        result.append((char *)to, status);
    }

    delete[] to;
    return result;
}

// 私匙签名
MiHoYoSDK::Bytes MiHoYoSDK::RSACrypto::privateSign(const Bytes &data)
{
    EVP_MD_CTX *rsa_sign_ctx = EVP_MD_CTX_create();
    EVP_PKEY *pri_key = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pri_key, _private);
    size_t sign_len = 0;

    //初始化
    if (EVP_DigestSignInit(rsa_sign_ctx, NULL, EVP_sha256(), NULL, pri_key) <= 0)
        RT("PS Error 0x01") && CCC("SignInit Error!");

    //写入数据
    if (EVP_DigestSignUpdate(rsa_sign_ctx, data.c_str(), data.length()) <= 0)
        RT("PS Error 0x02") && CCC("SignUpdate Error!");

    //获取长度
    if (EVP_DigestSignFinal(rsa_sign_ctx, NULL, &sign_len) <= 0)
        RT("PS Error 0x03") && CCC("SignLength Error!");

    //创建缓存
    uchar *buff = new uchar[sign_len];
    memset(buff, 0, sign_len);

    //获取数据
    if (EVP_DigestSignFinal(rsa_sign_ctx, buff, &sign_len) <= 0)
        RT("PS Error 0x04") && CCC("SignFinal Error!");

    Bytes result((char *)buff, sign_len);
    delete[] buff;
    EVP_PKEY_free(pri_key);
    EVP_MD_CTX_destroy(rsa_sign_ctx);
    return result;
}
