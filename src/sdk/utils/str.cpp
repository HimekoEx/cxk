#include "str.h"

// 子串删除
std::string &MiHoYoSDK::StrDeleteMark(std::string &src, const std::string &mark)
{
    if (src.empty())
        return src;

    size_t size = mark.size();
    while (true)
    {
        size_t pos = src.find(mark);
        if (pos == std::string::npos)
            break;
        src.erase(pos, size);
    }

    return src;
}

// 子串替换
std::string &MiHoYoSDK::StrReplaceMark(std::string &src, const std::string &from, const std::string &to)
{
    if (src.empty() || from.empty())
        return src;
    size_t start_pos = 0;
    size_t size = from.size();
    while ((start_pos = src.find(from, start_pos)) != std::string::npos)
    {
        src.replace(start_pos, size, to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }

    return src;
}
