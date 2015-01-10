//
//  ParseSDKManager.h
//  PlatformService
//
//  Created by Painache on 13-12-1.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Parse/Parse.h>
#include "IOSNDKHelper.h"

@interface ParseManager : NSObject{
    
}

+ (ParseManager *) sharedInstance;

- (void)initSDKWithApplicationID:(NSString *)applicationID ClientKey:(NSString *)clientKey;

@end
