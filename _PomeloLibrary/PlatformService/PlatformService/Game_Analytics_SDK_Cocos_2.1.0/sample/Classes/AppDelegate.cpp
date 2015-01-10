/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "AppDelegate.h"
#include "cocos2d.h"
#include "AccountScene.h"
#include "TDCCTalkingDataGA.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

void AppDelegate::loadAnalyticsPlugin()
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
	CCLog("enter applicationDidFinishLaunching...");
    TDCCTalkingDataGA::onStart("2B002F9CD724EB09730AF32CB4D909C3", "");
//    TDCCTalkingDataGA::setVerboseLogDisabled();
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    pDirector->getOpenGLView()->setDesignResolutionSize(320, 480, kResolutionExactFit);

    // create a scene. it's an autorelease object
    CCScene *pScene = AccountLayer::scene();
    CCLog("applicationDidFinishLaunching DeviceId:%s", TDCCTalkingDataGA::getDeviceId());
    // run
    pDirector->runWithScene(pScene);
    CCLog("exit applicationDidFinishLaunching...");
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCLog("applicationWillEnterForeground...");
    CCDirector::sharedDirector()->resume();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
