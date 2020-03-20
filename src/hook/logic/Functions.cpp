#include "src/hook/hook.h"
#include "src/sync/sync.h"
#include "src/verify/verify.h"
using namespace MiHoYoSDK;
using namespace MiHoYoSDK::StaticData;
using namespace Hook::Loaded;
using namespace Hook::Loaded::Il2cpp;
using Sync::GetStateOrValue;

static bool GUID_LOCK = false;

//网络管理器$$获取持久UUID
Il2CppString *(*Logic::_NetworkManager_GetPersistentUUID)(Il2CppObject *) = nullptr;
Il2CppString *Logic::NetworkManager_GetPersistentUUID(Il2CppObject *self)
{
    Il2CppString *result = _NetworkManager_GetPersistentUUID(self);
    if (!GUID_LOCK && (GUID_LOCK = true))
    {
        CSharpString css = result;
        LOGE("GetPersistentUUID: [%s]", css.c_str());

        Json::Value root;
        root[GET_SAFE_DATA(STR_guid)] = css.get();
        root[GET_SAFE_DATA(STR_chaos)] = Verify::GetChaosMD5().get();
        root[GET_SAFE_DATA(STR_cybl)] = Verify::GetCyBLMD5().get();
        root[GET_SAFE_DATA(STR_apk)] = Verify::GetAPKMD5().get();

        Bytes raw = SendJSON(GET_SAFE_CHAR(STR_gameLogin), root);
        if (Verify::VerifyFileByJson(raw))
            CCC("VerifyFileByJson Error");
    }

    return result;
}

//MTP$$Tp2用户登录
void (*Logic::_MonoMTP_Tp2UserLogin)(Il2CppObject *, Tp2Entry, int, Il2CppString *, Il2CppString *) = nullptr;
void Logic::MonoMTP_Tp2UserLogin(Il2CppObject *self, Tp2Entry accountType, int worldID, Il2CppString *openID, Il2CppString *roleID)
{
    CSharpString opID = openID;
    CSharpString roID = roleID;
    LOGE("Tp2UserLogin[accountType: %d, worldID: %d, openID: %s, roleID: %s]", accountType, worldID, opID.c_str(), roID.c_str());

    return _MonoMTP_Tp2UserLogin(self, accountType, worldID, openID, roleID);
}

//SafeFloat$$获取值
float (*Logic::_SafeFloat_get_Value)(Il2CppObject *) = nullptr;
float Logic::SafeFloat_get_Value(Il2CppObject *self)
{
    return _SafeFloat_get_Value(self);
}

//SafeFloat$$设置值
void (*Logic::_SafeFloat_set_Value)(Il2CppObject *, float) = nullptr;
void Logic::SafeFloat_set_Value(Il2CppObject *self, float value)
{
    return _SafeFloat_set_Value(self, value);
}

//关卡反作弊插件&&收集反作弊数据
void (*Logic::_LevelAntiCheatPlugin_CollectAntiCheatData)(Il2CppObject *, bool) = nullptr;
void Logic::LevelAntiCheatPlugin_CollectAntiCheatData(Il2CppObject *self, bool isMultiTeam)
{
    return _LevelAntiCheatPlugin_CollectAntiCheatData(self, isMultiTeam);
}

//关卡反作弊插件&&添加数据
void (*Logic::_LevelAntiCheatPlugin_AddData)(Il2CppObject *, StageCheatData_Type, float) = nullptr;
void Logic::LevelAntiCheatPlugin_AddData(Il2CppObject *self, StageCheatData_Type type, float value)
{
    switch (type)
    {
    case StageCheatData_Type::HP_GAIN_1:
    case StageCheatData_Type::HP_GAIN_2:
    case StageCheatData_Type::HP_GAIN_3:
        if (GetStateOrValue("吸血吸能", "", false) && GetStateOrValue("吸血吸能", "HP吸取", false))
            value *= GetStateOrValue("吸血吸能", "HP抑制率", 0.01f);
        break;
    case StageCheatData_Type::ATTACK_SP_GAIN_1:
    case StageCheatData_Type::ATTACK_SP_GAIN_2:
    case StageCheatData_Type::ATTACK_SP_GAIN_3:
        if (GetStateOrValue("吸血吸能", "", false) && GetStateOrValue("吸血吸能", "SP吸取", false))
            value *= GetStateOrValue("吸血吸能", "SP抑制率", 1.0f);
        break;
    default:
        break;
    }

#ifndef RELEASE
    RT(Uitls::ParseStageCheatData(type, value));
#endif

    return _LevelAntiCheatPlugin_AddData(self, type, value);
}

