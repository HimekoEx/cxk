#pragma once
#include "src/mihoyo_sdk/MiHoYoSDK.h"

// 全局的Hex表
extern const char HexCode[16];

// 使用JavaAPI进行签名验证
bool JniVerifySignature(JNIEnv *env);