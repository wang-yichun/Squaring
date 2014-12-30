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

#import "StoreInfo.h"
#import "StorageManager.h"
#import "KeyValDatabase.h"
#import "JSONConsts.h"
#import "VirtualCategory.h"
#import "VirtualGood.h"
#import "VirtualCurrency.h"
#import "VirtualCurrencyPack.h"
#import "NonConsumableItem.h"
#import "VirtualItemNotFoundException.h"
#import "MarketItem.h"
#import "ObscuredNSUserDefaults.h"
#import "StoreUtils.h"
#import "PurchaseType.h"
#import "PurchaseWithMarket.h"
#import "PurchaseWithVirtualItem.h"
#import "SingleUseVG.h"
#import "LifetimeVG.h"
#import "EquippableVG.h"
#import "SingleUsePackVG.h"
#import "UpgradeVG.h"
#import "KeyValueStorage.h"

@implementation StoreInfo

@synthesize virtualCategories, virtualCurrencies, virtualCurrencyPacks, virtualGoods, nonConsumableItems, virtualItems, purchasableItems, goodsCategories, goodsUpgrades;

static NSString* TAG = @"SOOMLA StoreInfo";

+ (StoreInfo*)getInstance{
    static StoreInfo* _instance = nil;
    
    @synchronized( self ) {
        if( _instance == nil ) {
            _instance = [[StoreInfo alloc ] init];
        }
    }
    
    return _instance;
}

- (void)checkAndAddPurchasable:(PurchasableVirtualItem*)pvi {
    PurchaseType* purchaseType = pvi.purchaseType;
    if ([purchaseType isKindOfClass:[PurchaseWithMarket class]]) {
        [self.purchasableItems setObject:pvi forKey:((PurchaseWithMarket*) purchaseType).marketItem.productId];
    }
}

- (void)addVirtualGood:(VirtualGood*)good {
    [self.virtualGoods addObject:good];
    
    [self.virtualItems setObject:good forKey:good.itemId];
    
    [self checkAndAddPurchasable:good];
}

- (void) save {
    // put StoreInfo in the database as JSON
    NSString* storeInfoJSON = [StoreUtils dictToJsonString:[self toDictionary]];
    NSString* ec = [[NSString alloc] initWithData:[storeInfoJSON dataUsingEncoding:NSUTF8StringEncoding] encoding:NSUTF8StringEncoding];
    [[[StorageManager getInstance] keyValueStorage] setValue:ec forKey:[KeyValDatabase keyMetaStoreInfo]];
}

- (void)save:(VirtualItem*)virtualItem {
    [self replaceVirtualItem:virtualItem];
    [self save];
}

- (void)replaceVirtualItem:(VirtualItem*)virtualItem {
    [self.virtualItems setObject:virtualItem forKey:virtualItem.itemId];
    
    if ([virtualItem isKindOfClass:[VirtualCurrency class]]) {
        for(int i=0; i<[self.virtualCurrencies count]; i++) {
            if ([((VirtualCurrency*)[self.virtualCurrencies objectAtIndex:i]).itemId isEqualToString:virtualItem.itemId]) {
                [self.virtualCurrencies removeObjectAtIndex:i];
                break;
            }
        }
        [self.virtualCurrencies addObject:virtualItem];
    }
    
    if ([virtualItem isKindOfClass:[VirtualCurrencyPack class]]) {

        [self checkAndAddPurchasable:(VirtualCurrencyPack*)virtualItem];
        
        for(int i=0; i<[self.virtualCurrencyPacks count]; i++) {
            if ([((VirtualCurrencyPack*)[self.virtualCurrencyPacks objectAtIndex:i]).itemId isEqualToString:virtualItem.itemId]) {
                [self.virtualCurrencyPacks removeObjectAtIndex:i];
                break;
            }
        }
        [self.virtualCurrencyPacks addObject:virtualItem];
        
    }
    
    if ([virtualItem isKindOfClass:[VirtualGood class]]) {
        
        if ([virtualItem isKindOfClass:[UpgradeVG class]]) {
            NSMutableArray* upgrades = [self.goodsUpgrades objectForKey:((UpgradeVG*)virtualItem).goodItemId];
            if (!upgrades) {
                upgrades = [NSMutableArray array];
                [self.goodsUpgrades setObject:upgrades forKey:((UpgradeVG*)virtualItem).goodItemId];
            }
            [upgrades addObject:virtualItem];
        }
        
        [self checkAndAddPurchasable:(VirtualGood*)virtualItem];
        
        for(int i=0; i<[self.virtualGoods count]; i++) {
            if ([((VirtualGood*)[self.virtualGoods objectAtIndex:i]).itemId isEqualToString:virtualItem.itemId]) {
                [self.virtualGoods removeObjectAtIndex:i];
                break;
            }
        }
        [self.virtualGoods addObject:virtualItem];
    }
    
    if ([virtualItem isKindOfClass:[NonConsumableItem class]]) {
        
        [self checkAndAddPurchasable:(NonConsumableItem*)virtualItem];
        
        for(int i=0; i<[self.nonConsumableItems count]; i++) {
            if ([((VirtualGood*)[self.nonConsumableItems objectAtIndex:i]).itemId isEqualToString:virtualItem.itemId]) {
                [self.nonConsumableItems removeObjectAtIndex:i];
                break;
            }
        }
        [self.nonConsumableItems addObject:virtualItem];
        
    }
}

