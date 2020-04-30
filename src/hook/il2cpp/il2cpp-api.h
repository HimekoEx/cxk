#pragma once
#include "src/sdk/MiHoYoSDK.h"

#include "il2cpp-api-types.h"
#include "il2cpp-blob.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-config.h"
#include "il2cpp-metadata.h"
#include "il2cpp-runtime-metadata.h"

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {
        //Il2cpp模块
        namespace Il2cpp
        {

            struct Il2CppNameToTypeDefinitionIndexHashTable;
            struct MonitorData;

            struct Il2CppObject
            {
                Il2CppClass *klass;
                MonitorData *monitor;
            };

            struct Il2CppString
            {
                Il2CppObject object;
                int32_t length; ///< Length of string *excluding* the trailing null (which is included in 'chars').
                Il2CppChar chars[IL2CPP_ZERO_LEN_ARRAY];
            };

        } // namespace Il2cpp
    }     // namespace Loaded
} // namespace Hook
