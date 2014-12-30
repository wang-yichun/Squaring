package com.soomla.cocos2dx.store;

import com.soomla.store.BusProvider;
import com.soomla.store.events.*;
import com.squareup.otto.Subscribe;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

/**
 * This bridge is used to populate events from the store to cocos2dx (through JNI).
 */
public class EventHandlerBridge {

    private Cocos2dxGLSurfaceView mGLThread;

    public EventHandlerBridge(Cocos2dxGLSurfaceView glThread) {
        mGLThread = glThread;

        BusProvider.getInstance().register(this);
    }

    @Subscribe
    public void onBillingSupported(BillingSupportedEvent billingSupportedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                billingSupported();
            }
        });
    }

    @Subscribe
    public void onBillingNotSupported(BillingNotSupportedEvent billingNotSupportedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                billingNotSupported();
            }
        });
    }

    @Subscribe
    public void onClosingStore(ClosingStoreEvent closingStoreEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                closingStore();
            }
        });
    }

    @Subscribe
    public void onCurrencyBalanceChanged(final CurrencyBalanceChangedEvent currencyBalanceChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                currencyBalanceChanged(currencyBalanceChangedEvent.getCurrency().getItemId(),
                        currencyBalanceChangedEvent.getBalance(),
                        currencyBalanceChangedEvent.getAmountAdded());
            }
        });
    }

    @Subscribe
    public void onGoodBalanceChanged(final GoodBalanceChangedEvent goodBalanceChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodBalanceChanged(goodBalanceChangedEvent.getGood().getItemId(),
                        goodBalanceChangedEvent.getBalance(),
                        goodBalanceChangedEvent.getAmountAdded());
            }
        });
    }

    @Subscribe
    public void onGoodEquipped(final GoodEquippedEvent goodEquippedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodEquipped(goodEquippedEvent.getGood().getItemId());
            }
        });
    }

    @Subscribe
    public void onGoodUnequipped(final GoodUnEquippedEvent goodUnEquippedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodUnequipped(goodUnEquippedEvent.getGood().getItemId());
            }
        });
    }

    @Subscribe
    public void onGoodUpgrade(final GoodUpgradeEvent goodUpgradeEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodUpgrade(goodUpgradeEvent.getGood().getItemId(), goodUpgradeEvent.getCurrentUpgrade().getItemId());
            }
        });
    }

    @Subscribe
    public void onItemPurchased(final ItemPurchasedEvent itemPurchasedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                itemPurchased(itemPurchasedEvent.getPurchasableVirtualItem().getItemId());
            }
        });
    }

    @Subscribe
    public void onItemPurchaseStarted(final ItemPurchaseStartedEvent itemPurchaseStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                itemPurchaseStarted(itemPurchaseStartedEvent.getPurchasableVirtualItem().getItemId());
            }
        });
    }

    @Subscribe
    public void onOpeningStore(OpeningStoreEvent openingStoreEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                openingStore();
            }
        });
    }

    @Subscribe
    public void onPlayPurchaseCancelled(final PlayPurchaseCancelledEvent playPurchaseCancelledEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                playPurchaseCancelled(playPurchaseCancelledEvent.getPurchasableVirtualItem().getItemId());
            }
        });
    }

    @Subscribe
    public void onPlayPurchase(final PlayPurchaseEvent playPurchaseEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                playPurchase(playPurchaseEvent.getPurchasableVirtualItem().getItemId());
            }
        });
    }

    @Subscribe
    public void onPlayPurchaseStarted(final PlayPurchaseStartedEvent playPurchaseStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                playPurchaseStarted(playPurchaseStartedEvent.getPurchasableVirtualItem().getItemId());
            }
        });
    }

    @Subscribe
    public void onPlayRefund(final PlayRefundEvent playRefundEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                playRefund(playRefundEvent.getPurchasableVirtualItem().getItemId());
            }
        });
    }

    @Subscribe
    public void onRestoreTransactions(final RestoreTransactionsEvent restoreTransactionsEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                restoreTransactions(restoreTransactionsEvent.isSuccess());
            }
        });
    }

    @Subscribe
    public void onRestoreTransactionsStarted(final RestoreTransactionsStartedEvent restoreTransactionsStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                restoreTransactionsStarted();
            }
        });
    }

    @Subscribe
    public void onUnexpectedErrorInStore(UnexpectedStoreErrorEvent unexpectedStoreErrorEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                unexpectedErrorInStore();
            }
        });
    }





    native void billingSupported();
    native void billingNotSupported();
    native void closingStore();
    native void currencyBalanceChanged(String itemId, int balance, int amountAdded);
    native void goodBalanceChanged(String itemId, int balance, int amountAdded);
    native void goodEquipped(String itemId);
    native void goodUnequipped(String itemId);
    native void goodUpgrade(String itemId, String upgradeItemId);
    native void itemPurchased(String itemId);
    native void itemPurchaseStarted(String itemId);
    native void openingStore();
    native void playPurchaseCancelled(String itemId);
    native void playPurchase(String itemId);
    native void playPurchaseStarted(String itemId);
    native void playRefund(String itemId);
    native void restoreTransactions(boolean success);
    native void restoreTransactionsStarted();
    native void unexpectedErrorInStore();


}
