//
//  OCBridge.h
//  TD
//
//  Created by LeadProgrammer on 12/18/14.
//
//

#ifndef TD_OCBridge_h
#define TD_OCBridge_h

@interface OCBridge : NSObject {
    NSString * name;
}

+(OCBridge *) getInstance;

-(void) initBridge;

-(void) ocb_test:(NSObject *)prms;

@end

#endif
