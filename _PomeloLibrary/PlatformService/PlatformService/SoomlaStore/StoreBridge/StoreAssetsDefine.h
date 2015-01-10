//
//  StoreAssetsDefine.h
//  PlatformService
//
//  Created by MeYouGames on 13-8-9.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#ifndef PlatformService_StoreAssetsDefine_h
#define PlatformService_StoreAssetsDefine_h

typedef struct _virtualCurrencyType
{
    char Name[30];
    char Description[50];
    char ItemID[30];
    int InitialAmount;
} VirtualCurrencyType;

typedef struct _virtualCurrencyPackType
{
    char Name[30];
    char Description[50];
    char ItemID[30];
    int Amount;
    int VirtualCurrencyID;
    char ProductID[30];
    double Price;
} VirtualCurrencyPackType;

typedef struct _singleUseVGType
{
    char Name[30];
    char Description[50];
    char ItemID[30];
    int VirtualCurrencyID;
    int ConsumeCurrencyAmount;
} SingleUseVGType;

typedef struct _virtualCategoryType
{
    char Name[30];
    int GoodsItemCount;
    int GoodsItemIDs[10];
} VirtualCategoryType;

typedef struct _nonConsumableItemType
{
    char Name[30];
    char Description[50];
    char ItemID[30];
    char ProductID[30];
    double Price;
} NonConsumableItemType;

typedef struct _storeAssetsType
{
    int Version;
    int VirtualCurrencyCount;
    VirtualCurrencyType vc[3];
    int VirtualCurrencyPackCount;
    VirtualCurrencyPackType vcp[10];
    int SingleUseVGCount;
    SingleUseVGType suvg[10];
    int VirtualCategoryCount;
    VirtualCategoryType vca[5];//suvg[   vca[i].GoodsItemsIDs[j]   ].itemID
    int NonConsumableItemCount;
    NonConsumableItemType nc[5];
} StoreAssetsType;

#endif
