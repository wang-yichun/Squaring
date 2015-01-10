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

#include "CCMarketItem.h"

USING_NS_CC;

namespace soomla {

    CCMarketItem *CCMarketItem::create(CCString *productId, CCInteger *consumable, CCDouble *price) {
        CCMarketItem *ret = new CCMarketItem();
        ret->autorelease();
        ret->init(productId, consumable, price);
        return ret;
    }

    CCMarketItem *CCMarketItem::createWithDictionary(CCDictionary *dict) {
        CCMarketItem *ret = new CCMarketItem();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCMarketItem::init(CCString *productId, CCInteger *consumable, CCDouble *price) {
        setProductId(productId);
        setConsumable(consumable);
        setPrice(price);

        return true;
    }

    bool CCMarketItem::initWithDictionary(CCDictionary *dict) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        char const* key = JSON_MARKETITEM_ANDROID_ID;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        char const* key = JSON_MARKETITEM_IOS_ID;
#endif
        cocos2d::CCObject* obj = dict->objectForKey(key);
        CCAssert(obj == NULL || dynamic_cast<CCString *>(obj), "invalid object type in dictionary");
        setProductId((CCString *)obj);

        if (mProductId == NULL) {
            fillProductIdFromDict(dict);
        }

        fillConsumableFromDict(dict);
        fillPriceFromDict(dict);

        return true;
    }

    CCMarketItem::~CCMarketItem() {
        CC_SAFE_RELEASE(mProductId);
        CC_SAFE_RELEASE(mConsumable);
        CC_SAFE_RELEASE(mPrice);
    }

    CCDictionary *CCMarketItem::toDictionary() {
        CCDictionary *dict = CCDictionary::create();

        putProductIdToDict(dict);
        putConsumableToDict(dict);
        putPriceToDict(dict);

        return dict;
    }
};

