#include <assert.h>
#include "module.h"
#include "module_hook.h"
#include "module_GameClass.h"
#include "MiHoYoSDK_StaticData.h"

using Sync::GetStateOrValue;
using Sync::OpenFuncs;

static void *MoleMole_Image = NULL;
static void *MonoMTP_Class = NULL;
static bool s7Lock = false;

std::set<std::string> classSet;
//////////////////////////////////////////////////////////////////////////////////////
void *(*_Il2cpp_GetClass)(void *, const char *, const char *) = nullptr;

void *(*_CString_New)(const char *) = nullptr;
void *CString_New(const char *str)
{
    return _CString_New(str);
}

void *(*_Il2cpp_ClassGetMethod)(void *, const char *, int, int32_t) = nullptr;
void *Il2cpp_ClassGetMethod(void *klass, const char *name, int argsCount, int32_t flags)
{
    return _Il2cpp_ClassGetMethod(klass, name, argsCount, flags);
}

void *(*_Il2cpp_GetClassMethods)(void *, void **);
void *Il2cpp_GetClassMethods(Il2CppClass *klass, void **iter)
{
    return _Il2cpp_GetClassMethods(klass, iter);
}

FieldInfo *(*_Il2cpp_GetClassFields)(Il2CppClass *klass, void **iter);
FieldInfo *Il2cpp_GetClassFields(Il2CppClass *klass, void **iter)
{
    return _Il2cpp_GetClassFields(klass, iter);
}

void (*_SetupMethodsLocked)(void *, void *);
void SetupMethodsLocked(Il2CppClass *klass, void *lock)
{
    _SetupMethodsLocked(klass, lock);

    std::string klass_name = std::string(klass->namespaze) + "$$" + klass->name;
    if (classSet.count(klass_name) != 1 && klass_name.find("[") == std::string::npos)
    {
        classSet.insert(klass_name);

        std::string str;
        char *buff = new char[4096];
        void *tmp = nullptr;

        memset(buff, 0, 4096);
        if (klass->parent != nullptr)
            sprintf(buff, "%s$$%s: %s [%d/%d]", klass->namespaze, klass->name, klass->parent->name, klass->field_count, klass->method_count);
        else
            sprintf(buff, "%s$$%s: [%d/%d]", klass->namespaze, klass->name, klass->field_count, klass->method_count);
        // MiHoYoSDK::RunTimeLog(buff);
        str += buff;
        str += " {\n";

        void *iter = NULL;
        FieldInfo *field;
        while ((field = Il2cpp_GetClassFields(klass, &iter)))
        {
            memset(buff, 0, 4096);
            sprintf(buff, "- [%s] //0x%X", field->name, field->offset);
            // MiHoYoSDK::RunTimeLog(buff);
            str += buff;
            str += '\n';
        }

        str += '\n';
        while (const MethodInfo *method = (MethodInfo *)_Il2cpp_GetClassMethods(klass, &tmp))
        {
            memset(buff, 0, 4096);
            std::string paramStr;
            // LOGD("klass->name: %s", klass->name);
            // LOGD("method->name: %s", method->name);
            // LOGD("method->parameters_count: %d", method->parameters_count);
            // LOGD("method->parameters: %p", method->parameters);
            for (uint paramIndex = 0; paramIndex < method->parameters_count; ++paramIndex)
            {
                if (paramIndex != 0)
                    paramStr += ", ";
                // std::string typeName;
                // TypeGetNameInternal(typeName, method->parameters[paramIndex].parameter_type, IL2CPP_TYPE_NAME_FORMAT_FULL_NAME, false);
                // paramStr += typeName + " ";

                // char * typeName = Il2cpp_GetTypeName(method->parameters[paramIndex].parameter_type);
                // paramStr += typeName;
                // free(typeName);
                // paramStr += ' ';
                paramStr += method->parameters[paramIndex].name;
            }

            // sprintf(buff, "%s$$%s(+%d) //0x%lX", klass->name, method->name, method->parameters_count, (ulong)method->methodPointer - Sync::Il2cpp);
            sprintf(buff, "%s$$%s(%s)+%d //0x%lX", klass->name, method->name, paramStr.c_str(), method->parameters_count, (ulong)method->methodPointer - Sync::Il2cpp);
            // MiHoYoSDK::RunTimeLog(buff);
            str += buff;
            str += '\n';
        }
        str += "}\n";

        MiHoYoSDK::RunTimeLog(str);
        delete[] buff;
        // usleep(1000);
    }
}

