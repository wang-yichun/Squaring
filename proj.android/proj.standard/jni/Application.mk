APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCOCOS2D_JAVASCRIPT=1 -DTARGET_ANDROID=1 -DTARGET_NORMAL=1
APP_CPPFLAGS += -DCOCOS2D_DEBUG=1 -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 
APP_PLATFORM := android-8