#include <fstream>
#include <sstream>
#include <zip/zip.h>
#include "src/sdk/MiHoYoSDK.h"

// 文件读取
std::string MiHoYoSDK::FileRead(const std::string &path)
{
    std::ifstream fs(path);
    std::stringstream buffer;
    buffer << fs.rdbuf();
    fs.close();
    return buffer.str();
}

// 文件读取单行
std::string MiHoYoSDK::FileLine(const std::string &path)
{
    std::string tmp;
    std::ifstream in(path);
    std::getline(in, tmp, '\n');
    in.close();
    return tmp.substr(0, tmp.find_last_not_of(" \n\r\t") + 1);
}

// 文件写出
void MiHoYoSDK::FileWrite(const std::string &src, const std::string &path)
{
    std::ofstream out(path, std::ios::trunc);
    out << src;
    out.close();
}

//解压APK并且调用回调
void MiHoYoSDK::UncompressAPK(const std::string &path, const std::string &name, VerifyCallBack callBack)
{
    struct zip *apk = nullptr;
    struct zip_stat status;
    struct zip_file *file = nullptr;

    if ((apk = zip_open(path.c_str(), 0, nullptr)) == nullptr)
        RT("UA Error 0x01") && CCC("ZIP open Error!");

    if ((file = zip_fopen(apk, name.c_str(), 0)) == nullptr)
        RT("UA Error 0x02") && CCC("ZIP fopen Error!");

    zip_stat_init(&status);
    zip_stat(apk, name.c_str(), 0, &status);

    char *buffer = new char[status.size];
    zip_fread(file, buffer, status.size);

    if (callBack(buffer, status.size))
        RT("UA Error 0x03") && CCC("CallBack Error!");

    delete[] buffer;
    zip_fclose(file);
    zip_close(apk);
}
