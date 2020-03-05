#include <pthread.h>

#include <include/openssl/sha.h>

#include "module.h"

//通过API验证签名
void verifySignature(JNIEnv *env)
{
    const char hexcode[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    jclass context_class = env->FindClass("android/content/Context");

    jclass xpp_class = env->FindClass("com/bly/chaosapp/application/BLYApplication");
    jmethodID get_app = env->GetStaticMethodID(xpp_class, "getApp", "()Lcom/bly/chaosapp/application/BLYApplication;");
    jobject context_object = env->CallStaticObjectMethod(xpp_class, get_app);
    env->DeleteLocalRef(xpp_class);

    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject package_manager = env->CallObjectMethod(context_object, methodId);
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name = (jstring)env->CallObjectMethod(context_object, methodId);
    env->DeleteLocalRef(context_class);

    //获取PackageInfo对象
    jclass pack_manager_class = env->GetObjectClass(package_manager);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info = env->CallObjectMethod(package_manager, methodId, package_name, 0x40);
    env->DeleteLocalRef(package_manager);

    //获取签名信息
    jclass package_info_class = env->GetObjectClass(package_info);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures", "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray)env->GetObjectField(package_info, fieldId);

    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info);

    //签名信息转换成sha1值
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
    env->DeleteLocalRef(signature_class);
    jbyteArray signature_byte = (jbyteArray)env->CallObjectMethod(signature_object, methodId);
    jclass byte_array_input_class = env->FindClass("java/io/ByteArrayInputStream");
    methodId = env->GetMethodID(byte_array_input_class, "<init>", "([B)V");
    jobject byte_array_input = env->NewObject(byte_array_input_class, methodId, signature_byte);
    jclass certificate_factory_class = env->FindClass("java/security/cert/CertificateFactory");
    methodId = env->GetStaticMethodID(certificate_factory_class, "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring x_509_jstring = env->NewStringUTF("X.509");
    jobject cert_factory = env->CallStaticObjectMethod(certificate_factory_class, methodId, x_509_jstring);
    methodId = env->GetMethodID(certificate_factory_class, "generateCertificate", ("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
    jobject x509_cert = env->CallObjectMethod(cert_factory, methodId, byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);
    jclass x509_cert_class = env->GetObjectClass(x509_cert);
    methodId = env->GetMethodID(x509_cert_class, "getEncoded", "()[B");
    jbyteArray cert_byte = (jbyteArray)env->CallObjectMethod(x509_cert, methodId);
    env->DeleteLocalRef(x509_cert_class);
    jclass message_digest_class = env->FindClass("java/security/MessageDigest");
    methodId = env->GetStaticMethodID(message_digest_class, "getInstance", "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring sha1_jstring = env->NewStringUTF("SHA1");
    jobject sha1_digest = env->CallStaticObjectMethod(message_digest_class, methodId, sha1_jstring);
    methodId = env->GetMethodID(message_digest_class, "digest", "([B)[B");
    jbyteArray sha1_byte = (jbyteArray)env->CallObjectMethod(sha1_digest, methodId, cert_byte);
    env->DeleteLocalRef(message_digest_class);

    //转换成char
    jsize array_size = env->GetArrayLength(sha1_byte);
    jbyte *sha1 = env->GetByteArrayElements(sha1_byte, NULL);
    char *hex_sha = new char[array_size * 2 + 1];
    for (int i = 0; i < array_size; ++i)
    {
        hex_sha[2 * i] = hexcode[((unsigned char)sha1[i]) / 16];
        hex_sha[2 * i + 1] = hexcode[((unsigned char)sha1[i]) % 16];
    }
    hex_sha[array_size * 2] = '\0';

    if (strcmp("86935830530C68151A2FB2A18B4A8EB149B8619A", hex_sha) != 0)
    // if (strcmp("E72CDC4F3C513B87EDDE6A8E66E15EF1588486BA", hex_sha) != 0)
    {
        LOGD("Signature: %s", hex_sha);
        env->ExceptionDescribe();
        env->ExceptionClear();
        jclass newExcCls = env->FindClass("java/lang/IllegalArgumentException");
        // set VirtualCore to null to cause a crash.
        jclass virtual_core_class = env->FindClass("com/bly/chaos/core/ChaosCore");
        jfieldID gCore = env->GetStaticFieldID(virtual_core_class, "m", "Lcom/bly/chaos/core/ChaosCore;");
        env->SetStaticObjectField(virtual_core_class, gCore, NULL);
        env->DeleteLocalRef(virtual_core_class);
        env->ThrowNew(newExcCls, "");
        env->DeleteLocalRef(newExcCls);
    }
    return;
}

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
    MiHoYoSDK::LinkServer(&Sync::InitConfig);
    ReplaceDlopen();
    pthread_create(&ntid, NULL, threadFuckingGame, NULL);
}

//SHA256 验证签名
bool SHA_Check(const char *data, int keys[])
{
    uchar hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    char hex[65] = "";

    MiHoYoSDK::DecryptAscii(keys, 0xD378);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, strlen(data));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        snprintf(hex + (i * 2), 3, "%02x", hash[i]);
    hex[64] = '\0';

    MiHoYoSDK::DecryptAscii(keys, 0xCF8A);
    MiHoYoSDK::CheakAscii(keys, hex, 0x3F5B);

    return true;
}

//验证回调函数
bool VerifyBinRsa(const char *buffer, const uint size)
{
    return SHA_Check(buffer, MiHoYoSDK::StaticData::binRsaKey);
}

//jni入口
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;
    MiHoYoSDK::Jvm = vm;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    verifySignature(env); //旧版签名校验
    jclass xpp_class = env->FindClass("com/bly/chaosapp/application/BLYApplication");
    jmethodID get_app = env->GetStaticMethodID(xpp_class, "getApp", "()Lcom/bly/chaosapp/application/BLYApplication;");
    jobject application = env->CallStaticObjectMethod(xpp_class, get_app);

    jclass context = env->GetObjectClass(application);
    jmethodID methodID_func = env->GetMethodID(context, "getPackageCodePath", "()Ljava/lang/String;");
    jstring path = static_cast<jstring>(env->CallObjectMethod(application, methodID_func));
    const char *ch = env->GetStringUTFChars(path, 0);

    MiHoYoSDK::UncompressApk(ch, "META-INF/BIN.RSA", VerifyBinRsa);

    env->ReleaseStringUTFChars(path, ch);
    return JNI_VERSION_1_6;
}