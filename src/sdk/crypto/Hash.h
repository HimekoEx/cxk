#pragma once
#include "src/sdk/Bytes.hpp"

//SDK
namespace MiHoYoSDK
{

    // 解密Ascii
    void DecryptAscii(int data[], const short key);
    // 验证Ascii
    bool CheakAscii(int data[], char src[], const short key);

    // 获取MD5
    Bytes MD5(const Bytes &src, bool notNull = false);

} // namespace MiHoYoSDK
