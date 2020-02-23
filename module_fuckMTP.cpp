#include "module.h"

int (*_tersafe_sysopen)(int, const char *, int, int, int, int, int, int, int, int, int);
int tersafe_sysopen(int a1, const char *a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
{
    return _tersafe_sysopen(a1, "", a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

//干MTP va检测
bool FuckingMTP(int32_t handle)
{
    using namespace MiHoYoSDK;
    using namespace MiHoYoSDK::StaticData;
    ulong lib_addr = GetModuleBaseAdderss(GET_SAFE_CHAR(tpsafeLib));
    if (lib_addr == 0UL)
        return RunTimeLog("FPC Error: 0x00") && CloseChaosCore1("NULL Error") && CloseChaosCore2();

    if (Sync::MTP_Off <= 0)
        return RunTimeLog("FPC Error: 0x01") && CloseChaosCore1("NULL Error") && CloseChaosCore2();

    // Sync::MTP_Off = 0xC2A20;
    // LOGE("mtp_off: 0x%X", Sync::MTP_Off);
    zzReplace(lib_addr + Sync::MTP_Off, tersafe_sysopen, &_tersafe_sysopen);

    return true;
}