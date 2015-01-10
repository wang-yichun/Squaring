//
//  Bridge.h
//  EasyJSBSample
//
//  Created by Simon on 14/1/4.
//
//

#ifndef __CPPBridge__
#define __CPPBridge__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class CPPBridge : public CCNode{
public:
    std::string name;
    
    static CPPBridge * getInstance();
    
    void initBridge();
    void cppb_test(CCNode * sender, void * data);
};

#endif
