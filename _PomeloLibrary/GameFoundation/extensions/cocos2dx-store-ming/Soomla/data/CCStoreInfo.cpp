//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCStoreInfo.h"
#include "../domain/virtualGoods/CCSingleUseVG.h"
#include "../domain/virtualGoods/CCEquippableVG.h"
#include "../domain/virtualGoods/CCSingleUsePackVG.h"
#include "../CCSoomlaNdkBridge.h"
#include "../CCStoreUtils.h"
#include "../domain/virtualCurrencies/CCVirtualCurrency.h"
#include "../domain/virtualCurrencies/CCVirtualCurrencyPack.h"
#include "../domain/CCNonConsumableItem.h"
#include "../domain/CCMarketItem.h"

namespace soomla {

#define TAG "SOOMLA StoreInfo"

#define SAFE_CREATE(__T__, __ret__, __retParams__)			\
	CCObject *_tempVi = createWithRetParams(__retParams__);	\
	__T__ __ret__ = dynamic_cast<__T__>(_tempVi);			\
	CC_ASSERT(__ret__);

    USING_NS_CC;

    static CCStoreInfo *s_SharedStoreInfo = NULL;

    CCStoreInfo *CCStoreInfo::sharedStoreInfo() {
        return s_SharedStoreInfo;
    }

    void CCStoreInfo::createShared(CCIStoreAssets *storeAssets) {
        CCStoreInfo *ret = new CCStoreInfo();
        if (ret->init(storeAssets)) {
            s_SharedStoreInfo = ret;
        } else {
            delete ret;
        }
    }

    bool CCStoreInfo::init(CCIStoreAssets *storeAssets) {
        CCArray *currenciesJSON = CCArray::create();
        {
            CCArray *currencies = storeAssets->getCurrencies();
            CCObject *obj;
            CCARRAY_FOREACH(currencies, obj) {
				currenciesJSON->addObject(((CCVirtualCurrency *)obj)->toDictionary());
			}
        }

        CCArray *packsJSON = CCArray::create();
        {
            CCArray *packs = storeAssets->getCurrencyPacks();
            CCObject *obj;
            CCARRAY_FOREACH(packs, obj) {
				packsJSON->addObject(((CCVirtualCurrencyPack *)obj)->toDictionary());
			}
        }

        CCArray *suGoods = CCArray::create();
        CCArray *ltGoods = CCArray::create();
        CCArray *eqGoods = CCArray::create();
        CCArray *upGoods = CCArray::create();
        CCArray *paGoods = CCArray::create();

        CCObject *obj;
        CCARRAY_FOREACH(storeAssets->getGoods(), obj) {
			if (dynamic_cast<CCSingleUseVG *>(obj)) {
				suGoods->addObject(((CCSingleUseVG *)obj)->toDictionary());
			} else if (dynamic_cast<CCEquippableVG *>(obj)) {
				eqGoods->addObject(((CCEquippableVG *)obj)->toDictionary());
			} else if (dynamic_cast<CCLifetimeVG *>(obj)) {
				ltGoods->addObject(((CCLifetimeVG *)obj)->toDictionary());
			} else if (dynamic_cast<CCSingleUsePackVG *>(obj)) {
				paGoods->addObject(((CCSingleUsePackVG *)obj)->toDictionary());
			} else if (dynamic_cast<CCUpgradeVG *>(obj)) {
				upGoods->addObject(((CCUpgradeVG *)obj)->toDictionary());
			}
		}

        CCDictionary *goodsJSON = CCDictionary::create();
        goodsJSON->setObject(suGoods, JSON_STORE_GOODS_SU);
        goodsJSON->setObject(ltGoods, JSON_STORE_GOODS_LT);
        goodsJSON->setObject(eqGoods, JSON_STORE_GOODS_EQ);
        goodsJSON->setObject(upGoods, JSON_STORE_GOODS_UP);
        goodsJSON->setObject(paGoods, JSON_STORE_GOODS_PA);

        CCArray *categoriesJSON = CCArray::create();
        {
            CCArray *categories = storeAssets->getCategories();
            CCObject *obj;
            CCARRAY_FOREACH(categories, obj) {
				categoriesJSON->addObject(((CCVirtualCategory *)obj)->toDictionary());
			}
        }


        CCArray *nonConsumablesJSON = CCArray::create();
        {
            CCArray *nonConsumables = storeAssets->getNonConsumableItems();
            CCObject *obj;
            CCARRAY_FOREACH(nonConsumables, obj) {
				nonConsumablesJSON->addObject(((CCNonConsumableItem *)obj)->toDictionary());
			}
        }

        CCDictionary *storeAssetsObj = CCDictionary::create();
        storeAssetsObj->setObject(categoriesJSON, JSON_STORE_CATEGORIES);
        storeAssetsObj->setObject(currenciesJSON, JSON_STORE_CURRENCIES);
        storeAssetsObj->setObject(packsJSON, JSON_STORE_CURRENCYPACKS);
        storeAssetsObj->setObject(goodsJSON, JSON_STORE_GOODS);
        storeAssetsObj->setObject(nonConsumablesJSON, JSON_STORE_NONCONSUMABLES);

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreAssets::init"), "method");
        params->setObject(CCInteger::create(storeAssets->getVersion()), "version");
        params->setObject(storeAssetsObj, "storeAssets");
        CCSoomlaNdkBridge::callNative(params, NULL);


        return true;
    }

