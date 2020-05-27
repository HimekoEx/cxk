#include <include/openssl/md5.h>
#include "src/sdk/MiHoYoSDK.h"

// 解密Ascii
void MiHoYoSDK::DecryptAscii(int data[], const short key)
{
    for (int i = 0; i < 64; ++i)
        data[i] ^= key;
}

// 验证Ascii
bool MiHoYoSDK::CheakAscii(int data[], char src[], const short key)
{
    for (int i = 0; i < 64; ++i)
        if (src[i] != (char)((data[i] ^ key) >> 2))
            return RT("CA Error") && CCC("CA Error");
        else
            data[i] = src[i] = 0xff;
    return false;
}

// 获取MD5
MiHoYoSDK::Bytes MiHoYoSDK::MD5(const Bytes &src, bool notNull)
{
    if (notNull)
        if (src.length() <= 0)
            RT("MD Error") && CCC("MD5 Src Null Error");

    char hex[33] = "";
    uchar digest[MD5_DIGEST_LENGTH];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, src.c_str(), src.length());
    MD5_Final(digest, &ctx);

    memset(hex, 0, sizeof(hex));
    for (int i = 0; i != sizeof(digest); i++)
        snprintf(hex + (i * 2), 3, GET_SAFE_CHAR(StaticData::STR_md5Format), digest[i]);
    hex[32] = '\0';

    return Bytes(hex, 32);
}
