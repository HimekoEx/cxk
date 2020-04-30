#pragma once
#include "src/sdk/Bytes.hpp"

//SDK
namespace MiHoYoSDK
{

    //RSA封装
    class RSACrypto
    {
    private:
        RSA *_public = nullptr;
        RSA *_private = nullptr;

    public:
        RSACrypto(const std::string &publicKey, const std::string &privateKey);
        ~RSACrypto();

        Bytes publicEncrypt(const Bytes &data);
        bool publicVerify(const Bytes &data, const Bytes &sign);

        Bytes privateDecrypt(const Bytes &data);
        Bytes privateSign(const Bytes &data);
    };

} // namespace MiHoYoSDK
