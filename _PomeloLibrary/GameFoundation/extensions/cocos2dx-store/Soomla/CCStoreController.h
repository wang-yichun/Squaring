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

#ifndef __CCStoreController_H_
#define __CCStoreController_H_

#include "cocos2d.h"
#include "CCIStoreAssets.h"
#include "CCSoomlaError.h"

namespace soomla {
	/** 
     @class CCStoreController
     @brief An interface to the native StoreController class.
     
     An interface to the native StoreController class, use this class to
     access the native StoreController functionality. This class holds the most 
     basic assets needed to operate the Store.
	 */
    class CCStoreController: public cocos2d::CCObject {
        CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mSoomSec, SoomSec);
    public:
        
		/**
         This class is singleton, use this function to access it.
		*/
        static CCStoreController* sharedStoreController();

		/**
         Initializes StoreController on native side and allows using its
         functions.
         @param storeAssets An instance of your store's assets class.
         @param storeParams A CCDictionary containing parameters for 
                CCStoreController (These were previously found in CCSoomla).
                This dictionary can contain the following:
                "soomSec": CCString - The value of the primary encryption key.
                "customSecret": CCString - The value of the secondary encryption 
                    key.
                "androidPublicKey": CCString - Your Android public key.
                "SSV": CCBool - Whether or not to enable server side 
                    verification of purchases.
		 */
        static void initShared(CCIStoreAssets *storeAssets, cocos2d::CCDictionary *storeParams);

        CCStoreController(void);
        virtual bool init(CCIStoreAssets *storeAssets, cocos2d::CCDictionary *storeParams);
       
        virtual ~CCStoreController(void);

        virtual void setupSoomSec();

		/**
         Starts an in app purchase process in the market (App Store, Google 
         Play, etc...).
         @param productId The product ID of the item in the market (App Store, 
                Google Play, etc..).
         @param soomlaError A CCSoomlaError for error checking.
		 */
        void buyMarketItem(const char *productId, const char *payload, CCSoomlaError **soomlaError);

		/**
         Restores this user's previous transactions.
		 */
        void restoreTransactions();

        /**
         Creates a list of all metadata stored in the Market (the items that 
         have been purchased). The metadata includes the item's name, 
         description, price, product id, etc..
         */
        void refreshInventory();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        
		/**
         Checks if the user has already restored his/her transactions.
         @return Whether or not the user restored his/her transactions.
		*/		
        bool transactionsAlreadyRestored();
        
        /**
         Refreshes the details of all market-purchasable items that were defined 
         in the market (App Store, Google Play, etc..).
         */
        void refreshMarketItemsDetails(CCSoomlaError **soomlaError);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        /**
         Starts the in-app billing service in background.
         */
		void startIabServiceInBg();
        
        /**
         Stops the in-app billing service in background.
         */
		void stopIabServiceInBg();
#endif
    };
};

#endif // !__CCStoreController_H_
