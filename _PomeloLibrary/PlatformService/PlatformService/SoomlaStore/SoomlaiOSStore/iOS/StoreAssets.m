#import "StoreAssets.h"
#import "VirtualCategory.h"
#import "VirtualCurrency.h"
#import "VirtualGood.h"
#import "VirtualCurrencyPack.h"
#import "NonConsumableItem.h"
#import "SingleUseVG.h"
#import "PurchaseWithMarket.h"
#import "PurchaseWithVirtualItem.h"

int VersionNumber;
NSMutableArray *VirtualCurrencys;
NSMutableArray *VirtualCurrencyPacks;
NSMutableArray *SingleUseVirtualGoods;
NSMutableArray *VirtualCategorys;
NSMutableArray *NonConsumableItems;

/**
 * This class represents a single game's metadata.
 * Use this protocol to create your assets class that will be transferred to StoreInfo
 * upon initialization.
 */
@implementation StoreAssets

-(void) initWithData:(StoreAssetsType)sa{
    
    NSLog(@"count = %d", sa.VirtualCurrencyPackCount);
    NSString *encrypted = [[NSString alloc] initWithCString:(const char*)sa.vcp[0].Name encoding:NSUTF8StringEncoding];
	NSLog(@"encrypted:%@", encrypted);
    
    VersionNumber = sa.Version;
    
    /** Virtual Currencies **/
    VirtualCurrencys = [[NSMutableArray alloc] initWithCapacity:sa.VirtualCurrencyCount];
    for (int i = 0; i < sa.VirtualCurrencyCount; i++) {
        [VirtualCurrencys addObject:[[VirtualCurrency alloc]
        initWithName:[[NSString alloc] initWithCString:(const char*)sa.vc[i].Name encoding:NSUTF8StringEncoding]
        andDescription:[[NSString alloc] initWithCString:(const char*)sa.vc[i].Description encoding:NSUTF8StringEncoding]
        andItemId:[[NSString alloc] initWithCString:(const char*)sa.vc[i].ItemID encoding:NSUTF8StringEncoding]]];
    }
    
    /** Virtual Currency Pack **/
    VirtualCurrencyPacks = [[NSMutableArray alloc] initWithCapacity:sa.VirtualCurrencyPackCount];
    for (int i = 0; i < sa.VirtualCurrencyPackCount; i++) {
        [VirtualCurrencyPacks addObject:[[VirtualCurrencyPack alloc]
        initWithName:[[NSString alloc] initWithCString:(const char*)sa.vcp[i].Name encoding:NSUTF8StringEncoding]
        andDescription:[[NSString alloc] initWithCString:(const char*)sa.vcp[i].Description encoding:NSUTF8StringEncoding]
        andItemId:[[NSString alloc] initWithCString:(const char*)sa.vcp[i].ItemID encoding:NSUTF8StringEncoding]
        andCurrencyAmount:sa.vcp[i].Amount
        andCurrency:[[NSString alloc] initWithCString:(const char*)sa.vc[sa.vcp[i].VirtualCurrencyID].ItemID encoding:NSUTF8StringEncoding]
        andPurchaseType:[[PurchaseWithMarket alloc]
        initWithProductId:[[NSString alloc] initWithCString:(const char*)sa.vcp[i].ProductID encoding:NSUTF8StringEncoding]
        andPrice:sa.vcp[i].Price]]];
    }
    
    /** Virtual Goods **/
    SingleUseVirtualGoods = [[NSMutableArray alloc] initWithCapacity:sa.SingleUseVGCount];
    for (int i = 0; i < sa.SingleUseVGCount; i++) {
        [SingleUseVirtualGoods addObject:[[SingleUseVG alloc]
        initWithName:[[NSString alloc] initWithCString:(const char*)sa.suvg[i].Name encoding:NSUTF8StringEncoding]
        andDescription:[[NSString alloc] initWithCString:(const char*)sa.suvg[i].Description encoding:NSUTF8StringEncoding]
        andItemId:[[NSString alloc] initWithCString:(const char*)sa.suvg[i].ItemID encoding:NSUTF8StringEncoding]
        andPurchaseType:[[PurchaseWithVirtualItem alloc]
        initWithVirtualItem:[[NSString alloc] initWithCString:(const char*)sa.vc[sa.suvg[i].VirtualCurrencyID].ItemID encoding:NSUTF8StringEncoding]
        andAmount:sa.suvg[i].ConsumeCurrencyAmount]]];
    }
    
    /** Virtual Categories **/
    VirtualCategorys = [[NSMutableArray alloc] initWithCapacity:sa.VirtualCategoryCount];
    for (int i = 0; i < sa.VirtualCategoryCount; i++) {
        NSMutableArray *goodItemIDs = [[NSMutableArray alloc] initWithCapacity:sa.vca[i].GoodsItemCount];
        for (int j = 0; j < sa.vca[i].GoodsItemCount; j++) {
            [goodItemIDs addObject:[[NSString alloc] initWithCString:(const char*)sa.suvg[sa.vca[i].GoodsItemIDs[j]].ItemID encoding:NSUTF8StringEncoding]];
        }
        [VirtualCategorys addObject:[[VirtualCategory alloc]
        initWithName:[[NSString alloc] initWithCString:(const char*)sa.vca[i].Name encoding:NSUTF8StringEncoding]
        andGoodsItemIds:(NSArray*)goodItemIDs]];
    }
    
    /** Non Consumables **/
    NonConsumableItems = [[NSMutableArray alloc] initWithCapacity:sa.NonConsumableItemCount];
    for (int i = 0; i < sa.NonConsumableItemCount; i++) {
        [NonConsumableItems addObject:[[NonConsumableItem alloc]
        initWithName:[[NSString alloc] initWithCString:(const char*)sa.nc[i].Name encoding:NSUTF8StringEncoding]
        andDescription:[[NSString alloc] initWithCString:(const char*)sa.nc[i].Description encoding:NSUTF8StringEncoding]
        andItemId:[[NSString alloc] initWithCString:(const char*)sa.nc[i].ItemID encoding:NSUTF8StringEncoding]
        andPurchaseType:[[PurchaseWithMarket alloc]
        initWithProductId:[[NSString alloc] initWithCString:(const char*)sa.nc[i].ProductID encoding:NSUTF8StringEncoding]
        andPrice:sa.nc[i].Price]]];
    }
    
}

