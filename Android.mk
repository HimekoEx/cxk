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

LOCAL_SRC_FILES :=  $(LOCAL_PATH)/hack.cpp \
                    $(LOCAL_PATH)/module_patch.cpp \
                    $(LOCAL_PATH)/module_dlopen.cpp \
                    $(LOCAL_PATH)/module_fuckMTP.cpp \
                    $(LOCAL_PATH)/module_hook.cpp \
                    $(LOCAL_PATH)/module_sync.cpp \
                    $(LOCAL_PATH)/module_GameClass.cpp \
                    $(LOCAL_PATH)/MiHoYoSDK.cpp \
                    $(LOCAL_PATH)/MiHoYoSDK_StaticData.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

# LOCAL_CFLAGS := -mllvm -sobf -mllvm -fla -mllvm -split -mllvm -split_num=3
LOCAL_CFLAGS += -Wall -O2 -U_FORTIFY_SOURCE -fstack-protector-all
LOCAL_LDLIBS := -lz -llog
LOCAL_STATIC_LIBRARIES += hookzz jsoncpp openssl-crypto openssl-ssl zip
include $(BUILD_SHARED_LIBRARY)

##############################End##############################
