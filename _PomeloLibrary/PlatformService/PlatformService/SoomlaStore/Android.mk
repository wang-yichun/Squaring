LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SoomlaStore_static

LOCAL_MODULE_FILENAME := libSoomlaStoreStatic

LOCAL_SRC_FILES := StoreBridge/JniHelpers.cpp \
                   StoreBridge/cocos2dx_StoreController.cpp \
                   StoreBridge/cocos2dx_StoreInventory.cpp \
                   StoreBridge/cocos2dx_EventHandlers.cpp \
                   StoreBridge/cocos2dx_StoreInfo.cpp \
                   StoreBridge/com_soomla_cocos2dx_store_EventHandlerBridge.cpp
                   

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/StoreBridge

LOCAL_C_INCLUDES := $(LOCAL_PATH)/StoreBridge

LOCAL_CFLAGS := -fexceptions

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
            
include $(BUILD_STATIC_LIBRARY)