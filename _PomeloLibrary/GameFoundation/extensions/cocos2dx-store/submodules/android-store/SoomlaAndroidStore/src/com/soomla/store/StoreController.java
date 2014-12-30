/*
 * Copyright (C) 2012-2014 Soomla Inc.
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

package com.soomla.store;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;

import com.soomla.store.billing.IIabService;
import com.soomla.store.billing.IabCallbacks;
import com.soomla.store.billing.IabException;
import com.soomla.store.billing.IabPurchase;
import com.soomla.store.billing.IabSkuDetails;
import com.soomla.store.data.ObscuredSharedPreferences;
import com.soomla.store.data.StorageManager;
import com.soomla.store.data.StoreInfo;
import com.soomla.store.domain.MarketItem;
import com.soomla.store.domain.NonConsumableItem;
import com.soomla.store.domain.PurchasableVirtualItem;
import com.soomla.store.events.BillingNotSupportedEvent;
import com.soomla.store.events.BillingSupportedEvent;
import com.soomla.store.events.IabServiceStartedEvent;
import com.soomla.store.events.MarketItemsRefreshFinishedEvent;
import com.soomla.store.events.MarketItemsRefreshStartedEvent;
import com.soomla.store.events.MarketPurchaseCancelledEvent;
import com.soomla.store.events.MarketPurchaseEvent;
import com.soomla.store.events.MarketPurchaseStartedEvent;
import com.soomla.store.events.MarketRefundEvent;
import com.soomla.store.events.RestoreTransactionsFinishedEvent;
import com.soomla.store.events.ItemPurchasedEvent;
import com.soomla.store.events.RestoreTransactionsStartedEvent;
import com.soomla.store.events.StoreControllerInitializedEvent;
import com.soomla.store.events.UnexpectedStoreErrorEvent;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;

import java.util.ArrayList;
import java.util.List;

/**
 * This class holds the basic assets needed to operate the Store.
 * You can use it to perform any operation related to the mobile store.
 *
 * This is the only class you need to initialize in order to use the SOOMLA SDK.
 *
 * To properly work with this class you must initialize it with the {@link #initialize} method.
 */
public class StoreController {

    /**
     * Initializes the SOOMLA SDK.
     * This initializer also initializes {@link com.soomla.store.data.StoreInfo}.
     *
     * @param storeAssets the definition of your application specific assets.
     * @param customSecret your encryption secret (it's used to encrypt your data in the database)
     */
    public boolean initialize(IStoreAssets storeAssets, String customSecret) {
        if (mInitialized) {
            String err = "StoreController is already initialized. You can't initialize it twice!";
            handleErrorResult(err);
            return false;
        }

        StoreUtils.LogDebug(TAG, "StoreController Initializing ...");

//        if (mInAppBillingService == null) {
//            StoreUtils.LogDebug(TAG, "Searching for the attached IAB Service.");
//
//            Class<?> aClass = null;
//            aClass = tryFetchIabService();
//            if (aClass == null) {
//                String err = "You don't have a billing service attached. " +
//                        "Decide which billing service you want, add it to AndroidManifest.xml " +
//                        "and add its jar to the path.";
//                handleErrorResult(err);
//                return false;
//            }
//
//            try {
//                mInAppBillingService = (IIabService) aClass.newInstance();
//            } catch (Exception e) {
//                String err = "Couldn't instantiate IIabService class. Something's totally wrong here.";
//                handleErrorResult(err);
//                return false;
//            }
//        }

        SharedPreferences prefs = new ObscuredSharedPreferences(SoomlaApp.getAppContext().
                getSharedPreferences(StoreConfig.PREFS_NAME, Context.MODE_PRIVATE));
        SharedPreferences.Editor edit = prefs.edit();

        if (customSecret != null && customSecret.length() != 0) {
            edit.putString(StoreConfig.CUSTOM_SEC, customSecret);
        } else if (prefs.getString(StoreConfig.CUSTOM_SEC, "").length() == 0) {
        	String err = "customSecret is null or empty. Can't initialize store!!";
            StoreUtils.LogError(TAG, err);
            BusProvider.getInstance().post(new UnexpectedStoreErrorEvent(err));
            return false;
        }
        edit.putInt("SA_VER_NEW", storeAssets.getVersion());
        edit.commit();

        if (storeAssets != null) {
            StoreInfo.setStoreAssets(storeAssets);
        }

        // Update SOOMLA store from DB
        StoreInfo.initializeFromDB();

        refreshInventory();

        mInitialized = true;
        BusProvider.getInstance().post(new StoreControllerInitializedEvent());
        return true;
    }

