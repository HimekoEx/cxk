#include "src/hook/hook.h"
using namespace MiHoYoSDK::StaticData;
using namespace Hook::Uitls;
using namespace Hook::Loaded;
using namespace Hook::Loaded::Il2cpp;

// 加载il2cpp库文件
bool Hook::Loaded::LoadIl2cppLib(void *handle)
{
    sleep(2);

    void *string_new_addr = dlsym(handle, GET_SAFE_CHAR(STR_il2cpp_string_new));
    if (!string_new_addr)
        RT("SN Null Error") && CCC("string_new_addr Is Null!");
    zzReplace(Amend_B(string_new_addr), String_New, &_String_New);

    void *class_get_methods_addr = dlsym(handle, GET_SAFE_CHAR(STR_il2cpp_class_get_methods));
    if (!class_get_methods_addr)
        RT("MS Null Error") && CCC("class_get_methods_addr Is Null!");
    zzReplace(Amend_B(class_get_methods_addr), Class_GetMethods, &_Class_GetMethods);

    void *class_get_fields_addr = dlsym(handle, GET_SAFE_CHAR(STR_il2cpp_class_get_fields));
    if (!class_get_fields_addr)
        RT("FS Null Error") && CCC("class_get_fields_addr Is Null!");
    zzReplace(Amend_B(class_get_fields_addr), Class_GetFields, &_Class_GetFields);

    void *class_get_method_from_name_addr = dlsym(handle, GET_SAFE_CHAR(STR_il2cpp_class_get_method_from_name));
    if (!class_get_method_from_name_addr)
        RT("GM Null Error") && CCC("class_get_method_from_name_addr Is Null!");
    zzReplace(Amend_ClassGetMethodFromNameFlags(class_get_method_from_name_addr),
              Class_GetMethodFromNameFlags, &_Class_GetMethodFromNameFlags);

    void *class_from_name_addr = dlsym(handle, GET_SAFE_CHAR(STR_il2cpp_class_from_name));
    if (!class_from_name_addr)
        RT("GC Null Error") && CCC("class_from_name_addr Is Null!");
    zzReplace(Amend_ClassFromName(class_from_name_addr), Class_FromName, &_Class_FromName);

    return true;
}

//生成C#字符串
Il2CppString *(*Il2cpp::_String_New)(const char *) = nullptr;
Il2CppString *Il2cpp::String_New(const char *str)
{
    return _String_New(str);
}

//获取Class中所有成员方法
MethodInfo *(*Il2cpp::_Class_GetMethods)(Il2CppClass *, void **) = nullptr;
MethodInfo *Il2cpp::Class_GetMethods(Il2CppClass *klass, void **iter)
{
    return _Class_GetMethods(klass, iter);
}

//获取Class中所有成员字段
FieldInfo *(*Il2cpp::_Class_GetFields)(Il2CppClass *, void **) = nullptr;
FieldInfo *Il2cpp::Class_GetFields(Il2CppClass *klass, void **iter)
{
    return _Class_GetFields(klass, iter);
}

//指定名称获取Class成员方法
MethodInfo *(*Il2cpp::_Class_GetMethodFromNameFlags)(Il2CppClass *, const char *, int, int32_t) = nullptr;
MethodInfo *Il2cpp::Class_GetMethodFromNameFlags(Il2CppClass *klass, const char *name, int argsCount, int32_t flags)
{
    return _Class_GetMethodFromNameFlags(klass, name, argsCount, flags);
}

//指定名称获取Class
Il2CppClass *(*Il2cpp::_Class_FromName)(const Il2CppImage *, const char *, const char *) = nullptr;
Il2CppClass *Il2cpp::Class_FromName(const Il2CppImage *image, const char *namespaze, const char *name)
{
    return Logic::HookClass((Il2CppImage *)image, namespaze, name);
}
