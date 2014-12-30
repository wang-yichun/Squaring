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

#include "SoomlaJSONConsts.h"

namespace soomla {
    char const* JSON_STORE_CURRENCIES         = "currencies";
    char const* JSON_STORE_CURRENCYPACKS      = "currencyPacks";
    char const* JSON_STORE_GOODS              = "goods";
    char const* JSON_STORE_CATEGORIES         = "categories";
    char const* JSON_STORE_NONCONSUMABLES     = "nonConsumables";
    char const* JSON_STORE_GOODS_SU           = "singleUse";
    char const* JSON_STORE_GOODS_PA           = "goodPacks";
    char const* JSON_STORE_GOODS_UP           = "goodUpgrades";
    char const* JSON_STORE_GOODS_LT           = "lifetime";
    char const* JSON_STORE_GOODS_EQ           = "equippable";
    
    char const* JSON_ITEM_NAME                = "name";
    char const* JSON_ITEM_DESCRIPTION         = "description";
    char const* JSON_ITEM_ITEMID              = "itemId";
    
    char const* JSON_CATEGORY_NAME            = "name";
    char const* JSON_CATEGORY_GOODSITEMIDS    = "goods_itemIds";
    
    char const* JSON_MARKETITEM_PRODUCT_ID    = "productId";
    char const* JSON_MARKETITEM_ANDROID_ID    = "androidId";
    char const* JSON_MARKETITEM_IOS_ID        = "iosId";

    char const* JSON_MARKETITEM_CONSUMABLE    = "consumable";
    char const* JSON_MARKETITEM_PRICE         = "price";
    
    char const* JSON_EQUIPPABLE_EQUIPPING     = "equipping";
    
    char const* JSON_VGP_GOOD_ITEMID          = "good_itemId";
    char const* JSON_VGP_GOOD_AMOUNT          = "good_amount";
    
    char const* JSON_VGU_GOOD_ITEMID          = "good_itemId";
    char const* JSON_VGU_PREV_ITEMID          = "prev_itemId";
    char const* JSON_VGU_NEXT_ITEMID          = "next_itemId";
    
    char const* JSON_CURRENCYPACK_CURRENCYAMOUNT = "currency_amount";
    char const* JSON_CURRENCYPACK_CURRENCYITEMID = "currency_itemId";
    
    char const* JSON_PURCHASABLE_ITEM         = "purchasableItem";
    
    char const* JSON_PURCHASE_TYPE            = "purchaseType";
    char const* JSON_PURCHASE_TYPE_MARKET     = "market";
    char const* JSON_PURCHASE_TYPE_VI         = "virtualItem";
    
    char const* JSON_PURCHASE_MARKET_ITEM     = "marketItem";
    
    char const* JSON_PURCHASE_VI_ITEMID       = "pvi_itemId";
    char const* JSON_PURCHASE_VI_AMOUNT       = "pvi_amount";
}