// 限制女武神挑战$$是已完成
bool Logic::LimitAvatarChallege_IsFinished(Il2CppObject *self)
{
    return true;
}

// BaseMonoAvatar$$被击中
void Logic::BaseMonoAvatar_BeHit(Il2CppObject *self)
{
    return;
}

// Gal触摸模块$$获取是Gal触摸和谐
bool Logic::GalTouchModule_get_IsGalTouchHeXie(Il2CppObject *self)
{
    return false;
}

//女武神管理$$尝试获取当前女武神
Il2CppObject *(*Logic::_AvatarManager_TryGetLocalAvatar)(Il2CppObject *) = nullptr;
Il2CppObject *Logic::AvatarManager_TryGetLocalAvatar(Il2CppObject *self)
{
    Il2CppObject *avatar = _AvatarManager_TryGetLocalAvatar(self);

    bool *isAutoBattle = (bool *)((char *)self + 0x10);
    bool tmp = GetStateOrValue("自动攻击", "", false);
    if (*isAutoBattle != tmp)
    {
        *isAutoBattle = tmp;
        if (avatar != nullptr)
            BaseMonoAvatar_RefreshController(avatar);
    }

    return avatar;
}

//BaseMonoAvatar$$刷新控制器
void (*Logic::_BaseMonoAvatar_RefreshController)(Il2CppObject *) = nullptr;
void Logic::BaseMonoAvatar_RefreshController(Il2CppObject *self)
{
    return _BaseMonoAvatar_RefreshController(self);
}

//BaseMonoMonster$$设置攻击目标
void (*Logic::_BaseMonoMonster_SetAttackTarget)(Il2CppObject *, Il2CppObject *) = nullptr;
void Logic::BaseMonoMonster_SetAttackTarget(Il2CppObject *self, Il2CppObject *newTarget)
{
    if (GetStateOrValue("定怪", "", false))
        newTarget = nullptr;

    return _BaseMonoMonster_SetAttackTarget(self, newTarget);
}

//基础能力角色$$可以造成伤害By运行时ID
bool (*Logic::_BaseAbilityActor_CanBeDamageByRuntimeid)(Il2CppObject *self, uint runtimeID) = nullptr;
bool Logic::BaseAbilityActor_CanBeDamageByRuntimeid(Il2CppObject *self, uint runtimeID)
{
    Il2CppObject *baseMonoActor = *(Il2CppObject **)((char *)self + 0x294);
    Il2CppClass *clazz = baseMonoActor->klass;

    for (; clazz != nullptr; clazz = clazz->parent)
    {
        if (String(clazz->name) == "BaseMonoAvatar")
        {
            if (GetStateOrValue("无伤", "", false))
                return false;

            break;
        }
        else if (String(clazz->name) == "BaseMonoEntity")
            break;
    }

    return _BaseAbilityActor_CanBeDamageByRuntimeid(self, runtimeID);
}