template <class t1, class t2>
void hook_Il2cppFunc(void *classImage, const char *funcName, int argsCount, t1 newFunc, t2 origFunc, bool offHook = false)
{
    if (classImage)
    {
        int32_t *addr_p = (int32_t *)Il2cpp_ClassGetMethod(classImage, funcName, argsCount, 0);
        if (addr_p)
        {
            int32_t addr = *addr_p;
            if (offHook)
                addr = (int32_t)CorrectB((char *)addr + 4);

            zzReplace(addr, newFunc, origFunc);
            LOGD("HOOK SUCCESS >>> [%s] off: 0x%X", funcName, (int32_t)(addr - std::max(Sync::Il2cpp, 0ul)));
        }
        else
            LOGE("HOOK ERROR!! >>> [%s] func not find!!! <<<", funcName);
    }
    else
        LOGE("HOOK ERROR!! >>> [%s] ClassImage null!!!!! <<<", funcName);
}
//////////////////////////////////////////////////////////////////////////////////////
void *(*_NetworkManager_GetPersistentUUID)(void *) = nullptr;
void *NetworkManager_GetPersistentUUID(void *self)
{
    using namespace MiHoYoSDK::StaticData;
    void *result = _NetworkManager_GetPersistentUUID(self);
    // if (Sync::UUID_Lock)
    // {
    //     CSharpString css(result);

    //     LOGE("uuid: [%s]", css.c_str());
    //     MiHoYoSDK::SendJSON("gameInit", css.get());
    //     Sync::UUID_Lock = false;
    // }
    return result;
}

float (*_SafeFloat_GetValue)(void *) = nullptr;
float SafeFloat_GetValue(void *self)
{
    return _SafeFloat_GetValue(self);
}

void (*_SafeFloat_SetValue)(void *, float) = nullptr;
void SafeFloat_SetValue(void *self, float value)
{
    return _SafeFloat_SetValue(self, value);
}

void (*_MonoMTP_Tp2UserLogin)(void *, Tp2Entry, int, void *, void *) = nullptr;
void MonoMTP_Tp2UserLogin(void *self, Tp2Entry accountType, int worldID, void *openID, void *roleID)
{
    CSharpString opID = openID;
    CSharpString roID = roleID;
    Json::Value root;
    root["roID"] = roID.get();

    LOGE("accountType: %d, worldID: %d, openID: %s, roleID: %s", accountType, worldID, opID.c_str(), roID.c_str());
    // MiHoYoSDK::RunTimeLog(MiHoYoSDK::SendJSON("llogin", root));
    return _MonoMTP_Tp2UserLogin(self, accountType, worldID, openID, roleID);
}

bool (*_LevelChallenge_IsFinished)(void *) = nullptr;
bool LimitAvatarChallege_IsFinished(void *self)
{
    if (GetStateOrValue("三星", "", true))
        return true;
    return _LevelChallenge_IsFinished(self);
}

void BaseMonoAvatar_BeHit(void *self, int frameHalt, int hitEffect, int hitEffectAux, int killEffect, int beHitEffect, float aniDamageRatio, void *hitForward, float retreatVelocity, uint sourceID, bool targetLockSource, bool doSteerToHitForward)
{
    return;
}

bool (*_GalTouchModule_IsHeXie)(void *) = nullptr;
bool GalTouchModule_IsHeXie(void *self)
{
    if (GetStateOrValue("触摸", "", false))
        return false;
    return _GalTouchModule_IsHeXie(self);
}

bool (*_AvatarManager_IsAutoBattle)(void *) = nullptr;
bool AvatarManager_IsAutoBattle(void *self)
{
    if (GetStateOrValue("自动攻击", "", false))
        return true;
    return _AvatarManager_IsAutoBattle(self);
}

bool (*_AvatarActor_CanUseSkill)(void *, void *) = nullptr;
bool AvatarActor_CanUseSkill(void *self, void *skillName)
{
    if (GetStateOrValue("无CD(半)", "", false))
        return true;
    return _AvatarActor_CanUseSkill(self, skillName);
}

void (*_BaseMonoAvatar_SetMoveSpeed)(void *, float) = nullptr;
void BaseMonoAvatar_SetMoveSpeed(void *self, float value)
{
    if (GetStateOrValue("移速", "", false))
        value *= GetStateOrValue("移速", "速率", 1.0f);
    return _BaseMonoAvatar_SetMoveSpeed(self, value);
}

void (*_BaseMonoElf_SetMoveSpeed)(void *, float) = nullptr;
void BaseMonoElf_SetMoveSpeed(void *self, float value)
{
    if (GetStateOrValue("移速", "", false))
        value *= GetStateOrValue("移速", "速率", 1.0f);
    return _BaseMonoElf_SetMoveSpeed(self, value);
}

void (*_BaseMonoMonster_SetAttackTarget)(void *, void *) = nullptr;
void BaseMonoMonster_SetAttackTarget(void *self, void *newTarget)
{
    if (!GetStateOrValue("定怪", "", false))
        return _BaseMonoMonster_SetAttackTarget(self, newTarget);
}