    /**
     * Starts in-app billing service in background.
     */
    public void startIabServiceInBg() {
        mInAppBillingService.startIabServiceInBg(new IabCallbacks.IabInitListener() {

            @Override
            public void success(boolean alreadyInBg) {
                if (!alreadyInBg) {
                    notifyIabServiceStarted();
                    StoreUtils.LogDebug(TAG, "Successfully started billing service in background.");
                } else {
                    StoreUtils.LogDebug(TAG, "Couldn't start billing service in background. "
                            + "Was already started.");
                }
            }

            @Override
            public void fail(String message) {
                StoreUtils.LogError(TAG, "Couldn't start billing service in background. error: "
                        + message);
            }
        });
    }

    /**
     * Stops in-app billing service in background.
     *
     * IMPORTANT: This function is not supported in all billing providers (Amazon for example).
     */
    public void stopIabServiceInBg() {
        mInAppBillingService.stopIabServiceInBg(new IabCallbacks.IabInitListener() {

            @Override
            public void success(boolean alreadyInBg) {
                StoreUtils.LogDebug(TAG, "Successfully stopped billing service in background.");
            }

            @Override
            public void fail(String message) {
                StoreUtils.LogError(TAG, "Couldn't stop billing service in background. error: "
                        + message);
            }
        });
    }

    /**
     * Restoring old purchases for the current user (device).
     * Here we just call the private function without refreshing market items details.
     */
    public void restoreTransactions() {
        restoreTransactions(false);
    }

    /**
     * Restoring old purchases for the current user (device).
     *
     * @param followedByRefreshItemsDetails determines weather we should perform a refresh market
     *                                      items operation right after a restore purchase success.
     */
    private void restoreTransactions(final boolean followedByRefreshItemsDetails) {
//        mInAppBillingService.initializeBillingService(
//                new IabCallbacks.IabInitListener() {
//
//                    @Override
//                    public void success(boolean alreadyInBg) {
//                        if (!alreadyInBg) {
//                            notifyIabServiceStarted();
//                        }
//
//                        StoreUtils.LogDebug(TAG,
//                                "Setup successful, restoring purchases");
//
//                        IabCallbacks.OnRestorePurchasesListener restorePurchasesListener = new IabCallbacks.OnRestorePurchasesListener() {
//                            @Override
//                            public void success(List<IabPurchase> purchases) {
//                                StoreUtils.LogDebug(TAG, "Transactions restored");
//
//                                if (purchases.size() > 0) {
//                                    for (IabPurchase iabPurchase : purchases) {
//                                        StoreUtils.LogDebug(TAG, "Got owned item: " + iabPurchase.getSku());
//
//                                        handleSuccessfulPurchase(iabPurchase);
//                                    }
//                                }
//
//                                BusProvider.getInstance().post(
//                                        new RestoreTransactionsFinishedEvent(true));
//
//                                if (followedByRefreshItemsDetails) {
//                                    refreshMarketItemsDetails();
//                                }
//                            }
//
//                            @Override
//                            public void fail(String message) {
//                                BusProvider.getInstance().post(new RestoreTransactionsFinishedEvent(false));
//                                handleErrorResult(message);
//                            }
//                        };
//
//                        mInAppBillingService.restorePurchasesAsync(restorePurchasesListener);
//
//                        BusProvider.getInstance().post(new RestoreTransactionsStartedEvent());
//                    }
//
//                    @Override
//                    public void fail(String message) {
//                        reportIabInitFailure(message);
//                    }
//                }
//        );
    }

