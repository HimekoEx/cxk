#pragma once

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {
        //逻辑模块
        namespace Logic
        {
            //名词模块
            namespace Noun
            {

                //类名 基础Avatar
                const std::string Clazz_BaseMonoAvatar = "BaseMonoAvatar";
                //类名 基础Entity
                const std::string Clazz_BaseMonoEntity = "BaseMonoEntity";

                //能力 SP回复倍率
                const std::string Actor_SPRecoverRatio = "Actor_SPRecoverRatio";
                //能力 攻击回复HP倍率
                const std::string Actor_AttackStealHPRatio = "Actor_AttackStealHPRatio";

                //动能 冰冻
                const std::string GLOBAL_FROZEN_POINT = "_GLOBAL_FROZEN_POINT";
                //动能 崩坏能
                const std::string GLOBAL_HONKAI_VALUE = "_GLOBAL_HONKAI_VALUE";
                //动能 霜冻(丽塔腐蚀)
                const std::string GLOBAL_DQ_FROST = "_GLOBAL_DQ_FROST_VALUE";

            } // namespace Noun
        }     // namespace Logic
    }         // namespace Loaded
} // namespace Hook
