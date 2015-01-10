/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __cocos2dx_store__cocos2dx_StoreInfo__
#define __cocos2dx_store__cocos2dx_StoreInfo__

#include <iostream>
#include "cocos2dx_VirtualItemNotFoundException.h"
#include <string>

using namespace std;

class cocos2dx_StoreInfo {
public:
    
    // static string getVirtualItem(string itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    // static string getPurchasableItem(string productId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getGoodFirstUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getGoodLastUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
	static string getItemProductId(string itemId) throw (cocos2dx_VirtualItemNotFoundException&);        
    static string getItemName(string itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getItemDescription(string itemId) throw (cocos2dx_VirtualItemNotFoundException&);
	static double getItemPrice(string itemId) throw (cocos2dx_VirtualItemNotFoundException&);

};


#endif /* defined(__cocos2dx_store__cocos2dx_StoreInfo__) */
