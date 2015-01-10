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

#ifndef __cocos2dx_store__cocos2dx_StoreInventory__
#define __cocos2dx_store__cocos2dx_StoreInventory__

#include <iostream>
#include <string>
#include "cocos2dx_VirtualItemNotFoundException.h"
#include "cocos2dx_InsufficientFundsException.h"

using namespace std;

class cocos2dx_StoreInventory {

public:
    static void buy(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&);
    static int getItemBalance(string itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static void giveItem(string itemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&);
    static void takeVirtualItem(string itemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&);
    static void equipGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static void unEquipGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static bool isGoodEquipped(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static int getGoodUpgradeLevel(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) ;
    static string getGoodCurrentUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static void upgradeVirtualGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&);
    static void removeUpgrades(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) ;
    static bool nonConsumableItemExists(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static void addNonConsumableItem(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&) ;
    static void removeNonConsumableItem(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&);    
};

#endif
