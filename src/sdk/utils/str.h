#pragma once
#include "src/sdk/Base.h"

//SDK
namespace MiHoYoSDK
{

    // 子串删除
    std::string &StrDeleteMark(std::string &src, const std::string &mark);
    // 子串替换
    std::string &StrReplaceMark(std::string &src, const std::string &from, const std::string &to);

} // namespace MiHoYoSDK
