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

#include "cocos2dx_StoreController.h"
#import "StoreController.h"
#import "VirtualItemNotFoundException.h"
#import "InsufficientFundsException.h"
#import "NotEnoughGoodsException.h"
#import "StoreAssets.h"
#import "cocos2dx_EventDispatcher.h"
#import "PurchasableVirtualItem.h"
#import "StoreInfo.h"
#import "PurchaseWithMarket.h"
#import "AppStoreItem.h"
#import "ObscuredNSUserDefaults.h"

#import "StoreAssetsDefine.h"

/**
 * This implementation is used to let cocos2dx functions perform actions on StoreController.
 *
 * You can see the documentation of every function in StoreController.
 */


void cocos2dx_StoreController::storeOpening() {
    [[StoreController getInstance] storeOpening];
}

void cocos2dx_StoreController::storeClosing() {
    [[StoreController getInstance] storeClosing];
}

void cocos2dx_StoreController::initialize(StoreAssetsType sa) {
    /**
     * We initialize StoreController when the application loads !
     *
     */
    string customSecret = "PapatuCustomSec";
    NSString * str = [[NSString alloc] initWithBytes:customSecret.c_str() length:strlen(customSecret.c_str()) encoding:NSUTF8StringEncoding];
    id<IStoreAsssets> storeAssets = [[StoreAssets alloc] init];
    [(StoreAssets*)storeAssets initWithData:sa];
    [[StoreController getInstance] initializeWithStoreAssets:storeAssets andCustomSecret:str];
    
    // Checking if it's a first run and adding 10000 currencies if it is.
    // OFCOURSE... THIS IS JUST FOR TESTING.
    if (![ObscuredNSUserDefaults boolForKey:@"NotFirstLaunch" withDefaultValue:NO])
    {
        [ObscuredNSUserDefaults setBool:YES forKey:@"NotFirstLaunch"];
        for (int i = 0; i < sa.VirtualCurrencyCount; i++) {
            [(VirtualCurrency*)[storeAssets.virtualCurrencies objectAtIndex:i] giveAmount:sa.vc[i].InitialAmount];
        }
    }
    
    [cocos2dx_EventDispatcher initialize];
}

void cocos2dx_StoreController::buyMarketItem(string productId) throw(cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:productId.c_str() length:strlen(productId.c_str()) encoding:NSUTF8StringEncoding];
        PurchasableVirtualItem* pvi = [[StoreInfo getInstance] purchasableItemWithProductId:str];
        if ([pvi.purchaseType isKindOfClass:[PurchaseWithMarket class]]) {
            [[StoreController getInstance] buyInAppStoreWithAppStoreItem:((PurchaseWithMarket*)pvi.purchaseType).appStoreItem];
        } else {
            throw cocos2dx_VirtualItemNotFoundException();
        }
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreController::restoreTransactions() {
    @try {
        [[StoreController getInstance] restoreTransactions];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}



