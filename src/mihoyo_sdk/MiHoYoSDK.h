#pragma once
#include <global_fix.h>

//NDK
#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>

//System
#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/syscall.h>

//Network
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if.h>

//OpenSSL
#include <include/openssl/ossl_typ.h>

//Json
#include <include/json/json.h>

//logcat
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "wdnmd", __VA_ARGS__)
//Bool 转 char*
#define BoolToChar(value) (value ? "true" : "false")
//Bytes追加std::string
#define BytesAppendString(name) name.c_str(), name.length()
//其他数据转std::string
#define ToString(data) std::to_string(data)

//类型定义
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef bool (*verifyCallBack)(const char *, const uint);

//SDK
namespace MiHoYoSDK
{

//安全的字符串类型
class SafeChars
{
private:
    static const short key;
    int *crypto_asciis = nullptr;
    uint Length = 0;

public:
    SafeChars(const int data[], uint size)
    {
        this->Length = size / sizeof(int);
        this->crypto_asciis = (int *)malloc(size);
        memcpy(this->crypto_asciis, data, size);
    }

    //string字符串
    std::string get() const
    {
        char buffer[Length + 1];
        memset(buffer, 0, Length + 1);
        for (int i = 0; i < Length + 1; ++i)
            buffer[i] = (crypto_asciis[i] ^ key) >> 2;
        buffer[Length] = '\0';

        return std::string(buffer, Length);
    }

    //获取长度
    uint length() const
    {
        return Length;
    }

    ~SafeChars()
    {
        free(crypto_asciis);
    }
};

//字节封装
class Bytes
{
private:
    char *Data = nullptr;
    uint Length = 0;
    uint Size = 0;

    void init(const char *src, uint length)
    {
        if (Data)
            free(Data);
        this->Length = length;
        this->Size = length + 1;
        this->Data = (char *)malloc(Size);
        memcpy(this->Data, src, Size);
    }

public:
    Bytes() {}
    Bytes(const char *src) { init(src, strlen(src)); }
    Bytes(const char *src, uint length) { init(src, length); }
    Bytes(const std::string &src) { init(src.c_str(), src.length()); }
    // Bytes(const Bytes &src) { init(src.Data, src.Length); }

    const char *c_str() const { return Data; }
    const uint length() const { return Length; }

    Bytes &append(const char *src, uint length)
    {
        uint new_size = length + (Size ? Size : 1);

        Data = (char *)realloc(Data, new_size);
        memcpy(Data + Length, src, length + 1);
        this->Size = new_size;
        this->Length = Length + length;

        return *this;
    }

    Bytes &append(const Bytes &src) { return append(src.Data, src.Length); }

    const int find(const Bytes &src)
    {
        int index = -1;
        for (int i = 0; i < this->Length; ++i)
        {
            for (int j = 0; j < src.Length; ++j)
            {
                index = i;
                int tmp = i + j;
                if (tmp > this->Length)
                    return -1;

                if (src.Data[j] != this->Data[tmp])
                    break;

                if (j == src.Length - 1)
                    return index;
            }
            index = -1;
        }
        return index;
    }

    Bytes &operator=(const Bytes &src)
    {
        if (this == &src)
            return *this;

        if (this->Data)
            free(this->Data);

        this->Length = src.Length;
        this->Size = src.Size;
        this->Data = (char *)malloc(Size);
        memcpy(this->Data, src.Data, Size);
        return *this;
    }

