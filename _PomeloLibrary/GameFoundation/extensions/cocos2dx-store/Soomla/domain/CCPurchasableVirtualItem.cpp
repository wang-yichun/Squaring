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

#include "CCPurchasableVirtualItem.h"

#include "../PurchaseTypes/CCPurchaseWithVirtualItem.h"
#include "../PurchaseTypes/CCPurchaseWithMarket.h"

namespace soomla {
    
    using namespace cocos2d;
    
    bool CCPurchasableVirtualItem::init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, CCPurchaseType * purchaseType) {
        bool bRet = CCVirtualItem::init(name, description, itemId);
        if (bRet) {
            setPurchaseType(purchaseType);
        }
        return bRet;
    }
    
    bool CCPurchasableVirtualItem::initWithDictionary(cocos2d::CCDictionary* dict) {
        bool bRet = CCVirtualItem::initWithDictionary(dict);
        if (bRet) {
            fillPurchaseTypeFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    CCPurchasableVirtualItem *CCPurchasableVirtualItem::create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, CCPurchaseType * purchaseType) {
        CCPurchasableVirtualItem * pRet = new CCPurchasableVirtualItem();
        if (pRet) {
            pRet->autorelease();
            pRet->init(name, description, itemId, purchaseType);
        }
        return pRet;
    }

    CCPurchasableVirtualItem *CCPurchasableVirtualItem::createWithDictionary(cocos2d::CCDictionary* dict) {
        CCPurchasableVirtualItem * pRet = new CCPurchasableVirtualItem();
        if (pRet) {
            pRet->autorelease();
            pRet->initWithDictionary(dict);
        }
        return pRet;
    }
    
    CCPurchasableVirtualItem::~CCPurchasableVirtualItem() {
        CC_SAFE_RELEASE(mPurchaseType);
    }
    
    cocos2d::CCDictionary*CCPurchasableVirtualItem::toDictionary() {
        CCDictionary* dict = CCVirtualItem::toDictionary();

        putPurchaseTypeToDict(dict);

        return dict;
    }

    void CCPurchasableVirtualItem::fillPurchaseTypeFromDict(CCDictionary *dict) {
        CCDictionary *purchasableDict = dynamic_cast<CCDictionary *>(dict->objectForKey(JSON_PURCHASABLE_ITEM));
        CC_ASSERT(purchasableDict);
        CCString* purchaseTypeStr = dynamic_cast<CCString *>(purchasableDict->objectForKey(JSON_PURCHASE_TYPE));
        CCAssert(purchaseTypeStr != NULL, "invalid object type in dictionary");
        if (purchaseTypeStr->compare(JSON_PURCHASE_TYPE_MARKET) == 0) {
            CCDictionary *marketItemDict = dynamic_cast<CCDictionary *>(purchasableDict->objectForKey(JSON_PURCHASE_MARKET_ITEM));
            CC_ASSERT(marketItemDict);
            setPurchaseType(CCPurchaseWithMarket::createWithMarketItem(
                    CCMarketItem::createWithDictionary(marketItemDict)));
        } else if (purchaseTypeStr->compare(JSON_PURCHASE_TYPE_VI) == 0) {
            CCString *itemId = dynamic_cast<CCString *>(purchasableDict->objectForKey(JSON_PURCHASE_VI_ITEMID));
            CC_ASSERT(itemId);
            CCInteger *amount = dynamic_cast<CCInteger *>(purchasableDict->objectForKey(JSON_PURCHASE_VI_AMOUNT));
            CC_ASSERT(amount);

            setPurchaseType(CCPurchaseWithVirtualItem::create(itemId, amount));
        } else {
            CCLog("Couldn't determine what type of class is the given purchaseType.");
        }
    }

    void CCPurchasableVirtualItem::putPurchaseTypeToDict(CCDictionary *dict) {
        CCDictionary *purchasableObj = CCDictionary::create();

        if (dynamic_cast<CCPurchaseWithMarket *>(mPurchaseType)) {
            purchasableObj->setObject(CCString::create(JSON_PURCHASE_TYPE_MARKET), JSON_PURCHASE_TYPE);

            CCPurchaseWithMarket *purchaseWithMarket = (CCPurchaseWithMarket *)mPurchaseType;
            CCMarketItem *mi = purchaseWithMarket->getMarketItem();
            purchasableObj->setObject(mi->toDictionary(), JSON_PURCHASE_MARKET_ITEM);
        }
        else if (dynamic_cast<CCPurchaseWithVirtualItem *>(mPurchaseType)) {
            CCPurchaseWithVirtualItem *purchaseWithVirtualItem = (CCPurchaseWithVirtualItem *)mPurchaseType;
            purchasableObj->setObject(CCString::create(JSON_PURCHASE_TYPE_VI), JSON_PURCHASE_TYPE);
            purchasableObj->setObject(purchaseWithVirtualItem->getItemId(), JSON_PURCHASE_VI_ITEMID);
            purchasableObj->setObject(purchaseWithVirtualItem->getAmount(), JSON_PURCHASE_VI_AMOUNT);
        } else {
            CC_ASSERT(false);
        }

        dict->setObject(purchasableObj, JSON_PURCHASABLE_ITEM);
    }


}