//基础能力角色$$回复SP
void (*Logic::_BaseAbilityActor_HealSP)(Il2CppObject *, float, LevelSPRecoverSource) = nullptr;
void Logic::BaseAbilityActor_HealSP(Il2CppObject *self, float amount, LevelSPRecoverSource source)
{
    Il2CppObject *maxSP = (Il2CppObject *)((char *)self + 0x158);
    Il2CppObject *SP = (Il2CppObject *)((char *)self + 0x178);

    Il2CppObject *baseMonoActor = *(Il2CppObject **)((char *)self + 0x294);
    Il2CppClass *clazz = baseMonoActor->klass;

    for (; clazz != nullptr; clazz = clazz->parent)
    {
        if (String(clazz->name) == "BaseMonoAvatar")
        {
            if (GetStateOrValue("无限SP", "", false))
                SafeFloat_set_Value(SP, SafeFloat_get_Value(maxSP));

            break;
        }
        else if (String(clazz->name) == "BaseMonoEntity")
            break;
    }

    return _BaseAbilityActor_HealSP(self, amount, source);
}

//MonoGoods$$更新
void (*Logic::_MonoGoods_Update)(Il2CppObject *) = nullptr;
void Logic::MonoGoods_Update(Il2CppObject *self)
{
    bool *forceFlyToAvatar = (bool *)((char *)self + 0x66);
    bool tmp = GetStateOrValue("强制吸掉落物", "", false);

    if (*forceFlyToAvatar != tmp)
        *forceFlyToAvatar = tmp;

    return _MonoGoods_Update(self);
}

//女武神角色$$可以使用技能
bool (*Logic::_AvatarActor_CanUseSkill)(Il2CppObject *, Il2CppString *) = nullptr;
bool Logic::AvatarActor_CanUseSkill(Il2CppObject *self, Il2CppString *skillName)
{
    if (GetStateOrValue("无CD", "", false))
        return true;

    return _AvatarActor_CanUseSkill(self, skillName);
}

//女武神角色$$是换人在CD中
bool (*Logic::_AvatarActor_IsSwitchInCD)(Il2CppObject *) = nullptr;
bool Logic::AvatarActor_IsSwitchInCD(Il2CppObject *self)
{
    if (GetStateOrValue("无CD", "", false))
        return false;

    return _AvatarActor_IsSwitchInCD(self);
}

//关卡设计管理$$战斗开始
void (*Logic::_LevelDesignManager_BattleBegin)(Il2CppObject *) = nullptr;
void Logic::LevelDesignManager_BattleBegin(Il2CppObject *self)
{
    _LevelDesignManager_BattleBegin(self);

    if (GetStateOrValue("速通系列", "进图结算", false))
        LevelDesignManager_EndLevel(self, LevelEndReason::EndWin, 0);
}

//关卡设计管理$$结束关卡
void (*Logic::_LevelDesignManager_EndLevel)(Il2CppObject *, LevelEndReason, int) = nullptr;
void Logic::LevelDesignManager_EndLevel(Il2CppObject *self, LevelEndReason reason, int endCgId)
{
    if (GetStateOrValue("速通系列", "退图结算", false) || GetStateOrValue("速通系列", "进图结算", false))
        reason = LevelEndReason::EndWin;

    return _LevelDesignManager_EndLevel(self, reason, endCgId);
}

//BaseMonoAvatar$$更新
void (*Logic::_BaseMonoAvatar_Update)(Il2CppObject *) = nullptr;
void Logic::BaseMonoAvatar_Update(Il2CppObject *self)
{
    if (GetStateOrValue("移速", "", false))
        BaseMonoAvatar_set_MoveSpeedRatio(self, GetStateOrValue("移速", "速率", 1.0f));

    return _BaseMonoAvatar_Update(self);
}

//BaseMonoAvatar$$设置移动速度倍率
void (*Logic::_BaseMonoAvatar_set_MoveSpeedRatio)(Il2CppObject *, float) = nullptr;
void Logic::BaseMonoAvatar_set_MoveSpeedRatio(Il2CppObject *self, float value)
{
    return _BaseMonoAvatar_set_MoveSpeedRatio(self, value);
}

//BaseMonoElf$$设置移动速度倍率
void (*Logic::_BaseMonoElf_set_MoveSpeedRatio)(Il2CppObject *, float) = nullptr;
void Logic::BaseMonoElf_set_MoveSpeedRatio(Il2CppObject *self, float value)
{
    if (GetStateOrValue("移速", "", false))
        value = GetStateOrValue("移速", "速率", 1.0f);

    return _BaseMonoElf_set_MoveSpeedRatio(self, value);
}

