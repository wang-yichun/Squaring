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

#ifndef __SingleUseVGX_H_
#define __SingleUseVGX_H_

#include <iostream>


#include "CCVirtualGood.h"

namespace soomla {
	/** 
     @class CCSingleUseVG
     @brief A consumable virtual good.
     
     SingleUse virtual goods are the most common type of `VirtualGood`.
     The `CCSingleUseVG`'s characteristics are:
     1. Can be purchased an unlimited number of times.
     2. Has a balance that is saved in the database. Its balance goes up when
        you `give` it or `buy` it. The balance goes down when you `take` it.
     Real Game Examples: 'Hat', 'Sword', 'Muffin'
     NOTE: In case you want this item to be available for purchase with real $$
     you'll need to define it in the Market (Google Play, App Store, etc...).
     
     Inheritance: SingleUseVG > VirtualGood > PurchasableVirtualItem > 
     VirtualItem
     */
    class CCSingleUseVG : public CCVirtualGood {
    
    public:
		/**
         Creates a `CCSingleUseVG`.
         @param name The virtual good's name.
         @param description The virtual good's description.
         @param itemId The virtual good's itemId.
         @param purchaseType The purchase type for this virtual good.
         @return The Single Use virtual good.
		*/
        static CCSingleUseVG *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);

		/**
         Create a `CCSingleUseVG` from a dictionary.
         @param dict A dictionary containing keys to each of the parameters
                required by the `create` function.
         @return The Single Use virtual good.
		*/
		static CCSingleUseVG *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};

#endif //__SingleUseVGX_H_