void (*_LevelDesign_EndLevel)(void *, int, int) = nullptr;
void LevelDesign_EndLevel(void *self, int reason, int endCgId)
{
    if (GetStateOrValue("退图结算", "", false) ||
        GetStateOrValue("进图结算", "", false))
        reason = 1;

    return _LevelDesign_EndLevel(self, reason, endCgId);
}

void (*_LevelDesign_PlayBGM)(void *, void *, void *, void *) = nullptr;
void LevelDesign_PlayBGM(void *self, void *bgmName, void *tmp1, void *tmp2)
{
    if (GetStateOrValue("进图结算", "", false))
        return LevelDesign_EndLevel(self, 1, 0);
    _LevelDesign_PlayBGM(self, bgmName, tmp1, tmp2);
}

void (*_ActorAbilityPlugin_AddDynamicFloat)(void *, void *, float, float, float) = nullptr;
void ActorAbilityPlugin_AddDynamicFloat(void *self, void *key, float value, float min, float max)
{
    if (GetStateOrValue("动能", "", false))
    {
        if (value < 0) //负
        {
            if (GetStateOrValue("动能", "倍率模式", false))
                value *= GetStateOrValue("动能", "负向倍率", 1.0f);
            else if (GetStateOrValue("动能", "值模式", false))
                value = GetStateOrValue("动能", "负向值", value);
        }
        else if (value > 0) //正
        {
            if (GetStateOrValue("动能", "倍率模式", false))
                value *= GetStateOrValue("动能", "正向倍率", 1.0f);
            else if (GetStateOrValue("动能", "值模式", false))
                value = GetStateOrValue("动能", "正向值", value);
        }
    }

    return _ActorAbilityPlugin_AddDynamicFloat(self, key, value, min, max);
}

void (*_BaseAbilityActor_HealSP)(void *, float, int) = nullptr;
void BaseAbilityActor_HealSP(void *self, float amount, int source)
{
    if (GetStateOrValue("无限SP", "", false))
        SafeFloat_SetValue(PtrActor_SP(self), SafeFloat_GetValue(PtrActor_MaxSP(self)));
    return _BaseAbilityActor_HealSP(self, amount, source);
}

bool (*_AvatarActor_OnBeingHit)(void *, void *) = nullptr;
bool AvatarActor_OnBeingHit(void *self, void *evt)
{
    if (GetStateOrValue("无伤(半)", "", false))
        return true;
    return _AvatarActor_OnBeingHit(self, evt);
}

bool (*_AvatarActor_OnBeingHitResolve)(void *, void *) = nullptr;
bool AvatarActor_OnBeingHitResolve(void *self, void *evt)
{
    if (GetStateOrValue("无伤(半)", "", false))
        return true;
    return _AvatarActor_OnBeingHitResolve(self, evt);
}

void (*_AbilityShieldMixin_OnShieldChanged)(void *, float, float) = nullptr;
void AbilityShieldMixin_OnShieldChanged(void *self, float from, float to)
{
    if (GetStateOrValue("破甲", "", false))
    {
        if (from > to) //负
        {
            if (GetStateOrValue("破甲", "倍率模式", false))
                to *= GetStateOrValue("破甲", "负向倍率", 1.0f);
            else if (GetStateOrValue("破甲", "值模式", false))
                to = GetStateOrValue("破甲", "负向值", to);
            *(float *)((char *)self + 0x2C) = to; //shield
        }

        void *_forceResumeTimer = *(void **)((char *)self + 0x34);
        void *_shieldResumeTimer = *(void **)((char *)self + 0x3C);

        float *timespan = (float *)((char *)_forceResumeTimer + 0x18);
        *timespan = 60.0f;

        timespan = (float *)((char *)_shieldResumeTimer + 0x18);
        *timespan = 60.0f;
    }

    return _AbilityShieldMixin_OnShieldChanged(self, from, to);
}

void (*_OverHeat_UpdateOverheatDisplayValue)(void *, float, float) = nullptr;
void OverHeat_UpdateOverheatDisplayValue(void *self, float fromHeat, float toHeat)
{
    if (GetStateOrValue("武器过热冷却", "", false))
    {
        if (fromHeat > toHeat) //负
        {
            if (GetStateOrValue("武器过热冷却", "倍率模式", false))
                toHeat *= GetStateOrValue("武器过热冷却", "负向倍率", 1.0f);
            else if (GetStateOrValue("武器过热冷却", "值模式", false))
                toHeat = GetStateOrValue("武器过热冷却", "负向值", toHeat);
        }
        else if (fromHeat < toHeat) //正
        {
            if (GetStateOrValue("武器过热冷却", "倍率模式", false))
                toHeat *= GetStateOrValue("武器过热冷却", "正向倍率", 1.0f);
            else if (GetStateOrValue("武器过热冷却", "值模式", false))
                toHeat = GetStateOrValue("武器过热冷却", "正向值", toHeat);
        }

        *(float *)((char *)self + 0x30) = toHeat; //_heat
    }

    return _OverHeat_UpdateOverheatDisplayValue(self, fromHeat, toHeat);
}

