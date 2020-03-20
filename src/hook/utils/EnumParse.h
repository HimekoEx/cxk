#pragma once
#include "src/sdk/MiHoYoSDK.h"
#include "src/hook/logic/Enum.h"

//Hook架构
namespace Hook
{
//工具
namespace Uitls
{

// 解析StageCheatData
std::string ParseStageCheatData(Loaded::Logic::StageCheatData_Type type, float value);

}
}
