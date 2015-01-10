package com.soomla.cocos2dx.store;

import android.util.Log;
import com.soomla.store.StoreInventory;
import com.soomla.store.exceptions.InsufficientFundsException;
import com.soomla.store.exceptions.VirtualItemNotFoundException;

/**
 * This bridge is used to let cocos2dx functions perform actions on StoreInventory (through JNI).
 *
 * You can see the documentation of every function in {@link StoreInventory}
 */
public class StoreInventoryBridge {

    static void buy(String itemId) throws VirtualItemNotFoundException, InsufficientFundsException {
        //Log.d("SOOMLA", "buy is called from java !");
        StoreInventory.buy(itemId);
    }

    static int getItemBalance(String itemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "getCurrencyBalance is called from java !");
        return StoreInventory.getVirtualItemBalance(itemId);
    }

    static void giveItem(String itemId, int amount) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "addCurrencyAmount is called from java !");
        StoreInventory.giveVirtualItem(itemId, amount);
    }

    static void takeItem(String itemId, int amount) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "removeCurrencyAmount is called from java !");
        StoreInventory.takeVirtualItem(itemId, amount);
    }

    static void equipGood(String goodItemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "equipGood is called from java !");
        StoreInventory.equipVirtualGood(goodItemId);
    }

    static void unEquipGood(String goodItemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "unEquipGood is called from java !");
        StoreInventory.unEquipVirtualGood(goodItemId);
    }

    static boolean isGoodEquipped(String goodItemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "isGoodEquipped is called from java !");
        return StoreInventory.isVirtualGoodEquipped(goodItemId);
    }

    static int getGoodUpgradeLevel(String goodItemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "getGoodUpgradeLevel is called from java !");
        return StoreInventory.getGoodUpgradeLevel(goodItemId);
    }

    static String getGoodCurrentUpgrade(String goodItemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "removeGoodAmount is called from java !");
        return StoreInventory.getGoodCurrentUpgrade(goodItemId);
    }

    static void upgradeVirtualGood(String goodItemId) throws VirtualItemNotFoundException, InsufficientFundsException {
        //Log.d("SOOMLA", "upgradeVirtualGood is called from java !");
        StoreInventory.upgradeVirtualGood(goodItemId);
    }

    static void removeUpgrades(String goodItemId) throws VirtualItemNotFoundException {
        //Log.d("SOOMLA", "removeUpgrades is called from java !");
        StoreInventory.removeUpgrades(goodItemId);
    }

    static boolean nonConsumableItemExists(String nonConsItemId) throws VirtualItemNotFoundException, ClassCastException {
        //Log.d("SOOMLA", "nonConsumableItemExists is called from java !");
        return StoreInventory.nonConsumableItemExists(nonConsItemId);
    }

    static void addNonConsumableItem(String nonConsItemId) throws VirtualItemNotFoundException, ClassCastException {
        //Log.d("SOOMLA", "addNonConsumableItem is called from java !");
        StoreInventory.addNonConsumableItem(nonConsItemId);
    }

    static void removeNonConsumableItem(String nonConsItemId) throws VirtualItemNotFoundException, ClassCastException {
        //Log.d("SOOMLA", "removeNonConsumableItem is called from java !");
        StoreInventory.removeNonConsumableItem(nonConsItemId);
    }

}
