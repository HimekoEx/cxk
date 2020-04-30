#pragma once
#include "src/sdk/Base.h"

//Hook架构
namespace Hook
{
    //Dlopen模块
    namespace Dlopen
    {

        //tpsafe劫持锁
        extern bool HookLock_Tpsafe;
        //il2cpp劫持锁
        extern bool HookLock_Il2cpp;

        // 劫持chaos的dlopen
        void ReplaceDlopen();
        // 动态库文件加载接口
        bool LoadedLib(const char *name, void *handle);

        //Dlopen
        void *DlopenV00(const char *name, int flag);
        extern void *(*_DlopenV00)(const char *, int);

        //v19 Dlopen
        void *DlopenV19(const char *name, int flag1, int flag2);
        extern void *(*_DlopenV19)(const char *, int, int);

        //v24 Dlopen
        void *DlopenV24(const char *name, int flag1, int flag2, int flag3);
        extern void *(*_DlopenV24)(const char *, int, int, int);

        //v26 Dlopen
        void *DlopenV26(const char *name, int flag1, int flag2, int flag3);
        extern void *(*_DlopenV26)(const char *, int, int, int);

    } // namespace Dlopen
} // namespace Hook
