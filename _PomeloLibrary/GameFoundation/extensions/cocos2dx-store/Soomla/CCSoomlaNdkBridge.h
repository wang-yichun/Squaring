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

// Created by Fedor Shubin on 5/20/13.

#ifndef __CCSoomlaNdkBridge_H_
#define __CCSoomlaNdkBridge_H_

#include "cocos2d.h"
#include "CCSoomlaError.h"

namespace soomla {
	/** @class CCSoomlaNdkBridge
		@brief The bridge between the application and the Cocos2d-x code.

		This class receives calls from the native application and sends them 
		over to the Cocos2d-x code, and vice versa.
	 */
    class CCSoomlaNdkBridge {
    
    public:
		/**
         Call a native application function.
         @param params A `CCDictionary` containing the name of the function
                to call and parameters to pass to it.
         @param pError A `CCSoomlaError` that can be used to tell if there was
                an error.
         @return The return value of the called function as a cocos2d::CCObject.
		 */
        static cocos2d::CCObject *callNative(cocos2d::CCDictionary *params, CCSoomlaError **pError);
    };
};


#endif //__CCSoomlaNdkBridge_H_
