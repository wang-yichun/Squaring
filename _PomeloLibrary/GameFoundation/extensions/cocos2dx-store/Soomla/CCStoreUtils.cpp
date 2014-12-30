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

#include "CCStoreUtils.h"
#include "cocos2d.h"

namespace soomla {
    void CCStoreUtils::logDebug(const char *tag, const char *message) {
        if (SOOMLA_DEBUG) {
            CCLOG("%s %s", tag, message);
        }
    }
    void CCStoreUtils::logError(const char *tag, const char *message) {
        CCLOGERROR("%s %s", tag, message);
    }

    void CCStoreUtils::logException(char const *tag, CCSoomlaError *error) {
        CC_ASSERT(error);
        cocos2d::CCLog("%s Soomla error: error code: %d, with information %s", tag, error->getCode(), error->getInfo());
    }

};
