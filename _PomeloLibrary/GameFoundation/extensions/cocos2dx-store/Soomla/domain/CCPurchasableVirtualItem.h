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

#ifndef __cocos2dx_store__PurchasableVirtualItem__
#define __cocos2dx_store__PurchasableVirtualItem__

#include "CCVirtualItem.h"
#include "../PurchaseTypes/CCPurchaseType.h"

namespace soomla {
	/** 
     @class CCPurchasableVirtualItem
     @brief A purchasable virtual item.

     A representation of a `CCVirtualItem` that you can actually purchase 
     (eitherwith real money or with other virtual items).
	*/
    class CCPurchasableVirtualItem : public CCVirtualItem {
        SL_SYNTHESIZE_RETAIN_WITH_DICT_DCL(CCPurchaseType*, mPurchaseType, PurchaseType);
    public:
        CCPurchasableVirtualItem(): CCVirtualItem(), mPurchaseType(NULL) {}

		/**
         Creates a `CCPurchasableVirtualItem`.
         @param name see parent.
         @param description see parent.
         @param itemId see parent.
         @param purchaseType Either purchase with market or purchase with
                virtual good.
         @return The item.
		*/
        static CCPurchasableVirtualItem * create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        virtual bool init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, CCPurchaseType * purchaseType);

		/**
         Creates a `CCPurchasableVirtualItem` from a dictionary.
         @param dict A dictionary containing keys to each of the parameters
                required by the create function.
         @return The purchasable virtual item.
		*/
        static CCPurchasableVirtualItem * createWithDictionary(cocos2d::CCDictionary* dict);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        /**
         Converts this `CCPurchasableVirtualItem` to a `CCDictionary`.
         @return `CCDictionary` representation of this 
                `CCPurchasableVirtualItem`.
         */
        virtual cocos2d::CCDictionary* toDictionary();
       
        virtual ~CCPurchasableVirtualItem();
    };
}

#endif /* defined(__cocos2dx_store__PurchasableVirtualItem__) */
