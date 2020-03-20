#pragma once

//SDK库
#include "Base.h"
#include "SafeChars.hpp"
#include "Bytes.hpp"
#include "crypto/AESCrypto.h"
#include "crypto/Hash.h"
#include "crypto/RSACrypto.h"
#include "net/network.h"
#include "utils/AntiDebug.h"
#include "utils/file.h"
#include "utils/str.h"
#include "utils/tools.h"

//静态数据
#include "static/StaticData.h"

#define RT(...) MiHoYoSDK::RunTimeLog(__VA_ARGS__)
#ifdef RELEASE
#define CCC(...) (MiHoYoSDK::CloseJVM() && MiHoYoSDK::CloseCore())
#else
#define CCC(...) (MiHoYoSDK::CloseJVM(__VA_ARGS__) && MiHoYoSDK::CloseCore())
#endif

// //内存读取
// template <class T1, class T2>
// inline T1 MiHoYoSDK::MemoryRead(T2 addr, uint off)
// {
//     if (!addr)
//         CloseJVM("Addr is nullprt!") && CloseCore();
//     return *(T1 *)((char *)addr + off);
// }
