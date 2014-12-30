/*
 * Copyright (C) 2012 Soomla Inc.
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

#include "cocos2dx_StoreInventory.h"
#include "JniHelpers.h"


void cocos2dx_StoreInventory::buy(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
	JniHelpers::jniCommonVoidCall(
		"buy", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		itemId.c_str()
	); 
}

int cocos2dx_StoreInventory::getItemBalance(string itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"getItemBalance", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		itemId.c_str()
	); 
}

void cocos2dx_StoreInventory::giveItem(string itemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"giveItem", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		itemId.c_str(),
		amount
	); 
}

void cocos2dx_StoreInventory::takeVirtualItem(string itemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"takeItem", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		itemId.c_str(),
		amount
	); 
}

void cocos2dx_StoreInventory::equipGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"equipGood", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	); 
}

void cocos2dx_StoreInventory::unEquipGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"unEquipGood", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	); 
}

bool cocos2dx_StoreInventory::isGoodEquipped(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonBoolCall(
		"isGoodEquipped", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	); 
}

int cocos2dx_StoreInventory::getGoodUpgradeLevel(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&)  {
	return JniHelpers::jniCommonIntCall(
		"getGoodUpgradeLevel", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	);
}

string cocos2dx_StoreInventory::getGoodCurrentUpgrade(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonStringCall(
		"getGoodCurrentUpgrade", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	);
}

void cocos2dx_StoreInventory::upgradeVirtualGood(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
	JniHelpers::jniCommonVoidCall(
		"upgradeVirtualGood", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	);
}

void cocos2dx_StoreInventory::removeUpgrades(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&)  {
	JniHelpers::jniCommonVoidCall(
		"removeUpgrades", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		goodItemId.c_str()
	);
}

bool cocos2dx_StoreInventory::nonConsumableItemExists(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonBoolCall(
		"nonConsumableItemExists", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		nonConsItemId.c_str()
	);
}

void cocos2dx_StoreInventory::addNonConsumableItem(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&)  {
	JniHelpers::jniCommonVoidCall(
		"addNonConsumableItem", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		nonConsItemId.c_str()
	);
}

void cocos2dx_StoreInventory::removeNonConsumableItem(string nonConsItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"removeNonConsumableItem", 
		"com/soomla/cocos2dx/store/StoreInventoryBridge", 
		nonConsItemId.c_str()
	);
}

