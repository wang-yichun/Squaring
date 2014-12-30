//
//  ParseSDKManager.m
//  PlatformService
//
//  Created by Painache on 13-12-1.
//  Copyright (c) 2013年 MeYouGames. All rights reserved.
//

#import "ParseManager.h"

@implementation ParseManager

static ParseManager *_parseManager = nil;

+ (ParseManager *) sharedInstance{
	if (nil == _parseManager) {
        _parseManager = [[[self class] alloc] init];
    }
    return _parseManager;
}

- (void)initSDKWithApplicationID:(NSString *)applicationID ClientKey:(NSString *)clientKey{
//    [IOSNDKHelper SetNDKReciever:self];
    [Parse setApplicationId:applicationID clientKey:clientKey];
    
    PFObject *testObject = [PFObject objectWithClassName:@"TestObject"];
    [testObject setObject:@"bar" forKey:@"foo"];
    [testObject save];
}

@end
