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

#ifndef __CCSoomlaError_H_
#define __CCSoomlaError_H_

#include "cocos2d.h"

#define SOOMLA_NO_ERROR 0
#define SOOMLA_EXCEPTION_ITEM_NOT_FOUND -1
#define SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS -2
#define SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS -3
#define SOOMLA_EXCEPTION_OTHER -4

namespace soomla {
	/** 
     @class CCSoomlaError
     @brief An interface for error handling, analogous exception handling in 
     the Java SDK.
     
     Pass this as a pointer to this class to functions requiring it and
     examine the result. If its value is not null then something went wrong.
	 */
    class CCSoomlaError: public cocos2d::CCObject {
		/**
         The error code.
         Can be one of `SOOMLA_EXCEPTION_ITEM_NOT_FOUND`,
         `SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS`, or
         `SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS`.
		 */
        CC_SYNTHESIZE_READONLY(int, mCode, Code);
    
    public:
        static CCSoomlaError *createWithObject(cocos2d::CCObject *obj);

        static CCSoomlaError *createVirtualItemNotFoundException();
        
        static CCSoomlaError *createInsufficientFundsException();
        
        static CCSoomlaError *createNotEnoughGoodsException();

        const char *getInfo() {return mInfo.c_str();};
    private:
		/**
         Extra information about what went wrong.
		 */
        std::string mInfo;

        CCSoomlaError():
            mCode(0),
            mInfo("") {}

        bool init(int code);
    };
};


#endif //__CCSoomlaError_H_
