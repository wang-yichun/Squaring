LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS) 
#LOCAL_MODULE    := cocos2dx-talkingdata
#LOCAL_SRC_FILES := libcocos2dx-talkingdata.a 
#include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := talkingdata

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AccountScene.cpp \
                   ../../Classes/MissionScene.cpp \
                   ../../Classes/ItemScene.cpp \
                   ../../Classes/VirtualCurrencyScene.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes  $(LOCAL_PATH)/../../../include $(LOCAL_PATH)/../../../platform/android

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static \
                                cocos2dx-talkingdata

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos2dx)
$(call import-module, proj.android/jni)