    /**
     * Queries the store for the details for all of the game's market items by product ids.
     * This operation will "fill" up the MarketItem objects with the information you provided in
     * the developer console including: localized price (as string), title and description.
     */
    public void refreshMarketItemsDetails() {
        mInAppBillingService.initializeBillingService(
                new IabCallbacks.IabInitListener() {

                    @Override
                    public void success(boolean alreadyInBg) {
                        if (!alreadyInBg) {
                            notifyIabServiceStarted();
                        }
                        StoreUtils.LogDebug(TAG,
                                "Setup successful, refreshing market items details");

                        IabCallbacks.OnFetchSkusDetailsListener fetchSkusDetailsListener =
                                new IabCallbacks.OnFetchSkusDetailsListener() {

                                    @Override
                                    public void success(List<IabSkuDetails> skuDetails) {
                                        StoreUtils.LogDebug(TAG, "Market items details refreshed");

                                        List<MarketItem> marketItems = new ArrayList<MarketItem>();
                                        if (skuDetails.size() > 0) {
                                            for (IabSkuDetails iabSkuDetails : skuDetails) {
                                                String productId = iabSkuDetails.getSku();
                                                String price = iabSkuDetails.getPrice();
                                                String title = iabSkuDetails.getTitle();
                                                String desc = iabSkuDetails.getDescription();

                                                StoreUtils.LogDebug(TAG, "Got item details: " +
                                                        "\ntitle:\t" + iabSkuDetails.getTitle() +
                                                        "\nprice:\t" + iabSkuDetails.getPrice() +
                                                        "\nproductId:\t" + iabSkuDetails.getSku() +
                                                        "\ndesc:\t" + iabSkuDetails.getDescription());

                                                try {
                                                    PurchasableVirtualItem pvi = StoreInfo.
                                                            getPurchasableItem(productId);
                                                    MarketItem mi = ((PurchaseWithMarket)
                                                            pvi.getPurchaseType()).getMarketItem();
                                                    mi.setMarketTitle(title);
                                                    mi.setMarketPrice(price);
                                                    mi.setMarketDescription(desc);

                                                    marketItems.add(mi);
                                                } catch (VirtualItemNotFoundException e) {
                                                    String msg = "(refreshInventory) Couldn't find a "
                                                            + "purchasable item associated with: " + productId;
                                                    StoreUtils.LogError(TAG, msg);
                                                }
                                            }
                                        }
                                        BusProvider.getInstance().post(new MarketItemsRefreshFinishedEvent(marketItems));
                                    }

                                    @Override
                                    public void fail(String message) {

                                    }
                                };

                        final List<String> purchasableProductIds = StoreInfo.getAllProductIds();
                        mInAppBillingService.fetchSkusDetailsAsync(purchasableProductIds, fetchSkusDetailsListener);

                        BusProvider.getInstance().post(new MarketItemsRefreshStartedEvent());
                    }

                    @Override
                    public void fail(String message) {
                        reportIabInitFailure(message);
                    }
                }
        );
    }

    /**
     * This runs restoreTransactions followed by market items refresh.
     * There are docs that explains restoreTransactions and refreshMarketItemsDetails on the actual
     * functions in this file.
     */
    public void refreshInventory() {
        restoreTransactions(true);
    }

    /**
     * Starts a purchase process in the market.
     *
     * @param marketItem The item to purchase - this item has to be defined EXACTLY the same in
     *                   the market
     * @param payload A payload to get back when this purchase is finished.
     * @throws IllegalStateException
     */
    public void buyWithMarket(final MarketItem marketItem, final String payload) throws IllegalStateException {
        final PurchasableVirtualItem pvi;
        try {
            pvi = StoreInfo.getPurchasableItem(marketItem.getProductId());
        } catch (VirtualItemNotFoundException e) {
            String msg = "Couldn't find a purchasable item associated with: " + marketItem.getProductId();
            StoreUtils.LogError(TAG, msg);
            BusProvider.getInstance().post(new UnexpectedStoreErrorEvent(msg));
            return;
        }

        mInAppBillingService.initializeBillingService
                (new IabCallbacks.IabInitListener() {

                    @Override
                    public void success(boolean alreadyInBg) {
                        if (!alreadyInBg) {
                            notifyIabServiceStarted();
                        }

                        IabCallbacks.OnPurchaseListener purchaseListener =
                                new IabCallbacks.OnPurchaseListener() {

                                    @Override
                                    public void success(IabPurchase purchase) {
                                        handleSuccessfulPurchase(purchase);
                                    }

                                    @Override
                                    public void cancelled(IabPurchase purchase) {
                                        handleCancelledPurchase(purchase);
                                    }

                                    @Override
                                    public void alreadyOwned(IabPurchase purchase) {
                                        StoreUtils.LogDebug(TAG, "Tried to buy an item that was not consumed. "
                                                + "Trying to consume it if it's a consumable.");
                                        consumeIfConsumable(purchase);
                                    }

                                    @Override
                                    public void fail(String message) {
                                        handleErrorResult(message);
                                    }
                                };
                        mInAppBillingService.launchPurchaseFlow(marketItem.getProductId(),
                                purchaseListener, payload);
                        BusProvider.getInstance().post(new MarketPurchaseStartedEvent(pvi));
                    }

                    @Override
                    public void fail(String message) {
                        reportIabInitFailure(message);
                    }

                });
    }

