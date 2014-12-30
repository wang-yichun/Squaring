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

#ifndef __CCSoomla_H_
#define __CCSoomla_H_

#include "cocos2d.h"
#include "CCEventHandler.h"

#define DEPRECATED(func) func __attribute__ ((deprecated("CCSoomla attributes have been removed, see README. Linking will fail.")))
#define CC_SYNTH_DEPRECATED(type, name, func) DEPRECATED(type get##func(void)); \
    DEPRECATED(void set##func(type name))

namespace soomla {

    #define SOOMLA_AND_PUB_KEY_DEFAULT "YOUR GOOGLE PLAY PUBLIC KEY"
    #define SOOMLA_ONLY_ONCE_DEFAULT "SET ONLY ONCE"

	/** 
     @class CCSoomla
     @brief Calls event handler functions when events are fired, also contains settings for StoreController.
     
     This class calls event handler functions when events are fired. To tie
     to your event handler call `addEventHandler`. You also set parameters for
     StoreController through this class.
	 */
    class CCSoomla: public cocos2d::CCObject {

    public:
		/**
         This class is singleton, access it with this function.
		 */
        static CCSoomla* sharedSoomla();

        virtual ~CCSoomla(void);
      
        virtual bool init(void);

		/**
         Calls an NDK function by name and parameters.
         @param parameters A dictionary containing the function to call and 
                parameters to pass to it.
		 */
        void easyNDKCallBack(cocos2d::CCDictionary *parameters);

		/**
         Adds an event handler. This retains the event handler.
         @param eventHandler A pointer to the event handler you'd like to add.
		 */
		void addEventHandler(CCEventHandler *eventHandler);

		/**
         Removes an event handler. This releases the event handler.
         @param eventHandler A pointer to the event handler you'd like to 
                remove.
		*/
		void removeEventHandler(CCEventHandler *eventHandler);

        /**
         CCSoomla attributes have been removed. Attributes were accessed by
         CCStoreController on initialization, and are now passed to it through
         a CCDictionary. See CCStoreController::createShared() for more 
         information.
         */
        CC_SYNTH_DEPRECATED(std::string, mCustomSecret, CustomSecret);
        CC_SYNTH_DEPRECATED(std::string, mAndroidPublicKey, AndroidPublicKey);
        CC_SYNTH_DEPRECATED(bool, mAndroidTestMode, AndroidTestMode);
        CC_SYNTH_DEPRECATED(std::string, mSoomSec, SoomSec);
        CC_SYNTH_DEPRECATED(bool, mSSV, SSV);
        
    private:
        cocos2d::CCSet mEventHandlers;
        
    };
};

#undef DEPRECATED
#undef CC_SYNTH_DEPRECATED

#endif //__CCSoomla_H_
