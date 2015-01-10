LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_sqlite_static

LOCAL_MODULE_FILENAME := libsqlite

LOCAL_SRC_FILES := KompexSQLiteBlob.cpp \
          KompexSQLiteDatabase.cpp \
          KompexSQLiteStatement.cpp \
          sqlite3.c \
          JSBinding/kompex_binding.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/ \
						   $(LOCAL_PATH)/JSBinding

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
					$(LOCAL_PATH)/JSBinding

LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += scriptingcore-spidermonkey

LOCAL_CFLAGS := -fexceptions

include $(BUILD_STATIC_LIBRARY)

$(call import-module,scripting/javascript/spidermonkey-android)
$(call import-module,scripting/javascript/bindings)

