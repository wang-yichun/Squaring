//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCSingleUseVG.h"

namespace soomla {
    USING_NS_CC;
    CCSingleUseVG *CCSingleUseVG::create(CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCSingleUseVG *ret = new CCSingleUseVG();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    CCSingleUseVG *CCSingleUseVG::createWithDictionary(CCDictionary *dict) {
        CCSingleUseVG *ret = new CCSingleUseVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
}
