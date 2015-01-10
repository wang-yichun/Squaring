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

/**
 Every item offered in the App Store has one of the five following purchase 
 types.
 */
typedef enum {
    kConsumable = 1,
    kNonConsumable = 2,
    kAutoRenewableSubscription = 3,
    kNonRenewableSubscription = 4,
    kFreeSubscription = 5
} Consumable;

/**
 This class represents an item in the App Store.
 Every `PurchasableVirtualItem` with `PurchaseType` of `PurchaseWithMarket`
 has an instance of this class.
 */
@interface MarketItem : NSObject{
    NSString* productId;
    Consumable      consumable;
    double          price;

    NSDecimalNumber *marketPrice;
    NSLocale        *marketLocale;
    NSString        *marketTitle;
    NSString        *marketDescription;
}

@property (nonatomic, retain) NSString* productId;
@property Consumable      consumable;
@property double          price;
@property (nonatomic, retain) NSDecimalNumber *marketPrice;
@property (nonatomic, retain) NSLocale        *marketLocale;
@property (nonatomic, retain) NSString        *marketTitle;
@property (nonatomic, retain) NSString        *marketDescription;

/** 
 Constructor
 
 @param oProductId The id of this `MarketItem` in the App Store.
 @param oConsumable The type of this `MarketItem` item in the App Store.
 @param oPrice The actual $$ cost of this `MarketItem` item in the App Store.
 */
- (id)initWithProductId:(NSString*)oProductId andConsumable:(Consumable)oConsumable andPrice:(double)oPrice;

/**
 Constructor
 
 @param dict An `NSDictionary` representation of the `MarketItem.`
 */
- (id)initWithDictionary:(NSDictionary*)dict;

/**
 Converts the current `MarketItem` to an `NSDictionary`.
 
 @return This instance of `MarketItem` as an `NSDictionary`.
 */
- (NSDictionary*)toDictionary;

/**
 Retrieves the price of `MarketItem` with its currency symbol.
 
 @return The price of this `MarketItem`.
 */
- (NSString*)priceWithCurrencySymbol;


@end
