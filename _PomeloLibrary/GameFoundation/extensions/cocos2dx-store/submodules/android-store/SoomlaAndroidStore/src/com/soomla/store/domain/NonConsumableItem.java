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

package com.soomla.store.domain;

import com.soomla.store.StoreUtils;
import com.soomla.store.data.StorageManager;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * A representation of a non-consumable item in the Market. These kinds of items are bought by the
 * user once and kept for him/her forever.
 * 
 * NOTE: Don't be confused: this is not a Lifetime <code>VirtualGood</code>, it's a MANAGED item in
 * the Market. This means that the product can be purchased only once per user (such as a new level
 * in a game), and is remembered by the Market (can be restored if this application is uninstalled
 * and then re-installed).
 * If you want to make a <code>LifetimeVG</code> available for purchase in the market (purchase with
 * real money $$), you will need to declare it as a <code>NonConsumableItem</code>.
 *
 * Inheritance: NonConsumableItem >
 * {@link com.soomla.store.domain.PurchasableVirtualItem} >
 * {@link com.soomla.store.domain.VirtualItem}
 */
public class NonConsumableItem extends PurchasableVirtualItem {

    /**
     * Constructor
     *
     * @param mName see parent
     * @param mDescription see parent
     * @param mItemId see parent
     * @param purchaseType see parent
     */
    public NonConsumableItem(String mName, String mDescription, String mItemId,
                             PurchaseWithMarket purchaseType) {
        super(mName, mDescription, mItemId, purchaseType);
    }

    /**
     * Constructor
     *
     * see parent
     */
    public NonConsumableItem(JSONObject jsonObject) throws JSONException {
        super(jsonObject);
    }

    /**
     * @{inheritDoc}
     */
    @Override
    public JSONObject toJSONObject(){
        return super.toJSONObject();
    }

    /**
     * @{inheritDoc}
     */
    @Override
    public int give(int amount, boolean notify) {
        return StorageManager.getNonConsumableItemsStorage().add(this) ? 1 : 0;
    }

    /**
     * @{inheritDoc}
     */
    @Override
    public int take(int amount, boolean notify) {
        return StorageManager.getNonConsumableItemsStorage().remove(this) ? 1 : 0;
    }

    /**
     * Determines if user is in a state that allows him/her to buy a <code>NonConsumableItem</code>
     * by checking if the user already owns such an item. If so, he/she cannot purchase this item
     * again because <code>NonConsumableItems</code> can only be purchased once!
     *
     * @return True if the user does NOT own such an item, False otherwise.
     */
    @Override
    protected boolean canBuy() {
        if (StorageManager.getNonConsumableItemsStorage().nonConsumableItemExists(this)) {
            StoreUtils.LogDebug(TAG,
                    "You can't buy a NonConsumableItem that was already given to the user.");
            return false;
        }
        return true;
    }

    /**
     * @{inheritDoc}
     */
    @Override
    public int resetBalance(int balance, boolean notify) {
        if (balance > 0) {
            return StorageManager.getNonConsumableItemsStorage().add(this) ? 1 : 0;
        } else {
            return StorageManager.getNonConsumableItemsStorage().remove(this) ? 1 : 0;
        }
    }

    /** Private members **/

    private static final String TAG = "SOOMLA NonConsumableItem"; //used for Log messages
}
