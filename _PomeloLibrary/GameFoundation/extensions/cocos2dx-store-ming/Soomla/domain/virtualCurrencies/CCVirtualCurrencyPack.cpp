//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCVirtualCurrencyPack.h"

USING_NS_CC;

namespace soomla {
    CCVirtualCurrencyPack *CCVirtualCurrencyPack::create(CCString *name, CCString *description, CCString *itemId, CCInteger *currencyAmount, CCString *currencyItemId, CCPurchaseType *purchaseType) {
        CCVirtualCurrencyPack *ret = new CCVirtualCurrencyPack();
        ret->autorelease();
        ret->init(name, description, itemId, currencyAmount, currencyItemId, purchaseType);
        return ret;
    }

    CCVirtualCurrencyPack *CCVirtualCurrencyPack::createWithDictionary(CCDictionary *dict) {
        CCVirtualCurrencyPack *ret = new CCVirtualCurrencyPack();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCVirtualCurrencyPack::init(CCString *name, CCString *description, CCString *itemId, CCInteger *currencyAmount, CCString *currencyItemId, CCPurchaseType *purchaseType) {
        bool res = CCPurchasableVirtualItem::init(name, description, itemId, purchaseType);
        if (res) {
            setCurrencyAmount(currencyAmount);
            setCurrencyItemId(currencyItemId);
            return true;
        } else {
            return false;
        }
    }

    bool CCVirtualCurrencyPack::initWithDictionary(CCDictionary *dict) {
        bool res = CCPurchasableVirtualItem::initWithDictionary(dict);
        if (res) {
            fillCurrencyAmountFromDict(dict);
            fillCurrencyItemIdFromDict(dict);

            return true;
        } else {
            return false;
        }
    }

    CCDictionary *CCVirtualCurrencyPack::toDictionary() {
        CCDictionary *dict = CCPurchasableVirtualItem::toDictionary();

        putCurrencyAmountToDict(dict);
        putCurrencyItemIdToDict(dict);

        return dict;
    }

    CCVirtualCurrencyPack::~CCVirtualCurrencyPack() {
        CC_SAFE_RELEASE(mCurrencyAmount);
        CC_SAFE_RELEASE(mCurrencyItemId);
    }
}    
