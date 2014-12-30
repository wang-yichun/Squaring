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

//  Created by Igor Yegoroff on 5/16/13.

#ifndef __cocos2dx_store__VirtualItem__
#define __cocos2dx_store__VirtualItem__

#include "cocos2d.h"
#include "../SoomlaMacros.h"
#include "../data/SoomlaJSONConsts.h"

namespace soomla {
	/** 
     @class CCVirtualItem
     @brief A virtual item.
     
     This is the parent class of all virtual items in the application.
     Almost every entity in your virtual economy will be a virtual item. There 
     are many types of virtual items - each one of the various types extends
     `CCVirtualItem` and adds its own behavior on top of it.
	*/    
    class CCVirtualItem : public cocos2d::CCObject {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mName, Name, JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mDescription, Description, JSON_ITEM_DESCRIPTION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mItemId, ItemId, JSON_ITEM_ITEMID);
        
    public:
        CCVirtualItem(): mName(NULL), mDescription(NULL), mItemId(NULL) {}

		/**
         Creates an instance of `CCVirtualItem`.
         @param name The item's name.
         @param description The item's description.
         @param itemId The item's itemId.
         @return The virtual item.
		*/
        static CCVirtualItem * create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);
        virtual bool init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);

		/**
         Creates a `CCVirtualItem` from a dictionary.
         @param dict A dictionary containing keys to each of the parameters 
                required by the create function.
         @return The item.
		*/
		static CCVirtualItem * createWithDictionary(cocos2d::CCDictionary* dict);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        virtual ~CCVirtualItem();
        
        /**
         Converts this `CCVirtualItem` to a `CCDictionary`.
         @return `CCDictionary` representation of this `CCVirtualItem`.
         */
        virtual cocos2d::CCDictionary* toDictionary();
    };
    
}

#endif /* defined(__cocos2dx_store__VirtualItem__) */
