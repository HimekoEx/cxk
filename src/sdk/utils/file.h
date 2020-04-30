#pragma once
#include "src/sdk/Base.h"

typedef bool (*VerifyCallBack)(const char *, const uint);

//SDK
namespace MiHoYoSDK
{

    // 文件读取
    std::string FileRead(const std::string &path);
    // 文件读取单行
    std::string FileLine(const std::string &path);

    // 文件写出
    void FileWrite(const std::string &src, const std::string &path);

    // 解压APK并且调用回调
    void UncompressAPK(const std::string &path, const std::string &name, VerifyCallBack callBack);

} // namespace MiHoYoSDK
