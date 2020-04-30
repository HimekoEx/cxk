#pragma once
#include "src/sdk/MiHoYoSDK.h"
#include "src/hook/il2cpp/il2cpp-api.h"

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {

        // 加载il2cpp库文件
        bool LoadIl2cppLib(void *handle);

        //Il2cpp模块
        namespace Il2cpp
        {

            // 生成C#字符串
            Il2CppString *String_New(const char *str);
            extern Il2CppString *(*_String_New)(const char *);

            // 获取Class中所有成员方法
            MethodInfo *Class_GetMethods(Il2CppClass *klass, void **iter);
            extern MethodInfo *(*_Class_GetMethods)(Il2CppClass *, void **);

            // 获取Class中所有成员字段
            FieldInfo *Class_GetFields(Il2CppClass *klass, void **iter);
            extern FieldInfo *(*_Class_GetFields)(Il2CppClass *, void **);

            // 指定名称获取Class成员方法
            MethodInfo *Class_GetMethodFromNameFlags(Il2CppClass *klass, const char *name, int argsCount, int32_t flags);
            extern MethodInfo *(*_Class_GetMethodFromNameFlags)(Il2CppClass *, const char *, int, int32_t);

            // 指定名称获取Class
            Il2CppClass *Class_FromName(const Il2CppImage *image, const char *namespaze, const char *name);
            extern Il2CppClass *(*_Class_FromName)(const Il2CppImage *, const char *, const char *);

        } // namespace Il2cpp
    }     // namespace Loaded
} // namespace Hook
