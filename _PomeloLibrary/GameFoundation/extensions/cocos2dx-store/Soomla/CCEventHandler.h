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

#ifndef __CCEventHandler__
#define __CCEventHandler__

#include "./domain/virtualCurrencies/CCVirtualCurrency.h"
#include "./domain/virtualGoods/CCVirtualGood.h"
#include "./domain/virtualGoods/CCEquippableVG.h"
#include "./domain/virtualGoods/CCUpgradeVG.h"

namespace soomla {
	/** 
     @class CCEventHandler
     @brief An abstract class that defines the event handler.
     
     Create your own implementation of this class and pass it to
     `CCSoomla::addEventHandler()` to work with the events. Functions are
     called when their corresponding events are fired in the SOOMLA SDK.
	 */
    class CCEventHandler : public cocos2d::CCObject {
    public:
        
        /**
         Handles an `onBillingNotSupported` event, which is fired when SOOMLA
         knows that billing is NOT supported on the device.
         */
        virtual void onBillingNotSupported() = 0;
        
        /**
         Handles an `onBillingSupported` event, which is fired when SOOMLA
         knows that billing IS supported on the device.
         */
        virtual void onBillingSupported() = 0;
        
        /**
         Handles an `onCurrencyBalanceChanged` event, which is fired when the
         balance of a specidifc virtual currency has changed.
         @param virtualCurrency The currency whose balance has changed.
         @param balance The balance of the currency.
         @param amountAdded The amount added to the currency.
         */
        virtual void onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded)  = 0;
        
        /**
         Handles an `onGoodBalanceChanged` event, which is fired when the
         balance of a specific virtual good has changed.
         @param virtualGood The good whose balance has changed.
         @param balance The balance of the good.
         @param amountAdded The amount added to the good.
         */
        virtual void onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded) = 0;
        
        /**
         Handles an `onGoodEquipped` event, which is fired when a specific
         equippable virtual good has been equipped.
         @param equippableVG The good that is being equipped.
         */
        virtual void onGoodEquipped(CCEquippableVG *equippableVG) = 0;
        
        /**
         Handles an `onGoodUnEquipped` event, which is fired when a specific
         equippable virtual good has been unequipped.
         @param equippableVG The good that is being unequipped.
         */
        virtual void onGoodUnEquipped(CCEquippableVG *equippableVG) = 0;
        
        /**
         Handles an `onGoodUpgrade` event, which is fired when a specific 
         virtual good has been upgraded.
         @param virtualGood The virtual good that is being upgraded.
         @param upgradeVG The upgrade.
         */
        virtual void onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG) = 0;
        
        /**
         Handles an `onItemPurchased` event, which is fired when when a specific
         virtual good has been purchased.
         @param purchasableVirtualItem The item being purchased.
         */
        virtual void onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
       
        /**
         Handles an `onItemPurchaseStarted` event, which is fired when a 
         purchase process has started.
         @param purchasableVirtualItem The item whose purchase has started.
         */
        virtual void onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        
        /**
         Handles an `onMarketPurchaseCancelled` event, which is fired when a 
         market (App Store, Google Play, etc..) purchase has been cancelled.
         @param purchasableVirtualItem the item whose purchase is being 
                cancelled.
         */
        virtual void onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;

        /**
         Handles an `onMarketPurchase` event, which is fired when a market item
         from the store (App Store, Google Play, etc..) has been purchased.
         @param purchasableVirtualItem The market item being purchased.
         @param receiptUrl Receipt URL from the store.
        */
        virtual void onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *token, cocos2d::CCString *payload) = 0;

        /**
         Handles an `onMarketPurchaseStarted` event, which is fired when a 
         purchase process has started, where the item is being purchased from
         the store (App Store, Google Play, etc..).
         @param purchasableVirtualItem The market item whose purchase has 
                started.
         */
        virtual void onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        
        /**
         Handles an `onMarketPurchaseVerification` event, which is fired when a
         market purchase verification process has started.
         @param purchasableVirtualItem The market item whose purchase is being 
                verified.
         */
        virtual void onMarketPurchaseVerification(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        
        /**
         Handles an `onRestoreTransactionsFinished` event, which is fired when a
         restore transactions process has finished.
         @param success Indicates if the restore transactions process finished 
                successfully.
         */
        virtual void onRestoreTransactionsFinished(bool success) = 0;
        
        /**
         Handles an `onRestoreTransactionsStarted` event, which is fired when a 
         restore transactions process has started.
         */
        virtual void onRestoreTransactionsStarted() = 0;
        
        /**
         Handles an `onUnexpectedErrorInStore` event, which is fired when an 
         unexpected error occurs in the store.
         */
        virtual void onUnexpectedErrorInStore() = 0;
		
        /**
         Handles an `onStoreControllerInitialized` event, which is fired when 
         store controller is initialized.
         */
        virtual void onStoreControllerInitialized() = 0;
        
        /**
         Handles an `onMarketItemsRefreshed` event, which is fired when a market
         item refreshed process has started.
         */
        virtual void onMarketItemsRefreshed() = 0;

/** Android only events*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        /**
         Handles an `onMarketRefund` event, which is fired when a market item is
         being refunded.
         @param purchasableVirtualItem The item that is being refunded in the 
                market.
         */
        virtual void onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
		
        /**
         Handles an `onIabServiceStarted` event, which is fired when in-app
         billing service is started.
         */
        virtual void onIabServiceStarted() = 0;
		
        /**
         Handles an `onIabServiceStopped` event, which is fired when in-app
         billing service is stopped.
         */
        virtual void onIabServiceStopped() = 0;
#endif
    };
};

#endif /* defined(__CCEventHandler__) */
