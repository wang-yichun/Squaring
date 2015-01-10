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

#include "cocos2dx_StoreInfo.h"
#import "VirtualCurrencyPack.h"
#import "VirtualGood.h"
#import "StoreInfo.h"
#import "UpgradeVG.h"
#import "AppStoreItem.h"
#import "VirtualItemNotFoundException.h"
#import "PurchasableVirtualItem.h"
#import "PurchaseWithMarket.h"
#import "PurchaseWithVirtualItem.h"

/**
 * This implementation is used to let cocos2dx functions retrieve data from StoreInfo.
 *
 * You can see the documentation of every function in StoreInfo.
 */


string cocos2dx_StoreInfo::getGoodFirstUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        UpgradeVG* vgu = [[StoreInfo getInstance] firstUpgradeForGoodWithItemId:str];
        return [vgu.itemId UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getGoodLastUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        UpgradeVG* vgu = [[StoreInfo getInstance] lastUpgradeForGoodWithItemId:str];
        return [vgu.itemId UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getItemProductId(string itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        VirtualItem* item = [[StoreInfo getInstance] virtualItemWithId:str];
        NSString* ret = @"";
        if ([item isKindOfClass:[PurchasableVirtualItem class]]) {
            PurchasableVirtualItem* pvi = (PurchasableVirtualItem*)item;
            if ([pvi.purchaseType isKindOfClass:[PurchaseWithMarket class]]) {
                PurchaseWithMarket* pwm = (PurchaseWithMarket*)pvi.purchaseType;
                ret = pwm.appStoreItem.productId;
            }
        }
        return [ret UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getItemName(string itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        VirtualItem* item = [[StoreInfo getInstance] virtualItemWithId:str];
        return [item.name UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getItemDescription(string itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        VirtualItem* item = [[StoreInfo getInstance] virtualItemWithId:str];
        return [item.description UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

double cocos2dx_StoreInfo::getItemPrice(string itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        VirtualItem* item = [[StoreInfo getInstance] virtualItemWithId:str];
        double ret = 0;
        if ([item isKindOfClass:[PurchasableVirtualItem class]]) {
            PurchasableVirtualItem* pvi = (PurchasableVirtualItem*)item;
            if ([pvi.purchaseType isKindOfClass:[PurchaseWithMarket class]]) {
                PurchaseWithMarket* pwm = (PurchaseWithMarket*)pvi.purchaseType;
                ret = pwm.appStoreItem.price;
            }
            
            if ([pvi.purchaseType isKindOfClass:[PurchaseWithVirtualItem class]]) {
                PurchaseWithVirtualItem* pwvi = (PurchaseWithVirtualItem*)pvi.purchaseType;
                ret = pwvi.amount;
            }
        }
        return ret;
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

