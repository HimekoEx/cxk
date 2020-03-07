#include <pthread.h>
#include <include/openssl/sha.h>

#include "sync/module.h"
#include "verify/verify.h"

//初始化patch
bool initPatch()
{
    ulong il2cpp = MiHoYoSDK::GetModuleBaseAdderss("libil2cpp.so");
    if (il2cpp == 0)
        return true;

    Sync::InitAddress(il2cpp);
    Sync::SyncJsonConfig();
    FirstFucking();

    return false;
}

//循环patch
uint loopPatch()
{
    Sync::SyncJsonConfig();
    FuckingLIB();
    return 5u;
}

//子线程
void *threadFuckingGame(void *arg)
{
    sleep(3);
    while (initPatch())
        sleep(1);

    while (true)
        sleep(loopPatch());

    return NULL;
}

//入口
__attribute__((constructor)) void FuckMiHoYo()
{
    pthread_t ntid;
    Sync::InitAllVariable();
    MiHoYoSDK::LinkServer(1, &Sync::InitConfig);
    ReplaceDlopen();
    pthread_create(&ntid, NULL, threadFuckingGame, NULL);
}

//SHA256 验证签名
bool SHA_Check(const char *data, const uint size, int keys[])
{
    uchar hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    char hex[65] = "";

    MiHoYoSDK::DecryptAscii(keys, 0x16A8);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, strlen(data));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        snprintf(hex + (i * 2), 3, "%02x", hash[i]);
    hex[64] = '\0';
    LOGE("SHA_Check1: %s", hex);

    MiHoYoSDK::DecryptAscii(keys, 0x2CF3);
    MiHoYoSDK::CheakAscii(keys, hex, 0x4455);

    return true;
}

//验证回调函数
bool VerifyBinRsa(const char *buffer, const uint size)
{
    return SHA_Check(buffer, size, MiHoYoSDK::StaticData::binRsaKey);
}

// Jni入口
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;
    MiHoYoSDK::Jvm = vm;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    //旧版签名校验
    if (JniVerifySignature(env))
        MiHoYoSDK::RunTimeLog("Sign Verify Fail") && MiHoYoSDK::CloseChaosCore1("ApiSign Fail") && MiHoYoSDK::CloseChaosCore2();

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

    MiHoYoSDK::UncompressApk(ch, GET_SAFE_DATA(MiHoYoSDK::StaticData::binRsaPath), VerifyBinRsa);

    env->ReleaseStringUTFChars(path, ch);
    return JNI_VERSION_1_6;
}