- (void)privInitializeWithIStoreAssets:(id)storeAssets {
    LogDebug(TAG, @"Initializing StoreInfo with a given store assets.");
    
    self.virtualGoods = [NSMutableArray arrayWithArray:[storeAssets virtualGoods]];
    self.virtualCurrencies = [NSMutableArray arrayWithArray:[storeAssets virtualCurrencies]];
    self.virtualCurrencyPacks = [NSMutableArray arrayWithArray:[storeAssets virtualCurrencyPacks]];
    self.virtualCategories = [NSMutableArray arrayWithArray:[storeAssets virtualCategories]];
    self.nonConsumableItems = [NSMutableArray arrayWithArray:[storeAssets nonConsumableItems]];
    
    self.virtualItems = [NSMutableDictionary dictionary];
    self.purchasableItems = [NSMutableDictionary dictionary];
    self.goodsCategories = [NSMutableDictionary dictionary];
    self.goodsUpgrades = [NSMutableDictionary dictionary];
    
    for(VirtualCurrency* vi in self.virtualCurrencies) {
        [self.virtualItems setObject:vi forKey:vi.itemId];
    }
    
    for(VirtualCurrencyPack* vi in self.virtualCurrencyPacks) {
        [self.virtualItems setObject:vi forKey:vi.itemId];
        
        [self checkAndAddPurchasable:vi];
    }
    
    for(VirtualGood* vi in self.virtualGoods) {
        [self.virtualItems setObject:vi forKey:vi.itemId];
        
        if ([vi isKindOfClass:[UpgradeVG class]]) {
            NSMutableArray* upgrades = [self.goodsUpgrades objectForKey:((UpgradeVG*)vi).goodItemId];
            if (!upgrades) {
                upgrades = [NSMutableArray array];
                [self.goodsUpgrades setObject:upgrades forKey:((UpgradeVG*)vi).goodItemId];
            }
            [upgrades addObject:vi];
        }
        
        [self checkAndAddPurchasable:vi];
    }
    
    for(NonConsumableItem* vi in self.nonConsumableItems) {
        [self.virtualItems setObject:vi forKey:vi.itemId];
        
        [self checkAndAddPurchasable:vi];
    }
    
    for(VirtualCategory* category in self.virtualCategories) {
        for(NSString* goodItemId in category.goodsItemIds) {
            [self.goodsCategories setObject:category forKey:goodItemId];
        }
    }
    
    [self save];
}

- (void)initializeWithIStoreAssets:(id <IStoreAssets>)storeAssets{
    if(storeAssets == NULL){
        LogError(TAG, @"The given store assets can't be null !");
        return;
    }
    
    // we prefer initialization from the database (storeAssets are only set on the first time the game is loaded)!
    if (![self initializeFromDB]){
        [self privInitializeWithIStoreAssets:storeAssets];
    }
}

