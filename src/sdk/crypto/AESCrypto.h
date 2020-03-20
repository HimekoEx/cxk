#pragma once
#include "src/sdk/Bytes.hpp"

//SDK
namespace MiHoYoSDK
{

// AES加密
Bytes AESEncode(const Bytes &src, const std::string &key);
// AES解密
Bytes AESDecode(const Bytes &src, const std::string &key);

}
