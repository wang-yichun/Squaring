//
//  VirtualCurrencyX.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#include "CCVirtualCurrency.h"

namespace soomla {
    
    CCVirtualCurrency* CCVirtualCurrency::create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId) {
        CCVirtualCurrency* pRet = new CCVirtualCurrency();
        if (pRet) {
            pRet->autorelease();
            pRet->init(name, description, itemId);
        }
        return pRet;
    }

    CCVirtualCurrency* CCVirtualCurrency::createWithDictionary(cocos2d::CCDictionary* dict) {
        CCVirtualCurrency* pRet = new CCVirtualCurrency();
        if (pRet) {
            pRet->autorelease();
            pRet->initWithDictionary(dict);
        }
        return pRet;
    }
}