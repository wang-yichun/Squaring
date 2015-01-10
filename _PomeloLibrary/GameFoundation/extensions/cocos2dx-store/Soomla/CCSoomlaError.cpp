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

// Created by Fedor Shubin on 5/21/13.

#include "CCSoomlaError.h"

USING_NS_CC;

namespace soomla {
    #define JSON_ERROR_CODE "errorCode"

    #define TAG "CCSoomlaError" // used for Log error messages

    CCSoomlaError *CCSoomlaError::createWithObject(cocos2d::CCObject *obj) {
        CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
        if (dict != NULL && dict->objectForKey(JSON_ERROR_CODE) != NULL) {
            CCInteger *errorCode = dynamic_cast<CCInteger *>(dict->objectForKey(JSON_ERROR_CODE));
            CC_ASSERT(errorCode);

            CCSoomlaError *ret = new CCSoomlaError();
            ret->autorelease();
            ret->init(errorCode->getValue());
            return ret;
        } else {
            return NULL;
        }
    }

    CCSoomlaError *CCSoomlaError::createVirtualItemNotFoundException() {
        CCSoomlaError *ret = new CCSoomlaError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_ITEM_NOT_FOUND);
        return ret;
    }

    CCSoomlaError *CCSoomlaError::createInsufficientFundsException() {
        CCSoomlaError *ret = new CCSoomlaError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS);
        return ret;
    }

    CCSoomlaError *CCSoomlaError::createNotEnoughGoodsException() {
        CCSoomlaError *ret = new CCSoomlaError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS);
        return ret;
    }

    bool CCSoomlaError::init(int code) {
        mCode = code;

        if (code == SOOMLA_EXCEPTION_ITEM_NOT_FOUND) {
            CCLog("%s %s", TAG, "SOOMLA/COCOS2DX Got VirtualItemNotFoundException exception");
            mInfo = "VirtualItemNotFoundException()";
        }
        else if (code == SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS) {
            CCLog("%s %s", TAG, "SOOMLA/COCOS2DX Got InsufficientFundsException exception");
            mInfo = "InsufficientFundsException()";
        }
        else if (code == SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS) {
            CCLog("%s %s", TAG, "SOOMLA/COCOS2DX Got NotEnoughGoodsException exception");
            mInfo = "NotEnoughGoodsException()";
        }
        else if (code == SOOMLA_EXCEPTION_OTHER) {
            CCLog("%s %s", TAG, "SOOMLA/COCOS2DX Got Unknown exception");
            mInfo = "unknown";
        } else {
            CC_ASSERT(false);
            return false;
        }

        return true;
    }
}
