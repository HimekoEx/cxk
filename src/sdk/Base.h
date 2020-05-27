#pragma once

//System
#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <android/log.h>

//第三方库
#include <src/fix.h>
#include <openssl/ossl_typ.h>
#include <json/json.h>

//类型定义
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned char uchar;

//logcat
#ifndef RELEASE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "wdnmd", __VA_ARGS__)
#else
#define LOGE(...)
#endif

//Bool转char*
#define BoolToChar(value) (value ? "true" : "false")

//快速转std::string类型
#define ToString(data) std::to_string(data)
#define String(data) std::string(data)