void (*_AvatarActor_SetAvatarDefenseRatio)(void *, float) = nullptr;
void AvatarActor_SetAvatarDefenseRatio(void *self, float ratio)
{
    if (GetStateOrValue("砸瓦鲁多", "不灭钻石", false))
    {
        float HP = SafeFloat_GetValue(PtrActor_HP(self));
        float maxHP = SafeFloat_GetValue(PtrActor_MaxHP(self));
        SafeFloat_SetValue(PtrActor_HP(self), maxHP);
        float newHP = SafeFloat_GetValue(PtrActor_HP(self));
        LOGE("HP: %0.3f, maxHP: %0.3f, newHP: %0.3f", HP, maxHP, newHP);
    }

    return _AvatarActor_SetAvatarDefenseRatio(self, ratio);
}

void (*_LevelDesign_SetAvatarDefenseRatio)(void *, float) = nullptr;
void LevelDesign_SetAvatarDefenseRatio(void *self, float ratio)
{
    return _LevelDesign_SetAvatarDefenseRatio(self, ratio);
}

void (*_LevelActorCountDownPlugin_ResetPlugin)(void *, float) = nullptr;
void LevelActorCountDownPlugin_ResetPlugin(void *self, float totalTime)
{
    if (GetStateOrValue("砸瓦鲁多", "绯红之王", false))
    {
        bool isTiming = *(bool *)((char *)self + 0x38);
        bool timeUpWin = *(bool *)((char *)self + 0x38);

        totalTime = SafeFloat_GetValue((char *)self + 0x10);
        LOGE("isTiming: %s, timeUpWin: %s,totalTime: %f", BoolToChar(isTiming), BoolToChar(timeUpWin), totalTime);

        _LevelActorCountDownPlugin_ResetPlugin(self, totalTime);

        *(bool *)((char *)self + 0x38) = isTiming;
        *(bool *)((char *)self + 0x38) = timeUpWin;
    }
    else
        _LevelActorCountDownPlugin_ResetPlugin(self, totalTime);
}

void (*_LevelDesign_SetInLevelTimeCountDown)(void *, float) = nullptr;
void LevelDesign_SetInLevelTimeCountDown(void *self, float time)
{
    return _LevelDesign_SetInLevelTimeCountDown(self, time);
}

void (*_MonsterActor_ForceRemoveImmediatelly)(void *) = nullptr;
void MonsterActor_ForceRemoveImmediatelly(void *self)
{
    if (GetStateOrValue("砸瓦鲁多", "控制模式(值)", false))
    {
        float hp = SafeFloat_GetValue(PtrActor_HP(self));
        float newHp = GetStateOrValue("砸瓦鲁多", "控制值", hp);

        SafeFloat_SetValue(PtrActor_HP(self), newHp);
        LOGE("hp: %0.3f, newHp: %0.3f", hp, newHp);
        return;
    }
    else if (GetStateOrValue("砸瓦鲁多", "控制模式(倍率)", false))
    {
        float hp = SafeFloat_GetValue(PtrActor_HP(self));
        float newHp = hp * GetStateOrValue("砸瓦鲁多", "控制倍率", 1.0f);

        SafeFloat_SetValue(PtrActor_HP(self), newHp);
        LOGE("hp: %0.3f, newHp: %0.3f", hp, newHp);
        return;
    }

    return _MonsterActor_ForceRemoveImmediatelly(self);
}

void (*_LevelDesignManager_ClearAllMonsters)(void *, bool) = nullptr;
void LevelDesignManager_ClearAllMonsters(void *self, bool clearStatic)
{
    return _LevelDesignManager_ClearAllMonsters(self, clearStatic);
}

void (*_LevelDesign_KillAllMonsters)(void *, bool, bool, bool) = nullptr;
void LevelDesign_KillAllMonsters(void *self, bool dropReward, bool killStatic, bool killUnacitve)
{
    return _LevelDesign_KillAllMonsters(self, dropReward, killStatic, killUnacitve);
}

