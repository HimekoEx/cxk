#include "src/hook/hook.h"

bool Hook::Dlopen::HookLock_Tpsafe = false;
bool Hook::Dlopen::HookLock_Il2cpp = false;

// 劫持chaos的dlopen
void Hook::Dlopen::ReplaceDlopen()
{
    using namespace MiHoYoSDK;
    using namespace MiHoYoSDK::StaticData;

    std::string lib_path = FileLine(GET_SAFE_DATA(PATH_Pack));
    lib_path += GET_SAFE_DATA(PATH_LIBchaos);

    void *handle = dlopen(lib_path.c_str(), RTLD_NOW);
    if (!handle)
        RT("RD Error 0x01") && CCC("handle NULL!");

    void *v00_addr = dlsym(handle, GET_SAFE_CHAR(STR_dlopenV00Func));
    if (!v00_addr)
        RT("RD Error 0x02") && CCC("v00_addr NULL!");

    void *v19_addr = dlsym(handle, GET_SAFE_CHAR(STR_dlopenV19Func));
    if (!v19_addr)
        RT("RD Error 0x03") && CCC("v19_addr NULL!");

    void *v24_addr = dlsym(handle, GET_SAFE_CHAR(STR_dlopenV24Func));
    if (!v24_addr)
        RT("RD Error 0x04") && CCC("v24_addr NULL!");

    void *v26_addr = dlsym(handle, GET_SAFE_CHAR(STR_dlopenV26Func));
    if (!v26_addr)
        RT("RD Error 0x05") && CCC("v26_addr NULL!");

    zzReplace(v00_addr, DlopenV00, &_DlopenV00);
    zzReplace(v19_addr, DlopenV19, &_DlopenV19);
    zzReplace(v24_addr, DlopenV24, &_DlopenV24);
    zzReplace(v26_addr, DlopenV26, &_DlopenV26);

    dlclose(handle);
#ifdef RELEASE
    RT("RD hook done...");
#endif
}

// 动态库文件加载接口
bool Hook::Dlopen::LoadedLib(const char *name, void *handle)
{
    using namespace MiHoYoSDK::StaticData;

    if (handle == nullptr)
        return false;

    if (!HookLock_Tpsafe && strstr(name, GET_SAFE_CHAR(STR_tpsafeLib)))
        return HookLock_Tpsafe = Loaded::LoadTersafe2Lib(handle);

    if (!HookLock_Il2cpp && strstr(name, GET_SAFE_CHAR(STR_il2cppLib)))
        return HookLock_Il2cpp = Loaded::LoadIl2cppLib(handle);

    return false;
}

void *(*Hook::Dlopen::_DlopenV00)(const char *, int) = nullptr;
void *Hook::Dlopen::DlopenV00(const char *name, int flag)
{
    void *handle = _DlopenV00(name, flag);
    LoadedLib(name, handle);
    return handle;
}

void *(*Hook::Dlopen::_DlopenV19)(const char *, int, int) = nullptr;
void *Hook::Dlopen::DlopenV19(const char *name, int flag1, int flag2)
{
    void *handle = _DlopenV19(name, flag1, flag2);
    LoadedLib(name, handle);
    return handle;
}

void *(*Hook::Dlopen::_DlopenV24)(const char *, int, int, int) = nullptr;
void *Hook::Dlopen::DlopenV24(const char *name, int flag1, int flag2, int flag3)
{
    void *handle = _DlopenV24(name, flag1, flag2, flag3);
    LoadedLib(name, handle);
    return handle;
}

void *(*Hook::Dlopen::_DlopenV26)(const char *, int, int, int) = nullptr;
void *Hook::Dlopen::DlopenV26(const char *name, int flag1, int flag2, int flag3)
{
    void *handle = _DlopenV26(name, flag1, flag2, flag3);
    LoadedLib(name, handle);
    return handle;
}
