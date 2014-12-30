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

package com.soomla.store.data;

import android.text.TextUtils;
import com.soomla.store.IStoreAssets;
import com.soomla.store.StoreUtils;
import com.soomla.store.domain.NonConsumableItem;
import com.soomla.store.domain.PurchasableVirtualItem;
import com.soomla.store.domain.VirtualCategory;
import com.soomla.store.domain.VirtualItem;
import com.soomla.store.domain.virtualCurrencies.VirtualCurrency;
import com.soomla.store.domain.virtualCurrencies.VirtualCurrencyPack;
import com.soomla.store.domain.virtualGoods.*;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import com.soomla.store.purchaseTypes.PurchaseType;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.*;

/**
 * This class holds the store's metadata including:
 * virtual currencies,
 * virtual currency packs,
 * all kinds of virtual goods,
 * virtual categories, and
 * non-consumable items
 */
public class StoreInfo {

    /**
     * Initializes <code>StoreInfo</code>.
     * On first initialization, when the database doesn't have any previous version of the store
     * metadata, <code>StoreInfo</code> gets loaded from the given <code>IStoreAssets</code>.
     * After the first initialization, <code>StoreInfo</code> will be initialized from the database.
     *
     * IMPORTANT: If you want to override the current <code>StoreInfo</code>, you'll have to bump
     * the version of your implementation of <code>IStoreAssets</code> in order to remove the
     * metadata when the application loads. Bumping the version is done by returning a higher number
     * in {@link com.soomla.store.IStoreAssets#getVersion()}.
     */
    public static void setStoreAssets(IStoreAssets storeAssets){
        if (storeAssets == null){
            StoreUtils.LogError(TAG, "The given store assets can't be null!");
            return;
        }
        // we always initialize from the database, unless this is the first time the game is
        // loaded - in that case we initialize with setStoreAssets.
        if (!initializeFromDB()){
            initializeWithStoreAssets(storeAssets);
        }
    }

    /**
     * Initializes <code>StoreInfo</code> from the database. This action should be performed only
     * once during the lifetime of a session of the game. <code>StoreController</code> automatically
     * initializes <code>StoreInfo</code>. Don't do it if you don't know what you're doing.
     *
     * @return success
     */
    public static boolean initializeFromDB() {
        String key = KeyValDatabase.keyMetaStoreInfo();
        String val = StorageManager.getKeyValueStorage().getValue(key);

        if (val == null && TextUtils.isEmpty(val)){
            StoreUtils.LogDebug(TAG, "store json is not in DB yet.");
            return false;
        }

        StoreUtils.LogDebug(TAG, "the metadata-economy json (from DB) is " + val);

        try {
            fromJSONObject(new JSONObject(val));

            // everything went well... StoreInfo is initialized from the local DB.
            // it's ok to return now.

            return true;
        } catch (JSONException e) {
            StoreUtils.LogDebug(TAG, "Can't parse metadata json. Going to return false and make "
                    + "StoreInfo load from static data: " + val);
        }

        return false;

    }

    /**
     * Checks if the <code>VirtualGood</code>d with the given <code>goodItemId</code> has upgrades.
     *
     * @param goodItemId the item id of the <code>VirtualGood</code> to check if has upgrades.
     * @return true if upgrades found for the <code>VirtualGood</code> with the given
     * <code>goodItemId</code>, otherwise false.
     */
    public static boolean hasUpgrades(String goodItemId) {
        return mGoodsUpgrades.containsKey(goodItemId);
    }


    /** Setters and Getters */

    /**
     * Retrieves a single <code>VirtualItem</code> that resides in the metadata.
     *
     * @param itemId the itemId of the required <code>VirtualItem</code>
     * @return virtual item for the given <code>itemId</code>
     * @throws VirtualItemNotFoundException if no <code>VirtualItem</code> with the given
     * <code>itemId</code> was found.
     */
    public static VirtualItem getVirtualItem(String itemId) throws VirtualItemNotFoundException{
        VirtualItem item = mVirtualItems.get(itemId);
        if (item == null) {
            throw new VirtualItemNotFoundException("itemId", itemId);
        }

        return item;
    }

