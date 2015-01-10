//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCPurchaseWithMarket.h"

namespace soomla {
    CCPurchaseWithMarket *CCPurchaseWithMarket::create(cocos2d::CCString *productId, cocos2d::CCDouble *price) {
        return createWithMarketItem(CCMarketItem::create(
                productId, cocos2d::CCInteger::create(CCMarketItem::CONSUMABLE), price));
    }

    CCPurchaseWithMarket *CCPurchaseWithMarket::createWithMarketItem(CCMarketItem *marketItem) {
        CCPurchaseWithMarket *ret = new CCPurchaseWithMarket();
        ret->autorelease();
        ret->initWithMarketItem(marketItem);
        return ret;
    }

    bool CCPurchaseWithMarket::initWithMarketItem(CCMarketItem *marketItem) {
        bool res = CCPurchaseType::init();
        if (res) {
            setMarketItem(marketItem);
            return true;
        } else {
            return false;
        }
    }

    CCPurchaseWithMarket::~CCPurchaseWithMarket() {
        CC_SAFE_RELEASE(mMarketItem);
    }
}
