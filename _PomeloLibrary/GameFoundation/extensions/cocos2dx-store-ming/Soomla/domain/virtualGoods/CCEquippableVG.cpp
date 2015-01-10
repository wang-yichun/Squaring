//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCEquippableVG.h"

USING_NS_CC;

#define EQUIPPING_MODEL_LOCAL "local"
#define EQUIPPING_MODEL_CATEGORY "category"
#define EQUIPPING_MODEL_GLOBAL "global"

namespace soomla {

    CCEquippableVG *CCEquippableVG::create(CCInteger *equippingModel, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCEquippableVG *ret = new CCEquippableVG();
        ret->autorelease();
        ret->init(equippingModel, name, description, itemId, purchaseType);
        return ret;
    }

    CCEquippableVG *CCEquippableVG::createWithDictionary(CCDictionary *dict) {
        CCEquippableVG *ret = new CCEquippableVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCEquippableVG::init(CCInteger *equippingModel, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        bool res = CCPurchasableVirtualItem::init(name, description, itemId, purchaseType);
        if (res) {
            setEquippingModel(equippingModel);
            return true;
        } else {
            return false;
        }
    }

    bool CCEquippableVG::initWithDictionary(CCDictionary *dict) {
        bool res = CCPurchasableVirtualItem::initWithDictionary(dict);
        if (res) {
            fillEquippingModelFromDict(dict);

            return true;
        } else {
            return false;
        }
    }

    CCDictionary *CCEquippableVG::toDictionary() {
        CCDictionary *dict = CCPurchasableVirtualItem::toDictionary();

        putEquippingModelToDict(dict);

        return dict;
    }

    void CCEquippableVG::fillEquippingModelFromDict(CCDictionary *dict) {
        CCString*equippingModelStr = dynamic_cast<CCString *>(dict->objectForKey(JSON_EQUIPPABLE_EQUIPPING));
        CCAssert(equippingModelStr != NULL, "invalid object type in dictionary");
        if (equippingModelStr->compare(EQUIPPING_MODEL_LOCAL) == 0) {
            setEquippingModel(CCInteger::create(kLocal));
        }
        else if (equippingModelStr->compare(EQUIPPING_MODEL_CATEGORY) == 0) {
            setEquippingModel(CCInteger::create(kCategory));
        }
        else if (equippingModelStr->compare(EQUIPPING_MODEL_GLOBAL) == 0) {
            setEquippingModel(CCInteger::create(kGlobal));
        } else {
            CC_ASSERT(false);
        }
    }

    void CCEquippableVG::putEquippingModelToDict(CCDictionary *dict) {
        EquippingModel equippingModel = (EquippingModel) getEquippingModel()->getValue();
        CCString *strEquippingModel;
        switch (equippingModel) {
            case kLocal: {
                strEquippingModel = CCString::create(EQUIPPING_MODEL_LOCAL);
                break;
            }
            case kCategory: {
                strEquippingModel = CCString::create(EQUIPPING_MODEL_CATEGORY);
                break;
            }
            case kGlobal: {
                strEquippingModel = CCString::create(EQUIPPING_MODEL_GLOBAL);
                break;
            }
            default: {
                CC_ASSERT(false);
                strEquippingModel = CCString::create("ERROR");
            }
        }
        dict->setObject(strEquippingModel, JSON_EQUIPPABLE_EQUIPPING);
    }

    CCEquippableVG::~CCEquippableVG() {
        CC_SAFE_RELEASE(mEquippingModel);
    }
}