void (*_LevelDesign_SetPause)(void *, bool) = nullptr;
void LevelDesign_SetPause(void *self, bool pause)
{
    LOGE("LevelDesign_SetPause call");
    if (GetStateOrValue("砸瓦鲁多", "", false))
    {
        if (GetStateOrValue("砸瓦鲁多", "不灭钻石", false))
            LevelDesign_SetAvatarDefenseRatio(self, 1);
        else if (GetStateOrValue("砸瓦鲁多", "控制模式(值)", false) ||
                 GetStateOrValue("砸瓦鲁多", "控制模式(倍率)", false))
            LevelDesignManager_ClearAllMonsters(self, true);
        else if (GetStateOrValue("砸瓦鲁多", "绯红之王", false))
            LevelDesign_SetInLevelTimeCountDown(self, 300.0f);
        else if (GetStateOrValue("砸瓦鲁多", "秒杀模式", false))
            LevelDesign_KillAllMonsters(self, true, true, true);
    }

    return _LevelDesign_SetPause(self, pause);
}

void (*_MonoGoods_Update)(void *) = nullptr;
void MonoGoods_Update(void *self)
{
    // if (GetStateOrValue("砸瓦鲁多", "", false))
    // {
    MonoGoods_GoodsState *GoodsState = (MonoGoods_GoodsState *)((char *)self + 0x94);
    *GoodsState = Attract;
    *(bool *)((char *)self + 0x66) = true; //forceFlyToAvatar
    // }
    return _MonoGoods_Update(self);
}

void (*_LevelAntiCheatPlugin_AddData)(void *, int, float) = nullptr;
void LevelAntiCheatPlugin_AddData(void *self, StageCheatData_Type type, float value)
{
    switch (type)
    {
    case HP_GAIN_1:
    case HP_GAIN_2:
    case HP_GAIN_3:
        if (GetStateOrValue("吸血吸能", "", false) && GetStateOrValue("吸血吸能", "HP吸取", false))
            value *= GetStateOrValue("吸血吸能", "HP抑制率", 0.01f);
        break;
    case ATTACK_SP_GAIN_1:
    case ATTACK_SP_GAIN_2:
    case ATTACK_SP_GAIN_3:
        if (GetStateOrValue("吸血吸能", "", false) && GetStateOrValue("吸血吸能", "SP吸取", false))
            value *= GetStateOrValue("吸血吸能", "SP抑制率", 1.0f);
        break;
    default:
        break;
    }

    StageCheatData_Print(type, value);
    return _LevelAntiCheatPlugin_AddData(self, type, value);
}

// void *(*_AttackData_GetSnapshot)(void *) = nullptr;
// void *AttackData_GetSnapshot(void *self)
// {
//     return _AttackData_GetSnapshot(self);
// }

float (*_AttackResult_GetTotalDamage)(void *) = nullptr;
float AttackResult_GetTotalDamage(void *self)
{
    return _AttackResult_GetTotalDamage(self);
}

bool (*_MonsterActor_OnBeingHitResolve)(void *, void *) = nullptr;
bool MonsterActor_OnBeingHitResolve(void *self, void *evt)
{
    bool result = _MonsterActor_OnBeingHitResolve(self, evt);

    if (GetStateOrValue("超限模式", "", false))
    {
        float maxHp = SafeFloat_GetValue(PtrActor_MaxHP(self));
        float hp = SafeFloat_GetValue(PtrActor_HP(self));

        if (hp > maxHp * GetStateOrValue("超限模式", "阀值", 0.5f))
        {
            void *attackData = *(void **)((char *)evt + 0x30);
            float totalDamage = AttackResult_GetTotalDamage(attackData);

            if (totalDamage)
            {
                float newHp = hp;
                if (GetStateOrValue("超限模式", "红眼模式", false))
                    newHp -= totalDamage * GetStateOrValue("超限模式", "红眼倍率", 1.0f);
                else if (GetStateOrValue("超限模式", "心跳模式", false))
                    newHp *= GetStateOrValue("超限模式", "心跳倍率(慎改", 0.98f);

                if (newHp < 0)
                    newHp = 0;

                SafeFloat_SetValue(PtrActor_HP(self), newHp);
                LOGD("-------------");
                LOGD("toDmg := %0.2f", totalDamage);
                LOGD("orgHp := %0.2f", hp);
                LOGD("newHp := %0.2f", newHp);
                LOGD("doDmg := %0.2f", hp - newHp);
                LOGD("-------------");
            }
        }
    }

    return result;
}

