#pragma once

//第三方库
#include <include/hookzz/hookzz.h>
#include "src/sdk/MiHoYoSDK.h"
#include "src/sync/sync.h"

//Hook库
#include "dlopen/dlopen.h"
#include "loaded/il2cpp.h"
#include "loaded/tersafe2.h"
#include "logic/ClassLoad.h"
#include "logic/Functions.h"
#include "patch/il2cpp.h"

//工具库
#include "il2cpp/il2cpp-api.h"
#include "logic/CSharpString.hpp"
#include "logic/Noun.h"
#include "patch/Const.h"
#include "logic/Enum.h"
#include "utils/Amend.h"
#include "utils/EnumParse.h"

//Hook架构
namespace Hook
{

    // 替换函数
    template <class T1, class T2, class T3>
    inline void zzReplace(T1 targetPtr, T2 replaceCall, T3 originCallPtr)
    {
        if (ZzHookReplace((void *)targetPtr, (void *)replaceCall, (void **)originCallPtr) < RS_SUCCESS)
            RT("RP Error!") && CCC("zzReplace Error!");
    }

    // 指令替换 & map备份
    template <typename T1, typename T2>
    inline void zzCodePatch(T1 address, T2 codeData, std::map<ulong, ulong> *data = NULL)
    {
        if (data != NULL)
            (*data)[address] = *(ulong *)address;
        if (ZzRuntimeCodePatch((void *)address, (void *)&codeData, 4) < RS_SUCCESS)
            RT("CP Error!") && CCC("zzCodePatch Error!");
    }

} // namespace Hook
