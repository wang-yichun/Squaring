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

// Created by Fedor Shubin on 5/21/13.

#ifndef __CCStoreInventory_H_
#define __CCStoreInventory_H_

#include "cocos2d.h"
#include "CCSoomlaError.h"

namespace soomla {
	/** @class CCStoreInventory
		@brief An interface to the native StoreInventory class.

		An interface to the native StoreInventory class, use this class to
		access the native StoreInventory functionality.
	 */
    class CCStoreInventory: public cocos2d::CCObject {
    public:
		
        /**
         This class is singleton, use this function to access it.
		 */
        static CCStoreInventory* sharedStoreInventory();
      
        CCStoreInventory(void);
        virtual bool init();
    
        virtual ~CCStoreInventory(void);

		/**
         Buys the item with the given `itemId`.
         @param itemId The id of the item to be purchased.
         @param soomlaError A `CCSoomlaError` for error checking.
		 */
        void buyItem(const char *itemId, CCSoomlaError **soomlaError);

		/**
         Retrieves the balance of the virtual item with the given `itemId`.
         @param itemId The id of the virtual item to be fetched - must be of
         `CCVirtualCurrency`, `CCSingleUseVG`, `CCLifetimeVG`, `CCEquippableVG`.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return The balance of the virtual item with the given `itemId`.
		*/
        int getItemBalance(const char *itemId, CCSoomlaError **soomlaError);

		/**
         Gives your user the given amount of the virtual item with the given 
         `itemId`.
         For example, when your user plays your game for the first time you GIVE 
         him/her 1000 gems.
         NOTE: This action is different than `buy` -
         You use `give` to give your user something for free.
         You use `buy` to give your user something and get something in return.
         @param amount The amount of the item to be given.
         @param itemId The id of the virtual item to be given.
         @param soomlaError A `CCSoomlaError`for error checking.
         */
		void giveItem(const char *itemId, int amount, CCSoomlaError **soomlaError);

		/**
         Takes from your user the given amount of the virtual item with the 
         given `itemId`.
         For example, when you want to downgrade a virtual good, you take the 
         upgrade.
         @param amount The amount of the item to be given.
         @param itemId The id of the virtual item to be taken.
         @param soomlaError A `CCSoomlaError` for error checking.
         */
        void takeItem(const char *itemId, int amount, CCSoomlaError **soomlaError);

		/**
         Equips the virtual good with the given `goodItemId`.
         Equipping means that the user decides to currently use a specific 
         virtual good. For more details and examples see `CCEquippableVG`.
         @param itemId The id of the virtual good to be equipped. Id MUST
                be of a `CCEquippableVG`.
         @param soomlaError A `CCSoomlaError` for error checking.
		*/
        void equipVirtualGood(const char *itemId, CCSoomlaError **soomlaError);

		/**
         Unequips the virtual good with the given `goodItemId`. Unequipping 
         means that the user decides to stop using the virtual good he/she is 
         currently using. For more details and examples see `CCEquippableVG`.
         @param itemId The id of the virtual good to be unequipped. Id MUST
                be of a `CCEquippableVG`.
         @param soomlaError A `CCSoomlaError` for error checking.
         */
		void unEquipVirtualGood(const char *itemId, CCSoomlaError **soomlaError);

		/**
         Checks if the virtual good with the given `goodItemId` is equipped 
         (currently being used).
         @param itemId The id of the virtual good to check on. Id MUST be of
                an `EquippableVG`.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return True if the virtual good with the given id is equipped, false 
                otherwise.
         */
        bool isVirtualGoodEquipped(const char *itemId, CCSoomlaError **soomlaError);

		/**
         Retrieves the upgrade level of the virtual good with the given 
         `goodItemId`.
         For Example:
         Let's say there's a strength attribute to one of the characters in your 
         game and you provide your users with the ability to upgrade that 
         strength on a scale of 1-3.
         This is what you've created:
         1. `CCSingleUseVG` for "strength"
         2. `CCUpgradeVG` for strength 'level 1'
         3. `CCUpgradeVG` for strength 'level 2'
         4. `CCUpgradeVG` for strength 'level 3'
         In the example, this function will retrieve the upgrade level for 
         "strength" (1, 2, or 3).
         @param goodItemId The id of the virtual good whose upgrade level we 
                want to know. The `goodItemId` can be of any `CCVirtualGood`.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return The upgrade level.
         */
        int getGoodUpgradeLevel(const char *goodItemId, CCSoomlaError **soomlaError);

		/**
         Retrieves the item id of the current upgrade of the virtual good with
         the given `goodItemId`.
         @param goodItemId Id of the virtual good whose upgrade id we want to
                know. The `goodItemId` can be of any `CCVirtualGood`.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return The upgrade id if exists, or empty string otherwise.
         */
		std::string getGoodCurrentUpgrade(const char *goodItemId, CCSoomlaError **soomlaError); //TODO: return c string?

		/**
         Upgrades the virtual good with the given `goodItemId` by doing the 
         following:
         1. Checks if the good is currently upgraded or if this is the first 
         time being upgraded.
         2. If the good is currently upgraded, upgrades to the next upgrade in 
         the series, or in other words, buys the next upgrade. In case there
         are no more upgrades available (meaning the current upgrade is the last 
         available) the function returns.
         3. If the good has never been upgraded before, the function upgrades it 
         to the first available upgrade, or in other words, buy()s the first 
         upgrade in the series.
         @param goodItemId The id of the virtual good to be upgraded. The
                `upgradeItemId` can be of any `CCUpgradeVG`.
         @param soomlaError A `CCSoomlaError` for error checking.
         */
        void upgradeGood(const char *goodItemId, CCSoomlaError **soomlaError);

		/**
         Removes all upgrades from the virtual good with the given `goodItemId`.
         @param goodItemId The id of the virtual good we want to remove all 
                upgrades from. The `upgradeItemId` can be of any `UpgradeVG`.
         @param soomlaError A `CCSoomlaError` for error checking.
         */
		void removeGoodUpgrades(const char *goodItemId, CCSoomlaError **soomlaError);

		/**
         Checks if the item with the given `itemId` exists in 
         `nonConsumableStorage`.
         @param itemId The id of the item to check if exists.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return True if the item with the given id exists in
                `nonConsumableStorage`, false otherwise.
         */
        bool nonConsumableItemExists(const char *nonConsItemId, CCSoomlaError **soomlaError);

		/**
         Adds the non-consumable item with the given itemId to 
         `nonConsumableStorage`.
         @param itemId The id of the item to add to the storage.
         @param soomlaError A `CCSoomlaError` for error checking.
         */
        void addNonConsumableItem(const char *nonConsItemId, CCSoomlaError **soomlaError);

		/**
         Removes the non-consumable item with the given `itemId` from
         `nonConsumableStorage`.
         @param itemId The id of the item to remove from the storage.
         @param soomlaError A `CCSoomlaError` for error checking.
         */
        void removeNonConsumableItem(const char *nonConsItemId, CCSoomlaError **soomlaError);
    };
};

#endif //__CCStoreInventory_H_
