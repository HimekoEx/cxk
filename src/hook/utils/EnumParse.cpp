#include "src/hook/hook.h"

#ifndef RELEASE
// 解析StageCheatData
std::string Hook::Uitls::ParseStageCheatData(Loaded::Logic::StageCheatData_Type type, float value)
{
    std::string tmp = "StageCheatData[";
    switch (type)
    {
    case Loaded::Logic::StageCheatData_Type::STAGE_ID:
        tmp += "阶段ID";
        break;
    case Loaded::Logic::StageCheatData_Type::STAGE_PROGRESS:
        tmp += "阶段进展";
        break;
    case Loaded::Logic::StageCheatData_Type::STAGE_MAX_SCORE:
        tmp += "阶段最大分数";
        break;
    case Loaded::Logic::StageCheatData_Type::TIME_START:
        tmp += "时间开始";
        break;
    case Loaded::Logic::StageCheatData_Type::TIME_USE:
        tmp += "使用时间";
        break;
    case Loaded::Logic::StageCheatData_Type::AVG_FRAME_TIME:
        tmp += "平均帧时间";
        break;
    case Loaded::Logic::StageCheatData_Type::PLAYER_LEVEL:
        tmp += "玩家等级";
        break;
    case Loaded::Logic::StageCheatData_Type::STAGE_SCORE:
        tmp += "阶段分数";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::AVATAR_ID_1:
        tmp += "女武神ID_1";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_LEVEL_1:
        tmp += "女武神等级_1";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_COMBAT_1:
        tmp += "女武神战斗力_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ATTACK_MAX_1:
        tmp += "攻击最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_MAX_1:
        tmp += "SP最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_BEGIN_1:
        tmp += "SP初始值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_END_1:
        tmp += "SP结束值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_GAIN_1:
        tmp += "SP获得值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_USE_1:
        tmp += "SP使用值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_MAX_1:
        tmp += "HP最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_BEGIN_1:
        tmp += "HP初始值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_END_1:
        tmp += "HP结束值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_GAIN_1:
        tmp += "HP获得值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_COUNT_1:
        tmp += "命中次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_DAMAGE_1:
        tmp += "命中伤害_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_NORMAL_DAMAGE_MAX_1:
        tmp += "正常伤害最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_CRITICAL_DAMAGE_MAX_1:
        tmp += "暴击伤害最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_COUNT_1:
        tmp += "被击中次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_NORMAL_DAMAGE_MAX_1:
        tmp += "被击中的正常伤害最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_CRITICAL_DAMAGE_MAX_1:
        tmp += "被击中的暴击伤害最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::COMBO_MAX_1:
        tmp += "连击最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_TIME_USE_1:
        tmp += "女武神使用时间_1";
        break;
    case Loaded::Logic::StageCheatData_Type::WEAPON_LEVEL_1:
        tmp += "武器等级_1";
        break;
    case Loaded::Logic::StageCheatData_Type::STIGMATA_LEVEL_MAX_1:
        tmp += "圣痕等级最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_TEAM_SKILL_TIMES_1:
        tmp += "MP团队技能次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_QTE_SKILL_TIMES_1:
        tmp += "MPQTE技能次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_BE_RESCUED_TIMES_1:
        tmp += "MP被拯救次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_RESCUE_TIMES_1:
        tmp += "MP拯救次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_AVG_RESCUE_TIME_1:
        tmp += "MP平均救援时间_1";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_CHAT_TIMES_1:
        tmp += "MP聊天次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ULTIMATE_SKILL_TIMES_1:
        tmp += "终极技能次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ULTIMATE_SKILL_DURATION_1:
        tmp += "终极技能持续时间_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ATTACK_SP_GAIN_1:
        tmp += "攻击获得SP_1";
        break;
    case Loaded::Logic::StageCheatData_Type::WEAPON_SKILL_TIMES_1:
        tmp += "武器技能次数_1";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::AVATAR_ID_2:
        tmp += "女武神ID_2";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_LEVEL_2:
        tmp += "女武神等级_2";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_COMBAT_2:
        tmp += "女武神战斗力_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ATTACK_MAX_2:
        tmp += "攻击最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_MAX_2:
        tmp += "SP最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_BEGIN_2:
        tmp += "SP初始值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_END_2:
        tmp += "SP结束值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_GAIN_2:
        tmp += "SP获得值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_USE_2:
        tmp += "SP使用值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_MAX_2:
        tmp += "HP最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_BEGIN_2:
        tmp += "HP初始值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_END_2:
        tmp += "HP结束值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_GAIN_2:
        tmp += "HP获得值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_COUNT_2:
        tmp += "命中次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_DAMAGE_2:
        tmp += "命中伤害_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_NORMAL_DAMAGE_MAX_2:
        tmp += "正常伤害最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_CRITICAL_DAMAGE_MAX_2:
        tmp += "暴击伤害最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_COUNT_2:
        tmp += "被击中次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_NORMAL_DAMAGE_MAX_2:
        tmp += "被击中的正常伤害最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_CRITICAL_DAMAGE_MAX_2:
        tmp += "被击中的暴击伤害最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::COMBO_MAX_2:
        tmp += "连击最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_TIME_USE_2:
        tmp += "女武神使用时间_2";
        break;
    case Loaded::Logic::StageCheatData_Type::WEAPON_LEVEL_2:
        tmp += "武器等级_2";
        break;
    case Loaded::Logic::StageCheatData_Type::STIGMATA_LEVEL_MAX_2:
        tmp += "圣痕等级最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_TEAM_SKILL_TIMES_2:
        tmp += "MP团队技能次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_QTE_SKILL_TIMES_2:
        tmp += "MPQTE技能次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_BE_RESCUED_TIMES_2:
        tmp += "MP被拯救次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_RESCUE_TIMES_2:
        tmp += "MP拯救次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_AVG_RESCUE_TIME_2:
        tmp += "MP平均救援时间_2";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_CHAT_TIMES_2:
        tmp += "MP聊天次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ULTIMATE_SKILL_TIMES_2:
        tmp += "终极技能次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ULTIMATE_SKILL_DURATION_2:
        tmp += "终极技能持续时间_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ATTACK_SP_GAIN_2:
        tmp += "攻击获得SP_2";
        break;
    case Loaded::Logic::StageCheatData_Type::WEAPON_SKILL_TIMES_2:
        tmp += "武器技能次数_2";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::AVATAR_ID_3:
        tmp += "女武神ID_3";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_LEVEL_3:
        tmp += "女武神等级_3";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_COMBAT_3:
        tmp += "女武神战斗力_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ATTACK_MAX_3:
        tmp += "攻击最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_MAX_3:
        tmp += "SP最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_BEGIN_3:
        tmp += "SP初始值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_END_3:
        tmp += "SP结束值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_GAIN_3:
        tmp += "SP获得值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::SP_USE_3:
        tmp += "SP使用值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_MAX_3:
        tmp += "HP最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_BEGIN_3:
        tmp += "HP初始值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_END_3:
        tmp += "HP结束值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HP_GAIN_3:
        tmp += "HP获得值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_COUNT_3:
        tmp += "命中次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_DAMAGE_3:
        tmp += "命中伤害_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_NORMAL_DAMAGE_MAX_3:
        tmp += "正常伤害最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::HIT_CRITICAL_DAMAGE_MAX_3:
        tmp += "暴击伤害最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_COUNT_3:
        tmp += "被击中次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_NORMAL_DAMAGE_MAX_3:
        tmp += "被击中的正常伤害最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::BEHIT_CRITICAL_DAMAGE_MAX_3:
        tmp += "被击中的暴击伤害最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::COMBO_MAX_3:
        tmp += "连击最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::AVATAR_TIME_USE_3:
        tmp += "女武神使用时间_3";
        break;
    case Loaded::Logic::StageCheatData_Type::WEAPON_LEVEL_3:
        tmp += "武器等级_3";
        break;
    case Loaded::Logic::StageCheatData_Type::STIGMATA_LEVEL_MAX_3:
        tmp += "圣痕等级最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_TEAM_SKILL_TIMES_3:
        tmp += "MP团队技能次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_QTE_SKILL_TIMES_3:
        tmp += "MPQTE技能次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_BE_RESCUED_TIMES_3:
        tmp += "MP被拯救次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_RESCUE_TIMES_3:
        tmp += "MP拯救次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_AVG_RESCUE_TIME_3:
        tmp += "MP平均救援时间_3";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_CHAT_TIMES_3:
        tmp += "MP聊天次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ULTIMATE_SKILL_TIMES_3:
        tmp += "终极技能次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ULTIMATE_SKILL_DURATION_3:
        tmp += "终极技能持续时间_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ATTACK_SP_GAIN_3:
        tmp += "攻击获得SP_3";
        break;
    case Loaded::Logic::StageCheatData_Type::WEAPON_SKILL_TIMES_3:
        tmp += "武器技能次数_3";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::ELF_ID:
        tmp += "人偶ID_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_LEVEL:
        tmp += "人偶等级_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_COMBAT:
        tmp += "人偶战斗力_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_ATTACK:
        tmp += "人偶攻击_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_SP_MAX:
        tmp += "人偶SP最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_ULTIMATE_SKILL_TIMES:
        tmp += "人偶终极技能次数_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_SP_USE:
        tmp += "人偶SP使用值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_HIT_CRITICAL_DAMAGE_MAX:
        tmp += "人偶暴击伤害最大值_1";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_HIT_NORMAL_DAMAGE_MAX:
        tmp += "人偶正常伤害最大值_1";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::ELF_ID_2:
        tmp += "人偶ID_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_LEVEL_2:
        tmp += "人偶等级_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_COMBAT_2:
        tmp += "人偶战斗力_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_ATTACK_2:
        tmp += "人偶攻击_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_SP_MAX_2:
        tmp += "人偶SP最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_ULTIMATE_SKILL_TIMES_2:
        tmp += "人偶终极技能次数_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_SP_USE_2:
        tmp += "人偶SP使用值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_HIT_CRITICAL_DAMAGE_MAX_2:
        tmp += "人偶暴击伤害最大值_2";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_HIT_NORMAL_DAMAGE_MAX_2:
        tmp += "人偶正常伤害最大值_2";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::ELF_ID_3:
        tmp += "人偶ID_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_LEVEL_3:
        tmp += "人偶等级_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_COMBAT_3:
        tmp += "人偶战斗力_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_ATTACK_3:
        tmp += "人偶攻击_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_SP_MAX_3:
        tmp += "人偶SP最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_ULTIMATE_SKILL_TIMES_3:
        tmp += "人偶终极技能次数_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_SP_USE_3:
        tmp += "人偶SP使用值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_HIT_CRITICAL_DAMAGE_MAX_3:
        tmp += "人偶暴击伤害最大值_3";
        break;
    case Loaded::Logic::StageCheatData_Type::ELF_HIT_NORMAL_DAMAGE_MAX_3:
        tmp += "人偶正常伤害最大值_3";
        break;
    //////////////////////////////////////
    case Loaded::Logic::StageCheatData_Type::IS_MP_VOICE_USED:
        tmp += "是否使用MP语音";
        break;
    case Loaded::Logic::StageCheatData_Type::MP_VOICE_USE_TIME:
        tmp += "MP语音使用时间";
        break;
    case Loaded::Logic::StageCheatData_Type::SEALED_EVENT_ID:
        tmp += "密封事件ID";
        break;
    }

    tmp += "]: ";
    tmp += ToString(value);
    return tmp;
}

// 解析EntityNature
std::string Hook::Uitls::ParseEntityNature(Loaded::Logic::EntityNature type)
{
    std::string tmp = "EntityNature[";
    switch (type)
    {
    case Loaded::Logic::EntityNature::Pure:
        tmp += "纯净";
        break;
    case Loaded::Logic::EntityNature::Biology:
        tmp += "生物";
        break;
    case Loaded::Logic::EntityNature::Psycho:
        tmp += "异能";
        break;
    case Loaded::Logic::EntityNature::Mechanic:
        tmp += "机械";
        break;
    case Loaded::Logic::EntityNature::Quantum:
        tmp += "量子";
        break;
    case Loaded::Logic::EntityNature::Imaginary:
        tmp += "虚数";
        break;
    case Loaded::Logic::EntityNature::Count:
        tmp += "??";
        break;
    }

    tmp += "]";
    return tmp;
}
#endif
