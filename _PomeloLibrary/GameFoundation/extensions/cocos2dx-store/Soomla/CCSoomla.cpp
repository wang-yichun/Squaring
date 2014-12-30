/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCSoomla.h"
#include "data/CCStoreInfo.h"
#include "CCStoreUtils.h"
#include "domain/CCMarketItem.h"
#include "PurchaseTypes/CCPurchaseWithMarket.h"

namespace soomla {

    USING_NS_CC;

    static CCSoomla *s_SharedSoomla = NULL;

    CCSoomla *CCSoomla::sharedSoomla() {
        if (!s_SharedSoomla) {
            s_SharedSoomla = new CCSoomla();
            s_SharedSoomla->init();
        }

        return s_SharedSoomla;
    }

    CCSoomla::~CCSoomla() {
    }

    bool CCSoomla::init() {
		return true;
    }

	void CCSoomla::addEventHandler(CCEventHandler *eventHandler) {
		mEventHandlers.addObject(eventHandler);
        eventHandler->retain();
	}

	void CCSoomla::removeEventHandler(CCEventHandler *eventHandler) {
		mEventHandlers.removeObject(eventHandler);
        eventHandler->release();
	}

    void CCSoomla::easyNDKCallBack(CCDictionary *parameters) {
        CCString *methodName = dynamic_cast<CCString *>(parameters->objectForKey("method"));
        CC_ASSERT(methodName);
		if (methodName->compare("CCEventHandler::onBillingNotSupported") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onBillingNotSupported();
			}
        }
        else if (methodName->compare("CCEventHandler::onBillingSupported") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onBillingSupported();
			}
        }
        else if (methodName->compare("CCEventHandler::onCurrencyBalanceChanged") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCInteger *balance = (CCInteger *)(parameters->objectForKey("balance"));
            CCInteger *amountAdded = (CCInteger *)(parameters->objectForKey("amountAdded"));
            CCSoomlaError *soomlaError = NULL;
            CCVirtualCurrency *virtualCurrency =
				dynamic_cast<CCVirtualCurrency *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onCurrencyBalanceChanged", soomlaError);
                return;
            }
            CC_ASSERT(virtualCurrency);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onCurrencyBalanceChanged(virtualCurrency, balance->getValue(), amountAdded->getValue());
			}
        }
        else if (methodName->compare("CCEventHandler::onGoodBalanceChanged") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCInteger *balance = (CCInteger *)(parameters->objectForKey("balance"));
            CCInteger *amountAdded = (CCInteger *)(parameters->objectForKey("amountAdded"));
            CCSoomlaError *soomlaError = NULL;
            CCVirtualGood *virtualGood =
				dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodBalanceChanged", soomlaError);
                return;
            }
            CC_ASSERT(virtualGood);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onGoodBalanceChanged(virtualGood, balance->getValue(), amountAdded->getValue());
			}
        }
        else if (methodName->compare("CCEventHandler::onGoodEquipped") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCEquippableVG *equippableVG =
				dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodEquipped", soomlaError);
                return;
            }
            CC_ASSERT(equippableVG);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onGoodEquipped(equippableVG);
			}
        }
        else if (methodName->compare("CCEventHandler::onGoodUnEquipped") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCEquippableVG *equippableVG =
				dynamic_cast<CCEquippableVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodUnEquipped", soomlaError);
                return;
            }
            CC_ASSERT(equippableVG);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onGoodUnEquipped(equippableVG);
			}
        }
        else if (methodName->compare("CCEventHandler::onGoodUpgrade") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCString *vguItemId = (CCString *)(parameters->objectForKey("vguItemId"));

            CCSoomlaError *soomlaError;

            soomlaError = NULL;
            CCVirtualGood *virtualGood =
				dynamic_cast<CCVirtualGood *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodUpgrade", soomlaError);
                return;
            }
            CC_ASSERT(virtualGood);

            soomlaError = NULL;
            CCUpgradeVG *upgradeVG =
				dynamic_cast<CCUpgradeVG *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(vguItemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodUpgrade", soomlaError);
                return;
            }
            CC_ASSERT(upgradeVG);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onGoodUpgrade(virtualGood, upgradeVG);
			}
        }
        else if (methodName->compare("CCEventHandler::onItemPurchased") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem =
				dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onItemPurchased", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onItemPurchased(purchasableVirtualItem);
			}
        }
        else if (methodName->compare("CCEventHandler::onItemPurchaseStarted") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
																										CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onItemPurchased", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onItemPurchaseStarted(purchasableVirtualItem);
			}
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchaseCancelled") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem =
				dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketPurchaseCancelled", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onMarketPurchaseCancelled(purchasableVirtualItem);
			}
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchase") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem =
				dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketPurchase", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            CCString *token = (CCString *)(parameters->objectForKey("token"));
            CCString *payload = (CCString *)(parameters->objectForKey("payload"));
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
                h->onMarketPurchase(purchasableVirtualItem, token, payload);
			}
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchaseStarted") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem =
				dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketPurchaseStarted", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onMarketPurchaseStarted(purchasableVirtualItem);
			}
        }
        else if (methodName->compare("CCEventHandler::onMarketItemsRefreshed") == 0) {
            CCArray *marketItems = (CCArray *)(parameters->objectForKey("marketItems"));

            CCSoomlaError *soomlaError = NULL;
            CCDictionary *marketItem = NULL;
            for (unsigned int i = 0; i < marketItems->count(); i++) {
                marketItem = dynamic_cast<CCDictionary *>(marketItems->objectAtIndex(i));
                CC_ASSERT(marketItem);
                CCString *productId = dynamic_cast<CCString *>(marketItem->objectForKey("productId"));
                CCString *marketPrice = dynamic_cast<CCString *>(marketItem->objectForKey("marketPrice"));
                CCString *marketTitle = dynamic_cast<CCString *>(marketItem->objectForKey("marketTitle"));
                CCString *marketDescription = dynamic_cast<CCString *>(marketItem->objectForKey("marketDesc"));

                CCPurchasableVirtualItem *pvi = CCStoreInfo::sharedStoreInfo()->getPurchasableItemWithProductId(
                        productId->getCString(), &soomlaError);
                if (soomlaError) {
                    CCStoreUtils::logException("CCEventHandler::onMarketItemsRefreshed", soomlaError);
                    return;
                }
                CC_ASSERT(pvi);

                CCPurchaseWithMarket *purchaseWithMarket = dynamic_cast<CCPurchaseWithMarket *>(pvi->getPurchaseType());
                CC_ASSERT(purchaseWithMarket);
                CCMarketItem *mi = purchaseWithMarket->getMarketItem();
                mi->setMarketPrice(marketPrice);
                mi->setMarketTitle(marketTitle);
                mi->setMarketDescription(marketDescription);
            }

            CCSetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
                h->onMarketItemsRefreshed();
            }
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchaseVerification") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem =
                    dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onPurchaseVerification", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            CCSetIterator i;
            for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
                CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
                h->onMarketPurchaseVerification(purchasableVirtualItem);
            }
        }
        else if (methodName->compare("CCEventHandler::onRestoreTransactionsFinished") == 0) {
            CCBool *success = (CCBool *)(parameters->objectForKey("success"));
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
                h->onRestoreTransactionsFinished(success->getValue());
			}
        }
        else if (methodName->compare("CCEventHandler::onRestoreTransactionsStarted") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onRestoreTransactionsStarted();
			}
        }
        else if (methodName->compare("CCEventHandler::onUnexpectedErrorInStore") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onUnexpectedErrorInStore();
			}
		} else if (methodName->compare("CCEventHandler::onStoreControllerInitialized") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onStoreControllerInitialized();
			}
		}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        else if (methodName->compare("CCEventHandler::onMarketRefund") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem =
            dynamic_cast<CCPurchasableVirtualItem *>(CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketRefund", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onMarketRefund(purchasableVirtualItem);
			}
        }
        else if (methodName->compare("CCEventHandler::onIabServiceStarted") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onIabServiceStarted();
			}
        }
        else if (methodName->compare("CCEventHandler::onIabServiceStopped") == 0) {
			CCSetIterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				CCEventHandler *h = dynamic_cast<CCEventHandler *>(*i);
				h->onIabServiceStopped();
			}
        }
#endif
		else {
            CC_ASSERT(false);
        }
    }
}