//女武神武器过热$$更新过热显示值
void (*Logic::_AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue)(Il2CppObject *, float, float) = nullptr;
void Logic::AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue(Il2CppObject *self, float fromHeat, float toHeat)
{
    float *_heat = (float *)((char *)self + 0x30);

    if (GetStateOrValue("过热冷却", "", false))
    {
        float differ = fromHeat - toHeat;

        if (differ > 0.0f) //冷却
            differ *= GetStateOrValue("过热冷却", "冷却倍率", 1.0f);
        else if (differ < 0.0f) //过热
            differ *= GetStateOrValue("过热冷却", "过热倍率", 1.0f);

        *_heat = toHeat = std::max<float>(fromHeat - differ, 0.0f);
    }

    return _AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue(self, fromHeat, toHeat);
}

//基础能力角色$$获取属性
float (*Logic::_BaseAbilityActor_GetProperty)(Il2CppObject *, Il2CppString *) = nullptr;
float Logic::BaseAbilityActor_GetProperty(Il2CppObject *self, Il2CppString *propertyKey)
{
    float result = _BaseAbilityActor_GetProperty(self, propertyKey);
    CSharpString css = propertyKey;

    Il2CppObject *maxSP = (Il2CppObject *)((char *)self + 0x158);
    Il2CppObject *SP = (Il2CppObject *)((char *)self + 0x178);

    Il2CppObject *maxHP = (Il2CppObject *)((char *)self + 0x148);
    Il2CppObject *HP = (Il2CppObject *)((char *)self + 0x168);

    Il2CppObject *baseMonoActor = *(Il2CppObject **)((char *)self + 0x294);
    Il2CppClass *clazz = baseMonoActor->klass;

    if (GetStateOrValue("吸血吸能", "", false))
    {
        for (; clazz != nullptr; clazz = clazz->parent)
        {
            if (String(clazz->name) == "BaseMonoAvatar")
            {
                if (GetStateOrValue("吸血吸能", "SP吸取", false) && css.get() == "Actor_SPRecoverRatio")
                {
                    float sp = SafeFloat_get_Value(SP);
                    float max = SafeFloat_get_Value(maxSP);

                    if (sp < max * GetStateOrValue("吸血吸能", "SP(低)阀值", 0.0f))
                        result = GetStateOrValue("吸血吸能", "SP(低)吸收率", 0.0f);
                    else if (sp < max * GetStateOrValue("吸血吸能", "SP(高)阀值", 0.0f))
                        result = GetStateOrValue("吸血吸能", "SP(中)吸收率", 0.0f);
                    else
                        result = GetStateOrValue("吸血吸能", "SP(高)吸收率", 0.0f);
                }
                else if (GetStateOrValue("吸血吸能", "HP吸取", false) && css.get() == "Actor_AttackStealHPRatio")
                {
                    float hp = SafeFloat_get_Value(HP);
                    float max = SafeFloat_get_Value(maxHP);

                    if (hp < max * GetStateOrValue("吸血吸能", "HP(低)阀值", 0.0f))
                        result = GetStateOrValue("吸血吸能", "HP(低)吸收率", 0.0f) * 0.001;
                    else if (hp < max * GetStateOrValue("吸血吸能", "HP(高)阀值", 0.0f))
                        result = GetStateOrValue("吸血吸能", "HP(中)吸收率", 0.0f) * 0.001;
                    else
                        result = GetStateOrValue("吸血吸能", "HP(高)吸收率", 0.0f) * 0.001;
                }

                break;
            }
            else if (String(clazz->name) == "BaseMonoEntity")
                break;
        }
    }

    return result;
}