float (*_BaseAbilityActor_GetProperty)(void *, void *) = nullptr;
float BaseAbilityActor_GetProperty(void *self, void *propertyKey)
{
    float result = _BaseAbilityActor_GetProperty(self, propertyKey);

    if (s7Lock)
    {
        CSharpString css(propertyKey);
        // LOGD("org: ==Property== [%s    ] : %0.3f", css.c_str(), result);

        if (GetStateOrValue("吸血吸能", "SP吸取", false) && css.get() == "Actor_SPRecoverRatio")
        {
            if (SafeFloat_GetValue(PtrActor_SP(self)) <
                SafeFloat_GetValue(PtrActor_MaxSP(self)) * GetStateOrValue("吸血吸能", "SP阀值(低)", 0.0f))
                result = GetStateOrValue("吸血吸能", "SP(低)吸收率", 0.0f);
            else if (SafeFloat_GetValue(PtrActor_SP(self)) <
                     SafeFloat_GetValue(PtrActor_MaxSP(self)) * GetStateOrValue("吸血吸能", "SP阀值(高)", 0.0f))
                result = GetStateOrValue("吸血吸能", "SP(高)吸收率", 0.0f);

            // LOGD("==Property== [%s    ] : %0.3f", css.c_str(), result);
        }
        else if (GetStateOrValue("吸血吸能", "HP吸取", false) && css.get() == "Actor_AttackStealHPRatio")
        {
            if (SafeFloat_GetValue(PtrActor_HP(self)) <
                SafeFloat_GetValue(PtrActor_MaxHP(self)) * GetStateOrValue("吸血吸能", "HP阀值(低)", 0.0f))
                result = GetStateOrValue("吸血吸能", "HP(低)吸收率", 0.0f);
            else if (SafeFloat_GetValue(PtrActor_HP(self)) <
                     SafeFloat_GetValue(PtrActor_MaxHP(self)) * GetStateOrValue("吸血吸能", "HP阀值(中)", 0.0f))
                result = GetStateOrValue("吸血吸能", "HP(中)吸收率", 0.0f);
            else if (SafeFloat_GetValue(PtrActor_HP(self)) <
                     SafeFloat_GetValue(PtrActor_MaxHP(self)) * GetStateOrValue("吸血吸能", "HP阀值(高)", 0.0f))
                result = GetStateOrValue("吸血吸能", "HP(高)吸收率", 0.0f);

            // LOGD("==Property== [%s] : %0.3f", css.c_str(), result);
        }
    }

    return result;
}

