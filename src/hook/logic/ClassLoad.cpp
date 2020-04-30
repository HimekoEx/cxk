#include "src/hook/hook.h"
#include "src/sync/sync.h"
using namespace Hook;
using namespace Hook::Loaded;
using namespace Hook::Loaded::Il2cpp;
using Sync::GetStateOrValue;
using Sync::OpenFuncs;

Il2CppImage *Logic::MoleMole = nullptr;
Il2CppClass *Logic::MonoMTP = nullptr;

// 劫持游戏函数
template <class T1, class T2>
static void HookFunc(Il2CppClass *clazz, const char *funcName, int argsCount, T1 newFunc, T2 origFunc,
                     bool offHook = false, ulong off = 0ul)
{
    if (clazz)
    {
        MethodInfo *method = Il2cpp::Class_GetMethodFromNameFlags(clazz, funcName, argsCount, 0);
        if (method)
        {
            Il2CppMethodPointer addr = method->methodPointer;
            if (offHook)
                addr = (Il2CppMethodPointer)Uitls::Amend_B((char *)addr + off);

            zzReplace(addr, newFunc, origFunc);
            LOGE("--HOOK SUCCESS-- >>> [%s$$%s] off: 0x%X", clazz->name, funcName,
                 (int32_t)((int32_t)addr - std::max(Sync::Il2cpp, 0ul)));
        }
        else
            LOGE("***HOOK ERROR*** >>> [%s$$%s] func not find!!! <<<", clazz->name, funcName);
    }
    else
        LOGE("***HOOK ERROR*** >>> [%s] Class null!!!!! <<<", funcName);
}

