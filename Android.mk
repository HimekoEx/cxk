##############################初始化##############################

LOCAL_PATH := $(call my-dir)

##############################静态库##############################

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := hookzz
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libhookzz.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := dobby
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libdobby.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := substrate
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libsubstrate.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := jsoncpp
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libjsoncpp.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := openssl-crypto
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := openssl-ssl
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := zip
LOCAL_SRC_FILES := $(LOCAL_PATH)/libs/libzip.a
include $(PREBUILT_STATIC_LIBRARY)

##############################主项目##############################

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := libCyBL

LOCAL_SRC_FILES :=  $(LOCAL_PATH)/src/hack.cpp \
                    $(LOCAL_PATH)/src/verify/verify.cpp \
                    $(LOCAL_PATH)/src/sync/sync.cpp \
                    $(LOCAL_PATH)/src/hook/dlopen/dlopen.cpp \
                    $(LOCAL_PATH)/src/hook/loaded/il2cpp.cpp \
                    $(LOCAL_PATH)/src/hook/loaded/tersafe2.cpp \
                    $(LOCAL_PATH)/src/hook/logic/ClassLoad.cpp \
                    $(LOCAL_PATH)/src/hook/logic/Functions.cpp \
                    $(LOCAL_PATH)/src/hook/patch/il2cpp.cpp \
                    $(LOCAL_PATH)/src/hook/utils/EnumParse.cpp \
                    $(LOCAL_PATH)/src/sdk/crypto/AESCrypto.cpp \
                    $(LOCAL_PATH)/src/sdk/crypto/Hash.cpp \
                    $(LOCAL_PATH)/src/sdk/crypto/RSACrypto.cpp \
                    $(LOCAL_PATH)/src/sdk/net/network.cpp \
                    $(LOCAL_PATH)/src/sdk/utils/AntiDebug.cpp \
                    $(LOCAL_PATH)/src/sdk/utils/str.cpp \
                    $(LOCAL_PATH)/src/sdk/utils/file.cpp \
                    $(LOCAL_PATH)/src/sdk/utils/tools.cpp \
                    $(LOCAL_PATH)/src/sdk/static/config/config.cpp \
                    $(LOCAL_PATH)/src/sdk/static/config/keys.cpp \
                    $(LOCAL_PATH)/src/sdk/static/config/path.cpp \
                    $(LOCAL_PATH)/src/sdk/static/hook/dlopen/dlopen.cpp \
                    $(LOCAL_PATH)/src/sdk/static/hook/loaded/il2cpp.cpp \
                    $(LOCAL_PATH)/src/sdk/static/hook/logic/Functions.cpp \
                    $(LOCAL_PATH)/src/sdk/static/sdk/crypto/Hash.cpp \
                    $(LOCAL_PATH)/src/sdk/static/sdk/net/network.cpp \
                    $(LOCAL_PATH)/src/sdk/static/sdk/utils/AntiDebug.cpp \
                    $(LOCAL_PATH)/src/sdk/static/sdk/utils/tools.cpp \
                    $(LOCAL_PATH)/src/sdk/static/sync/sync.cpp \
                    $(LOCAL_PATH)/src/sdk/static/verify/verify.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_CFLAGS := -std=c11 -mllvm -sobf -mllvm -fla -mllvm -split -mllvm -split_num=3
LOCAL_CFLAGS := -std=c11 -Wall -O2 -U_FORTIFY_SOURCE -fstack-protector-all
LOCAL_CPPFLAGS := -std=c++17 -fexceptions -frtti
LOCAL_LDLIBS := -lz -llog
LOCAL_STATIC_LIBRARIES += hookzz dobby substrate jsoncpp openssl-crypto openssl-ssl zip
include $(BUILD_SHARED_LIBRARY)

##############################End##############################
