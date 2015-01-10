//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCVirtualCategory.h"

USING_NS_CC;

namespace soomla {
    CCVirtualCategory *CCVirtualCategory::create(CCString *name, CCArray *goodItemIds) {
        CCVirtualCategory *ret = new CCVirtualCategory();
        ret->autorelease();
        ret->init(name, goodItemIds);
        return ret;
    }

    CCVirtualCategory *CCVirtualCategory::createWithDictionary(CCDictionary *dict) {
        CCVirtualCategory *ret = new CCVirtualCategory();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCVirtualCategory::init(CCString *name, CCArray *goodItemIds) {
        setName(name);
        setGoodItemIds(goodItemIds);

        return true;
    }

    bool CCVirtualCategory::initWithDictionary(CCDictionary *dict) {
        fillNameFromDict(dict);
        fillGoodItemIdsFromDict(dict);

        return true;
    }

    CCDictionary *CCVirtualCategory::toDictionary() {
        CCDictionary *dict = CCDictionary::create();

        putNameToDict(dict);
        putGoodItemIdsToDict(dict);

        return dict;
    }

    CCVirtualCategory::~CCVirtualCategory() {
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mGoodItemIds);
    }
}
