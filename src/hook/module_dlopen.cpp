#include "src/sync/module.h"

using namespace MiHoYoSDK;
using namespace MiHoYoSDK::StaticData;

static bool hook_lock_il2cpp = false;
static bool hook_lock_tpsafe = false;
static std::string LIB_PATH;

//初始化lib路径
void initLibPath()
{
    std::string package = ReadFileLine(GET_SAFE_DATA(cfgPath));
    LIB_PATH += package;
    LIB_PATH += GET_SAFE_DATA(libPath);
}

//so加载
bool onSoLoaded(const char *name, void *handle)
{
    if (handle == NULL)
        return false;
    if (!hook_lock_tpsafe && strstr(name, GET_SAFE_CHAR(tpsafeLib)))
        return hook_lock_tpsafe = FuckingMTP((int32_t)handle);
    if (hook_lock_il2cpp)
        return false;
    if (!strstr(name, GET_SAFE_CHAR(il2cppLib)))
        return false;

    hook_lock_il2cpp = true;
    FuckingIl2cpp(handle);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////
void *(*_R_dlopen_V26)(const char *, int, int, int) = nullptr;
void *R_dlopen_V26(const char *name, int flag1, int flag2, int flag3)
{
    void *handle = _R_dlopen_V26(name, flag1, flag2, flag3);
    onSoLoaded(name, handle);
    return handle;
}

void *(*_R_dlopen_V24)(const char *, int, int, int) = nullptr;
void *R_dlopen_V24(const char *name, int flag1, int flag2, int flag3)
{
    void *handle = _R_dlopen_V24(name, flag1, flag2, flag3);
    onSoLoaded(name, handle);
    return handle;
}

void *(*_R_dlopen_V19)(const char *, int, int) = nullptr;
void *R_dlopen_V19(const char *name, int flag1, int flag2)
{
    void *handle = _R_dlopen_V19(name, flag1, flag2);
    onSoLoaded(name, handle);
    return handle;
}

void *(*_R_dlopen)(const char *, int) = nullptr;
void *R_dlopen(const char *name, int flag)
{
    void *handle = _R_dlopen(name, flag);
    onSoLoaded(name, handle);
    return handle;
}
//////////////////////////////////////////////////////////////////////////////////////

//代理chaos的dlopen
void ReplaceDlopen()
{
    initLibPath();
    void *handle = dlopen(LIB_PATH.c_str(), RTLD_NOW);
    if (!handle)
        RunTimeLog("RD Error: 0x00") && CloseChaosCore1("handle NULL!") && CloseChaosCore2();

    void *V26_addr = dlsym(handle, GET_SAFE_CHAR(dlopenV26Str));
    if (!V26_addr)
        RunTimeLog("RD Error: 0x01") && CloseChaosCore1("V26_addr NULL!") && CloseChaosCore2();

    void *V24_addr = dlsym(handle, GET_SAFE_CHAR(dlopenV24Str));
    if (!V24_addr)
        RunTimeLog("RD Error: 0x02") && CloseChaosCore1("V24_addr NULL!") && CloseChaosCore2();

    void *V19_addr = dlsym(handle, GET_SAFE_CHAR(dlopenV19Str));
    if (!V19_addr)
        RunTimeLog("RD Error: 0x03") && CloseChaosCore1("V19_addr NULL!") && CloseChaosCore2();

    void *dlopen_addr = dlsym(handle, GET_SAFE_CHAR(dlopenStr));
    if (!dlopen_addr)
        RunTimeLog("RD Error: 0x04") && CloseChaosCore1("dlopen_addr NULL!") && CloseChaosCore2();

    zzReplace(V26_addr, R_dlopen_V26, &_R_dlopen_V26);
    zzReplace(V24_addr, R_dlopen_V24, &_R_dlopen_V24);
    zzReplace(V19_addr, R_dlopen_V19, &_R_dlopen_V19);
    zzReplace(dlopen_addr, R_dlopen, &_R_dlopen);

    LOGE("dlopen hook done. handle >> 0x%lX", (long)handle);
}