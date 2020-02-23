#include "module.h"
using namespace Sync;

namespace
{
ulong Down_23 = 0xEA000023;
ulong Down_38 = 0xEA000038;
ulong Down_47 = 0xEA000047;
ulong Down_04 = 0xEA000004;

ulong NOP = 0xE320F000;
ulong BX_LR = 0xE12FFF1E;

ulong MOV_R0_f0_1 = 0xE3A005F7;
ulong MOV_R0_f0_25 = 0xE3A005FA;
ulong MOV_R0_f0_5 = 0xE3A0043F;
ulong MOV_R0_f1_5 = 0xE3A005FF;

ulong MOV_R0_43000000 = 0xE3A00443;
ulong MOV_R0_44000000 = 0xE3A00444;
ulong MOV_R0_45000000 = 0xE3A00445;
ulong MOV_R0_46000000 = 0xE3A00446;
ulong MOV_R0_47000000 = 0xE3A00447;

ulong VMOV_S4_R0 = 0xEE020A10;

ulong Down_17 = 0x8A000017;
ulong MOV_R0_48000000 = 0xE3A00312;
ulong VMOV_S0_R0 = 0xEE000A10;
ulong VCMP_S18_S0 = 0xEEB49A40;
ulong VMRS = 0xEEF1FA10;
ulong BLS_2A = 0x9A00002A;
ulong MOV_R0_3F000000 = 0xE3A0043F;
ulong MOV_R1_600000 = 0xE3A01606;
ulong ADD_R0_R0_R1 = 0xE0800001;
ulong VMUL_S18_S18_S0 = 0xEE299A00;
ulong Down_24 = 0xEA000024;

} // namespace

//初始化patch
void FirstFucking()
{
    //三星条件选择器
    if (GetStateOrValue("三星", "", true))
        zzCodePatch(Address[0] + 0xA4, Down_38);

    //解锁服装
    // zzCodePatch(Address[1] + 0xFC, NOP);

    //皮肤重置
    // zzCodePatch(Address[2] + 0x1D8, Down_23);

    //触摸隐私部位
    zzCodePatch(Address[3] + 0xD4, NOP);
    zzCodePatch(Address[3] + 0x154, NOP);
}

//循环patch
void FuckingLIB()
{
}