//关卡设计管理$$设置暂停
void (*Logic::_LevelDesignManager_SetPause)(Il2CppObject *, bool) = nullptr;
void Logic::LevelDesignManager_SetPause(Il2CppObject *self, bool pause)
{
    if (pause && GetStateOrValue("暂停接口", "", false))
    {
        LOGE("SetPauseCall: %s", BoolToChar(pause));
        if (GetStateOrValue("暂停接口", "不灭钻石(H)", false) ||
            GetStateOrValue("暂停接口", "不灭钻石(S)", false) ||
            GetStateOrValue("暂停接口", "不灭钻石(H/S)", false))
            LevelDesignManager_SetAvatarDefenseRatio(self, 1.0f);
        else if (GetStateOrValue("暂停接口", "砸瓦鲁多", false))
            LevelDesignManager_KillAllMonstersIter(self, true, true, true);
        else if (GetStateOrValue("暂停接口", "食堂泼辣酱(R)", false) ||
                 GetStateOrValue("暂停接口", "食堂泼辣酱(V)", false))
            LevelDesignManager_ClearAllMonsters(self, true);
        else if (GetStateOrValue("暂停接口", "绯红之王", false))
            LevelDesignManager_SetInLevelTimeCountDownSpeedRatio(self, 1.0f, 1.0f);
    }

    return _LevelDesignManager_SetPause(self, pause);
}

//关卡设计管理$$设置女武神防御倍率
void (*Logic::_LevelDesignManager_SetAvatarDefenseRatio)(Il2CppObject *, float) = nullptr;
void Logic::LevelDesignManager_SetAvatarDefenseRatio(Il2CppObject *self, float ratio)
{
    return _LevelDesignManager_SetAvatarDefenseRatio(self, ratio);
}

//女武神角色$$设置女武神防御倍率
void (*Logic::_AvatarActor_SetAvatarDefenseRatio)(Il2CppObject *, float) = nullptr;
void Logic::AvatarActor_SetAvatarDefenseRatio(Il2CppObject *self, float ratio)
{
    Il2CppObject *maxSP = (Il2CppObject *)((char *)self + 0x158);
    Il2CppObject *SP = (Il2CppObject *)((char *)self + 0x178);

    Il2CppObject *maxHP = (Il2CppObject *)((char *)self + 0x148);
    Il2CppObject *HP = (Il2CppObject *)((char *)self + 0x168);

    if (GetStateOrValue("暂停接口", "不灭钻石(H)", false))
    {
        // float hp = SafeFloat_get_Value(HP);
        float max = SafeFloat_get_Value(maxHP);
        SafeFloat_set_Value(HP, max);
        // LOGE("HP: %0.3f, maxHP: %0.3f, newHP: %0.3f", hp, max, max);
    }
    else if (GetStateOrValue("暂停接口", "不灭钻石(S)", false))
    {
        // float sp = SafeFloat_get_Value(SP);
        float max = SafeFloat_get_Value(maxSP);
        SafeFloat_set_Value(SP, max);
        // LOGE("SP: %0.3f, maxSP: %0.3f, newSP: %0.3f", sp, max, max);
    }
    else if (GetStateOrValue("暂停接口", "不灭钻石(H/S)", false))
    {
        // float hp = SafeFloat_get_Value(HP);
        float max_hp = SafeFloat_get_Value(maxHP);
        SafeFloat_set_Value(HP, max_hp);
        // LOGE("1:HP: %0.3f, maxHP: %0.3f, newHP: %0.3f", hp, max_hp, max_hp);

        // float sp = SafeFloat_get_Value(SP);
        float max_sp = SafeFloat_get_Value(maxSP);
        SafeFloat_set_Value(SP, max_sp);
        // LOGE("2:SP: %0.3f, maxSP: %0.3f, newSP: %0.3f", sp, max_sp, max_sp);
    }

    return _AvatarActor_SetAvatarDefenseRatio(self, ratio);
}

