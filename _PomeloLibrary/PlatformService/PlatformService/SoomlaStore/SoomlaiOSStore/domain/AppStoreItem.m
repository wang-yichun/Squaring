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

#import "AppStoreItem.h"
#import "JSONConsts.h"

@implementation AppStoreItem

@synthesize price, productId, consumable;

- (id)initWithProductId:(NSString*)oProductId andConsumable:(Consumable)oConsumable andPrice:(double)oPrice{
    self = [super init];
    if (self){
        self.productId = oProductId;
        self.consumable = oConsumable;
        self.price = oPrice;
    }
    
    return self;
}

- (id)initWithDictionary:(NSDictionary*)dict{
    self = [super init];
    if (self) {
        self.consumable = [[dict valueForKey:JSON_MARKETITEM_CONSUMABLE] intValue];
        self.productId = [dict objectForKey:JSON_MARKETITEM_PRODUCT_ID];
        self.price = [[dict valueForKey:JSON_MARKETITEM_PRICE] doubleValue];
    }
    
    return self;
}

- (NSDictionary*)toDictionary{
    return [[NSDictionary alloc] initWithObjectsAndKeys:
            [NSNumber numberWithInt:self.consumable], JSON_MARKETITEM_CONSUMABLE,
            self.productId, JSON_MARKETITEM_PRODUCT_ID,
            [NSNumber numberWithDouble:self.price], JSON_MARKETITEM_PRICE,
            nil];
}

@end
