//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCPurchaseWithVirtualItem.h"

namespace soomla {
    CCPurchaseWithVirtualItem *CCPurchaseWithVirtualItem::create(cocos2d::CCString *itemId, cocos2d::CCInteger *amount) {
        CCPurchaseWithVirtualItem *ret = new CCPurchaseWithVirtualItem();
        ret->autorelease();
        ret->init(itemId, amount);
        return ret;
    }

    bool CCPurchaseWithVirtualItem::init(cocos2d::CCString *itemId, cocos2d::CCInteger *amount) {
        setItemId(itemId);
        setAmount(amount);

        return true;
    }

    CCPurchaseWithVirtualItem::~CCPurchaseWithVirtualItem() {
        CC_SAFE_RELEASE(mItemId);
        CC_SAFE_RELEASE(mAmount);
    }
}
