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

#import "VirtualGoodStorage.h"
#import "VirtualGood.h"
#import "StorageManager.h"
#import "KeyValDatabase.h"
#import "StoreEncryptor.h"
#import "EventHandling.h"
#import "StoreUtils.h"
#import "StoreInfo.h"
#import "VirtualItemNotFoundException.h"
#import "UpgradeVG.h"
#import "EquippableVG.h"

@implementation VirtualGoodStorage

- (id)init {
    if (self = [super init]) {
        tag = @"SOOMLA VirtualGoodStorage";
    }
    return self;
}

- (void)removeUpgradesFrom:(VirtualGood*)good {
    LogDebug(tag, ([NSString stringWithFormat:@"Removing upgrade information from virtual good: %@", good.name]));
    
    NSString* key = [StoreEncryptor encryptString:[KeyValDatabase keyGoodUpgrade:good.itemId]];
    
    [[[StorageManager getInstance] kvDatabase] deleteKeyValWithKey:key];
    
    [EventHandling postGoodUpgrade:good withGoodUpgrade:nil];
}

- (void)assignCurrentUpgrade:(UpgradeVG*)upgradeVG toGood:(VirtualGood*)good {
    if ([[self currentUpgradeOf:good].itemId isEqualToString:upgradeVG.itemId]) {
        return;
    }
    
    LogDebug(tag, ([NSString stringWithFormat:@"Assigning upgrade %@ to virtual good: %@", upgradeVG.name, good.name]));
    
    NSString* key = [StoreEncryptor encryptString:[KeyValDatabase keyGoodUpgrade:good.itemId]];
    
    NSString* upItemId = [StoreEncryptor encryptString:upgradeVG.itemId];
    [[[StorageManager getInstance] kvDatabase] setVal:upItemId forKey:key];
    
    [EventHandling postGoodUpgrade:good withGoodUpgrade:upgradeVG];
}

- (UpgradeVG*)currentUpgradeOf:(VirtualGood*)good {
    LogDebug(tag, ([NSString stringWithFormat:@"Fetching upgrade to virtual good: %@", good.name]));
    
    NSString* key = [StoreEncryptor encryptString:[KeyValDatabase keyGoodUpgrade:good.itemId]];
    
    NSString* upItemId = [[[StorageManager getInstance] kvDatabase] getValForKey:key];
    
    if(!upItemId) {
        LogError(tag, ([NSString stringWithFormat:@"You tried to fetch the current upgrade of %@ but there's no upgrade in the DB for it.", good.name]));
        return nil;
    }
    
    @try {
        upItemId = [StoreEncryptor decryptToString:upItemId];
        return (UpgradeVG*)[[StoreInfo getInstance] virtualItemWithId:upItemId];
    } @catch (VirtualItemNotFoundException* ex){
        LogError(tag, @"The current upgrade's itemId from the DB is not found in StoreInfo.");
    } @catch (NSException* e) {
        LogError(tag, @"Something bad happend while trying to decrypt or fetch current upgrade.");
    }
    
    return nil;
}

- (BOOL)isGoodEquipped:(EquippableVG*)good {
    LogDebug(tag, ([NSString stringWithFormat:@"checking if virtual good with itemId: %@ is equipped", good.itemId]));
    
    NSString* key = [StoreEncryptor encryptString:[KeyValDatabase keyGoodEquipped:good.itemId]];
    NSString* val = [[[StorageManager getInstance] kvDatabase] getValForKey:key];
    
    if (!val || [val length]==0){
        return NO;
    }
    
    // we're returning YES as long as there's a value for the required key.
    return YES;
}

- (void)equipGood:(EquippableVG*)good {
    if ([self isGoodEquipped:good]) {
        return;
    }
    
    [self privEquipGood:good withEquipValue:YES];
}

- (void)unequipGood:(EquippableVG*)good {
    if (![self isGoodEquipped:good]) {
        return;
    }
    
    [self privEquipGood:good withEquipValue:NO];
}

- (void)privEquipGood:(EquippableVG*)good withEquipValue:(BOOL)equip{
    LogDebug(tag, ([NSString stringWithFormat:@"%@ %@.", (equip ? @"equipping" : @"unequipping"), good.name]));
    
    NSString* key = [StoreEncryptor encryptString:[KeyValDatabase keyGoodEquipped:good.itemId]];
    
    if (equip) {
        [[[StorageManager getInstance] kvDatabase] setVal:@"equipped" forKey:key];
        [EventHandling postGoodEquipped:good];
    } else {
        [[[StorageManager getInstance] kvDatabase] deleteKeyValWithKey:key];
        [EventHandling postGoodUnEquipped:good];
    }
}

- (NSString*)keyBalance:(NSString*)itemId {
    return [KeyValDatabase keyGoodBalance:itemId];
}

- (void)postBalanceChangeToItem:(VirtualItem*)item withBalance:(int)balance andAmountAdded:(int)amountAdded {
    [EventHandling postChangedBalance:balance forGood:(VirtualGood*)item withAmount:amountAdded];
}

@end
