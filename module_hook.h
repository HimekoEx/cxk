#pragma once
#include <global_fix.h>

//修正函数的地址
inline void *CorrectGetMethodAddr(void *symbol)
{
    return ((char *)symbol + (*(long *)(symbol) << 8 >> 6) + (*(long *)((char *)symbol + (*(long *)(symbol) << 8 >> 6) + 12) << 8 >> 6) + 20);
}

//修正函数的地址
inline void *CorrectGetClassAddr(void *symbol)
{
    return ((char *)symbol + (*(long *)(symbol) << 8 >> 6) + (*(long *)((char *)symbol + (*(long *)(symbol) << 8 >> 6) + 8) << 8 >> 6) + 16);
}

//修正函数的地址
inline void *CorrectB(void *symbol)
{
    return ((char *)symbol + (*(long *)(symbol) << 8 >> 6) + 8);
}

//AttackResult 类 成员 damage
inline float *PtrAttack_Damage(void *self)
{
    return (float *)((char *)self + 0x8);
}

//AttackResult 类 成员 fireDamage
inline float *PtrAttack_FireDamage(void *self)
{
    return (float *)((char *)self + 0xC);
}

//AttackResult 类 成员 thunderDamage
inline float *PtrAttack_ThunderDamage(void *self)
{
    return (float *)((char *)self + 0x10);
}

//AttackResult 类 成员 iceDamage
inline float *PtrAttack_IceDamage(void *self)
{
    return (float *)((char *)self + 0x14);
}

//BaseAbilityActor 类 成员 maxHP
inline void *PtrActor_MaxHP(void *self)
{
    return (void *)((char *)self + 0x148);
}

//BaseAbilityActor 类 成员 maxSP
inline void *PtrActor_MaxSP(void *self)
{
    return (void *)((char *)self + 0x158);
}

//BaseAbilityActor 类 成员 HP
inline void *PtrActor_HP(void *self)
{
    return (void *)((char *)self + 0x168);
}

//BaseAbilityActor 类 成员 SP
inline void *PtrActor_SP(void *self)
{
    return (void *)((char *)self + 0x178);
}