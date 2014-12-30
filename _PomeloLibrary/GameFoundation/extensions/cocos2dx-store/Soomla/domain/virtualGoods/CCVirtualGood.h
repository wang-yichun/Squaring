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

#ifndef __VirtualGoodX_H_
#define __VirtualGoodX_H_

#include "../CCPurchasableVirtualItem.h"

namespace soomla {
	/** 
     @class CCVirtualGood
     @brief A virtual good.
	
     This is an abstract representation of the application's virtual goods.
     Your game's virtual economy revolves around virtual goods. This class 
     defines the abstract and most common virtual goods while the descendants 
     of this class define specific definitions of virtual goods.
     
     Inheritance: CCVirtualGood > CCPurchasableVirtualItem > CCVirtualItem
     */
    class CCVirtualGood : public CCPurchasableVirtualItem {
    
    public:
		
        /**
		   Creates a `CCVirtualGood`.
		   @param name see parent.
		   @param description see parent.
		   @param itemId see parent.
		   @param purchaseType see parent.
		   @return The virtual good.
		*/
        static CCVirtualGood *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);

		/**
         Creates a `CCLifetimeVG` from a dictionary.
         @param dict A dictionary containing keys to each of the parameters 
                required by the `create` function.
         @return The virtual good.
		*/
        static CCVirtualGood *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};


#endif //__VirtualGoodX_H_
