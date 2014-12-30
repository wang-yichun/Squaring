package com.soomla.cocos2dx.store;

import com.soomla.store.data.StoreInfo;
import com.soomla.store.domain.PurchasableVirtualItem;
import com.soomla.store.domain.VirtualItem;
import com.soomla.store.domain.virtualGoods.UpgradeVG;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;
import com.soomla.store.purchaseTypes.PurchaseWithVirtualItem;

/**
 * This bridge is used to let cocos2dx functions retrieve data from StoreInfo (through JNI).
 *
 * You can see the documentation of every function in {@link StoreInfo}
 */
public class StoreInfoBridge {

//    static String getVirtualItem(String itemId) throws VirtualItemNotFoundException{
//        VirtualItem item = StoreInfo.getVirtualItem(itemId);
//        return item.getItemId();
//    }
//
//    static String getPurchasableItem(String productId) throws VirtualItemNotFoundException{
//        PurchasableVirtualItem pvi = StoreInfo.getPurchasableItem(productId);
//        return pvi.getItemId();
//    }

    static String getGoodFirstUpgrade(String goodItemId) throws VirtualItemNotFoundException {
        UpgradeVG vgu = StoreInfo.getGoodFirstUpgrade(goodItemId);
        return vgu.getItemId();
    }

    static String getGoodLastUpgrade(String goodItemId) throws VirtualItemNotFoundException {
        UpgradeVG vgu = StoreInfo.getGoodLastUpgrade(goodItemId);
        return vgu.getItemId();
    }

    static String getItemProductId(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        if (item instanceof PurchasableVirtualItem) {
            PurchasableVirtualItem pvi = (PurchasableVirtualItem) item;
            if (pvi.getPurchaseType() instanceof PurchaseWithMarket) {
                PurchaseWithMarket pwm = (PurchaseWithMarket)pvi.getPurchaseType();
                return pwm.getGoogleMarketItem().getProductId();
            }
        }
        return "";
    }

    static String getItemName(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        return item.getName();
    }

    static String getItemDescription(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        return item.getDescription();
    }

    static double getItemPrice(String itemId) throws VirtualItemNotFoundException {
        VirtualItem item = StoreInfo.getVirtualItem(itemId);
        if (item instanceof PurchasableVirtualItem) {
            PurchasableVirtualItem pvi = (PurchasableVirtualItem) item;
            if (pvi.getPurchaseType() instanceof PurchaseWithMarket) {
                PurchaseWithMarket pwm = (PurchaseWithMarket)pvi.getPurchaseType();
                return pwm.getGoogleMarketItem().getPrice();
            }

            if (pvi.getPurchaseType() instanceof PurchaseWithVirtualItem) {
                PurchaseWithVirtualItem pwvi = (PurchaseWithVirtualItem)pvi.getPurchaseType();
                return pwvi.getAmount();
            }
        }
        return -1;
    }
}
