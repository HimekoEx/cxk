#include "src/sync/module.h"
using namespace Sync;

namespace
{

static ulong Down_38 = 0xEA000038;

static ulong NOP = 0xE320F000;
// static ulong BX_LR = 0xE12FFF1E;

// static ulong MOV_R0_f0_1 = 0xE3A005F7;
// static ulong MOV_R0_f0_25 = 0xE3A005FA;
// static ulong MOV_R0_f0_5 = 0xE3A0043F;
// static ulong MOV_R0_f1_5 = 0xE3A005FF;

// static ulong MOV_R0_43000000 = 0xE3A00443;
// static ulong MOV_R0_44000000 = 0xE3A00444;
// static ulong MOV_R0_45000000 = 0xE3A00445;
// static ulong MOV_R0_46000000 = 0xE3A00446;
// static ulong MOV_R0_47000000 = 0xE3A00447;

} // namespace

//初始化patch
void FirstFucking()
{
    //三星条件选择器
    if (GetStateOrValue("三星", "", true))
        zzCodePatch(Address[0] + 0xA4, Down_38);

    //触摸隐私部位
    zzCodePatch(Address[1] + 0xD4, NOP);
    zzCodePatch(Address[1] + 0x154, NOP);

    //解锁服装
    zzCodePatch(Address[2] + 0xFC, NOP);

    //皮肤重置 报废状态
    zzCodePatch(Address[3] + 0x26C, NOP);
}

//循环patch
void FuckingLIB()
{
}