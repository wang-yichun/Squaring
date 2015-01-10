/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "com_soomla_cocos2dx_store_EventHandlerBridge.h"

#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#include "cocos2dx_EventHandlers.h"

#include <string>

using namespace std;

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_billingSupported
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Billing is supported.");
	  
	  cocos2dx_EventHandlers::getInstance()->billingSupported();
  }


JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_billingNotSupported
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Billing is not supported.");
	  
	  cocos2dx_EventHandlers::getInstance()->billingNotSupported();
  }


JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_closingStore
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Store is closing.");
	  
	  cocos2dx_EventHandlers::getInstance()->closingStore();
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_currencyBalanceChanged
  (JNIEnv * env, jobject obj, jstring itemId, jint balance, jint amountAdded){
	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
	  string msg("Currency balance changed for: ");
	  msg += itemIdStr;
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  	  
	  
  	  cocos2dx_EventHandlers::getInstance()->currencyBalanceChanged(itemIdStr, balance, amountAdded);
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_goodBalanceChanged
  (JNIEnv * env, jobject obj, jstring itemId, jint balance, jint amountAdded){
      string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
      string msg("Good balance changed for: ");
      msg += itemIdStr;
      __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  	  
	  
      cocos2dx_EventHandlers::getInstance()->goodBalanceChanged(itemIdStr, balance, amountAdded);
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_goodEquipped
  (JNIEnv * env, jobject obj, jstring itemId){
	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
	  string msg(itemIdStr);
	  msg.append(" was just equipped.");
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  
	  cocos2dx_EventHandlers::getInstance()->goodEquipped(itemIdStr);
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_goodUnequipped
   (JNIEnv * env, jobject obj, jstring itemId){
  	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
  	  string msg(itemIdStr);
  	  msg.append(" was just unequipped.");
  	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
	  
  	  cocos2dx_EventHandlers::getInstance()->goodUnequipped(itemIdStr);
  }
  
JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_goodUpgrade
  (JNIEnv * env, jobject obj, jstring itemId, jstring upgradeItemId){
   	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
	  string upgradeItemIdStr = cocos2d::JniHelper::jstring2string(upgradeItemId);
   	  string msg(itemIdStr);
   	  msg.append(" was just Upgraded.");
   	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  
  	  cocos2dx_EventHandlers::getInstance()->goodUpgrade(itemIdStr, upgradeItemIdStr);
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_itemPurchased
  (JNIEnv * env, jobject obj, jstring itemId){
  	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
  	  string msg(itemIdStr);
  	  msg.append(" was just purchased.");
  	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());

  	  cocos2dx_EventHandlers::getInstance()->itemPurchased(itemIdStr);	  
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_itemPurchaseStarted
  (JNIEnv * env, jobject obj, jstring itemId){
   	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
   	  string msg(itemIdStr);
   	  msg.append(" was just purchased.");
   	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());

   	  cocos2dx_EventHandlers::getInstance()->itemPurchased(itemIdStr);	  
  }


JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_openingStore
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Store is opening.");
	  
  	  cocos2dx_EventHandlers::getInstance()->openingStore();
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_playPurchaseCancelled
  (JNIEnv * env, jobject obj, jstring itemId){
   	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
   	  string msg("Market purchase just cancelled for: ");
   	  msg += itemIdStr;
   	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());

   	  cocos2dx_EventHandlers::getInstance()->marketPurchaseCancelled(itemIdStr);
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_playPurchase
  (JNIEnv * env, jobject obj, jstring itemId){
   	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
   	  string msg("Market purchase for: ");
  	  msg += itemIdStr;
   	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());

   	  cocos2dx_EventHandlers::getInstance()->marketPurchase(itemIdStr);
  }
  
JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_playPurchaseStarted
  (JNIEnv * env, jobject obj, jstring itemId){
   	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
   	  string msg("Market purchase started for: ");
  	  msg += itemIdStr;
   	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());

   	  cocos2dx_EventHandlers::getInstance()->marketPurchaseStarted(itemIdStr);
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_playRefund
  (JNIEnv * env, jobject obj, jstring itemId){
   	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
   	  string msg("Market purchase refund for: ");
  	  msg += itemIdStr;
   	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());

   	  cocos2dx_EventHandlers::getInstance()->marketRefund(itemIdStr);
  }
  
  
JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_restoreTransactions
  (JNIEnv * env, jobject obj, jboolean success){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "transactions restored.");
	  
	  cocos2dx_EventHandlers::getInstance()->restoreTransactions(success);
  }
  
JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_restoreTransactionsStarted
  (JNIEnv * env, jobject obj){
  	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "transactions restored started.");
	  
  	  cocos2dx_EventHandlers::getInstance()->restoreTransactionsStarted();
  }


JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_unexpectedErrorInStore
  (JNIEnv * env, jobject obj){
  	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Unexpected error occured.");
	  
  	  cocos2dx_EventHandlers::getInstance()->unexpectedErrorInStore();
  }


	
