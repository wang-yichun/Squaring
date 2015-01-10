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

#ifndef __MarketItemX_H_
#define __MarketItemX_H_

#include "cocos2d.h"
#include "../SoomlaMacros.h"
#include "../data/SoomlaJSONConsts.h"

namespace soomla {
	/** 
     @class CCMarketItem
     @brief An item you can purchase in the market (App Store, Google Play...).

     This class represents an item in the market (App Store, Google Play...).
     Every `CCPurchasableVirtualItem` with `CCPurchaseType` of 
     `CCPurchaseWithMarket` has an instance of this class.
	 */
    class CCMarketItem : public cocos2d::CCObject {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mProductId, ProductId, JSON_MARKETITEM_PRODUCT_ID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mConsumable, Consumable, JSON_MARKETITEM_CONSUMABLE);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCDouble *, mPrice, Price, JSON_MARKETITEM_PRICE);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mMarketPrice, MarketPrice);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mMarketTitle, MarketTitle);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mMarketDescription, MarketDescription);
   
    public:
        
        /**
         Every item offered in the market (App Store, Google Play...) has one 
         of the five following purchase types.
         */
        enum Consumable {
            NONCONSUMABLE,
            CONSUMABLE,
            SUBSCRIPTION,
        };
        CCMarketItem(): mProductId(NULL), mConsumable(NULL), mPrice(NULL), mMarketPrice(NULL), mMarketTitle(NULL), mMarketDescription(NULL) {};

		/**
         Creates a `CCMarketItem`.
         @param productId The item's id in the native store.
         @param consumable Whether or not the item is consumable.
         @param price The price of the item, in USD.
         @return The Market item.
		 */
        static CCMarketItem *create(cocos2d::CCString *productId, cocos2d::CCInteger *consumable, cocos2d::CCDouble * price);
        bool init(cocos2d::CCString *productId, cocos2d::CCInteger *consumable, cocos2d::CCDouble * price);

		/**
         Creates a `CCMarketItem` from a dictionary.
         @param dict A dictionary containing keys for the item's product id,
                price and consumable status.
         @return The Market item.
		*/
		static CCMarketItem *createWithDictionary(cocos2d::CCDictionary* dict);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCMarketItem();

        /**
         Converts this `CCMarketItem` to a `CCDictionary`.
         @return `CCDictionary` representation of this `CCMarketItem`.
         */
        virtual cocos2d::CCDictionary* toDictionary();
    };
};


#endif //__MarketItemX_H_
