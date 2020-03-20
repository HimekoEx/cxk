#pragma once
#include "src/sdk/MiHoYoSDK.h"

//同步
namespace Sync
{

//行数据
struct LineData
{
    int LineType;
    double LineValue;
    bool LineState;
};

//主体数据
struct MainData
{
    bool State;
    std::map<std::string, LineData> SubData;
};

//状态数组
extern std::map<std::string, MainData> *Config;

//获取状态和值
template <class T>
T GetStateOrValue(const std::string &key, const std::string &subKey, T defVale)
{
    auto iter = Config->find(key);
    if (iter != Config->end())
    {
        if (subKey.empty())
        {
            // if (iter->second.State) //&& key != "定怪")
            //     LOGE("%s -> %s", key.c_str(), BoolToChar(iter->second.State));
            return iter->second.State;
        }
        else if (!iter->second.State)
            return defVale;

        std::map<std::string, Sync::LineData> subData = iter->second.SubData;
        auto iter = subData.find(subKey);
        if (iter != subData.end())
        {
            if (iter->second.LineType == 1)
            {
                // LOGE("%s::%s -> %0.2f", key.c_str(), subKey.c_str(), (float)iter->second.LineValue);
                return (float)iter->second.LineValue;
            }
            else if (iter->second.LineType == 2)
            {
                if (iter->second.LineState)
                {
                    // LOGE("%s::%s -> %s", key.c_str(), subKey.c_str(), BoolToChar(iter->second.LineState));
                    return iter->second.LineState;
                }
            }
        }
    }

    // LOGE("%s.%s not find!", key.c_str(), subKey.c_str());
    return defVale;
}

} // namespace Sync
