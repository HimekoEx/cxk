#include "src/sdk/MiHoYoSDK.h"

#define AX(symbol) (*(int32_t *)(symbol) << 8 >> 6)

//Hook架构
namespace Hook
{
//工具
namespace Uitls
{

// 修正B指令转跳
inline void *Amend_B(void *symbol)
{
    return ((char *)symbol + AX(symbol) + 8);
}

// 修正Class_GetMethodFromNameFlags的地址
inline void *Amend_ClassGetMethodFromNameFlags(void *symbol)
{
    return ((char *)symbol + AX(symbol) +
            AX((char *)symbol + AX(symbol) + 12) + 20);
}

//修正函数的地址
inline void *Amend_ClassFromName(void *symbol)
{
    return ((char *)symbol + AX(symbol) +
            AX((char *)symbol + AX(symbol) + 8) + 16);
}

}
}
