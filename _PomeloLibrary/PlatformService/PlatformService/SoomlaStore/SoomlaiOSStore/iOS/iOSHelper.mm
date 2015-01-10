//
//  iOSHelper.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/27/12.
//
//

#include "iOSHelper.h"
    
void iOSHelper::LogMessage(const char* msg) {
    NSString *message = [[NSString alloc] initWithBytes:msg length:strlen(msg) encoding:NSUTF8StringEncoding];
    NSLog(@"%@", message);
}