- (BOOL)initializeFromDB{
    NSString* storeInfoJSON = [[[StorageManager getInstance] keyValueStorage] getValueForKey:[KeyValDatabase keyMetaStoreInfo]];
    
    if(!storeInfoJSON || [storeInfoJSON length] == 0){
        LogDebug(TAG, @"store json is not in DB yet.")
        return NO;
    }
    
    LogDebug(TAG, ([NSString stringWithFormat:@"the metadata-economy json (from DB) is %@", storeInfoJSON]));
    
    @try {
        
        NSDictionary* storeInfo = [StoreUtils jsonStringToDict:storeInfoJSON];
        
        self.virtualItems = [NSMutableDictionary dictionary];
        self.purchasableItems = [NSMutableDictionary dictionary];
        self.goodsCategories = [NSMutableDictionary dictionary];
        self.goodsUpgrades = [NSMutableDictionary dictionary];
        
        self.virtualCurrencies = [[NSMutableArray alloc] init];
        NSArray* currenciesDicts = [storeInfo objectForKey:JSON_STORE_CURRENCIES];
        for(NSDictionary* currencyDict in currenciesDicts){
            VirtualCurrency* o = [[VirtualCurrency alloc] initWithDictionary: currencyDict];
            [self.virtualCurrencies addObject:o];
            
            [self.virtualItems setObject:o forKey:o.itemId];
        }
        
        self.virtualCurrencyPacks = [[NSMutableArray alloc] init];
        NSArray* currencyPacksDicts = [storeInfo objectForKey:JSON_STORE_CURRENCYPACKS];
        for(NSDictionary* currencyPackDict in currencyPacksDicts){
            VirtualCurrencyPack* o = [[VirtualCurrencyPack alloc] initWithDictionary: currencyPackDict];
            [self.virtualCurrencyPacks addObject:o];
            
            [self.virtualItems setObject:o forKey:o.itemId];
            
            [self checkAndAddPurchasable:o];
        }
        
        
        NSDictionary* goodsDict = [storeInfo objectForKey:JSON_STORE_GOODS];
        NSArray* suGoods = [goodsDict objectForKey:JSON_STORE_GOODS_SU];
        NSArray* ltGoods = [goodsDict objectForKey:JSON_STORE_GOODS_LT];
        NSArray* eqGoods = [goodsDict objectForKey:JSON_STORE_GOODS_EQ];
        NSArray* upGoods = [goodsDict objectForKey:JSON_STORE_GOODS_UP];
        NSArray* paGoods = [goodsDict objectForKey:JSON_STORE_GOODS_PA];
        self.virtualGoods = [[NSMutableArray alloc] init];
        for(NSDictionary* gDict in suGoods){
            SingleUseVG* g = [[SingleUseVG alloc] initWithDictionary: gDict];
            [self addVirtualGood:g];
        }
        for(NSDictionary* gDict in ltGoods){
            LifetimeVG* g = [[LifetimeVG alloc] initWithDictionary: gDict];
            [self addVirtualGood:g];
        }
        for(NSDictionary* gDict in eqGoods){
            EquippableVG* g = [[EquippableVG alloc] initWithDictionary: gDict];
            [self addVirtualGood:g];
        }
        for(NSDictionary* gDict in upGoods){
            UpgradeVG* g = [[UpgradeVG alloc] initWithDictionary: gDict];
            
            NSMutableArray* upgrades = [self.goodsUpgrades objectForKey:g.goodItemId];
            if (!upgrades) {
                upgrades = [NSMutableArray array];
                [self.goodsUpgrades setObject:upgrades forKey:g.goodItemId];
            }
            [upgrades addObject:g];
            
            [self addVirtualGood:g];
        }
        for(NSDictionary* gDict in paGoods){
            SingleUsePackVG* g = [[SingleUsePackVG alloc] initWithDictionary: gDict];
            [self addVirtualGood:g];
        }
        
        self.virtualCategories = [[NSMutableArray alloc] init];
        NSArray* categoriesDicts = [storeInfo objectForKey:JSON_STORE_CATEGORIES];
        for(NSDictionary* categoryDict in categoriesDicts){
            VirtualCategory* c = [[VirtualCategory alloc] initWithDictionary: categoryDict];
            [self.virtualCategories addObject:c];
            
            for(NSString* goodItemId in c.goodsItemIds) {
                [self.goodsCategories setObject:c forKey:goodItemId];
            }
        }
        
        self.nonConsumableItems = [[NSMutableArray alloc] init];
        NSArray* nonConsumableItemsDict = [storeInfo objectForKey:JSON_STORE_NONCONSUMABLES];
        for(NSDictionary* nonConsumableItemDict in nonConsumableItemsDict){
            NonConsumableItem* non = [[NonConsumableItem alloc] initWithDictionary:nonConsumableItemDict];
            [self.nonConsumableItems addObject:non];
            
            [self.virtualItems setObject:non forKey:non.itemId];
            
            [self checkAndAddPurchasable:non];
        }
        
        // everything went well... StoreInfo is initialized from the local DB.
        // it's ok to return now.
        
        return YES;
    } @catch (NSException* ex) {
        LogError(TAG, @"An error occured while trying to parse store info JSON.");
    }
    
    return NO;
}

