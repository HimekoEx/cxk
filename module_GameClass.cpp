#include "module.h"
#include "module_GameClass.h"

//打印StageCheatData数据
void StageCheatData_Print(StageCheatData_Type type, float value)
{
    std::string tmp = "StageCheatData[";
    switch (type)
    {
    case STAGE_ID:
        tmp += "阶段ID";
        break;
    case STAGE_PROGRESS:
        tmp += "阶段进展";
        break;
    case STAGE_MAX_SCORE:
        tmp += "阶段最大分数";
        break;
    case TIME_START:
        tmp += "时间开始";
        break;
    case TIME_USE:
        tmp += "使用时间";
        break;
    case AVG_FRAME_TIME:
        tmp += "平均帧时间";
        break;
    case PLAYER_LEVEL:
        tmp += "玩家等级";
        break;
    case STAGE_SCORE:
        tmp += "阶段分数";
        break;
    //////////////////////////////////////
    case AVATAR_ID_1:
        tmp += "女武神ID_1";
        break;
    case AVATAR_LEVEL_1:
        tmp += "女武神等级_1";
        break;
    case AVATAR_COMBAT_1:
        tmp += "女武神战斗力_1";
        break;
    case ATTACK_MAX_1:
        tmp += "攻击最大值_1";
        break;
    case SP_MAX_1:
        tmp += "SP最大值_1";
        break;
    case SP_BEGIN_1:
        tmp += "SP初始值_1";
        break;
    case SP_END_1:
        tmp += "SP结束值_1";
        break;
    case SP_GAIN_1:
        tmp += "SP获得值_1";
        break;
    case SP_USE_1:
        tmp += "SP使用值_1";
        break;
    case HP_MAX_1:
        tmp += "HP最大值_1";
        break;
    case HP_BEGIN_1:
        tmp += "HP初始值_1";
        break;
    case HP_END_1:
        tmp += "HP结束值_1";
        break;
    case HP_GAIN_1:
        tmp += "HP获得值_1";
        break;
    case HIT_COUNT_1:
        tmp += "命中次数_1";
        break;
    case HIT_DAMAGE_1:
        tmp += "命中伤害_1";
        break;
    case HIT_NORMAL_DAMAGE_MAX_1:
        tmp += "正常伤害最大值_1";
        break;
    case HIT_CRITICAL_DAMAGE_MAX_1:
        tmp += "暴击伤害最大值_1";
        break;
    case BEHIT_COUNT_1:
        tmp += "被击中次数_1";
        break;
    case BEHIT_NORMAL_DAMAGE_MAX_1:
        tmp += "被击中的正常伤害最大值_1";
        break;
    case BEHIT_CRITICAL_DAMAGE_MAX_1:
        tmp += "被击中的暴击伤害最大值_1";
        break;
    case COMBO_MAX_1:
        tmp += "连击最大值_1";
        break;
    case AVATAR_TIME_USE_1:
        tmp += "女武神使用时间_1";
        break;
    case WEAPON_LEVEL_1:
        tmp += "武器等级_1";
        break;
    case STIGMATA_LEVEL_MAX_1:
        tmp += "圣痕等级最大值_1";
        break;
    case MP_TEAM_SKILL_TIMES_1:
        tmp += "MP团队技能次数_1";
        break;
    case MP_QTE_SKILL_TIMES_1:
        tmp += "MPQTE技能次数_1";
        break;
    case MP_BE_RESCUED_TIMES_1:
        tmp += "MP被拯救次数_1";
        break;
    case MP_RESCUE_TIMES_1:
        tmp += "MP拯救次数_1";
        break;
    case MP_AVG_RESCUE_TIME_1:
        tmp += "MP平均救援时间_1";
        break;
    case MP_CHAT_TIMES_1:
        tmp += "MP聊天次数_1";
        break;
    case ULTIMATE_SKILL_TIMES_1:
        tmp += "终极技能次数_1";
        break;
    case ULTIMATE_SKILL_DURATION_1:
        tmp += "终极技能持续时间_1";
        break;
    case ATTACK_SP_GAIN_1:
        tmp += "攻击获得SP_1";
        break;
    case WEAPON_SKILL_TIMES_1:
        tmp += "武器技能次数_1";
        break;
    //////////////////////////////////////
    case AVATAR_ID_2:
        tmp += "女武神ID_2";
        break;
    case AVATAR_LEVEL_2:
        tmp += "女武神等级_2";
        break;
    case AVATAR_COMBAT_2:
        tmp += "女武神战斗力_2";
        break;
    case ATTACK_MAX_2:
        tmp += "攻击最大值_2";
        break;
    case SP_MAX_2:
        tmp += "SP最大值_2";
        break;
    case SP_BEGIN_2:
        tmp += "SP初始值_2";
        break;
    case SP_END_2:
        tmp += "SP结束值_2";
        break;
    case SP_GAIN_2:
        tmp += "SP获得值_2";
        break;
    case SP_USE_2:
        tmp += "SP使用值_2";
        break;
    case HP_MAX_2:
        tmp += "HP最大值_2";
        break;
    case HP_BEGIN_2:
        tmp += "HP初始值_2";
        break;
    case HP_END_2:
        tmp += "HP结束值_2";
        break;
    case HP_GAIN_2:
        tmp += "HP获得值_2";
        break;
    case HIT_COUNT_2:
        tmp += "命中次数_2";
        break;
    case HIT_DAMAGE_2:
        tmp += "命中伤害_2";
        break;
    case HIT_NORMAL_DAMAGE_MAX_2:
        tmp += "正常伤害最大值_2";
        break;
    case HIT_CRITICAL_DAMAGE_MAX_2:
        tmp += "暴击伤害最大值_2";
        break;
    case BEHIT_COUNT_2:
        tmp += "被击中次数_2";
        break;
    case BEHIT_NORMAL_DAMAGE_MAX_2:
        tmp += "被击中的正常伤害最大值_2";
        break;
    case BEHIT_CRITICAL_DAMAGE_MAX_2:
        tmp += "被击中的暴击伤害最大值_2";
        break;
    case COMBO_MAX_2:
        tmp += "连击最大值_2";
        break;
    case AVATAR_TIME_USE_2:
        tmp += "女武神使用时间_2";
        break;
    case WEAPON_LEVEL_2:
        tmp += "武器等级_2";
        break;
    case STIGMATA_LEVEL_MAX_2:
        tmp += "圣痕等级最大值_2";
        break;
    case MP_TEAM_SKILL_TIMES_2:
        tmp += "MP团队技能次数_2";
        break;
    case MP_QTE_SKILL_TIMES_2:
        tmp += "MPQTE技能次数_2";
        break;
    case MP_BE_RESCUED_TIMES_2:
        tmp += "MP被拯救次数_2";
        break;
    case MP_RESCUE_TIMES_2:
        tmp += "MP拯救次数_2";
        break;
    case MP_AVG_RESCUE_TIME_2:
        tmp += "MP平均救援时间_2";
        break;
    case MP_CHAT_TIMES_2:
        tmp += "MP聊天次数_2";
        break;
    case ULTIMATE_SKILL_TIMES_2:
        tmp += "终极技能次数_2";
        break;
    case ULTIMATE_SKILL_DURATION_2:
        tmp += "终极技能持续时间_2";
        break;
    case ATTACK_SP_GAIN_2:
        tmp += "攻击获得SP_2";
        break;
    case WEAPON_SKILL_TIMES_2:
        tmp += "武器技能次数_2";
        break;
    //////////////////////////////////////
    case AVATAR_ID_3:
        tmp += "女武神ID_3";
        break;
    case AVATAR_LEVEL_3:
        tmp += "女武神等级_3";
        break;
    case AVATAR_COMBAT_3:
        tmp += "女武神战斗力_3";
        break;
    case ATTACK_MAX_3:
        tmp += "攻击最大值_3";
        break;
    case SP_MAX_3:
        tmp += "SP最大值_3";
        break;
    case SP_BEGIN_3:
        tmp += "SP初始值_3";
        break;
    case SP_END_3:
        tmp += "SP结束值_3";
        break;
    case SP_GAIN_3:
        tmp += "SP获得值_3";
        break;
    case SP_USE_3:
        tmp += "SP使用值_3";
        break;
    case HP_MAX_3:
        tmp += "HP最大值_3";
        break;
    case HP_BEGIN_3:
        tmp += "HP初始值_3";
        break;
    case HP_END_3:
        tmp += "HP结束值_3";
        break;
    case HP_GAIN_3:
        tmp += "HP获得值_3";
        break;
    case HIT_COUNT_3:
        tmp += "命中次数_3";
        break;
    case HIT_DAMAGE_3:
        tmp += "命中伤害_3";
        break;
    case HIT_NORMAL_DAMAGE_MAX_3:
        tmp += "正常伤害最大值_3";
        break;
    case HIT_CRITICAL_DAMAGE_MAX_3:
        tmp += "暴击伤害最大值_3";
        break;
    case BEHIT_COUNT_3:
        tmp += "被击中次数_3";
        break;
    case BEHIT_NORMAL_DAMAGE_MAX_3:
        tmp += "被击中的正常伤害最大值_3";
        break;
    case BEHIT_CRITICAL_DAMAGE_MAX_3:
        tmp += "被击中的暴击伤害最大值_3";
        break;
    case COMBO_MAX_3:
        tmp += "连击最大值_3";
        break;
    case AVATAR_TIME_USE_3:
        tmp += "女武神使用时间_3";
        break;
    case WEAPON_LEVEL_3:
        tmp += "武器等级_3";
        break;
    case STIGMATA_LEVEL_MAX_3:
        tmp += "圣痕等级最大值_3";
        break;
    case MP_TEAM_SKILL_TIMES_3:
        tmp += "MP团队技能次数_3";
        break;
    case MP_QTE_SKILL_TIMES_3:
        tmp += "MPQTE技能次数_3";
        break;
    case MP_BE_RESCUED_TIMES_3:
        tmp += "MP被拯救次数_3";
        break;
    case MP_RESCUE_TIMES_3:
        tmp += "MP拯救次数_3";
        break;
    case MP_AVG_RESCUE_TIME_3:
        tmp += "MP平均救援时间_3";
        break;
    case MP_CHAT_TIMES_3:
        tmp += "MP聊天次数_3";
        break;
    case ULTIMATE_SKILL_TIMES_3:
        tmp += "终极技能次数_3";
        break;
    case ULTIMATE_SKILL_DURATION_3:
        tmp += "终极技能持续时间_3";
        break;
    case ATTACK_SP_GAIN_3:
        tmp += "攻击获得SP_3";
        break;
    case WEAPON_SKILL_TIMES_3:
        tmp += "武器技能次数_3";
        break;
    //////////////////////////////////////
    case ELF_ID:
        tmp += "女儿ID_1";
        break;
    case ELF_LEVEL:
        tmp += "女儿等级_1";
        break;
    case ELF_COMBAT:
        tmp += "女儿战斗力_1";
        break;
    case ELF_ATTACK:
        tmp += "女儿攻击_1";
        break;
    case ELF_SP_MAX:
        tmp += "女儿SP最大值_1";
        break;
    case ELF_ULTIMATE_SKILL_TIMES:
        tmp += "女儿终极技能次数_1";
        break;
    case ELF_SP_USE:
        tmp += "女儿SP使用值_1";
        break;
    case ELF_HIT_CRITICAL_DAMAGE_MAX:
        tmp += "女儿暴击伤害最大值_1";
        break;
    case ELF_HIT_NORMAL_DAMAGE_MAX:
        tmp += "女儿正常伤害最大值_1";
        break;
    //////////////////////////////////////
    case ELF_ID_2:
        tmp += "女儿ID_2";
        break;
    case ELF_LEVEL_2:
        tmp += "女儿等级_2";
        break;
    case ELF_COMBAT_2:
        tmp += "女儿战斗力_2";
        break;
    case ELF_ATTACK_2:
        tmp += "女儿攻击_2";
        break;
    case ELF_SP_MAX_2:
        tmp += "女儿SP最大值_2";
        break;
    case ELF_ULTIMATE_SKILL_TIMES_2:
        tmp += "女儿终极技能次数_2";
        break;
    case ELF_SP_USE_2:
        tmp += "女儿SP使用值_2";
        break;
    case ELF_HIT_CRITICAL_DAMAGE_MAX_2:
        tmp += "女儿暴击伤害最大值_2";
        break;
    case ELF_HIT_NORMAL_DAMAGE_MAX_2:
        tmp += "女儿正常伤害最大值_2";
        break;
    //////////////////////////////////////
    case ELF_ID_3:
        tmp += "女儿ID_3";
        break;
    case ELF_LEVEL_3:
        tmp += "女儿等级_3";
        break;
    case ELF_COMBAT_3:
        tmp += "女儿战斗力_3";
        break;
    case ELF_ATTACK_3:
        tmp += "女儿攻击_3";
        break;
    case ELF_SP_MAX_3:
        tmp += "女儿SP最大值_3";
        break;
    case ELF_ULTIMATE_SKILL_TIMES_3:
        tmp += "女儿终极技能次数_3";
        break;
    case ELF_SP_USE_3:
        tmp += "女儿SP使用值_3";
        break;
    case ELF_HIT_CRITICAL_DAMAGE_MAX_3:
        tmp += "女儿暴击伤害最大值_3";
        break;
    case ELF_HIT_NORMAL_DAMAGE_MAX_3:
        tmp += "女儿正常伤害最大值_3";
        break;
    //////////////////////////////////////
    case IS_MP_VOICE_USED:
        tmp += "是否使用MP语音";
        break;
    case MP_VOICE_USE_TIME:
        tmp += "MP语音使用时间";
        break;
    case SEALED_EVENT_ID:
        tmp += "密封事件ID";
        break;
    }

    tmp += "]: ";
    LOGE("%s%f", tmp.c_str(), value);
}