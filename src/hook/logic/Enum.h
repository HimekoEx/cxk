#pragma once
#include "src/sdk/MiHoYoSDK.h"

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {
        //逻辑模块
        namespace Logic
        {

            enum class Tp2Entry //Tp2入口
            {
                ENTRY_ID_QZONE = 1,
                ENTRY_ID_MM = 2,
                ENTRT_ID_FACEBOOK = 3,
                ENTRY_ID_TWITTER = 4,
                ENTRY_ID_LINE = 5,
                ENTRY_ID_WHATSAPP = 6,
                ENTRY_ID_OTHERS = 99,
            };

            enum class AttackResult_AnimatorHitEffect
            {
                Mute = 0,
                Light = 1,
                Normal = 2,
                FaceAttacker = 3,
                ThrowUp = 4,
                ThrowDown = 5,
                KnockDown = 6,
                ThrowUpBlow = 7,
                ThrowBlow = 8,
                ThrowAirBlow = 9,
                ThrowSkillKnockDown = 10,
            };

            enum class AttackResult_AnimatorHitEffectAux
            {
                Normal = 0,
                HitLeft = 1,
                HitRight = 2,
                HitUpper = 3,
                HitCentered = 4,
                HitBack = 5,
                HitOnLeft = 6,
                HitOnRight = 7,
            };

            enum class KillEffect
            {
                KillNow = 0,
                KillFastWithDieAnim = 1,
                KillFastWithNormalAnim = 2,
                KillFastImmediately = 3,
                KillImmediately = 4,
                KillTillHitAnimationEnd = 5,
                KillWithSwitchOutFader = 6,
            };

            enum class BeHitEffect
            {
                NormalBeHit = 0,
                KillingBeHit = 1,
                OverkillBeHit = 2,
            };

            enum class StageCheatData_Type //关卡收集数据
            {
                STAGE_ID = 1,                         // 阶段ID
                STAGE_PROGRESS = 2,                   // 阶段进展
                STAGE_MAX_SCORE = 3,                  // 阶段最大分数
                TIME_START = 1001,                    // 时间开始
                TIME_USE = 1002,                      // 使用时间
                AVG_FRAME_TIME = 1003,                // 平均帧时间
                PLAYER_LEVEL = 1004,                  // 玩家等级
                STAGE_SCORE = 1005,                   // 阶段分数
                AVATAR_ID_1 = 2001,                   // 女武神ID_1
                AVATAR_LEVEL_1 = 2002,                // 女武神等级_1
                AVATAR_COMBAT_1 = 2003,               // 女武神战斗力_1
                ATTACK_MAX_1 = 2004,                  // 攻击最大值_1
                SP_MAX_1 = 2005,                      // SP最大值_1
                SP_BEGIN_1 = 2006,                    // SP初始值_1
                SP_END_1 = 2007,                      // SP结束值_1
                SP_GAIN_1 = 2008,                     // SP获得值_1
                SP_USE_1 = 2009,                      // SP使用值_1
                HP_MAX_1 = 2010,                      // HP最大值_1
                HP_BEGIN_1 = 2011,                    // HP初始值_1
                HP_END_1 = 2012,                      // HP结束值_1
                HP_GAIN_1 = 2013,                     // HP获得值_1
                HIT_COUNT_1 = 2014,                   // 命中次数_1
                HIT_DAMAGE_1 = 2015,                  // 命中伤害_1
                HIT_NORMAL_DAMAGE_MAX_1 = 2016,       // 正常伤害最大值_1
                HIT_CRITICAL_DAMAGE_MAX_1 = 2017,     // 暴击伤害最大值_1
                BEHIT_COUNT_1 = 2018,                 // 被击中次数_1
                BEHIT_NORMAL_DAMAGE_MAX_1 = 2019,     // 被击中的正常伤害最大值_1
                BEHIT_CRITICAL_DAMAGE_MAX_1 = 2020,   // 被击中的暴击伤害最大值_1
                COMBO_MAX_1 = 2021,                   // 连击最大值_1
                AVATAR_TIME_USE_1 = 2022,             // 女武神使用时间_1
                WEAPON_LEVEL_1 = 2023,                // 武器等级_1
                STIGMATA_LEVEL_MAX_1 = 2024,          // 圣痕等级最大值_1
                MP_TEAM_SKILL_TIMES_1 = 2025,         // MP团队技能次数_1
                MP_QTE_SKILL_TIMES_1 = 2026,          // MPQTE技能次数_1
                MP_BE_RESCUED_TIMES_1 = 2027,         // MP被拯救次数_1
                MP_RESCUE_TIMES_1 = 2028,             // MP拯救次数_1
                MP_AVG_RESCUE_TIME_1 = 2029,          // MP平均救援时间_1
                MP_CHAT_TIMES_1 = 2030,               // MP聊天次数_1
                ULTIMATE_SKILL_TIMES_1 = 2031,        // 终极技能次数_1
                ULTIMATE_SKILL_DURATION_1 = 2032,     // 终极技能持续时间_1
                ATTACK_SP_GAIN_1 = 2033,              // 攻击获得SP_1
                WEAPON_SKILL_TIMES_1 = 2034,          // 武器技能次数_1
                AVATAR_ID_2 = 2101,                   // 女武神ID_2
                AVATAR_LEVEL_2 = 2102,                // 女武神等级_2
                AVATAR_COMBAT_2 = 2103,               // 女武神战斗力_2
                ATTACK_MAX_2 = 2104,                  // 攻击最大值_2
                SP_MAX_2 = 2105,                      // SP最大值_2
                SP_BEGIN_2 = 2106,                    // SP初始值_2
                SP_END_2 = 2107,                      // SP结束值_2
                SP_GAIN_2 = 2108,                     // SP获得值_2
                SP_USE_2 = 2109,                      // SP使用值_2
                HP_MAX_2 = 2110,                      // HP最大值_2
                HP_BEGIN_2 = 2111,                    // HP初始值_2
                HP_END_2 = 2112,                      // HP结束值_2
                HP_GAIN_2 = 2113,                     // HP获得值_2
                HIT_COUNT_2 = 2114,                   // 命中次数_2
                HIT_DAMAGE_2 = 2115,                  // 命中伤害_2
                HIT_NORMAL_DAMAGE_MAX_2 = 2116,       // 正常伤害最大值_2
                HIT_CRITICAL_DAMAGE_MAX_2 = 2117,     // 暴击伤害最大值_2
                BEHIT_COUNT_2 = 2118,                 // 被击中次数_2
                BEHIT_NORMAL_DAMAGE_MAX_2 = 2119,     // 被击中的正常伤害最大值_2
                BEHIT_CRITICAL_DAMAGE_MAX_2 = 2120,   // 被击中的暴击伤害最大值_2
                COMBO_MAX_2 = 2121,                   // 连击最大值_2
                AVATAR_TIME_USE_2 = 2122,             // 女武神使用时间_2
                WEAPON_LEVEL_2 = 2123,                // 武器等级_2
                STIGMATA_LEVEL_MAX_2 = 2124,          // 圣痕等级最大值_2
                MP_TEAM_SKILL_TIMES_2 = 2125,         // MP团队技能次数_2
                MP_QTE_SKILL_TIMES_2 = 2126,          // MPQTE技能次数_2
                MP_BE_RESCUED_TIMES_2 = 2127,         // MP被拯救次数_2
                MP_RESCUE_TIMES_2 = 2128,             // MP拯救次数_2
                MP_AVG_RESCUE_TIME_2 = 2129,          // MP平均救援时间_2
                MP_CHAT_TIMES_2 = 2130,               // MP聊天次数_2
                ULTIMATE_SKILL_TIMES_2 = 2131,        // 终极技能次数_2
                ULTIMATE_SKILL_DURATION_2 = 2132,     // 终极技能持续时间_2
                ATTACK_SP_GAIN_2 = 2133,              // 攻击获得SP_2
                WEAPON_SKILL_TIMES_2 = 2134,          // 武器技能次数_2
                AVATAR_ID_3 = 2201,                   // 女武神ID_3
                AVATAR_LEVEL_3 = 2202,                // 女武神等级_3
                AVATAR_COMBAT_3 = 2203,               // 女武神战斗力_3
                ATTACK_MAX_3 = 2204,                  // 攻击最大值_3
                SP_MAX_3 = 2205,                      // SP最大值_3
                SP_BEGIN_3 = 2206,                    // SP初始值_3
                SP_END_3 = 2207,                      // SP结束值_3
                SP_GAIN_3 = 2208,                     // SP获得值_3
                SP_USE_3 = 2209,                      // SP使用值_3
                HP_MAX_3 = 2210,                      // HP最大值_3
                HP_BEGIN_3 = 2211,                    // HP初始值_3
                HP_END_3 = 2212,                      // HP结束值_3
                HP_GAIN_3 = 2213,                     // HP获得值_3
                HIT_COUNT_3 = 2214,                   // 命中次数_3
                HIT_DAMAGE_3 = 2215,                  // 命中伤害_3
                HIT_NORMAL_DAMAGE_MAX_3 = 2216,       // 正常伤害最大值_3
                HIT_CRITICAL_DAMAGE_MAX_3 = 2217,     // 暴击伤害最大值_3
                BEHIT_COUNT_3 = 2218,                 // 被击中次数_3
                BEHIT_NORMAL_DAMAGE_MAX_3 = 2219,     // 被击中的正常伤害最大值_3
                BEHIT_CRITICAL_DAMAGE_MAX_3 = 2220,   // 被击中的暴击伤害最大值_3
                COMBO_MAX_3 = 2221,                   // 连击最大值_3
                AVATAR_TIME_USE_3 = 2222,             // 女武神使用时间_3
                WEAPON_LEVEL_3 = 2223,                // 武器等级_3
                STIGMATA_LEVEL_MAX_3 = 2224,          // 圣痕等级最大值_3
                MP_TEAM_SKILL_TIMES_3 = 2225,         // MP团队技能次数_3
                MP_QTE_SKILL_TIMES_3 = 2226,          // MPQTE技能次数_3
                MP_BE_RESCUED_TIMES_3 = 2227,         // MP被拯救次数_3
                MP_RESCUE_TIMES_3 = 2228,             // MP拯救次数_3
                MP_AVG_RESCUE_TIME_3 = 2229,          // MP平均救援时间_3
                MP_CHAT_TIMES_3 = 2230,               // MP聊天次数_3
                ULTIMATE_SKILL_TIMES_3 = 2231,        // 终极技能次数_3
                ULTIMATE_SKILL_DURATION_3 = 2232,     // 终极技能持续时间_3
                ATTACK_SP_GAIN_3 = 2233,              // 攻击获得SP_3
                WEAPON_SKILL_TIMES_3 = 2234,          // 武器技能次数_3
                ELF_ID = 2301,                        // 人偶ID_1
                ELF_LEVEL = 2302,                     // 人偶等级_1
                ELF_COMBAT = 2303,                    // 人偶战斗力_1
                ELF_ATTACK = 2304,                    // 人偶攻击_1
                ELF_SP_MAX = 2305,                    // 人偶SP最大值_1
                ELF_ULTIMATE_SKILL_TIMES = 2306,      // 人偶终极技能次数_1
                ELF_SP_USE = 2307,                    // 人偶SP使用值_1
                ELF_HIT_CRITICAL_DAMAGE_MAX = 2308,   // 人偶暴击伤害最大值_1
                ELF_HIT_NORMAL_DAMAGE_MAX = 2309,     // 人偶正常伤害最大值_1
                ELF_ID_2 = 2401,                      // 人偶ID_2
                ELF_LEVEL_2 = 2402,                   // 人偶等级_2
                ELF_COMBAT_2 = 2403,                  // 人偶战斗力_2
                ELF_ATTACK_2 = 2404,                  // 人偶攻击_2
                ELF_SP_MAX_2 = 2405,                  // 人偶SP最大值_2
                ELF_ULTIMATE_SKILL_TIMES_2 = 2406,    // 人偶终极技能次数_2
                ELF_SP_USE_2 = 2407,                  // 人偶SP使用值_2
                ELF_HIT_CRITICAL_DAMAGE_MAX_2 = 2408, // 人偶暴击伤害最大值_2
                ELF_HIT_NORMAL_DAMAGE_MAX_2 = 2409,   // 人偶正常伤害最大值_2
                ELF_ID_3 = 2501,                      // 人偶ID_3
                ELF_LEVEL_3 = 2502,                   // 人偶等级_3
                ELF_COMBAT_3 = 2503,                  // 人偶战斗力_3
                ELF_ATTACK_3 = 2504,                  // 人偶攻击_3
                ELF_SP_MAX_3 = 2505,                  // 人偶SP最大值_3
                ELF_ULTIMATE_SKILL_TIMES_3 = 2506,    // 人偶终极技能次数_3
                ELF_SP_USE_3 = 2507,                  // 人偶SP使用值_3
                ELF_HIT_CRITICAL_DAMAGE_MAX_3 = 2508, // 人偶暴击伤害最大值_3
                ELF_HIT_NORMAL_DAMAGE_MAX_3 = 2509,   // 人偶正常伤害最大值_3
                IS_MP_VOICE_USED = 3001,              // 是否使用MP语音
                MP_VOICE_USE_TIME = 3002,             // MP语音使用时间
                SEALED_EVENT_ID = 4001                // 密封事件ID
            };

            enum class LevelSPRecoverSource
            {
                None = 0,
                Attack = 1,
                Ability = 2,
                Item = 3,
                Steal = 4,
                Rogue = 5,
            };

            enum class LevelEndReason
            {
                EndUncertainReason = 0,
                EndWin = 1,
                EndLoseNotMeetCondition = 2,
                EndLoseAllDead = 3,
                EndLoseQuit = 4,
                EndLoseJump = 5,
            };

            enum class EntityNature //属性
            {
                Pure = 0,      //纯净
                Biology = 1,   //生物
                Psycho = 2,    //异能
                Mechanic = 3,  //机械
                Quantum = 4,   //量子
                Imaginary = 5, //虚数
                Count = 6,
            };

        } // namespace Logic
    }     // namespace Loaded
} // namespace Hook
