//
//  cocos2dx_EventDispatcher.m
//  Trying
//
//  Created by Refael Dakar on 12/03/13.
//
//

#include <iostream>
#include <string>
#import "cocos2dx_EventDispatcher.h"
#import "EventHandling.h"
#import "cocos2dx_EventHandlers.h"
#import "VirtualCurrencyPack.h"
#import "AppStoreItem.h"
#import "VirtualGood.h"
#import "VirtualCurrency.h"
#import "UpgradeVG.h"
#import "EquippableVG.h"
#import "PurchasableVirtualItem.h"

@implementation cocos2dx_EventDispatcher


+ (void)initialize {
    static cocos2dx_EventDispatcher* instance = nil;
    
    if (!instance) {
        instance = [[cocos2dx_EventDispatcher alloc] init];
    }
}

- (id) init {
    if (self = [super init]) {
        [EventHandling observeAllEventsWithObserver:self withSelector:@selector(eventFired:)];
    }
    
    return self;
}

- (void)eventFired:(NSNotification*)notification{
    if ([notification.name isEqualToString:EVENT_BILLING_SUPPORTED]) {
        cocos2dx_EventHandlers::getInstance()->billingSupported();
    }
    else if ([notification.name isEqualToString:EVENT_BILLING_NOT_SUPPORTED]) {
        cocos2dx_EventHandlers::getInstance()->billingNotSupported();
    }
    else if ([notification.name isEqualToString:EVENT_CLOSING_STORE]) {
        cocos2dx_EventHandlers::getInstance()->closingStore();
    }
    else if ([notification.name isEqualToString:EVENT_CURRENCY_BALANCE_CHANGED]) {
		int balance = [(NSNumber*)[notification.userInfo objectForKey:DICT_ELEMENT_BALANCE] intValue];
        int amountAdded = [(NSNumber*)[notification.userInfo objectForKey:DICT_ELEMENT_AMOUNT_ADDED] intValue];
		VirtualCurrency* currency = (VirtualCurrency*)[notification.userInfo objectForKey:DICT_ELEMENT_CURRENCY];
		string itemId([currency.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->currencyBalanceChanged(itemId, balance, amountAdded);
    }
    else if ([notification.name isEqualToString:EVENT_GOOD_BALANCE_CHANGED]) {
		int balance = [(NSNumber*)[notification.userInfo objectForKey:EVENT_CURRENCY_BALANCE_CHANGED] intValue];
        int amountAdded = [(NSNumber*)[notification.userInfo objectForKey:DICT_ELEMENT_AMOUNT_ADDED] intValue];
		VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:DICT_ELEMENT_GOOD];
		string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->goodBalanceChanged(itemId, balance, amountAdded);
    }
    else if ([notification.name isEqualToString:EVENT_GOOD_EQUIPPED]) {
        EquippableVG* good = (EquippableVG*)[notification.userInfo objectForKey:DICT_ELEMENT_EquippableVG];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->goodEquipped(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_GOOD_UNEQUIPPED]) {
        EquippableVG* good = (EquippableVG*)[notification.userInfo objectForKey:DICT_ELEMENT_EquippableVG];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->goodUnequipped(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_GOOD_UPGRADE]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:DICT_ELEMENT_GOOD];
        UpgradeVG* vgu = (UpgradeVG*)[notification.userInfo objectForKey:DICT_ELEMENT_UpgradeVG];
        string itemId([good.itemId UTF8String]);
        string vguItemId([vgu.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->goodUpgrade(itemId, vguItemId);
    }
    else if ([notification.name isEqualToString:EVENT_ITEM_PURCHASED]) {
        PurchasableVirtualItem* pvi = (PurchasableVirtualItem*)[notification.userInfo objectForKey:DICT_ELEMENT_PURCHASABLE];
        string itemId([pvi.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->itemPurchased(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_ITEM_PURCHASE_STARTED]) {
        cocos2dx_EventHandlers::getInstance()->itemPurchaseStarted();
    }
    else if ([notification.name isEqualToString:EVENT_OPENING_STORE]) {
        cocos2dx_EventHandlers::getInstance()->openingStore();
    }
    else if ([notification.name isEqualToString:EVENT_APPSTORE_PURCHASE_CANCELLED]) {
        PurchasableVirtualItem* pvi = (PurchasableVirtualItem*)[notification.userInfo objectForKey:DICT_ELEMENT_PURCHASABLE];
        string itemId([pvi.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchaseCancelled(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_APPSTORE_PURCHASED]) {
        PurchasableVirtualItem* pvi = (PurchasableVirtualItem*)[notification.userInfo objectForKey:DICT_ELEMENT_PURCHASABLE];
        string itemId([pvi.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchase(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_APPSTORE_PURCHASE_STARTED]) {
        PurchasableVirtualItem* pvi = (PurchasableVirtualItem*)[notification.userInfo objectForKey:DICT_ELEMENT_PURCHASABLE];
        string itemId([pvi.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchaseStarted(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_TRANSACTION_RESTORED]) {
        BOOL success = [(NSNumber*)[notification.userInfo objectForKey:DICT_ELEMENT_SUCCESS] boolValue];
        cocos2dx_EventHandlers::getInstance()->restoreTransactions(success);
    }
    else if ([notification.name isEqualToString:EVENT_TRANSACTION_RESTORE_STARTED]) {
        cocos2dx_EventHandlers::getInstance()->restoreTransactionsStarted();
    }
    else if ([notification.name isEqualToString:EVENT_UNEXPECTED_ERROR_IN_STORE]) {
        cocos2dx_EventHandlers::getInstance()->unexpectedErrorInStore();
    }
    

}


@end
