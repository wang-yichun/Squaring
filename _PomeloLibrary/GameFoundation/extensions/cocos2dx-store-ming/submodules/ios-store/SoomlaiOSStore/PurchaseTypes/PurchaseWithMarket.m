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

#import "PurchaseWithMarket.h"
#import "AppStoreItem.h"
#import "StoreUtils.h"
#import "StoreController.h"
#import "EventHandling.h"

@implementation PurchaseWithMarket

@synthesize appStoreItem;

static NSString* TAG = @"SOOMLA PurchaseWithMarket";

- (id)initWithProductId:(NSString*)oProductId andPrice:(double)oPrice {
    if (self = [super init]) {
        self.appStoreItem = [[AppStoreItem alloc] initWithProductId:oProductId andConsumable:kConsumable andPrice:oPrice];
    }
    return self;
}

- (id)initWithAppStoreItem:(AppStoreItem*)oAppStoreItem {
    if (self = [super init]) {
        self.appStoreItem = oAppStoreItem;
    }
    return self;
}

- (void)buy {
    LogDebug(TAG, ([NSString stringWithFormat:@"Starting in-app purchase for productId: %@", self.appStoreItem.productId]));
    
    if (![[StoreController getInstance] buyInAppStoreWithAppStoreItem:self.appStoreItem]) {
        [EventHandling postUnexpectedError:ERR_PURCHASE_FAIL forObject:self];
        return;
    }
    
    [EventHandling postItemPurchaseStarted:self.associatedItem];
}

@end
