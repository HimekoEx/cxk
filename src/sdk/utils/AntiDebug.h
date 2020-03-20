#pragma once
#include "src/sdk/Base.h"

//SDK
namespace MiHoYoSDK
{

//反调试线程ID
extern pthread_t AntiDebugID;

// 开启反调试线程
void AntiDebug();
// 检测Debug状态
void *CheckDebug(void *);

}
