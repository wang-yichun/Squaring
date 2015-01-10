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

// Created by Fedor Shubin on 6/22/13.

#include "CCSoomlaJsonHelper.h"

USING_NS_CC;
using namespace std;

CCObject *CCSoomlaJsonHelper::getCCObjectFromJson(json_t *obj) {
    if (obj == NULL) {
        return NULL;
    }

    if (json_is_object(obj)) {
        CCDictionary *dictionary = CCDictionary::create();

        const char *key;
        json_t *value;

        void *iter = json_object_iter(obj);
        while (iter) {
            key = json_object_iter_key(iter);
            value = json_object_iter_value(iter);

            dictionary->setObject(CCSoomlaJsonHelper::getCCObjectFromJson(value), string(key));

            iter = json_object_iter_next(obj, iter);
        }

        return dictionary;
    }
    else if (json_is_array(obj)) {
        size_t sizeArray = json_array_size(obj);
        CCArray *array = CCArray::createWithCapacity(sizeArray);

        for (unsigned int i = 0; i < sizeArray; i++) {
            array->addObject(CCSoomlaJsonHelper::getCCObjectFromJson(json_array_get(obj, i)));
        }

        return array;
    }
    else if (json_is_boolean(obj)) {
        CCBool *ccBool = CCBool::create(json_is_true(obj));
        return ccBool;
    }
    else if (json_is_integer(obj)) {
        json_int_t intVal = json_integer_value(obj);

        CCInteger *ccInteger = CCInteger::create((int) intVal);
        return ccInteger;
    }
    else if (json_is_real(obj)) {
        double realVal = json_real_value(obj);

        CCDouble *ccDouble = CCDouble::create(realVal);
        return ccDouble;
    }
    else if (json_is_string(obj)) {
        stringstream str;
        str << json_string_value(obj);

        CCString *ccString = CCString::create(str.str());
        return ccString;
    }
    else if (json_is_null(obj)) {
        return CCString::create("");
    }
    else {
        CC_ASSERT(false);
        return NULL;
    }
}

json_t*CCSoomlaJsonHelper::getJsonFromCCObject(CCObject* obj) {
    if (dynamic_cast<CCDictionary *>(obj)) {
        CCDictionary *mainDict = (CCDictionary *) obj;
        CCArray *allKeys = mainDict->allKeys();
        json_t *jsonDict = json_object();

        if (allKeys == NULL ) return jsonDict;
        for (unsigned int i = 0; i < allKeys->count(); i++) {
            const char *key = ((CCString *) allKeys->objectAtIndex(i))->getCString();
            json_object_set_new(jsonDict,
                    key,
                    CCSoomlaJsonHelper::getJsonFromCCObject(mainDict->objectForKey(key)));
        }

        return jsonDict;
    }
    else if (dynamic_cast<CCArray *>(obj)) {
        CCArray *mainArray = (CCArray *) obj;
        json_t *jsonArray = json_array();

        for (unsigned int i = 0; i < mainArray->count(); i++) {
            json_array_append_new(jsonArray,
                    CCSoomlaJsonHelper::getJsonFromCCObject(mainArray->objectAtIndex(i)));
        }

        return jsonArray;
    }
    else if (dynamic_cast<CCString *>(obj)) {
        CCString *mainString = (CCString *) obj;
        json_t *jsonString = json_string(mainString->getCString());

        return jsonString;
    }
    else if (dynamic_cast<CCInteger *>(obj)) {
        CCInteger *mainInteger = (CCInteger *) obj;
        json_t *jsonInt = json_integer(mainInteger->getValue());

        return jsonInt;
    }
    else if (dynamic_cast<CCDouble *>(obj)) {
        CCDouble *mainDouble = (CCDouble *) obj;
        json_t *jsonReal = json_real(mainDouble->getValue());

        return jsonReal;
    }
    else if (dynamic_cast<CCFloat *>(obj)) {
        CCFloat *mainFloat = (CCFloat *) obj;
        json_t *jsonString = json_real(mainFloat->getValue());

        return jsonString;
    }
    else if (dynamic_cast<CCBool *>(obj)) {
        CCBool *mainBool = (CCBool *) obj;
        json_t *jsonBoolean = json_boolean(mainBool->getValue());

        return jsonBoolean;
    }
    else {
        CC_ASSERT(false);
        return NULL;
    }
}