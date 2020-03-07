#pragma once

//System
#include <array>
#include <map>
#include <set>
#include <vector>

//Hookzz
#include <include/hookzz/hookzz.h>

#include "src/hook/module_CString.h"
#include "src/mihoyo_sdk/MiHoYoSDK.h"
#include "src/mihoyo_sdk/static/MiHoYoSDK_StaticData.h"

//同步
namespace Sync
{

//行数据
struct LineData
{
    int LineType;
    double LineValue;
    bool LineState;
};
//主体数据
struct MainData
{
    bool State;
    std::map<std::string, LineData> SubData;
};

//全局Il2cpp地址
extern ulong Il2cpp;
//MTP va检测函数地址
extern int MTP_Off;
//二段 UUID上传锁
extern bool UUID_Lock;
//地址数量
const uchar ADSS_NUM = 4;

//开启使用权限的函数列表
extern std::set<std::string> *OpenFuncs;
//地址数组
extern std::array<ulong, ADSS_NUM> Address;
//还原用的数据保存
extern std::map<ulong, std::map<ulong, ulong>> *PatchData;
//状态数组
extern std::map<std::string, MainData> *Config;

//初始化地址
extern void InitAddress(ulong il2cpp);
//通过服务器发送的配置进行初始化
extern void InitConfig(const MiHoYoSDK::Bytes &configs);
//手动初始化所有全局变量, 以防多线程导致过快操作变量导致出问题
extern void InitAllVariable();
//同步json状态
extern void SyncJsonConfig();

//获取状态和值
template <class T>
T GetStateOrValue(const std::string &key, const std::string &subKey, T defVale)
{
    auto iter = Config->find(key);
    if (iter != Config->end())
    {
        if (subKey.empty())
        {
            // if (iter->second.State &&
            //     key != "定怪")
            //     LOGE("%s -> %s", key.c_str(), BoolToChar(iter->second.State));
            return iter->second.State;
        }

        std::map<std::string, Sync::LineData> subData = iter->second.SubData;
        auto iter = subData.find(subKey);
        if (iter != subData.end())
        {
            if (iter->second.LineType == 1)
            {
                // LOGE("%s::%s -> %0.2f", key.c_str(), subKey.c_str(), (float)iter->second.LineValue);
                return (float)iter->second.LineValue;
            }
            else if (iter->second.LineType == 2)
            {
                if (iter->second.LineState)
                    // LOGE("%s::%s -> %s", key.c_str(), subKey.c_str(), BoolToChar(iter->second.LineState));
                    return iter->second.LineState;
            }
        }
    }

    return defVale;
}

} // namespace Sync

//代理chaos的dlopen
extern void ReplaceDlopen();
//功能hook
extern void FuckingIl2cpp(void *handle);
//初始化patch
extern void FirstFucking();
//循环patch
extern void FuckingLIB();
//干MTP va检测
extern bool FuckingMTP(int32_t handle);

//zzHook 替换函数
template <class t1, class t2, class t3>
inline void zzReplace(t1 target_ptr, t2 replace_call, t3 origin_call_ptr)
{
    if (ZzHookReplace((void *)target_ptr, (void *)replace_call, (void **)origin_call_ptr) < RS_SUCCESS)
        MiHoYoSDK::RunTimeLog("zzRP Error!") && MiHoYoSDK::CloseChaosCore1("zzReplace error!") && MiHoYoSDK::CloseChaosCore2();
}

//zzHook 修改指令 & 添加备份
template <typename t1, typename t2>
inline void zzCodePatch(t1 address, t2 code_data, std::map<ulong, ulong> *data = NULL)
{
    if (data != NULL)
        (*data)[address] = *(ulong *)address;
    if (ZzRuntimeCodePatch((void *)address, (void *)&code_data, 4) < RS_SUCCESS)
        MiHoYoSDK::RunTimeLog("zzCP Error!") && MiHoYoSDK::CloseChaosCore1("zzCodePatch error!") && MiHoYoSDK::CloseChaosCore2();
}
