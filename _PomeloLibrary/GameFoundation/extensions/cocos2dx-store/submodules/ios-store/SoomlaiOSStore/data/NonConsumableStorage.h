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

#import <Foundation/Foundation.h>

@class NonConsumableItem;

/**
 This class provides basic storage operations on the App Store's
 Non-Consumable items.
 */
@interface NonConsumableStorage : NSObject

/**
 Determines if the given Non-Consumable item exists.
 
 @param nonConsumableItem The Non-Consumable item to check if exists.
 @return YES if exists, NO otherwise.
 */
- (BOOL)nonConsumableExists:(NonConsumableItem*)nonConsumableItem;

/**
 Adds the given App Store Non-Consumable item to the storage.
 
 @param nonConsumableItem The Non-Consumable item to add to the storage.
 @return 1
 */
- (BOOL)add:(NonConsumableItem*)nonConsumableItem;

/**
 Removes the given App Store Non-Consumable item from the storage.
 
 @param nonConsumableItem The Non-Consumable item to remove from the storage.
 @return 0
 */
- (BOOL)remove:(NonConsumableItem*)nonConsumableItem;

@end