//关卡设计管理$$击杀所有怪物Iter
void (*Logic::_LevelDesignManager_KillAllMonstersIter)(Il2CppObject *, bool, bool, bool) = nullptr;
void Logic::LevelDesignManager_KillAllMonstersIter(
    Il2CppObject *self, bool dropReward, bool killStatic, bool killUnacitve)
{
    return _LevelDesignManager_KillAllMonstersIter(self, dropReward, killStatic, killUnacitve);
}

//关卡设计管理$$清除所有怪物
void (*Logic::_LevelDesignManager_ClearAllMonsters)(Il2CppObject *, bool) = nullptr;
void Logic::LevelDesignManager_ClearAllMonsters(Il2CppObject *self, bool clearStatic)
{
    return _LevelDesignManager_ClearAllMonsters(self, clearStatic);
}

//怪物角色$$立即强制移除
void (*Logic::_MonsterActor_ForceRemoveImmediatelly)(Il2CppObject *) = nullptr;
void Logic::MonsterActor_ForceRemoveImmediatelly(Il2CppObject *self)
{
    Il2CppObject *HP = (Il2CppObject *)((char *)self + 0x168);

    if (GetStateOrValue("暂停接口", "食堂泼辣酱(R)", false))
    {
        float hp = SafeFloat_get_Value(HP);
        float new_hp = hp - (hp * GetStateOrValue("暂停接口", "倍率", 0.0f));

        SafeFloat_set_Value(HP, new_hp);
        // LOGE("Monster[hp: %0.3f, newHP: %0.3f]", hp, new_hp);
        return;
    }
    else if (GetStateOrValue("暂停接口", "食堂泼辣酱(V)", false))
    {
        float hp = SafeFloat_get_Value(HP);
        float new_hp = GetStateOrValue("暂停接口", "值", hp);

        SafeFloat_set_Value(HP, new_hp);
        // LOGE("Monster[hp: %0.3f, newHP: %0.3f]", hp, new_hp);
        return;
    }

    return _MonsterActor_ForceRemoveImmediatelly(self);
}

//关卡设计管理$$设置关卡内时间下降速度倍率
void (*Logic::_LevelDesignManager_SetInLevelTimeCountDownSpeedRatio)(Il2CppObject *, float, float) = nullptr;
void Logic::LevelDesignManager_SetInLevelTimeCountDownSpeedRatio(Il2CppObject *self, float ratioInNormalTime, float ratioInWitchTime)
{
    return _LevelDesignManager_SetInLevelTimeCountDownSpeedRatio(self, ratioInNormalTime, ratioInWitchTime);
}

//关卡角色倒计时插件$$设置倒计时速度倍率
void (*Logic::_LevelActorCountDownPlugin_SetCountDownSpeedRatio)(Il2CppObject *, float, float) = nullptr;
void Logic::LevelActorCountDownPlugin_SetCountDownSpeedRatio(Il2CppObject *self, float ratioInNormalTime, float ratioInWitchTime)
{
    Il2CppObject *totalTime = (Il2CppObject *)((char *)self + 0x10);
    Il2CppObject *countDownTimer = (Il2CppObject *)((char *)self + 0x20);

    float *speedRatioInNormalTime = (float *)((char *)self + 0x40);
    float *speedRatioInWitchTime = (float *)((char *)self + 0x44);

    if (GetStateOrValue("暂停接口", "绯红之王", false))
    {
        //还原值
        ratioInNormalTime = (*speedRatioInNormalTime == 0.0f ? 1.0f : *speedRatioInNormalTime);
        ratioInWitchTime = (*speedRatioInWitchTime == 0.0f ? 1.0f : *speedRatioInWitchTime);

        if (GetStateOrValue("暂停接口", "复位", false))
            SafeFloat_set_Value(countDownTimer, SafeFloat_get_Value(totalTime));
        else if (GetStateOrValue("暂停接口", "清零", false))
            SafeFloat_set_Value(countDownTimer, 1.0f);
        else
        {
            float pass = GetStateOrValue("暂停接口", "流逝速度", 1.0f);
            if (pass != 1.0f)
                ratioInNormalTime = ratioInWitchTime = pass;
        }
    }

    return _LevelActorCountDownPlugin_SetCountDownSpeedRatio(self, ratioInNormalTime, ratioInWitchTime);
}

