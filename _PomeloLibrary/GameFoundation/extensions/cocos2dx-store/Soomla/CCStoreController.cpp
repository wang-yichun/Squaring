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

// Created by Fedor Shubin on 5/20/13.

#include "CCStoreController.h"
#include "CCSoomla.h"
#include "CCStoreUtils.h"
#include "CCSoomlaNdkBridge.h"
#include "data/CCStoreInfo.h"

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCStoreController *s_SharedStoreController = NULL;

    CCStoreController *CCStoreController::sharedStoreController() {
        if (!s_SharedStoreController)
        {
            s_SharedStoreController = new CCStoreController();
            s_SharedStoreController->retain();
        }
        return s_SharedStoreController;
    }

    void CCStoreController::initShared(CCIStoreAssets *storeAssets, CCDictionary *storeParams) {
        CCStoreController *storeController = CCStoreController::sharedStoreController();
        if (!storeController->init(storeAssets, storeParams)) {
            exit(1);
        }
    }

    CCStoreController::CCStoreController() {
        this->mSoomSec = NULL;
    }

    CCStoreController::~CCStoreController() {

    }

    bool CCStoreController::init(CCIStoreAssets *storeAssets, CCDictionary *storeParams) {
        CCString *customSecret = dynamic_cast<CCString *>(storeParams->objectForKey("customSecret"));
        CCString *soomSec = mSoomSec;
        if (soomSec == NULL) {
            soomSec = dynamic_cast<CCString *>(storeParams->objectForKey("soomSec"));
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CCString *androidPublicKey = dynamic_cast<CCString *>(storeParams->objectForKey("androidPublicKey"));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCBool *SSV = dynamic_cast<CCBool *>(storeParams->objectForKey("SSV"));
#endif

        if (customSecret == NULL) customSecret = CCString::create("");
        if (soomSec      == NULL) soomSec      = CCString::create("");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (androidPublicKey == NULL) androidPublicKey = CCString::create("");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (SSV == NULL) SSV = CCBool::create(false);
#endif

        // Redundancy checking. Most JS libraries don't do this. I hate it when they don't do this. Do this.
        CCDictElement* el = NULL;
        CCDICT_FOREACH(storeParams, el) {
            std::string key = el->getStrKey();
            if (!(
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                  key.compare("androidPublicKey") == 0 ||
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                  key.compare("SSV") == 0 ||
#endif
                  key.compare("customSecret") == 0 ||
                  key.compare("soomSec")      == 0 )) {
                CCString *message =
                    CCString::createWithFormat("WARNING!! Possible typo in member of storeParams: %s", key.c_str());
                CCStoreUtils::logError(TAG, message->getCString());
            }
        }


        if (customSecret->length() == 0 || soomSec->length() == 0) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX MISSING customSecret or soomSec !!! Stopping here !!");
            return false;
        }

        if (customSecret->compare(SOOMLA_ONLY_ONCE_DEFAULT) == 0 ||
            soomSec->compare(SOOMLA_ONLY_ONCE_DEFAULT) == 0) {

            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX You have to change customSecret and soomSec !!! Stopping here !!");
            return false;
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (androidPublicKey->length() == 0) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX MISSING publickKey !!! Stopping here !!");
            return false;
        }

        if (androidPublicKey->compare(SOOMLA_AND_PUB_KEY_DEFAULT) == 0) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX You have to change android publicKey !!! Stopping here !!");
            return false;
        }

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setAndroidPublicKey"), "method");
            params->setObject(androidPublicKey, "androidPublicKey");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }
#endif

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSoomSec"), "method");
            params->setObject(soomSec, "soomSec");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSSV"), "method");
            params->setObject(SSV, "ssv");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }
#endif

        CCStoreInfo::createShared(storeAssets);

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::init"), "method");
            params->setObject(customSecret, "customSecret");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            params->setObject(androidPublicKey, "androidPublicKey");
#endif
            CCSoomlaError *soomlaError = NULL;
            CCSoomlaNdkBridge::callNative(params, &soomlaError);

            if (soomlaError) {
                return false;
            }
        }

        return true;
    }

    void CCStoreController::setupSoomSec() {
        CC_ASSERT(mSoomSec);
        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSoomSec"), "method");
            params->setObject(mSoomSec, "soomSec");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }
    }

    void CCStoreController::buyMarketItem(const char *productId, const char *payload, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::buyMarketItem"), "method");
        params->setObject(CCString::create(productId), "productId");
        // NOTE: payload is not supported on iOS !
        params->setObject(CCString::create(payload), "payload");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    void CCStoreController::restoreTransactions() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::restoreTransactions"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    void CCStoreController::refreshInventory() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::refreshInventory"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool CCStoreController::transactionsAlreadyRestored() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::transactionsAlreadyRestored"), "method");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void CCStoreController::refreshMarketItemsDetails(CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::refreshMarketItemsDetails"), "method");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void CCStoreController::startIabServiceInBg() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::startIabServiceInBg"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    void CCStoreController::stopIabServiceInBg() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::stopIabServiceInBg"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }
#endif
}
