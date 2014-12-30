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
#import "VirtualItemStorage.h"

@class VirtualGood;
@class UpgradeVG;
@class EquippableVG;

/**
 This class provides basic storage operations on Virtual Goods.
 */
@interface VirtualGoodStorage : VirtualItemStorage

- (id)init;

/**
 Removes any upgrade associated with the given `VirtualGood`.
 
 @param good The `VirtualGood` to remove the upgrade from.
 */
- (void)removeUpgradesFrom:(VirtualGood*)good;
- (void)removeUpgradesFrom:(VirtualGood*)good withEvent:(BOOL)notify;

/**
 Assigns a specific upgrade to the given `VirtualGood`.
 
 @param upgradeVG The upgrade to assign.
 @param good The `VirtualGood` to upgrade.
 */
- (void)assignCurrentUpgrade:(UpgradeVG*)upgradeVG toGood:(VirtualGood*)good;
- (void)assignCurrentUpgrade:(UpgradeVG*)upgradeVG toGood:(VirtualGood*)good withEvent:(BOOL)notify;

/**
 Retrieves the current upgrade for the given `VirtualGood`.
 
 @param good The `VirtualGood` to retrieve the upgrade for.
 */
- (UpgradeVG*)currentUpgradeOf:(VirtualGood*)good;

/**
 Checks the equipping status of the given `EquippableVG`.
 
 @param good The `EquippableVG` to check the status for.
 */
- (BOOL)isGoodEquipped:(EquippableVG*)good;

/**
 Equips the given `EquippableVG`.
 
 @param good The `EquippableVG` to equip.
 */
- (void)equipGood:(EquippableVG*)good;
- (void)equipGood:(EquippableVG*)good withEvent:(BOOL)notify;

/**
 UnEquips the given `EquippableVG`.
 
 @param good The `EquippableVG` to unequip.
 */
- (void)unequipGood:(EquippableVG*)good;
- (void)unequipGood:(EquippableVG*)good withEvent:(BOOL)notify;

@end
