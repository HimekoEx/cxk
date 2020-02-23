LOCAL_PATH := $(call my-dir)

###########################################################

include $(CLEAR_VARS)
LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true
LOCAL_MODULE    := CyBL

LOCAL_SRC_FILES := hack.cpp \
                   module_patch.cpp \
                   module_dlopen.cpp \
                   module_fuckMTP.cpp \
                   module_hook.cpp \
                   module_sync.cpp \
                   module_GameClass.cpp \
                   MiHoYoSDK.cpp \
                   MiHoYoSDK_StaticData.cpp 
             
LOCAL_C_INCLUDES := include/hookzz \
                    include/json \
                    include/curl \
                    include/openssl \
                    include/zip

LOCAL_LDFLAGS := include/libhookzz.a \
                 include/libjsoncpp.a \
                 include/libcurl.a \
                 include/libcrypto.a \
                 include/libssl.a \
                 include/libzip.a

LOCAL_LDLIBS := -llog -lz
# LOCAL_CFLAGS := -mllvm -sobf -mllvm -fla -mllvm -split -mllvm -split_num=3
include $(BUILD_SHARED_LIBRARY)

###########################################################