    /**
     * Retrieves a single <code>PurchasableVirtualItem</code> that resides in the metadata.
     * IMPORTANT: The retrieved <code>PurchasableVirtualItem</code> has a <code>PurchaseType</code>
     * of <code>PurchaseWithMarket</code> (This is why we fetch here with <code>productId</code>).
     *
     * @param productId the product id of the purchasable item to be fetched
     * @return <code>PurchasableVirtualItem</code>
     * @throws VirtualItemNotFoundException if no PurchasableVirtualItem with the given
     *         productId was found.
     */
    public static PurchasableVirtualItem getPurchasableItem(String productId)
            throws VirtualItemNotFoundException{
        PurchasableVirtualItem item = mPurchasableItems.get(productId);
        if (item == null) {
            throw new VirtualItemNotFoundException("productId", productId);
        }

        return item;
    }

    /**
     * Retrieves the <code>VirtualCategory</code> that the virtual good with the given
     * <code>goodItemId</code> belongs to.
     *
     * @param goodItemId the id of the virtual good whose category is to be fetched
     * @return the virtual category that the good with the given <code>goodItemId</code> belongs to
     * @throws VirtualItemNotFoundException if the given <code>goodItemId</code> is not found
     */
    public static VirtualCategory getCategory(String goodItemId)
            throws VirtualItemNotFoundException {
        VirtualCategory item = mGoodsCategories.get(goodItemId);
        if (item == null) {
            throw new VirtualItemNotFoundException("goodItemId", goodItemId);
        }

        return item;
    }

    /**
     * Retrieves the first <code>UpgradeVG</code> for the given <code>goodItemId</code>.
     *
     * @param goodItemId The item id of the <code>VirtualGood</code> whose upgrade we are looking
     *                   for.
     * @return The first upgrade for the virtual good with the given <code>goodItemId</code>, or
     * null if it has no upgrades.
     */
    public static UpgradeVG getGoodFirstUpgrade(String goodItemId) {
        List<UpgradeVG> upgrades = mGoodsUpgrades.get(goodItemId);
        if (upgrades != null) {
            for(UpgradeVG upgradeVG : upgrades) {
                if (TextUtils.isEmpty(upgradeVG.getPrevItemId())) {
                    return upgradeVG;
                }
            }
        }
        return null;
    }

    /**
     * Retrieves the last <code>UpgradeVG</code> for the given <code>goodItemId</code>.
     *
     * @param goodItemId The item id of the <code>VirtualGood</code> whose upgrade we are looking
     *                   for.
     * @return The last upgrade for the virtual good with the given <code>goodItemId</code> or null
     *     if there are no upgrades.
     */
    public static UpgradeVG getGoodLastUpgrade(String goodItemId) {
        List<UpgradeVG> upgrades = mGoodsUpgrades.get(goodItemId);
        if (upgrades != null) {
            for(UpgradeVG upgradeVG : upgrades) {
                if (TextUtils.isEmpty(upgradeVG.getNextItemId())) {
                    return upgradeVG;
                }
            }
        }
        return null;
    }

    /**
     * Retrieves all <code>UpgradeVGs</code> for the virtual good with the given
     * <code>goodItemId</code>.
     *
     * @param goodItemId The item id of the <code>VirtualGood</code> whose upgrades we are looking
     *                   for.
     * @return list of all UpgradeVGs for the virtual good with the given <code>goodItemId</code>
     */
    public static List<UpgradeVG> getGoodUpgrades(String goodItemId) {
        return mGoodsUpgrades.get(goodItemId);
    }

    public static List<VirtualCurrency> getCurrencies(){
        return mCurrencies;
    }

    public static List<VirtualCurrencyPack> getCurrencyPacks() {
        return mCurrencyPacks;
    }

    public static List<VirtualGood> getGoods() {
        return mGoods;
    }

    public static List<NonConsumableItem> getNonConsumableItems() {
        return mNonConsumables;
    }

    public static List<VirtualCategory> getCategories() {
        return mCategories;
    }

    public static List<String> getAllProductIds() {
        return new ArrayList<String>(mPurchasableItems.keySet());
    }


