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

            // 首次修改il2cpp
            void FirstPatchIl2cpp();

            // 循环修改il2cpp
            void LoopPatchIl2cpp();

        } // namespace Patch
    }     // namespace Loaded
} // namespace Hook
