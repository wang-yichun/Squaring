//
// Created by Fedor Shubin on 5/21/13.
//

#include "CCStoreInventory.h"
#include "CCStoreUtils.h"
#include "CCSoomlaNdkBridge.h"

namespace soomla {
#define TAG "SOOMLA StoreInventory"

    USING_NS_CC;

    static CCStoreInventory *s_SharedStoreInventory = NULL;

    CCStoreInventory *CCStoreInventory::sharedStoreInventory() {
        return s_SharedStoreInventory;
    }

    CCStoreInventory::CCStoreInventory() {

    }

    CCStoreInventory::~CCStoreInventory() {

    }

    bool CCStoreInventory::init() {
        return true;
    }

    void CCStoreInventory::buyItem(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling buyItem with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::buyItem"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    int CCStoreInventory::getItemBalance(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling getItemBalance with: %s", itemId)->getCString());
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::getItemBalance"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);

        if (retParams == NULL) {
        	return 0;
        }

		CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
		if (retValue) {
			return retValue->getValue();
		} else {
			return 0;
		}
    }

    void CCStoreInventory::giveItem(char const *itemId, int amount, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG, CCString::createWithFormat(
                "SOOMLA/COCOS2DX Calling giveItem with itemId: %s and amount %d", itemId, amount)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::giveItem"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        params->setObject(CCInteger::create(amount), "amount");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    void CCStoreInventory::takeItem(char const *itemId, int amount, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG, CCString::createWithFormat(
                "SOOMLA/COCOS2DX Calling takeItem with itemId: %s and amount %d", itemId, amount)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::takeItem"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        params->setObject(CCInteger::create(amount), "amount");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    void CCStoreInventory::equipVirtualGood(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling equipVirtualGood with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::equipVirtualGood"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
   }

    void CCStoreInventory::unEquipVirtualGood(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling unEquipVirtualGood with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::unEquipVirtualGood"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    bool CCStoreInventory::isVirtualGoodEquipped(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling isVirtualGoodEquipped with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::isVirtualGoodEquipped"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);

        if (retParams == NULL) {
        	return false;
        }

		CCBool *retValue = (CCBool *) retParams->objectForKey("return");
		if (retValue) {
			return retValue->getValue();
		} else {
			return false;
		}
    }

    int CCStoreInventory::getGoodUpgradeLevel(char const *goodItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling getGoodUpgradeLevel with: %s", goodItemId)->getCString());
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::getGoodUpgradeLevel"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);

        if (retParams == NULL) {
        	return 0;
        }

		CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
		if (retValue) {
			return retValue->getValue();
		} else {
			return 0;
		}
    }

    std::string CCStoreInventory::getGoodCurrentUpgrade(char const *goodItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling getGoodCurrentUpgrade with: %s", goodItemId)->getCString());
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::getGoodCurrentUpgrade"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);

        if (retParams == NULL) {
        	return "";
        }

		CCString *retValue = (CCString *) retParams->objectForKey("return");
		if (retValue) {
			return retValue->getCString();
		} else {
			return "";
		}
    }

    void CCStoreInventory::upgradeGood(char const *goodItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling upgradeGood with: %s", goodItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::upgradeGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    void CCStoreInventory::removeGoodUpgrades(char const *goodItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling removeGoodUpgrades with: %s", goodItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::removeGoodUpgrades"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    bool CCStoreInventory::nonConsumableItemExists(char const *nonConsItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling nonConsumableItemExists with: %s", nonConsItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::nonConsumableItemExists"), "method");
        params->setObject(CCString::create(nonConsItemId), "nonConsItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);

        if (retParams == NULL) {
        	return false;
        }

		CCBool *retValue = (CCBool *) retParams->objectForKey("return");
		if (retValue) {
			return retValue->getValue();
		} else {
			return false;
		}
    }

    void CCStoreInventory::addNonConsumableItem(char const *nonConsItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling addNonConsumableItem with: %s", nonConsItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::addNonConsumableItem"), "method");
        params->setObject(CCString::create(nonConsItemId), "nonConsItemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
   }

    void CCStoreInventory::removeNonConsumableItem(char const *nonConsItemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/COCOS2DX Calling removeNonConsumableItem with: %s", nonConsItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::removeNonConsumableItem"), "method");
        params->setObject(CCString::create(nonConsItemId), "nonConsItemId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }
}
