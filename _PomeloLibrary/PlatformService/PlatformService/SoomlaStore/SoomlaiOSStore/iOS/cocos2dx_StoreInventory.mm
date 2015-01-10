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

#include "cocos2dx_StoreInventory.h"
#import "StoreInventory.h"
#import "VirtualItemNotFoundException.h"
#import "InsufficientFundsException.h"


/**
 * This implementation is used to let cocos2dx functions perform actions on StoreInventory.
 *
 * You can see the documentation of every function in StoreInventory.
 */

void cocos2dx_StoreInventory::buy(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory buyItemWithItemId:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
    @catch (InsufficientFundsException *ex2) {
        throw cocos2dx_InsufficientFundsException();
    }
}

int cocos2dx_StoreInventory::getItemBalance(string itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory getItemBalance:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::giveItem(string itemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory giveAmount:amount ofItem:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::takeVirtualItem(string itemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory takeAmount:amount ofItem:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::equipGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory equipVirtualGoodWithItemId:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::unEquipGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory unEquipVirtualGoodWithItemId:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

bool cocos2dx_StoreInventory::isGoodEquipped(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory isVirtualGoodWithItemIdEquipped:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::getGoodUpgradeLevel(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory goodUpgradeLevel:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInventory::getGoodCurrentUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        NSString* vguItemId = [StoreInventory goodCurrentUpgrade:str];
        return [vguItemId UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::upgradeVirtualGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory upgradeVirtualGood:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
    @catch (InsufficientFundsException *ex2) {
        throw cocos2dx_InsufficientFundsException();
    }
}

void cocos2dx_StoreInventory::removeUpgrades(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory removeUpgrades:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

bool cocos2dx_StoreInventory::nonConsumableItemExists(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:nonConsItemId.c_str() length:strlen(nonConsItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory nonConsumableItemExists:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::addNonConsumableItem(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:nonConsItemId.c_str() length:strlen(nonConsItemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory addNonConsumableItem:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreInventory::removeNonConsumableItem(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:nonConsItemId.c_str() length:strlen(nonConsItemId.c_str()) encoding:NSUTF8StringEncoding];
        [StoreInventory removeNonConsumableItem:str];
    }
    @catch (VirtualItemNotFoundException *ex1) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

