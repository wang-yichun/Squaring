LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := EasyNDK_static

LOCAL_MODULE_FILENAME := libEasyNDKStatic

LOCAL_SRC_FILES := jansson/dump.c \
                   jansson/error.c \
                   jansson/hashtable.c \
                   jansson/load.c \
                   jansson/memory.c \
                   jansson/pack_unpack.c \
                   jansson/strbuffer.c \
                   jansson/strconv.c \
                   jansson/utf.c \
                   jansson/value.c \
                   NDKHelper/NDKCallbackNode.cpp \
                   NDKHelper/NDKHelper.cpp
                   

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/NDKHelper \
                        $(LOCAL_PATH)/jansson

LOCAL_C_INCLUDES := $(LOCAL_PATH)/NDKHelper \
                        $(LOCAL_PATH)/jansson

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
            
include $(BUILD_STATIC_LIBRARY)