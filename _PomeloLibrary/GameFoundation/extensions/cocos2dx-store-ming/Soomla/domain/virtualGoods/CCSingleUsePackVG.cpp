//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCSingleUsePackVG.h"

USING_NS_CC;

namespace soomla {
    CCSingleUsePackVG *CCSingleUsePackVG::create(CCString *goodItemId, CCInteger *goodAmount, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCSingleUsePackVG *ret = new CCSingleUsePackVG();
        ret->autorelease();
        ret->init(goodItemId, goodAmount, name, description, itemId, purchaseType);
        return ret;
    }

    CCSingleUsePackVG *CCSingleUsePackVG::createWithDictionary(CCDictionary *dict) {
        CCSingleUsePackVG *ret = new CCSingleUsePackVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCSingleUsePackVG::init(CCString *goodItemId, CCInteger *goodAmount, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        bool res = CCVirtualGood::init(name, description, itemId, purchaseType);
        if (res) {
            setGoodItemId(goodItemId);
            setGoodAmount(goodAmount);
            return true;
        } else {
            return false;
        }
    }

    bool CCSingleUsePackVG::initWithDictionary(CCDictionary *dict) {
        bool res = CCVirtualGood::initWithDictionary(dict);
        if (res) {
            fillGoodItemIdFromDict(dict);
            fillGoodAmountFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    CCDictionary *CCSingleUsePackVG::toDictionary() {
        CCDictionary *dict = CCVirtualGood::toDictionary();

        putGoodItemIdToDict(dict);
        putGoodAmountToDict(dict);

        return dict;
    }

    CCSingleUsePackVG::~CCSingleUsePackVG() {
        CC_SAFE_RELEASE(mGoodItemId);
        CC_SAFE_RELEASE(mGoodAmount);
    }
}