+ (void)initialize{}

/**
 * A version for your specific game's store assets
 *
 * This value will determine if the saved data in the database will be deleted or not.
 * Bump the version every time you want to delete the old data in the DB.
 * If you don't bump this value, you won't be able to see changes you've made to the objects in this file.
 *
 * NOTE: You can NOT bump this value and just delete the app from your device to see changes. You can't do this after
 * you publish your application on the market.
 *
 * For example: If you previously created a VirtualGood with name "Hat" and you published your application,
 * the name "Hat will be saved in any of your users' databases. If you want to change the name to "Green Hat"
 * than you'll also have to bump the version (from 0 to 1). Now the new "Green Hat" name will replace the old one.
 */
- (int)getVersion {
    return VersionNumber;
}

/**
 * A representation of your game's virtual currency.
 */
- (NSArray*)virtualCurrencies{
    return (NSArray*)VirtualCurrencys;
}

/**
 * An array of all virtual goods served by your store (all kinds in one array). If you have UpgradeVGs, they must appear in the order of levels.
 */
- (NSArray*)virtualGoods{
    return (NSArray*)SingleUseVirtualGoods;
}

/**
 * An array of all virtual currency packs served by your store.
 */
- (NSArray*)virtualCurrencyPacks{
    return (NSArray*)VirtualCurrencyPacks;
}

/**
 * An array of all virtual categories served by your store.
 */
- (NSArray*)virtualCategories{
    return (NSArray*)VirtualCategorys;
}

/**
 * You can define non consumable items that you'd like to use for your needs.
 * CONSUMABLE items are usually just currency packs.
 * NON-CONSUMABLE items are usually used to let users purchase a "no-ads" token.
 */
- (NSArray*)nonConsumableItems{
    return (NSArray*)NonConsumableItems;
}

@end