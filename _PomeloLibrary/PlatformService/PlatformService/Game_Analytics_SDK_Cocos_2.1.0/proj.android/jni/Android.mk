LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx-talkingdata

LOCAL_SRC_FILES := \
$(addprefix ../../platform/android/, \
    TDCCTalkingDataGA.cpp \
    TDGAJniHelper.cpp \
    TDCCItem.cpp \
    TDCCMission.cpp \
    TDCCVirtualCurrency.cpp \
    TDCCAccount.cpp \
) \

LOCAL_CFLAGS := 

LOCAL_EXPORT_CFLAGS := 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include $(LOCAL_PATH)/../../platform/android

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include 


LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)