    /**
     * Determines if Store Controller is initialized
     *
     * @return true if initialized, false otherwise
     */
    public boolean isInitialized() {
        return mInitialized;
    }


    /**
     * Fetches the current billing service.
     *
     * @return the current billing service.
     */
    public IIabService getInAppBillingService() {
        return mInAppBillingService;
    }

    /*==================== Common callbacks for success \ failure \ finish ====================*/

    /**
     * Notifies the user that the billing service is supported and started.
     */
    private void notifyIabServiceStarted() {
        BusProvider.getInstance().post(new BillingSupportedEvent());
        BusProvider.getInstance().post(new IabServiceStartedEvent());
    }

    /**
     * Reports that in-app billing service initialization failed.
     *
     * @param message error message.
     */
    private void reportIabInitFailure(String message) {
        String msg = "There's no connectivity with the billing service. error: " + message;
        StoreUtils.LogDebug(TAG, msg);
        BusProvider.getInstance().post(new BillingNotSupportedEvent());
        //BusProvider.getInstance().post(new UnexpectedStoreErrorEvent(msg));
    }



    /**
     * Checks the state of the purchase and responds accordingly, giving the user an item,
     * throwing an error, or taking the item away and paying the user back.
     *
     * @param purchase purchase whose state is to be checked.
     */
    private void handleSuccessfulPurchase(IabPurchase purchase) {
        String sku = purchase.getSku();
        String developerPayload = purchase.getDeveloperPayload();
        String token = purchase.getToken();

        PurchasableVirtualItem pvi;
        try {
            pvi = StoreInfo.getPurchasableItem(sku);
        } catch (VirtualItemNotFoundException e) {
            StoreUtils.LogError(TAG, "(handleSuccessfulPurchase - purchase or query-inventory) "
                    + "ERROR : Couldn't find the " +
                    " VirtualCurrencyPack OR MarketItem  with productId: " + sku +
                    ". It's unexpected so an unexpected error is being emitted.");
            BusProvider.getInstance().post(new UnexpectedStoreErrorEvent("Couldn't find the sku "
                    + "of a product after purchase or query-inventory."));
            return;
        }

        switch (purchase.getPurchaseState()) {
            case 0:
                StoreUtils.LogDebug(TAG, "IabPurchase successful.");

                // if the purchasable item is NonConsumableItem and it already exists then we
                // don't fire any events.
                // fixes: https://github.com/soomla/unity3d-store/issues/192
                if (pvi instanceof NonConsumableItem) {
                    boolean exists = StorageManager.getNonConsumableItemsStorage().
                            nonConsumableItemExists((NonConsumableItem) pvi);
                    if (exists) {
                        return;
                    }
                }

                BusProvider.getInstance().post(new MarketPurchaseEvent
                        (pvi, developerPayload, token));
                pvi.give(1);
                BusProvider.getInstance().post(new ItemPurchasedEvent(pvi));

                consumeIfConsumable(purchase);
                break;

            case 1:

            case 2:
                StoreUtils.LogDebug(TAG, "IabPurchase refunded.");
                if (!StoreConfig.friendlyRefunds) {
                    pvi.take(1);
                }
                BusProvider.getInstance().post(new MarketRefundEvent(pvi, developerPayload));
                break;
        }
    }

