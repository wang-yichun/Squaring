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

#ifndef __SingleUsePackVGX_H_
#define __SingleUsePackVGX_H_

#include "CCVirtualGood.h"

namespace soomla {
	/** 
     @class CCSingleUsePackVG
     @brief A pack of single use virtual goods.

     Single Use Packs are just bundles of `SingleUseVG`s.
     This kind of virtual good can be used to let your users buy more than one
     `SingleUseVG` at once.
     
     The `SingleUsePackVG`'s characteristics are:
     1. Can be purchased an unlimited number of times.
     2. Doesn't have a balance in the database. The `SingleUseVG` that's 
     associated with this pack has its own balance. When your users buy a 
     `SingleUsePackVG`, the balance of the associated `SingleUseVG` goes up in 
     the amount that this pack represents.
     
     Real Game Examples: 'Box Of Chocolates', '10 Swords'
     
     NOTE: In case you want this item to be available for purchase with real $$
     you'll need to define it in the Market (Google Play, App Store, etc...).
     
     Inheritance: CCSingleUsePackVG > CCVirtualGood > CCPurchasableVirtualItem >
     CCVirtualItem
     */
    class CCSingleUsePackVG : public CCVirtualGood {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mGoodItemId, GoodItemId, JSON_VGP_GOOD_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mGoodAmount, GoodAmount, JSON_VGP_GOOD_AMOUNT);
    public:
        CCSingleUsePackVG(): CCVirtualGood(), mGoodItemId(NULL), mGoodAmount(NULL) {};
        
        /**
         Creates a `CCSingleUsePackVG`.
         @param goodItemId The item id of the Single Use item associated with 
                this Pack.
         @param goodAmount The amount of Single Use items in the Pack.
         @param name see parent.
         @param description see parent.
         @param itemId see parent.
         @param purchaseType see parent.
         @return The Sinlge Use Pack good.
         */
        static CCSingleUsePackVG *create(cocos2d::CCString* goodItemId, cocos2d::CCInteger* goodAmount,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        bool init(cocos2d::CCString* goodItemId, cocos2d::CCInteger* goodAmount,
				  cocos2d::CCString* name, cocos2d::CCString* description,
				  cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        
        /**
         Creates a `CCSingleUsePackVG` from a dictionary.
         @param dict A dictionary containing keys to each of the parameters
                required by the create function.
         @return The Sinlge Use Pack good.
         */
        static CCSingleUsePackVG *createWithDictionary(cocos2d::CCDictionary *dict);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        /**
         Converts this `CCSingleUsePackVG` to a `CCDictionary`.
         @return `CCDictionary` representation of this `CCSingleUsePackVG`.
         */
        cocos2d::CCDictionary *toDictionary();

        virtual ~CCSingleUsePackVG();
    };
};

#endif //__SingleUsePackVGX_H_
