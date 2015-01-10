/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

// Created by Fedor Shubin on 5/19/13.

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