//BaseMonoAvatar$$获取固定攻击速度倍率
float (*Logic::_BaseMonoAvatar_GetFixedAttackSpeedRatio)(Il2cpp::Il2CppObject *) = nullptr;
float Logic::BaseMonoAvatar_GetFixedAttackSpeedRatio(Il2cpp::Il2CppObject *self)
{
    float reslut = _BaseMonoAvatar_GetFixedAttackSpeedRatio(self);

    if (GetStateOrValue("攻速", "", false))
    {
        float add = GetStateOrValue("攻速", "增值倍率", 1.0f);
        if (add > 1.0f)
            return reslut * add;

        float fixed = GetStateOrValue("攻速", "固定倍率", 0.0f);
        if (fixed > 0.0f)
            return fixed;
    }

    return reslut;
}

//角色能力插件$$获取动态浮点
Il2CppObject *(*Logic::_ActorAbilityPlugin_GetDynamicFloat)(Il2CppObject *, Il2CppString *) = nullptr;
Il2CppObject *Logic::ActorAbilityPlugin_GetDynamicFloat(Il2CppObject *self, Il2CppString *key)
{
    return _ActorAbilityPlugin_GetDynamicFloat(self, key);
}

//角色能力插件$$添加动态浮点
void (*Logic::_ActorAbilityPlugin_AddDynamicFloat)(Il2CppObject *, Il2CppString *, float) = nullptr;
void Logic::ActorAbilityPlugin_AddDynamicFloat(Il2CppObject *self, Il2CppString *key, float value)
{
    CSharpString css = key;
    LOGE("AddDynamicFloat: key[%s] value[%0.3f]", css.c_str(), value);

    return _ActorAbilityPlugin_AddDynamicFloat(self, key, value);
}

//角色能力插件$$添加动态浮点
void (*Logic::_ActorAbilityPlugin_AddDynamicFloatWithRange)(Il2CppObject *, Il2CppString *, float, float, float) = nullptr;
void Logic::ActorAbilityPlugin_AddDynamicFloatWithRange(Il2CppObject *self, Il2CppString *key, float value, float min, float max)
{
    CSharpString css = key;

    if (GetStateOrValue("角色动能", "", false))
    {
        // Il2CppObject *DynamicActorValue = ActorAbilityPlugin_GetDynamicFloat(self, key);
        // float *Dvalue = (float *)((char *)DynamicActorValue + 0x8);
        // LOGE("///AddDynamic: key[%s] Dv[%3.3f] value[%3.3f] min[%3.3f] max[%3.3f]", css.c_str(), *Dvalue, value, min, max);

        Il2CppObject *_owner = *(Il2CppObject **)((char *)self + 0xC);
        Il2CppObject *baseMonoActor = *(Il2CppObject **)((char *)_owner + 0x294);
        Il2CppClass *clazz = baseMonoActor->klass;

        // int count = 0;
        // LOGE("///STA///");
        for (; clazz != nullptr; clazz = clazz->parent)
        {
            // LOGE("(%d)class name: [%s]", ++count, clazz->name);
            if (String(clazz->name) == "BaseMonoAvatar")
            {
                if (css.get() == "_GLOBAL_DQ_FROST_VALUE")
                {
                    value = min;
                    break;
                }

                if (value < 0) //减值
                {
                    float add = GetStateOrValue("角色动能", "减值倍率", 1.0f);
                    if (add < 1.0f)
                        value *= add;
                }
                else if (value > 0) //增值
                {
                    float sub = GetStateOrValue("角色动能", "增值倍率", 1.0f);
                    if (sub > 1.0f)
                        value *= sub;
                }

                // LOGE("\\\\\\AddDynamic: key[%s] Dv[%3.3f] value[%3.3f] min[%3.3f] max[%3.3f]", css.c_str(), *Dvalue, value, min, max);
                break;
            }
            else if (String(clazz->name) == "BaseMonoEntity")
                break;
        }
        // LOGE("///END///");
    }

    return _ActorAbilityPlugin_AddDynamicFloatWithRange(self, key, value, min, max);
}

