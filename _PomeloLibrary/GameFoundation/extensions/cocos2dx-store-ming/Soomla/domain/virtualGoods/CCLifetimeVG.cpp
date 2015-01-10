//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCLifetimeVG.h"


namespace soomla {
    USING_NS_CC;
    CCLifetimeVG *CCLifetimeVG::create(CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCLifetimeVG *ret = new CCLifetimeVG();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    CCLifetimeVG *CCLifetimeVG::createWithDictionary(CCDictionary *dict) {
        CCLifetimeVG *ret = new CCLifetimeVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
}