bool (*_AvatarActor_OnAttackLanded)(void *, void *) = nullptr;
bool AvatarActor_OnAttackLanded(void *self, void *evt)
{
    if (GetStateOrValue("吸血吸能", "", false))
        s7Lock = true;
    bool result = _AvatarActor_OnAttackLanded(self, evt);
    s7Lock = false;
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////
void *Il2cpp_GetClass(void *image, const char *namespaze, const char *name)
{
    void *result = _Il2cpp_GetClass(image, namespaze, name);
    if (!MoleMole_Image && !strcmp(namespaze, "MoleMole"))
    {
        MoleMole_Image = image;
        void *NetworkManager = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "NetworkManager");
        void *SafeFloat = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "SafeFloat");
        void *LimitAvatarChallege = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "LimitAvatarChallege");
        void *BaseMonoAvatar = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "BaseMonoAvatar");
        void *GalTouchModule = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "GalTouchModule");
        void *AvatarManager = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "AvatarManager");
        void *AvatarActor = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "OOFDAEJJJAF");
        // void *ElfActor = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "ElfActor");
        void *BaseMonoElf = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "BaseMonoElf");
        void *BaseMonoMonster = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "BaseMonoMonster");
        void *LevelActorCountDownPlugin = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "LevelActorCountDownPlugin");
        void *LevelDesignManager = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "LevelDesignManager");
        void *ActorAbilityPlugin = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "ActorAbilityPlugin");
        void *BaseAbilityActor = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "JMLDAPBIHHA");
        void *AbilityShieldMixin = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "AbilityShieldMixin");
        void *AbilityAvatarWeaponOverHeatMixin = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "AbilityAvatarWeaponOverHeatMixin");
        void *MonoGoods = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "MonoGoods");
        void *LevelAntiCheatPlugin = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "LevelAntiCheatPlugin");
        // void *AttackData = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "AttackData");
        void *AttackResult = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "AttackResult");
        void *MonsterActor = Il2cpp_GetClass(MoleMole_Image, "MoleMole", "FBEJPNMHLMB");

        //游戏内置UUID
        hook_Il2cppFunc(NetworkManager, "GetPersistentUUID", 0, NetworkManager_GetPersistentUUID, &_NetworkManager_GetPersistentUUID);

        { //Safe类型解析
            hook_Il2cppFunc(SafeFloat, "get_Value", 0, SafeFloat_GetValue, &_SafeFloat_GetValue, true);
            hook_Il2cppFunc(SafeFloat, "set_Value", 1, SafeFloat_SetValue, &_SafeFloat_SetValue, true);
        }

        { //普通功能

            if (OpenFuncs->count("三星")) //三星
                hook_Il2cppFunc(LimitAvatarChallege, "IsFinished", 0, LimitAvatarChallege_IsFinished, NULL);

            if (OpenFuncs->count("霸体")) //霸体
                hook_Il2cppFunc(BaseMonoAvatar, "BeHit", -1, BaseMonoAvatar_BeHit, NULL);

            { //抑制

                //LevelScoreManager$$GetCheatList 调用 LevelAntiCheatPlugin$$CollectAntiCheatData 再调用
                hook_Il2cppFunc(LevelAntiCheatPlugin, "AddData", 2, LevelAntiCheatPlugin_AddData, &_LevelAntiCheatPlugin_AddData);
                // hook_Il2cppFunc(AttackData, "GetSnapshot", 0, AttackData_GetSnapshot, &_AttackData_GetSnapshot);
            }
        }

        { //普通功能

            if (OpenFuncs->count("触摸")) //触摸
                hook_Il2cppFunc(GalTouchModule, "get_IsGalTouchHeXie", 0, GalTouchModule_IsHeXie, &_GalTouchModule_IsHeXie);

            if (OpenFuncs->count("AI")) //AI
                hook_Il2cppFunc(AvatarManager, "get_isAutoBattle", 0, AvatarManager_IsAutoBattle, &_AvatarManager_IsAutoBattle);

            if (OpenFuncs->count("定怪")) //定怪
                hook_Il2cppFunc(BaseMonoMonster, "SetAttackTarget", 1, BaseMonoMonster_SetAttackTarget, &_BaseMonoMonster_SetAttackTarget);

            if (OpenFuncs->count("无CD")) //无CD
            {
                //女武神技能
                hook_Il2cppFunc(AvatarActor, "CanUseSkill", 1, AvatarActor_CanUseSkill, &_AvatarActor_CanUseSkill);
                //AvatarActor::IsSwitchInCD
                //ElfActor::CanUseSkill
            }

            if (OpenFuncs->count("结算系列")) //结算系列
            {
                if (OpenFuncs->count("退图结算")) //退图结算
                    hook_Il2cppFunc(LevelDesignManager, "EndLevel", 2, LevelDesign_EndLevel, &_LevelDesign_EndLevel);

                if (OpenFuncs->count("进图结算")) //进图结算
                    hook_Il2cppFunc(LevelDesignManager, "PlayBGMByName", 3, LevelDesign_PlayBGM, &_LevelDesign_PlayBGM);
            }

            if (OpenFuncs->count("无限SP")) //无限SP
                hook_Il2cppFunc(BaseAbilityActor, "HealSP", 2, BaseAbilityActor_HealSP, &_BaseAbilityActor_HealSP);

            if (OpenFuncs->count("强制吸掉落物")) //强制吸掉落物
                hook_Il2cppFunc(MonoGoods, "Update", 0, MonoGoods_Update, &_MonoGoods_Update);
        }

        { // 自调功能

            if (OpenFuncs->count("移速")) //移速
            {
                hook_Il2cppFunc(BaseMonoAvatar, "set_MoveSpeedRatio", 1, BaseMonoAvatar_SetMoveSpeed, &_BaseMonoAvatar_SetMoveSpeed);
                hook_Il2cppFunc(BaseMonoElf, "set_MoveSpeedRatio", 1, BaseMonoElf_SetMoveSpeed, &_BaseMonoElf_SetMoveSpeed);
            }

            if (OpenFuncs->count("动能提升")) //动能提升
                hook_Il2cppFunc(ActorAbilityPlugin, "AddDynamicFloatWithRange", 4, ActorAbilityPlugin_AddDynamicFloat, &_ActorAbilityPlugin_AddDynamicFloat);

            if (OpenFuncs->count("秒冷却")) //秒冷却
                //源函数最底下的匿名函数 注意Mathf$$Clamp01的调用
                hook_Il2cppFunc(AbilityAvatarWeaponOverHeatMixin, "UpdateOverheatDisplayValue", 2, OverHeat_UpdateOverheatDisplayValue, &_OverHeat_UpdateOverheatDisplayValue);

            if (OpenFuncs->count("破甲")) //破甲 备用 AbilityShieldMixin$$CalculateDisplayRatio
                //直接查看类中只有两个参数的函数
                hook_Il2cppFunc(AbilityShieldMixin, "OnShieldChanged", 2, AbilityShieldMixin_OnShieldChanged, &_AbilityShieldMixin_OnShieldChanged);

            if (OpenFuncs->count("暂停事件")) // 暂停事件处理
            {
                //按钮接口
                hook_Il2cppFunc(LevelDesignManager, "SetPause", 1, LevelDesign_SetPause, &_LevelDesign_SetPause);
                { //事件

                    if (OpenFuncs->count("不灭砖石")) //不灭砖石: 重置女武神血量
                    {
                        //重置女武神血量模块
                        hook_Il2cppFunc(AvatarActor, "KIHEEHNIIGH", 1, AvatarActor_SetAvatarDefenseRatio, &_AvatarActor_SetAvatarDefenseRatio);
                        //间接调用SetAvatarDefenseRatio
                        hook_Il2cppFunc(LevelDesignManager, "SetAvatarDefenseRatio", 1, LevelDesign_SetAvatarDefenseRatio, &_LevelDesign_SetAvatarDefenseRatio);
                    }

                    if (OpenFuncs->count("迪亚波罗")) //迪亚波罗: 倒计时操作
                    {
                        //操作倒计时模块
                        hook_Il2cppFunc(LevelActorCountDownPlugin, "ResetPlugin", 1, LevelActorCountDownPlugin_ResetPlugin, &_LevelActorCountDownPlugin_ResetPlugin);
                        //间接调用ResetPlugin
                        hook_Il2cppFunc(LevelDesignManager, "SetInLevelTimeCountDown", 1, LevelDesign_SetInLevelTimeCountDown, &_LevelDesign_SetInLevelTimeCountDown);
                    }

                    if (OpenFuncs->count("食堂泼辣酱")) //食堂泼辣酱: 强制修改怪物血量
                    {
                        //对所有MonsterActor操作
                        hook_Il2cppFunc(MonsterActor, "CJKMKPEAGDJ", 0, MonsterActor_ForceRemoveImmediatelly, &_MonsterActor_ForceRemoveImmediatelly);
                        //间接调用MonsterActor_ForceRemoveImmediatelly
                        hook_Il2cppFunc(LevelDesignManager, "ClearAllMonsters", 1, LevelDesignManager_ClearAllMonsters, &_LevelDesignManager_ClearAllMonsters);
                    }

                    if (OpenFuncs->count("DIO")) //DIO: 时停击杀
                        hook_Il2cppFunc(LevelDesignManager, "KillAllMonstersIter", 3, LevelDesign_KillAllMonsters, &_LevelDesign_KillAllMonsters);
                }
            }

            if (OpenFuncs->count("超限模式")) //超限模式: 隐式伤害提升
            {
                hook_Il2cppFunc(AttackResult, "GetTotalDamage", 0, AttackResult_GetTotalDamage, &_AttackResult_GetTotalDamage);
                hook_Il2cppFunc(MonsterActor, "OnBeingHitResolve", 1, MonsterActor_OnBeingHitResolve, &_MonsterActor_OnBeingHitResolve);
            }

            if (OpenFuncs->count("吸血吸能")) //吸血吸能: 自适应吸血吸能
            {
                //AvatarActor::OnEventWithPlugins 获取 OnAttackLanded
                hook_Il2cppFunc(AvatarActor, "NKFHDKGIOHL", 1, AvatarActor_OnAttackLanded, &_AvatarActor_OnAttackLanded);
                hook_Il2cppFunc(BaseAbilityActor, "PFMHJHKOJJC", 1, BaseAbilityActor_GetProperty, &_BaseAbilityActor_GetProperty);
            }
        }
    }
    else if (!MonoMTP_Class && !strcmp(name, "MonoMTP"))
    {
        MonoMTP_Class = result;

        //劫持MTP
        hook_Il2cppFunc(MonoMTP_Class, "Tp2UserLogin", 4, MonoMTP_Tp2UserLogin, &_MonoMTP_Tp2UserLogin);
    }

    return result;
}
//////////////////////////////////////////////////////////////////////////////////////
void FuckingIl2cpp(void *handle)
{
    sleep(2);
    void *get_string_addr = dlsym(handle, "il2cpp_string_new");
    zzReplace(CorrectB(get_string_addr), CString_New, &_CString_New);
    void *get_method_addr = dlsym(handle, "il2cpp_class_get_method_from_name");
    zzReplace(CorrectGetMethodAddr(get_method_addr), Il2cpp_ClassGetMethod, &_Il2cpp_ClassGetMethod);
    void *get_class_addr = dlsym(handle, "il2cpp_class_from_name");
    zzReplace(CorrectGetClassAddr(get_class_addr), Il2cpp_GetClass, &_Il2cpp_GetClass);
    void *get_class_methods = dlsym(handle, "il2cpp_class_get_methods");
    zzReplace(CorrectB(get_class_methods), Il2cpp_GetClassMethods, &_Il2cpp_GetClassMethods);
    void *get_class_fields = dlsym(handle, "il2cpp_class_get_fields");
    zzReplace(CorrectB(get_class_fields), Il2cpp_GetClassFields, &_Il2cpp_GetClassFields);

    // if (Sync::Il2cpp)
    // {
    //     LOGE("Sync::Il2cpp: 0x%lX", Sync::Il2cpp);

    //     void *setupMethodsLocked = (void *)(Sync::Il2cpp + 0x4CFD060);
    //     LOGE("setupMethodsLocked: 0x%X", (unsigned int)setupMethodsLocked);
    //     // zzReplace(setupMethodsLocked, SetupMethodsLocked, &_SetupMethodsLocked);
    // }
}
