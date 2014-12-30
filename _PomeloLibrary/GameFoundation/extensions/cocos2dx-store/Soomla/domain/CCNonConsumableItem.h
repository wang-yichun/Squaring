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

#ifndef __NonConsumableItemX_H_
#define __NonConsumableItemX_H_

#include "CCPurchasableVirtualItem.h"

namespace soomla {
	/** 
     @class CCNonConsumableItem
     @brief A non consumable virtual item.

     A representation of a non-consumable item in the store.
     These kinds of items are bought by the user once and kept for him/her 
     forever.
     
     NOTE: Don't be confused: this is not a `CCLifetimeVG`, it's a Non-
     Consumable item in the store. This means that the product is purchased only 
     once per user (such as a new level in a game), and is remembered by the 
     store.
     
     Inheritance: CCNonConsumableItem > CCPurchasableVirtualItem > CCVirtualItem
	*/

    class CCNonConsumableItem : public CCPurchasableVirtualItem {
    
    public:
        CCNonConsumableItem(): CCPurchasableVirtualItem() {}

		/**
         Creates a `CCNonConsumableItem`.
         @param name see parent.
         @param description see parent.
         @param itemId see parent.
         @param purchaseType see parent.
         @return The non-consumable item.
		*/
		static CCNonConsumableItem * create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId,
            CCPurchaseType *purchaseType);

		/**
         Creates a `CCNonConsumableItem` from a dictionary.
         @param dict A dictionary containing keys to each of the parameters
                required by the create function.
         @return The non-consumable item.
		*/
		static CCNonConsumableItem * createWithDictionary(cocos2d::CCDictionary* dict);
    };
};

#endif //__NonConsumableItemX_H_
