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

//  Created by Igor Yegoroff on 5/17/13.

#include "CCVirtualCurrency.h"

namespace soomla {
    
    CCVirtualCurrency* CCVirtualCurrency::create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId) {
        CCVirtualCurrency* pRet = new CCVirtualCurrency();
        if (pRet) {
            pRet->autorelease();
            pRet->init(name, description, itemId);
        }
        return pRet;
    }

    CCVirtualCurrency* CCVirtualCurrency::createWithDictionary(cocos2d::CCDictionary* dict) {
        CCVirtualCurrency* pRet = new CCVirtualCurrency();
        if (pRet) {
            pRet->autorelease();
            pRet->initWithDictionary(dict);
        }
        return pRet;
    }
}