    /** Private functions **/
    /**
     * Transforms given jsonObject to StoreInfo
     *
     * @param jsonObject
     * @throws JSONException
     */
    private static void fromJSONObject(JSONObject jsonObject) throws JSONException {

        mVirtualItems = new HashMap<String, VirtualItem>();
        mPurchasableItems = new HashMap<String, PurchasableVirtualItem>();
        mGoodsCategories = new HashMap<String, VirtualCategory>();
        mGoodsUpgrades = new HashMap<String, List<UpgradeVG>>();
        mCurrencyPacks = new LinkedList<VirtualCurrencyPack>();
        mGoods = new LinkedList<VirtualGood>();
        mCategories = new LinkedList<VirtualCategory>();
        mCurrencies = new LinkedList<VirtualCurrency>();
        mNonConsumables = new LinkedList<NonConsumableItem>();

        if (jsonObject.has(JSONConsts.STORE_CURRENCIES)) {
            JSONArray virtualCurrencies = jsonObject.getJSONArray(JSONConsts.STORE_CURRENCIES);
            for (int i=0; i<virtualCurrencies.length(); i++){
                JSONObject o = virtualCurrencies.getJSONObject(i);
                VirtualCurrency c = new VirtualCurrency(o);
                mCurrencies.add(c);

                mVirtualItems.put(c.getItemId(), c);
            }
        }

        if (jsonObject.has(JSONConsts.STORE_CURRENCYPACKS)) {
            JSONArray currencyPacks = jsonObject.getJSONArray(JSONConsts.STORE_CURRENCYPACKS);
            for (int i=0; i<currencyPacks.length(); i++){
                JSONObject o = currencyPacks.getJSONObject(i);
                VirtualCurrencyPack pack = new VirtualCurrencyPack(o);
                mCurrencyPacks.add(pack);

                mVirtualItems.put(pack.getItemId(), pack);

                PurchaseType purchaseType = pack.getPurchaseType();
                if (purchaseType instanceof PurchaseWithMarket) {
                    mPurchasableItems.put(((PurchaseWithMarket) purchaseType)
                            .getMarketItem().getProductId(), pack);
                }
            }
        }

        // The order in which VirtualGoods are created matters!
        // For example: VGU and VGP depend on other VGs
        if (jsonObject.has(JSONConsts.STORE_GOODS)) {
            JSONObject virtualGoods = jsonObject.getJSONObject(JSONConsts.STORE_GOODS);

            if (virtualGoods.has(JSONConsts.STORE_GOODS_SU)) {
                JSONArray suGoods = virtualGoods.getJSONArray(JSONConsts.STORE_GOODS_SU);
                for (int i=0; i<suGoods.length(); i++){
                    JSONObject o = suGoods.getJSONObject(i);
                    SingleUseVG g = new SingleUseVG(o);
                    addVG(g);
                }
            }


            if (virtualGoods.has(JSONConsts.STORE_GOODS_LT)) {
                JSONArray ltGoods = virtualGoods.getJSONArray(JSONConsts.STORE_GOODS_LT);
                for (int i=0; i<ltGoods.length(); i++){
                    JSONObject o = ltGoods.getJSONObject(i);
                    LifetimeVG g = new LifetimeVG(o);
                    addVG(g);
                }
            }


            if (virtualGoods.has(JSONConsts.STORE_GOODS_EQ)) {
                JSONArray eqGoods = virtualGoods.getJSONArray(JSONConsts.STORE_GOODS_EQ);
                for (int i=0; i<eqGoods.length(); i++){
                    JSONObject o = eqGoods.getJSONObject(i);
                    EquippableVG g = new EquippableVG(o);
                    addVG(g);
                }
            }

            if (virtualGoods.has(JSONConsts.STORE_GOODS_PA)) {
                JSONArray paGoods = virtualGoods.getJSONArray(JSONConsts.STORE_GOODS_PA);
                for (int i=0; i<paGoods.length(); i++){
                    JSONObject o = paGoods.getJSONObject(i);
                    SingleUsePackVG g = new SingleUsePackVG(o);
                    addVG(g);
                }
            }


            if (virtualGoods.has(JSONConsts.STORE_GOODS_UP)) {
                JSONArray upGoods = virtualGoods.getJSONArray(JSONConsts.STORE_GOODS_UP);
                for (int i=0; i<upGoods.length(); i++){
                    JSONObject o = upGoods.getJSONObject(i);
                    UpgradeVG g = new UpgradeVG(o);
                    addVG(g);

                    List<UpgradeVG> upgrades = mGoodsUpgrades.get(g.getGoodItemId());
                    if (upgrades == null) {
                        upgrades = new ArrayList<UpgradeVG>();
                        mGoodsUpgrades.put(g.getGoodItemId(), upgrades);
                    }
                    upgrades.add(g);
                }
            }

        }

        // Categories depend on virtual goods. That's why the have to be initialized after!
        if (jsonObject.has(JSONConsts.STORE_CATEGORIES)) {
            JSONArray virtualCategories = jsonObject.getJSONArray(JSONConsts.STORE_CATEGORIES);
            for(int i=0; i<virtualCategories.length(); i++){
                JSONObject o = virtualCategories.getJSONObject(i);
                VirtualCategory category = new VirtualCategory(o);
                mCategories.add(category);
                for(String goodItemId : category.getGoodsItemIds()) {
                    mGoodsCategories.put(goodItemId, category);
                }
            }
        }

        if (jsonObject.has(JSONConsts.STORE_NONCONSUMABLES)) {
            JSONArray nonConsumables = jsonObject.getJSONArray(JSONConsts.STORE_NONCONSUMABLES);
            for (int i=0; i<nonConsumables.length(); i++){
                JSONObject o = nonConsumables.getJSONObject(i);
                NonConsumableItem non = new NonConsumableItem(o);
                mNonConsumables.add(non);

                mVirtualItems.put(non.getItemId(), non);

                PurchaseType purchaseType = non.getPurchaseType();
                if (purchaseType instanceof PurchaseWithMarket) {
                    mPurchasableItems.put(((PurchaseWithMarket) purchaseType)
                            .getMarketItem().getProductId(), non);
                }
            }
        }
    }

