#pragma once
#include "src/sdk/MiHoYoSDK.h"
#include "src/hook/il2cpp/il2cpp-api.h"
#include "src/hook/logic/Enum.h"

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {
        //逻辑模块
        namespace Logic
        {

            // 网络管理器$$获取持久UUID
            Il2cpp::Il2CppString *NetworkManager_GetPersistentUUID(Il2cpp::Il2CppObject *self);
            extern Il2cpp::Il2CppString *(*_NetworkManager_GetPersistentUUID)(Il2cpp::Il2CppObject *);

            // MTP$$Tp2用户登录
            void MonoMTP_Tp2UserLogin(Il2cpp::Il2CppObject *self, Tp2Entry accountType, int worldID, Il2cpp::Il2CppString *openID, Il2cpp::Il2CppString *roleID);
            extern void (*_MonoMTP_Tp2UserLogin)(Il2cpp::Il2CppObject *, Tp2Entry, int, Il2cpp::Il2CppString *, Il2cpp::Il2CppString *);

            // SafeFloat$$获取值
            float SafeFloat_get_Value(Il2cpp::Il2CppObject *self);
            extern float (*_SafeFloat_get_Value)(Il2cpp::Il2CppObject *);

            // SafeFloat$$设置值
            void SafeFloat_set_Value(Il2cpp::Il2CppObject *self, float value);
            extern void (*_SafeFloat_set_Value)(Il2cpp::Il2CppObject *, float);

            // 单例管理$$添加单例
            void SingletonManager_AddSingletonInstance(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppObject *singleton, Il2cpp::Il2CppString *typeName);
            extern void (*_SingletonManager_AddSingletonInstance)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *);

            // 单例管理$$获取单例
            Il2cpp::Il2CppObject *SingletonManager_GetSingletonInstance(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppString *typeName);
            extern Il2cpp::Il2CppObject *(*_SingletonManager_GetSingletonInstance)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *);

            // 关卡反作弊插件&&收集反作弊数据
            void LevelAntiCheatPlugin_CollectAntiCheatData(Il2cpp::Il2CppObject *self, bool isMultiTeam);
            extern void (*_LevelAntiCheatPlugin_CollectAntiCheatData)(Il2cpp::Il2CppObject *, bool);

            // 关卡反作弊插件&&添加数据
            void LevelAntiCheatPlugin_AddData(Il2cpp::Il2CppObject *self, StageCheatData_Type type, float value);
            extern void (*_LevelAntiCheatPlugin_AddData)(Il2cpp::Il2CppObject *, StageCheatData_Type, float);

            // 限制女武神挑战$$是已完成
            bool LimitAvatarChallege_IsFinished(Il2cpp::Il2CppObject *self);

            // BaseMonoAvatar$$被击中
            void BaseMonoAvatar_BeHit(Il2cpp::Il2CppObject *self);

            // Gal触摸模块$$获取是Gal触摸和谐
            bool GalTouchModule_get_IsGalTouchHeXie(Il2cpp::Il2CppObject *self);

            // 女武神管理$$尝试获取当前女武神
            Il2cpp::Il2CppObject *AvatarManager_TryGetLocalAvatar(Il2cpp::Il2CppObject *self);
            extern Il2cpp::Il2CppObject *(*_AvatarManager_TryGetLocalAvatar)(Il2cpp::Il2CppObject *);

            // BaseMonoAvatar$$刷新控制器
            void BaseMonoAvatar_RefreshController(Il2cpp::Il2CppObject *self);
            extern void (*_BaseMonoAvatar_RefreshController)(Il2cpp::Il2CppObject *);

            // BaseMonoMonster$$设置攻击目标
            void BaseMonoMonster_SetAttackTarget(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppObject *newTarget);
            extern void (*_BaseMonoMonster_SetAttackTarget)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppObject *);

            // 基础能力角色$$可以造成伤害By运行时ID
            bool BaseAbilityActor_CanBeDamageByRuntimeid(Il2cpp::Il2CppObject *self, uint runtimeID);
            extern bool (*_BaseAbilityActor_CanBeDamageByRuntimeid)(Il2cpp::Il2CppObject *, uint);

            // 基础能力角色$$回复SP
            void BaseAbilityActor_HealSP(Il2cpp::Il2CppObject *self, float amount, LevelSPRecoverSource source);
            extern void (*_BaseAbilityActor_HealSP)(Il2cpp::Il2CppObject *, float, LevelSPRecoverSource);

            // MonoGoods$$更新
            void MonoGoods_Update(Il2cpp::Il2CppObject *self);
            extern void (*_MonoGoods_Update)(Il2cpp::Il2CppObject *);

            // 女武神角色$$可以使用技能
            bool AvatarActor_CanUseSkill(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppString *skillName);
            extern bool (*_AvatarActor_CanUseSkill)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *);

            // 女武神角色$$是换人在CD中
            bool AvatarActor_IsSwitchInCD(Il2cpp::Il2CppObject *self);
            extern bool (*_AvatarActor_IsSwitchInCD)(Il2cpp::Il2CppObject *);

            // 关卡设计管理$$战斗开始
            void LevelDesignManager_BattleBegin(Il2cpp::Il2CppObject *self);
            extern void (*_LevelDesignManager_BattleBegin)(Il2cpp::Il2CppObject *);

            // 关卡设计管理$$结束关卡
            void LevelDesignManager_EndLevel(Il2cpp::Il2CppObject *self, LevelEndReason reason, int endCgId);
            extern void (*_LevelDesignManager_EndLevel)(Il2cpp::Il2CppObject *, LevelEndReason, int);

            // BaseMonoAvatar$$更新
            void BaseMonoAvatar_Update(Il2cpp::Il2CppObject *self);
            extern void (*_BaseMonoAvatar_Update)(Il2cpp::Il2CppObject *);

            // BaseMonoAvatar$$设置移动速度倍率
            void BaseMonoAvatar_set_MoveSpeedRatio(Il2cpp::Il2CppObject *self, float value);
            extern void (*_BaseMonoAvatar_set_MoveSpeedRatio)(Il2cpp::Il2CppObject *, float);

            // BaseMonoElf$$设置移动速度倍率
            void BaseMonoElf_set_MoveSpeedRatio(Il2cpp::Il2CppObject *self, float value);
            extern void (*_BaseMonoElf_set_MoveSpeedRatio)(Il2cpp::Il2CppObject *, float);

            // 女武神武器过热$$更新过热显示值
            void AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue(Il2cpp::Il2CppObject *self, float fromHeat, float toHeat);
            extern void (*_AbilityAvatarWeaponOverHeatMixin_UpdateOverheatDisplayValue)(Il2cpp::Il2CppObject *, float, float);

            // 基础能力角色$$获取属性
            float BaseAbilityActor_GetProperty(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppString *propertyKey);
            extern float (*_BaseAbilityActor_GetProperty)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *);

            // 关卡设计管理$$核心
            void LevelDesignManager_Core(Il2cpp::Il2CppObject *self);
            extern void (*_LevelDesignManager_Core)(Il2cpp::Il2CppObject *);

            // 关卡管理$$设置暂停
            void LevelManager_SetPause(Il2cpp::Il2CppObject *self, bool pause);
            extern void (*_LevelManager_SetPause)(Il2cpp::Il2CppObject *, bool);

            // 关卡设计管理$$设置暂停
            void LevelDesignManager_SetPause(Il2cpp::Il2CppObject *self, bool pause);
            extern void (*_LevelDesignManager_SetPause)(Il2cpp::Il2CppObject *, bool);

            // 关卡设计管理$$设置女武神防御倍率
            void LevelDesignManager_SetAvatarDefenseRatio(Il2cpp::Il2CppObject *self, float ratio);
            extern void (*_LevelDesignManager_SetAvatarDefenseRatio)(Il2cpp::Il2CppObject *, float);

            // 女武神角色$$设置女武神防御倍率
            void AvatarActor_SetAvatarDefenseRatio(Il2cpp::Il2CppObject *self, float ratio);
            extern void (*_AvatarActor_SetAvatarDefenseRatio)(Il2cpp::Il2CppObject *, float);

            // 关卡设计管理$$击杀所有怪物Iter
            void LevelDesignManager_KillAllMonstersIter(Il2cpp::Il2CppObject *self, bool dropReward, bool killStatic, bool killUnacitve, bool isKilledByLocalAvatar);
            extern void (*_LevelDesignManager_KillAllMonstersIter)(Il2cpp::Il2CppObject *, bool, bool, bool, bool);

            // 关卡设计管理$$清除所有怪物
            void LevelDesignManager_ClearAllMonsters(Il2cpp::Il2CppObject *self, bool clearStatic);
            extern void (*_LevelDesignManager_ClearAllMonsters)(Il2cpp::Il2CppObject *, bool);

            // 怪物角色$$立即强制移除
            void MonsterActor_ForceRemoveImmediatelly(Il2cpp::Il2CppObject *self);
            extern void (*_MonsterActor_ForceRemoveImmediatelly)(Il2cpp::Il2CppObject *);

            // 关卡设计管理$$设置关卡内时间下降速度倍率
            void LevelDesignManager_SetInLevelTimeCountDownSpeedRatio(Il2cpp::Il2CppObject *self, float ratioInNormalTime, float ratioInWitchTime);
            extern void (*_LevelDesignManager_SetInLevelTimeCountDownSpeedRatio)(Il2cpp::Il2CppObject *, float, float);

            // 关卡角色倒计时插件$$设置倒计时速度倍率
            void LevelActorCountDownPlugin_SetCountDownSpeedRatio(Il2cpp::Il2CppObject *self, float ratioInNormalTime, float ratioInWitchTime);
            extern void (*_LevelActorCountDownPlugin_SetCountDownSpeedRatio)(Il2cpp::Il2CppObject *, float, float);

            // BaseMonoAvatar$$获取固定攻击速度倍率
            float BaseMonoAvatar_GetFixedAttackSpeedRatio(Il2cpp::Il2CppObject *self);
            extern float (*_BaseMonoAvatar_GetFixedAttackSpeedRatio)(Il2cpp::Il2CppObject *);

            // 角色能力插件$$获取动态浮点
            Il2cpp::Il2CppObject *ActorAbilityPlugin_GetDynamicFloat(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppString *key);
            extern Il2cpp::Il2CppObject *(*_ActorAbilityPlugin_GetDynamicFloat)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *);

            // 角色能力插件$$添加动态浮点
            void ActorAbilityPlugin_AddDynamicFloat(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppString *key, float value);
            extern void (*_ActorAbilityPlugin_AddDynamicFloat)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *, float);

            // 角色能力插件$$添加动态浮点为范围
            void ActorAbilityPlugin_AddDynamicFloatWithRange(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppString *key, float value, float min, float max);
            extern void (*_ActorAbilityPlugin_AddDynamicFloatWithRange)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppString *, float, float, float);

            // 护盾能力插件$$在护盾改变
            void AbilityShieldMixin_OnShieldChanged(Il2cpp::Il2CppObject *self, float from, float to);
            extern void (*_AbilityShieldMixin_OnShieldChanged)(Il2cpp::Il2CppObject *, float, float);

            // 攻击结果$$获取总量伤害
            float AttackResult_GetTotalDamage(Il2cpp::Il2CppObject *self);
            extern float (*_AttackResult_GetTotalDamage)(Il2cpp::Il2CppObject *);

            // 怪物角色$$在被击中解决
            bool MonsterActor_OnBeingHitResolve(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppObject *evt);
            extern bool (*_MonsterActor_OnBeingHitResolve)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppObject *);

            // 伤害模型逻辑$$获取本质伤害加成倍率
            float DamageModelLogic_GetNatureDamageBonusRatio(Il2cpp::Il2CppObject *self, EntityNature attackerNature, EntityNature attackeeNature, Il2cpp::Il2CppObject *attackee);
            extern float (*_DamageModelLogic_GetNatureDamageBonusRatio)(Il2cpp::Il2CppObject *, EntityNature, EntityNature, Il2cpp::Il2CppObject *);

            // 关卡演员$$重置连击计时器
            void LevelActor_ResetComboTimer(Il2cpp::Il2CppObject *self);
            extern void (*_LevelActor_ResetComboTimer)(Il2cpp::Il2CppObject *);

            // 闪避能力插件$$在能力触发
            void AbilityEvadeMixin_OnAbilityTriggered(Il2cpp::Il2CppObject *self, Il2cpp::Il2CppObject *evt);
            extern void (*_AbilityEvadeMixin_OnAbilityTriggered)(Il2cpp::Il2CppObject *, Il2cpp::Il2CppObject *);

            // 女武神角色$$初始化Debuff持续时间倍率
            void AvatarActor_InitDebuffDurationRatio(Il2cpp::Il2CppObject *self);
            extern void (*_AvatarActor_InitDebuffDurationRatio)(Il2cpp::Il2CppObject *);

            // 服装模块$$设置女武神服装ID
            bool DressModule_SetAvatarDressId(Il2cpp::Il2CppObject *self, int avatarId, int dressId, bool forceSendReq, bool forceNotSendReq);
            extern bool (*_DressModule_SetAvatarDressId)(Il2cpp::Il2CppObject *, int, int, bool, bool);

        } // namespace Logic
    }     // namespace Loaded
} // namespace Hook
