APPNAME="HelloAnalytics"
APP_ANDROID_NAME="org.cocos2dx.helloanalytics"

if [ -z "${SDK_ROOT+aaa}" ]; then
# ... if SDK_ROOT is not set, use "$HOME/bin/android-sdk"
    SDK_ROOT="/Users/meyougames/Documents/AndroidDev/adt-bundle-mac-x86_64-20130729/sdk"
fi

if [ -z "${NDK_ROOT+aaa}" ]; then
# ... if NDK_ROOT is not set, use "$HOME/bin/android-ndk"
    NDK_ROOT="/Users/meyougames/Documents/AndroidDev/android-ndk-r8e"
fi

if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
# ... if COCOS2DX_ROOT is not set
# ... find current working directory
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
    COCOS2DX_ROOT="/Users/meyougames/Desktop/cocos2d-x-2.2.0"
    APP_ROOT="/Users/meyougames/Desktop/cocos2d-x-2.2.0/plugin/samples/HelloAnalytics"
    APP_ANDROID_ROOT="/Users/meyougames/Desktop/cocos2d-x-2.2.0/plugin/samples/HelloAnalytics/proj.android"
else
    APP_ROOT="/Users/meyougames/Desktop/cocos2d-x-2.2.0/plugin/samples/HelloAnalytics"
    APP_ANDROID_ROOT="/Users/meyougames/Desktop/cocos2d-x-2.2.0/plugin/samples/HelloAnalytics/proj.android"
fi

echo "NDK_ROOT = $NDK_ROOT"
echo "SDK_ROOT = $SDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "APP_ANDROID_NAME = $APP_ANDROID_NAME"

echo
echo "Killing and restarting ${APP_ANDROID_NAME}"
echo

set -x

/Users/meyougames/Documents/AndroidDev/adt-bundle-mac-x86_64-20130729/sdk/platform-tools/adb shell am force-stop "${APP_ANDROID_NAME}"

NDK_MODULE_PATH="${COCOS2DX_ROOT}":"${COCOS2DX_ROOT}"/cocos2dx/platform/third_party/android/prebuilt \
    "${NDK_ROOT}"/ndk-gdb \
    --adb="${SDK_ROOT}"/platform-tools/adb \
    --verbose \
    --start \
    --force
