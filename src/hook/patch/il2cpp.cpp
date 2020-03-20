#include "src/hook/hook.h"
using namespace Sync;
using namespace Hook::Loaded;
using namespace Hook::Loaded::Patch::Const;

// 首次修改il2cpp
void Patch::FirstPatchIl2cpp()
{
    //三星条件选择器
    if (GetStateOrValue("三星", "", true))
        zzCodePatch(Address[0] + 0xA4, Down_x38);

    //触摸隐私部位
    zzCodePatch(Address[1] + 0xD4, NOP);
    zzCodePatch(Address[1] + 0x154, NOP);

    //解锁服装
    zzCodePatch(Address[2] + 0xFC, NOP);
}

// 循环修改il2cpp
void Patch::LoopPatchIl2cpp()
{
}
