//
//  Bridge.cpp
//  EasyJSBSample
//
//  Created by Simon on 14/1/4.
//
//

#include "CPPBridge.h"
#include "JSBHelper.h"
using namespace std;

CPPBridge * s_cpp_bridge = NULL;

CPPBridge * CPPBridge::getInstance() {
    if (s_cpp_bridge == NULL) {
        s_cpp_bridge = new CPPBridge();
    }
    return s_cpp_bridge;
}

void CPPBridge::initBridge() {
    CCLOG("CPP: initBridge");
    
    // 需要把Javascript端调用的函数都注册进来
    JSBHelper::AddSelector("cppb_test", callfuncND_selector(CPPBridge::cppb_test), this);
    
    // 初始化成员变量
    name = "Hello CPPBridge";
}

void CPPBridge::cppb_test(CCNode * sender, void * data){
    CCLog("CPP: cppb_test name: %s", this->name.c_str());
    
    // 接收的数据
    CCDictionary * dic_get = (CCDictionary *) data;
    CCLog("CPP: number_float = %f", dic_get->valueForKey("number_float")->floatValue());
    CCLog("CPP: number_int = %d", dic_get->valueForKey("number_int")->intValue());
    CCLog("CPP: string_value1 = %s", dic_get->valueForKey("string_value1")->getCString());
    CCLog("CPP: string_value2 = %s", dic_get->valueForKey("string_value2")->getCString());
    CCLog("CPP: obj_key1 = %d", ((CCDictionary *)dic_get->objectForKey("object_value"))->valueForKey("key1")->intValue());
    CCLog("CPP: obj_key2 = %s", ((CCDictionary *)dic_get->objectForKey("object_value"))->valueForKey("key2")->getCString());
    
    // 发送的数据
    CCDictionary * dic_send = CCDictionary::create();
    dic_send->setObject(CCString::create("cpp_value"), "cpp_string_key");
    dic_send->setObject(CCInteger::create(123), "cpp_int_key");
    dic_send->setObject(CCFloat::create(123.123), "cpp_float_key");
    dic_send->setObject(dic_get, "cpp_dictionary_key");
    
    CCArray * array_send = CCArray::create();
    array_send->addObject(CCString::create("郑东新区"));
    array_send->addObject(CCInteger::create(123));
    
    dic_send->setObject(array_send, "cpp_array_key");
    
    SendMessageToJS(dic_get->valueForKey("call_back")->getCString(), dic_send);
}