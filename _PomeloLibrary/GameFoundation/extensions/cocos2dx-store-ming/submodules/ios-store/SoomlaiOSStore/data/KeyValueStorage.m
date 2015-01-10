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

#import "KeyValueStorage.h"
#import "KeyValDatabase.h"
#import "StoreEncryptor.h"
#import "StorageManager.h"

@implementation KeyValueStorage

- (NSString*)getValueForKey:(NSString*)key {
    key = [StoreEncryptor encryptString:key];
    NSString* val = [[[StorageManager getInstance] kvDatabase] getValForKey:key];
    if (val && [val length]>0){
        return [StoreEncryptor decryptToString:val];
    }
    
    return NULL;
}

- (void)setValue:(NSString*)val forKey:(NSString*)key {
    key = [StoreEncryptor encryptString:key];
    [[[StorageManager getInstance] kvDatabase] setVal:[StoreEncryptor encryptString:val] forKey:key];
}

- (void)deleteValueForKey:(NSString*)key {
    key = [StoreEncryptor encryptString:key];
    [[[StorageManager getInstance] kvDatabase] deleteKeyValWithKey:key];
}

- (NSDictionary*)getKeysValuesForNonEncryptedQuery:(NSString*)query {
    NSDictionary* dbResults = [[[StorageManager getInstance] kvDatabase] getKeysValsForQuery:query];
    NSMutableDictionary* results = [NSMutableDictionary dictionary];
    NSArray* keys = [dbResults allKeys];
    for (NSString* key in keys) {
        NSString* val = [dbResults objectForKey:key];
        if (val && [val length]>0){
            NSString* valDec = [StoreEncryptor decryptToString:val];
            if (valDec && [valDec length]>0){
                [results setObject:valDec forKey:key];
            }
        }
    }
    
    return results;
}

- (NSArray*)getValuesForNonEncryptedQuery:(NSString*)query {
    NSArray* vals = [[[StorageManager getInstance] kvDatabase] getValsForQuery:query];
    NSMutableArray* results = [NSMutableArray array];
    for (NSString* val in vals) {
        if (val && [val length]>0){
            NSString* valDec = [StoreEncryptor decryptToString:val];
            if (valDec && [valDec length]>0){
                [results addObject:valDec];
            }
        }
    }
    
    return results;
}


- (NSString*)getValueForNonEncryptedKey:(NSString*)key {
    NSString* val = [[[StorageManager getInstance] kvDatabase] getValForKey:key];
    if (val && [val length]>0){
        return [StoreEncryptor decryptToString:val];
    }
    
    return NULL;
}

- (void)setValue:(NSString*)val forNonEncryptedKey:(NSString*)key {
    [[[StorageManager getInstance] kvDatabase] setVal:[StoreEncryptor encryptString:val] forKey:key];
}

- (void)deleteValueForNonEncryptedKey:(NSString*)key {
    [[[StorageManager getInstance] kvDatabase] deleteKeyValWithKey:key];
}

@end