    bool operator==(const Bytes &src) const
    {
        if (!this->Data || !src.Data)
            return false;
        if (this->Length != src.Length)
            return false;

        for (uint i = 0; i < this->Length; i++)
        {
            if (this->Data[i] != src.Data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Bytes &src) const
    {
        return !this->operator==(src);
    }

    std::string get()
    {
        if (Data)
            return std::string(Data, Length);
        return std::string("(null)");
    }

    ~Bytes()
    {
        if (Data)
            free(Data);
    }
};

//RSA封装
class RSACrypto
{
private:
    RSA *PublicRsa = nullptr;
    RSA *PrivateRsa = nullptr;

public:
    RSACrypto(const std::string &publicKey, const std::string &privateKey);
    Bytes publicEncrypt(const Bytes &data);
    bool publicVerify(const Bytes &data, const Bytes &sign);

    Bytes privateDecrypt(const Bytes &data);
    Bytes privateSign(const Bytes &data);
};

//全局JavaVM
extern JavaVM *Jvm;
//全局app路径
extern std::string AppPath;
//客户端套接字文件描述符
extern int Client;
//读到空数据次数
extern uint ReadNullDataTimes;
//同步锁
extern bool SyncLock;
//循环次数
extern uint Times;
//日志文件输出流
extern std::ofstream *RunTimeStream;
//全局RSA
extern RSACrypto *Rsa;

//获取模块基址
ulong GetModuleBaseAdderss(const char *module_name);
//子串删除
std::string &DeleteAllMark(std::string &src, const std::string &mark);
//子串替换
std::string &ReplaceAll(std::string &src, const std::string &from, const std::string &to);
//读取文件到字符串
std::string ReadFile(const std::string &path);
//读取文件到字符串(单行)
std::string ReadFileLine(const std::string &path);
//写出到文件
void WriteFile(const std::string &src, const std::string &path);
//获取当前时间(毫秒级)
const std::string NowTime();
//获取JINEnv
JNIEnv *EnsureEnvCreated();
//关闭ChaosCore1
bool CloseChaosCore1(std::string msg = "");
//关闭ChaosCore2
bool CloseChaosCore2();

//解压APK并且调用回调
void UncompressApk(const std::string &path, const std::string &name, verifyCallBack callBack);
//解密Ascii
void DecryptAscii(int data[], const short key);
//验证Ascii
void CheakAscii(int data[], char src[], const short key);
//获取MD5
Bytes MD5(const Bytes &src, bool notNull = false);
//AES加密
Bytes AESEncode(const Bytes &src, const std::string &key);
//AES解密
Bytes AESDecode(const Bytes &src, const std::string &key);
//Base64加密
Bytes Base64Encode(const Bytes &src);
//Base64解密
Bytes Base64Decode(const Bytes &src);

//连接服务器
void LinkServer(const uint channelID, void (*initCallback)(const Bytes &src));
//发送并接收数据
Bytes SendMsg(const Bytes &msg);
//双向验证的发送接收数据
Bytes SendMsgEX(const Bytes &send_msg);
//JSON格式收发数据
Bytes SendJSON(const char *send_msg, const Json::Value &send_data);

//初始化运行日志
void RunTimeInit();

//写入运行日志
bool RunTimeLog(const char *msg);
bool RunTimeLog(const Bytes &msg);
bool RunTimeLog(const std::string &msg);

//内存读取
template <class T1, class T2>
T1 MemoryRead(T2 addr, uint off);

} // namespace MiHoYoSDK

//关闭ChaosCore2
inline bool MiHoYoSDK::CloseChaosCore2()
{
    int *p = nullptr;
    *p = 0x92D9;
    pid_t pid = syscall(__NR_getpid);
    kill(pid, SIGKILL);
    _exit(0);
    return true;
}

//写入运行日志 char*
inline bool MiHoYoSDK::RunTimeLog(const char *msg)
{
    if (RunTimeStream)
        *RunTimeStream << NowTime() + ": " << msg << std::endl;
    LOGE("RT: [%s]", msg);
    return true;
}

//写入运行日志 Bytes
inline bool MiHoYoSDK::RunTimeLog(const Bytes &msg)
{
    if (RunTimeStream)
        (*RunTimeStream << NowTime() + ": ").write(msg.c_str(), msg.length()) << std::endl;
    LOGE("RT: [%s]", msg.c_str());
    return true;
}

//写入运行日志 std::string
inline bool MiHoYoSDK::RunTimeLog(const std::string &msg)
{
    if (RunTimeStream)
        *RunTimeStream << NowTime() + ": " << msg << std::endl;
    LOGE("RT: [%s]", msg.c_str());
    return true;
}

//内存读取
template <class T1, class T2>
inline T1 MiHoYoSDK::MemoryRead(T2 addr, uint off)
{
    if (!addr)
        CloseChaosCore1("Addr is nullprt!") && CloseChaosCore2();
    return *(T1 *)((char *)addr + off);
}
