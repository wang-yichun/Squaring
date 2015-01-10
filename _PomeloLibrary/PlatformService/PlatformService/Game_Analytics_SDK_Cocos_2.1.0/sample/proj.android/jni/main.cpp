#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include "TDGAJniHelper.h"
#include "TDGALog.h"
#include <jni.h>
#include <android/log.h>

#include "AccountScene.h"
#include "TDCCTalkingDataGA.h"

using namespace cocos2d;

extern "C"
{

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
	LOGD("JNI_OnLoad");
	JniHelper::setJavaVM(vm);
	TDGAJniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
	LOGD("JNI_OnUnload");
	TDGAJniHelper::globalDeInit();
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}
