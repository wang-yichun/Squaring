//
//  ParseSDKBridge.h
//  PlatformService
//
//  Created by Painache on 13-12-1.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#ifndef PlatformService_ParseSDKBridge_h
#define PlatformService_ParseSDKBridge_h

#include <string>

class ParseSDKBridge {
public:
    ParseSDKBridge();
    ~ParseSDKBridge();
    
    static void initSDK(std::string applicationID, std::string clientKey);
};

#endif