//护盾能力插件$$在护盾改变
void (*Logic::_AbilityShieldMixin_OnShieldChanged)(Il2CppObject *, float, float) = nullptr;
void Logic::AbilityShieldMixin_OnShieldChanged(Il2CppObject *self, float from, float to)
{
    float *shield = (float *)((char *)self + 0x2C);
    Il2CppObject *_forceResumeTimer = *(Il2CppObject **)((char *)self + 0x34);
    Il2CppObject *_minForceResumeTimer = *(Il2CppObject **)((char *)self + 0x38);
    Il2CppObject *_shieldResumeTimer = *(Il2CppObject **)((char *)self + 0x3C);
    float *timespan = nullptr;

    if (GetStateOrValue("破甲", "", false))
    {
        float differ = from - to;
        if (differ > 0.0f) //减少
            differ *= GetStateOrValue("破甲", "减值倍率", 1.0f);
        *shield = to = std::max<float>(from - differ, 0.0f);

        float new_timespan = GetStateOrValue("破甲", "盾恢复时间", 0.0f);
        if (new_timespan > 0.0f)
        {
            timespan = (float *)((char *)_forceResumeTimer + 0x18);
            *timespan = new_timespan;

            timespan = (float *)((char *)_minForceResumeTimer + 0x18);
            *timespan = new_timespan;

            timespan = (float *)((char *)_shieldResumeTimer + 0x18);
            *timespan = new_timespan;
        }
    }

    return _AbilityShieldMixin_OnShieldChanged(self, from, to);
}

//攻击结果$$获取总量伤害
float (*Logic::_AttackResult_GetTotalDamage)(Il2CppObject *) = nullptr;
float Logic::AttackResult_GetTotalDamage(Il2CppObject *self)
{
    return _AttackResult_GetTotalDamage(self);
}

//怪物角色$$在被击中解决
bool (*Logic::_MonsterActor_OnBeingHitResolve)(Il2CppObject *, Il2CppObject *) = nullptr;
bool Logic::MonsterActor_OnBeingHitResolve(Il2CppObject *self, Il2CppObject *evt)
{
    bool result = _MonsterActor_OnBeingHitResolve(self, evt);

    Il2CppObject *maxHP = (Il2CppObject *)((char *)self + 0x148);
    Il2CppObject *HP = (Il2CppObject *)((char *)self + 0x168);

    Il2CppObject *attackData = *(Il2CppObject **)((char *)evt + 0x30);

    if (GetStateOrValue("超限模式", "", false))
    {
        float max_hp = SafeFloat_get_Value(maxHP);
        float hp = SafeFloat_get_Value(HP);

        if (hp > max_hp * GetStateOrValue("超限模式", "阀值", 0.5f))
        {
            float totalDamage = AttackResult_GetTotalDamage(attackData);
            if (totalDamage > 0)
            {
                float newHp = hp;
                if (GetStateOrValue("超限模式", "红眼模式", false))
                    newHp = std::max<float>(newHp - totalDamage * (GetStateOrValue("超限模式", "红眼倍率", 1.0f) - 1.0f), 0.0f);
                else if (GetStateOrValue("超限模式", "心跳模式", false))
                    newHp = std::max<float>(newHp * GetStateOrValue("超限模式", "心跳倍率", 0.98f), 0.0f);

                SafeFloat_set_Value(HP, newHp);
                LOGE("-------------");
                LOGE("toDmg := %0.2f", totalDamage);
                LOGE("orgHp := %0.2f", hp);
                LOGE("newHp := %0.2f", newHp);
                LOGE("doDmg := %0.2f", hp - newHp);
                LOGE("-------------");
            }
        }
    }

    return result;
}
