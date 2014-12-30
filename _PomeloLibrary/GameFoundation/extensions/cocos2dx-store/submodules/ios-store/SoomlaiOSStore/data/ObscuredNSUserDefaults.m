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

#import "ObscuredNSUserDefaults.h"
#import "StoreConfig.h"
#import <CommonCrypto/CommonCryptor.h>
#import "FBEncryptorAES.h"
#import "StoreUtils.h"

@interface ObscuredNSUserDefaults (Private)
+ (NSString*)key;
@end

@implementation ObscuredNSUserDefaults

+ (NSString*)key
{
    return [SOOM_SEC stringByAppendingString:[StoreUtils deviceId]];
}

+ (NSString*)keyWithDeviceId:(NSString*)deviceId
{
    return [SOOM_SEC stringByAppendingString:deviceId];
}

+ (BOOL)boolForKey:(NSString *)defaultName withDefaultValue:(BOOL)def {
    @synchronized(self) {
        NSString* val = [[NSUserDefaults standardUserDefaults] objectForKey:defaultName];
        if (!val) {
            return def;
        }
        val = [FBEncryptorAES decryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults key]];
        return [val isEqualToString:@"YES"];
    }
}

+ (void)setBool:(BOOL)value forKey:(NSString *)defaultName {
    @synchronized(self) {
        NSString* val = value ? @"YES" : @"NO";
        val = [FBEncryptorAES encryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults key]
                                    separateLines:NO];
        [[NSUserDefaults standardUserDefaults] setValue:val forKey:defaultName];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

+ (void)setInt:(int)value forKey:(NSString *)defaultName {
    @synchronized(self) {
        NSString* val = [NSString stringWithFormat:@"%d",value];
        val = [FBEncryptorAES encryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults key]
                                    separateLines:NO];
        [[NSUserDefaults standardUserDefaults] setValue:val forKey:defaultName];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

+ (int)intForKey:(NSString *)defaultName withDefaultValue:(int)def {
    @synchronized(self) {
        NSString* val = [[NSUserDefaults standardUserDefaults] objectForKey:defaultName];
        if (!val) {
            return def;
        }
        val = [FBEncryptorAES decryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults key]];
        return [val intValue];
    }
}

+ (int)intForKey:(NSString *)defaultName withDefaultValue:(int)def andDeviceId:(NSString*)deviceId {
    @synchronized(self) {
        NSString* val = [[NSUserDefaults standardUserDefaults] objectForKey:defaultName];
        if (!val) {
            return def;
        }
        val = [FBEncryptorAES decryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults keyWithDeviceId:deviceId]];
        return [val intValue];
    }
}

+ (NSString*)stringForKey:(NSString *)defaultName withDefaultValue:(NSString*)def {
    @synchronized(self) {
        NSString* val = [[NSUserDefaults standardUserDefaults] objectForKey:defaultName];
        if (!val) {
            return def;
        }
        return [FBEncryptorAES decryptBase64String:val
                                         keyString:[ObscuredNSUserDefaults key]];
    }
}

+ (void)setString:(NSString*)value forKey:(NSString *)defaultName {
    @synchronized(self) {
        NSString* val = [FBEncryptorAES encryptBase64String:value
                                        keyString:[ObscuredNSUserDefaults key]
                                    separateLines:NO];
        [[NSUserDefaults standardUserDefaults] setValue:val forKey:defaultName];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

+ (long long)longlongForKey:(NSString *)defaultName withDefaultValue:(long long)def {
    @synchronized(self) {
        NSString* val = [[NSUserDefaults standardUserDefaults] objectForKey:defaultName];
        if (!val) {
            return def;
        }
        val = [FBEncryptorAES decryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults key]];
        return [val longLongValue];
    }
}

+ (void)setLongLong:(long long)value forKey:(NSString *)defaultName {
    @synchronized(self) {
        NSString* val = [NSString stringWithFormat:@"%lld",value];
        val = [FBEncryptorAES encryptBase64String:val
                                        keyString:[ObscuredNSUserDefaults key]
                                    separateLines:NO];
        [[NSUserDefaults standardUserDefaults] setValue:val forKey:defaultName];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

@end
