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
                JNIEnv *mEnv = nullptr;
                int32_t mLength = 0;
                jstring mJstring = nullptr;
                const char *mChars = nullptr;
                std::string mStrs;

            public:
                CSharpString(Il2cpp::Il2CppString *src)
                {
                    mEnv = MiHoYoSDK::GetJEnv();
                    mLength = src->length;
                    mJstring = mEnv->NewString((const jchar *)(src->chars), mLength);
                    if (mJstring != nullptr)
                        mStrs = mChars = mEnv->GetStringUTFChars(mJstring, nullptr);
                    else
                        mStrs = mChars = nullptr;
                }

                const std::string get() const
                {
                    if (mLength == 0)
                        return "(null)";
                    if (mJstring == nullptr)
                        return "(error)";
                    return mStrs;
                }

                const char *c_str() const
                {
                    if (mLength == 0)
                        return "(null)";
                    if (mJstring == nullptr)
                        return "(error)";
                    return mChars;
                }

                const int32_t length() const { return mLength; }

                ~CSharpString()
                {
                    mEnv->ReleaseStringUTFChars(mJstring, mChars);
                    mEnv->DeleteLocalRef(mJstring);
                }
            };

        } // namespace Logic
    }     // namespace Loaded
} // namespace Hook
