#include <pthread.h>

#include "sync/sync.h"
#include "verify/verify.h"

#define MAIN __attribute__((constructor))

// 初始化patch
bool initPatch()
{
    ulong il2cpp = MiHoYoSDK::GetModuleAddr(GET_SAFE_CHAR(MiHoYoSDK::StaticData::STR_il2cppLib));
    if (il2cpp == 0)
        return true;

    Sync::InitAddress(il2cpp);
    Hook::Loaded::Patch::FirstPatchIl2cpp();

    return false;
}

// 循环patch
uint loopPatch()
{
    Sync::SyncJsonConfig();
    Hook::Loaded::Patch::LoopPatchIl2cpp();
    return 3u;
}

// 子线程
void *threadFuckingGame(void *)
{
    sleep(5);
    while (initPatch())
        usleep(300000u);

    while (true)
        sleep(loopPatch());

    return NULL;
}

// 入口
MAIN void FuckMiHoYo()
{
    pthread_t ntid;
    Sync::InitAllVariable();
    MiHoYoSDK::RunTimeInit();
    MiHoYoSDK::LinkServer(&Sync::InitConfig);
    Hook::Dlopen::ReplaceDlopen();
    pthread_create(&ntid, NULL, threadFuckingGame, NULL);
}

// Jni入口
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;
    MiHoYoSDK::Jvm = vm;
    MiHoYoSDK::AntiDebug();
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    //旧版签名校验
    if (Verify::JniVerifySignature(env))
        RT("AS Error") && CCC("ApiSign Error");
#ifdef RELEASE
    RT("AS done.");
#endif

    //验证RSA文件
    jclass xpp_class = env->FindClass("com/bly/chaosapp/application/BLYApplication");
    jmethodID get_app = env->GetStaticMethodID(xpp_class, "getApp", "()Lcom/bly/chaosapp/application/BLYApplication;");
    jobject application = env->CallStaticObjectMethod(xpp_class, get_app);
    env->DeleteLocalRef(xpp_class);

    jclass context = env->GetObjectClass(application);
    jmethodID methodID_func = env->GetMethodID(context, "getPackageCodePath", "()Ljava/lang/String;");
    jstring path = static_cast<jstring>(env->CallObjectMethod(application, methodID_func));
    env->DeleteLocalRef(application);
    env->DeleteLocalRef(context);
    const char *ch = env->GetStringUTFChars(path, 0);

    MiHoYoSDK::UncompressAPK(ch, GET_SAFE_DATA(MiHoYoSDK::StaticData::PATH_RSA), Verify::VerifyCertRsaExt);
#ifdef RELEASE
    RT("VCRE done.");
#endif

    env->ReleaseStringUTFChars(path, ch);
    env->DeleteLocalRef(path);
    return JNI_VERSION_1_6;
}
