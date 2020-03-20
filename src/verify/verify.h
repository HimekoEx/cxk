#pragma once
#include "src/sdk/MiHoYoSDK.h"

namespace Verify
{

//全局的Hex表
extern const char HexCode[16];
//本地文件验证次数
extern uint LocalVFC;
//远程文件验证次数
extern uint RemoteVFC;

// 使用JavaAPI进行签名验证
bool JniVerifySignature(JNIEnv *env);
// 外部验证CERT.RSA
bool VerifyCertRsaExt(const char *data, const uint size);
// 内部验证CERT.RSA
bool VerifyCertRsaIns(const char *data, const uint size);
// 文件验证
bool VerifyFile(const std::string &chaos, const std::string &cybl, const std::string &apk);

// 获取Chaos的MD5
MiHoYoSDK::Bytes GetChaosMD5();
// 获取CyBL的MD5
MiHoYoSDK::Bytes GetCyBLMD5();
// 获取APK的MD5
MiHoYoSDK::Bytes GetAPKMD5();
// 通过解析json验证文件
bool VerifyFileByJson(const MiHoYoSDK::Bytes &rawData);

// 验证文件验证次数是否真实
void VerifyVFC();

} // namespace Verify
