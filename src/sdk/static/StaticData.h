#pragma once
#include <src/sdk/Base.h>

//SDK
#include "config/config.h"
#include "config/keys.h"
#include "config/path.h"
#include "sdk/crypto/Hash.h"
#include "sdk/net/network.h"
#include "sdk/utils/AntiDebug.h"
#include "sdk/utils/tools.h"

//第三方
#include "hook/dlopen/dlopen.h"
#include "hook/loaded/il2cpp.h"
#include "hook/logic/Functions.h"
#include "sync/sync.h"
#include "verify/verify.h"

#define GET_SAFE_CORT(name) name, sizeof(name)
#define GET_SAFE_CHAR(name) (MiHoYoSDK::SafeChars(name, sizeof(name)).get().c_str())
#define GET_SAFE_DATA(name) (MiHoYoSDK::SafeChars(name, sizeof(name)).get())
