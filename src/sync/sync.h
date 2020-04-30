#pragma once

//System
#include <array>
#include <map>
#include <set>
#include <vector>
#include <time.h>

//第三方库
#include "src/sdk/MiHoYoSDK.h"
#include "src/hook/hook.h"
#include "configs.h"

//同步
namespace Sync
{

    //全局Il2cpp地址
    extern ulong Il2cpp;
    //MTP va检测函数地址
    extern int MTP_Off;
    //地址数量
    const uchar ADSS_NUM = 4;

    //开启使用权限的函数列表
    extern std::set<std::string> *OpenFuncs;
    //地址数组
    extern std::array<ulong, ADSS_NUM> Address;
    //还原用的数据保存
    extern std::map<ulong, std::map<ulong, ulong>> *PatchData;

    // 初始化全局变量
    void InitAllVariable();
    // 初始化地址
    void InitAddress(ulong il2cpp);
    // 通过服务器发送的配置进行初始化
    bool InitConfig(const MiHoYoSDK::Bytes &configs);
    // 同步json状态
    void SyncJsonConfig();

} // namespace Sync