    /**
     * Adds the given virtual good to <code>StoreInfo</code>'s <code>mGoods</code>,
     * <code>mVirtualItems</code>, and if the good has purchase type <code>PurchaseWithMarket</code>
     * then it is also added to <code>mPurchasableItems</code>.
     *
     * @param g virtual good to be added
     */
    private static void addVG(VirtualGood g) {
        mGoods.add(g);

        mVirtualItems.put(g.getItemId(), g);

        PurchaseType purchaseType = g.getPurchaseType();
        if (purchaseType instanceof PurchaseWithMarket) {
            mPurchasableItems.put(((PurchaseWithMarket) purchaseType)
                    .getMarketItem().getProductId(), g);
        }
    }

    /**
     * Converts <code>StoreInfo</code> to a <code>JSONObject</code>.
     *
     * @return a <code>JSONObject</code> representation of <code>StoreInfo</code>.
     */
    public static JSONObject toJSONObject(){

        JSONArray currencies = new JSONArray();
        for(VirtualCurrency c : mCurrencies){
            currencies.put(c.toJSONObject());
        }

        JSONArray currencyPacks = new JSONArray();
        for(VirtualCurrencyPack pack : mCurrencyPacks){
            currencyPacks.put(pack.toJSONObject());
        }

        JSONObject goods = new JSONObject();
        JSONArray suGoods = new JSONArray();
        JSONArray ltGoods = new JSONArray();
        JSONArray eqGoods = new JSONArray();
        JSONArray paGoods = new JSONArray();
        JSONArray upGoods = new JSONArray();
        for(VirtualGood good : mGoods){
            if (good instanceof SingleUseVG) {
                suGoods.put(good.toJSONObject());
            } else if (good instanceof UpgradeVG) {
                upGoods.put(good.toJSONObject());
            } else if (good instanceof EquippableVG) {
                eqGoods.put(good.toJSONObject());
            } else if (good instanceof SingleUsePackVG) {
                paGoods.put(good.toJSONObject());
            } else if (good instanceof LifetimeVG) {
                ltGoods.put(good.toJSONObject());
            }
        }


        JSONArray categories = new JSONArray();
        for (VirtualCategory cat : mCategories){
            categories.put(cat.toJSONObject());
        }

        JSONArray nonConsumableItems = new JSONArray();
        for(NonConsumableItem non : mNonConsumables){
            nonConsumableItems.put(non.toJSONObject());
        }

        JSONObject jsonObject = new JSONObject();
        try {
            goods.put(JSONConsts.STORE_GOODS_SU, suGoods);
            goods.put(JSONConsts.STORE_GOODS_LT, ltGoods);
            goods.put(JSONConsts.STORE_GOODS_EQ, eqGoods);
            goods.put(JSONConsts.STORE_GOODS_PA, paGoods);
            goods.put(JSONConsts.STORE_GOODS_UP, upGoods);

            jsonObject.put(JSONConsts.STORE_CATEGORIES, categories);
            jsonObject.put(JSONConsts.STORE_CURRENCIES, currencies);
            jsonObject.put(JSONConsts.STORE_GOODS, goods);
            jsonObject.put(JSONConsts.STORE_CURRENCYPACKS, currencyPacks);
            jsonObject.put(JSONConsts.STORE_NONCONSUMABLES, nonConsumableItems);
        } catch (JSONException e) {
            StoreUtils.LogError(TAG, "An error occurred while generating JSON object.");
        }

        return jsonObject;
    }

