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

#ifndef __VirtualCurrencyPackX_H_
#define __VirtualCurrencyPackX_H_

#include "../../SoomlaMacros.h"
#include "../CCPurchasableVirtualItem.h"

namespace soomla {
	/** 
     @class CCVirtualCurrencyPack
     @brief A virtual currency pack.

     Every game has its virtual currencies. Here you represent a pack of a 
     specific `CCVirtualCurrency`. Real Game Example: If virtual currency in 
     your game is a 'Coin', you will sell packs of 'Coins' (e.g. "10 Coins Set" 
     or "Super Saver Pack").
     
     NOTE: In case you want this item to be available for purchase in the native 
     store (with real money) you'll need to define the item in the App Store,
     Google Play, etc..
     
     Inheritance: CCVirtualCurrencyPack > CCPurchasableVirtualItem > 
     CCVirtualItem
	 */
    class CCVirtualCurrencyPack : public CCPurchasableVirtualItem {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mCurrencyAmount, CurrencyAmount, JSON_CURRENCYPACK_CURRENCYAMOUNT);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mCurrencyItemId, CurrencyItemId, JSON_CURRENCYPACK_CURRENCYITEMID);
    public:
	CCVirtualCurrencyPack(): CCPurchasableVirtualItem(), mCurrencyAmount(NULL), mCurrencyItemId(NULL) {};

		/**
         Creates a `CCVirtualCurrencyPack`.
         @param name see parent.
         @param description see parent.
         @param itemId see parent.
         @param currencyAmount The amount of currency in the pack.
         @param currencyItemId The itemId of the currency associated with this 
                pack.
         @param purchaseType see parent.
         @return The currency pack.
		*/
        static CCVirtualCurrencyPack *create(cocos2d::CCString* name, cocos2d::CCString* description,
											 cocos2d::CCString* itemId, cocos2d::CCInteger* currencyAmount, cocos2d::CCString* currencyItemId,
											 CCPurchaseType * purchaseType);
        bool init(cocos2d::CCString* name, cocos2d::CCString* description,
                  cocos2d::CCString* itemId, cocos2d::CCInteger* currencyAmount, cocos2d::CCString* currencyItemId,
                  CCPurchaseType * purchaseType);

		/**
         Creates a `CCVirtualCurrencyPack`.
         @param dict A dictionary containing keys to each of the parameters 
                required by the create function.
         @return The pack.
		*/
        static CCVirtualCurrencyPack *createWithDictionary(cocos2d::CCDictionary *dict);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        /**
         Converts this `CCVirtualCurrencyPack` to a `CCDictionary`.
         @return `CCDictionary` representation of this `CCVirtualCurrencyPack`.
         */
        cocos2d::CCDictionary *toDictionary();

        virtual ~CCVirtualCurrencyPack();
    };
};


#endif //__VirtualCurrencyPackX_H_
