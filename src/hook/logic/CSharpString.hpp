#pragma once
#include "src/hook/hook.h"

//Hook架构
namespace Hook
{
    //Lib加载模块
    namespace Loaded
    {
        //逻辑模块
        namespace Logic
        {

            //C#字符串解析
            class CSharpString
            {
            private:
                JNIEnv *env;
                int32_t length;
                jstring string;
                const char *chars;
                std::string strs;

            public:
                CSharpString(Il2cpp::Il2CppString *src)
                {
                    env = MiHoYoSDK::GetJEnv();
                    length = src->length;
                    string = env->NewString((const jchar *)(src->chars), length);
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

                int32_t getLength() { return length; }

                ~CSharpString()
                {
                    env->ReleaseStringUTFChars(string, chars);
                    env->DeleteLocalRef(string);
                }
            };

        } // namespace Logic
    }     // namespace Loaded
} // namespace Hook
