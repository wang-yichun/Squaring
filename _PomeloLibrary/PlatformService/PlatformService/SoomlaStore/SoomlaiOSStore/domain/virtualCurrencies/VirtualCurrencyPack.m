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

#import "VirtualCurrencyPack.h"
#import "VirtualCurrency.h"
#import "JSONConsts.h"
#import "VirtualItemNotFoundException.h"
#import "AppStoreItem.h"
#import "StoreUtils.h"
#import "StorageManager.h"
#import "VirtualCurrencyStorage.h"
#import "StoreInfo.h"

@implementation VirtualCurrencyPack

@synthesize currencyAmount, currencyItemId;

static NSString* TAG = @"SOOMLA VirtualCurrencyPack";

- (id)initWithName:(NSString*)oName andDescription:(NSString*)oDescription
            andItemId:(NSString*)oItemId andCurrencyAmount:(int)oCurrencyAmount andCurrency:(NSString*)oCurrencyItemId
            andPurchaseType:(PurchaseType*)oPurchaseType {
    if (self = [super initWithName:oName andDescription:oDescription andItemId:oItemId andPurchaseType:oPurchaseType]) {
        self.currencyItemId = oCurrencyItemId;
        self.currencyAmount = oCurrencyAmount;
    }
    
    return self;
}

- (id)initWithDictionary:(NSDictionary*)dict{
    if (self = [super initWithDictionary:dict]) {
        self.currencyAmount = [[dict objectForKey:JSON_CURRENCYPACK_CURRENCYAMOUNT] intValue];
        
        self.currencyItemId = [dict objectForKey:JSON_CURRENCYPACK_CURRENCYITEMID];
    }
    
    return self;
}

- (NSDictionary*)toDictionary{
    NSDictionary* parentDict = [super toDictionary];
    NSMutableDictionary* toReturn = [[NSMutableDictionary alloc] initWithDictionary:parentDict];
    [toReturn setValue:[NSNumber numberWithInt:self.currencyAmount] forKey:JSON_CURRENCYPACK_CURRENCYAMOUNT];
    [toReturn setValue:self.currencyItemId forKey:JSON_CURRENCYPACK_CURRENCYITEMID];
    
    return toReturn;
}


- (void)giveAmount:(int)amount {
    VirtualCurrency* currency = NULL;
    @try {
        currency = (VirtualCurrency*)[[StoreInfo getInstance] virtualItemWithId:self.currencyItemId];
    } @catch (VirtualItemNotFoundException* ex) {
        LogError(TAG, ([NSString stringWithFormat:@"VirtualCurrency with itemId: %@ doesn't exist! Can't give this pack.", self.currencyItemId]));
        return;
    }
    [[[StorageManager getInstance] virtualCurrencyStorage] addAmount:amount*self.currencyAmount toItem:currency];
}

- (void)takeAmount:(int)amount {
    VirtualCurrency* currency = NULL;
    @try {
        currency = (VirtualCurrency*)[[StoreInfo getInstance] virtualItemWithId:self.currencyItemId];
    } @catch (VirtualItemNotFoundException* ex) {
        LogError(TAG, ([NSString stringWithFormat:@"VirtualCurrency with itemId: %@ doesn't exist! Can't take this pack.", self.currencyItemId]));
        return;
    }
    [[[StorageManager getInstance] virtualCurrencyStorage] removeAmount:amount*self.currencyAmount fromItem:currency];
}

- (void)resetBalance:(int)balance {
    // Not supported for VirtualCurrencyPacks !
    LogError(TAG, @"Someone tried to reset balance of CurrencyPack. That's not right.");
}

- (BOOL)canBuy {
    return YES;
}

@end