// 劫持游戏Class
Il2CppClass *Logic::HookClass(Il2CppImage *image, const char *namespaze, const char *name)
{
    Il2CppClass *result = _Class_FromName(image, namespaze, name);

    if (!MoleMole && !strcmp(namespaze, "MoleMole") && (MoleMole = image))
    {
        //获取类型
        Il2CppClass *NetworkManager = Class_FromName(image, namespaze, "NetworkManager");
        Il2CppClass *SafeFloat = Class_FromName(image, namespaze, "SafeFloat");
        Il2CppClass *LevelAntiCheatPlugin = Class_FromName(image, namespaze, "LevelAntiCheatPlugin");
        Il2CppClass *LimitAvatarChallege = Class_FromName(image, namespaze, "LimitAvatarChallege");
        Il2CppClass *BaseMonoAvatar = Class_FromName(image, namespaze, "BaseMonoAvatar");
        Il2CppClass *GalTouchModule = Class_FromName(image, namespaze, "GalTouchModule");
        Il2CppClass *AvatarManager = Class_FromName(image, namespaze, "AvatarManager");
        Il2CppClass *BaseMonoMonster = Class_FromName(image, namespaze, "BaseMonoMonster");
        Il2CppClass *BaseAbilityActor = Class_FromName(image, namespaze, "JMLDAPBIHHA"); //
        Il2CppClass *MonoGoods = Class_FromName(image, namespaze, "MonoGoods");
        Il2CppClass *AvatarActor = Class_FromName(image, namespaze, "OOFDAEJJJAF"); //
        Il2CppClass *LevelDesignManager = Class_FromName(image, namespaze, "LevelDesignManager");
        Il2CppClass *BaseMonoElf = Class_FromName(image, namespaze, "BaseMonoElf");
        Il2CppClass *AbilityAvatarWeaponOverHeatMixin = Class_FromName(image, namespaze, "AbilityAvatarWeaponOverHeatMixin");
        Il2CppClass *LevelActorCountDownPlugin = Class_FromName(image, namespaze, "LevelActorCountDownPlugin");
        Il2CppClass *ActorAbilityPlugin = Class_FromName(image, namespaze, "ActorAbilityPlugin");
        Il2CppClass *AbilityShieldMixin = Class_FromName(image, namespaze, "AbilityShieldMixin");
        Il2CppClass *AttackResult = Class_FromName(image, namespaze, "AttackResult");
        Il2CppClass *MonsterActor = Class_FromName(image, namespaze, "FBEJPNMHLMB");
        Il2CppClass *DamageModelLogic = Class_FromName(image, namespaze, "OALPDPHBIEL");

        { //获取游戏内置UUID
            HookFunc(NetworkManager, "GetPersistentUUID", 0, NetworkManager_GetPersistentUUID, &_NetworkManager_GetPersistentUUID);
        }

        { //Safe类型解析
            HookFunc(SafeFloat, "get_Value", 0, SafeFloat_get_Value, &_SafeFloat_get_Value, true, 4ul);
            HookFunc(SafeFloat, "set_Value", 1, SafeFloat_set_Value, &_SafeFloat_set_Value, true, 4ul);
        }

        { //抑制

            //LevelScoreManager$$GetCheatList 调用 LevelAntiCheatPlugin$$CollectAntiCheatData 再调用
            HookFunc(LevelAntiCheatPlugin, "CollectAntiCheatData", 1,
                     LevelAntiCheatPlugin_CollectAntiCheatData, &_LevelAntiCheatPlugin_CollectAntiCheatData);
            HookFunc(LevelAntiCheatPlugin, "AddData", 2, LevelAntiCheatPlugin_AddData, &_LevelAntiCheatPlugin_AddData);
            // HookFunc(AttackData, "GetSnapshot", 0, AttackData_GetSnapshot, &_AttackData_GetSnapshot);
        }

        { //普通功能

            if (OpenFuncs->count("三星") && GetStateOrValue("三星", "", false)) //三星
                HookFunc(LimitAvatarChallege, "IsFinished", 0, LimitAvatarChallege_IsFinished, nullptr);

            if (OpenFuncs->count("霸体") && GetStateOrValue("霸体", "", false)) //霸体
                HookFunc(BaseMonoAvatar, "BeHit", -1, BaseMonoAvatar_BeHit, nullptr);

            if (OpenFuncs->count("触摸") && GetStateOrValue("触摸", "", false)) //触摸
                HookFunc(GalTouchModule, "get_IsGalTouchHeXie", 0, GalTouchModule_get_IsGalTouchHeXie, nullptr);

            if (OpenFuncs->count("AI")) //AI
            {
                HookFunc(AvatarManager, "TryGetLocalAvatar", 0,
                         AvatarManager_TryGetLocalAvatar, &_AvatarManager_TryGetLocalAvatar);
                HookFunc(BaseMonoAvatar, "RefreshController", 0,
                         BaseMonoAvatar_RefreshController, &_BaseMonoAvatar_RefreshController);
            }

            if (OpenFuncs->count("定怪")) //定怪
                HookFunc(BaseMonoMonster, "SetAttackTarget", 1,
                         BaseMonoMonster_SetAttackTarget, &_BaseMonoMonster_SetAttackTarget);

            if (OpenFuncs->count("无伤")) //无伤
                HookFunc(BaseAbilityActor, "BGKICEMLBDP", 1,
                         BaseAbilityActor_CanBeDamageByRuntimeid, &_BaseAbilityActor_CanBeDamageByRuntimeid);

            if (OpenFuncs->count("无限SP")) //无限SP
                HookFunc(BaseAbilityActor, "HealSP", 2, BaseAbilityActor_HealSP, &_BaseAbilityActor_HealSP);

            if (OpenFuncs->count("强制吸掉落物")) //强制吸掉落物
                HookFunc(MonoGoods, "Update", 0, MonoGoods_Update, &_MonoGoods_Update);

            if (OpenFuncs->count("无CD")) //无CD
            {
                HookFunc(AvatarActor, "CanUseSkill", 1, AvatarActor_CanUseSkill, &_AvatarActor_CanUseSkill);
                //AbilityAvatarQTEMixin$$Core 调用 AvatarActor::IsSwitchInCD
                HookFunc(AvatarActor, "IIFJPACIDLM", 0, AvatarActor_IsSwitchInCD, &_AvatarActor_IsSwitchInCD);
            }

            if (OpenFuncs->count("速通系列") && GetStateOrValue("速通系列", "", false)) //结算系列
            {
                if (OpenFuncs->count("进图结算")) //进图结算
                    HookFunc(LevelDesignManager, "BattleBegin", 0, LevelDesignManager_BattleBegin, &_LevelDesignManager_BattleBegin);

                if (OpenFuncs->count("退图结算")) //退图结算
                    HookFunc(LevelDesignManager, "EndLevel", 2, LevelDesignManager_EndLevel, &_LevelDesignManager_EndLevel);
            }
        }

        { // 自调功能

            if (OpenFuncs->count("移速")) //移速
            {
                //女武神移速
                HookFunc(BaseMonoAvatar, "Update", 0, BaseMonoAvatar_Update, &_BaseMonoAvatar_Update);
                HookFunc(BaseMonoAvatar, "set_MoveSpeedRatio", 1,
                         BaseMonoAvatar_set_MoveSpeedRatio, &_BaseMonoAvatar_set_MoveSpeedRatio);

                //人偶移速 (高刷新率不需要人工调用)
                HookFunc(BaseMonoElf, "set_MoveSpeedRatio", 1, BaseMonoElf_set_MoveSpeedRatio, &_BaseMonoElf_set_MoveSpeedRatio);
            }

            if (OpenFuncs->count("过热冷却")) //过热冷却
                //源函数最底下的匿名函数 注意Mathf$$Clamp01的调用
                HookFunc(AbilityAvatarWeaponOverHeatMixin, "UpdateOverheatDisplayValue", 2, AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue,
                         &_AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue);

            if (OpenFuncs->count("吸血吸能")) //吸血吸能
            {
                //LevelActor$$ResetComboTimer 调用 BaseAbilityActor::GetProperty
                HookFunc(BaseAbilityActor, "PFMHJHKOJJC", 1, BaseAbilityActor_GetProperty, &_BaseAbilityActor_GetProperty);
            }

            if (OpenFuncs->count("暂停事件")) // 暂停事件处理
            {
                //按钮接口
                HookFunc(LevelDesignManager, "SetPause", 1, LevelDesignManager_SetPause, &_LevelDesignManager_SetPause);
                { //事件

                    if (OpenFuncs->count("东方仗助")) //不灭砖石: 重置女武神血量
                    {
                        //间接调用SetAvatarDefenseRatio
                        HookFunc(LevelDesignManager, "SetAvatarDefenseRatio", 1,
                                 LevelDesignManager_SetAvatarDefenseRatio, &_LevelDesignManager_SetAvatarDefenseRatio);
                        //重置女武神血量模块
                        HookFunc(AvatarActor, "KIHEEHNIIGH", 1,
                                 AvatarActor_SetAvatarDefenseRatio, &_AvatarActor_SetAvatarDefenseRatio);
                    }

                    if (OpenFuncs->count("DIO")) //砸瓦鲁多: 时停击杀
                        HookFunc(LevelDesignManager, "KillAllMonstersIter", 3,
                                 LevelDesignManager_KillAllMonstersIter, &_LevelDesignManager_KillAllMonstersIter);

                    if (OpenFuncs->count("空条承太郎")) //食堂泼辣酱: 强制修改怪物血量
                    {
                        //间接调用MonsterActor_ForceRemoveImmediatelly
                        HookFunc(LevelDesignManager, "ClearAllMonsters", 1,
                                 LevelDesignManager_ClearAllMonsters, &_LevelDesignManager_ClearAllMonsters);
                        //对所有MonsterActor操作
                        HookFunc(MonsterActor, "CJKMKPEAGDJ", 0,
                                 MonsterActor_ForceRemoveImmediatelly, &_MonsterActor_ForceRemoveImmediatelly);
                    }

                    if (OpenFuncs->count("迪亚波罗")) //迪亚波罗: 倒计时操作
                    {
                        //间接调用SetCountDownSpeedRatio
                        HookFunc(LevelDesignManager, "SetInLevelTimeCountDownSpeedRatio", 2,
                                 LevelDesignManager_SetInLevelTimeCountDownSpeedRatio,
                                 &_LevelDesignManager_SetInLevelTimeCountDownSpeedRatio);
                        //操作倒计时模块
                        HookFunc(LevelActorCountDownPlugin, "SetCountDownSpeedRatio", 2,
                                 LevelActorCountDownPlugin_SetCountDownSpeedRatio,
                                 &_LevelActorCountDownPlugin_SetCountDownSpeedRatio);
                    }
                }
            }

            if (OpenFuncs->count("攻速")) //攻速
                HookFunc(BaseMonoAvatar, "GetFixedAttackSpeedRatio", 0,
                         BaseMonoAvatar_GetFixedAttackSpeedRatio, &_BaseMonoAvatar_GetFixedAttackSpeedRatio);

            if (OpenFuncs->count("动能系列")) //动能系列
            {
                HookFunc(ActorAbilityPlugin, "GetDynamicFloat", 1,
                         ActorAbilityPlugin_GetDynamicFloat, &_ActorAbilityPlugin_GetDynamicFloat);

                // HookFunc(ActorAbilityPlugin, "AddDynamicFloat", 2,
                //          ActorAbilityPlugin_AddDynamicFloat, &_ActorAbilityPlugin_AddDynamicFloat);

                HookFunc(ActorAbilityPlugin, "AddDynamicFloatWithRange", 4,
                         ActorAbilityPlugin_AddDynamicFloatWithRange, &_ActorAbilityPlugin_AddDynamicFloatWithRange);
            }

            if (OpenFuncs->count("破甲")) //破甲
                //直接查看类中只有两个参数的函数 备用 AbilityShieldMixin$$CalculateDisplayRatio
                HookFunc(AbilityShieldMixin, "OnShieldChanged", 2,
                         AbilityShieldMixin_OnShieldChanged, &_AbilityShieldMixin_OnShieldChanged);

            if (OpenFuncs->count("超限模式")) //超限模式
            {
                HookFunc(AttackResult, "GetTotalDamage", 0, AttackResult_GetTotalDamage, &_AttackResult_GetTotalDamage);
                HookFunc(MonsterActor, "OnBeingHitResolve", 1, MonsterActor_OnBeingHitResolve, &_MonsterActor_OnBeingHitResolve);
            }

            HookFunc(DamageModelLogic, "KFJJGCMBFLE", 3,
                     DamageModelLogic_GetNatureDamageBonusRatio, &_DamageModelLogic_GetNatureDamageBonusRatio);
        }
    }
    else if (!MonoMTP && !strcmp(name, "MonoMTP") && (MonoMTP = result))
    {
        //MTP登录
        HookFunc(MonoMTP, "Tp2UserLogin", 4, MonoMTP_Tp2UserLogin, &_MonoMTP_Tp2UserLogin);
    }

    return result;
}
