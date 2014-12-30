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
#include "VirtualCurrencyScene.h"
#include "cocos2d.h"
#include "AppDelegate.h"
#include "TDCCVirtualCurrency.h"
#include "TDCCTalkingDataGA.h"

using namespace cocos2d;

enum {
	ONREQUEST = 0,
	ONSUCCESS,
    ONREWARD,
	ONEVENT
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
} EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"Request", ONREQUEST},
    {"Success", ONSUCCESS},
    {"Reward", ONREWARD},
    {"OnEvent", ONEVENT}
};

VirtualCurrencyLayer::VirtualCurrencyLayer() {
}

VirtualCurrencyLayer::~VirtualCurrencyLayer() {
}

CCScene* VirtualCurrencyLayer::scene() {
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    VirtualCurrencyLayer *layer = VirtualCurrencyLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool VirtualCurrencyLayer::init() {
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() ) {
        return false;
    }

    this->setKeypadEnabled(true);

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* title = CCLabelTTF::create("Virtual Currency", "Arial", 24);
	title->setPosition( ccp(size.width / 2, size.height - 20));
	this->addChild(title, 1);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "b1.png",
                                        "b2.png",
                                        this,
                                        menu_selector(VirtualCurrencyLayer::menuBackCallback) );
    pCloseItem->setPosition( ccp(pCloseItem->getContentSize().width / 2 , 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    

    float step = 35;
    float yPos = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
        CCLabelTTF* label = CCLabelTTF::create(s_EventMenuItem[i].id.c_str(), "Arial", 24);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(VirtualCurrencyLayer::eventMenuCallback));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
        yPos = size.height - step*i - 100;
        pMenuItem->setPosition( ccp(size.width / 2, yPos));
    }

    return true;
}


void VirtualCurrencyLayer::eventMenuCallback(CCObject* pSender) {
	CCMenuItemLabel* pMenuItem = (CCMenuItemLabel*)pSender;
    int i = pMenuItem->getTag();
    EventParamMap paramMap;
    pthread_t thread;
    switch (i) {
    case ONREQUEST:
    	TDCCVirtualCurrency::onChargeRequest("o_1", "iap", 10, "CN", 20, "T1");
        break;
            
    case ONSUCCESS:

    	pthread_create(&thread, NULL, runThread, NULL);

        break;
            
    case ONREWARD:
        TDCCVirtualCurrency::onReward(100, "reason");
        break;

    case ONEVENT:
    	paramMap.insert(EventParamPair("type", "popular"));
		paramMap.insert(EventParamPair("artist", "JJLin"));
        paramMap["aa"] = "bb";
		TDCCTalkingDataGA::onEvent("music", &paramMap);

    	break;

    default:
        break;
    }

}

void VirtualCurrencyLayer::menuBackCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->popScene();
}

void VirtualCurrencyLayer::keyBackClicked() {
	menuBackCallback(NULL);
}

void* VirtualCurrencyLayer::runThread(void* arg) {
    TDCCVirtualCurrency::onChargeSuccess("o_1");
#ifdef ANDROID
    TDGAJniHelper::detachEnv();
#endif
    return NULL;
}
