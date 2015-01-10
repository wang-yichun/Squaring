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

#include "CCUpgradeVG.h"

USING_NS_CC;

namespace soomla {
    CCUpgradeVG *CCUpgradeVG::create(CCString *goodItemId, CCString *prevItemId, CCString *nextItemId, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCUpgradeVG *ret = new CCUpgradeVG();
        ret->autorelease();
        ret->init(goodItemId, prevItemId, nextItemId, name, description, itemId, purchaseType);
        return ret;
    }

    CCUpgradeVG *CCUpgradeVG::createWithDictionary(CCDictionary *dict) {
        CCUpgradeVG *ret = new CCUpgradeVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCUpgradeVG::init(CCString *goodItemId, CCString *prevItemId, CCString *nextItemId, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        bool res = CCVirtualGood::init(name, description, itemId, purchaseType);
        if (res) {
            setGoodItemId(goodItemId);
            setPrevItemId(prevItemId);
            setNextItemId(nextItemId);
            return true;
        } else {
            return false;
        }
    }

    bool CCUpgradeVG::initWithDictionary(CCDictionary *dict) {
        bool res = CCVirtualGood::initWithDictionary(dict);
        if (res) {
            fillGoodItemIdFromDict(dict);
            fillPrevItemIdFromDict(dict);
            fillNextItemIdFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    CCDictionary *CCUpgradeVG::toDictionary() {
        CCDictionary *dict = CCVirtualGood::toDictionary();

        putGoodItemIdToDict(dict);
        if (mPrevItemId != NULL) {
            putPrevItemIdToDict(dict);
        } else {
            dict->setObject(CCString::create(""), JSON_VGU_PREV_ITEMID);
        }
        if (mNextItemId != NULL) {
            putNextItemIdToDict(dict);
        } else {
            dict->setObject(CCString::create(""), JSON_VGU_NEXT_ITEMID);
        }

        return dict;
    }

    CCUpgradeVG::~CCUpgradeVG() {
        CC_SAFE_RELEASE(mGoodItemId);
        CC_SAFE_RELEASE(mPrevItemId);
        CC_SAFE_RELEASE(mNextItemId);
    }
}