    /**
     * Saves the store's metadata in the database as JSON.
     */
    public static void save() {
        String store_json = toJSONObject().toString();
        StoreUtils.LogDebug(TAG, "saving StoreInfo to DB. json is: " + store_json);
        String key = KeyValDatabase.keyMetaStoreInfo();
        StorageManager.getKeyValueStorage().setValue(key, store_json);
    }

    /**
     * Replaces the given virtual item, and then saves the store's metadata.
     *
     * @param virtualItem the virtual item to replace
     */
    public static void save(VirtualItem virtualItem) {
        replaceVirtualItem(virtualItem);
        save();
    }

    /**
     * Replaces an old virtual item with a new one by doing the following:
     * 1. Determines the type of the given virtual item.
     * 2. Looks for the given virtual item in the relevant list, according to its type.
     * 3. If found, removes it.
     * 4. Adds the given virtual item.
     *
     * @param virtualItem the virtual item that replaces the old one if exists.
     */
    public static void replaceVirtualItem(VirtualItem virtualItem) {
        mVirtualItems.put(virtualItem.getItemId(), virtualItem);

        if (virtualItem instanceof VirtualCurrency) {
            for(int i=0; i<mCurrencies.size(); i++) {
                if (mCurrencies.get(i).getItemId().equals(virtualItem.getItemId())) {
                    mCurrencies.remove(i);
                    break;
                }
            }
            mCurrencies.add((VirtualCurrency)virtualItem);
        }

        if (virtualItem instanceof VirtualCurrencyPack) {
            VirtualCurrencyPack vcp = (VirtualCurrencyPack)virtualItem;
            PurchaseType purchaseType = vcp.getPurchaseType();
            if (purchaseType instanceof PurchaseWithMarket) {
                mPurchasableItems.put(((PurchaseWithMarket) purchaseType).getMarketItem()
                        .getProductId(), vcp);
            }

            for(int i=0; i<mCurrencyPacks.size(); i++) {
                if (mCurrencyPacks.get(i).getItemId().equals(vcp.getItemId())) {
                    mCurrencyPacks.remove(i);
                    break;
                }
            }
            mCurrencyPacks.add(vcp);
        }

        if (virtualItem instanceof VirtualGood) {
            VirtualGood vg = (VirtualGood)virtualItem;

            if (vg instanceof UpgradeVG) {
                List<UpgradeVG> upgrades = mGoodsUpgrades.get(((UpgradeVG) vg).getGoodItemId());
                if (upgrades == null) {
                    upgrades = new ArrayList<UpgradeVG>();
                    mGoodsUpgrades.put(((UpgradeVG) vg).getGoodItemId(), upgrades);
                }
                upgrades.add((UpgradeVG) vg);
            }

            PurchaseType purchaseType = vg.getPurchaseType();
            if (purchaseType instanceof PurchaseWithMarket) {
                mPurchasableItems.put(((PurchaseWithMarket) purchaseType).getMarketItem()
                        .getProductId(), vg);
            }

            for(int i=0; i<mGoods.size(); i++) {
                if (mGoods.get(i).getItemId().equals(vg.getItemId())) {
                    mGoods.remove(i);
                    break;
                }
            }
            mGoods.add(vg);
        }

        if (virtualItem instanceof NonConsumableItem) {
            NonConsumableItem non = (NonConsumableItem) virtualItem;

            PurchaseType purchaseType = non.getPurchaseType();
            if (purchaseType instanceof PurchaseWithMarket) {
                mPurchasableItems.put(((PurchaseWithMarket) purchaseType).getMarketItem()
                        .getProductId(), non);
            }

            for(int i=0; i<mNonConsumables.size(); i++) {
                if (mNonConsumables.get(i).getItemId().equals(non.getItemId())) {
                    mNonConsumables.remove(i);
                    break;
                }
            }
            mNonConsumables.add(non);
        }
    }

