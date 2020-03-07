#include "verify.h"

const char HexCode[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// 使用JavaAPI进行签名验证
bool JniVerifySignature(JNIEnv *env)
{
    //获取context类型和对象
    jclass context_class = env->FindClass("android/content/Context");
    jclass xpp_class = env->FindClass("com/bly/chaosapp/application/BLYApplication");
    jmethodID get_app = env->GetStaticMethodID(xpp_class, "getApp", "()Lcom/bly/chaosapp/application/BLYApplication;");
    jobject context_object = env->CallStaticObjectMethod(xpp_class, get_app);
    env->DeleteLocalRef(xpp_class);

    //获取包管理和包名
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject package_manager = env->CallObjectMethod(context_object, methodId);
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name = (jstring)env->CallObjectMethod(context_object, methodId);
    env->DeleteLocalRef(context_class);
    env->DeleteLocalRef(context_object);

    //获取PackageInfo对象
    jclass pack_manager_class = env->GetObjectClass(package_manager);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject package_info = env->CallObjectMethod(package_manager, methodId, package_name, 0x40);
    env->DeleteLocalRef(package_manager);
    env->DeleteLocalRef(package_name);
    env->DeleteLocalRef(pack_manager_class);

    //获取签名信息对象
    jclass package_info_class = env->GetObjectClass(package_info);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signature_object_array = (jobjectArray)env->GetObjectField(package_info, fieldId);
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info);
    env->DeleteLocalRef(package_info_class);
    env->DeleteLocalRef(signature_object_array);

    //签名信息转换成sha1值
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
    jbyteArray signature_byte = (jbyteArray)env->CallObjectMethod(signature_object, methodId);
    env->DeleteLocalRef(signature_object);
    env->DeleteLocalRef(signature_class);

    jclass byte_array_input_class = env->FindClass("java/io/ByteArrayInputStream");
    methodId = env->GetMethodID(byte_array_input_class, "<init>", "([B)V");
    jobject byte_array_input = env->NewObject(byte_array_input_class, methodId, signature_byte);
    env->DeleteLocalRef(signature_byte);
    env->DeleteLocalRef(byte_array_input_class);

    jclass certificate_factory_class = env->FindClass("java/security/cert/CertificateFactory");
    methodId = env->GetStaticMethodID(certificate_factory_class, "getInstance", "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring x_509_jstring = env->NewStringUTF("X.509");
    jobject cert_factory = env->CallStaticObjectMethod(certificate_factory_class, methodId, x_509_jstring);
    methodId = env->GetMethodID(certificate_factory_class, "generateCertificate", ("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
    jobject x509_cert = env->CallObjectMethod(cert_factory, methodId, byte_array_input);
    env->DeleteLocalRef(byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);
    env->DeleteLocalRef(x_509_jstring);
    env->DeleteLocalRef(cert_factory);

    jclass x509_cert_class = env->GetObjectClass(x509_cert);
    methodId = env->GetMethodID(x509_cert_class, "getEncoded", "()[B");
    jbyteArray cert_byte = (jbyteArray)env->CallObjectMethod(x509_cert, methodId);
    env->DeleteLocalRef(x509_cert);
    env->DeleteLocalRef(x509_cert_class);

    jclass message_digest_class = env->FindClass("java/security/MessageDigest");
    methodId = env->GetStaticMethodID(message_digest_class, "getInstance", "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring sha1_jstring = env->NewStringUTF("SHA1");
    jobject sha1_digest = env->CallStaticObjectMethod(message_digest_class, methodId, sha1_jstring);
    methodId = env->GetMethodID(message_digest_class, "digest", "([B)[B");
    jbyteArray sha1_byte = (jbyteArray)env->CallObjectMethod(sha1_digest, methodId, cert_byte);
    env->DeleteLocalRef(cert_byte);
    env->DeleteLocalRef(message_digest_class);
    env->DeleteLocalRef(sha1_jstring);
    env->DeleteLocalRef(sha1_digest);

    //转换成char
    jsize array_size = env->GetArrayLength(sha1_byte);
    jbyte *sha1 = env->GetByteArrayElements(sha1_byte, NULL);
    char *hex_sha = new char[array_size * 2 + 1];
    for (int i = 0; i < array_size; ++i)
    {
        hex_sha[2 * i] = HexCode[((uchar)sha1[i]) / 16];
        hex_sha[2 * i + 1] = HexCode[((uchar)sha1[i]) % 16];
    }
    hex_sha[array_size * 2] = '\0';

    LOGE("ApiSign: %s", hex_sha);
    if (strcmp("86935830530C68151A2FB2A18B4A8EB149B8619A", hex_sha) != 0)
        return MiHoYoSDK::RunTimeLog("Sign Verify Fail") && MiHoYoSDK::CloseChaosCore1("ApiSign Fail") && MiHoYoSDK::CloseChaosCore2();

    env->DeleteLocalRef(sha1_byte);
    delete[] hex_sha;
    return false;
}