//
//  ParseSDKBridge.mm
//  PlatformService
//
//  Created by Painache on 13-12-1.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#import "ParseSDKBridge.h"
#import "ParseManager.h"

ParseSDKBridge::ParseSDKBridge() {
    
}

ParseSDKBridge::~ParseSDKBridge() {
    
}

void ParseSDKBridge::initSDK(std::string applicationID, std::string clientKey) {
    [[ParseManager sharedInstance] initSDKWithApplicationID:[NSString stringWithUTF8String:applicationID.c_str()] ClientKey:[NSString stringWithUTF8String:clientKey.c_str()]];
    
}