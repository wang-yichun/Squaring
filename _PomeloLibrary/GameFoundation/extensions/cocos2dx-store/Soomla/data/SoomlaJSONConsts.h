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

//  Created by Igor Yegoroff on 5/17/13.


#ifndef __cocos2dx_store__SoomlaJSONConsts__
#define __cocos2dx_store__SoomlaJSONConsts__

/**
 This class contains all static const String names of the keys/vals in the
 JSON being parsed all around the SDK.
 */
namespace soomla {
    
    extern char const* JSON_STORE_CURRENCIES;
    extern char const* JSON_STORE_CURRENCYPACKS;
    extern char const* JSON_STORE_GOODS;
    extern char const* JSON_STORE_CATEGORIES;
    extern char const* JSON_STORE_NONCONSUMABLES;
    extern char const* JSON_STORE_GOODS_SU;
    extern char const* JSON_STORE_GOODS_PA;
    extern char const* JSON_STORE_GOODS_UP;
    extern char const* JSON_STORE_GOODS_LT;
    extern char const* JSON_STORE_GOODS_EQ;
    
    extern char const* JSON_ITEM_NAME;
    extern char const* JSON_ITEM_DESCRIPTION;
    extern char const* JSON_ITEM_ITEMID;
    
    extern char const* JSON_CATEGORY_NAME;
    extern char const* JSON_CATEGORY_GOODSITEMIDS;
    
    extern char const* JSON_MARKETITEM_PRODUCT_ID;
    extern char const* JSON_MARKETITEM_ANDROID_ID;
    extern char const* JSON_MARKETITEM_IOS_ID;

    extern char const* JSON_MARKETITEM_CONSUMABLE;
    extern char const* JSON_MARKETITEM_PRICE;
    
    extern char const* JSON_EQUIPPABLE_EQUIPPING;
    
    extern char const* JSON_VGP_GOOD_ITEMID;
    extern char const* JSON_VGP_GOOD_AMOUNT;
    
    extern char const* JSON_VGU_GOOD_ITEMID;
    extern char const* JSON_VGU_PREV_ITEMID;
    extern char const* JSON_VGU_NEXT_ITEMID;
    
    extern char const* JSON_CURRENCYPACK_CURRENCYAMOUNT;
    extern char const* JSON_CURRENCYPACK_CURRENCYITEMID;
    
    extern char const* JSON_PURCHASABLE_ITEM;
    
    extern char const* JSON_PURCHASE_TYPE;
    extern char const* JSON_PURCHASE_TYPE_MARKET;
    extern char const* JSON_PURCHASE_TYPE_VI;
    
    extern char const* JSON_PURCHASE_MARKET_ITEM;
    
    extern char const* JSON_PURCHASE_VI_ITEMID;
    extern char const* JSON_PURCHASE_VI_AMOUNT;
}

#endif /* defined(__cocos2dx_store__SoomlaJSONConsts__) */
