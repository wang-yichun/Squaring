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

#import "StoreUtils.h"
#import "StoreConfig.h"
#import "OpenUDID.h"

@implementation StoreUtils

static NSString* TAG = @"SOOMLA StoreUtils";

+ (void)LogDebug:(NSString*)tag withMessage:(NSString*)msg {
    if (STORE_DEBUG_LOG) {
        NSLog(@"[Debug] %@: %@", tag, msg);
    }
}

+ (void)LogError:(NSString*)tag withMessage:(NSString*)msg {
    NSLog(@"[*** ERROR ***] %@: %@", tag, msg);
}

+ (NSString*)deviceId {
    NSString* val = [[NSUserDefaults standardUserDefaults] objectForKey:@"UNIQUE_DEVICE_ID_FOR_ENC"];
    if (!val) {
        float osVersion = [[[UIDevice currentDevice] systemVersion] floatValue];
        if (osVersion >= 5.0 && osVersion < 6.0) {
            [[NSUserDefaults standardUserDefaults] setValue:[MyOpenUDID value] forKey:@"UNIQUE_DEVICE_ID_FOR_ENC"];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }else if(osVersion >=6.0){
            [[NSUserDefaults standardUserDefaults] setValue:[[[UIDevice currentDevice] identifierForVendor] UUIDString] forKey:@"UNIQUE_DEVICE_ID_FOR_ENC"];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
        return [[NSUserDefaults standardUserDefaults] objectForKey:@"UNIQUE_DEVICE_ID_FOR_ENC"];
    }
    
    return val;
//    return [[[UIDevice currentDevice] identifierForVendor] UUIDString];
}

+ (NSDictionary*)jsonStringToDict:(NSString*)str {
    NSError* error = NULL;
    NSDictionary *dict =
    [NSJSONSerialization JSONObjectWithData: [str dataUsingEncoding:NSUTF8StringEncoding]
                                    options: NSJSONReadingMutableContainers
                                      error: &error];
    if (error) {
        LogError(TAG, ([NSString stringWithFormat:@"There was a problem parsing the given JSON string. error: %@", [error localizedDescription]]));
        
        return NULL;
    }
    
    return dict;
}

+ (NSString*)dictToJsonString:(NSDictionary*)dict {
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    
    if (! jsonData) {
        LogError(TAG, ([NSString stringWithFormat:@"There was a problem parsing the given NSDictionary. error: %@", [error localizedDescription]]));
        
        return NULL;
    }
    
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}

@end
