#pragma once
#include "src/sdk/MiHoYoSDK.h"

//Hook架构
namespace Hook
{
//Lib加载模块
namespace Loaded
{
//Patch模块
namespace Patch
{
//常量模块
namespace Const
{

const ulong Down_x38 = 0xEA000038;
const ulong NOP = 0xE320F000;
const ulong BX_LR = 0xE12FFF1E;

} // namespace Const
} // namespace Patch
} // namespace Loaded
} // namespace Hook
