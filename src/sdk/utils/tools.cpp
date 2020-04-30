#include <sys/system_properties.h>
#include "src/sdk/MiHoYoSDK.h"

JavaVM *MiHoYoSDK::Jvm = nullptr;
std::ofstream *MiHoYoSDK::RunTimeStream = nullptr;
Json::Reader MiHoYoSDK::JsonReader;
Json::FastWriter MiHoYoSDK::JsonWriter;

// 获取模块基址
ulong MiHoYoSDK::GetModuleAddr(const char *moduleName)
{
    FILE *fp;
    ulong addr = 0;
    char *pch;
    char line[1024];

    if ((fp = fopen(GET_SAFE_CHAR(StaticData::PATH_maps), "r")) == NULL)
        RT("MA Error") && CCC("Fopen Error!");

    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, moduleName))
        {
            pch = strtok(line, "-");
            addr = strtoul(pch, NULL, 16);
            if (addr == 0x8000)
                addr = 0;
            break;
        }
    }

    fclose(fp);
    return addr;
}

// 获取当前时间(毫秒级)
std::string MiHoYoSDK::NowTime()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    time_t t = time(NULL);
    tm *ptm = localtime(&t);

    static char szTime[19];
    snprintf(szTime, sizeof(szTime), GET_SAFE_CHAR(StaticData::STR_timeFormat),
             ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, tv.tv_usec);
    szTime[18] = 0;

    return std::string(szTime);
}

// 获取JINEnv
JNIEnv *MiHoYoSDK::GetJEnv()
{
    JNIEnv *env;
    Jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    return env;
}

// 初始化运行日志
void MiHoYoSDK::RunTimeInit()
{
    if (RunTimeStream != nullptr)
        return;

    RunTimeStream = new std::ofstream(
        GET_SAFE_DATA(StaticData::PATH_log),
        std::ios::out | std::ios::trunc | std::ios::binary);

    if (RunTimeStream == nullptr || !RunTimeStream->is_open())
        CCC("RT Open Error!");

    RT(GET_SAFE_DATA(StaticData::STR_logStart) +
       GET_SAFE_DATA(StaticData::BUILD_VERSION));
}

// 关闭Java虚拟机
bool MiHoYoSDK::CloseJVM(std::string msg)
{
    if (msg.empty())
        LOGE("CCC Call!");
    else
        LOGE("CCC Error: %s", msg.c_str());

    JNIEnv *env = GetJEnv();
    env->ExceptionClear();
    env->FatalError("");
    return true;
}

// 获取机器UUID
MiHoYoSDK::Bytes MiHoYoSDK::GetUUID()
{
    using namespace MiHoYoSDK::StaticData;

    Bytes buff;
    char tmp[PROP_VALUE_MAX] = "";
    int len = 0;

    //主板系统
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData01), tmp)) <= 0)
        RT("UI Error 0x01") && CCC("UUID roData01 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //机器品牌
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData02), tmp)) <= 0)
        RT("UI Error 0x02") && CCC("UUID roData02 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //CPU类型
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData03), tmp)) <= 0)
        RT("UI Error 0x03") && CCC("UUID roData03 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //设备名
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData04), tmp)) <= 0)
        RT("UI Error 0x04") && CCC("UUID roData04 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //显示标识
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData05), tmp)) <= 0)
        RT("UI Error 0x05") && CCC("UUID roData05 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //系统主机名
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData06), tmp)) <= 0)
        RT("UI Error 0x06") && CCC("UUID roData06 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //构建ID
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData07), tmp)) <= 0)
        RT("UI Error 0x07") && CCC("UUID roData07 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //制造商
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData08), tmp)) <= 0)
        RT("UI Error 0x08") && CCC("UUID roData08 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //机器型号
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData09), tmp)) <= 0)
        RT("UI Error 0x09") && CCC("UUID roData09 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //系统标记
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData10), tmp)) <= 0)
        RT("UI Error 0x10") && CCC("UUID roData10 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //系统编译类型
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData11), tmp)) <= 0)
        RT("UI Error 0x11") && CCC("UUID roData11 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //系统用户名
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData12), tmp)) <= 0)
        RT("UI Error 0x12") && CCC("UUID roData12 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //版本的增加说明
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData13), tmp)) <= 0)
        RT("UI Error 0x13") && CCC("UUID roData13 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //系统编译的SDK
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData14), tmp)) <= 0)
        RT("UI Error 0x14") && CCC("UUID roData14 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //版本编码名称
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData15), tmp)) <= 0)
        RT("UI Error 0x15") && CCC("UUID roData15 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //公布的版本
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData16), tmp)) <= 0)
        RT("UI Error 0x16") && CCC("UUID roData16 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //系统编译的时间
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData17), tmp)) <= 0)
        RT("UI Error 0x17") && CCC("UUID roData17 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //编译设备名
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData18), tmp)) <= 0)
        RT("UI Error 0x18") && CCC("UUID roData18 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //用户的KEY
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData19), tmp)) <= 0)
        RT("UI Error 0x19") && CCC("UUID roData19 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //机身码
    if ((len = __system_property_get(GET_SAFE_CHAR(STR_roData20), tmp)) <= 0)
        RT("UI Error 0x20") && CCC("UUID roData20 Error!");
    buff = MD5(buff += MD5(Bytes(tmp, len)));

    //cpu最大频率
    std::string cpu_max_freq = FileLine(GET_SAFE_CHAR(PATH_CPUMaxFreq));
    buff = MD5(buff += MD5(cpu_max_freq, true));

    //cpu最小频率
    std::string cpu_min_freq = FileLine(GET_SAFE_CHAR(PATH_CPUMinFreq));
    buff = MD5(buff += MD5(cpu_min_freq, true));

    //cpu信息
    std::string cpu_info = FileRead(GET_SAFE_CHAR(PATH_CPUInfo));
    buff = MD5(buff += MD5(cpu_info, true));

    //内存信息
    std::string mem_info = FileLine(GET_SAFE_CHAR(PATH_MemInfo));
    StrDeleteMark(mem_info, " "); //删掉空格
    buff = MD5(buff += MD5(mem_info, true));

    //系统版本
    std::string version = FileLine(GET_SAFE_CHAR(PATH_SystemVersion));
    StrDeleteMark(version, " "); //删掉空格
    buff = MD5(buff += MD5(version));

    //整体的MD5
    buff = MD5(buff += MD5(buff));

    LOGE("UUID: [%s]", buff.c_str());
    return buff;
}