    CCVirtualItem *CCStoreInfo::getItemByItemId(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
							   CCString::createWithFormat("Trying to fetch an item with itemId: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getItemByItemId"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);
        if (!*soomlaError) {
            SAFE_CREATE(CCVirtualItem *, ret, retParams);
            return ret;
        } else {
            return NULL;
        }
    }

    CCPurchasableVirtualItem *CCStoreInfo::getPurchasableItemWithProductId(char const *productId, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getPurchasableItemWithProductId"), "method");
        params->setObject(CCString::create(productId), "productId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);
        if (!soomlaError) {
            SAFE_CREATE(CCPurchasableVirtualItem *, ret, retParams);
            return ret;
        } else {
            return NULL;
        }
    }

    CCVirtualCategory *CCStoreInfo::getCategoryForVirtualGood(char const *goodItemId, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getCategoryForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, soomlaError);
        if (!soomlaError) {
            SAFE_CREATE(CCVirtualCategory *, ret, retParams);
            return ret;
        } else {
            return NULL;
        }
    }

    CCUpgradeVG *CCStoreInfo::getFirstUpgradeForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getFirstUpgradeForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
        SAFE_CREATE(CCUpgradeVG *, ret, retParams);
        return ret;
    }

    CCUpgradeVG *CCStoreInfo::getLastUpgradeForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getLastUpgradeForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
        SAFE_CREATE(CCUpgradeVG *, ret, retParams);
        return ret;
    }

    CCArray *CCStoreInfo::getUpgradesForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getUpgradesForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
		CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
		CCArray *retArray = (CCArray *)retParams->objectForKey("return");

        CCArray *ret = CCArray::create();
        CCObject *obj;
        CCARRAY_FOREACH(retArray, obj) {
			CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
			CC_ASSERT(dict);
			
			CCDictionary *container = CCDictionary::create();
			container->setObject(dict, "return");
			SAFE_CREATE(CCUpgradeVG *, item, container);
			ret->addObject(item);
		}
        return ret;
    }

    CCArray *CCStoreInfo::getVirtualCurrencies() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getVirtualCurrencies"), "method");
		CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
		CCArray *retArray = (CCArray *)retParams->objectForKey("return");

        CCArray *ret = CCArray::create();
        CCObject *obj;
        CCARRAY_FOREACH(retArray, obj) {
			CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
			CC_ASSERT(dict);
			
			CCDictionary *container = CCDictionary::create();
			container->setObject(dict, "return");
			SAFE_CREATE(CCVirtualCurrency *, item, container);
			ret->addObject(item);
		}
        return ret;
    }

    CCArray *CCStoreInfo::getVirtualGoods() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getVirtualGoods"), "method");
		CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
		CCArray *retArray = (CCArray *)retParams->objectForKey("return");

        CCArray *ret = CCArray::create();
        CCObject *obj;
        CCARRAY_FOREACH(retArray, obj) {
			CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
			CC_ASSERT(dict);
			
			CCDictionary *container = CCDictionary::create();
			container->setObject(dict, "return");
			SAFE_CREATE(CCVirtualGood *, item, container);
			ret->addObject(item);
		}
        return ret;
    }

    CCArray *CCStoreInfo::getVirtualCurrencyPacks() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getVirtualCurrencyPacks"), "method");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
		CCArray *retArray = (CCArray *)retParams->objectForKey("return");
		
        CCArray *ret = CCArray::create();
        CCObject *obj;
        CCARRAY_FOREACH(retArray, obj) {
			CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
			CC_ASSERT(dict);

			CCDictionary *container = CCDictionary::create();
			container->setObject(dict, "return");
			SAFE_CREATE(CCVirtualCurrencyPack *, item, container);
			ret->addObject(item);
		}
        return ret;
    }

    CCArray *CCStoreInfo::getNonConsumableItems() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getNonConsumableItems"), "method");
		CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
		CCArray *retArray = (CCArray *)retParams->objectForKey("return");
		
		CCArray *ret = CCArray::create();
		CCObject *obj;
		CCARRAY_FOREACH(retArray, obj) {
			CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
			CC_ASSERT(dict);

			CCDictionary *container = CCDictionary::create();
			container->setObject(dict, "return");
			SAFE_CREATE(CCNonConsumableItem *, item, container);
			ret->addObject(item);
		}
		return ret;
    }

    CCArray *CCStoreInfo::getVirtualCategories() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getVirtualCategories"), "method");
		CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
		CCArray *retArray = (CCArray *)retParams->objectForKey("return");
		
		CCArray *ret = CCArray::create();
		CCObject *obj;
		CCARRAY_FOREACH(retArray, obj) {
			CCDictionary *dict = dynamic_cast<CCDictionary *>(obj);
			CC_ASSERT(dict);

			CCDictionary *container = CCDictionary::create();
			container->setObject(dict, "return");
			SAFE_CREATE(CCVirtualCategory *, item, container);
			ret->addObject(item);
		}
		return ret;
    }

    CCObject *CCStoreInfo::createWithRetParams(CCDictionary *retParams) {
        CCDictionary *retValue = dynamic_cast<CCDictionary *>(retParams->objectForKey("return"));
        CC_ASSERT(retValue);
        CCString *className = dynamic_cast<CCString *>(retValue->objectForKey("className"));
		CCDictionary *item = dynamic_cast<CCDictionary *>(retValue->objectForKey("item"));
        CC_ASSERT(item);
		
        if (className->compare("VirtualItem") == 0) {
            return CCVirtualItem::createWithDictionary(item);
        }
        else if (className->compare("MarketItem") == 0) {
            return CCMarketItem::createWithDictionary(item);
        }
        else if (className->compare("NonConsumableItem") == 0) {
            return CCNonConsumableItem::createWithDictionary(item);
        }
        else if (className->compare("PurchasableVirtualItem") == 0) {
            return CCPurchasableVirtualItem::createWithDictionary(item);
        }
        else if (className->compare("VirtualCategory") == 0) {
            return CCVirtualCategory::createWithDictionary(item);
        }
        else if (className->compare("VirtualCurrency") == 0) {
            return CCVirtualCurrency::createWithDictionary(item);
        }
        else if (className->compare("VirtualCurrencyPack") == 0) {
            return CCVirtualCurrencyPack::createWithDictionary(item);
        }
        else if (className->compare("EquippableVG") == 0) {
            return CCEquippableVG::createWithDictionary(item);
        }
        else if (className->compare("LifetimeVG") == 0) {
            return CCLifetimeVG::createWithDictionary(item);
        }
        else if (className->compare("SingleUsePackVG") == 0) {
            return CCSingleUsePackVG::createWithDictionary(item);
        }
        else if (className->compare("SingleUseVG") == 0) {
            return CCSingleUseVG::createWithDictionary(item);
        }
        else if (className->compare("UpgradeVG") == 0) {
            return CCUpgradeVG::createWithDictionary(item);
        }
        else if (className->compare("VirtualGood") == 0) {
            return CCVirtualGood::createWithDictionary(item);
        } else {
            CC_ASSERT(false);
            return NULL;
        }
    }

#undef SAFE_CREATE

}

