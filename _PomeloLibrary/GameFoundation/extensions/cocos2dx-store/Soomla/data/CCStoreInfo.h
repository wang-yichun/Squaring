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

#ifndef __CCStoreInfo_H_
#define __CCStoreInfo_H_

#include "cocos2d.h"
#include "../CCSoomlaError.h"
#include "../CCIStoreAssets.h"
#include "../domain/CCVirtualItem.h"
#include "../domain/virtualGoods/CCUpgradeVG.h"
#include "../domain/CCVirtualCategory.h"

namespace soomla {
	/** 
     @class CCStoreInfo
     @brief An interface to the native `StoreInfo` class.
     
     This class holds the store's metadata including:
     virtual currencies,
     virtual currency packs,
     all virtual goods,
     virtual categories, and
     non-consumables
	*/
	class CCStoreInfo: cocos2d::CCObject {
    public:
        
		/**
         This class is a singleton, use this function to access it.
		*/
        static CCStoreInfo *sharedStoreInfo();
        
        /**
         Initializes `CCStoreInfo` on native side and allows using its
         functions.
         @param storeAssets An instance of your store's assets class.
		 */
        static void createShared(CCIStoreAssets *storeAssets);
        virtual bool init(CCIStoreAssets *storeAssets);

		/**
         Retrieves a single `CCVirtualItem` that resides in the metadata.
         @param itemId The item id of the item to be fetched.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return The virtual item with the given `itemId`.
		 */
        CCVirtualItem *getItemByItemId(const char *itemId, CCSoomlaError **soomlaError);

		/**
         Retrieves a single `CCPurchasableVirtualItem` that resides in the
         metadata.
         IMPORTANT: The retrieved `CCPurchasableVirtualItem` has a purchaseType 
         of `CCPurchaseWithMarket`. This is why we fetch here with `productId` 
         and not with `itemId` (`productId` is the id of the product in the App
         Store).
         @param productId The product id of the item to be fetched.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return The purchasable virtual item with the given `productId`.
		*/
		CCPurchasableVirtualItem *getPurchasableItemWithProductId(const char *productId, CCSoomlaError **soomlaError);

		/**
         Retrieves the `CCVirtualCategory` that the `CCVirtualGood` with the 
         given `goodItemId` belongs to.
         @param goodItemId The item id of the virtual good whose category is 
                being retrieved.
         @param soomlaError A `CCSoomlaError` for error checking.
         @return The `CCVirtualCategory` for the `CCVirtualGood` with the given
         `goodItemId`.
		*/
		CCVirtualCategory *getCategoryForVirtualGood(const char *goodItemId, CCSoomlaError **soomlaError);

		/**
         Retrieves the first `CCUpgradeVG` for the`CCVirtualGood` with the given
         `itemId`.
         @param goodItemId The `CCVirtualGood` whose upgrade is being retrieved.
         @return The first `CCUpgradeVG` for the virtual good with the given
                `itemId`.
		*/
        CCUpgradeVG *getFirstUpgradeForVirtualGood(const char *goodItemId);

		/**
         Retrieves the last `CCUpgradeVG` for the`CCVirtualGood` with the given
         `itemId`.
         @param goodItemId the `CCVirtualGood` we're searching the upgrade for.
         @return The last `CCUpgradeVG` for the virtual good with the given
                `ItemId`.
		*/
		CCUpgradeVG *getLastUpgradeForVirtualGood(const char *goodItemId);

		/**
         Retrieves all `CCUpgradeVG`s for the `CCVirtualGood` with the given
         `itemId`.
         @param goodItemId the `CCVirtualGood` we're searching the upgrades for.
         @return Array of all upgrades for the good with the given item id.
         */
        cocos2d::CCArray *getUpgradesForVirtualGood(const char *goodItemId);

		/**
         Retrieves all virtual currencies.
         @return The virtual currencies of the game.
		*/
		cocos2d::CCArray *getVirtualCurrencies();

		/**
         Retrieves all virtual goods.
         @return The virtual goods of the game.
		*/
        cocos2d::CCArray *getVirtualGoods();

		/**
         Retrieves all virtual currency packs.
         @return The virtual currency packs of the game.
		*/
        cocos2d::CCArray *getVirtualCurrencyPacks();

		/**
         Retrieves all non consumable items.
         @return The non consumable items of the game.
		*/
        cocos2d::CCArray *getNonConsumableItems();

		/**
         Retrieves all virtual categories.
         @return The virtual categories of the game.
		*/
		cocos2d::CCArray *getVirtualCategories();
        
    private:
        cocos2d::CCObject *createWithRetParams(cocos2d::CCDictionary *retParams);
    };
};

#endif //__CCStoreInfo_H_
