package com.soomla.cocos2dx.store;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;
import com.soomla.store.*;
import com.soomla.store.data.ObscuredSharedPreferences;
import com.soomla.store.data.StoreInfo;
import com.soomla.store.domain.PurchasableVirtualItem;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

/**
 * This bridge is used to let cocos2dx functions perform actions on StoreController (through JNI).
 *
 * You can see the documentation of every function in {@link StoreController}
 */
public class StoreControllerBridge {
    private static Activity mActivity          = null;
    private static IStoreAssets mStoreAssets   = null;
    private static String mPublicKey           = "";
    private static EventHandlerBridge mEventHandler = null;

    public static void initialize(Cocos2dxGLSurfaceView mGLView,
                                  IStoreAssets storeAssets,
                                  String publicKey,
                                  Activity activity) {
        mStoreAssets = storeAssets;
        mPublicKey   = publicKey;
        mActivity    = activity;


        mEventHandler = new EventHandlerBridge(mGLView);
    }

    static void initialize(String customSecret) {
        Log.d("SOOMLA", "initialize is called from java !");
        StoreController.getInstance().initialize(mStoreAssets, mPublicKey, customSecret);
    }

    static void initialize() {
        Log.d("SOOMLA", "initialize is called from java and data from c struct!");
        StoreController.getInstance().setTestMode(true);
        StoreController.getInstance().initialize(mStoreAssets, mPublicKey, "PapatuCustomSec");
        
        SharedPreferences prefs = new ObscuredSharedPreferences(SoomlaApp.getAppContext(), SoomlaApp.getAppContext().getSharedPreferences(StoreConfig.PREFS_NAME, Context.MODE_PRIVATE));
        SharedPreferences.Editor edit = prefs.edit();
        if(!prefs.getBoolean("NotFirstLaunch", false)){
        	edit.putBoolean("NotFirstLaunch", true);
        	for(int i = 0; i < mStoreAssets.getCurrencies().length; i++){
        		mStoreAssets.getCurrencies()[i].give(mStoreAssets.getCurrencies()[i].getInitialAmount());
        	}
        }
        edit.commit();
    }
    
//    static void initialize() {
//                Log.d("SOOMLA", "initialize is called from java !");
//                StoreController.getInstance().initialize(mStoreAssets, mPublicKey, "PapatuCustomSec");
//    }

    static void storeOpening() {
        Log.d("SOOMLA", "storeOpening is called from java !");
        StoreController.getInstance().storeOpening(mActivity);
    }

    static void storeClosing() {
        Log.d("SOOMLA", "storeClosing is called from java !");
        StoreController.getInstance().storeClosing();
    }

    static void buyWithGooglePlay(String productId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "buyWithGooglePlay is called from java with productId: " + productId + " !");
        PurchasableVirtualItem pvi = StoreInfo.getPurchasableItem(productId);
        if(pvi.getPurchaseType() instanceof PurchaseWithMarket) {
            StoreController.getInstance().buyWithGooglePlay(((PurchaseWithMarket)pvi.getPurchaseType()).getGoogleMarketItem(), "");
        } else {
            throw new VirtualItemNotFoundException("productId", productId);
        }
    }

    static void restoreTransactions() {
        Log.d("SOOMLA", "restoreTransactions is called from java !");
        StoreController.getInstance().restoreTransactions();
    }

    private static String TAG = "StoreControllerBridge";
}
