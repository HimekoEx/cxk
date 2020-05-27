#include <include/openssl/sha.h>
#include "verify.h"
using namespace MiHoYoSDK;
using namespace MiHoYoSDK::StaticData;

const char Verify::HexCode[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

uint Verify::LocalVFC = 0;
uint Verify::RemoteVFC = 0;

// 使用JavaAPI进行签名验证
bool Verify::JniVerifySignature(JNIEnv *env)
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

#ifdef SignLog
    LOGE("ApiSign: %s", hex_sha);
#endif
    if (strcmp("86935830530C68151A2FB2A18B4A8EB149B8619A", hex_sha) != 0)
        return RT("AS Error") && CCC("ApiSign Error!");

    env->DeleteLocalRef(sha1_byte);
    delete[] hex_sha;
    return false;
}

// 外部验证CERT.RSA
bool Verify::VerifyCertRsaExt(const char *data, const uint size)
{
    int *keys = StaticData::CERT_RSA_EXT_KEY;
    uchar hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    char hex[65] = "";

    DecryptAscii(keys, 0x16A8);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, 38u);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        snprintf(hex + (i * 2), 3, GET_SAFE_CHAR(StaticData::STR_md5Format), hash[i]);
    hex[64] = '\0';
#ifdef SignLog
    LOGE("CERT.RSA(%d)Ext: %s", 38u, hex);
#endif

    DecryptAscii(keys, 0x2CF3);
    return CheakAscii(keys, hex, 0x4455);
}

// 内部验证CERT.RSA
bool Verify::VerifyCertRsaIns(const char *data, const uint size)
{

    int *keys = StaticData::CERT_RSA_INS_KEY;
    uchar hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    char hex[65] = "";

    DecryptAscii(keys, 0x3009);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, 38u);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        snprintf(hex + (i * 2), 3, GET_SAFE_CHAR(StaticData::STR_md5Format), hash[i]);
    hex[64] = '\0';
#ifdef SignLog
    LOGE("CERT.RSA(%d)Ins: %s", 38u, hex);
#endif

    DecryptAscii(keys, 0xB0E8);
    return CheakAscii(keys, hex, 0x212B);
}

// 文件验证
bool Verify::VerifyFile(const std::string &chaos, const std::string &cybl, const std::string &apk)
{
    std::string package = FileLine(GET_SAFE_DATA(PATH_Pack));

    std::string chaos_path = package + GET_SAFE_DATA(PATH_LIBchaos);
    std::string cybl_path = package + GET_SAFE_DATA(PATH_LIBcybl);
    std::string apk_path = package + GET_SAFE_DATA(PATH_baseAPK);

    Bytes chaosMD5 = MD5(FileRead(chaos_path), true);
#ifdef SignLog
    LOGE("chaos md5 : %s", chaosMD5.c_str());
#endif
#ifdef RELEASE
    if (chaosMD5 != chaos)
        return RT("V1 Error") && CCC("chaos MD5 Error!");
#endif

    Bytes cyblMD5 = MD5(FileRead(cybl_path), true);
#ifdef SignLog
    LOGE("cybl md5  : %s", cyblMD5.c_str());
#endif
#ifdef RELEASE
    if (cyblMD5 != cybl)
        return RT("V2 Error") && CCC("cybl MD5 Error!");
#endif

    Bytes apkMD5 = MD5(FileRead(apk_path), true);
#ifdef SignLog
    LOGE("apk  md5  : %s", apkMD5.c_str());
#endif
#ifdef RELEASE
    if (apkMD5 != apk)
        return RT("V3 Error") && CCC("apk MD5 Error!");
#endif

    return false;
}

// 获取Chaos的MD5
MiHoYoSDK::Bytes Verify::GetChaosMD5()
{
    std::string package = FileLine(GET_SAFE_DATA(PATH_Pack));
    std::string chaos_path = package + GET_SAFE_DATA(PATH_LIBchaos);
    return MD5(FileRead(chaos_path), true);
}

// 获取CyBL的MD5
MiHoYoSDK::Bytes Verify::GetCyBLMD5()
{
    std::string package = FileLine(GET_SAFE_DATA(PATH_Pack));
    std::string cybl_path = package + GET_SAFE_DATA(PATH_LIBcybl);
    return MD5(FileRead(cybl_path), true);
}

// 获取APK的MD5
MiHoYoSDK::Bytes Verify::GetAPKMD5()
{
    std::string package = FileLine(GET_SAFE_DATA(PATH_Pack));
    std::string apk_path = package + GET_SAFE_DATA(PATH_baseAPK);
    return MD5(FileRead(apk_path), true);
}

// 通过解析json验证文件
bool Verify::VerifyFileByJson(const MiHoYoSDK::Bytes &rawData)
{
    Json::Reader reader;
    Json::Value root;

    // 解析json
    if (!reader.parse(rawData.get(), root))
        return RT("VJ Error: 0x01") && CCC("Parse Error");

    return VerifyFile(root[GET_SAFE_DATA(STR_chaos)].asString(),
                      root[GET_SAFE_DATA(STR_cybl)].asString(),
                      root[GET_SAFE_DATA(STR_apk)].asString());
}

// 验证文件验证次数是否真实
void Verify::VerifyVFC()
{
    // Json::Reader reader;
    // Json::Value sendRoot, readRoot;
    // sendRoot["local"] = LocalVFC;
    // sendRoot["remote"] = RemoteVFC;

    int off = LocalVFC - RemoteVFC;
    // LOGE("LocalVFC: %u, RemoteVFC: %u", LocalVFC, RemoteVFC);

    if (off > 3 || off < -3)
        RT("VVFC Error: 0x01") && CCC("VVFC Error");

    // Bytes raw = SendJSON("verifyVFC", sendRoot);

    // // 解析json
    // if (!reader.parse(raw.get(), readRoot))
    //     RT("VVFC Error: 0x02") && CCC("Parse Error");

    // off = readRoot["vfc"].asInt();
    // off = LocalVFC - off;
    // if (off > 5 || off < -5)
    //     RT("VVFC Error: 0x01") && CCC("VVFC Error");
}
