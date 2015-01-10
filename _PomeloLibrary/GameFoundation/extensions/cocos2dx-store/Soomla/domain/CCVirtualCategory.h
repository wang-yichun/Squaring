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

#include "cocos2d.h"
#include "../SoomlaMacros.h"
#include "../data/SoomlaJSONConsts.h"

#ifndef __VirtualCategoryX_H_
#define __VirtualCategoryX_H_

namespace soomla {
	/** 
     @class CCVirtualCategory
     @brief A category for virtual items.

     This class is a definition of a category. A single category can be 
     associated with many virtual goods. Virtual categories help in organizing 
     your economy's virtual goods.
	 */
    class CCVirtualCategory : public cocos2d::CCObject {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mName, Name, JSON_CATEGORY_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCArray*, mGoodItemIds, GoodItemIds, JSON_CATEGORY_GOODSITEMIDS);
    public:
	CCVirtualCategory(): mName(NULL), mGoodItemIds(NULL) {};

		/**
         Creates a virtual category.
         @param name The name of the category.
         @param goodItemIds An array containing the item ids of all the items 
                in this category.
         @return The virtual category.
		 */
        static CCVirtualCategory *create(cocos2d::CCString *name, cocos2d::CCArray *goodItemIds);
        bool init(cocos2d::CCString *name, cocos2d::CCArray *goodItemIds);

		/**
         Creates a virtual category.
         @param dict A dictionary containing keys to each of the parameters
                required by the create function.
         @return The virtual category.
		*/
		static CCVirtualCategory *createWithDictionary(cocos2d::CCDictionary *dict);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        /**
         Converts this `~CCVirtualCategory` to a `CCDictionary`.
         @return `CCDictionary` representation of this `~CCVirtualCategory`.
         */
        cocos2d::CCDictionary *toDictionary();

        virtual ~CCVirtualCategory();
    };
};


#endif //__VirtualCategoryX_H_
