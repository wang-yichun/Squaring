//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCVirtualGood.h"

USING_NS_CC;

namespace soomla {
    CCVirtualGood *CCVirtualGood::create(CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCVirtualGood *ret = new CCVirtualGood();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    CCVirtualGood *CCVirtualGood::createWithDictionary(CCDictionary *dict) {
        CCVirtualGood *ret = new CCVirtualGood();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
}