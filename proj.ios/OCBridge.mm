//
//  OCBridge.m
//  TD
//
//  Created by LeadProgrammer on 12/18/14.
//
//

#import <Foundation/Foundation.h>
#import "OCBridge.h"
#import "IOSNDKHelper.h"
#import "IOSJSBHelper.h"

@implementation OCBridge

static OCBridge * s_bridge = nil;

+(OCBridge *) getInstance {
    if (s_bridge == nil) {
        s_bridge = [[[self class] alloc] init];
    }
    return s_bridge;
}

-(void) initBridge {
    NSLog(@"OC: initBridge");
    [IOSNDKHelper SetNDKReciever:self];
    
    // 初始化成员变量
    self->name = @"Hello OCBridge";
}

-(void) ocb_test:(NSObject *)para {
    NSLog(@"OC: ocb_test name:%@", self->name);
    
    // 接收的数据
    NSMutableDictionary * dic_get = (NSMutableDictionary*)para;
    NSLog(@"OC: %@", [dic_get description]);
    NSLog(@"OC: number_float = %f", [[dic_get objectForKey:@"number_float"] floatValue]);
    NSLog(@"OC: number_int = %d", [[dic_get objectForKey:@"number_int"] integerValue]);
    NSLog(@"OC: string_value1 = %@", [dic_get objectForKey:@"string_value1"]);
    NSLog(@"OC: string_value2 = %@", [dic_get objectForKey:@"string_value2"]);
    NSLog(@"OC: vector_value = %@", [[dic_get objectForKey:@"vector_value"] description]);
    NSLog(@"OC: object_value = %@", [[dic_get objectForKey:@"object_value"] description]);
    
    // 发送的数据
    NSMutableDictionary * dic_send = [NSMutableDictionary dictionary];
    [dic_send setObject:@"oc_value" forKey:@"oc_string_key"];
    [dic_send setObject:[NSNumber numberWithInt:123] forKey:@"oc_int_key"];
    [dic_send setObject:[NSNumber numberWithFloat:1234.1234] forKey:@"oc_float_key"];
    [dic_send setObject:dic_get forKey:@"oc_dictionary_key"];
    
    NSMutableArray * array_send = [NSMutableArray array];
    [array_send addObject:@"郑东新区"];
    [array_send addObject:[NSNumber numberWithInt:123]];
    
    [dic_send setObject:array_send forKey:@"oc_array_key"];
    
    [IOSJSBHelper SendMessageToJS:[dic_get objectForKey:@"call_back"] WithParameters:dic_send];
}

@end