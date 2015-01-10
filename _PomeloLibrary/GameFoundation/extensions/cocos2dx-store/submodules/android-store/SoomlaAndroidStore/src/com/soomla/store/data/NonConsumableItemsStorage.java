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

import com.soomla.store.StoreUtils;
import com.soomla.store.domain.NonConsumableItem;

/**
 * This class provides basic storage operations on the Market's MANAGED items.
 */
public class NonConsumableItemsStorage {

    /**
     * Constructor
     */
    public NonConsumableItemsStorage() {
    }

    /**
     * Checks if the given {@link NonConsumableItem} exists.
     *
     * @param nonConsumableItem the non-consumable to check if exists.
     * @return true if the given item exists, false otherwise.
     */
    public boolean nonConsumableItemExists(NonConsumableItem nonConsumableItem){

        StoreUtils.LogDebug(TAG, "Checking if the given MANAGED item exists.");

        String itemId = nonConsumableItem.getItemId();
        String key = KeyValDatabase.keyNonConsExists(itemId);

        String val = StorageManager.getKeyValueStorage().getValue(key);

        return val != null;
    }

    /**
     * Adds the given non-consumable item to the storage.
     *
     * @param nonConsumableItem the required non-consumable item.
     * @return true
     */
    public boolean add(NonConsumableItem nonConsumableItem){
        StoreUtils.LogDebug(TAG, "Adding " + nonConsumableItem.getItemId());

        String itemId = nonConsumableItem.getItemId();
        String key = KeyValDatabase.keyNonConsExists(itemId);

        StorageManager.getKeyValueStorage().setValue(key, "");

        return true;
    }

    /**
     * Removes the given non-consumable item from the storage.
     *
     * @param nonConsumableItem the required non-consumable item.
     * @return false
     */
    public boolean remove(NonConsumableItem nonConsumableItem){
        StoreUtils.LogDebug(TAG, "Removing " + nonConsumableItem.getName());

        String itemId = nonConsumableItem.getItemId();
        String key = KeyValDatabase.keyNonConsExists(itemId);

        StorageManager.getKeyValueStorage().deleteKeyValue(key);

        return false;
    }


    /** Private Members **/

    private static final String TAG = "SOOMLA NonConsumableItemsStorage"; //used for Log messages
}