- (NSDictionary*)toDictionary{
    
    NSMutableArray* currencies = [NSMutableArray array];
    for(VirtualCurrency* c in self.virtualCurrencies){
        [currencies addObject:[c toDictionary]];
    }
    
    NSMutableArray* packs = [NSMutableArray array];
    for(VirtualCurrencyPack* c in self.virtualCurrencyPacks){
        [packs addObject:[c toDictionary]];
    }
    
    NSMutableArray* suGoods = [NSMutableArray array];
    NSMutableArray* ltGoods = [NSMutableArray array];
    NSMutableArray* eqGoods = [NSMutableArray array];
    NSMutableArray* upGoods = [NSMutableArray array];
    NSMutableArray* paGoods = [NSMutableArray array];
    for(VirtualGood* g in self.virtualGoods){
        if ([g isKindOfClass:[SingleUseVG class]]) {
            [suGoods addObject:[g toDictionary]];
        } else if ([g isKindOfClass:[UpgradeVG class]]) {
            [upGoods addObject:[g toDictionary]];
        } else if ([g isKindOfClass:[EquippableVG class]]) {
            [eqGoods addObject:[g toDictionary]];
        } else if ([g isKindOfClass:[SingleUsePackVG class]]) {
            [paGoods addObject:[g toDictionary]];
        } else if ([g isKindOfClass:[LifetimeVG class]]) {
            [ltGoods addObject:[g toDictionary]];
        }
    }
    NSDictionary* goods = [NSDictionary dictionaryWithObjectsAndKeys:
                           suGoods, JSON_STORE_GOODS_SU,
                           ltGoods, JSON_STORE_GOODS_LT,
                           eqGoods, JSON_STORE_GOODS_EQ,
                           upGoods, JSON_STORE_GOODS_UP,
                           paGoods, JSON_STORE_GOODS_PA, nil];
    
    NSMutableArray* categories = [NSMutableArray array];
    for(VirtualCategory* c in self.virtualCategories){
        [categories addObject:[c toDictionary]];
    }
    
    NSMutableArray* nonConsumables = [NSMutableArray array];
    for(NonConsumableItem* non in self.nonConsumableItems) {
        [nonConsumables addObject:[non toDictionary]];
    }
    
    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
    
    [dict setObject:categories forKey:JSON_STORE_CATEGORIES];
    [dict setObject:currencies forKey:JSON_STORE_CURRENCIES];
    [dict setObject:packs forKey:JSON_STORE_CURRENCYPACKS];
    [dict setObject:goods forKey:JSON_STORE_GOODS];
    [dict setObject:nonConsumables forKey:JSON_STORE_NONCONSUMABLES];
    
    return dict;
}

- (VirtualItem*)virtualItemWithId:(NSString*)itemId {
    VirtualItem* vi = [self.virtualItems objectForKey:itemId];
    if (!vi) {
        @throw [[VirtualItemNotFoundException alloc] initWithLookupField:@"itemId" andLookupValue:itemId];
    }
    
    return vi;
}

- (NSArray*)allProductIds {
    NSMutableArray* array = [NSMutableArray array];
    
    for(PurchasableVirtualItem* pvi in purchasableItems) {
        [array addObject:pvi];
    }
    return array;
}

- (PurchasableVirtualItem*)purchasableItemWithProductId:(NSString*)productId {
    PurchasableVirtualItem* pvi = [self.purchasableItems objectForKey:productId];
    if (!pvi) {
        @throw [[VirtualItemNotFoundException alloc] initWithLookupField:@"productId" andLookupValue:productId];
    }
    
    return pvi;
}

- (VirtualCategory*)categoryForGoodWithItemId:(NSString*)goodItemId {
    VirtualCategory* cat = [self.goodsCategories objectForKey:goodItemId];
    
    if (!cat) {
        @throw [[VirtualItemNotFoundException alloc] initWithLookupField:@"goodItemId" andLookupValue:goodItemId];
    }
    
    return cat;
}

- (UpgradeVG*)firstUpgradeForGoodWithItemId:(NSString*)goodItemId {
    NSArray* upgrades = [self.goodsUpgrades objectForKey:goodItemId];
    if (upgrades) {
        for(UpgradeVG* upgradeVG in upgrades) {
            if ((!upgradeVG.prevGoodItemId) ||
                (upgradeVG.prevGoodItemId.length == 0)) {
                return upgradeVG;
            }
        }
    }
    
    return NULL;
}

- (UpgradeVG*)lastUpgradeForGoodWithItemId:(NSString*)goodItemId {
    NSArray* upgrades = [self.goodsUpgrades objectForKey:goodItemId];
    if (upgrades) {
        for(UpgradeVG* upgradeVG in upgrades) {
            if ((!upgradeVG.nextGoodItemId) ||
                (upgradeVG.nextGoodItemId.length == 0)) {
                return upgradeVG;
            }
        }
    }
    
    return NULL;
}

- (NSArray*)upgradesForGoodWithItemId:(NSString*)goodItemId {
    return [self.goodsUpgrades objectForKey:goodItemId];
}

- (BOOL)goodHasUpgrades:(NSString*)goodItemId {
    return [goodsUpgrades objectForKey:goodItemId] != NULL;
}

@end
