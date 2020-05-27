#include "tersafe2.h"

// 加载tersafe2库文件
bool Hook::Loaded::LoadTersafe2Lib(void *handle)
{
    using namespace MiHoYoSDK::StaticData;

    ulong lib_addr = MiHoYoSDK::GetModuleAddr(GET_SAFE_CHAR(STR_tpsafeLib));
    if (lib_addr == 0ul)
        return RT("T2 Error 0x01") && CCC("tpsafeLib NULL Error!");

    if (Sync::Off_MTP <= 0)
        return RT("T2 Error 0x02") && CCC("Off_MTP NULL Error!");

    //Sync::Off_MTP = 0xD6820;
    zzReplace(lib_addr + Sync::Off_MTP, Tersafe2::SysOpen, &Tersafe2::_SysOpen);

#ifndef RELEASE
    RT("MTP Hook Done...");
#endif

    return true;
}

//文件开启函数
int (*Hook::Loaded::Tersafe2::_SysOpen)(int, const char *, int, int) = nullptr;
int Hook::Loaded::Tersafe2::SysOpen(int a1, const char *a2, int a3, int a4)
{
    return _SysOpen(a1, "", a3, a4);
}