    /**
     * Initializes from <code>IStoreAssets</code>.
     * This happens only once - when the game is loaded for the first time.
     *
     * @param storeAssets game economy
     */
    private static void initializeWithStoreAssets(IStoreAssets storeAssets) {
        // fall-back here if the json doesn't exist,
        // we load the store from the given {@link IStoreAssets}.
        mCurrencies = Arrays.asList(storeAssets.getCurrencies());
        mCurrencyPacks = Arrays.asList(storeAssets.getCurrencyPacks());
        mGoods = Arrays.asList(storeAssets.getGoods());
        mCategories = Arrays.asList(storeAssets.getCategories());
        mNonConsumables = Arrays.asList(storeAssets.getNonConsumableItems());

        mVirtualItems = new HashMap<String, VirtualItem>();
        mPurchasableItems = new HashMap<String, PurchasableVirtualItem>();
        mGoodsCategories = new HashMap<String, VirtualCategory>();
        mGoodsUpgrades = new HashMap<String, List<UpgradeVG>>();

        for(VirtualCurrency vi : mCurrencies) {
            mVirtualItems.put(vi.getItemId(), vi);
        }

        for(VirtualCurrencyPack vi : mCurrencyPacks) {
            mVirtualItems.put(vi.getItemId(), vi);

            PurchaseType purchaseType = vi.getPurchaseType();
            if (purchaseType instanceof PurchaseWithMarket) {
                mPurchasableItems.put(((PurchaseWithMarket) purchaseType).getMarketItem()
                        .getProductId(), vi);
            }
        }

        for(VirtualGood vi : mGoods) {
            mVirtualItems.put(vi.getItemId(), vi);

            if (vi instanceof UpgradeVG) {
                List<UpgradeVG> upgrades = mGoodsUpgrades.get(((UpgradeVG) vi).getGoodItemId());
                if (upgrades == null) {
                    upgrades = new ArrayList<UpgradeVG>();
                    mGoodsUpgrades.put(((UpgradeVG) vi).getGoodItemId(), upgrades);
                }
                upgrades.add((UpgradeVG) vi);
            }

            PurchaseType purchaseType = vi.getPurchaseType();
            if (purchaseType instanceof PurchaseWithMarket) {
                mPurchasableItems.put(((PurchaseWithMarket) purchaseType).getMarketItem()
                        .getProductId(), vi);
            }
        }

        for(NonConsumableItem vi : mNonConsumables) {
            mVirtualItems.put(vi.getItemId(), vi);

            PurchaseType purchaseType = vi.getPurchaseType();
            if (purchaseType instanceof PurchaseWithMarket) {
                mPurchasableItems.put(((PurchaseWithMarket) purchaseType).getMarketItem()
                        .getProductId(), vi);
            }
        }

        for(VirtualCategory category : mCategories) {
            for(String goodItemId : category.getGoodsItemIds()) {
                mGoodsCategories.put(goodItemId, category);
            }
        }

        save();
    }


    /** Private Members **/

    private static final String TAG = "SOOMLA StoreInfo"; //used for Log messages

    // convenient hash of virtual items
    private static HashMap<String, VirtualItem> mVirtualItems;

    // convenient hash of purchasable virtual items
    private static HashMap<String, PurchasableVirtualItem> mPurchasableItems;

    // convenient hash of goods-categories
    private static HashMap<String, VirtualCategory> mGoodsCategories;

    // convenient hash of good-upgrades
    private static HashMap<String, List<UpgradeVG>> mGoodsUpgrades;

    // list of virtual currencies
    private static List<VirtualCurrency> mCurrencies;

    // list of currency-packs
    private static List<VirtualCurrencyPack> mCurrencyPacks;

    // list of virtual goods
    private static List<VirtualGood> mGoods;

    // list of virtul categories
    private static List<VirtualCategory> mCategories;

    // list of non consumable items
    private static List<NonConsumableItem> mNonConsumables;
}