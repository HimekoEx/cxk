#pragma once
#include <sys/syscall.h>
#include "src/sdk/Base.h"

//SDK
namespace MiHoYoSDK
{

//全局JavaVM
extern JavaVM *Jvm;
//日志文件输出流
extern std::ofstream *RunTimeStream;
//全局Json解析器
extern Json::Reader JsonReader;
//全局Json转换器
extern Json::FastWriter JsonWriter;

// 获取模块基址
ulong GetModuleAddr(const char *moduleName);
// 获取当前时间(毫秒级)
std::string NowTime();
// 获取JINEnv
JNIEnv *GetGEnv();
// 初始化运行日志
void RunTimeInit();
// 关闭Java虚拟机
bool CloseJVM(std::string msg = "");
// 获取机器UUID
Bytes GetUUID();

// 关闭核心
static inline bool CloseCore()
{
    int *p = nullptr;
    *p = 0x92D9;
    pid_t pid = syscall(__NR_getpid);
    kill(pid, SIGKILL);
    _exit(0);
    return true;
}

// 日志输出
inline bool RunTimeLog(const Bytes &msg)
{
    if (RunTimeStream)
        *RunTimeStream << (NowTime() + ": ")
                       << (msg.get())
                       << (std::endl);

    LOGE("RT: [%s]", msg.c_str());
    return true;
}

} // namespace MiHoYoSDK
