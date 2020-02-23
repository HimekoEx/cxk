#pragma once
#include "MiHoYoSDK.h"

//il2cpp原生C#字符串获取
extern void *CString_New(const char *str);

//饭哥的C#字符串解析
class CSharpString
{
private:
    JNIEnv *env;
    int32_t length;
    jstring string;
    const char *chars;
    std::string strs;

public:
    CSharpString(void *cSharpString)
    {
        env = MiHoYoSDK::EnsureEnvCreated();
        length = *(int32_t *)((char *)cSharpString + 0x8);
        string = env->NewString((const jchar *)((char *)cSharpString + 0xc), length);
        if (string != nullptr)
            strs = chars = env->GetStringUTFChars(string, nullptr);
        else
            strs = chars = nullptr;
    }

    std::string get()
    {
        if (length == 0)
            return "(null)";
        if (string == nullptr)
            return "(error!)";
        return strs;
    }

    const char *c_str()
    {
        if (length == 0)
            return "(null)";
        if (string == nullptr)
            return "(error!)";
        return chars;
    }

    int32_t getLength()
    {
        return length;
    }

    static void *New(const char *str)
    {
        return CString_New(str);
    }

    ~CSharpString()
    {
        env->ReleaseStringUTFChars(string, chars);
        env->DeleteLocalRef(string);
    }
};