    /**
     * Handles a cancelled purchase by either posting an event containing a
     * <code>PurchasableVirtualItem</code> corresponding to the given purchase, or an unexpected
     * error event if the item was not found.
     *
     * @param purchase cancelled purchase to handle.
     */
    private void handleCancelledPurchase(IabPurchase purchase) {
        String sku = purchase.getSku();
        try {
            PurchasableVirtualItem v = StoreInfo.getPurchasableItem(sku);
            BusProvider.getInstance().post(new MarketPurchaseCancelledEvent(v));
        } catch (VirtualItemNotFoundException e) {
            StoreUtils.LogError(TAG, "(purchaseActionResultCancelled) ERROR : Couldn't find the "
                    + "VirtualCurrencyPack OR MarketItem  with productId: " + sku
                    + ". It's unexpected so an unexpected error is being emitted.");
            BusProvider.getInstance().post(new UnexpectedStoreErrorEvent());
        }
    }

    /**
     * Consumes the given purchase, or writes error message to log if unable to consume
     *
     * @param purchase purchase to be consumed
     */
    private void consumeIfConsumable(IabPurchase purchase) {
        String sku = purchase.getSku();
        try {
            PurchasableVirtualItem pvi = StoreInfo.getPurchasableItem(sku);

            if (!(pvi instanceof NonConsumableItem)) {
                mInAppBillingService.consume(purchase);
            }
        } catch (VirtualItemNotFoundException e) {
            StoreUtils.LogError(TAG, "(purchaseActionResultCancelled) ERROR : Couldn't find the "
                    + "VirtualCurrencyPack OR MarketItem  with productId: " + sku
                    + ". It's unexpected so an unexpected error is being emitted.");
            BusProvider.getInstance().post(new UnexpectedStoreErrorEvent());
        } catch (IabException e) {
            StoreUtils.LogDebug(TAG, "Error while consuming: " + sku);
            BusProvider.getInstance().post(new UnexpectedStoreErrorEvent(e.getMessage()));
        }
    }

    /**
     * Fetches the associated billing service according to the meta-data tag in AndroidManifest.xml.
     *
     * @return the Main class of the associated billing service or null if none was found.
     */
    private Class<?> tryFetchIabService() {
        String iabServiceClassName;
        try {
            ApplicationInfo ai = SoomlaApp.getAppContext().getPackageManager().getApplicationInfo(
                    SoomlaApp.getAppContext().getPackageName(), PackageManager.GET_META_DATA);
            assert ai.metaData != null;
            iabServiceClassName = ai.metaData.getString("billing.service");
        } catch (Exception e) {
            StoreUtils.LogError(TAG, "Failed to load billing service from AndroidManifest.xml, NullPointer: " + e.getMessage());
            return null;
        }

        Class<?> aClass = null;
        try {
            StoreUtils.LogDebug(TAG, "Trying to find " + iabServiceClassName);
            aClass = Class.forName("com.soomla.store.billing." + iabServiceClassName);
        } catch (ClassNotFoundException e) {
            StoreUtils.LogDebug(TAG, "Failed finding " + iabServiceClassName);
        }
        return aClass;
    }

    /**
     * Posts an unexpected error event saying the purchase failed.
     *
     * @param message error message.
     */
    private void handleErrorResult(String message) {
        BusProvider.getInstance().post(new UnexpectedStoreErrorEvent(message));
        StoreUtils.LogError(TAG, "ERROR: IabPurchase failed: " + message);
    }

    /* Singleton */
    private static StoreController sInstance = null;

    /**
     * Retrieves the singleton instance of <code>StoreController</code>
     *
     * @return singleton instance of <code>StoreController</code>
     */
    public static StoreController getInstance() {
        if (sInstance == null) {
            sInstance = new StoreController();
        }
        return sInstance;
    }

    /**
     * Constructor
     */
    private StoreController() {
    }


    /* Private Members */

    private static final String TAG = "SOOMLA StoreController"; //used for Log messages
    private boolean mInitialized = false;
    private IIabService mInAppBillingService;

}
