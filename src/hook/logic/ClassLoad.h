#pragma once
#include "src/sdk/MiHoYoSDK.h"
#include "src/hook/il2cpp/il2cpp-api.h"

//Hook架构
namespace Hook
{
//Lib加载模块
namespace Loaded
{
//逻辑模块
namespace Logic
{

//MoleMole镜像
extern Il2cpp::Il2CppImage *MoleMole;
//MonoMTP类型
extern Il2cpp::Il2CppClass *MonoMTP;

// 劫持游戏Class
Il2cpp::Il2CppClass *HookClass(Il2cpp::Il2CppImage *image, const char *namespaze, const char *name);

}
}
}
